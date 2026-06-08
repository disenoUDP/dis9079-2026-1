#include <WiFiS3.h>
#include <Servo.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"

// conexión a wifi
#define WLAN_SSID "si"
#define WLAN_PASS "mailo6192."

// conexión al adafruit io
#define AIO_SERVER     "io.adafruit.com"
#define AIO_SERVERPORT 1883
#define AIO_USERNAME   "udpmontoyamoraga"
#define AIO_KEY        "keydeaarón"
#define LED_PIN 13

WiFiClient client;
Adafruit_MQTT_Client mqtt(
  &client,
  AIO_SERVER,
  AIO_SERVERPORT,
  AIO_USERNAME,
  AIO_KEY
);

// se suscribe al feed que es de donde recibe la información
Adafruit_MQTT_Subscribe potenciometro =
Adafruit_MQTT_Subscribe(
  &mqtt,
  AIO_USERNAME "/feeds/potenciometro-05"
);

Servo miServo;
void MQTT_connect();

void setup() {
  Serial.begin(115200); // ver si monitor serial está a 115200, de no ser así, cambiarlo
  miServo.attach(9); // servo en pin ~9

  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

  Serial.println("Conectando WiFi"); // aquí se inicia la conexión al wifi
  WiFi.begin(WLAN_SSID, WLAN_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print("."); // puntitos hasta que lo logre
    delay(500);
  }
  Serial.println();
  Serial.println("WiFi conectado"); // yey!!

  mqtt.subscribe(&potenciometro);
}

void loop() {
  MQTT_connect();

  Adafruit_MQTT_Subscribe *subscription;
  while ((subscription = mqtt.readSubscription(1000))) {
    if (subscription == &potenciometro) {
      int valorPot = atoi(
        (char*)potenciometro.lastread
      );
      Serial.print("Recibido: ");
      Serial.println(valorPot);

      digitalWrite(LED_PIN, HIGH);
      delay(200); 
      digitalWrite(LED_PIN, LOW);

// aquí convierte la escala del potenciómetro de
// 0 - 1023 a ángulos del servo (de 0 - 180°)
      int angulo = map(valorPot, 0, 1023, 0, 180);
      angulo = constrain(angulo, 0, 180);

      Serial.print("Ángulo: ");
      Serial.println(angulo);
      miServo.write(angulo);
    }
  }
}

void MQTT_connect() {
  int8_t ret;
  if (mqtt.connected()) { 
    return;
  }
  Serial.print("Conectando MQTT...");
  while ((ret = mqtt.connect()) != 0) { // se intenta reconectar en caso de que suceda algo
    Serial.println(mqtt.connectErrorString(ret)); // si no logra hacerlo, imprime error y
    mqtt.disconnect(); // se desconecta
    delay(5000);  // pero vuelve a intentarlo luego de un reposo de 5 seg
  }
  Serial.println(" conectado"); // logrado!! yey
}