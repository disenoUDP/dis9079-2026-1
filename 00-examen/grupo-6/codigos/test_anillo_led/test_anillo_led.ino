// ============================================================
// PUENTE DIGITAL — Grupo 6
// Código de PRUEBA para el Anillo LED RGB WS2812 (16 LEDs)
// Solo verifica que el anillo funcione correctamente.
// No requiere WiFi ni Adafruit IO.
// ============================================================
//
// Librería necesaria (Library Manager):
//  - Adafruit NeoPixel
// ============================================================

#include <Adafruit_NeoPixel.h>

#define LED_PIN   6     // Pin de datos (DIN) conectado al anillo
#define NUM_LEDS  16    // Cantidad de LEDs del anillo

Adafruit_NeoPixel ring(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  Serial.begin(115200);
  ring.begin();
  ring.setBrightness(50);  // brillo (0-255), bajarlo si calienta mucho
  ring.show();             // apaga todos los LEDs al inicio
  Serial.println("Anillo inicializado. Iniciando prueba...");
}

void loop() {
  // 1) Prueba de colores: todo el anillo en ROJO, VERDE, AZUL y BLANCO
  llenarTodo(255, 182, 193);   // rosa pastel
  delay(800);
  llenarTodo(255, 20, 147);   // Rosa neón
  delay(800);
  llenarTodo(0, 255, 255);   // cian
  delay(800);
  llenarTodo(255, 0, 255); // Magenta
  delay(800);
  apagarTodo();
  delay(500);

  // 2) Prueba LED por LED (verifica que los 16 funcionen)
  for (int i = 0; i < NUM_LEDS; i++) {
    apagarTodo();
    ring.setPixelColor(i, ring.Color(0, 150, 255)); // celeste
    ring.show();
    delay(100);
  }
  apagarTodo();
  delay(500);

  // 3) Prueba de "llenado" progresivo (como en el proyecto final)
  for (int i = 0; i <= NUM_LEDS; i++) {
    actualizarAnillo(i);
    delay(150);
  }
  delay(500);
  apagarTodo();
  delay(1000);
}

// ---------- Funciones auxiliares ----------

void llenarTodo(int r, int g, int b) {
  for (int i = 0; i < NUM_LEDS; i++) {
    ring.setPixelColor(i, ring.Color(r, g, b));
  }
  ring.show();
}

void apagarTodo() {
  llenarTodo(0, 0, 0);
}

// Misma lógica de colores que el proyecto final, para probarla
void actualizarAnillo(int conteo) {
  conteo = constrain(conteo, 0, NUM_LEDS);

  for (int i = 0; i < NUM_LEDS; i++) {
    if (i < conteo) {
      if (conteo <= 5) {
        ring.setPixelColor(i, ring.Color(0, 255, 0));     // verde
      } else if (conteo <= 10) {
        ring.setPixelColor(i, ring.Color(255, 255, 0));   // amarillo
      } else {
        ring.setPixelColor(i, ring.Color(255, 0, 0));     // rojo
      }
    } else {
      ring.setPixelColor(i, ring.Color(0, 0, 0));
    }
  }
  ring.show();
}
