import time
import board
import analogio
import digitalio
import wifi
import socketpool
import adafruit_minimqtt.adafruit_minimqtt as MQTT


# ── Configuración ──────────────────────────────────────────────────────────────
WIFI_SSID    = "NombreRedWifi"
WIFI_PASS    = "ContraseñaWifi"
AIO_USERNAME = "UsernameAio"
AIO_KEY      = "KeyAio"
FEED         = f"{AIO_USERNAME}/feeds/AioFeed"
INTERVALO        = 0.2   # segundos entre lecturas del loop
INTERVALO_ENVIO  = 3.0   # segundos máximos sin enviar (aunque no haya cambio)


# ── Hardware ───────────────────────────────────────────────────────────────────
pot = analogio.AnalogIn(board.A0)


button = digitalio.DigitalInOut(board.GP0)
button.direction = digitalio.Direction.INPUT
button.pull = digitalio.Pull.UP


# ── Helpers ────────────────────────────────────────────────────────────────────
def map_value(x, in_min, in_max, out_min, out_max):
    return int((x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min)


def conectar_wifi():
    if not wifi.radio.connected:
        print("Conectando a WiFi...")
        wifi.radio.connect(WIFI_SSID, WIFI_PASS)
        print(f"WiFi OK — IP: {wifi.radio.ipv4_address}")


def crear_mqtt():
    pool = socketpool.SocketPool(wifi.radio)
    cliente = MQTT.MQTT(
        broker="io.adafruit.com",
        port=1883,
        username=AIO_USERNAME,
        password=AIO_KEY,
        socket_pool=pool,
    )
    return cliente


def reconectar(mqtt):
    try:
        conectar_wifi()
        mqtt.reconnect()
        print("Reconectado a MQTT!")
        return True
    except Exception as e:
        print(f"Reintento fallido: {e}")
        return False


# ── Conexión inicial ───────────────────────────────────────────────────────────
conectar_wifi()
mqtt = crear_mqtt()
mqtt.connect()
print("MQTT conectado!")


# ── Estado ─────────────────────────────────────────────────────────────────────
ultimo_valor        = -1
pausado_antes       = False
ultimo_envio        = time.monotonic()  # <-- temporizador


# ── Loop principal ─────────────────────────────────────────────────────────────
while True:
    try:
        mqtt.loop()


        boton_presionado = not button.value
        ahora = time.monotonic()


        if boton_presionado:
            if not pausado_antes:
                print("Envío pausado (botón presionado)")
                pausado_antes = True
        else:
            if pausado_antes:
                print("Reanudando envío...")
                pausado_antes = False
                ultimo_envio = ahora  # reinicia el temporizador al reanudar


            angulo = map_value(pot.value, 0, 65535, 0, 180)


            hay_cambio        = abs(angulo - ultimo_valor) >= 2
            tiempo_cumplido   = (ahora - ultimo_envio) >= INTERVALO_ENVIO


            if hay_cambio or tiempo_cumplido:  # <-- la clave del cambio
                print(f"Publicando: {angulo}°")
                mqtt.publish(FEED, str(angulo))
                ultimo_valor = angulo
                ultimo_envio = ahora  # reinicia el temporizador


        time.sleep(INTERVALO)


    except (MQTT.MMQTTException, OSError, RuntimeError) as e:
        print(f"Conexión perdida: {e}")
        print("Esperando 5 segundos antes de reconectar...")
        time.sleep(5)
        reconectar(mqtt)
