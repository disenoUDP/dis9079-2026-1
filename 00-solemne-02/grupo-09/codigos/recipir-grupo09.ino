#include <WiFiS3.h>
#include <Servo.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"


// WiFi


#define WIFI_SSID "NombreRedWifi"
#define WIFI_PASS "ContraseñaWifi"


// Adafruit IO


#define AIO_SERVER     "io.adafruit.com"
#define AIO_PORT        1883
#define AIO_USERNAME   "UsernameAio"
#define AIO_KEY        "KeyAio"






//  Servo


Servo myServo;
const int SERVO_PIN = 9;


// limitantes de movimiento
#define IZQUIERDA  45
#define DERECHA   135
#define CENTRO     90


// variables de movimiento
unsigned long MOVING_TIME = 1000;   // ms para llegar al destino (más bajo = más rápido)
unsigned long moveStartTime;
int startAngle  = CENTRO;          // ángulo desde donde parte
int targetAngle = CENTRO;          // ángulo destino recibido por MQTT
int currentAngle = CENTRO;         // ángulo actual del servo


// --- MQTT ---
WiFiClient wifiClient;
Adafruit_MQTT_Client mqtt(&wifiClient, AIO_SERVER, AIO_PORT, AIO_USERNAME, AIO_KEY);
Adafruit_MQTT_Subscribe servoFeed = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/AioFeed");


void connectWiFi() {
  Serial.print("Conectando a WiFi");
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500); Serial.print(".");
  }
  Serial.println("\nWiFi conectado: " + WiFi.localIP().toString());
}


void connectMQTT() {
  int8_t ret;
  while ((ret = mqtt.connect()) != 0) {
    Serial.print("Error MQTT :( ");
    Serial.println(mqtt.connectErrorString(ret));
    Serial.println("Reintentando en 3s...");
    mqtt.disconnect();
    delay(3000);
  }
  Serial.println("MQTT conectado :D!");
}


int mapearRango(int angle) {
  return map(angle, 0, 180, IZQUIERDA, DERECHA);
}


void setup() {
  Serial.begin(115200);
  myServo.attach(SERVO_PIN);
  myServo.write(CENTRO);
  moveStartTime = millis();


  Serial.println("Izquierda = " + String(IZQUIERDA) + "°");
  Serial.println("Centro    = " + String(CENTRO)    + "°");
  Serial.println("Derecha   = " + String(DERECHA)   + "°");


  connectWiFi();
  mqtt.subscribe(&servoFeed);
  connectMQTT();
}


void loop() {
  if (!mqtt.connected()) connectMQTT();


  //Ping cada 60s para no bloquear el loop
  static unsigned long lastPing = 0;
  if (millis() - lastPing > 60000) {
    mqtt.ping();
    lastPing = millis();
  }


  //Leer nuevo ángulo desde Adafruit IO
  Adafruit_MQTT_Subscribe* subscription;
  while ((subscription = mqtt.readSubscription(5))) {
    if (subscription == &servoFeed) {
      int received = atoi((char*)servoFeed.lastread);
      int mapped   = constrain(mapearRango(received), IZQUIERDA, DERECHA);


      // Solo actualizar si el ángulo cambió
      if (mapped != targetAngle) {
        startAngle    = currentAngle;  // parte desde donde está ahora
        targetAngle   = mapped;
        moveStartTime = millis();      // reinicia el movimiento
        Serial.println("Destino: " + String(targetAngle) + "°");
      }
    }
  }


  // Mover servo progresivamente hacia el destino
  unsigned long progress = millis() - moveStartTime;


  if (progress <= MOVING_TIME) {
    currentAngle = map(progress, 0, MOVING_TIME, startAngle, targetAngle);
    myServo.write(currentAngle);
  } else {
    currentAngle = targetAngle;
    myServo.write(currentAngle);
  }
}
