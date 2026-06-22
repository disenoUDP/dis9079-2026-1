# PROYECTO BRUMA COMPACTA

#  La Raspi se conecta al WiFi, consulta la humedad real de 8 ciudades
#  chilenas usando la API de Open-Meteo, y publica esos datos en
#  Adafruit IO para que el Arduino los reciba y haga la ruleta.

#  El switch activa el envío y el LED muestra cuándo está trabajando.

import time
import wifi
import socketpool
import ssl
import board
import digitalio
import adafruit_requests
import adafruit_minimqtt.adafruit_minimqtt as MQTT


#  Define rangos para la comunicación al terminal serial de PuTTY

BAUD_RATE = 115200
print(f"Baudios: {BAUD_RATE}")

# Define credenciales constantes

WIFI_SSID     = "si"
WIFI_PASSWORD = "mailo-6192"


AIO_USER   = "nicolasvgreve"
AIO_KEY    = "aio_key"


AIO_BROKER = "io.adafruit.com"
AIO_PORT   = 1883


OWM_BASE_URL = "https://api.open-meteo.com/v1/forecast" # Dirección base de la API de Open-Meteo


# Ciudades: (Nombre, latitud, longitud, nombre-del-feed)
CIUDADES = [
    ("Arica",               -18.48,  -70.33,  "humedad-arica"),
    ("Copiapo",             -27.37,  -70.33,  "humedad-copiapo"),
    ("Santiago",            -33.45,  -70.67,  "humedad-santiago"),
    ("Valparaiso",          -33.05,  -71.62,  "humedad-valparaiso"),
    ("Isla de Pascua",      -27.11,  -109.35, "humedad-isla-pascua"), 
    ("Juan Fernandez",      -33.65,  -78.83,  "humedad-juan-fernandez"),
    ("Punta Arenas",        -53.16,  -70.91,  "humedad-punta-arenas"),
    ("Villa Las Estrellas", -62.19,  -58.98,  "humedad-antartica"),
]

# Define conexiones del hardware

# Cada sensor: (pin, pull, descripción)

# Pull.UP → valor False = activado (conectado a GND)

SENSORES = [
    {"pin": board.GP14, "pull": digitalio.Pull.UP, "nombre": "switch-principal"},
]


# Cada actuador: (pin, descripción)

ACTUADORES = [
    {"pin": board.GP16, "nombre": "led-principal"},
]


# Inicializar sensores con bucle

for s in SENSORES:
    dio = digitalio.DigitalInOut(s["pin"])
    dio.direction = digitalio.Direction.INPUT
    dio.pull = s["pull"]
    s["io"] = dio          # guardar objeto DigitalInOut dentro del dict


# Inicializar actuadores con bucle
for a in ACTUADORES:
    dio = digitalio.DigitalInOut(a["pin"])
    dio.direction = digitalio.Direction.OUTPUT
    dio.value = False
    a["io"] = dio          # guardar objeto DigitalInOut dentro del dict


# Accesos rápidos (para no cambiar el resto del código)

switch = SENSORES[0]["io"]
led    = ACTUADORES[0]["io"]


# Helpers de hardware


def set_todos_actuadores(valor: bool):
    """Enciende o apaga todos los LEDs del arreglo."""
    for a in ACTUADORES:
        a["io"].value = valor


def parpadeo_actuadores(n: int = 3, intervalo: float = 0.2):
    """Hace parpadear todos los LEDs n veces."""
    for _ in range(n):
        set_todos_actuadores(True)   # encender todos
        time.sleep(intervalo)        # descansar
        set_todos_actuadores(False)  # apagar todos
        time.sleep(intervalo)        # esperar antes del siguiente parpadeo


def leer_sensores() -> list:
    """Devuelve lista de (nombre, valor) para cada sensor."""
    return [(s["nombre"], s["io"].value) for s in SENSORES]


# Funciones WiFi


def conectar_wifi():
    print(f"Conectando a {WIFI_SSID}...")
    intentos = 0
    while not wifi.radio.connected and intentos < 20:
        try:
            wifi.radio.connect(WIFI_SSID, WIFI_PASSWORD)
        except Exception as e:
            print(f"  Intento {intentos + 1} fallido: {e}")
        intentos += 1

        # Parpadear el LED en cada intento para indicar que está tratando de conectar

        for a in ACTUADORES:
            a["io"].value = not a["io"].value
        time.sleep(0.5)


    if wifi.radio.connected:
        set_todos_actuadores(False) # apagar el LED cuando ya conectó
        print(f"WiFi conectado: {wifi.radio.ipv4_address}")
        return True


    print("ERROR: no se pudo conectar al WiFi")
    return False


def obtener_humedad(requests, nombre, lat, lon):
    """Consulta la API de Open-Meteo con la latitud y longitud de una ciudad
    y devuelve el porcentaje de humedad actual. Si hay error, devuelve None."""

    # Construir la URL con los parámetros de la ciudad
    # La API espera latitud, longitud y el parámetro que queremos (humedad relativa)

    url = (
        f"{OWM_BASE_URL}"
        f"?latitude={lat}"
        f"&longitude={lon}"
        f"&current=relative_humidity_2m" # pedir solo la humedad actual
)
    try:
        res   = requests.get(url)          # hacer la petición a internet
        datos = res.json()                 # convertir la respuesta de texto a diccionario
        res.close()                        # cerrar la conexión para no sobrecargar
        humedad = datos["current"]["relative_humidity_2m"]  # extraer el dato de humedad
        print(f"  {nombre}: {humedad}%")
        return humedad
    except Exception as e:
        # Si algo falla (sin internet, API caída, etc.), avisa y sigue con la siguiente ciudad
        print(f"  {nombre}: error → {e}")
    return None  # devolver None indica que no se pudo obtener el dato



# FUNCIÓN PRINCIPAL


def publicar_todas(requests, mqtt):

# """Recorre el array de ciudades, obtiene la humedad de cada una
#    y la publica en su feed de Adafruit IO. El LED permanece encendido
#   durante todo el proceso y se apaga al terminar."""

    print("\n── Iniciando ciclo de publicación ──")
    set_todos_actuadores(True)   # encender el LED para indicar que está enviando datos

# Verificar conexión MQTT antes de empezar — si se cayó, reconectar

    if not mqtt.is_connected():
        try:
            mqtt.connect()
            print("MQTT conectado a Adafruit IO")
        except Exception as e:
            print(f"Error MQTT: {e}")
            set_todos_actuadores(False) # apagar el LED si no se pudo conectar
            return # salir de la función sin publicar nada


    # Recorrer el array CIUDADES con un for.
    # Cada vuelta del bucle procesa una ciudad distinta:
    # obtiene su humedad y la publica en su feed de Adafruit IO.

    for nombre, lat, lon, feed in CIUDADES:
        humedad = obtener_humedad(requests, nombre, lat, lon) # consultar la API
        if humedad is not None:   # si se obtuvo el dato correctamente
            topic = f"{AIO_USER}/feeds/{feed}" # construir la dirección completa del feed
            try:
                mqtt.publish(topic, str(humedad))
                print(f"  → Publicado {feed}: {humedad}%") # publicar el dato como texto
            except Exception as e:
                print(f"  → Error publicando {feed}: {e}")
        time.sleep(0.5) # esperar medio segundo entre ciudades para no saturar la API


    set_todos_actuadores(False)  # apagar el LED al terminar el ciclo
    print("── Ciclo completado ──\n")


# Setup


if not conectar_wifi():
    while True:
        parpadeo_actuadores(intervalo=0.2)


pool     = socketpool.SocketPool(wifi.radio)
requests = adafruit_requests.Session(pool, ssl.create_default_context())


mqtt = MQTT.MQTT(
    broker=AIO_BROKER,
    port=AIO_PORT,
    username=AIO_USER,
    password=AIO_KEY,
    socket_pool=pool,
)


try:
    mqtt.connect()
    print("MQTT conectado a Adafruit IO")
except Exception as e:
    print(f"Error MQTT inicial: {e}")


print("Sistema listo! Mueve el switch para publicar los datos de humedad.")


# Loop principal

# Guardar el último estado conocido de cada s en una lista.
# Empieza en True porque con Pull.UP el estado inicial (sin presionar) es True.
# Hay un elemento por cada sensor en la lista SENSORES.

ultimo_estado = [True] * len(SENSORES)

# Tiempo de espera entre lecturas del switch para evitar rebotes.


DEBOUNCE_SEG  = 0.05 # 0.05 segundos descanso

while True:
    time.sleep(DEBOUNCE_SEG) # pausa petit para estabilizar la lectura


    # Leer todos los sensores con bucle

    for i, s in enumerate(SENSORES):
        estado_actual = s["io"].value   # False = ON, True = OFF


        # Switch recién activado (OFF → ON)
        if not estado_actual and ultimo_estado[i]:
            print(f"[{s['nombre']}] activado → publicando datos...")
            publicar_todas(requests, mqtt)


        # Switch apagado
        if estado_actual and not ultimo_estado[i]:
            set_todos_actuadores(False)
            print(f"[{s['nombre']}] apagado.")


        ultimo_estado[i] = estado_actual

