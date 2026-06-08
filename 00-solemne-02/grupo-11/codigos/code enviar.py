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
SSID = "x"
PASSWORD = "x"

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
AIO_USERNAME = "x"
AIO_KEY = "x"

FEED_BOTON = AIO_USERNAME + "/feeds/prueba"

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

        # True = no presionado, False = presionado (lógica invertida por Pull.UP)

        # Botón presionado: True -> False → ENCENDER LED
        if estado_anterior and not estado_actual:
            print("Botón presionado → Encendiendo LED")
            mqtt.publish(FEED_BOTON, "ON")
            print("Enviado: ON")
            time.sleep(0.25)  # anti-rebote

        # Botón suelto: False -> True → APAGAR LED
        elif not estado_anterior and estado_actual:
            print("Botón suelto → Apagando LED")
            mqtt.publish(FEED_BOTON, "OFF")
            print("Enviado: OFF") # type: ignore
            time.sleep(0.25)  # anti-rebote

        estado_anterior = estado_actual

    except Exception as e:
        print("Error:")
        print(e)

    time.sleep(0.02)