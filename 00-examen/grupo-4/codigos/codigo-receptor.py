```cpp
// Librerías para la conexión WiFi del Arduino UNO R4 WiFi
#include <WiFiS3.h>

// Librería para conectarse y comunicarse con Adafruit IO
#include "AdafruitIO_WiFi.h"

// Archivo que contiene las credenciales WiFi y de Adafruit IO
#include "config.h"

// Librería para controlar la pantalla TFT GC9A01
#include <Arduino_GFX_Library.h>

// Definición de colores en formato RGB565
#define BLACK 0x0000
#define WHITE 0xFFFF
#define RED   0x001F
#define GREEN 0x07E0

// Crea el objeto de conexión a Adafruit IO
AdafruitIO_WiFi io(IO_USERNAME, IO_KEY, WIFI_SSID, WIFI_PASS);

// Crea un feed llamado "pulsaciones"
AdafruitIO_Feed *bpmFeed = io.feed("pulsaciones");

// Definición de los pines de la pantalla TFT
#define TFT_CS 10   // Chip Select
#define TFT_DC 9    // Data/Command
#define TFT_RST 8   // Reset

// Configura el bus SPI por hardware para la pantalla
Arduino_DataBus *bus = new Arduino_HWSPI(TFT_DC, TFT_CS);

// Crea el objeto de la pantalla GC9A01
Arduino_GFX *tft = new Arduino_GC9A01(bus, TFT_RST, 0, false);

// Variable que almacena el valor actual del pulso
int bpm = 75;

void setup() {

  // Inicializa la comunicación serial
  Serial.begin(115200);

  // Espera para estabilizar el sistema
  delay(2000);

  // Inicializa la pantalla TFT
  tft->begin();

  // Limpia la pantalla con color negro
  tft->fillScreen(BLACK);

  // Configura el color y tamaño del texto
  tft->setTextColor(WHITE);
  tft->setTextSize(2);

  // Muestra un mensaje de conexión
  tft->setCursor(35, 105);
  tft->print("Conectando...");

  // Inicia la conexión con Adafruit IO
  io.connect();

  // Espera hasta que la conexión sea exitosa
  while (io.status() < AIO_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.println("\nAdafruit conectado");

  // Asocia la función recibirBPM() al feed "pulsaciones"
  // Cada vez que llegue un nuevo dato, esta función se ejecutará automáticamente
  bpmFeed->onMessage(recibirBPM);

  // Dibuja la interfaz inicial de la pantalla
  dibujarPantalla();
}

void loop() {

  // Mantiene activa la conexión con Adafruit IO
  // y revisa si hay nuevos datos disponibles
  io.run();
}

// Función que se ejecuta automáticamente cuando llega un nuevo BPM
void recibirBPM(AdafruitIO_Data *data) {

  // Convierte el dato recibido a entero
  bpm = data->toInt();

  // Verifica que el BPM esté dentro del rango esperado
  if (bpm < 55 || bpm > 130) {
    bpm = 75;
  }

  // Muestra el BPM recibido en el monitor serial
  Serial.print("BPM recibido: ");
  Serial.println(bpm);

  // Actualiza la información mostrada en la pantalla
  dibujarPantalla();
}

// Función encargada de dibujar toda la interfaz gráfica
void dibujarPantalla() {

  // Limpia la pantalla
  tft->fillScreen(BLACK);

  // Configura el texto principal
  tft->setTextColor(WHITE);
  tft->setTextSize(3);

  // Muestra el valor del BPM
  tft->setCursor(55, 30);
  tft->print(bpm);
  tft->print(" BPM");

  // Configura el texto secundario
  tft->setTextSize(1);

  // Muestra una descripción debajo del BPM
  tft->setCursor(78, 65);
  tft->print("Pulso en nube");

  // Dibuja un corazón utilizando dos círculos y un triángulo

  // Parte superior izquierda del corazón
  tft->fillCircle(112, 115, 18, RED);

  // Parte superior derecha del corazón
  tft->fillCircle(128, 115, 18, RED);

  // Parte inferior del corazón
  tft->fillTriangle(88, 125, 152, 125, 120, 170, RED);

  // Dibuja una línea que simula la señal de un electrocardiograma

  tft->drawLine(20, 200, 60, 200, GREEN);
  tft->drawLine(60, 200, 75, 175, GREEN);
  tft->drawLine(75, 175, 90, 220, GREEN);
  tft->drawLine(90, 220, 110, 160, GREEN);
  tft->drawLine(110, 160, 130, 200, GREEN);
  tft->drawLine(130, 200, 220, 200, GREEN);
}
```
> Con ayuda de CHATGPT realizamos los comentarios del código.
