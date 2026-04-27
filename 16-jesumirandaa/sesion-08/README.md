# sesion-08

lunes 27 abril 2026

## Hoy incorporamos un nuevo lenguaje: Phyton
Durante la clase comenzamos a trabajar con Python aplicado a hardware, lo que marca una diferencia con el uso anterior de Arduino.

- Monty Phyton -> es un grupo de comedia británico famoso por su humor absurdo, que inspiró el nombre del lenguaje de programación Python
- Circuit Phyton -> permite utilizar Python en dispositivos electrónicos
- Descargamos Circuit Phyton 10.2.0

Qué es Circuit Phyton 10.2.0? 
Es una versión de Python hecha para microcontroladores (como placas más avanzadas que Arduino, por ejemplo de Adafruit)
Permite:
- programar sensores
- controlar LEDs, pantallas, botones
- desarrollar proyectos de electrónica de forma más simple
En términos simples, es como usar Python, pero aplicado directamente al hardware.

Removimos la información del disco de la Raspberry Pi y luego se le instaló CircuitPython 10.2.0 para poder trabajar con este nuevo entorno.

Además, descargamos el Bundle for Version 10.x desde las librerías de Adafruit, el cual incluye las librerías necesarias para el uso de sensores y componentes electrónicos en CircuitPython.


Este código permite leer los valores de un potenciómetro y enviarlos a una plataforma en línea mediante conexión WiFi.

Primero se establece la conexión a internet, luego se configura el protocolo MQTT para comunicarse con Adafruit IO. Después, se lee constantemente el valor del sensor y se envía cada 5 segundos al feed correspondiente.

Esto se relaciona directamente con lo trabajado anteriormente en clase, donde se envían datos desde un sensor hacia una plataforma para su visualización.



nos vemos a la vuelta del receso

