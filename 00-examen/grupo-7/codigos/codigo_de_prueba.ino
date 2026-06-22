#include <Wire.h>
#include <Adafruit_ADS1X15.h>

Adafruit_ADS1115 ads;

void setup() {
  Serial.begin(9600);
  Serial.println("=== PRUEBA ADS1115 ===");

  if (!ads.begin()) {
    Serial.println("ERROR: No se encontro el ADS1115.");
    Serial.println("Revisar conexiones VDD, GND, SDA, SCL.");
    while (1);
  }

  Serial.println("ADS1115 encontrado correctamente.");
  Serial.println("Leyendo los 4 canales cada 1 segundo...");
  Serial.println("-------------------------------------");
}

void loop() {
  for (int i = 0; i < 4; i++) {
    int valor = ads.readADC_SingleEnded(i);
    float voltaje = ads.computeVolts(valor);

    Serial.print("Canal ");
    Serial.print(i);
    Serial.print(": ");
    Serial.print(valor);
    Serial.print(" raw  |  ");
    Serial.print(voltaje, 4);
    Serial.println(" V");
  }

  Serial.println("-------------------------------------");
  delay(1000);
}