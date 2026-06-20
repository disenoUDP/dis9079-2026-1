import time
import wifi
import socketpool
import board
import digitalio
import adafruit_minimqtt.adafruit_minimqtt as MQTT

# Datos de tu WiFi
WIFI_SSID = "iPhone de M"
WIFI_PASS = "blabla"

# Datos de Adafruit IO
AIO_USERNAME = "catasola"
AIO_KEY = "blabla"
FEED_NAME = "pruebasemaforo"

# Pines del semaforo
led_verde = digitalio.DigitalInOut(board.GP16)
led_verde.direction = digitalio.Direction.OUTPUT

led_amarillo = digitalio.DigitalInOut(board.GP17)
led_amarillo.direction = digitalio.Direction.OUTPUT

led_rojo = digitalio.DigitalInOut(board.GP18)
led_rojo.direction = digitalio.Direction.OUTPUT

# Conectar WiFi
print("Conectando a WiFi...")
wifi.radio.connect(WIFI_SSID, WIFI_PASS)
print("Conectado! IP:", wifi.radio.ipv4_address)

pool = socketpool.SocketPool(wifi.radio)

# Funcion para actualizar el semaforo segun el valor recibido
def actualizar_semaforo(valor):
    valor = int(valor)
    print("Valor recibido:", valor)

    if valor <= 5:
        led_verde.value = True
        led_amarillo.value = False
        led_rojo.value = False
    elif valor <= 10:
        led_verde.value = False
        led_amarillo.value = True
        led_rojo.value = False
    else:
        led_verde.value = False
        led_amarillo.value = False
        led_rojo.value = True

# Callback cuando llega un mensaje del feed
def mensaje_recibido(client, topic, message):
    actualizar_semaforo(message)

# Configurar cliente MQTT
mqtt_client = MQTT.MQTT(
    broker="io.adafruit.com",
    username=AIO_USERNAME,
    password=AIO_KEY,
    socket_pool=pool,
)

mqtt_client.on_message = mensaje_recibido

print("Conectando a Adafruit IO...")
mqtt_client.connect()

feed_topic = "{}/feeds/{}".format(AIO_USERNAME, FEED_NAME)
mqtt_client.subscribe(feed_topic)

print("Conectado a Adafruit IO, esperando datos...")

# Loop principal
while True:
    try:
        mqtt_client.loop()
    except Exception as e:
        print("Error:", e)
    time.sleep(0.1)