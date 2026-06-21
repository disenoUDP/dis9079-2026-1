//  BRUMA COMPACTA

//  El Arduino escucha los datos de humedad que la Raspberry Pi Pico 2W
//  publica en Adafruit IO. Cuando llegan los 8 datos (uno por ciudad),
//  hace una ruleta con los LEDs para elegir una ciudad al azar y muestra
//  el resultado con colores: verde si hay humedad alta (sobre e igual a 35%), rojo si hay poca (bajo 35%).

//  Bibliotecas necesarias:
//    - ArduinoMqttClient  (Arduino)
//    - Adafruit NeoPixel  (Adafruit)
//
//  Pines:
//    D2 a Módulo RGB 8 bits	WS2812 (Data Neo Pixel)

// Estas tres líneas traen al código las bibliotecas instaladas. 

#include <WiFiS3.h>
#include <ArduinoMqttClient.h>
#include <Adafruit_NeoPixel.h>

// Definir credenciales constantes

const char* WIFI_SSID     = "tuRedWiFi";
const char* WIFI_PASSWORD = "tuContraseñaWifi";


const char* AIO_USER      = "tuUserAIO";
const char* AIO_KEY       = "tuAIOkey";


const char* AIO_BROKER    = "io.adafruit.com";
const int   AIO_PORT      = 1883;

// define pines y cantidad de LEDs RGB

#define PIN_NEOPIXEL  2  // pin de datos de la ruleta
#define NUM_LEDS      8  // un led por ciudad

// Definir ciudades y su feed respectivo en Adafruit
// Estos dos arrays funcionan como una tabla de dos columnas.
// La fila 1 es Arica, la fila 2 es Copiapó, y así hasta la 8 que es Antártica.
// El LED número 1 representa a Arica, el LED 2 a Copiapó, etc.


const char* NOMBRES[NUM_LEDS] = {
  "Arica",           // LED 0
  "Copiapo",         // LED 1
  "Santiago",        // LED 2
  "Valparaiso",      // LED 3
  "Isla de Pascua",  // LED 4
  "Juan Fernandez",  // LED 5
  "Punta Arenas",    // LED 6
  "Antartica"        // LED 7
};

// Direcciones exactas de los feeds en Adafruit IO a las cuales se suscribe el Arduino

const char* FEEDS[NUM_LEDS] = {
  "nicolasvgreve/feeds/humedad-arica",
  "nicolasvgreve/feeds/humedad-copiapo",
  "nicolasvgreve/feeds/humedad-santiago",
  "nicolasvgreve/feeds/humedad-valparaiso",
  "nicolasvgreve/feeds/humedad-isla-pascua",
  "nicolasvgreve/feeds/humedad-juan-fernandez",
  "nicolasvgreve/feeds/humedad-punta-arenas",
  "nicolasvgreve/feeds/humedad-antartica"
};

// Definición de colores en RGB 

#define COLOR_RULETA         pixels.Color(0,   80,  255)  // azul — mientras la ruleta gira
#define COLOR_GANADOR_HUMEDO pixels.Color(0,   200, 50)   // verde — ciudad con humedad >= 35%
#define COLOR_GANADOR_SECO   pixels.Color(220, 30,  0)    // rojo  — ciudad con humedad < 35%
#define COLOR_CONFIRMACION   pixels.Color(0,   40,  10)   // verde tenue — confirma que llegó el dato de esa ciudad
#define COLOR_FONDO          pixels.Color(0,   5,   20)   // azul muy tenue 

// Umbral humedad
// Si la humedad de la ciudad sorteada es igual o mayor a 35%, el LED se pone verde, si es menor, se pone rojo.


const int UMBRAL_HUMEDAD = 35;

// Define el estado — administrado con arrays 

// Estas variables recuerdan los datos del ciclo actual.
// Cuando termina un ciclo, se resetean para empezar de cero.

// Guarda el porcentaje de humedad de cada ciudad.
// Empieza en -1 porque -1 significa que todavía no llegó ningún dato de esta ciudad.

int  humedades[NUM_LEDS];      // guarda el % de humedad de cada ciudad (-1 si aún no llegó)

// Registra con true/false si ya llegó el dato de cada ciudad, empieza todo en false (no ha llegado ni un dato).

bool feedRecibido[NUM_LEDS];   

int  ciudadGanadora = -1;      // índice de la ciudad elegida por la ruleta (-1 = todavía no se sortea)

bool todosListos    = false;   // se vuelve true cuando llegaron los 8 datos y se puede sortear

// Objetos
// Crea el objeto que controla el módulo NeoPixel.
// Le decimos cuántos LEDs tiene, en qué pin está el cable de datos y el tipo de señal que entiende ese modelo (NEO_GRB + NEO_KHZ800).

Adafruit_NeoPixel pixels(NUM_LEDS, PIN_NEOPIXEL, NEO_GRB + NEO_KHZ800);

WiFiClient  wifiClient;
MqttClient  mqttClient(wifiClient);

// Funciones de ayuda para los arrays, encapsulan las operaciones repetitivas sobre los arrays.
// Recibe el topic de un mensaje MQTT y busca en el array FEEDS a qué ciudad pertenece. Devuelve el índice (1-8) o -1 si no lo encuentra.

int buscarCiudad(const String& topic) {
  for (int i = 0; i < NUM_LEDS; i++) {
        // Compara el topic recibido con cada dirección guardada en el array
    if (topic == String(FEEDS[i])) return i;
  }
  return -1; // no encontró ninguna coincidencia
}

// Recorre feedRecibido[] y cuenta cuántas ciudades ya mandaron su dato y muestra el proceso en el monitor serial

int contarFeedsRecibidos() {
  int count = 0;
  for (int i = 0; i < NUM_LEDS; i++) {
    if (feedRecibido[i]) count++; // si esta ciudad ya mandó dato, suma 1
  }
  return count; // devuelve el total acumulado
}

// Revisa si todos los elementos de feedRecibido[] son true, si encuentra uno en false, sabe que falta alguno y para de buscar.

bool todosLosFeeds() {
  for (int i = 0; i < NUM_LEDS; i++) {
    if (!feedRecibido[i]) return false; // encontró un false por lo que falta ese dato
  }
  return true; // si se llega a esta etapa, todos están true
}

// Pone los dos arrays de estado en sus valores iniciales, se llama al encender el Arduino y también al terminar cada ciclo.
// Al hacerlo en un solo for, los dos arrays siempre quedan sincronizados.

void resetearArrays() {
  for (int i = 0; i < NUM_LEDS; i++) {
    humedades[i]    = -1; // -1 significa que no ha llegado ni un dato
    feedRecibido[i] = false; // false = aún no llegó nada de esta ciudad
  }
}

// Apaga los 8 LEDs del módulo uno por uno y luego llama a show() para que el cambio se vea físicamente en la ruleta de LEDs
// (show() es necesario porque los cambios no se aplican hasta llamarlo)

void apagarLeds() {
  for (int i = 0; i < NUM_LEDS; i++) {
    pixels.setPixelColor(i, 0); // color 0 = negro = apagado
  }
  pixels.show(); // aplica los cambios a la ruleta
}

// Setup, corre una sola vez cuando el Arduino se enciende o se reinicia

void setup() {
  Serial.begin(115200);
  while (!Serial); // espera a que el puerto serial esté listo antes de continuar


  resetearArrays();   // Dejar los arrays limpios antes de empezar


  pixels.begin();
  pixels.setBrightness(180);
  apagarLeds();
  animacionArranque();   // Encender la ruleta y dar la bienvenida con las luces

  // Conectar al WiFi y luego a Adafruit IO por MQTT

  conectarWifi();

  // Le decimos a cliente MQTT que funione el callback cuando llegue un mensaje (recibirMensaje() se ejecutará automáticamente cada vez que Adafruit IO nos mande un dato nuevo.

  mqttClient.setId("arduino-humedad-instalacion");
  mqttClient.setUsernamePassword(AIO_USER, AIO_KEY);
  mqttClient.onMessage(recibirMensaje); // registrar el callback
  conectarMqtt();

  // Suscribirse a los 8 feeds usando el array para no escribir 8 veces lo mismo.
  // Suscribirse significa pedirle a Adafruit IO que nos avise cada vez
  // que llegue un dato nuevo a cada uno de esos feeds.

  for (int i = 0; i < NUM_LEDS; i++) {
    mqttClient.subscribe(FEEDS[i]);
    Serial.print("Suscrito: ");
    Serial.println(FEEDS[i]);
  }

  Serial.println("Esperando que el mago haga su truco y se teletransporte...");
}

// Loop Principal se repite indefinidamente mientras el Arduino esté encendido

void loop() {
  if (WiFi.status() != WL_CONNECTED) conectarWifi();
  if (!mqttClient.connected())        conectarMqtt();

  mqttClient.poll();

  if (todosListos && ciudadGanadora == -1) {
    delay(500);
    ejecutarRuleta();
  }
}

//  CALLBACK MQTT
//  Esta función la llama automáticamente mqttClient.poll() cada vez que llega un mensaje desde Adafruit IO.


void recibirMensaje(int messageSize) {  //  messageSize es el tamaño del mensaje en bytes — lo recibe sola, no hay que pasarlo.

// Leer de qué feed vino el mensaje — por ejemplo "nicolasvgreve/feeds/humedad-santiago"
  String topic   = mqttClient.messageTopic();



  String payload = ""; 
  while (mqttClient.available()) {   // Leer el valor que mandó la raspi 
    payload += (char)mqttClient.read();   // Se construye letra por letra porque llega como un flujo de bytes
  }

  // Buscar ciudad usando la función de array
  int idx = buscarCiudad(topic);
  if (idx == -1) return;   // -1 = topic desconocido, ignorar

  humedades[idx]    = payload.toInt();   // Guardar el porcentaje de humedad en el lugar que le corresponde en el array. toInt() convierte el texto "72" al número entero 72.
  feedRecibido[idx] = true;

  Serial.print("El mago visitó ");
  Serial.print(NOMBRES[idx]); // Nombre de la ciudad
  Serial.print(" y descubrió que tiene un ");
  Serial.print(humedades[idx]); // Porcentaje de humedad
  Serial.print("% de humedad  (");
  Serial.print(contarFeedsRecibidos());  // Cuántas ciudades han llegado hasta ahora
  Serial.println("/8 ciudades visitadas)");

  // Encender el LED de esta ciudad en verde tenue para confirmar visualmente

  pixels.setPixelColor(idx, COLOR_CONFIRMACION);
  pixels.show();

  // Verificar si ya llegaron todos usando la función de array
  if (!todosListos && todosLosFeeds()) {
    todosListos = true;
    Serial.println(" . Iniciando ruleta... (ojalá no caiga en Copiapó)");
  }
}

// Ruleta

void ejecutarRuleta() {
  
  // Generar una semilla aleatoria leyendo el ruido eléctrico de dos pines analógicos que están al aire (sin nada conectado). Sin el randomSeed, el resultado 
  // del sorteo sería siempre el mismo. Con él, cada vez que la raspi manda datos nuevos y se corre la ruleta, la ciudad ganadora es genuinamente al azar.

  randomSeed(analogRead(A0) + analogRead(A1));

    // Elegir un número al azar entre 1 y 8 (los 8 índices del array)

  ciudadGanadora = random(0, NUM_LEDS);

  // Confirmar en el Serial Monitor qué ciudad fue elegida

  Serial.print("\n★ Ciudad seleccionada: ");
  Serial.print(NOMBRES[ciudadGanadora]);
  Serial.print(" (");
  Serial.print(humedades[ciudadGanadora]);
  Serial.println("%)");

  // Fase 1 de la ruleta: todos parpadean en azul para generar suspenso

  for (int ronda = 0; ronda < 5; ronda++) { // bucle se repite 5 veces

      // Encender todos los LEDs en azul
    for (int i = 0; i < NUM_LEDS; i++) {
      pixels.setPixelColor(i, COLOR_RULETA);
    }
    pixels.show();
    delay(180); // Quedarse en azul por 180 milisegundos 
    apagarLeds();
    delay(120); // Descansa por 120 milisegundos
  }
  delay(300); // Descansa 300 ms antes de arrancar la ruleta

  // Fase 2: barrido que frena gradualmente
  // totalPasos está calculado para que el último paso caiga exactamente en el índice de la ciudad ganadora.
  // Por ejemplo: si ganó Santiago (índice 2), totalPasos = 30 + 2 = 32.

  int totalPasos = (NUM_LEDS * 4) + ciudadGanadora;

  for (int paso = 0; paso < totalPasos; paso++) {
    // Calcular el porcentaje de progreso del barrido (de 0% a 100%)
    int progreso = paso * 100 / totalPasos;

    // Según el progreso, asignar un tiempo de espera entre pasos.
    // Al principio espera poco (va rápido), al final espera más (va lento).
    int delayMs;
    if      (progreso < 40) delayMs = 60;  // primero 40% va corriendo rápido
    else if (progreso < 70) delayMs = 100; // siguiente 30% frena de apoquito 
    else if (progreso < 85) delayMs = 160; // siguiente 15% frena más fuerte
    else                    delayMs = 240; // último patita, casi detenido

    int posActual = paso % NUM_LEDS;     // Calcular en qué LED está el punto brillante ahora mismo.

  
    for (int i = 0; i < NUM_LEDS; i++) {
      pixels.setPixelColor(i, COLOR_FONDO);   // Poner todos los LEDs en azul muy oscuro 
    }
    pixels.setPixelColor(posActual, COLOR_RULETA);     // Encender solo el LED de la posición actual en azul vivo
    pixels.show();
    delay(delayMs);    // esperar según la velocidad de esta etapa
  }

  // Se revela la ciudad ganadora!!!! 

  int humGanadora = humedades[ciudadGanadora];   // Leer la humedad de la ciudad ganadora
  uint32_t colorGanador = (humGanadora >= UMBRAL_HUMEDAD)   // Elegir el color según si la humedad supera o no el umbral de 35%
                          ? COLOR_GANADOR_HUMEDO  // mayor e igual a 35% verde
                          : COLOR_GANADOR_SECO;   // menor a 35% rojo

  apagarLeds();
  delay(400);   // Apagar todo y esperar un poquito, para mas impacto


  for (int destello = 0; destello < 3; destello++) {   // 3 destellos del ganador
    pixels.setPixelColor(ciudadGanadora, colorGanador);
    pixels.show();
    delay(250);
    apagarLeds();
    delay(150);
  }

  // LED ganador fijo
  pixels.setPixelColor(ciudadGanadora, colorGanador);
  pixels.show();

  Serial.print("Resultado: ");
  Serial.print(NOMBRES[ciudadGanadora]);
  Serial.print(" | ");
  Serial.print(humGanadora);
  Serial.print("% | ");
  Serial.println(humGanadora >= UMBRAL_HUMEDAD ? "Humedo" : "Copiapó (seco)");   // Si humedad >= 35 imprime "Humedo", si no imprime "Copiapó (seco)"
  Serial.println("Esperando que el mago se recupere");

  resetearEstado(); // Iniciar el proceso de reseteo para dejar todo listo para el próximo ciclo
}

// Reset

void resetearEstado() {
  delay(10000);   // mantener resultado 10 segundos antes de borrar todo

  // Volver las variables de control a su estado inicial

  ciudadGanadora = -1; // -1 significa no hay ciudad sorteada aún
  todosListos    = false; // false significa que esperamos a los 8 feeds de nuevo
  resetearArrays();   // resetea humedades[] y feedRecibido[] en un solo for
  apagarLeds();       // apaga todos los LEDs en un solo for

  Serial.println("Estado reseteado. Listo para nuevo truco de magia");
}

// Conexión wifi

void conectarWifi() {
  Serial.print("Alineando los astros (Conectando a WiFi)");
  int intentos = 0;
  while (WiFi.begin(WIFI_SSID, WIFI_PASSWORD) != WL_CONNECTED && intentos < 20) {
    pixels.setPixelColor(0, pixels.Color(60, 60, 60));
    pixels.show();
    delay(300);
    pixels.setPixelColor(0, 0);
    pixels.show();
    delay(200);
    Serial.print(".");
    intentos++;
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.print(" Astros alineado (se conectó a WiFi) IP: ");
    Serial.println(WiFi.localIP());
  } else {
    Serial.println(" ERROR: No se alinearon los astros :( (no se pudo conectar a WiFi)");
    while (true) {   // parpadeo rojo de error permanente
      pixels.setPixelColor(0, pixels.Color(200, 0, 0));
      pixels.show();
      delay(200);
      pixels.setPixelColor(0, 0);
      pixels.show();
      delay(200);
    }
  }
}

// Conexión MQTT

void conectarMqtt() {
  Serial.print("Conectando a Adafruit IO");
  int intentos = 0;
  while (!mqttClient.connect(AIO_BROKER, AIO_PORT) && intentos < 10) {
    Serial.print("Reintentando en 3s...");
    delay(3000);
    intentos++;
  }

  if (mqttClient.connected()) {
    Serial.println("MQTT conectado :D!");
    // Re-suscribir a todos los feeds usando el array
    for (int i = 0; i < NUM_LEDS; i++) {
      mqttClient.subscribe(FEEDS[i]);
    }
  } else {
    Serial.print("Error MQTT :( ");
    Serial.println(mqttClient.connectError());
  }
}  // ← llave de cierre de conectarMqtt()

// Animación arranque

void animacionArranque() {
  // Barrido blanco recorriendo el array de LEDs
  for (int i = 0; i < NUM_LEDS; i++) {
    pixels.setPixelColor(i, pixels.Color(80, 80, 80));  //  Enciende los LEDs uno por uno de izquierda a derecha en blanco.
    //  Sirve para confirmar que el módulo está funcionando y todos los LEDs responden.
    pixels.show();
    delay(80);
  }
  delay(300);
  apagarLeds();
}
