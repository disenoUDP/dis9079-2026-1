// ============================================================
// EMISOR - Lee potenciómetro y envía valor de volumen a Adafruit IO
// Arduino R4 WiFi
// ============================================================

#include "config.h"   // Credenciales WiFi y Adafruit IO

// --- CONFIGURACIÓN DEL POTENCIÓMETRO ---
// Conexión:
//   Pin izquierdo  → GND
//   Pin central    → A0  (señal analógica)
//   Pin derecho    → 5V
const int PIN_POTENCIOMETRO = A0;

// --- FEED DE ADAFRUIT IO ---
// Mismo nombre exacto que usa el receptor
AdafruitIO_Feed *feedVolumen = io.feed("paredesvania-volumen");

// --- VARIABLE GLOBAL ---
// Guarda el último valor enviado para no repetir envíos innecesarios
int ultimoVolumen = -1;

// ============================================================
void setup() {

  // Iniciar comunicación serial a 115200 baud
  Serial.begin(115200);

  // Esperar a que el Monitor Serial esté listo
  while (!Serial);

  Serial.print("Conectando a Adafruit IO...");

  // Conectar usando las credenciales del config.h
  io.connect();

  // Esperar hasta que la conexión sea exitosa
  while (io.status() < AIO_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  // Confirmar conexión
  Serial.println();
  Serial.println(io.statusText());
  Serial.println("Listo para enviar volumen!");
}

// ============================================================
void loop() {

  // Mantener conexión activa con Adafruit IO
  io.run();

  // --- LEER EL POTENCIÓMETRO ---
  // analogRead devuelve 0–1023 según la posición del potenciómetro
  int lecturaRaw = analogRead(PIN_POTENCIOMETRO);

  // Convertir 0–1023 a 0–100 (porcentaje de volumen)
  int volumen = map(lecturaRaw, 0, 1023, 0, 100);

  // Mostrar en Monitor Serial para verificar
  Serial.print("Lectura: ");
  Serial.print(lecturaRaw);
  Serial.print(" -> Volumen: ");
  Serial.print(volumen);
  Serial.println("%");

  // --- ENVIAR SOLO SI EL VALOR CAMBIÓ ---
  // Evita saturar el feed de Adafruit IO con valores repetidos
  if (volumen != ultimoVolumen) {

    Serial.print("Enviando: ");
    Serial.println(volumen);

    // Publicar el valor en el feed
    feedVolumen->save(volumen);

    // Actualizar el último valor enviado
    ultimoVolumen = volumen;
  }

  // Pausa de 200ms entre lecturas
  delay(200);
}