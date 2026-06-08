/*************************************************************
   PROYECTO: RECEPTOR ARDUINO (ESPEJO DE BOTÓN)
*************************************************************/
#include "AdafruitIO_WiFi.h"

// ==========================================
// CREDENCIALES
// ==========================================
#define IO_USERNAME  "udpmontoyamoraga"
#define IO_KEY       "clavecredencial"
#define WIFI_SSID    "marce"
#define WIFI_PASS    "marce1234"

// ==========================================
// CONFIGURACIÓN
// ==========================================

// Instancia Adafruit IO
AdafruitIO_WiFi io(IO_USERNAME, IO_KEY, WIFI_SSID, WIFI_PASS);

// Pin del LED
const int ledPin = 13;

// Feed (debe ser el mismo que usa la Raspberry)
AdafruitIO_Feed *botonFeed = io.feed("boton-prueba-grupo10");

// ==========================================
// SETUP
// ==========================================
void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(115200);

  Serial.print("Conectando a Adafruit IO...");
  io.connect();

  // Función que reaccionará a los datos
  botonFeed->onMessage(handleMessage);

  // Esperar conexión
  while(io.status() < AIO_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("¡Arduino Conectado!");
}

// ==========================================
// LOOP
// ==========================================
void loop() {
  // Mantener conexión activa
  io.run();
}

// ==========================================
// FUNCIÓN QUE RECIBE DATOS
// ==========================================
void handleMessage(AdafruitIO_Data *data) {
  // Convertir dato recibido a entero
  int comando = data->toInt();

  // Si recibe 1 -> prender LED
  if (comando == 1) {
    digitalWrite(ledPin, HIGH);
    Serial.println("LED ON");
  }
  // Si recibe 0 -> apagar LED
  else {
    digitalWrite(ledPin, LOW);
    Serial.println("LED OFF");
  }
}