# ============================================================
# Raspberry Pi Pico 2W — Emisor de 1 botón a Adafruit IO
# Instrumento Maywa Denki / Chan
# ============================================================
# CONEXIONES:
#   Botón: un extremo → GP14, otro extremo → GND
#
# PROTOCOLO (feed: papa):
#   "1" → botón presionado (dispara un golpe)
#   (soltar el botón no envía nada)
# ============================================================

import time
import board
import digitalio
import wifi
import socketpool
import adafruit_minimqtt.adafruit_minimqtt as MQTT

# ------------------------------------------------------------
WIFI_SSID     = "iPhone de Vania"
WIFI_PASSWORD = "dilt1234"

AIO_USERNAME  = "paredesvania"
AIO_KEY       = ""

FEED          = f"{AIO_USERNAME}/feeds/papa"

PIN_BOTON     = board.GP14
DEBOUNCE_MS   = 50
MQTT_LOOP_INTERVAL_MS = 1000
# ------------------------------------------------------------

boton = digitalio.DigitalInOut(PIN_BOTON)
boton.direction = digitalio.Direction.INPUT
boton.pull = digitalio.Pull.UP

def conectar_wifi():
    while True:
        try:
            print("Conectando a WiFi...")
            wifi.radio.connect(WIFI_SSID, WIFI_PASSWORD)
            print(f"Conectado! IP: {wifi.radio.ipv4_address}")
            return
        except Exception as e:
            print(f"Fallo WiFi ({e}). Reintento en 5s...")
            time.sleep(5)

conectar_wifi()

pool = socketpool.SocketPool(wifi.radio)
mqtt = MQTT.MQTT(
    broker="io.adafruit.com",
    port=1883,
    username=AIO_USERNAME,
    password=AIO_KEY,
    socket_pool=pool,
    socket_timeout=1,
    connect_retries=2,
    keep_alive=60,
)

def conectar_mqtt():
    intentos = 0
    while True:
        try:
            if not wifi.radio.connected:
                print("WiFi caído, reconectando...")
                conectar_wifi()
            print("Conectando a Adafruit IO...")
            mqtt.connect()
            print("¡Conectado a Adafruit IO!")
            return
        except Exception as e:
            intentos += 1
            espera = min(3 * intentos, 30)
            print(f"Fallo al conectar ({e}). Reintento en {espera}s...")
            time.sleep(espera)

def publicar(valor):
    try:
        mqtt.publish(FEED, valor)
        print(f"   ✓ Publicado: {valor}")
    except Exception as e:
        print(f"Error al publicar ({e}). Reconectando...")
        try:
            mqtt.disconnect()
        except:
            pass
        conectar_mqtt()
        try:
            mqtt.publish(FEED, valor)
        except Exception as e2:
            print(f"Error tras reconexión: {e2}")

conectar_mqtt()

estado_anterior = False
ultimo_cambio   = 0
ultimo_loop_mqtt = 0

print("=== Listo. Presiona el botón para disparar ===")
print()

while True:
    ahora = time.monotonic_ns() // 1_000_000

    presionado = not boton.value

    # ----- BOTÓN: envía "1" solo al presionar -----
    if presionado != estado_anterior and (ahora - ultimo_cambio) > DEBOUNCE_MS:
        ultimo_cambio = ahora
        estado_anterior = presionado
        if presionado:
            print(">>> BOTÓN PRESIONADO — enviando '1'")
            publicar("1")

    # ----- Mantener viva la conexión MQTT -----
    if (ahora - ultimo_loop_mqtt) > MQTT_LOOP_INTERVAL_MS:
        ultimo_loop_mqtt = ahora
        try:
            mqtt.loop(timeout=1)
        except Exception as e:
            print(f"Conexión perdida ({e}). Reconectando...")
            try:
                mqtt.disconnect()
            except:
                pass
            conectar_mqtt()