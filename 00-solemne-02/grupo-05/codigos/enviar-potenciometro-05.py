import time
import board
import analogio
import digitalio
import wifi
import socketpool
import adafruit_minimqtt.adafruit_minimqtt as MQTT

# conexión a wifi
SSID = "si"
PASSWORD = "mailo6192."

print("Conectando WiFi...")
wifi.radio.connect(
    SSID,
    PASSWORD
)
print("WiFi conectado")

# conexión mqtt
pool = socketpool.SocketPool(wifi.radio)
mqtt = MQTT.MQTT(
    broker="io.adafruit.com",
    username="udpmontoyamoraga",
    password="keydeaarón",
    socket_pool=pool
)
mqtt.connect()
print("MQTT conectado")

# potenciómetro
pot = analogio.AnalogIn(board.A0)

# se configura pin gp0 como entrada digital del botón
button = digitalio.DigitalInOut(board.GP0)
button.direction = digitalio.Direction.INPUT
button.pull = digitalio.Pull.UP # resistencia interna pull-up

# pin gp1 como salida digital para controlar el led
led = digitalio.DigitalInOut(board.GP1)
led.direction = digitalio.Direction.OUTPUT

ultimo_valor = -1 # empieza en -1 para asegurar que siempre suceda el primer envío

while True:
    if not button.value:
        led.value = True # se enciende el LED cuando el botón se presiona

        valor = pot.value * 1023 // 65535 # de valor crudo a escala de 0 a 1023
        if abs(valor - ultimo_valor) > 5: # manda datos cuando el valor cambia por 5 unidades y así no se satura el adafruit
            print("Enviando:", valor)
            mqtt.publish(
                "udpmontoyamoraga/feeds/potenciometro-05",
                str(valor)
            )
            ultimo_valor = valor
        time.sleep(0.2) # descanso pequeño para que no lea taaaan rápido
    else:
        # se apaga el led al soltar el botón
        led.value = False
        time.sleep(0.01)