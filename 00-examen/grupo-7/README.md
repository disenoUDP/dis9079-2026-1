# grupo-7

* brauliofigueroa2001
* marlensoto-lab
* Luisaatoro9
* marcezm

# La Voz de las Plantas — Grupo 07

## Declaración de uso de IA

Durante todo el desarrollo del proyecto se utilizó Claude (Anthropic) como herramienta de apoyo. Su rol fue el de guía técnica y acompañamiento en el proceso de aprendizaje, no generó el concepto del proyecto ni tomó decisiones creativas. Todas las decisiones de diseño, concepto y dirección fueron del grupo. A continuación se detalla exactamente cómo y cuándo se usó.

## 1. Contexto inicial y definición del proyecto

El grupo comenzó con una idea general: hacer visible el mundo invisible de las plantas y hongos, dándoles una voz a través de tecnología. La propuesta inicial era traducir señales de la planta en sonido, pero a lo largo del proceso fue evolucionando hacia una visualización generativa en tiempo real combinada con sonido.

**Uso de IA en esta etapa:** Se consultó a Claude para entender qué era posible técnicamente con los materiales disponibles (Arduino UNO R4 WiFi, Raspberry Pi Pico 2W). Claude explicó el concepto de bio-conductividad, cómo las plantas cambian sus micro-voltajes internos según estímulos externos, y sugirió el módulo ADS1115 como solución al problema de resolución del Arduino Pico.

**Prompt utilizado:**

"Tenemos una planta y queremos medir sus señales eléctricas. ¿Qué necesitamos para eso?"

Claude respondió explicando que la Raspberry Pi Pico tiene solo 12 bits de resolución analógica, insuficiente para micro-voltajes, y recomendó el ADS1115 de 16 bits.

### Código de prueba — primera verificación del ADS1115

```cpp
#include <Wire.h>
#include <Adafruit_ADS1X15.h>

Adafruit_ADS1115 ads;

void setup() {
  Serial.begin(9600);
  Serial.println("=== PRUEBA ADS1115 ===");

  if (!ads.begin()) {
    Serial.println("ERROR: No se encontro el ADS1115.");
    Serial.println("Revisar conexiones VDD, GND, SDA, SCL.");
    while (1);
  }

  Serial.println("ADS1115 encontrado correctamente.");
  Serial.println("Leyendo los 4 canales cada 1 segundo...");
  Serial.println("-------------------------------------");
}

void loop() {
  for (int i = 0; i < 4; i++) {
    int valor = ads.readADC_SingleEnded(i);
    float voltaje = ads.computeVolts(valor);

    Serial.print("Canal ");
    Serial.print(i);
    Serial.print(": ");
    Serial.print(valor);
    Serial.print(" raw  |  ");
    Serial.print(voltaje, 4);
    Serial.println(" V");
  }

  Serial.println("-------------------------------------");
  delay(1000);
}
```

### Resultado de la prueba

Sin tocar nada, todos los canales se mantuvieron estables alrededor de 3150 raw (~0.59V). Al tocar el pin A0 con el dedo, el Canal 0 subió a 4329 raw (0.81V), mientras los otros canales se mantuvieron estables.

Esto confirmó tres cosas importantes:
- El ADS1115 detecta señales externas correctamente.
- Los canales son independientes: tocar A0 solo cambia el Canal 0.
- La sensibilidad del módulo es suficiente para detectar la planta.

Posteriormente se realizaron las conexiones físicas completas: primero la planta hacia el ADS1115 mediante pinzas de cocodrilo, y luego el ADS1115 hacia el Arduino. Una vez conectado todo el sistema, se comprobó que estaba funcionando correctamente.

Una segunda prueba consistió en acercar la mano a una hoja sin tocarla directamente. El resultado confirmó que el sistema funciona incluso a distancia: el Canal 0 subió más de 1000 puntos solo con la mano cerca de la planta, sin contacto físico.

**Proceso de conexiones realizadas:**
1. Conectar la planta con los cables al ADS1115.
2. Conexión del ADS1115 a Arduino.
3. Pinzas de cocodrilo al ADS1115.
4. Sistema completo armado y funcionando.

¡Funciona perfectamente! El Canal 0 subió más de 1000 puntos sin tocar la planta, solo acercando la mano.

### Código de prueba mejorado — calibración automática y visualización en consola

Esta segunda versión se usó para comprobar de forma más clara los cambios detectados por cada canal, agregando una calibración automática de los valores base y una representación visual con barras directamente en el Monitor Serial.

```cpp
// ============================================================
// PRUEBA ADS1115 - Grupo 07
// Version mejorada: muestra cambios de forma clara
// ============================================================

#include <Wire.h>
#include <Adafruit_ADS1X15.h>

Adafruit_ADS1115 ads;

// Valor base de cada canal (sin tocar la planta)
// El codigo lo calibra solo los primeros 3 segundos
int base[4] = {0, 0, 0, 0};
bool calibrado = false;

void setup() {
  Serial.begin(9600);

  if (!ads.begin()) {
    Serial.println("ERROR: ADS1115 no encontrado. Revisar cables.");
    while (1);
  }

  ads.setGain(GAIN_SIXTEEN); // maxima sensibilidad

  Serial.println("Calibrando... no toques la planta");
  delay(1000);

  for (int i = 0; i < 4; i++) {
    long suma = 0;
    for (int j = 0; j < 5; j++) {
      suma += ads.readADC_SingleEnded(i);
      delay(100);
    }
    base[i] = suma / 5;
  }

  calibrado = true;
  Serial.println("Calibrado! Valores base:");
  for (int i = 0; i < 4; i++) {
    Serial.print("  Canal ");
    Serial.print(i);
    Serial.print(": ");
    Serial.println(base[i]);
  }
  Serial.println("=============================");
  Serial.println("Acerca la mano o toca la planta");
  Serial.println("=============================");
}

void loop() {
  String nombres[4] = {"hoja grande ", "hoja pequeña", "tallo       ", "sustrato    "};

  Serial.println();

  for (int i = 0; i < 4; i++) {
    int valor = ads.readADC_SingleEnded(i);
    int cambio = valor - base[i];
    int porcentaje = abs(cambio) * 100 / max(base[i], 1);

    String barra = "";
    int bloques = min(porcentaje / 5, 20);
    for (int b = 0; b < bloques; b++) barra += "█";

    String estado = "";
    if (porcentaje < 2)       estado = "  calma";
    else if (porcentaje < 8)  estado = "  movimiento leve";
    else if (porcentaje < 15) estado = "  ¡actividad!";
    else                      estado = "  ¡¡MUCHO MOVIMIENTO!!";

    Serial.print(nombres[i]);
    Serial.print(" | ");
    if (cambio >= 0) Serial.print("+");
    Serial.print(cambio);
    Serial.print("\t");
    Serial.print(barra);
    Serial.print(estado);
    Serial.println();
  }

  Serial.println("-----------------------------");
  delay(800);
}
```

Esta versión se probó tanto sin acercar la mano a la planta como acercando la mano o tocando la tierra, lo que permitió observar en vivo el cambio de estado de "calma" a "¡actividad!" directamente en el Monitor Serial.

Luego de todo esto se le planteó a Claude el siguiente paso: aún faltaba que los datos detectados por la planta llegaran de forma inalámbrica a un lugar donde se pudieran generar dibujos o imágenes según los datos percibidos — si el entorno de la planta estaba tranquilo o había movimiento. Ya teníamos la base de que el sistema de lectura funcionaba; ahora había que subirlo de nivel.

### Primera versión del Arduino con servidor WiFi propio

Claude entregó el siguiente código, que crea una red WiFi propia desde el Arduino y sirve los datos como JSON mediante un servidor HTTP simple:

```cpp
#include <Wire.h>
#include <Adafruit_ADS1X15.h>
#include <WiFiS3.h>

const char* NOMBRE_RED = "planta-sensor";
const char* CLAVE_RED  = "plantaviva";

Adafruit_ADS1115 ads;
WiFiServer servidor(80);

int lecturas[4]  = {0, 0, 0, 0};
int base[4]      = {0, 0, 0, 0};
int cambio[4]    = {0, 0, 0, 0};

String nombres[4] = {"hoja_grande", "hoja_pequena", "tallo", "sustrato"};

void setup() {
  Serial.begin(9600);
  Serial.println("=== La Voz de las Plantas - Grupo 07 ===");

  if (!ads.begin()) {
    Serial.println("ERROR: ADS1115 no encontrado.");
    while (1);
  }
  ads.setGain(GAIN_SIXTEEN);
  Serial.println("ADS1115 listo.");

  Serial.println("Calibrando... no toques la planta");
  delay(2000);
  for (int i = 0; i < 4; i++) {
    long suma = 0;
    for (int j = 0; j < 10; j++) {
      suma += ads.readADC_SingleEnded(i);
      delay(100);
    }
    base[i] = suma / 10;
    Serial.print("Base canal ");
    Serial.print(i);
    Serial.print(": ");
    Serial.println(base[i]);
  }
  Serial.println("Calibrado!");

  Serial.print("Creando red: ");
  Serial.println(NOMBRE_RED);
  WiFi.beginAP(NOMBRE_RED, CLAVE_RED);
  while (WiFi.status() != WL_AP_LISTENING) {
    delay(500);
    Serial.print(".");
  }
  servidor.begin();
  Serial.println("\nRed lista!");
  Serial.println("Conectarse a 'planta-sensor' y abrir:");
  Serial.println("http://192.168.4.1/datos");
}

void loop() {
  for (int i = 0; i < 4; i++) {
    lecturas[i] = ads.readADC_SingleEnded(i);
    cambio[i]   = lecturas[i] - base[i];
  }

  for (int i = 0; i < 4; i++) {
    Serial.print(nombres[i]);
    Serial.print(": ");
    Serial.print(lecturas[i]);
    Serial.print(" (");
    if (cambio[i] >= 0) Serial.print("+");
    Serial.print(cambio[i]);
    Serial.println(")");
  }
  Serial.println("---");

  WiFiClient cliente = servidor.available();
  if (cliente) {
    String peticion = "";
    while (cliente.connected()) {
      if (cliente.available()) {
        char c = cliente.read();
        peticion += c;
        if (peticion.endsWith("\r\n\r\n")) break;
      }
    }

    if (peticion.indexOf("GET /datos") >= 0) {
      String json = "{";
      for (int i = 0; i < 4; i++) {
        json += "\"" + nombres[i] + "\":" + String(lecturas[i]);
        json += ",\"" + nombres[i] + "_cambio\":" + String(cambio[i]);
        if (i < 3) json += ",";
      }
      json += "}";

      cliente.println("HTTP/1.1 200 OK");
      cliente.println("Content-Type: application/json");
      cliente.println("Access-Control-Allow-Origin: *");
      cliente.println("Connection: close");
      cliente.println();
      cliente.println(json);

    } else if (peticion.indexOf("GET / ") >= 0) {
      cliente.println("HTTP/1.1 200 OK");
      cliente.println("Content-Type: text/html");
      cliente.println("Connection: close");
      cliente.println();
      cliente.println("<html><body style='background:#000;color:#0f0;font-family:monospace;padding:2rem'>");
      cliente.println("<h2>La Voz de las Plantas</h2>");
      cliente.println("<p>Abre <a href='/datos' style='color:#0f0'>/datos</a> para ver los valores</p>");
      cliente.println("</body></html>");
    }

    delay(10);
    cliente.stop();
  }

  delay(50);
}
```

Se logró conectar, pero surgieron varios problemas: el código mandaba datos muy rápido (la luz del Arduino parpadeaba casi sin pausa), y existía la duda de cómo manejar la conexión si el PC que visualiza los datos está a varios metros de distancia del Arduino, cada uno en redes distintas. También se necesitaba que la visualización mostrara formas y colores tipo animación en vez de solo texto plano.

**Se le preguntó a Claude sobre el error**, planteando estas dudas: la velocidad de envío de datos, si el PC con el Arduino necesitaba quedarse sin internet al estar conectado a la red de la planta, y cómo separar la red del Arduino de la red desde donde se visualizan los datos. Además se pidió una página con formas y colores animados según los datos recibidos, ya que el HTML inicial no servía para eso.

Claude entonces entregó un HTML nuevo con visualización gráfica.

### ¿Qué hizo Claude en la visualización?

Se le preguntó a Claude cómo había generado esa visualización, a lo que respondió que usó p5.js, una librería/API de JavaScript para arte generativo, que se carga así en el código:

```html
<script src="https://cdnjs.cloudflare.com/ajax/libs/p5.js/1.9.0/p5.min.js"></script>
```

Esa línea descarga la API de p5.js desde internet y la usa para dibujar todo lo que se ve en pantalla; sin esa línea no habría nada visual.

### Cuidado físico de la planta

Durante el proceso de conectar todo el sistema directamente a la planta, se detectó que las hojas y el tallo se rompían con facilidad al manipular las pinzas, por lo que fue necesario colocarlas con mucho cuidado para no dañar el organismo que se estaba midiendo.

### Pruebas con otra gráfica y sonido en el HTML

Aquí nos dimos cuenta de que, al querer conectar el Arduino (con el ADS1115 y la planta) a una página que visualizara los cambios, esto no se lograba a larga distancia porque no estábamos usando una nube intermedia: la información que recibía el Arduino a larga distancia no se almacenaba en ningún servicio al que el HTML pudiera conectarse, por lo que ni siquiera el HTML lograba conectarse. Fue ahí donde se empezó a usar dweet.io, pero el servicio estaba fallando.

En la imagen de prueba se veía que el Arduino se conectaba al WiFi, pero la IP marcaba 0.0.0.0, lo que significa que el router no le había asignado dirección todavía. Tampoco aparecía el mensaje "Enviado a dweet.io OK", lo que confirmaba que dweet.io no estaba respondiendo bien.

Le preguntamos a Claude cómo solucionar esto, y luego tratamos de resolverlo usando Visual Studio Code, ya que el HTML seguía sin conectarse. Claude guió la instalación y uso de la extensión Live Server (de Ritwik Dey) para servir el archivo HTML localmente. Aun así, el problema de fondo persistía, por lo que se decidió migrar de dweet.io a HiveMQ Cloud.

### Contexto del cambio: de dweet.io a HiveMQ Cloud

El servicio que estábamos usando originalmente, dweet.io, dejó de funcionar (el sitio estaba caído). Esto generó un primer dilema: necesitábamos que dos personas en casas distintas pudieran ver los datos del sensor de la planta en tiempo real, así que había que decidir entre:

- Volver a la red propia del Arduino (solución rápida, pero solo funciona si están en el mismo lugar).
- Migrar a un servicio en la nube (más trabajo, pero permite la comunicación real a distancia).

Se optó por la segunda opción, ya que el requisito real era que cada integrante pudiera grabar desde su propia casa.

#### Paso 1 — Elección del servicio en la nube

Se evaluó HiveMQ Cloud como alternativa a dweet.io, usando el protocolo MQTT, por ser gratuito, estable y no requerir gestión de servidores propios. Se eligió el plan "Serverless" (sin servidores), gratuito y sin necesidad de configuración de infraestructura.

#### Paso 2 — Creación de la cuenta y el clúster en HiveMQ

Pasos seguidos dentro de la consola de HiveMQ:

1. Registro en console.hivemq.cloud.
2. Creación de un clúster gratuito tipo "Sin Servidores".
3. Obtención de los datos de conexión:
   - Host: 9ef881d840d84aea8f8f7eacc45fa211.s1.eu.hivemq.cloud
   - Puerto MQTT (TLS): 8883
   - Puerto WebSocket (TLS): 8884

#### Paso 3 — Creación de credenciales de acceso

En la sección "Gestión de acceso" → "Credenciales" se creó un usuario con permiso de Publicar y Suscribir (PUBLISH/SUBSCRIBE), necesario para que el Arduino pudiera enviar datos y el navegador pudiera leerlos.

- Usuario: Planta
- Contraseña: Planta2024!

#### Paso 4 — Primera versión del código en el Arduino UNO R4 WiFi + ADS1115

Se programó el Arduino para que leyera el ADS1115 por I2C, se conectara a la red WiFi de la casa, y publicara los datos por MQTT (con conexión segura TLS) al topic planta/humedad.

Lo que no funcionó al principio: al subir el código por primera vez, el Arduino IDE mostró "Not connected" en el monitor serial, lo que en un principio se interpretó como un error del código. En realidad, solo faltaba conectar el USB y seleccionar el puerto correcto en Herramientas → Puerto, además de instalar las librerías necesarias (ArduinoMqttClient y Adafruit ADS1X15).

### Primer código de prueba completo de esta etapa

Antes de migrar por completo a MQTT, esta fue la primera versión funcional que combinó la lectura del ADS1115 con un servidor propio en el Arduino, sirviendo los datos como JSON sin depender todavía de ningún servicio externo:

```cpp
#include <Wire.h>
#include <Adafruit_ADS1X15.h>
#include <WiFiS3.h>

const char* NOMBRE_RED = "planta-sensor";
const char* CLAVE_RED  = "plantaviva";

Adafruit_ADS1115 ads;
WiFiServer servidor(80);

int lecturas[4] = {0, 0, 0, 0};
int base[4]     = {0, 0, 0, 0};
int cambio[4]   = {0, 0, 0, 0};

String nombres[4] = {"hoja_grande", "hoja_pequena", "tallo", "sustrato"};

unsigned long ultimaLectura = 0;
const int INTERVALO = 500;

void setup() {
  Serial.begin(9600);
  Serial.println("=== La Voz de las Plantas - Grupo 07 ===");

  if (!ads.begin()) {
    Serial.println("ERROR: ADS1115 no encontrado.");
    while (1);
  }
  ads.setGain(GAIN_SIXTEEN);

  Serial.println("Calibrando... no toques la planta");
  delay(2000);
  for (int i = 0; i < 4; i++) {
    long suma = 0;
    for (int j = 0; j < 10; j++) {
      suma += ads.readADC_SingleEnded(i);
      delay(100);
    }
    base[i] = suma / 10;
  }
  Serial.println("Calibrado!");

  WiFi.beginAP(NOMBRE_RED, CLAVE_RED);
  while (WiFi.status() != WL_AP_LISTENING) {
    delay(500);
    Serial.print(".");
  }
  servidor.begin();
  Serial.println("\nRed lista!");
  Serial.println("http://192.168.4.1/datos");
}

void loop() {
  unsigned long ahora = millis();
  if (ahora - ultimaLectura >= INTERVALO) {
    ultimaLectura = ahora;
    for (int i = 0; i < 4; i++) {
      lecturas[i] = ads.readADC_SingleEnded(i);
      cambio[i]   = lecturas[i] - base[i];
    }
    for (int i = 0; i < 4; i++) {
      Serial.print(nombres[i]);
      Serial.print(": ");
      Serial.print(lecturas[i]);
      Serial.print(" (");
      if (cambio[i] >= 0) Serial.print("+");
      Serial.print(cambio[i]);
      Serial.println(")");
    }
    Serial.println("---");
  }

  WiFiClient cliente = servidor.available();
  if (cliente) {
    String peticion = "";
    unsigned long inicio = millis();
    while (cliente.connected() && millis() - inicio < 1000) {
      if (cliente.available()) {
        char c = cliente.read();
        peticion += c;
        if (peticion.endsWith("\r\n\r\n")) break;
      }
    }

    if (peticion.indexOf("GET /datos") >= 0) {
      String json = "{";
      for (int i = 0; i < 4; i++) {
        json += "\"" + nombres[i] + "\":" + String(lecturas[i]);
        json += ",\"" + nombres[i] + "_cambio\":" + String(cambio[i]);
        if (i < 3) json += ",";
      }
      json += "}";

      cliente.println("HTTP/1.1 200 OK");
      cliente.println("Content-Type: application/json");
      cliente.println("Access-Control-Allow-Origin: *");
      cliente.println("Connection: close");
      cliente.println();
      cliente.print(json);
    }
    cliente.stop();
  }
}
```

Esta versión ya incorporaba un control de intervalo con millis() (en vez de delay()) para no bloquear el servidor mientras se hacían las lecturas, y fue la base directa sobre la que luego se construyó la versión con MQTT descrita en los pasos siguientes.

#### Paso 5 — Comprobación de que los datos llegaban a HiveMQ

Se usó el Cliente Web de HiveMQ (incluido gratis en la consola) para verificar que el Arduino realmente estaba publicando datos, sin necesidad de tener el HTML abierto al mismo tiempo.

Esto funcionó muy bien: al suscribirse al topic planta/humedad desde el Cliente Web se vieron los mensajes JSON llegando en vivo, lo que confirmó que la conexión Arduino → HiveMQ estaba funcionando antes de seguir con la visualización.

#### Paso 6 — Primera visualización web: porcentaje de humedad de suelo

La primera versión del HTML calculaba un % de humedad del suelo (0–100%) a partir de un solo sensor capacitivo, mostrando una tarjeta simple con barra de progreso y un emoji de planta.

Lo que no funcionó: este enfoque asumía que el ADS1115 estaba conectado a un sensor de humedad de suelo tradicional. La lógica de calibración (valor seco / valor mojado) no aplicaba al hardware real, porque en realidad lo conectado eran 4 electrodos (pinzas) en distintas partes de la planta (hoja grande, hoja chica, tallo y tierra), no un sensor de humedad capacitivo. Esto se descubrió cuando la humedad siempre marcaba 100%, sin importar la condición real de la planta.

#### Paso 7 — Cambio de enfoque visual: "La Voz de las Plantas"

Se reemplazó la tarjeta simple por una visualización orgánica tipo "campo de energía": ondas circulares deformables, partículas y un núcleo central pulsante, siguiendo una referencia visual que el grupo ya tenía pensada para el proyecto.

Problema detectado: la primera versión de esta visualización no mostraba diferencias notorias entre valores bajos y altos del sensor; el cambio era casi imperceptible a simple vista.

Cómo se solucionó: se recalculó la amplitud de la distorsión de las ondas usando una relación cuadrática en vez de lineal, lo que exagera la diferencia visual entre un valor bajo y uno alto. También se agregó un panel de estado de conexión a HiveMQ visible en pantalla (estado, hora del último dato, contador de mensajes), para comprobar a simple vista que todo seguía conectado durante la grabación.

#### Paso 8 — Corrección final: del "sensor de humedad" a los "4 electrodos de la planta"

Al revisar el Serial Monitor del Arduino se notó que la humedad calculada siempre salía 100%, porque el código estaba mal interpretando los datos: intentaba calcular un porcentaje de humedad de suelo a partir de pinzas que en realidad medían conductividad eléctrica en 4 puntos distintos de la planta (hoja grande, hoja chica, tallo y tierra), no humedad de un sustrato.

Lo aprendido de este error: es importante verificar primero qué tipo de sensor/dato se está leyendo realmente antes de aplicar fórmulas de conversión, porque una fórmula que tiene sentido para un sensor capacitivo de humedad no tiene ningún sentido para electrodos de conductividad.

Solución final aplicada:
- Se reescribió el código del Arduino para que enviara los 4 valores crudos de cada electrodo por separado, sin intentar convertirlos a un porcentaje de humedad.
- Se cambió el cálculo de "estado" para que se basara en el promedio de actividad eléctrica de los 4 electrodos (DORMIDA / TRANQUILA / ACTIVA / INTENSA), en vez de un falso porcentaje de humedad.
- Se actualizó la visualización HTML para que cada uno de los 4 electrodos tuviera su propia onda, su propio color y su propia barra de actividad en pantalla, y para que el sonido generado tuviera un oscilador independiente por cada electrodo.

### Resumen de aprendizajes para la bitácora

| Problema | Causa real | Solución |
|---|---|---|
| dweet.io no funcionaba | El servicio estaba caído | Migrar a HiveMQ Cloud (MQTT) |
| "Not connected" en Arduino IDE | Faltaba conectar USB / seleccionar puerto | No era un error de código |
| Humedad siempre en 100% | El sensor no era de humedad de suelo, sino 4 electrodos de conductividad | Cambiar la lógica de cálculo y enviar los 4 valores crudos por separado |
| Visualización sin cambios visibles | La distorsión de las ondas era proporcional de forma lineal al valor del sensor | Usar una relación cuadrática para exagerar el contraste visual |

### Configuración de credenciales de HiveMQ en el código del Arduino

Una vez adoptado HiveMQ, fue necesario configurar el código de Arduino correctamente, lo que implicó resolver distintos errores que fueron apareciendo durante la integración. Se descubrió que era necesario agregar las credenciales específicas de HiveMQ (host, usuario y contraseña del clúster) directamente en el código del Arduino para que la conexión MQTT con TLS se autenticara correctamente.

### Código definitivo (Arduino → HiveMQ vía MQTT)

```cpp
/*
 * LA VOZ DE LAS PLANTAS — Arduino UNO R4 WiFi + ADS1115
 * Publica los 4 canales del ADS1115 a HiveMQ Cloud via MQTT
 *
 * Librerías necesarias (Herramientas → Gestionar librerías):
 *   - ArduinoMqttClient  (de Arduino)
 *   - Adafruit ADS1X15   (de Adafruit)
 *   WiFiS3 ya viene incluida con Arduino UNO R4
 */

#include <WiFiS3.h>
#include <ArduinoMqttClient.h>
#include <Wire.h>
#include <Adafruit_ADS1X15.h>

// ─── CONFIGURACIÓN WiFi ───────────────────────────────────────────
const char* WIFI_SSID     = "xxxxxx";       // <-- tu red
const char* WIFI_PASSWORD = "xxxxxxxxxx";   // <-- tu contraseña

// ─── CONFIGURACIÓN HiveMQ Cloud ──────────────────────────────────
const char* MQTT_HOST     = "9ef881d840d84aea8f8f7eacc45fa211.s1.eu.hivemq.cloud";
const int   MQTT_PORT     = 8883;
const char* MQTT_USER     = "Planta";
const char* MQTT_PASSWORD = "Planta2024!";
const char* MQTT_TOPIC    = "planta/humedad";
const char* CLIENT_ID     = "arduino-planta-001";

// ─── CALIBRACIÓN DEL SENSOR DE HUMEDAD (canal A0) ────────────────
// Mide tu sensor en aire seco y en agua, ajusta estos valores:
const int VALOR_SECO   = 17000;   // lectura con suelo SECO
const int VALOR_MOJADO =  8000;   // lectura con suelo MOJADO

// ─── INTERVALO DE ENVÍO ──────────────────────────────────────────
const long INTERVALO_MS = 3000;   // enviar cada 3 segundos

// ─── OBJETOS ─────────────────────────────────────────────────────
Adafruit_ADS1115 ads;
WiFiSSLClient    wifiClient;
MqttClient       mqttClient(wifiClient);

unsigned long ultimoEnvio = 0;

// ─────────────────────────────────────────────────────────────────
void setup() {
  Serial.begin(9600);
  while (!Serial) delay(10);

  Serial.println("================================");
  Serial.println("  LA VOZ DE LAS PLANTAS");
  Serial.println("================================");

  // Iniciar ADS1115
  if (!ads.begin()) {
    Serial.println("[ERROR] ADS1115 no encontrado. Verifica SDA/SCL.");
    while (1) delay(1000);
  }
  ads.setGain(GAIN_ONE);
  Serial.println("[OK] ADS1115 listo");

  // Conectar WiFi
  conectarWiFi();

  // Configurar y conectar MQTT
  mqttClient.setId(CLIENT_ID);
  mqttClient.setUsernamePassword(MQTT_USER, MQTT_PASSWORD);
  conectarMQTT();
}

// ─────────────────────────────────────────────────────────────────
void loop() {
  mqttClient.poll();

  // Reconectar MQTT si se cae
  if (!mqttClient.connected()) {
    Serial.println("[MQTT] Desconectado, reconectando...");
    delay(1000);
    conectarMQTT();
  }

  // Enviar datos según intervalo
  unsigned long ahora = millis();
  if (ahora - ultimoEnvio >= INTERVALO_MS) {
    ultimoEnvio = ahora;
    leerYEnviar();
  }
}

// ─────────────────────────────────────────────────────────────────
void leerYEnviar() {

  // Leer los 4 canales del ADS1115
  int16_t a0 = ads.readADC_SingleEnded(0);  // sensor principal humedad suelo
  int16_t a1 = ads.readADC_SingleEnded(1);  // canal extra 1
  int16_t a2 = ads.readADC_SingleEnded(2);  // canal extra 2
  int16_t a3 = ads.readADC_SingleEnded(3);  // canal extra 3

  // Calcular humedad como porcentaje (basado en A0)
  int humedad = map(a0, VALOR_SECO, VALOR_MOJADO, 0, 100);
  humedad = constrain(humedad, 0, 100);

  // Determinar estado
  String estado;
  if      (humedad < 30) estado = "SECO";
  else if (humedad < 60) estado = "OPTIMO";
  else                   estado = "HUMEDO";

  // Construir JSON con todos los datos
  String json = "{";
  json += "\"humedad\":"    + String(humedad)  + ",";
  json += "\"valorCrudo\":" + String(a0)       + ",";
  json += "\"a1\":"         + String(a1)       + ",";
  json += "\"a2\":"         + String(a2)       + ",";
  json += "\"a3\":"         + String(a3)       + ",";
  json += "\"estado\":\""   + estado           + "\"";
  json += "}";

  // Publicar en HiveMQ
  mqttClient.beginMessage(MQTT_TOPIC);
  mqttClient.print(json);
  mqttClient.endMessage();

  // Log en Serial Monitor
  Serial.println("─────────────────────────");
  Serial.println("[MQTT] Enviado:");
  Serial.println("  humedad  : " + String(humedad) + "%");
  Serial.println("  A0 (raw) : " + String(a0));
  Serial.println("  A1       : " + String(a1));
  Serial.println("  A2       : " + String(a2));
  Serial.println("  A3       : " + String(a3));
  Serial.println("  estado   : " + estado);
}

// ─────────────────────────────────────────────────────────────────
void conectarWiFi() {
  Serial.print("[WiFi] Conectando a: ");
  Serial.println(WIFI_SSID);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  int intentos = 0;
  while (WiFi.status() != WL_CONNECTED && intentos < 30) {
    delay(500);
    Serial.print(".");
    intentos++;
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println();
    Serial.println("[WiFi] Conectado!");
    Serial.print("[WiFi] IP: ");
    Serial.println(WiFi.localIP());
  } else {
    Serial.println();
    Serial.println("[WiFi] ERROR: No se pudo conectar.");
    Serial.println("[WiFi] Verifica SSID y contraseña.");
  }
}

// ─────────────────────────────────────────────────────────────────
void conectarMQTT() {
  Serial.print("[MQTT] Conectando a HiveMQ...");

  int intentos = 0;
  while (!mqttClient.connect(MQTT_HOST, MQTT_PORT) && intentos < 5) {
    Serial.print(".");
    delay(2000);
    intentos++;
  }

  if (mqttClient.connected()) {
    Serial.println(" OK!");
  } else {
    Serial.println(" FALLO");
    Serial.print("[MQTT] Error codigo: ");
    Serial.println(mqttClient.connectError());
  }
}
```

Las credenciales generadas en HiveMQ (host, usuario, contraseña) tuvieron que copiarse directamente en este código del Arduino para que la autenticación funcionara. En el Cliente Web de HiveMQ se confirmó que la información sí estaba llegando correctamente.

### Evolución del código: de "humedad" a "electrodos de conductividad"

Esta sección detalla, con el código exacto, las tres versiones por las que pasó la lógica del Arduino hasta llegar a la solución final.

#### Versión 1 — Primer intento (sensor de humedad de suelo)

La primera idea fue tratar el ADS1115 como si estuviera conectado a un sensor capacitivo de humedad de suelo tradicional:

```cpp
const int VALOR_SECO   = 17000;   // Valor cuando el suelo está SECO
const int VALOR_MOJADO = 8000;    // Valor cuando el suelo está MOJADO

int16_t valorCrudo = ads.readADC_SingleEnded(0);
int humedad = map(valorCrudo, VALOR_SECO, VALOR_MOJADO, 0, 100);
humedad = constrain(humedad, 0, 100);
```

La idea de map() era simple: tomar el valor crudo del ADC (que puede ir de -32768 a 32767) y convertirlo a una escala de 0% a 100%, usando dos puntos de referencia: cómo se ve el valor cuando está seco y cómo se ve cuando está mojado.

Por qué esto no funcionó: este cálculo solo tiene sentido si el sensor conectado es un sensor de humedad capacitivo de una sola entrada. La conexión real era distinta: había 4 pinzas/electrodos conectados a los 4 canales del ADS1115 (A0, A1, A2, A3), cada uno tocando una parte diferente de la planta — hoja grande, hoja chica, tallo y tierra. Estos electrodos no miden "humedad", miden diferencias de conductividad eléctrica entre puntos de la planta.

Cómo se detectó: al revisar el Serial Monitor, se vio que sin importar qué tan húmeda o seca estuviera la tierra, el cálculo de humedad siempre marcaba 100%:
[MQTT] Enviado:

humedad  : 100%

A0 (raw) : 4593

A1       : 4325

A2       : 5115

A3       : 3268

estado   : HÚMEDO
Todos los valores crudos estaban muy por debajo de VALOR_MOJADO = 8000, lo que map() interpretaba como "más húmedo que el punto más húmedo posible", forzando el resultado a 100% siempre.

#### Versión 2 — Envío de los 4 canales sin calibrar (intermedia)

Antes de corregir la lógica completa, se hizo una versión donde simplemente se agregó la lectura de los otros 3 canales (A1, A2, A3) al JSON, manteniendo el cálculo erróneo de humedad basado solo en A0:

```cpp
int16_t a0 = ads.readADC_SingleEnded(0);
int16_t a1 = ads.readADC_SingleEnded(1);
int16_t a2 = ads.readADC_SingleEnded(2);
int16_t a3 = ads.readADC_SingleEnded(3);

int humedad = map(a0, VALOR_SECO, VALOR_MOJADO, 0, 100);
humedad = constrain(humedad, 0, 100);
```

Esto sirvió para confirmar en el Cliente Web de HiveMQ que los 4 canales sí estaban llegando correctamente a la nube, aunque el campo "humedad" seguía siendo incorrecto conceptualmente. Fue un paso útil de diagnóstico, aunque el dato final todavía no tenía sentido.

#### Versión 3 — Corrección final (electrodos de conductividad)

Una vez confirmado que el hardware real eran 4 electrodos de contacto, se reescribió la lógica completa del Arduino.

Cambio 1 — Eliminación del cálculo de "humedad por mapeo". Ya no tenía sentido convertir un valor a porcentaje usando seco/mojado, porque no se estaba midiendo humedad de un sustrato sino actividad eléctrica entre puntos de la planta.

Cambio 2 — Nombrado de los canales según su ubicación física real:

```cpp
int16_t hojaGrande = ads.readADC_SingleEnded(0);
int16_t hojaChica  = ads.readADC_SingleEnded(1);
int16_t tallo      = ads.readADC_SingleEnded(2);
int16_t tierra     = ads.readADC_SingleEnded(3);
```

Esto hizo el código mucho más legible y fácil de relacionar con el hardware real, en vez de tener variables genéricas a0, a1, a2, a3 sin contexto.

Cambio 3 — Reemplazo del "% de humedad" por un "nivel de actividad eléctrica":

```cpp
long promedio = ((long)abs(hojaGrande) + abs(hojaChica) + abs(tallo) + abs(tierra)) / 4;

String estado;
if      (promedio < 2000)  estado = "DORMIDA";
else if (promedio < 6000)  estado = "TRANQUILA";
else if (promedio < 12000) estado = "ACTIVA";
else                        estado = "INTENSA";
```

En vez de forzar una métrica de humedad que no correspondía a la realidad, se calculó el promedio de actividad de los 4 electrodos y se clasificó ese promedio en 4 estados cualitativos. Se usó abs() porque los valores del ADS1115 pueden venir negativos (depende de la polaridad de la pinza), y lo que interesa es la magnitud de la señal, no su signo.

Cambio 4 — Estructura del JSON enviado. Pasó de esto:

```json
{"humedad":100,"valorCrudo":5317,"a1":5315,"a2":3037,"a3":4882,"estado":"HÚMEDO"}
```

a esto:

```json
{"hojaGrande":5317,"hojaChica":5315,"tallo":3037,"tierra":4882,"promedio":4888,"estado":"TRANQUILA"}
```

La diferencia clave es que ahora cada campo representa exactamente lo que mide (un electrodo específico), y el "estado" ya no es un falso porcentaje de humedad sino una clasificación basada en la actividad eléctrica real medida.

Cambio 5 — Cambio del nombre del topic MQTT. De planta/humedad se pasó a planta/voz, porque el nombre anterior ya no representaba lo que se estaba transmitiendo: no era información de humedad, sino la señal eléctrica de la planta.

Por qué importa este cambio para la bitácora: este fue el aprendizaje técnico más importante del proyecto: el tipo de sensor determina la fórmula, no al revés. Se había escrito una fórmula de conversión razonable (map() con calibración seco/mojado) que funcionaba perfectamente bien en código, pero estaba mal porque no correspondía al fenómeno físico real que se estaba midiendo. El código no tenía ningún error de sintaxis ni de lógica de programación — el error fue conceptual, en cómo se interpretaba la naturaleza de los datos del hardware.

También se aprendió a usar el Serial Monitor y el Cliente Web de HiveMQ como herramientas de diagnóstico paralelas: revisar los valores crudos en ambos lugares fue lo que permitió notar que el resultado final no coincidía con lo esperado, antes de pasar a corregir la causa raíz en el código.

## 2. Investigación técnica y referentes

El grupo investigó cómo otros artistas han trabajado con bio-electricidad de plantas. Los referentes más relevantes encontrados fueron:

- **Mileece** — artista que desde 2005 transforma bio-emisiones de plantas en música. Ha presentado en MoMA Nueva York y Tate Modern Londres. Su sistema usa electrodos en hojas para amplificar micro-voltajes. La diferencia con nuestro proyecto: Mileece trabaja solo con sonido y sin transmisión inalámbrica. (https://www.mileece.is/bio)

- **PlantWave / Data Garden** — plataforma de bio-sonificación fundada por Joe Patitucci y Alex Tyson, basada en el trabajo del artista Richard Lowenberg. (https://plantwave.com/blogs/blog/plant-biosonification-plantwave-history)

- **Monica Gagliano** — investigadora que demostró que las plantas emiten señales eléctricas y acústicas reales, con una red de señalización basada en calcio similar a los procesos de memoria animal. (https://www.monicagagliano.com/)

**Uso de IA en esta etapa:** Se preguntó a Claude sobre artistas y proyectos similares en el mundo. Claude buscó y entregó los referentes anteriores con contexto sobre qué los diferencia de nuestra propuesta.

**Prompt utilizado:**

"¿Alguien en el mundo ya hizo algo similar, planta como sensor biológico con visualización? ¿Qué artistas o proyectos existen?"

## 3. Arquitectura del sistema

Luego de investigar, el grupo definió la arquitectura técnica del proyecto:
Planta (4 electrodos)

↓

ADS1115 (conversor analógico-digital 16 bits)

↓

Arduino UNO R4 WiFi (emisor)

↓ WiFi / MQTT

Receptor (PC o navegador)

↓

Visualización generativa en tiempo real (p5.js)

+ Sonido generativo (Web Audio API)

Se decidió usar 4 electrodos en distintas partes de la planta (hoja grande, hoja pequeña, tallo, sustrato) en lugar de uno solo, para cumplir con el requisito de múltiplos y arrays del examen. Esta decisión surgió de entender que el ADS1115 tiene 4 canales de entrada independientes (A0, A1, A2, A3).

**Uso de IA en esta etapa:** Se consultó a Claude sobre si era necesario un segundo ADS1115 para usar 4 electrodos. Claude explicó que no, el módulo tiene 4 canales y puede leerlos todos con un solo módulo. También explicó el concepto de arrays y for de forma práctica.

**Prompts utilizados:**

"Si ponemos 4 pinzas en la planta, ¿necesitamos más de un ADS1115?"

"No entiendo bien lo de múltiples, arrays y for, explícame como si no cachaba nada"

Claude explicó que un array es una lista con nombre (lecturas[4]) y un for recorre esa lista automáticamente, haciendo que el código funcione igual para 4 electrodos que para 40.

### Materiales utilizados

| Material | Cantidad | Precio unitario | Subtotal |
|---|---|---|---|
| Arduino UNO R4 WiFi | 1 | $35.000 | $35.000 |
| Módulo ADS1115 (conversor ADC 16 bits) | 1 | $6.000 | $6.000 |
| Pinzas de cocodrilo (electrodos) | 4 | $500 | $2.000 |
| Cable jumper macho-macho (pack) | 1 | $2.500 | $2.500 |
| Cable flexible 24 AWG (metro) | 1 | $1.500 | $1.500 |
| Protoboard | 1 | $3.000 | $3.000 |
| Planta de menta | 1 | $4.000 | $4.000 |
| Cable USB-C | 1 | $3.500 | $3.500 |
| **Total estimado** | | | **$57.500** |

## 4. Prueba del hardware

Antes de conectar la planta, el grupo realizó pruebas para verificar que el ADS1115 funcionaba correctamente.

**Pasos realizados:**

1. Instalación de la librería Adafruit ADS1X15 v2.6.2 en Arduino IDE.
2. Conexión del ADS1115 al Arduino (VDD → 3.3V, GND → GND, SCL → SCL, SDA → SDA).
3. Carga de código de prueba que leía los 4 canales cada 1 segundo.
4. Verificación en Monitor Serial de que los valores aparecían.

**Resultado:** Los 4 canales mostraron valores consistentes (~3150 raw, ~0.59V) sin nada conectado, ruido eléctrico normal.

**Prueba de sensibilidad:** Al tocar el pin A0 del ADS1115 con el dedo, el Canal 0 subió de ~3150 a 4329 raw, confirmando que el módulo detecta señales externas.

**Uso de IA en esta etapa:** Claude guió paso a paso la instalación de la librería y el proceso de prueba. Cuando salió el error Missing FQBN, Claude explicó que era un error del IDE por no tener seleccionada la placa, no del código.

## 5. Prueba con la planta real

Se conectaron 4 pinzas de cocodrilo a la planta de menta disponible:

- Pinza A0 → hoja grande
- Pinza A1 → hoja pequeña
- Pinza A2 → tallo
- Pinza A3 → sustrato (tierra)

### Resultados de la prueba

| Estado | Canal 0 (hoja grande) | Cambio |
|---|---|---|
| Sin actividad | ~3050 raw | base |
| Mano a 10cm | 4059 raw | +1009 |

Los cambios llegaron hasta ±19000 al acercar la mano o tocar la planta, confirmando que la planta funciona como antena biológica.

Se mejoró el código de prueba para mostrar los cambios de forma visual con barras y estados (calma / movimiento leve / actividad / mucho movimiento).

**Uso de IA en esta etapa:** Se consultó a Claude si la planta podía detectar el ambiente sin que nadie la tocara. Claude explicó que sí: el campo eléctrico del cuerpo humano activa la señal cuando alguien se acerca a 20–50cm, especialmente con la ganancia máxima GAIN_SIXTEEN del ADS1115.

## 6. Desarrollo de la visualización

Se eligió p5.js como librería de visualización, una API de arte generativo que corre directo en el navegador.

La visualización final consiste en un solo núcleo orgánico con 4 capas de color independientes, cada una controlada por un canal distinto:

| Canal | Color | Atributo visual |
|---|---|---|
| hoja grande | Verde esmeralda | Tamaño total de la forma |
| hoja pequeña | Cian azulado | Segunda capa interior |
| tallo | Dorado verdoso | Segunda capa exterior |
| sustrato | Violeta tenue | Capa más exterior y halo |

La paleta fue diseñada para que siempre permanezca en tonos verde/naturaleza, nunca llega a blanco. El rango va de verde casi negro (calma) a verde esmeralda brillante (actividad máxima).

**Uso de IA en esta etapa:** Claude escribió el código de la visualización en p5.js basándose en las decisiones del grupo. Se reiteró varias veces: la primera versión tenía el MAX calibrado en 600, lo que hacía que la visualización casi no reaccionara. Al mostrar los valores reales de la planta (±19000), Claude recalibró el MAX a 20000 y la visualización empezó a responder correctamente.

**Prompts utilizados:**

"La visualización no reacciona bien cuando paso la mano, apenas cambia"

"Quiero que sea un solo núcleo con distintos colores como la foto que te subí, y el sonido sigue sin funcionar"

## 7. Desarrollo del sonido generativo

Se sumó la Web Audio API — segunda API del proyecto — para que la planta también genere sonido.

**Comportamiento del sonido:**

- Sin actividad → silencio total (umbral mínimo de 0.08)
- Actividad leve → drone grave (Do2, 65Hz), timbre sine puro
- Actividad media → frecuencia sube, timbre cambia a triangle
- Actividad alta → frecuencia aguda, timbre sawtooth

El audio se activa únicamente con el clic en la pantalla de inicio, requisito del navegador para permitir reproducción de audio.

**Uso de IA en esta etapa:** El sonido tardó varias iteraciones en funcionar. El problema principal era que el AudioContext no puede crearse antes de una interacción del usuario, ya que el navegador lo bloquea. Claude identificó este problema y reestructuró el código para que el audio se creara dentro del evento de clic.

**Prompt utilizado:**

"El sonido no funciona, no se escucha nada"

## 8. Sistema de transmisión inalámbrica

Se evaluaron tres arquitecturas de transmisión:

**Opción A — Red propia del Arduino (Access Point).** El Arduino crea su propia red WiFi planta-sensor. El PC receptor se conecta a esa red. Funciona sin internet, en la misma sala.

**Opción B — dweet.io (HTTP).** El Arduino envía datos a dweet.io por internet. El HTML los lee desde ahí. Funciona entre casas distintas, pero dweet.io presentó caídas durante las pruebas.

**Opción C — HiveMQ (MQTT).** El Arduino publica datos en un broker MQTT gratuito. El HTML se suscribe al mismo canal vía WebSocket. Funciona entre casas distintas, de forma más estable.

Para el examen en sala se usa la Opción A (red propia). Para el video entre casas se usa la Opción C (HiveMQ MQTT).

**Uso de IA en esta etapa:** Se consultó a Claude extensamente sobre cómo resolver la comunicación entre casas distintas. Claude explicó las diferencias entre las opciones y los problemas encontrados (dweet.io caído, IP 0.0.0.0 por falta de delay al conectar).

**Prompts utilizados:**

"Estaremos en casas distintas para grabar el video, ¿cómo lo hacemos si no podemos estar en la misma red?"

"dweet.io no se puede abrir en el navegador"

"¿Podemos ocupar otro que no sea dweet?"

## 9. Plan de contingencia

El grupo identificó los posibles puntos de falla y preparó soluciones:

| Riesgo | Solución |
|---|---|
| ADS1115 defectuoso | Simular datos con random() en el Arduino |
| Planta con poca señal | Tocar los electrodos con el dedo directamente |
| WiFi del Arduino no llega | Usar cable USB y datos por Serial |
| Visualización sin reacción | Ajustar el valor MAX según los datos reales |
| Sonido no funciona | Verificar que se hizo clic en "toca para iniciar" |

## 10. Reflexión final

El mayor aprendizaje técnico fue la calibración de los datos. El sistema funcionaba correctamente desde el inicio, pero la visualización no reaccionaba porque el MAX estaba mal calibrado. Una vez que se midieron los valores reales de la planta (±19000) y se ajustó el código, todo funcionó.

El mayor aprendizaje conceptual fue entender que la planta no es solo un sensor, es un organismo con partes distintas que responden de manera diferente. Eso justifica los 4 electrodos y los 4 atributos visuales independientes.

Lo que diferencia este proyecto de otros similares en el mundo (Mileece, PlantWave) es la combinación de:

- Múltiples puntos de lectura simultáneos (4 canales)
- Transmisión inalámbrica propia sin hardware propietario
- Visualización generativa en tiempo real
- Todo con tecnología accesible y open source

### Resumen de uso de IA

| Momento | Herramienta | Tipo de uso |
|---|---|---|
| Definición técnica | Claude (Anthropic) | Consulta sobre hardware disponible |
| Investigación de referentes | Claude (Anthropic) | Búsqueda de artistas y proyectos similares |
| Explicación de conceptos | Claude (Anthropic) | Arrays, for, bio-conductividad |
| Prueba de hardware | Claude (Anthropic) | Guía paso a paso, diagnóstico de errores |
| Calibración de datos | Claude (Anthropic) | Identificación del problema con el MAX |
| Código de visualización | Claude (Anthropic) | Escritura del código p5.js iterado con el grupo |
| Código de sonido | Claude (Anthropic) | Escritura del código Web Audio API |
| Código Arduino | Claude (Anthropic) | Escritura y depuración del código |
| Arquitectura WiFi/MQTT | Claude (Anthropic) | Consulta y decisión entre opciones |

Claude no tomó decisiones creativas. Todas las decisiones sobre concepto, estética, qué planta usar, qué colores, qué tipo de visualización, fueron del grupo. Claude funcionó como un profesor técnico disponible en cualquier momento.

## Conclusión

"La Voz de las Plantas" partió de un problema de infraestructura —un servicio caído— y terminó convirtiéndose en un sistema propio, más robusto y mejor entendido en cada una de sus capas: hardware, conectividad y visualización.

El mayor aprendizaje no fue de programación, sino de método: varios errores que parecían bugs de código eran en realidad errores de interpretación sobre qué estaba midiendo realmente el hardware. Antes de corregir una fórmula, primero hay que entender el fenómeno físico que esa fórmula intenta representar.

El resultado final logra justamente eso: traducir la actividad eléctrica real de una planta medida en cuatro puntos distintos en una experiencia sensorial coherente, donde cada electrodo tiene su propia onda, su propio color y su propio sonido, reaccionando en tiempo real a lo que la planta está haciendo.

Más que un proyecto cerrado, "La Voz de las Plantas" deja una arquitectura abierta: misma base de hardware y conectividad, lista para nuevas formas de visualización o nuevos tipos de sensores en el futuro.
