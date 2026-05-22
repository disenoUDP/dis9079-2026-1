# solemne-02

## Integrantes

- Sofía Cartes Aravena / <https://github.com/sofiacartes>
- Monserrat Paredes / <https://github.com/Monserrat-Paredes>
- Valentina Ruz Pizarro / <https://github.com/vxlentiinaa>

## Descripción textual del proyecto

Este proyecto consiste en un sistema de interacciones inalámbricas entre una Raspberry Pi Pico 2 W y un Arduino UNO R4 WIFI, utilizando la plataforma Adafruit IO como intermediario para la visualización y envío de datos en tiempo real.

El funcionamiento comienza con un potenciómetro conectado a la Raspberry Pi Pico 2 W, el cual envía datos del ángulo al girar la perilla. La Raspberry Pi lee estos valores analógicos y los envía al feed llamado “moluscos” dentro de Adafruit IO utilizando conexión WiFi.

Posteriormente, el Arduino recibe los datos publicados en el feed y los interpreta para controlar un servomotor SG90. Dependiendo del valor enviado por el potenciómetro, el servo cambia su ángulo de rotación. Cuando el servomotor alcanza un ángulo específico (previamente programado), se activa automáticamente una luz LED amarilla, generando una respuesta visual al movimiento.

## Materiales usados

|Componente|Cantidad|Precio|Link|
|---|---|---|---|
|Raspberry Pi Pico 2 W|1|$14.990|<https://raspberrypi.cl/products/raspberry-pi-pico-2-w-con-headers>|
|Arduino UNO R4 WIFI|1|$38.990|<https://mcielectronics.cl/shop/product/arduino-uno-r4-minima>|
|Servomotor SG90|1|$3.290|<https://arduino.cl/producto/micro-servo-motor-sg90-9g/>|
|Potenciómetro B500k|1|$500|<https://afel.cl/products/potenciometro-10k-ohm>|
|LED amarillo 10mm|1|$500|<https://www.mechatronicstore.cl/led-10mm-variedad-de-colores/>|
|Resistencias 200 ohms|1|$413|<https://altronics.cl/pack-10-resistencias-220ohm-025watt-1porciento>|
|Protoboard|1|$1.500|<https://afel.cl/products/mini-protoboard-400-puntos>|
|cables|4|$1.000|<https://afel.cl/products/pack-20-cables-de-conexion-macho-macho>|

## Sensor usado

`Potenciómetro B500K`

El sensor utilizado en este proyecto es un potenciómetro de B500K. Este componente funciona como una resistencia variable que permite modificar manualmente el voltaje entregado a la Raspberry Pi Pico 2 W. En este caso, modificaría el ángulo del servomotor.

La Raspberry Pi interpreta este cambio mediante una entrada analógica ADC, convirtiendo los valores físicos del giro del potenciómetro en datos digitales. Estos datos son enviados posteriormente al feed “moluscos” en Adafruit IO para ser utilizados por el Arduino.

El potenciómetro actúa como interfaz de control principal del sistema, permitiendo manejar el comportamiento del servomotor en tiempo real.

## Actuador usado

`Servomotor SG90`

El actuador principal del proyecto es un servomotor SG90. Este tipo de motor permite controlar con precisión el ángulo de movimiento mediante señales PWM enviadas desde el Arduino.

El servo recibe los datos provenientes del feed “moluscos” y ajusta su posición según los valores entregados por el potenciómetro. Cuando alcanza un ángulo determinado, el sistema activa un LED amarillo como indicador visual del estado alcanzado.

## Código usado para enviar

## Código usado para recibir

## Imágenes del proyecto

## Animaciones del proyecto

<img src="./imagenes/imagenFinal1.gif" alt="final" width="300">
<img src="./imagenes/imagenFinal2.gif" alt="final" width="300">
<img src="./imagenes/imagenFinal3.gif" alt="final" width="300">

## Bibliografía
