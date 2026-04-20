# sesion-02

## Solemne 1 en equipos

Integrantes: Magda - Jesu - Carla

## Introducción y primer acercamiento a Arduino Uno R4 Wifi

Arduino se referirá a 3 cosas distintas:

1. Placa de desarrollo
2. Software Arduino IDE
3. Dialecto de lenguaje C++

-> Estructura básica de Código Arduino
   void setup() {

   }

   void loop() {

   }

## Ejemplos :)

```cpp
// ejemplo01
// imprime la sigla del curso en la pantalla led
// de la Arduino Uno R4 WiFi
// basado en
// https://docs.arduino.cc/tutorials/uno-r4-wifi/led-matrix/#scrolling-text-example
// marzo 2026
// por montoyamoraga para disenoUDP

// incluir bibliotecas
#include <ArduinoGraphics.h>
#include "Arduino_LED_Matrix.h"

// declarar instancia de ArduinoLEDMatrix
// con nombre pantalla
ArduinoLEDMatrix pantalla;

void setup() {

  // iniciar puerto serial
  Serial.begin(115200);

  // inicializar pantalla
  pantalla.begin();

}

void loop() {

  // definir nuevo dibujo
  pantalla.beginDraw();

  // definir trazo
  pantalla.stroke(0xFFFFFFFF);

  // definir velocidad de deslizamiento
  pantalla.textScrollSpeed(100);

  // definir texto
  const char texto[] = "    diseno udp dis9704 interacciones inalambricas    ";
  
  // definir tipo
  pantalla.textFont(Font_5x7);

  // definir inicio del texto
  pantalla.beginText(0, 1, 0xFFFFFF);

  // imprimir el texto
  pantalla.println(texto);

  // deslizar hacia la izquierda
  pantalla.endText(SCROLL_LEFT);

  // fin del dibujo
  pantalla.endDraw();
}
```

## [Mosquitto](https://mosquitto.org/)

   mosquitto es un broker de MQTT, que se encarga de recibir y distribuir mensajes entre clientes MQTTT

## -  Haciendo pruebas con Arduinitossss 😲

lunes 16 marzo 2026
