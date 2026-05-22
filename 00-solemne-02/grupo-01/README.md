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

## Animaciones del proyecto

## Bibliografía
