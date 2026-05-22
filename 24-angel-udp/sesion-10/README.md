# sesion-10

lunes 18 mayo 2026

**solemne 2**

Avanzamos en la solemne

Mientras unos configurábamos el código para hacer que la señal se mandara al servomotor, otros anotábamos los componentes con la descripción del proyecto para ir avanzando a la par con la entrega completa de la solemne.

Durante el trayecto de la clase hicimos las conexiones y probábamos el código, grabando y tomando fotos del proceso para que así pudiéramos tener lista una base para terminar el proyecto por ese camino.

Luego anotamos todo en la carpeta "00-solemne-02, grupo-01", en donde describimos mejor el proyecto, pero pondré la descripción textual:

## Descripción textual del proyecto

Nuestro proyecto consiste en enviar información entre 2 microcontroladores a través de WiFi, estando separados físicamente.

Para esto usamos una Raspberry Pi Pico 2 W como la placa emisora y un Arduino Uno R4 WiFi como placa receptora. La Raspberry lee los valores de un potenciómetro conectado mediante una protoboard y sube esa información a la nube utilizando Adafruit IO. Por otro lado, el Arduino lee el feed de datos creado en la nube y según el valor que reciba, mueve un servomotor en distintos ángulos.

Para poder controlar el envío de información y no saturar la nube, cuenta con un botón pulsador conectado a la Raspberry, permitiendo que solo se envíen los datos pulsando brevemente el botón. Arduino lo recibe y mueve el servomotor al último dato enviado.

A la Raspberry le sumamos una pantalla OLED de 128x64 px para poder ver los datos que vamos enviando en tiempo real.
