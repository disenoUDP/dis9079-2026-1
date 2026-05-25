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
SSID = "si"
PASSWORD = "mailo6192."

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
AIO_USERNAME = "Magdalena"
AIO_KEY = "keyadafruit"

# Feed al que se envían los mensajes
FEED_BOTON = AIO_USERNAME + "/feeds/prueba05"

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

# Contador de presiones
contador_boton = 0

# Mensajes que se enviarán en orden
mensajes = ["Sonrie por mi", "amigo", "yo sonrio por ti", "..."]

print("Sistema listo")
print("Esperando botón...")


# -------------------------
# Loop principal
# -------------------------
while True:

    try:
        mqtt.loop()

        estado_actual = boton.value

        # Detecta cuando el botón pasa de NO presionado a presionado
        if estado_anterior == True and estado_actual == False:

            mensaje = mensajes[contador_boton]

            print("Botón presionado")
            print("Enviando:", mensaje)

            mqtt.publish(FEED_BOTON, mensaje)

            print("Mensaje enviado a Adafruit IO")

            # Avanza al siguiente mensaje
            contador_boton = contador_boton + 1

            # Si ya mandó boton 03, vuelve a boton 01
            if contador_boton >= 4:
                contador_boton = 0

            # Anti-rebote
            time.sleep(0.3)

            # Espera a que sueltes el botón antes de leer otra presión
            while boton.value == False:
                mqtt.loop()
                time.sleep(0.01)

        estado_anterior = boton.value

    except Exception as e:
        print("Error:")
        print(e)

    time.sleep(0.02)