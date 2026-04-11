# sesion-04

lunes 30 marzo 2026

## HIVE MQ
https://www.hivemq.com/ 

Es un sistema de almacenamiento de datos distribuido y tolerante a errores que permite la realización de análisis a escala masiva . Un almacenamiento de datos proporciona un almacén central de información que se puede analizar con facilidad para tomar decisiones informadas y controladas por datos.

Routter del curso: Arduino se conectara a la red wifi

5g muy rapida pero de poco alcance

## TigerVNC (Tiger Virtual Network Computing)

https://tigervnc.org/

es un sistema de escritorio gráfico compartido que le permite controlar remotamente otros ordenadores.

Ayuda a instalar las cosas, renderizar el escritorio y permite instalar cosasde manera mas rapida.
sudo rf: borra todo el disco duro del computador
sudo topic: tiene que ser mismo pata enviar y recivir para que se pueda encontrar la ip
ia: claude o chat gpt

Ejemplo grupo 01: enviar a arduino R4 wifi


Arduino01
clave: dis9079


/*
  ArduinoMqttClient - WiFi Simple Sender

  This example connects to a MQTT broker and publishes a message to
  a topic once a second.

  The circuit:
  - Arduino MKR 1000, MKR 1010 or Uno WiFi Rev2 board

  This example code is in the public domain.
*/

#include <ArduinoMqttClient.h>
#if defined(ARDUINO_SAMD_MKRWIFI1010) || defined(ARDUINO_SAMD_NANO_33_IOT) || defined(ARDUINO_AVR_UNO_WIFI_REV2)
  #include <WiFiNINA.h>
#elif defined(ARDUINO_SAMD_MKR1000)
  #include <WiFi101.h>
#elif defined(ARDUINO_ARCH_ESP8266)
  #include <ESP8266WiFi.h>
#elif defined(ARDUINO_PORTENTA_H7_M7) || defined(ARDUINO_NICLA_VISION) || defined(ARDUINO_ARCH_ESP32) || defined(ARDUINO_GIGA) || defined(ARDUINO_OPTA)
  #include <WiFi.h>
#elif defined(ARDUINO_PORTENTA_C33)
  #include <WiFiC3.h>
#elif defined(ARDUINO_UNOR4_WIFI)
  #include <WiFiS3.h>
#endif

// #include "arduino_secrets.h"
///////please enter your sensitive data in the Secret tab/arduino_secrets.h
char ssid[] = "dis9079";    // your network SSID (name)
char pass[] = "75288273";    // your network password (use for WPA, or use as key for WEP)

// To connect with SSL/TLS:
// 1) Change WiFiClient to WiFiSSLClient.
// 2) Change port value from 1883 to 8883.
// 3) Change broker value to a server with a known SSL/TLS root certificate 
//    flashed in the WiFi module.

WiFiClient wifiClient;
MqttClient mqttClient(wifiClient);

const char broker[] = "192.168.0.100";
int        port     = 1883;
const char topic[]  = "arduino/simple";

const long interval = 1000;
unsigned long previousMillis = 0;

int count = 0;

// MODIFICAR
const char mqttId[] = "arduino01";
const char mqttPass[] = "dis9079";

void setup() {
  //Initialize serial and wait for port to open:
  Serial.begin(9600);

  // attempt to connect to WiFi network:
  Serial.print("Attempting to connect to WPA SSID: ");
  Serial.println(ssid);
  while (WiFi.begin(ssid, pass) != WL_CONNECTED) {
    // failed, retry
    Serial.print(".");
    delay(5000);
  }

  Serial.println("You're connected to the network");
  Serial.println();

  // You can provide a unique client ID, if not set the library uses Arduino-millis()
  // Each client must have a unique client ID
  mqttClient.setId(mqttId);

  // You can provide a username and password for authentication
  mqttClient.setUsernamePassword(mqttId, mqttPass);

  Serial.print("Attempting to connect to the MQTT broker: ");
  Serial.println(broker);

  if (!mqttClient.connect(broker, port)) {
    Serial.print("MQTT connection failed! Error code = ");
    Serial.println(mqttClient.connectError());

    delay(2000);
  }

  Serial.println("You're connected to the MQTT broker!");
  Serial.println();
}

void loop() {
  // call poll() regularly to allow the library to send MQTT keep alives which
  // avoids being disconnected by the broker
  mqttClient.poll();

  // to avoid having delays in loop, we'll use the strategy from BlinkWithoutDelay
  // see: File -> Examples -> 02.Digital -> BlinkWithoutDelay for more info
  unsigned long currentMillis = millis();
  
  if (currentMillis - previousMillis >= interval) {
    // save the last time a message was sent
    previousMillis = currentMillis;

    Serial.print("Sending message to topic: ");
    Serial.println(topic);
    Serial.print("hello ");
    Serial.println(count);

    // send message, the Print interface can be used to set the message contents
    mqttClient.beginMessage(topic);
    mqttClient.print("hello ");
    mqttClient.print(count);
    mqttClient.endMessage();

    Serial.println();

    count++;
  }
}

Pudo enviar el mensaje, pero no recibir 


Para que arduino prenda y apague la luz: se debe conectar a la red wifi dis9079
clave: 75288273
sitio web: 192.48.56.2/


## Claude Shannon

Claude Elwood Shannon, nacido el 30 de abril de 1916 en Petoskey, Michigan, fue uno de los matemáticos e ingenieros más brillantes del siglo XX.
Considerado el «padre de la era digital» por fundamentar la teoría de la información y la lógica de circuitos.

Su trabajo revolucionario en la teoría de la información y la lógica digital sentó las bases para el progreso digital de la computación moderna y transformó radicalmente la manera en que entendemos y manipulamos la información.

## 1. El inventor del "Bit"

Antes de Shannon, la información era algo vago. Él fue quien popularizó el término BIT (Binary Digit) y demostró que cualquier tipo de información (voz, imagen, texto, o el contador de tu código de Arduino) podía ser representada mediante unos y ceros.

## 2. La Teoría de la Información

Shannon definió un modelo universal de comunicación que es exactamente lo que estás replicando en tu tarea de Adafruit:

-Fuente: Tu Arduino.

-Transmisor: El chip WiFi de tu placa.

-Canal: El aire (ondas de radio).

-Ruido: Las interferencias que hacían que te salieran "signos de interrogación".

-Receptor: Los servidores de Adafruit.

-Destino: Tu otra computadora.


