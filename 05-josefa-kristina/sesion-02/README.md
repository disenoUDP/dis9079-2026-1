# sesion-02

## Arduino uno R3 2011

Conector usb-b

## Arduino R4 MINIMA

Chip renesas (mejor que el R3)
conector usb-cc más pequeño

## Arduino uno R4 WIFI

Chip más potente con WIFI

---

## Lenguaje Arduino

1. Placa de desarrollo
2. Software
3. El lenguaje de programación

Arduino es como processing pero hardware

Set up: Corre una vez, configurar entradas y salidas

Loop: Corre infinitamente

Serial.Begin(9600): Iniciar puerto serial

Serial.printIn(x);
delay(1000): espera 1 segundo

# Imprimir siglas del curso en la pantalla

`#include` incluir x p.e bibliotecas

`ArduinoLEDMatrix` pantalla o cualquier palabra;

`pantalla.begin()`;  inicializar pantalla

`pantalla.beginDraw`: definir dibujo

`pantalla.stroke(0xFFFFFFFF)`: Definir trazo

`pantalla.textScrollSpeed(100)`; Definir velocidad deslizamiento

`const char texto[]` = "    diseno udp dis9704 interacciones inalambricas    ";  Definir texto

`pantalla.textFont(Font_5x7)`; Definir tipo

`pantalla.beginText(0, 1, 0xFFFFFF)`; Definir el inicio del texto

`pantalla.println(texto)`; Imprimir el texto

`pantalla.endText(SCROLL_LEFT)`; Deslizar hacia la izq

`pantalla.endDraw()`; Fin del dibujo
}

# Mosquitto (open source)

MQTT broker

lunes 16 marzo 2026
