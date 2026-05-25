# ============================================================
# Raspberry Pi Pico 2W — Potenciómetro + botón switch + OLED
# Envío de datos a Adafruit IO con pantalla de estado
# ============================================================
# CONEXIONES:
#   Botón:        un extremo → GP14, otro extremo → GND
#   Potenciómetro: señal → GP26 (ADC0), patas → 3V3 y GND
#   OLED SSD1306:  VCC → 3V3, GND → GND, SDA → GP4, SCL → GP5
# ============================================================

import time
import board
import digitalio
import analogio
import busio
import wifi
import socketpool
import adafruit_minimqtt.adafruit_minimqtt as MQTT

import displayio
import i2cdisplaybus
import terminalio
from adafruit_display_text import label
import adafruit_displayio_ssd1306

# ------------------------------------------------------------
# CONFIGURACIÓN
# ------------------------------------------------------------
WIFI_SSID     = "iPhone-cs"
WIFI_PASSWORD = "lasagna342"

AIO_USERNAME  = "Camila_Parada"
AIO_KEY       = "Clave-io"

FEED          = f"{AIO_USERNAME}/feeds/papa-prueba"

PIN_BOTON     = board.GP14
PIN_POT       = board.GP26
PIN_SDA       = board.GP4
PIN_SCL       = board.GP5

DEBOUNCE_MS   = 50
ENVIO_MS      = 250
UMBRAL_CAMBIO = 500
MQTT_LOOP_INTERVAL_MS = 500
# ------------------------------------------------------------

# --- Inicializar pantalla OLED ---
displayio.release_displays()
i2c = busio.I2C(PIN_SCL, PIN_SDA)
display_bus = i2cdisplaybus.I2CDisplayBus(i2c, device_address=0x3C)
oled = adafruit_displayio_ssd1306.SSD1306(display_bus, width=128, height=64)

# Grupo de elementos en pantalla
splash = displayio.Group()
oled.root_group = splash

# Tres líneas de texto reutilizables
linea_titulo = label.Label(terminalio.FONT, text="", x=0, y=8)
linea_estado = label.Label(terminalio.FONT, text="", x=0, y=30)
linea_valor  = label.Label(terminalio.FONT, text="", x=0, y=52)
splash.append(linea_titulo)
splash.append(linea_estado)
splash.append(linea_valor)

def mostrar(titulo=None, estado=None, valor=None):
    if titulo is not None:
        linea_titulo.text = titulo
    if estado is not None:
        linea_estado.text = estado
    if valor is not None:
        linea_valor.text = valor

mostrar("Iniciando...", "", "")

# --- Botón ---
boton = digitalio.DigitalInOut(PIN_BOTON)
boton.direction = digitalio.Direction.INPUT
boton.pull = digitalio.Pull.UP

# --- Potenciómetro ---
pot = analogio.AnalogIn(PIN_POT)

# --- WiFi ---
def conectar_wifi():
    while True:
        try:
            mostrar("Conectando WiFi", "", "")
            print("Conectando a WiFi...")
            wifi.radio.connect(WIFI_SSID, WIFI_PASSWORD)
            print(f"Conectado! IP: {wifi.radio.ipv4_address}")
            return
        except Exception as e:
            print(f"Fallo WiFi ({e}). Reintento en 5s...")
            mostrar("Error WiFi", "Reintentando...", "")
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
                conectar_wifi()
            mostrar("Conectando", "Adafruit IO...", "")
            print("Conectando a Adafruit IO...")
            mqtt.connect()
            print("¡Conectado a Adafruit IO!")
            return
        except Exception as e:
            intentos += 1
            espera = min(3 * intentos, 30)
            print(f"Fallo al conectar ({e}). Reintento en {espera}s...")
            mostrar("Error conexion", f"Reintento {espera}s", "")
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

def leer_pot_porcentaje():
    return int((pot.value / 65535) * 100)

# --- Variables de estado ---
encendido        = False
estado_boton_ant = True
ultimo_cambio_b  = 0
ultimo_envio     = 0
ultima_lectura   = -9999
ultimo_loop_mqtt = 0

# Pantalla inicial: instrucción al usuario
mostrar("Listo!", "Presiona y gira", "Estado: APAGADO")
print("=== Listo ===")
print("Presiona el botón para ENCENDER el envío del potenciómetro")
print()

while True:
    ahora = time.monotonic_ns() // 1_000_000

    # ----- BOTÓN: toggle -----
    presionado = not boton.value
    if presionado != (not estado_boton_ant):
        if (ahora - ultimo_cambio_b) > DEBOUNCE_MS:
            ultimo_cambio_b = ahora
            estado_boton_ant = boton.value
            if presionado:
                encendido = not encendido
                if encendido:
                    print(">>> ENCENDIDO")
                    mostrar("ENCENDIDO", "Gira el pot", "Pot: ---")
                else:
                    print(">>> APAGADO")
                   mostrar("APAGADO", "Presiona y gira", "Estado: OFF")
                    publicar("0")

    # ----- POTENCIÓMETRO: solo si está encendido -----
    if encendido and (ahora - ultimo_envio) > ENVIO_MS:
        lectura_cruda = pot.value
        if abs(lectura_cruda - ultima_lectura) > UMBRAL_CAMBIO:
            ultima_lectura = lectura_cruda
            ultimo_envio = ahora
            valor = leer_pot_porcentaje()
            print(f"    Pot = {valor}%")
            mostrar("ENCENDIDO", "Gira el pot", f"Pot: {valor}%")
            publicar(str(valor))

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