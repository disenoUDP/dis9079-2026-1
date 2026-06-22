
```cpp
#include <WiFiS3.h>              // Librería para la conexión WiFi del Arduino UNO R4 WiFi
#include "AdafruitIO_WiFi.h"    // Librería para comunicarse con Adafruit IO
#include "config.h"             // Archivo donde se guardan las credenciales WiFi y Adafruit

// Crea el objeto de conexión a Adafruit IO usando las credenciales definidas en config.h
AdafruitIO_WiFi io(IO_USERNAME, IO_KEY, WIFI_SSID, WIFI_PASS);

// Crea un feed llamado "pulsaciones" para enviar los BPM a Adafruit IO
AdafruitIO_Feed *bpmFeed = io.feed("pulsaciones");

// Pin analógico donde está conectado el sensor ECG AD8232
#define ECG_PIN A0

// Variables para aplicar un filtro simple a la señal ECG
float ecgFiltrado = 0;   // Valor filtrado actual
float anteriorECG = 0;   // Valor filtrado anterior

// Variables para controlar el tiempo entre latidos y el envío de datos
unsigned long ultimoLatido = 0;
unsigned long ultimoEnvio = 0;

// Bandera para evitar detectar varias veces el mismo latido
bool detectando = false;

// Variables para el cálculo de BPM
float bpm = 75;                // Valor temporal de BPM
float ultimoBPMValido = 75;   // Último BPM válido calculado

// Umbral de detección del pico R del ECG
// Ajustado según la amplitud observada en la señal
int umbral = 233;

void setup() {

  // Inicializa la comunicación serial
  Serial.begin(115200);

  // Espera 2 segundos para estabilizar el sistema
  delay(2000);

  Serial.println("Iniciando emisor ECG");
  Serial.println("Conectando Adafruit...");

  // Inicia la conexión con Adafruit IO
  io.connect();

  // Espera hasta que la conexión sea exitosa
  while (io.status() < AIO_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.println("\nAdafruit conectado");
}

void loop() {

  // Mantiene activa la conexión con Adafruit IO
  io.run();

  // Lee el valor analógico proveniente del sensor ECG
  int lectura = analogRead(ECG_PIN);

  // Aplica un filtro paso bajo para reducir el ruido de la señal
  ecgFiltrado = 0.75 * anteriorECG + 0.25 * lectura;

  // Guarda el valor filtrado para la siguiente iteración
  anteriorECG = ecgFiltrado;

  // Muestra la señal filtrada y el BPM actual en el monitor serial
  Serial.print("ECG: ");
  Serial.print(ecgFiltrado);
  Serial.print(" | BPM: ");
  Serial.println(ultimoBPMValido);

  // Obtiene el tiempo actual desde que el Arduino se encendió
  unsigned long ahora = millis();

  // Detecta un nuevo latido cuando la señal supera el umbral
  if (ecgFiltrado > umbral && !detectando) {

    // Calcula el tiempo transcurrido desde el último latido
    unsigned long intervalo = ahora - ultimoLatido;

    // Filtra intervalos válidos (equivalentes a 50–133 BPM aprox.)
    if (intervalo > 450 && intervalo < 1200) {

      // Convierte el intervalo entre latidos a BPM
      float bpmDetectado = 60000.0 / intervalo;

      // Acepta únicamente valores fisiológicamente válidos
      if (bpmDetectado > 55 && bpmDetectado < 130) {

        bpm = bpmDetectado;

        // Suaviza el BPM mediante un promedio ponderado
        ultimoBPMValido = (0.7 * ultimoBPMValido) + (0.3 * bpm);

        Serial.print("BPM valido: ");
        Serial.println(ultimoBPMValido);

      } else {

        // Descarta valores anómalos
        Serial.print("BPM descartado: ");
        Serial.println(bpmDetectado);
      }
    }

    // Guarda el instante del último latido detectado
    ultimoLatido = ahora;

    // Activa la bandera para evitar detecciones múltiples
    detectando = true;
  }

  // Reinicia la detección cuando la señal baja del umbral
  if (ecgFiltrado < umbral - 2) {
    detectando = false;
  }

  // Envía los datos a Adafruit cada 5 segundos
  if (ahora - ultimoEnvio > 5000) {

    ultimoEnvio = ahora;

    // Convierte el BPM a entero antes de enviarlo
    int bpmEnviar = (int)ultimoBPMValido;

    // Verifica que el valor esté dentro del rango esperado
    if (bpmEnviar < 55 || bpmEnviar > 130) {
      bpmEnviar = 75;
    }

    // Envía el dato al feed "pulsaciones"
    bpmFeed->save(bpmEnviar);

    Serial.print("ENVIADO A ADAFRUIT: ");
    Serial.println(bpmEnviar);
  }

  // Pequeña pausa para estabilizar las lecturas
  delay(10);
}
```

> Con ayuda de CHATGPT realizamos los comentarios del código.
