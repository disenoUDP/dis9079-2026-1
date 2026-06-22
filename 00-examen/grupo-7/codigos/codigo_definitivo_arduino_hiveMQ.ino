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