#include "config.h"

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// -------------------------
// Pantalla OLED
// -------------------------
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// -------------------------
// Feed Adafruit IO
// -------------------------
AdafruitIO_Feed *botonFeed = io.feed("prueba05");

// -------------------------
// Mostrar texto en pantalla
// -------------------------
void mostrarPantalla(String linea1, String linea2) {
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);

  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println(linea1);

 display.setTextSize(1);
 display.setCursor(0, 25);
 display.println(linea2);  

  display.display();
}

// -------------------------
// Cuando llega mensaje
// -------------------------
void handleMessage(AdafruitIO_Data *data) {
  String mensaje = data->toString();

  Serial.print("Mensaje recibido: ");
  Serial.println(mensaje);

  mostrarPantalla("Mensaje recibido:", mensaje);
}

// -------------------------
// Setup
// -------------------------
void setup() {
  Serial.begin(115200);
  delay(3000);

  Serial.println("Iniciando...");

  // Iniciar pantalla
  Wire.begin();

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("No se encontro pantalla OLED");
    while (true);
  }

  mostrarPantalla("Iniciando...", "");

  // Asociar feed a funcion
  botonFeed->onMessage(handleMessage);

  Serial.println("Conectando a Adafruit IO...");
  mostrarPantalla("Conectando a", "Adafruit");

  io.connect();

  while (io.status() < AIO_CONNECTED) {
    io.run();

    Serial.print("Estado: ");
    Serial.println(io.statusText());

    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 0);
    display.println("Conectando...");
    display.println(io.statusText());
    display.display();

    delay(1000);
  }

  Serial.println("Conectado a Adafruit IO");

  mostrarPantalla("Conectado!", "OK");

  delay(1500);

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("Esperando mensaje");
  display.println("del boton...");
  display.display();

  // Trae el ultimo mensaje enviado al feed
  botonFeed->get();
}

// -------------------------
// Loop
// -------------------------
void loop() {
  io.run();
}