# solemne-02

## Integrantes

- Benjamín Álvarez - [benjaminalvarez21](https://github.com/benjaminalvarez21)
- Anays Cornejo - [Anaysval](https://github.com/Anaysval)
- Agustina Aceituno - 
- Antonia Fuentealba - 
  
## Descripción textual del proyecto

Como encargo para la segunda solemne del curso, se nos pidió nuevamente desarrollar un sistema de comunicación inalámbrica. Para esto, trabajamos con dos microcontroladores distintos, programados mediante código: un Arduino Uno R4 WiFi y una Raspberry Pi Pico 2 W.

El proyecto consiste en un sistema de detección de movimiento que envía información de forma remota. Para esto, se utilizó un sensor PIR que se activa mediante un botón. Una vez encendido, el sensor detecta movimiento y transmite esta información a través de la Raspberry Pi Pico 2 W hacia la plataforma Adafruit IO. 

Luego, estos datos son recibidos por el Arduino Uno R4 WiFi, el cual interpreta la señal y genera una respuesta visual en una pantalla OLED, que también se activa mediante un botón. En esta pantalla se muestran animaciones en pixel art, compuestas por tres frames por personaje, que, al reproducirse de manera secuencial, simulan movimiento, funcionando de forma similar a un GIF. Las animaciones muestran a una persona y un alien caminando, mientras que el fantasma se desplaza flotando. 

La lógica del sistema permite que, al detectar movimiento en el sensor, se active toda la cadena de comunicación hasta transformar ese evento en una representación visual. De esta forma, se traduce una acción física en una respuesta digital interactiva.

El objetivo principal es evidenciar la integración entre sensores, actuadores y comunicación inalámbrica, generando una experiencia donde el usuario puede interactuar con el sistema y observar en tiempo real cómo la información se transmite y se convierte en una visualización dinámica.

## Materiales usados

| Componente | Cantidad | Valor Unitario | Link |
|------------|----------|-----------------|------|
| Raspberry Pi Pico 2 W | 1 | $14.990 | <https://raspberrypi.cl/products/raspberry-pi-pico-2-w-con-headers> |
| Arduino UNO R4 WiFi | 1 | $38.990 | <https://arduino.cl/producto/arduino-uno-r4-wifi/> |
| Protoboard 400 pines | 2 | $2.100 | <https://prodelab.cl/productos/didacticos/nivel-superior-y-ensenanza-media/robotica-y-programacion/accesorios-robotica-y-programacion/protoboard-breadboard-400-pines/> |
| Cables Dupont Macho-Macho (40 unid.) | 1 | $2.590 | <https://mcielectronics.cl/shop/product/cable-dupont-macho-macho-20cm-pack-40-unidades/> |
| Cables Dupont Macho-Hembra (40 unid.) | 1 | $2.990 | <https://mcielectronics.cl/shop/product/cable-dupont-macho-hembra-20cm-pack-40-unidades-2/> |
| Sensor PIR HC-SR501 | 1 | $2.323 | <https://altronics.cl/modulo-sensor-hc-sr501?search=sensor%20pir> |
| Pantalla OLED 128x64 I2C | 1 | $5.490 | <https://mcielectronics.cl/shop/product/display-oled-de-128-x-64-pixeles-controlable-por-i2c-29546/?srsltid=AfmBOoonygPNjPY_CAA3XBDYsyRPx98Fq9mW3L_sUcpU92KsMYcuqRFvqeo> |
| Cable USB A a USB-C | 1 | $10.990 | <https://www.falabella.com/falabella-cl/product/17549587/>|
| Cable USB A a Micro USB | 1 | $4.990 | <https://mcielectronics.cl/shop/product/cable-usb-a-micro-usb-negro/?srsltid=AfmBOor5DUGYyFpc1Hoo8KOhWzD-8jsF487IqqcuJiWnDG3BJi_rRwnQ> |



## Sensor usado

Se utilizó un sensor PIR junto con un push button. El funcionamiento del sistema fue el siguiente: al presionar el botón, se activaba el sensor PIR, el cual detectaba movimiento mediante cambios en la radiación infrarroja (calor corporal). Cuando detecta movimiento, el sensor envía una señal al sistema Adafruit. Para detener el envío de datos, se presiona nuevamente el botón, desactivando el sensor.

El sensor PIR funciona detectando variaciones de temperatura en su entorno, generalmente causadas por personas o animales en movimiento. Este tipo de sensor tiene un rango aproximado de detección entre 3 y 7 metros, y su salida es digital (HIGH cuando detecta movimiento y LOW cuando no). Además, suele incluir ajustes de sensibilidad y tiempo de activación.
 
## Actuador usado

Se utilizó como actuador una pantalla OLED junto con un push button. El funcionamiento consiste en que el botón permite activar el envío de información hacia la pantalla. Al presionar el botón, la pantalla OLED recibe y muestra los datos que previamente fueron captados por el sistema Adafruit. De esta manera, el botón actúa como un controlador de visualización, permitiendo decidir cuándo mostrar la información en la pantalla. Mientras el botón no está activado, la pantalla puede permanecer apagada o sin actualizar datos.

La pantalla OLED funciona mediante comunicación digital (generalmente protocolo I2C), lo que permite transmitir datos desde el microcontrolador hacia la pantalla usando pocos pines. Este tipo de pantalla se caracteriza por su bajo consumo energético, buen contraste y capacidad de mostrar texto o gráficos de forma clara. Por otro lado, el push button es un interruptor momentáneo que cierra el circuito solo mientras se presiona, enviando una señal digital al sistema.

## Código usado para enviar

## Código usado para recibir

## Imágenes del proyecto

## Animaciones del proyecto

## Bibliografía
