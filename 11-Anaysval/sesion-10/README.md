# sesion-10

lunes 18 mayo 2026

solemne 2

Junto a Benjamín, terminamos de definir la solemne que haríamos. Elegimos trabajar con un sensor PIR que detecta movimiento, conectado a una Raspberry Pi Pico 2 W para enviar los datos a Adafruit IO. Luego, la idea era usar una placa Arduino UNO R4 WiFi para mostrar una animación tipo GIF (como un fantasma, alien o persona caminando) según la información recibida. Más adelante, la idea del proyecto tuvo que cambiar debido a complicaciones de los códigos.

Después se nos indicó que debíamos incorporar un botón en ambas placas para evitar la saturación de datos en Adafruit IO. Por esto, dedicamos la clase entera a lograr el funcionamiento correcto del botón ദ്ദി( • ᴗ < )  (Fue un proceso estresante y complicado, pero finalmente se logró)

Al final de la clase, se informó que los grupos 07 y 04 debían unirse para la entrega del proyecto.

### Código botón 

```python

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
AIO_KEY = "blabla"

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

### Recordatorios de Aaron

![foto](./imagenes/aaron.jpg)

