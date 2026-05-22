# solemne-02

## Integrantes

- Antonella Aguilar / antokiaraa
- Tomas Catrileo / tomascatri
- Angel Sabogal / angel-udp

## Descripción textual del proyecto

Nuestro proyecto consiste en enviar información entre 2 microcontroladores a través de WiFi, estando separados físicamente. 

Para esto usamos una Raspberry Pi Pico 2 W como la placa emisora y un Arduino Uno R4 WiFi como placa receptora. 
La Raspberry lee los valores de un potenciómetro conectado mediante una protoboard y sube esa información a la nube utilizando Adafruit IO. 
Por otro lado el Arduino lee el feed de datos creado en la nube y según el valor que reciba, mueve un servomotor en distintos ángulos. 

Para poder controlar el envío de información y no saturar la nube, cuenta con un botón pulsador conectado a la Raspberry permitiendo que solo se envíen los datos pulsando brevemente el botón, Arduino lo recibe y mueve el servomotor al último dato envíado.

A la Raspberry le sumamos una pantalla OLED de 128x64 px para poder ver los datos que vamos enviando en tiempo real.

## Materiales usados

- Protoboard
- Arduino Uno R4 WIFI
- Raspberry Pi Pico 2 W
- Cable USB a Micro-USB
- Cable USB a tipo C
- Cables dupont
- Potenciómetro 10K
- Pantalla OLED 128x84 px
- Botón pulsador
- Servomotor

## Sensor usado

Potenciómetro (10K): Resistencia variable que cambia su valor interno cuando giramos la perilla.

Lo utilizamos para captar la posición en la que queremos mover el servomotor, envía los  datos mediante la Raspberry hacia Adafruit IO.

## Actuador usado

Servomotor: Motor pequeño que puede moverse y quedarse fijo en un ángulo entre 0° y 180°.

Utilizado en el Arduino Uno para realizar un movimiento en un ángulo exacto dependiendo del valor recibido desde Adafruit IO.

Pantalla OLED 128x64 px: Pantalla pequeña que sirve para mostrar textos, números o gráficos simples programados desde el microcontrolador. 

Es el monitor del proyecto, utilizada para mostrar la información recibida del potenciómetro y el ángulo en el que moveremos el servo que se enviará a través de Adafruit IO, permitiendo saber en tiempo real los datos que vamos enviando a la nube. 

## Código usado para enviar

## Código usado para recibir

## Imágenes del proyecto

![proceso](./imagenes/proceso.jpeg)

## Animaciones del proyecto

![Proceso 1](./imagenes/ejemplo1.gif)

![Proceso 2](./imagenes/ejemplo2.gif)

![Proceso 3](./imagenes/ejemplo3.gif)

![Proceso 4](./imagenes/ejemplo4.gif)

![Proceso 5](./imagenes/ejemplo5.gif)

## Proceso y errores

En el proceso es importante tener cuidado en los pequeños detalles ya que si no se les da la importancia necesaria puede no funcionar el proyecto, como en nuestro caso que tuvimos un fallo al conectar mal los jumpers con los pines de la Raspberry Pi Pico 2 W y eso daba un error desconocido en la pantalla del código que, con la ayuda de la IA y fijándonos mejor dónde debía conectarse cada cable, pudimos solucionar esto en la parte de la protoboard que tiene las conexiones del sensor.

## Bibliografía

- Adafruit Learning System. (s.f.). Monochrome OLED breakouts. Adafruit Industries.
- Arduino Documentation. (s.f.). Analog input. Arduino.
- Interacciones inalámbricas. (2026). Código y ejemplos prácticos utilizados en clases. Material proporcionado por los profesores.
- PuTTY Official Website. (s.f.). PuTTY. PuTTY.org.
- Raspberry Pi Documentation. (s.f.). Pico series. Raspberry Pi Ltd.
- Raspberry Pi Projects. (s.f.). Physical computing. Raspberry Pi Foundation.
