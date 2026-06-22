# grupo-8

* AlegriaColoma
* antolavalle
* catasal

## Desarrollo examen

### ¿Qué hace nuestro semáforo?

Es un sistema que detecta cuántas personas entran/salen de la Sala Alpha (sala de computación pública de la universidad Diego Portales) mediante dos botones en un Arduino UNO R4 WiFi, y muestra la ocupación de la sala en un semáforo remoto conectado a una Raspberry Pi Pico 2 W, comunicados a través de Adafruit IO.

```
Sala Alpha                         ☁️ Adafruit IO          Patio central SS
─────────────────                   ──────────────         ──────────────────
Arduino R4 WiFi                                             Raspi Pico 2
+ 2 botones       ──publica──→    feed:pruebasemaforo  →   + semáforo RGB
                                  
```

Parámetros del semáforo 

- 0-5 personas → 🟢 Verde
- 6-10 personas → 🟡 Amarillo
- 11+ personas → 🔴 Rojo
  

### Materiales 

| materiales | costo | cantidad|
|------------|-------|---------|
|Modulo Luz Led de Semaforo ( (con pines GND, R, Y, G integrados)| 1.500 | 1       |
|Raspberry Pi Pico 2 W         | 14.990 | 1        |
|arduino UNO R4 wifi        | 38.990  | 1       |
|botones         | 100 c/u  | 2       |
|Protoboards     | 1.500c/u  | 2       |
|cables jumper (pack de 20 cables de conexión macho macho)  | 1.000  |    1  |


## Proceso 

Creamos un feed en Adafruit IO llamado ```pruebasemaforo```, posteriormente pasamos a el desarrollo de códigos en con ayuda de la IA.

#### Proceso Raspberry Pi Pico 2 w 

##### Pseudocódigo

```
INICIO
  conectarse a WiFi
  conectarse a Adafruit IO

  REPETIR SIEMPRE:
    leer valor del feed "pruebasemaforo" desde Adafruit IO

    SI valor es 0 a 5:
      encender LED VERDE
      apagar LED amarillo
      apagar LED rojo

    SI valor es 6 a 10:
      apagar LED verde
      encender LED AMARILLO
      apagar LED rojo

    SI valor es 11 o más:
      apagar LED verde
      apagar LED amarillo
      encender LED ROJO
FIN
```

Una vez obtenido el código procedimos a probarlo en la placa y surgieron un par de problemas en el proceso 

Como primer problema, la placa no se conectaba al WiFi. Se probó con distintos hotspots y ninguno dio resultados. Sin embargo, durante un momento creemos que sí logró conectarse a uno de ellos. No obstante, al volver a intentarlo con el teléfono de mi compañera, nuevamente no se conectaba.

Al revisar el monitor serial, cuya instalación nos ayudó a realizar una compañera, nos dimos cuenta de que el código que estábamos utilizando no estaba ejecutando ninguna función. Esto se debía a que el código inicial estaba escrito en MicroPython, mientras que la placa tenía instalado CircuitPython. Finalmente, se reescribió todo el código en CircuitPython.

Procedimos con la conexion del cableado y moódulo de semáforo: GP16→G, GP17→Y, GP18→R, GND→GND.

Segundo problema, la Pico recibía bien los valores de Adafruit IO, pero ningún LED encendía.

Se probó un código simple LED por LED, descartando errores de código. Se probó conectar un cable directo a 3.3V → tampoco prendía → se sospechó del GND y el cable de GND no estaba bien conectado. Al corregirlo, los 3 LEDs (verde, amarillo, rojo) parpadearon correctamente con un código de prueba simple.

#### Código de prueba de los LEDS 

```
import time
import board
import digitalio

led_verde = digitalio.DigitalInOut(board.GP16)
led_verde.direction = digitalio.Direction.OUTPUT

led_amarillo = digitalio.DigitalInOut(board.GP17)
led_amarillo.direction = digitalio.Direction.OUTPUT

led_rojo = digitalio.DigitalInOut(board.GP18)
led_rojo.direction = digitalio.Direction.OUTPUT

while True:
    print("Verde ON")
    led_verde.value = True
    led_amarillo.value = False
    led_rojo.value = False
    time.sleep(1)

    print("Amarillo ON")
    led_verde.value = False
    led_amarillo.value = True
    led_rojo.value = False
    time.sleep(1)

    print("Rojo ON")
    led_verde.value = False
    led_amarillo.value = False
    led_rojo.value = True
    time.sleep(1)
```

*foto del proyecto, especifico del semáforo*

<img width="1600" height="1544" alt="WhatsApp Image 2026-06-22 at 11 05 44" src="https://github.com/user-attachments/assets/6296b9c9-cc42-4daf-8ab4-8fdaf618cffd" />


https://youtube.com/shorts/gFcf4EqzTzc?si=k5rP9XQtdY6noI2l

#### Proceso Arduino UNO R4 WiFI


#### Pseudocódigo

```
INICIO
  contador = 0 o +
  conectarse a WiFi
  conectarse a Adafruit IO

  REPETIR SIEMPRE:
    SI se aprieta botón "entró":
      contador = contador + 1
      publicar contador en Adafruit IO

    SI se aprieta botón "salió":
      SI contador > 0:
        contador = contador - 1
      publicar contador en Adafruit IO
FIN
```


Una vez obtenido el código para ARDUINO realizamos la prueba para ver si es que el código tenía algún fallo


Primer problema, necesitábamos hacer que el Arduino se conectara al hotspot de un iPhone, pero no lo lograba. Por lo que averiguamos, una posible causa era que los iPhone comparten la conexión en 5 GHz, mientras que las placas se conectan en 2,4 GHz. Por ello, procedimos a activar la opción *"Maximizar compatibilidad"* en el teléfono.

Posteriormente realizamos la conexión de cableado y botones (resistencia a GND, botón a 5 V)

Segundo problema, el contador se actualiza si se conecta o desconecta el cable manualmente, pero no responde al presionar el botón físico. Al mover el Arduino, los valores fluctúan por sí solos (señal "flotante"), lo que indica que el circuito de pull-down no está cerrando correctamente hacia GND, aunque se revisó la disposición del circuito (A3 conectado a D2, B3 con una resistencia de 10 kΩ, C3 y E3 con las patitas del botón, y A8 conectado al riel positivo) y parecía estar correcta si embargo no era posible controlar el envio de datos, por lo que buscamos otras opciones para los botones y al buscar otras opciones nos quedamos esta opcion que no se necesita necesita resistencias.

|Componente | Pin del componente	| Conecta a |
|-----------|---------------------|-----------|
|Botón SUMA |	Pin 1	| Pin D2 del Arduino|
Botón SUMA |	Pin 2	| Riel GND de la protoboard|
Botón RESTA	|Pin 1	| Pin D3 del Arduino|
Botón RESTA	|Pin 2 |	Riel GND de la protoboard|
Protoboard|	Riel GND |	Pin GND del Arduino|


*foto del proyecto, especifico ARDUINO+BOTONES*
<img width="900" height="1600" alt="WhatsApp Image 2026-06-22 at 11 10 36 (1)" src="https://github.com/user-attachments/assets/60f0d5c3-d86c-46fb-8795-d79f75d66b1c" />
<img width="900" height="1600" alt="WhatsApp Image 2026-06-22 at 11 10 36" src="https://github.com/user-attachments/assets/b68a869c-b2e9-40c9-ac88-7e6a252eaa8d" />

*prueba en adafruit, sumando y restando personas*
<img width="1912" height="855" alt="Captura de pantalla 2026-06-18 161901" src="https://github.com/user-attachments/assets/c0c32417-e97f-4fe3-9612-d75ae046a6aa" />



https://youtube.com/shorts/AJlLrTNiS2I?si=OBioyqRRyYEKV35q

### IA (claude.ai)

El proyecto fue realizado con ayuda de la IA

*Prompt utilizado con la IA para el desarrollo del proyecto*

Hola, necesito hacer un proyecto de electrónica sencillo, ojalá enviando datos de un arduino a una raspi o viceversa. Ya logramos que apretando un botón se encendiera un LED en el arduino enviando datos desde una raspi, a través de Adafruit. Ahora nosotras estábamos pensando en hacer un semáforo, ya con un módulo de semáforo, pero me imagino hacer que el semáforo se encienda con el movimiento de algo. Qué podría ser que no fuese tan complejo?, considerando que soy principiante en el mundo de la electrónica.

## Bibliografía

- https://pip-assets.raspberrypi.com/categories/1088-raspberry-pi-pico-2-w/documents/RP-008305-DS-1-pico-2-w-pinout.pdf
- https://docs.arduino.cc/resources/pinouts/ABX00087-full-pinout.pdf
- https://docs.arduino.cc/hardware/uno-r4-wifi/
