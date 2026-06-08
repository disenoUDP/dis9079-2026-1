# sesion-02 - lunes 16 marzo 2026

Hoy nos dedicamos a dejar todo listo para poder programar y documentar de forma profesional. Lo primero fue unirnos al Discord del laboratorio (usando Nombre-Apellido para que los profes no se pierdan) y hacer el fork del repositorio del curso en GitHub y formamos grupos de trabajos para la entrega n°1.

**Tip de organización:** Usar Markdown es clave para que la documentación se vea jerarquizada y limpia. Aprendí que con Ctrl + A seleccionas todo el código rápido en el IDE.

### Hardware y Software: Entrando en materia

Trabajamos con la placa Arduino Uno R4 WiFi. Lo que más me llamó la atención es que, a diferencia de la R3 clásica, esta ya trae WiFi integrado y una matriz LED de 12×8 pixeles. Es hardware de código abierto (OSHW), lo que significa que cualquiera puede estudiarlo y mejorarlo.


**Instalaciones obligatorias:**

  1. Arduino IDE 2.3.8: El centro de mando.
  2. Bibliotecas: ArduinoGraphics, ArduinoMQTTClienet (para la mensajería) y Arduino_LED_Matrix.
  3. Mosquitto: Instalar vía Homebrew (en Mac), que sirve como el "broker" o intermediario para que los dispositivos se hablen entre sí.

### Primeros pasos con código

Entendí que un código básico de Arduino siempre tiene dos partes:

  1. setup(): Donde configuro todo (se corre solo una vez).
  2. loop(): Donde ocurre la magia y se repite infinitamente.

#### Reto 1: Texto en la matriz LED

Hicimos una prueba para que la placa mostrara un texto en movimiento. Usamos la biblioteca ArduinoGraphics.h. El código define una instancia llamada pantalla y luego en el loop dibujamos el texto con textScrollSpeed(100).

Código que usamos para la animación:
```cpp
// ejemplo01
// imprime la sigla del curso en la pantalla led
// de la Arduino Uno R4 WiFi
// basado en
// https://docs.arduino.cc/tutorials/uno-r4-wifi/led-matrix/#scrolling-text-example
// marzo 2026
// por montoyamoraga para disenoUDP

// incluir bibliotecas
#include <ArduinoGraphics.h>
#include "Arduino_LED_Matrix.h"

// declarar instancia de ArduinoLEDMatrix
// con nombre pantalla
ArduinoLEDMatrix pantalla;

void setup() {

  // iniciar puerto serial
  Serial.begin(115200);

  // inicializar pantalla
  pantalla.begin();

}

void loop() {

  // definir nuevo dibujo
  pantalla.beginDraw();

  // definir trazo
  pantalla.stroke(0xFFFFFFFF);

  // definir velocidad de deslizamiento
  pantalla.textScrollSpeed(100);

  // definir texto
  const char texto[] = "    diseno udp dis9704 interacciones inalambricas    ";
  
  // definir tipo
  pantalla.textFont(Font_5x7);

  // definir inicio del texto
  pantalla.beginText(0, 1, 0xFFFFFF);

  // imprimir el texto
  pantalla.println(texto);

  // deslizar hacia la izquierda
  pantalla.endText(SCROLL_LEFT);

  // fin del dibujo
  pantalla.endDraw();
}
```
### Reto 2: Comunicación con MQTT (Recibir mensajes)

Esto fue lo más "pro". Configuramos el Arduino para que se conectara al WiFi y escuchara un "topic" específico en el broker Mosquitto (IP: 10.174.124.28, puerto 1883).

const char birker[] = "ip" es capaz de encontrar donde está mosquitto

Para la recepción de mensajes, lo configuramos así:

```cpp
int port = 1883;
const char topic[] = "asistencia/20260316";

#define SECRET_SSID "pixel9"
#define SECRET_PASS "mateo123"
```
```cpp
// placa se conecta a un servidor mosquitto
// y recibe mensajes del topic asistencia/20260316
// basado en ejemplo de la biblioteca
// ArduinoMqttClient - WiFi Simple Receive
// marzo 2026
// por montoyamoraga para disenoUDP

/*
  ArduinoMqttClient - WiFi Simple Sender

  This example connects to a MQTT broker and publishes a message to
  a topic once a second.
*/

// importar bibliotecas
#include <ArduinoMqttClient.h>
#include <WiFiS3.h>

// importar archivo .h con claves
#include "arduino_secrets.h"

char ssid[] = SECRET_SSID;
char pass[] = SECRET_PASS;

WiFiClient wifiClient;
MqttClient mqttClient(wifiClient);

const char broker[] = "10.174.124.28";
int port = 1883;
const char topic[] = "asistencia/20260316";

const long intervalo = 10000;
unsigned long previousMillis = 0;

int count = 0;

void setup() {
  // inicializar el puerto serial
  Serial.begin(9600);
  // si no se ha inicializado, esperar
  while (!Serial) {
    ;
  }

  // conectarse a wifi
  Serial.print("conectandose a red ");
  Serial.println(ssid);

  while (WiFi.begin(ssid, pass) != WL_CONNECTED) {
    // si falla, reintentar
    Serial.print(".");
    delay(5000);
  }

  Serial.println("te conectaste a la red!");

  // ID del cliente
  // cada cliente debe tener una ID unica
  mqttClient.setId("montoyamoraga");

  // autenticacion con username y clave
  mqttClient.setUsernamePassword("montoyamoraga", "dis9079");

  Serial.print("tratando de conectarse al MQTT broker ");
  Serial.println(broker);

  if (!mqttClient.connect(broker, port)) {
    Serial.print("conexion a MQTT fallida! codigo del error = ");
    Serial.println(mqttClient.connectError());

    while (1)
      ;
  }

  Serial.println("te conectaste al MQTT broker!");
  Serial.println();

  Serial.print("subscribiendose al topic: ");
  Serial.println(topic);
  Serial.println();

  // subscribe to a topic
  mqttClient.subscribe(topic);

  // topics can be unsubscribed using:
  // mqttClient.unsubscribe(topic);

  Serial.print("esperando mensajes en el topic: ");
  Serial.println(topic);
  Serial.println();
}

void loop() {
  int messageSize = mqttClient.parseMessage();
  if (messageSize) {
    // we received a message, print out the topic and contents
    Serial.print("recibi un mensaje con el topic '");
    Serial.print(mqttClient.messageTopic());
    Serial.print("', length ");
    Serial.print(messageSize);
    Serial.println(" bytes:");

    // use the Stream interface to print the contents
    while (mqttClient.available()) {
      Serial.print((char)mqttClient.read());
    }
    Serial.println();

    Serial.println();
  }
}
```

**Nota personal:** Me di cuenta de que si el puerto serial no abre (usando while (!Serial);), el código se queda pegado ahí. Tengo que estar atenta al monitor serial!


### Bibliografía y Referencias

* Arduino. (s.f.). *LED matrix*. https://docs.arduino.cc/tutorials/uno-r4-wifi/led-matrix/

* GitHub. (s.f.). *Primeros pasos con la escritura y el formato en GitHub: Sintaxis básica*. https://docs.github.com/es/get-started/writing-on-github/getting-started-with-writing-and-formatting-on-github/basic-writing-and-formatting-syntax

* Mosquitto. (s.f.). *Documentation*. https://mosquitto.org/documentation/

* Open Source Hardware Association. (s.f.). *Open source hardware*. https://oshwa.org/

* Techlib. (s.f.). *Hardware de código abierto*. https://techlib.net/techedu/hardware-de-codigo-abierto/


