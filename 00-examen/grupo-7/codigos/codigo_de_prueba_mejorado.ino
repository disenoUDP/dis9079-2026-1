// ============================================================
// PRUEBA ADS1115 - Grupo 07
// Version mejorada: muestra cambios de forma clara
// ============================================================

#include <Wire.h>
#include <Adafruit_ADS1X15.h>

Adafruit_ADS1115 ads;

// Valor base de cada canal (sin tocar la planta)
// El codigo lo calibra solo los primeros 3 segundos
int base[4] = {0, 0, 0, 0};
bool calibrado = false;

void setup() {
  Serial.begin(9600);

  if (!ads.begin()) {
    Serial.println("ERROR: ADS1115 no encontrado. Revisar cables.");
    while (1);
  }

  ads.setGain(GAIN_SIXTEEN); // maxima sensibilidad

  Serial.println("Calibrando... no toques la planta");
  delay(1000);

  for (int i = 0; i < 4; i++) {
    long suma = 0;
    for (int j = 0; j < 5; j++) {
      suma += ads.readADC_SingleEnded(i);
      delay(100);
    }
    base[i] = suma / 5;
  }

  calibrado = true;
  Serial.println("Calibrado! Valores base:");
  for (int i = 0; i < 4; i++) {
    Serial.print("  Canal ");
    Serial.print(i);
    Serial.print(": ");
    Serial.println(base[i]);
  }
  Serial.println("=============================");
  Serial.println("Acerca la mano o toca la planta");
  Serial.println("=============================");
}

void loop() {
  String nombres[4] = {"hoja grande ", "hoja pequeña", "tallo       ", "sustrato    "};

  Serial.println();

  for (int i = 0; i < 4; i++) {
    int valor = ads.readADC_SingleEnded(i);
    int cambio = valor - base[i];
    int porcentaje = abs(cambio) * 100 / max(base[i], 1);

    String barra = "";
    int bloques = min(porcentaje / 5, 20);
    for (int b = 0; b < bloques; b++) barra += "█";

    String estado = "";
    if (porcentaje < 2)       estado = "  calma";
    else if (porcentaje < 8)  estado = "  movimiento leve";
    else if (porcentaje < 15) estado = "  ¡actividad!";
    else                      estado = "  ¡¡MUCHO MOVIMIENTO!!";

    Serial.print(nombres[i]);
    Serial.print(" | ");
    if (cambio >= 0) Serial.print("+");
    Serial.print(cambio);
    Serial.print("\t");
    Serial.print(barra);
    Serial.print(estado);
    Serial.println();
  }

  Serial.println("-----------------------------");
  delay(800);
}