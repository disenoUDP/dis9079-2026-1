// ejemplo02Enviar
// placa se conecta a un servidor mosquitto
// y envia mensaje al topic dis9079/20260323/led
// para ser recibido por una placa raspberry pi
// y prender su led
// basado en ejemplo de la biblioteca
// ArduinoMqttClient - WiFi Simple Sender
// marzo 2026
// por montoyamoraga para disenoUDP

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
const char topic[] = "dis9079/20260323/led";

const long intervalo = 10000;
unsigned long previousMillis = 0;

int count = 0;

void setup()
{
  // inicializar el puerto serial
  Serial.begin(9600);
  // si no se ha inicializado, esperar
  while (!Serial)
  {
    ;
  }

  // conectarse a wifi
  Serial.print("conectandose a red ");
  Serial.println(ssid);

  while (WiFi.begin(ssid, pass) != WL_CONNECTED)
  {
    // si falla, reintentar
    Serial.print(".");
    delay(5000);
  }

  Serial.println("te conectaste a la red!");

  // ID del cliente
  // cada cliente debe tener una ID unica
  mqttClient.setId("agustinaaceituno");

  // autenticacion con username y clave
  mqttClient.setUsernamePassword("agustinaaceituno", "dis9079");

  Serial.print("tratando de conectarse al MQTT broker ");
  Serial.println(broker);

  if (!mqttClient.connect(broker, port))
  {
    Serial.print("conexion a MQTT fallida! codigo del error = ");
    Serial.println(mqttClient.connectError());

    while (1)
      ;
  }

  Serial.println("te conectaste al MQTT broker!");
  Serial.println();
}

void loop()
{
  // call poll() regularly to allow the library to send MQTT keep alives which
  // avoids being disconnected by the broker
  mqttClient.poll();

  // to avoid having delays in loop, we'll use the strategy from BlinkWithoutDelay
  // see: File -> Examples -> 02.Digital -> BlinkWithoutDelay for more info
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= intervalo)
  {
    // save the last time a message was sent
    previousMillis = currentMillis;

    Serial.print("enviando mensaje al topic:");
    Serial.println(topic);
    Serial.print("presente ");
    Serial.println(count);

    // send message, the Print interface can be used to set the message contents
    mqttClient.beginMessage(topic);
    mqttClient.print("presente profe ");
    mqttClient.print(count);
    mqttClient.endMessage();

    Serial.println();

    count++;
  }
}
