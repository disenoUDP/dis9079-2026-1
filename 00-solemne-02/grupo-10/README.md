# solemne-02

## Integrantes

- Braulio Figueroa / github: [brauliofigueroa2001](https://github.com/brauliofigueroa2001)
- Luisa Toro / github: [Luisaatoro9](https://github.com/Luisaatoro9)
- Marlén Soto / github: [marlensoto-lab](https://github.com/marlensoto-lab)
- Marcela Zúñiga / github: [marcezm](https://github.com/marcezm)

El proceso de documentación está dividido en el inicio debido a que en el comienzo de la clase estuvimos trabajando como 2 dúos separados y nos juntamos casi al final de la clase en un grupo de 4. Es por ello que no quisimos perder el material y la documentación que se había logrado en un principio, por lo que primero se mostrarán los avances por separado y posteriormente el trabajo grupal de 4.

## Avance en clases dúo Braulio Figueroa y Luisa toro

**Paso a paso en clase**

El objetivo es tener un código de enviar desde un Raspberry Pi Pico 2W y un código de recibir en un Arduino Uno R4 Wifi, utilizaremos un botón como primer acercamiento para poder crear una especie de "puerta" que nos dé la opción de activar y desactivar el envío de lecturas de datos hacia Adafruit IO, de esta manera, el servidor de IO no colapsa y evitamos problemas.

Además, queríamos sumar un potenciómetro que enviara valores a Adafruit e interactuara con el led, prendiéndolo y apagándolo, pero no logramos conseguirlo en clases, por lo que la interacción solo fue entre el botón y el led.

**Conexión de botón a Raspberry Pi Pico 2w**

En un comienzo buscamos ejemplos de conexión de un botón a Raspberry Pi Pico 2w pero en las fotos mostraban la conexión mediante una resistencia, le preguntamos a Aarón si esto era necesario pero nos dijo que no porque estos botones vienen con una resistencia interna.

Luego de esta duda, lo que hicimos fue conectar un botón de 4 pines al módulo de Raspberry Pi Pico 2w, para ello seguimos como guía el pinout de la placa visto anteriormente en clases.

![pinoutRaspi](./imagenes/pinoutRaspi2w.JPG)

**Imagen 01**, *Pinout Raspberry Pi Pico 2w*

- En el código que nos mandó Mateo, se establece que el botón debe estar conectado al pin GP0, ya que, este pin entiende una lógica de 2 estados, HIGH y LOW, lo cuál sirve para el funcionamiento del botón (presionado, no presionado). La otra conexión que debemos hacer es a GND.

![conexionBoton](./imagenes/RaspberryBoton.jpg)

**Imagen 02**, *conexión de botón a Raspberry Pi Pico 2w*

## Código de enviar, experimentación en clases - Raspberry Pi Pico 2w

```cpp
import time
import board
import digitalio
import wifi
import socketpool
import adafruit_minimqtt.adafruit_minimqtt as MQTT

print("Iniciando programa...")

# -------------------------
# WiFi
# -------------------------
SSID = "auxilio"
PASSWORD = "cabal123"

print("Conectando WiFi...")

try:
    wifi.radio.connect(SSID, PASSWORD)
    print("WiFi conectado")
    print("IP:", wifi.radio.ipv4_address)

except Exception as e:
    print("Error WiFi:")
    print(e)

    while True:
        pass


# -------------------------
# Adafruit IO
# -------------------------
AIO_USERNAME = "udpmontoyamoraga"
AIO_KEY = "clavecredencial"

FEED_BOTON = AIO_USERNAME + "/feeds/boton-prueba-grupo10"

print("Creando conexión MQTT...")

pool = socketpool.SocketPool(wifi.radio)

mqtt = MQTT.MQTT(
    broker="io.adafruit.com",
    username=AIO_USERNAME,
    password=AIO_KEY,
    socket_pool=pool,
)

print("Conectando a Adafruit IO...")

try:
    mqtt.connect()
    print("Conectado a Adafruit IO")

except Exception as e:
    print("Error MQTT:")
    print(e)

    while True:
        pass


# -------------------------
# Botón GP0
# -------------------------
boton = digitalio.DigitalInOut(board.GP0)
boton.direction = digitalio.Direction.INPUT
boton.pull = digitalio.Pull.UP

estado_anterior = True

print("Sistema listo")

# -------------------------
# Loop principal
# -------------------------
while True:

    try:
        mqtt.loop()

        estado_actual = boton.value

        # Detecta transición:
        # sin presionar -> presionado
        if estado_anterior and not estado_actual:

            print("Botón presionado")
            print("Enviando impulso...")

            mqtt.publish(FEED_BOTON, "1")

            print("Impulso enviado")

            # anti-rebote
            time.sleep(0.25)

        estado_anterior = estado_actual

    except Exception as e:
        print("Error:")
        print(e)

    time.sleep(0.02)
```
Este código nos fue facilitado por Mateo, quien nos ayudó durante todo el proceso. Lo que hace en resumen es conectar la Raspberry Pi Pico 2w al wifi y enviar datos al feed asignado de nuestro grupo, estos datos se envían cuando se presiona el botón, envía de 1 a la vez.

Después de varios intentos de intentar conectarse al wifi, finalmente la placa lo pudo lograr, pulsamos el botón y enviaba datos a Adafruit IO y notamos que existía un pequeño delay al enviar el dato.

![datos](./imagenes/adafruitBoton2.JPG)

**Imagen 03**, *datos enviados a Adafruit IO*

![datos](./imagenes/botonRaspifeeds.JPG)

**Imagen 04**, *datos enviados a  Adafruit IO con fecha y hora*

- Un error que ocurrió después de enviar constantemente datos es que el led se quedó encendido y no volvió a apagarse.

## Código recibir, Experimentación en clases, Arduino UNO R4 Wifi

**colocar aquí código, gif queda al final de toda esta parte de proceso**

![gif](./imagenes/RaspberryArduinogif.gif)

## Avance en clases Marlén Soto y Marcela Zúñiga

## Descripción del proyecto















## Materiales usados

| Cantidad | Componente / Recurso | Función en esta Etapa |
| --- | --- | --- |
| 1 | Arduino UNO R4 WiFi | Placa para recibir mensajes. |
| 1 | Raspberry Pi Pico 2w | Placa para enviar mensajes
| 1 | Cable USB-C | Conexión física para cargar el código desde el PC en Arduino. |
| 1 | Cable USB-A Micro USB | Conexión física para cargar el código desde PC a Raspberry Pi Pico 2. |
| 1 | Arduino IDE (Software) | Instalado en el PC para programar la placa Arduino. |
| 1 | Visual Studio Code (Software) | Instalado en el PC para programar en Python hacia Raspberry. |
| 1 | Cuenta Adafruit IO | Registro en la plataforma para recibir los primeros datos. |
| 1 | Hotspot Móvil / WiFi | Red de 2.4 GHz necesaria para la salida a internet. |
| 1 | LED 5 MM | Encenderse y apagarse en base al pulso del botón. | 
| 2 | Protoboard pequeña | sirve para conectar placas, LED, resistencia y botón. |
| 1 | Resistencia 220K | Limitar la corriente que entra al LED. |
| 1 | Push Button 4 pines | Envía mensaje a través de una pulsación. |
| 4 | Cables Dupont | Encargados de establecer las conexiones de Hardware. |



## Sensor usado

## Actuador usado

- Leds/Servomotor

## Código usado para enviar Raspberry Pi Pico 2w

```cpp
import time
import board
import digitalio
import wifi
import socketpool
import adafruit_minimqtt.adafruit_minimqtt as MQTT

print("Iniciando programa...")

# -------------------------
# WiFi
# -------------------------
SSID = "auxilio"
PASSWORD = "cabal123"

print("Conectando WiFi...")

try:
    wifi.radio.connect(SSID, PASSWORD)
    print("WiFi conectado")
    print("IP:", wifi.radio.ipv4_address)

except Exception as e:
    print("Error WiFi:")
    print(e)
    while True:
        pass

# -------------------------
# Adafruit IO
# -------------------------
AIO_USERNAME = "udpmontoyamoraga"
AIO_KEY = "clavecredencial"

FEED_BOTON = AIO_USERNAME + "/feeds/boton-prueba-grupo10"

print("Creando conexión MQTT...")

pool = socketpool.SocketPool(wifi.radio)

mqtt = MQTT.MQTT(
    broker="io.adafruit.com",
    username=AIO_USERNAME,
    password=AIO_KEY,
    socket_pool=pool,
)

print("Conectando a Adafruit IO...")

try:
    mqtt.connect()
    print("Conectado a Adafruit IO")

except Exception as e:
    print("Error MQTT:")
    print(e)
    while True:
        pass

# -------------------------
# Botón GP0
# -------------------------
boton = digitalio.DigitalInOut(board.GP0)
boton.direction = digitalio.Direction.INPUT
boton.pull = digitalio.Pull.UP

estado_anterior = True

print("Sistema listo")

# -------------------------
# Loop principal
# -------------------------
while True:

    try:
        mqtt.loop()

        estado_actual = boton.value

        # presionado -> envía 1
        if estado_anterior and not estado_actual:
            print("Botón presionado")
            mqtt.publish(FEED_BOTON, "1")
            print("Enviado: 1")
            time.sleep(0.25)  # anti-rebote

        # soltado -> envía 0
        if not estado_anterior and estado_actual:
            print("Botón soltado")
            mqtt.publish(FEED_BOTON, "0")
            print("Enviado: 0")
            time.sleep(0.25)  # anti-rebote

        estado_anterior = estado_actual

    except Exception as e:
        print("Error, reconectando:", e)
        try:
            mqtt.reconnect()
        except:
            pass

    time.sleep(0.02)
```
**Explicación breve del código**

- La primera parte del código importa las bibliotecas puestas dentro de nuestra Raspberry Pi, inicia el programa e intenta conectar la placa al WiFi asignado en las líneas "SSID: auxilio" y "PASSWORD: cabal123".

- En la segunda sección del código tenemos todo lo destinado a Adafruit IO, aquí colocamos las credenciales de la cuenta.

- La línea de código "FEED_BOTON = AIO_USERNAME + "/feeds/boton-prueba-grupo10" identifica el canal de conexión MQTT en el cuál se publicarán los mensajes que se reciban. Esta línea establece: ¿de quien es el feed? --> AIO_USERNAME y ¿qué feed es? --> boton-prueba-grupo10.

- La tercera parte del código establece el funcionamiento del botón, lo asigna dentro del pin GP 0 que es donde está conectado y es una entrada digital, esto ocurre con la línea "boton = digitalio.DigitalInOut(board.GP0)".

- "mqtt.loop()" mantiene en todo momento la conexión con Adafruit.

- "estado_actual = boton.value" muestra el valor del botón y lee si es que el botón está presionado o no, en este caso, true --> botón en reposo (no presionado) y false --> botón presionado.

- Cuando se de la condición "if estado_anterior and not estado_actual:" significa que el estado anterior es distinto del estado actual del botón, por ende, detecta que alguien SÍ presionó el botón.

- Cuando estado_anterior = estado_actual, significa que no está presionado el botón porque ambos estados son iguales, por lo que no pasa nada, el botón únicamente activa la lectura cuando el estado actual es distinto del estado anterior.

**Agregamos una nueva parte al código para poder solucionar el error en el que sólo se enviaba "1" hacia Adafruit IO**

![codigo2](./imagenes/codigoRaspi2.JPG)

- La línea "if not estado_anterior and estado_actual:" hace lo opuesto a "if estado_anterior and not estado_actual:" , es decir, si anteriormente el botón estaba presionado (false) y ahora ya no lo está (true) entonces significa que alguien soltó el botón, por lo tanto envía 0 a Adafruit.

- La línea "time.sleep(0.25)" en ambos casos (apretar botón y soltar botón) sirve para que el botón registre solamente 1 lectura en 1 pulsada, es un anti-rebote.

- Por último, a diferencia de antes, ahora si es que hay un error intenta reconectarse automáticamente a Adafruit IO. Anteriormente sólo imprimía el mensaje del error.

![codigoultimaparte](./imagenes/codigoRaspi3.JPG)

## Errores en Raspberry Pi Pico 2w

Hubo diversos errores durante el proceso, al enfrentarse nuevamente a Raspberry Pi Pico 2w y abrir vscode, enviar el código, aparecía lo siguiente:

![error1](./imagenes/errorparabitacora1.JPG)

Esto sucedía porque estábamos presionando el ícono de flecha en vscode para correr el código, aparecían estos avisos y el código no funcionaba correctamente, la placa no se conectaba a Wifi. 

Le preguntamos a Mateo y nos dijo que sólo era necesario apretar ctrl+s para enviar el código a la Raspberry, lo intentamos, se envió correctamente y la placa se pudo conectar a WiFi. También notamos que al enviarse el código, el LED de la Raspberry siempre se enciende 1 vez rápidamente, esto es un aviso de que recibió el código y no habíamos notado esto hasta ese momento.

Otro error al momento de iniciar vscode era el modo restringido

![error2](./imagenes/errorPython.JPG)

Esto aparecía cada vez que abríamos vscode en un computador, debemos apretar trust para poder seguir adelante. Lo que hacía este error era que de alguna manera restringe a Python y este no puede operar con normalidad, es como si lo "reprimiera". No encontramos la forma de evitar que se abriera esta ventana cada vez que abríamos vscode por lo que siempre teníamos que apretar "trust" para continuar.

Uno de los errores más importantes fue el hecho de que el LED se quedaba encendido tras presionar el botón reiteradas veces. Esto ocurría porque el código en un inicio (lunes) al enviar datos a adafruit, sólo enviaba el valor 1, esto hacía que el LED detectara sólo la opción de encenderse, entonces después de cierto rato presionando el botón repetidamente se bugeaba y dejaba de funcionar correctamente.

Este error se solucionó al agregar esta parte extra al código, la cuál hace que al soltar el botón se envíe un 0, indicando que el led se debe apagar

![errorsolucion3](./imagenes/codigoBoton2.JPG)

![errorsolucion4](./imagenes/0y1Raspi.JPG)

De esta manera ahora en los feeds aparecía que se enviaban 0 y 1 respectivamente, lo cuál hace que el led se encienda y se apague sin bugearse, independiente de la cantidad de veces que presionemos el botón.









## Código usado para recibir Arduino UNO R4 Wifi

## Imágenes del proyecto

## Animaciones del proyecto

## Bibliografía
