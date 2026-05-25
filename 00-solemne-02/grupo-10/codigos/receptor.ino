#include "AdafruitIO_WiFi.h"

#define IO_USERNAME "TU_USUARIO"
#define IO_KEY "TU_KEY"

#define WIFI_SSID "TU_WIFI"
#define WIFI_PASS "TU_PASSWORD"

AdafruitIO_WiFi io(IO_USERNAME, IO_KEY, WIFI_SSID, WIFI_PASS);

const int ledPin = 13;

AdafruitIO_Feed *botonFeed = io.feed("boton-prueba-grupo10");

void setup() {

  pinMode(ledPin, OUTPUT);

  Serial.begin(115200);

  Serial.print("Conectando a Adafruit IO...");

  io.connect();

  botonFeed->onMessage(handleMessage);

  while(io.status() < AIO_CONNECTED) {

    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("¡Arduino Conectado!");
}

void loop() {

  io.run();
}

void handleMessage(AdafruitIO_Data *data) {

  int comando = data->toInt();

  if (comando == 1) {

    digitalWrite(ledPin, HIGH);

    Serial.println("LED ON");
  }

  else {

    digitalWrite(ledPin, LOW);

    Serial.println("LED OFF");
  }
}