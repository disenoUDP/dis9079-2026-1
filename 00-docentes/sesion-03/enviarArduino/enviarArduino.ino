// enviarArduino
// placa se conecta a un servidor mosquitto
// y envia mensaje a un topic
// para ser recibido por una placa raspberry pi
// y prender su led
// basado en ejemplo de la biblioteca
// ArduinoMqttClient - WiFi Simple Sender
// marzo 2026
// por montoyamoraga para disenoUDP

// importar bibliotecas
#include <ArduinoMqttClient.h>
#include <WiFiS3.h>

const char *grupos[] = {
    "aaron",
    "grupo-01",
    "grupo-02",
    "grupo-03",
    "grupo-04",
    "grupo-05",
    "grupo-06",
    "grupo-07",
    "grupo-08",
    "grupo-09",
    "grupo-10",
    "grupo-11",
    "mateo",
};

const char *arduinos[] = {
    "arduinoAaron",
    "arduino01",
    "arduino02",
    "arduino03",
    "arduino04",
    "arduino05",
    "arduino06",
    "arduino07",
    "arduino08",
    "arduino09",
    "arduino10",
    "arduino11",
    "arduinoMateo",
};

const char *raspicos[] = {
    "raspicoAaron",
    "raspico01",
    "raspico02",
    "raspico03",
    "raspico04",
    "raspico05",
    "raspico06",
    "raspico07",
    "raspico08",
    "raspico09",
    "raspico10",
    "raspico11",
    "raspicoMateo",
};

// cambiar por tu numero de grupo
// yo soy 0, mateo es 12
int numeroDeGrupo = 0;

// importar archivo .h con claves
#include "arduino_secrets.h"

char ssid[] = SECRET_SSID;
char pass[] = SECRET_PASS;

WiFiClient wifiClient;
MqttClient mqttClient(wifiClient);

const char broker[] = "10.175.169.28";
int port = 1883;
const char topic[] = "dis9079/20260323/grupo20";

// intervalo de tiempo para enviar mensaje
// medido en ms
const long intervalo = 10000;

// variable para guardar el momento en que se envio
// el mensaje anterior
unsigned long momentoAnterior = 0;

int numeritoMensaje = numeroDeGrupo;

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
  // este cliente es la placa arduino
  mqttClient.setId(arduinos[numeroDeGrupo]);

  // autenticacion con username y clave
  mqttClient.setUsernamePassword(arduinos[numeroDeGrupo], "dis9079");

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

  if (currentMillis - momentoAnterior >= intervalo)
  {
    // save the last time a message was sent
    momentoAnterior = currentMillis;

    Serial.print("enviando mensaje al topic:");
    Serial.println(topic);
    Serial.print("numeritoMensaje ");
    Serial.println(numeritoMensaje);

    // enviar mensaje
    // la interfaz print puede ser usada para
    // definir los contenidos del mensaje
    mqttClient.beginMessage(topic);
    mqttClient.print("numeritoMensaje ");
    mqttClient.print(numeritoMensaje);
    mqttClient.endMessage();

    Serial.println();
  }
}
