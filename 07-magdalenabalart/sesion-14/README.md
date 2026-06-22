# sesion-14

lunes 15 junio 2026

# La sesión pasada quedamos con este código: 

```cpp
// -----------------------------
// SENSOR ULTRASÓNICO HC-SR04 + LED
// 3 condiciones + parpadeo + ausencia prolongada
// -----------------------------

const int trigPin = 2;
const int echoPin = 3;
const int ledPin = 6; // Pin PWM

long duracion;
float distancia;

String estadoActual = "";
String estadoAnterior = "";

// Control lectura sensor
unsigned long tiempoAnteriorSensor = 0;
const unsigned long intervaloSensor = 80;

// Control parpadeo LED
unsigned long tiempoAnteriorParpadeo = 0;
bool ledEncendido = false;

// Control ausencia prolongada
unsigned long tiempoInicioSinPresencia = 0;
bool contandoAusencia = false;
bool ausenciaProlongadaActivada = false;

const unsigned long tiempoAusencia = 120000;
// 120000 ms = 2 minutos

// Control encendido progresivo por ausencia
unsigned long tiempoAnteriorFade = 0;
const unsigned long intervaloFade = 200;
// Mientras más alto este número, más lento prende

int brilloAusencia = 0;

void setup() {
  Serial.begin(9600);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(ledPin, OUTPUT);

  analogWrite(ledPin, 0);

  Serial.println("Sistema iniciado");
}

void loop() {
  unsigned long tiempoActual = millis();

  // -----------------------------
  // LECTURA DEL SENSOR
  // -----------------------------
  if (tiempoActual - tiempoAnteriorSensor >= intervaloSensor) {
    tiempoAnteriorSensor = tiempoActual;

    distancia = medirDistancia();

    if (distancia < 0) {
      estadoActual = "No se detecta lectura valida";
    }

    else if (distancia > 230) {
      estadoActual = "sin presencia";
    }

    else if (distancia > 150 && distancia <= 230) {
      estadoActual = "hay alguien lejano";
    }

    else if (distancia > 50 && distancia <= 150) {
      estadoActual = "alguien se acerca";
    }

    else if (distancia <= 50) {
      estadoActual = "hay alguien cerca";
    }

    if (estadoActual != estadoAnterior) {
      Serial.print("Distancia medida: ");
      Serial.print(distancia);
      Serial.println(" cm");

      Serial.print("Mensaje para Totem 02: ");
      Serial.println(estadoActual);

      Serial.println("-------------------------");

      estadoAnterior = estadoActual;
    }
  }

  // -----------------------------
  // DETECTAR SI HAY O NO PRESENCIA
  // -----------------------------

  bool sinPresencia = 
    estadoActual == "sin presencia" || 
    estadoActual == "No se detecta lectura valida";

  if (sinPresencia) {
    if (contandoAusencia == false) {
      tiempoInicioSinPresencia = tiempoActual;
      contandoAusencia = true;
      ausenciaProlongadaActivada = false;
      brilloAusencia = 0;
    }

    if (tiempoActual - tiempoInicioSinPresencia >= tiempoAusencia) {
      ausenciaProlongadaActivada = true;
    }
  }

  else {
    contandoAusencia = false;
    ausenciaProlongadaActivada = false;
    brilloAusencia = 0;
  }

  // -----------------------------
  // CONTROL DEL LED
  // -----------------------------

  if (sinPresencia) {
    if (ausenciaProlongadaActivada) {
      encenderProgresivamentePorAusencia();

      if (estadoActual != "ausencia prolongada") {
        estadoActual = "ausencia prolongada";

        Serial.println("Mensaje para Totem 02: ausencia prolongada");
        Serial.println("LED encendiendose lentamente por ausencia");
        Serial.println("-------------------------");
      }
    }

    else {
      analogWrite(ledPin, 0);
      ledEncendido = false;
    }
  }

  else if (estadoActual == "hay alguien lejano") {
    parpadearLED(1000, 80);
    // parpadeo lento
  }

  else if (estadoActual == "alguien se acerca") {
    parpadearLED(400, 150);
    // parpadeo medio
  }

  else if (estadoActual == "hay alguien cerca") {
    analogWrite(ledPin, 255);
    // encendido fijo al máximo
    ledEncendido = true;
  }
}

// -----------------------------
// FUNCIÓN PARA MEDIR DISTANCIA
// -----------------------------
float medirDistancia() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duracion = pulseIn(echoPin, HIGH, 25000);

  if (duracion == 0) {
    return -1;
  }

  float distanciaCalculada = duracion * 0.0343 / 2;

  return distanciaCalculada;
}

// -----------------------------
// FUNCIÓN PARA PARPADEAR LED
// -----------------------------
void parpadearLED(unsigned long intervalo, int brillo) {
  unsigned long tiempoActual = millis();

  if (tiempoActual - tiempoAnteriorParpadeo >= intervalo) {
    tiempoAnteriorParpadeo = tiempoActual;

    ledEncendido = !ledEncendido;

    if (ledEncendido) {
      analogWrite(ledPin, brillo);
    } else {
      analogWrite(ledPin, 0);
    }
  }
}

// -----------------------------
// FUNCIÓN PARA AUSENCIA PROLONGADA
// -----------------------------
void encenderProgresivamentePorAusencia() {
  unsigned long tiempoActual = millis();

  if (tiempoActual - tiempoAnteriorFade >= intervaloFade) {
    tiempoAnteriorFade = tiempoActual;

    if (brilloAusencia < 255) {
      brilloAusencia++;
    }

    analogWrite(ledPin, brilloAusencia);
  }
}
```

y quedamos en que teníamos que corregir esto: 

esta correccion: También queda pendiente mejorar la lógica de envío de datos hacia Adafruit IO. Actualmente, el código trabaja con los valores del sensor en su estado natural, es decir, con lecturas numéricas constantes de distancia. Sin embargo, para no enviar demasiada información a Adafruit, la idea es simplificar y decodificar esos datos. En vez de mandar todas las mediciones del sensor, se podría enviar solo un valor o código por condición, por ejemplo:

0 = sin presencia  
1 = alguien lejano  
2 = alguien se acerca  
3 = alguien cerca  
4 = ausencia prolongada   

y agregar un modo demo con botón. 

# Tótem 01: sensor, botón y LED 
 
Se trabajó sobre el código del primer tótem, encargado de detectar la cercanía de una persona mediante un sensor ultrasónico HC-SR04. Inicialmente, el sensor enviaba demasiada información porque trabajaba directamente con las lecturas numéricas de distancia. Para resolver esto, se implementó una lógica de decodificación, donde las distancias se transforman en códigos simples antes de ser enviadas.

La lógica final quedó organizada así:

0 = sin presencia  
1 = distancia 01  
2 = distancia 02  
3 = distancia 03  
4 = ausencia prolongada  

Además, se ajustaron los rangos de distancia para que la detección fuera más coherente con la escala real del prototipo:

100 cm o más = sin presencia  
70 a 99 cm = distancia 01  
40 a 69 cm = distancia 02  
menos de 40 cm = distancia 03  

Para evitar lecturas inestables, se incorporó un promedio de mediciones del sensor. Esto permite que el sistema no reaccione frente a una sola lectura aislada, sino que calcule un valor más estable antes de cambiar de estado. También se agregó una confirmación temporal para que el cambio de estado ocurra solo cuando la condición se mantiene durante un breve periodo. 

### Modo demo con botón 

 Se agregó un botón para poder demostrar el funcionamiento del sistema sin depender de que una persona se ubique físicamente frente al sensor durante la presentación o examen. El botón quedó conectado con positivo al pin 7, señal al pin 4 y GND a GND.

La lógica del botón quedó así:

Primera presión = distancia 01  
Segunda presión = distancia 02  
Tercera presión = distancia 03  
Cuarta presión = ausencia prolongada  
Quinta presión = vuelve al modo sensor  

Esto permite recorrer todos los estados del sistema de forma manual y controlada. 

### Comportamiento del LED 

También se ajustó el comportamiento del LED para que respondiera de forma distinta según el nivel de cercanía detectado.

La lógica lumínica quedó definida así:

Sin presencia = LED apagado  
Distancia 01 = titileo muy lento  
Distancia 02 = titileo más rápido  
Distancia 03 = LED encendido fijo  
Ausencia prolongada = encendido progresivo  

En el caso de ausencia prolongada, se configuró un fade progresivo para que el LED aumente su brillo lentamente hasta llegar al máximo en 10 segundos. Esta decisión permite que la ausencia no se represente como un apagado inmediato, sino como una activación más lenta y atmosférica. 

### Envío de datos a Adafruit IO 

Se preparó el código para enviar la información a Adafruit IO. En vez de enviar todas las mediciones del sensor, el sistema envía solamente el código correspondiente al estado actual. Esto reduce la cantidad de datos enviados y hace más clara la comunicación entre dispositivos.

El envío se realiza únicamente cuando cambia el estado, evitando mandar información repetida constantemente.  

# Tótem 02: pantalla y servo 

También se comenzó a construir el código del segundo tótem. Este segundo Arduino recibe los códigos enviados por el Tótem 01 a través de Adafruit IO. Según el código recibido, el sistema muestra un mensaje en una pantalla OLED y mueve un servo a distintos grados.

La lógica propuesta para el servo es:

0 = sin presencia → servo en 0°  
1 = distancia 01 → servo en 45°  
2 = distancia 02 → servo en 90°  
3 = distancia 03 → servo en 135°  
4 = ausencia prolongada → movimiento irregular automático  

Para la ausencia prolongada, se propuso que el servo no quede fijo, sino que se mueva de manera irregular entre distintos ángulos. Esto busca generar una reacción más extraña o inquietante, diferenciándola de los estados normales de cercanía. 

# Tótem 02 Código
```cpp
// -----------------------------
// TOTEM 02
// Recibe datos desde Adafruit IO
// Pantalla OLED + Servo
//
// Recibe códigos desde TOTEM01:
// 0 = sin presencia
// 1 = distancia 01
// 2 = distancia 02
// 3 = distancia 03
// 4 = ausencia prolongada
//
// Pantalla: muestra mensaje
// Servo: se mueve según cercanía
// En ausencia prolongada: movimiento raro automático
// -----------------------------

#include "AdafruitIO_WiFi.h"
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Servo.h>

// -----------------------------
// DATOS ADAFRUIT IO
// -----------------------------

#define IO_USERNAME  "Magdalena"
#define IO_KEY       ""

#define WIFI_SSID    "Jesu"
#define WIFI_PASS    "slay4321"

AdafruitIO_WiFi io(IO_USERNAME, IO_KEY, WIFI_SSID, WIFI_PASS);

// Debe ser el mismo feed que usa el Totem 01
AdafruitIO_Feed *estadoFeed = io.feed("TOTEM01");

// -----------------------------
// CÓDIGOS RECIBIDOS
// -----------------------------

const int COD_SIN_PRESENCIA = 0;
const int COD_DISTANCIA_01 = 1;
const int COD_DISTANCIA_02 = 2;
const int COD_DISTANCIA_03 = 3;
const int COD_AUSENCIA = 4;

// -----------------------------
// PANTALLA OLED
// -----------------------------

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1

Adafruit_SSD1306 display(
  SCREEN_WIDTH,
  SCREEN_HEIGHT,
  &Wire,
  OLED_RESET
);

// -----------------------------
// SERVO
// -----------------------------

Servo servoDistancia;

const int servoPin = 9;

// Grados del servo por cercanía
const int gradoSinPresencia = 0;
const int gradoDistancia01 = 45;
const int gradoDistancia02 = 90;
const int gradoDistancia03 = 135;

// -----------------------------
// MOVIMIENTO RARO EN AUSENCIA
// -----------------------------

bool movimientoAusenciaActivo = false;

int anguloActualServo = 0;
int anguloObjetivoServo = 0;

unsigned long tiempoAnteriorMovimientoServo = 0;
unsigned long tiempoAnteriorCambioObjetivo = 0;

unsigned long intervaloMovimientoServo = 25;
unsigned long intervaloCambioObjetivo = 500;

// -----------------------------
// VARIABLES GENERALES
// -----------------------------

int codigoActual = -1;
int codigoAnterior = -2;

String mensajeActual = "";
int gradoActual = 0;

// -----------------------------
// SETUP
// -----------------------------

void setup() {
  Serial.begin(9600);

  // -----------------------------
  // INICIAR PANTALLA
  // -----------------------------

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("No se encontro pantalla OLED");
    while (true);
  }

  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println("Totem 02");
  display.println("Iniciando...");
  display.display();

  // -----------------------------
  // INICIAR SERVO
  // -----------------------------

  servoDistancia.attach(servoPin);

  gradoActual = gradoSinPresencia;
  anguloActualServo = gradoSinPresencia;
  anguloObjetivoServo = gradoSinPresencia;

  servoDistancia.write(gradoSinPresencia);

  // Semilla para movimiento irregular
  randomSeed(analogRead(A0));

  // -----------------------------
  // CONFIGURAR ADAFRUIT IO
  // -----------------------------

  estadoFeed->onMessage(recibirEstado);

  Serial.print("Conectando a Adafruit IO");

  io.connect();

  while (io.status() < AIO_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.println();
  Serial.println("Conectado a Adafruit IO");
  Serial.println("-------------------------");

  display.clearDisplay();
  display.setCursor(0, 0);
  display.println("Totem 02");
  display.println("Conectado");
  display.println("Esperando datos...");
  display.display();

  // Pide el último valor del feed
  estadoFeed->get();
}

// -----------------------------
// LOOP
// -----------------------------

void loop() {
  // Mantiene viva la conexión con Adafruit IO
  io.run();

  // Si está en ausencia prolongada,
  // el servo se mueve de forma irregular
  if (movimientoAusenciaActivo) {
    moverServoAusenciaRara();
  }
}

// -----------------------------
// RECIBIR ESTADO DESDE ADAFRUIT IO
// -----------------------------

void recibirEstado(AdafruitIO_Data *data) {
  int codigoRecibido = data->toInt();

  Serial.print("Codigo recibido: ");
  Serial.println(codigoRecibido);

  // Evita repetir la misma acción si llega el mismo código
  if (codigoRecibido == codigoAnterior) {
    return;
  }

  codigoActual = codigoRecibido;
  codigoAnterior = codigoActual;

  interpretarCodigo(codigoActual);
}

// -----------------------------
// INTERPRETAR CÓDIGO RECIBIDO
// -----------------------------

void interpretarCodigo(int codigo) {
  if (codigo == COD_SIN_PRESENCIA) {
    mensajeActual = "Sin presencia";
    gradoActual = gradoSinPresencia;

    movimientoAusenciaActivo = false;

    moverServoFijo(gradoActual);
    mostrarEnPantalla(mensajeActual, codigo, gradoActual);
  }

  else if (codigo == COD_DISTANCIA_01) {
    mensajeActual = "Distancia 01";
    gradoActual = gradoDistancia01;

    movimientoAusenciaActivo = false;

    moverServoFijo(gradoActual);
    mostrarEnPantalla(mensajeActual, codigo, gradoActual);
  }

  else if (codigo == COD_DISTANCIA_02) {
    mensajeActual = "Distancia 02";
    gradoActual = gradoDistancia02;

    movimientoAusenciaActivo = false;

    moverServoFijo(gradoActual);
    mostrarEnPantalla(mensajeActual, codigo, gradoActual);
  }

  else if (codigo == COD_DISTANCIA_03) {
    mensajeActual = "Distancia 03";
    gradoActual = gradoDistancia03;

    movimientoAusenciaActivo = false;

    moverServoFijo(gradoActual);
    mostrarEnPantalla(mensajeActual, codigo, gradoActual);
  }

  else if (codigo == COD_AUSENCIA) {
    mensajeActual = "Ausencia prolongada";

    movimientoAusenciaActivo = true;

    anguloObjetivoServo = random(20, 161);
    tiempoAnteriorCambioObjetivo = millis();
    tiempoAnteriorMovimientoServo = millis();

    mostrarEnPantallaAusencia(mensajeActual, codigo);
  }

  else {
    mensajeActual = "Codigo no valido";
    gradoActual = gradoSinPresencia;

    movimientoAusenciaActivo = false;

    moverServoFijo(gradoActual);
    mostrarEnPantalla(mensajeActual, codigo, gradoActual);
  }

  Serial.print("Mensaje: ");
  Serial.println(mensajeActual);

  if (codigo == COD_AUSENCIA) {
    Serial.println("Servo en movimiento raro");
  } else {
    Serial.print("Servo en grados: ");
    Serial.println(gradoActual);
  }

  Serial.println("-------------------------");
}

// -----------------------------
// MOVER SERVO A GRADO FIJO
// -----------------------------

void moverServoFijo(int grado) {
  servoDistancia.write(grado);

  anguloActualServo = grado;
  anguloObjetivoServo = grado;
}

// -----------------------------
// MOVIMIENTO RARO DEL SERVO
// EN AUSENCIA PROLONGADA
// -----------------------------

void moverServoAusenciaRara() {
  unsigned long tiempoActual = millis();

  // Cada cierto tiempo escoge un nuevo ángulo
  if (
    tiempoActual - tiempoAnteriorCambioObjetivo >=
    intervaloCambioObjetivo
  ) {
    tiempoAnteriorCambioObjetivo = tiempoActual;

    // Nuevo ángulo entre 20° y 160°
    anguloObjetivoServo = random(20, 161);

    // Cambia el ritmo para que se sienta irregular
    intervaloCambioObjetivo = random(300, 1200);
    intervaloMovimientoServo = random(15, 60);
  }

  // Movimiento progresivo hacia el objetivo
  if (
    tiempoActual - tiempoAnteriorMovimientoServo >=
    intervaloMovimientoServo
  ) {
    tiempoAnteriorMovimientoServo = tiempoActual;

    if (anguloActualServo < anguloObjetivoServo) {
      anguloActualServo++;
    }

    else if (anguloActualServo > anguloObjetivoServo) {
      anguloActualServo--;
    }

    servoDistancia.write(anguloActualServo);
  }
}

// -----------------------------
// MOSTRAR MENSAJE EN PANTALLA
// -----------------------------

void mostrarEnPantalla(String mensaje, int codigo, int gradoServo) {
  display.clearDisplay();

  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println("Totem 02");

  display.setCursor(0, 14);
  display.println("Mensaje:");

  display.setTextSize(2);
  display.setCursor(0, 26);
  display.println(mensaje);

  display.setTextSize(1);
  display.setCursor(0, 54);
  display.print("Cod:");
  display.print(codigo);

  display.setCursor(55, 54);
  display.print("Servo:");
  display.print(gradoServo);
  display.print((char)247);

  display.display();
}

// -----------------------------
// PANTALLA PARA AUSENCIA
// -----------------------------

void mostrarEnPantallaAusencia(String mensaje, int codigo) {
  display.clearDisplay();

  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println("Totem 02");

  display.setCursor(0, 14);
  display.println("Mensaje:");

  display.setTextSize(1);
  display.setCursor(0, 28);
  display.println(mensaje);

  display.setCursor(0, 50);
  display.print("Cod:");
  display.print(codigo);

  display.setCursor(55, 50);
  display.print("Servo: auto");

  display.display();
}
``` 
### Problemas revisados durante la sesión

Durante la sesión también se resolvieron varios problemas técnicos:

Se revisó la conexión del LED al pin 6 y GND.  
Se probó el LED con códigos simples para comprobar que el problema no fuera de hardware.  
Se corrigieron errores de puerto en Arduino IDE.  
Se ajustó el código para que no se quedara bloqueado si Adafruit IO no lograba conectarse.  
Se detectó que el segundo tótem quedaba en “Iniciando…” porque estaba esperando indefinidamente la conexión a internet.  
Se propuso una conexión a Adafruit con tiempo máximo de espera, para que el sistema pueda informar si no logra conectarse.   

# Consideración sobre la sensibilidad del sensor

Durante las pruebas se identificó que el sensor ultrasónico es bastante sensible a las variaciones del entorno y a pequeños cambios de posición. Por esta razón, las distancias de activación debieron definirse de manera muy específica para que cada estado respondiera correctamente.

Los rangos finales quedaron delimitados con precisión:

100 cm o más = sin presencia  
70 a 99 cm = distancia 01  
40 a 69 cm = distancia 02  
menos de 40 cm = distancia 03  

A partir de esta sensibilidad, se planteó la necesidad de generar una especie de recorrido marcado en el suelo. La idea es señalar visualmente las distancias frente al tótem para que la interacción sea más clara, controlada y limpia. De esta manera, la persona usuaria puede ubicarse dentro de cada rango sin confusión, y el sistema puede responder de forma más estable durante la demostración o presentación del proyecto.

