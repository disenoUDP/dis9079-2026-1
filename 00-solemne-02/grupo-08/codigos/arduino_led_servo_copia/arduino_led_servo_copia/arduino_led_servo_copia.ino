// Grupo 08
// Arduino UNO R4 WiFi — Adafruit IO → Servo SG90 + LED rojo

//  Recibe ángulo (0-180°) desde Adafruit IO
//  → Mueve el servo SG90 a ese ángulo
//  → Si ángulo >= 150°: LED rojo enciende (señal de término)
//  → Si ángulo <  150°: LED rojo apagado
// incluir libreías para que funicoofg
#include <WiFiS3.h>
#include <ArduinoMqttClient.h>
#include <Servo.h>

// configuracion de los datos
const char* WIFI_SSID     = "iPhone de Valentina";
const char* WIFI_PASSWORD = "blabla";

const char* AIO_SERVER    = "io.adafruit.com";
const int   AIO_PORT      = 1883;
const char* AIO_USERNAME  = "vxlentiinaa";
const char* AIO_KEY       = "blabla";

const char* FEED_ANGULO   = "vxlentiinaa/feeds/moluscos";

// definir pines del servo y led
const int PIN_SERVO    = 9;
const int PIN_LED_ROJO = 3;

// angulo a partir del cual enciende el LED (señal de termino)
const int ANGULO_TERMINO = 125;

// wifi + servo
WiFiClient   wifiClient;
MqttClient   mqttClient(wifiClient);
Servo        miServo;

// se ejecuta al recibir el mensaje
void onMqttMessage(int messageSize) {
  String payload = "";
  while (mqttClient.available()) {
    payload += (char)mqttClient.read();
  }

  int angulo = payload.toInt();
  angulo = constrain(angulo, 0, 180);  // seguridad: limita al rango del servo

  Serial.print("Ángulo recibido: ");
  Serial.print(angulo);
  Serial.println("°");

  // mueve el servo
  miServo.write(angulo);

  // LED rojo: enciende si llego al angulo de termino
  if (angulo >= ANGULO_TERMINO) {
    digitalWrite(PIN_LED_ROJO, HIGH);
    Serial.println("  → LED ROJO encendido ✓ (término alcanzado)");
  } else {
    digitalWrite(PIN_LED_ROJO, LOW);
    Serial.print("  → Servo en ");
    Serial.print(angulo);
    Serial.print("° (falta ");
    Serial.print(ANGULO_TERMINO - angulo);
    Serial.println("° para término)");
  }
}

// setup
void setup() {
  Serial.begin(115200);
  delay(1500);

  // pines
  pinMode(PIN_LED_ROJO, OUTPUT);
  digitalWrite(PIN_LED_ROJO, LOW);

  miServo.attach(PIN_SERVO);
  miServo.write(0);   // posicion inicial: 0°

  Serial.println("=== Arduino UNO R4 WiFi — Servo SG90 + LED ===\n");

  // wifi
  Serial.print("Conectando a WiFi");
  while (WiFi.begin(WIFI_SSID, WIFI_PASSWORD) != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
  }
  Serial.println();
  Serial.print("  ✓ IP: ");
  Serial.println(WiFi.localIP());

  // mqtt
  mqttClient.setId("ArduinoUNOR4_servo");
  mqttClient.setUsernamePassword(AIO_USERNAME, AIO_KEY);
  mqttClient.onMessage(onMqttMessage);

  Serial.print("Conectando a Adafruit IO...");
  while (!mqttClient.connect(AIO_SERVER, AIO_PORT)) {
    Serial.print(".");
    delay(1000);
  }
  Serial.println();
  Serial.println("  ✓ Conectado a Adafruit IO");

  mqttClient.subscribe(FEED_ANGULO);
  Serial.println("  ✓ Suscrito al feed: moluscos");
  Serial.print("\nEsperando datos... LED enciende al llegar a ");
  Serial.print(ANGULO_TERMINO);
  Serial.println("°\n");

  // parpadeo de confirmacion
  for (int i = 0; i < 3; i++) {
    digitalWrite(PIN_LED_ROJO, HIGH); delay(150);
    digitalWrite(PIN_LED_ROJO, LOW);  delay(150);
  }
}

// loop
void loop() {
  // reconexion automatica
  if (!mqttClient.connected()) {
    Serial.println("[MQTT] Desconectado. Reconectando...");
    digitalWrite(PIN_LED_ROJO, LOW);
    miServo.write(0);

    while (!mqttClient.connect(AIO_SERVER, AIO_PORT)) {
      Serial.print(".");
      delay(2000);
    }
    mqttClient.subscribe(FEED_ANGULO);
    Serial.println("\n  ✓ Reconectado");
  }

  mqttClient.poll();
}
