# solemne-02

## Integrantes

- Josefa Araya / josefa-kristina
- Débora Soto / DebSkar
- Cristóbal Vergara / cristobalvergarasilva

## Descripción textual del proyecto
Para la segunda solemne, el encargo consistió en usar microcontroladores, para realizar una comunicación inalámbrica a través de Adafruit IO, usando sensores y actuadores.

Para la realización de nuestro proyecto, usamos un potenciómetro conectado a una Raspberry Pi Pico 2W, que envía valores a un motor Servo, el que va conectado a un Arduino r4 wifi. El motor Servo recibe los valores y los transforma en ángulos de (agregar ángulos) además utilizamos un botón pulsador de 4 pines que permite dejar de enviar datos para no sobrecargar la nube.
Toda esta interacción se realiza mediante un feed de  Adafruit IO.

El primer paso fue eliminar el firmware de la Raspberry, este se tiene que remplazar por el code.py de CircuitPython10.2.0, luego practicamos con un código que nos dio Aarón para conectarla a Adafruit Io, es el mismo código que después usamos como base para comenzar a modificar el nuestro.

Cuando tratamos de modificar el código en Visual Studio Code, no nos funcionaba el código, después de un rato nos dimos cuenta de que lo estábamos corriendo en el computador y no en la Raspberry. Solucionado eso guardamos el código en su carpeta interna y lo comenzamos a correr utilizando Putty.

En Putty tuvimos el siguiente problema: “Error de módulo (no module named...”.
Estuvimos un buen rato estancados en eso hasta que le preguntamos a Claude y nos dio lo siguiente para escribir en Putty:



import sys
print(sys.version)

import wifi
print("wifi OK")

import adafruit_minimqtt.adafruit_minimqtt
print("mqtt OK")

import adafruit_io.adafruit_io
print("adafruit_io OK")

Ahí se soluciona el problema y comenzó a correr exitosamente.

En la clase siguiente, le comentamos a Aarón lo que habíamos hecho y  nos dijo que cambiaríamos la temática de nuestro proyecto, puesto que queríamos hacer una guillotina que le cortara la cabeza a Kast y nos comentó que él no merecía nuestra atención.

Se nos sugirió hacer algo más interesante con el movimiento del motor servo, el cual teníamos con un movimiento estándar entre los 0 y 180 grados, este movimiento lo cambiamos con un código para que se moviera entre los 45 y 135 grados.

Con este código solo se publicaba en Adafruit cuando el ángulo cambiaba más de 2° para no superar el límite de los 30 mensajes por minuto, aún con esto logramos sobrecargar nuestro feed por lo que modificamos el código para que enviara los datos cada 5 segundos.

Línea modificada:

´´if abs(angle - last_angle) = 2 and (now - last_send_time) = 5´



## Materiales usados
| Componente | Cantidad | Valor Unidad | Link |
| --- | --- | --- | --- |
| Raspberry Pi Pico 2W | 1 | $14.990 | <https://raspberrypi.cl/products/raspberry-pi-pico-2-w-con-headers>|
| AArduino UNO R4 WiFi | 1 | $$38,990 |<https://arduino.cl/producto/arduino-uno-r4-wifi/?srsltid=AfmBOoqwfINu-FJZk1WDnGEYJtedpDJvTJDexifC6sv4sWK-dkDemYzB>|
| Micro Servo Motor SG90 9g | 1 | $3.290 | <https://mcielectronics.cl/shop/product/micro-servo-motor-sg90-9g-25775/?gad_source=1&gad_campaignid=21444224314&gbraid=0AAAAADijL1VxzGcSMKlmDhlqY2cOAjRxf&gclid=Cj0KCQjw_b_QBhCSARIsAP6hR4elepSjJKN4jPfIKgfN_K-b6ohCxZjZjnqn1VFlP0gA9_3-oqqY5n0aAmWzEALw_wcB> |
| Cables Dupont | 1 | $65 | <https://mcielectronics.cl/shop/product/cable-dupont-macho-macho-20cm-pack-40-unidades/> |
| Potenciometro 20K Ohm | 1 | $500 | <https://afel.cl/products/potenciometro-20k-ohm?_pos=3&_sid=bc780bb62&_ss=r/> |
| Boton pulsador switch de 4 pines push button 6x6x4.3mm | 1 | $290 | <https://www.mechatronicstore.cl/push-button-4-pines/> |

## Sensor usado
Potenciometro 20K Ohm 

-Resistencia que puede variar su valor de forma manual, está compuesta de tres puntos de conexión de las cuales dos son fijos y están conectados a un elemento resistivo, y el otro está conectado a una pieza que se mueve lado a lado. Puntualmente la que utilizamos nosotros va desde 0 Ohm a 20K Ohm

Botón pulsador

- 

## Actuador usado
Micro Servo Motor SG90 9g 

Es un actuador controlable que recibe señales especificando los angulos en los que tiene que girar, puntualmente el nuestro va de 0° a 180°.

## Código usado para enviar

## Código usado para recibir

## Imágenes del proyecto

## Animaciones del proyecto

## Bibliografía
https://eepower.com/resistor-guide/resistor-types/potentiometer/#
https://www.youtube.com/watch?v=sWbSeJmUFfw
