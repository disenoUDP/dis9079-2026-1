#  LIBRERIA necesaria en /lib:
#    - adafruit_minimqtt
# ============================================================

import time
import board # type: ignore
import analogio # type: ignore
import digitalio # type: ignore
import wifi # type: ignore
import socketpool # type: ignore
import adafruit_minimqtt.adafruit_minimqtt as MQTT # type: ignore

#  cambiar claves wifi
WIFI_SSID     = "iPhone de Valentina"
WIFI_PASSWORD = "blablabla"

AIO_USERNAME  = "vxlentiinaa"
AIO_KEY       = "blablabla"

FEED_ANGULO   = f"{AIO_USERNAME}/feeds/moluscos"

# definir potenciometro + led
potenciometro = analogio.AnalogIn(board.GP27)

led = digitalio.DigitalInOut(board.LED)
led.direction = digitalio.Direction.OUTPUT
led.value = False

# lee los valores en angulo, del potenciometro
def leer_angulo():
    # ADC devuelve 0-65535, convertimos a 0-180
    return int(potenciometro.value * 180 / 65535)

# verificar conexion wifi
print("Conectando a WiFi...")
try:
    wifi.radio.connect(WIFI_SSID, WIFI_PASSWORD)
    print("  ✓ IP:", wifi.radio.ipv4_address)
except Exception as e:
    print("  ✗ Error WiFi:", e)
    while True:
        pass

# verificar conexion mqtt
pool = socketpool.SocketPool(wifi.radio)

mqtt = MQTT.MQTT(
    broker="io.adafruit.com",
    port=1883,
    username=AIO_USERNAME,
    password=AIO_KEY,
    socket_pool=pool,
)

try:
    mqtt.connect()
    print("  ✓ Conectado a Adafruit IO")
    print("  Feed:", FEED_ANGULO)
    print("\nListo. Gira el potenciómetro...\n")
except Exception as e:
    print("  ✗ Error MQTT:", e)
    while True:
        pass

# aqui se define todo 
angulo_anterior = -1

while True:
    try:
        mqtt.loop()

        angulo = leer_angulo()

        # Publica solo si cambi0 mas de 2 grados (filtra ruido del ADC)
        if abs(angulo - angulo_anterior) > 2:
            print("Angulo:", angulo, "° → publicando...")
            mqtt.publish(FEED_ANGULO, str(angulo))
            angulo_anterior = angulo

            # Parpadeo del LED al publicar
            led.value = True
            time.sleep(0.05)
            led.value = False

    except Exception as e:
        print("Error:", e, "— reconectando...")
        try:
            mqtt.reconnect()
        except Exception:
            pass

    time.sleep(0.1)
