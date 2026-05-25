// ============================================================
// Arduino UNO R4 WiFi — Receptor MQTT → Relé → Solenoide
// El potenciómetro controla la FRECUENCIA de golpes
//
// LIBRERÍAS (Library Manager):
//   "Adafruit MQTT Library" by Adafruit
//   "WiFiS3" viene con el soporte del R4
//
// PROTOCOLO (feed: papa-prueba):
//   "0"        → detener (sin golpes)
//   "1".."100" → frecuencia de golpes (mayor = más rápido)
//
// NOTA: el ZHO-0420S es pull-type y golpea al DESACTIVARSE.
// ============================================================

#include <WiFiS3.h>
#include <Adafruit_MQTT.h>
#include <Adafruit_MQTT_Client.h>

// ---- CONFIGURACIÓN ----------------------------------------
const char* WIFI_SSID     = "iPhone-cs";
const char* WIFI_PASSWORD = "lasagna342";

const char* AIO_SERVER    = "io.adafruit.com";
const int   AIO_PORT      = 1883;
const char* AIO_USERNAME  = "Camila_Parada";
const char* AIO_KEY       = "Clave-io";

const char* AIO_FEED      = "Camila_Parada/feeds/papa-prueba";

const int   RELE_PIN      = 7;
const int   PULSO_MS      = 60;   // duración energizado de cada golpe

// Rango de frecuencia (en ms entre golpes)
const long  INTERVALO_MIN = 200;   // a 100% → golpe cada 200ms (~5/seg)
const long  INTERVALO_MAX = 2000;  // a 1%   → golpe cada 2000ms (1 cada 2s)
// -----------------------------------------------------------

WiFiClient wifiClient;
Adafruit_MQTT_Client mqtt(&wifiClient, AIO_SERVER, AIO_PORT,
                          AIO_USERNAME, AIO_KEY);

Adafruit_MQTT_Subscribe feed =
    Adafruit_MQTT_Subscribe(&mqtt, AIO_FEED);

int  nivelActual      = 0;       // 0-100, controla la frecuencia
long intervaloGolpe   = 0;       // ms entre golpes (0 = detenido)
unsigned long ultimoGolpe = 0;

// ============================================================
void setup() {
  Serial.begin(115200);
  delay(1000);

  pinMode(RELE_PIN, OUTPUT);
  digitalWrite(RELE_PIN, LOW);

  Serial.println("=== Receptor MQTT — Solenoide por frecuencia ===");

  Serial.print("Conectando a WiFi");
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();

  Serial.print("Esperando IP");
  while (WiFi.localIP() == IPAddress(0, 0, 0, 0)) {
    delay(300);
    Serial.print(".");
  }
  Serial.println();
  Serial.print("Conectado! IP: ");
  Serial.println(WiFi.localIP());
  delay(500);

  mqtt.subscribe(&feed);
  conectarMQTT();
  Serial.println("Esperando datos del potenciometro...");
}

// ============================================================
void loop() {
  if (!mqtt.connected()) conectarMQTT();
  mqtt.processPackets(50);

  // --- Leer mensajes entrantes ---
  Adafruit_MQTT_Subscribe* sub;
  while ((sub = mqtt.readSubscription(50))) {
    if (sub == &feed) {
      String msg = String((char*)feed.lastread);
      int valor = msg.toInt();   // convierte a número
      nivelActual = valor;

      Serial.print("Recibido: ");
      Serial.print(valor);
      Serial.print("% -> ");

      if (valor <= 0) {
        intervaloGolpe = 0;  // detenido
        Serial.println("DETENIDO");
      } else {
        // Mapear 1-100% a intervalo (mayor % = menor intervalo = más rápido)
        intervaloGolpe = map(valor, 1, 100, INTERVALO_MAX, INTERVALO_MIN);
        Serial.print("golpe cada ");
        Serial.print(intervaloGolpe);
        Serial.println(" ms");
      }
    }
  }

  // --- Generar golpes según la frecuencia ---
  if (intervaloGolpe > 0) {
    unsigned long ahora = millis();
    if (ahora - ultimoGolpe >= intervaloGolpe) {
      ultimoGolpe = ahora;
      dispararSolenoide();
    }
  }
}

// ============================================================
void dispararSolenoide() {
  Serial.println(">>> GOLPE");
  digitalWrite(RELE_PIN, HIGH);  // energiza (retrae el émbolo)
  delay(PULSO_MS);
  digitalWrite(RELE_PIN, LOW);   // suelta → golpe al final
}

// ============================================================
void conectarMQTT() {
  Serial.print("Conectando a Adafruit IO");
  int8_t ret;
  uint8_t intentos = 0;
  while ((ret = mqtt.connect()) != 0) {
    Serial.print(".");
    Serial.println(mqtt.connectErrorString(ret));
    mqtt.disconnect();
    delay(3000);
    intentos++;
    if (intentos > 5) {
      Serial.println("Reseteando WiFi...");
      WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
      intentos = 0;
    }
  }
  Serial.println(" Conectado!");
}