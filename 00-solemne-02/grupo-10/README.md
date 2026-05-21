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

**Conexión de botón a Raspberry Pi Pico 2w**

En un comienzo buscamos ejemplos de conexión de un botón a Raspberry Pi Pico 2w pero en las fotos mostraban la conexión mediante una resistencia, le preguntamos a Aarón si esto era necesario pero nos dijo que no porque estos botones vienen con una resistencia interna.

Luego de esta duda, lo que hicimos fue conectar un botón de 4 pines al módulo de Raspberry Pi Pico 2w, para ello seguimos como guía el pinout de la placa visto anteriormente en clases.

![pinoutRaspi](./imagenes/pinoutRaspi2w.JPG)

**Imagen 01**, *Pinout Raspberry Pi Pico 2w*

- En el código que nos mandó Mateo, se establece que el botón debe estar conectado al pin GP0, ya que, este pin entiende una lógica de 2 estados, HIGH y LOW, lo cuál sirve para el funcionamiento del botón (presionado, no presionado). La otra conexión que debemos hacer es a GND.

![conexionBoton](./imagenes/RaspberryBoton.jpg)

**Imagen 02**, *conexión de botón a Raspberry Pi Pico 2w*

## Código de enviar - Raspberry Pi Pico 2w

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

**agregar explicación breve del código?**

- Después de varios intentos de que la placa se conectara al wifi finalmente lo hizo

- Pulsamos el botón y enviaba datos a Adafruit IO, notamos que tiene un pequeño delay al recibir el dato

- Cabe destacar que Mateo nos ayudó durante este proceso

![datos](./imagenes/adafruitBoton2.JPG)

**Imagen 03**, *recibimiento de datos en Adafruit IO*

![datos](./imagenes/botonRaspifeeds.JPG)

**Imagen 04**, *recibimiento de datos en Adafruit IO*





De momento pudimos prender el led en el arduino mediante el pulso con un botón en raspberry pi 

**borrador de lo que se estaba haciendo el lunes, agregar o quitar cosas**







## Materiales usados

## Sensor usado

## Actuador usado

- Leds/Servomotor

## Código usado para enviar

## Código usado para recibir

## Imágenes del proyecto

## Animaciones del proyecto

## Bibliografía
