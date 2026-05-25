import time
import board
import digitalio
import wifi
import socketpool
import adafruit_minimqtt.adafruit_minimqtt as MQTT

print("Iniciando programa...")

SSID = "nombre_wifi"
PASSWORD = "clave_wifi"

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


AIO_USERNAME = "tu_usuario"
AIO_KEY = "tu_clave"

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

boton = digitalio.DigitalInOut(board.GP0)
boton.direction = digitalio.Direction.INPUT
boton.pull = digitalio.Pull.UP

estado_anterior = True

print("Sistema listo")

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