import time
import wifi
import socketpool
import ssl
import analogio
import board

import adafruit_minimqtt.adafruit_minimqtt as MQTT

# ==========================
# WIFI
# ==========================

SSID = "bla"
PASSWORD = "bla"

# ==========================
# ADAFRUIT IO
# ==========================

AIO_USERNAME = "bla"
AIO_KEY = "bla"

FEED_CEREBRO = f"{AIO_USERNAME}/feeds/cerebro"

# ==========================
# MICROFONO MAX4466
# ==========================

mic = analogio.AnalogIn(board.GP26)

UMBRAL = 40000

# ==========================
# WIFI
# ==========================

print("Conectando WiFi...")

wifi.radio.connect(SSID, PASSWORD)

print("WiFi OK")
print("IP:", wifi.radio.ipv4_address)

# ==========================
# MQTT
# ==========================

pool = socketpool.SocketPool(wifi.radio)

mqtt = MQTT.MQTT(
    broker="io.adafruit.com",
    username=AIO_USERNAME,
    password=AIO_KEY,
    socket_pool=pool,
    ssl_context=ssl.create_default_context()
)

print("Conectando MQTT...")

mqtt.connect()

print("Conectado a Adafruit IO")
print("Esperando soplidos...")

# ==========================
# LOOP
# ==========================

while True:

    lectura = mic.value

    if lectura > UMBRAL:

        maximo = lectura
        suma = 0
        cantidad = 0

        inicio = time.monotonic()

        # Captura durante 150 ms
        while (time.monotonic() - inicio) < 0.15:

            muestra = mic.value

            suma += muestra
            cantidad += 1

            if muestra > maximo:
                maximo = muestra

        promedio = suma // cantidad

        ultimo_digito = (maximo + promedio) % 10

        print("----------------")
        print("Maximo:", maximo)
        print("Promedio:", promedio)
        print("Ultimo digito:", ultimo_digito)

        mqtt.publish(FEED_CEREBRO, str(ultimo_digito))

        print("Enviado a feed cerebro")

        # Evita múltiples detecciones
        time.sleep(5)

    time.sleep(0.01)