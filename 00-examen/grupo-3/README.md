# grupo-3

* Josefa Cristina Araya Cartes / [josefa-kristina](<https://github.com/disenoUDP/dis9079-2026-1/tree/main/05-josefa-kristina>)
* Débora Skarlett Soto Valenzuela / [DebSkar](<https://github.com/disenoUDP/dis9079-2026-1/tree/main/26-DebSkar>)
* Nicolás Elías Valdés Greve / [nicolasvaldesgreve](<https://github.com/disenoUDP/dis9079-2026-1/tree/main/28-nicolasvaldesgreve>)
* Cristóbal Vergara Silva / [cristobalvergarasilva](<https://github.com/disenoUDP/dis9079-2026-1/tree/main/29-cristobalvergarasilva>)

---


# Bruma compacta

Chile es un territorio con climas muy distintos el uno con el otro, en algunas localidades puede llegar a ser muy desértico mientras en el otro extremo del país existen bosques frondosos y ríos que demuestran la riqueza ecosistémica de nuestro país.
Nos parece interesante crear una experiencia donde por medio de componentes electrónicos y programación se pueda sentir que interactuamos con nuestro patrimonio natural, por eso es que a través de nuestro proyecto queremos provocar una escena inmersiva entre el agua y el usuario, reinterpretando el clima de 8 localidades distintas de Chile, totalmente al azar con la intención de utilizar datos concretos para generar una instancia divertida.


El punto de partida para materializar nuestro proyecto fue conectar una Raspberry Pi Pico 2W en una protoboard, junto a un switch que activa el envío de datos y un LED que indica cuándo el microcontrolador está conectado al WiFi y transmitiendo información. Usamos el terminal serial de PuTTY para ver los prints.

En este proceso de envío se recopila información climática desde la API de [Open Weather Map](<https://openweathermap.org/>), donde seleccionamos 8 ciudades de Chile distribuidas a lo largo del territorio: Arica, Copiapó, Santiago, Valparaíso, Isla de Pascua, Juan Fernández, Punta Arenas y Villa Las Estrellas en la Antártica. Los porcentajes de humedad de cada localidad se almacenan en un array de 8 posiciones (una por ciudad) y se publican en Adafruit IO a través de feeds individuales, también recorridos con un for.

Para armar el código, utilizamos **arrays**  que son como listas ordenadas de datos las que nos permiten manejar las 8 ciudades y sus valores de humedad eficientemente en lugar de tener que escribir el mismo código ocho veces, para utilizar los arrays un **for** recorre cada ciudad automáticamente y realiza la misma operación para todas: consultar la API, guardar el dato y publicarlo. 

Estos datos son recibidos por un Arduino UNO R4 WiFi, que también utiliza arrays para gestionar los 8 feeds simultáneamente: suscribirse a todos, esperar que lleguen los 8 valores y confirmar cada recepción encendiendo el LED correspondiente en un módulo RGB de 8 bits. Una vez llegados los datos de las 8 ciudades el Arduino ejecuta el sorteo.

El resultado se muestra en el módulo LED, mientras la Raspberry recopila los porcentajes, se iluminan todos los LED en azul, luego comienza a funcionar como una ruleta que barre los 8 LEDs en secuencia, frenando gradualmente hasta detenerse en la ciudad ganadora. La ruleta, sostenida por un mago, ilumina ese LED en verde si la humedad de la ciudad supera el 35%, o en rojo si es inferior. Una serie de letreros indica al usuario que si la luz es verde puede presionar el botón del humidificador, activando una membrana ultrasónica que libera una bruma en el espacio.

---

# API utilizada

###### Página web de Open Meteo

<img src="./imagenes/open-meteo.png" alt="install" width="500">




Open Meteo es una API de código abierto y gratuita, nos permite tener acceso a los datos meteorológicos globales, es decir, los datos están disponibles para cualquier coordenada del mundo. Las APIs que nos ofrece incluyen información como:

Condiciones meteorológicas actuales
Datos sobre el clima marítimo 
Pronósticos por hora y diarios
Perspectivas a corto y largo plazo
Alerta de inundaciónes
Más de 47 años de observaciones históricas
Archivos históricos de pronósticos
Datos estadísticos sobre el clima 
Datos sobre la calidad del aire
Información sobre la radiación satelital 

Algo que diferencia a Open Meteo API es que dan los créditos correspondientes a los medios donde recopilan sus datos climáticos y son totalmente transparentes con su código base, la gracia de esto es que cualquier persona pueda desarrollar su propio sistema rapidamente

Los servicios de Open Meteo se ofrecen a través de _API REST_ con respuestas _JSON_ estructuradas, adecuadas para su integración en entornos web, móviles, análisis, IoT y empresariales.

> **API REST**: Interfaz de programación de aplicaciones que sigue los principios de REST, el cual significa transferencia de estado representacional y consiste en un conjunto de reglas y recomendaciones para diseñar una API web.
Fuente: <https://www.redhat.com/es/topics/api/what-is-a-rest-api> 

> **JSON**: Formato ligero de intercambio de datos, basado en un subconjunto del lenguaje JavaScript.
Fuente: <https://www.json.org/json-es.html>


---

# Proceso 

Durante la primera clase de avance en examen, se nos indicó realizar un párrafo descriptivo (conceptual, no técnico) de lo que queríamos lograr con nuestro proyecto. La razón por la que se hizo esta actividad fue para poder recibir dudas y críticas de otros compañeros, para así lograr hacer la versión mejorada de este texto en base a su retroalimentación.

El párrafo inicial fue el siguiente:

“Bruma compacta: Queremos expresar y materializar el clima a través de un humidificador alimentado de los datos de humedad en el ambiente (datos de un API), provocando una escena inmersiva entre el agua y el usuario.” 

Luego de enviar el texto, nuestros compañeros del grupo 9 realizaron las siguientes preguntas en donde se muestran sus respectivas respuestas:

P1: Cuando dicen en el ambiente, sería el ambiente donde están físicamente? o un lugar random que la api les haya dado?

R1: De un lugar aleatorio pero de Chile.

P2: A que se refieren con materializar el clima?

R2: Con materializar el clima nos referíamos a que sería una demostración más literal y concentrada de la humedad al que el humidificador expulse una bruma de agua.

P3: Ese lugar aleatorio es siempre el mismo? o cambia cada vez que alguien interactúa con el proyecto?

R3: Cambiaría cada vez.

### Pseudocódigo

Para poder entender lo que haría nuestro código, se nos recomendó hacer un pseudocódigo que mencione de manera simplificada lo que harían nuestros códigos de enviar y recibir, en donde el resultado fue el siguiente:

#### RASPBERRY

```ccp
código enviar: 

Verificar si Wi Fi conectado
Verificar si API está funcionando
Verificar conexión con la nube

Nombre WIFI
Contraseña WIFI
User nube 
Contraseña nube
interruptor
LEDS

Al mover el interruptor de la izq a la derecha se encienden leds y empieza a enviar la información de la API al arduino a través de aio

Envía la información de la humedad de 8 ciudades de Chile

Arica
Copiapó
Santiago
Valparaíso
Isla de Pascua
Juan Fernández
Punta Arenas
Antártica

deja de enviar información al girar el interruptor de derecha a izq
```

#### ARDUINO

```ccp
código recibir:


Definir módulo led
Definir pantalla
Definir humidificador
Verificar si Wi Fi conectado
Verificar si API está funcionando
Verificar conexión con la nube

Definir componentes conectados al arduino


Recibir información de la humedad de las 8 ciudades
asignarle un valor y relacionarlo a un led del módulo

Con dado digital elegir al azar un valor y encender el led correspondiente de la ciudad
detectar el porcentaje de humedad del lugar y mostrarlo en monitor serial
reiniciar y esperar nueva información
```

Luego de crear nuestros pseudocódigos, nos dedicamos a buscar APIs que nos dieran datos meteorológicos para poder detectar la humedad de distintos lugares de Chile, en donde descubrimos una API de [Dirección Meteorológica de Chile](<https://www.meteochile.gob.cl/PortalDMC-web/index.xhtml>), la cual utilizamos durante los primeros intentos de código pero que luego tuvimos que cambiar debido a que esta solo contiene la información meteorológica de una cantidad reducida de ciudades de Chile, y no se encontraban todas las que queríamos mencionar. Como no nos funcionaba con lo que queríamos, estuvimos buscando otras APIs que den datos meteorológicos y logramos encontrar la que estamos usando actualmente:  [Open Weather Map](<https://openweathermap.org/>).

En este punto como ya habíamos solucionado el tema de la API, decidimos probar códigos con los componentes que teníamos pensados utilizar en este proyecto los cuales eran los siguientes:

Módulo RGB LED de 8 bits 5050

Módulo LCD 1602 con interfaz I2C

KIT humidificador USB M020

Push button 4 pines

LED 5mm

<img src="./imagenes/pedido-componentes1.jpeg" alt="install" width="500">

## Prompts creados para claude AI

Luego de crear nuestro pseudocódigo, decidir los componentes y elegir la API, creamos los siguientes prompts para pedirle ayuda a Claude AI:

#### Prompt 1 

Primero decidimos redactar un panorama completo de lo que era nuestro proyecto hasta ese entonces, asi que le escribimos lo siguiente:

Queremos conectar una Raspberry Pi Pico 2 W con un Botón push 4 pines y una luz led

Necesitamos que nuestro código de python use OpenWeatherMap y que en Adafruit IO use un feed por ciudad (ciudades: Arica, Copiapó, Santiago, Valparaíso, Isla de Pascua, Juan Fernández, Punta Arenas, Antártica) y la Raspberry Pi Pico 2W publicará en esos feeds los datos de la humedad. El botón se usaría para empezar a enviar los datos y la luz led para mostrar que se están enviando.

Recibiendo estaría un Arduino UNO R4 WiFi conectado a un Módulo RGB led de 8 bits 505 (cada led representaría una ciudad) sorteará los datos de las ciudades mediante un dado digital mostrando este sorteo en el modulo rgb tipo una ruleta, se iluminarán de manera aleatoria las luces y se detendrá en una indicando la ciudad seleccionada la cual según el porcentaje de humedad actuará el KIT Humidificador USB (Placa de control para humidificador y membrana ultrasónica) todas estas conecciones en una Protoboard 400 puntos, esto pero con putty, en 115200 bauds y en circuitpython

#### Respuesta 1
Lado emisor (Raspberry Pi Pico 2 W, CircuitPython):

Botón presiona → enciende LED → se conecta a WiFi → consulta OpenWeatherMap para las 8 ciudades → publica cada humedad en su feed de Adafruit IO → apaga LED.

Lado receptor (Arduino UNO R4 WiFi):

Se suscribe a los 8 feeds vía MQTT → cada cierto tiempo corre la animación de "ruleta" en el módulo RGB de 8 LEDs (barrido que va frenando hasta caer en una ciudad al azar) → revisa la humedad de esa ciudad → si es mayor a 35%, activa el humidificador a través del transistor/relé.

Pico 2 W: botón en GP15, LED en GP16

Arduino: módulo RGB en D2, control del relé (vía transistor) en pin 5, igual a como ya lo tenías armado

Created 2 files, ran a command
Created 2 files, ran a command

Ahora el receptor en el Arduino UNO R4 WiFi:

Created a file, ran a command, read a file
Created a file, ran a command, read a file

Cómo instalarlo:

Pico 2 W: copia code.py a la raíz del Pico, renombra settings_example.toml a settings.toml, complétalo con tus credenciales reales, y copia en /lib las librerías adafruit_requests, adafruit_io (carpeta completa) y adafruit_connection_manager desde el bundle de CircuitPython.

Arduino UNO R4 WiFi: instala desde el Library Manager Adafruit MQTT Library y Adafruit NeoPixel, completa SSID/password y usuario/key de Adafruit IO arriba del archivo, y sube el sketch.

Verifica los nombres de feed: en el código asumí que tus 8 feeds se llaman arica, copiapo, santiago, valparaiso, isla-de-pascua, juan-fernandez, punta-arenas, antartica. Si en Adafruit IO los nombraste distinto, son fáciles de cambiar en el diccionario CIUDADES (Pico) y el arreglo FEEDS_CIUDADES (Arduino).

Pines: botón en GP15 y LED en GP16 del Pico; módulo RGB en D2 y relé en pin 5 del Arduino (igual al transistor/relé que ya tenías armado). Si tu protoboard usa otros pines, son una sola línea para cambiar arriba de cada archivo.

Como hago las conexiones?

Transistor BC547 (o 2N2222):

Base → resistencia 10kΩ → pin D2 del Arduino

Emisor → GND Arduino

Colector → pad SW1 del botón en la placa del humidificador

El otro pad del botón (SW2) → GND Arduino (cierra el circuito del switch)

Alimentación del humidificador:

Pin +5V de la placa → fuente externa 5V (recomendado) o pin 5V del Arduino si tu fuente lo soporta

GND de la placa → GND común

# Codigos sugeridos por Claude

Raspberry pi, envío 
```ccp
# ===================================================================
# EMISOR - Raspberry Pi Pico 2 W (CircuitPython)
# Lee humedad de 8 ciudades desde OpenWeatherMap y la publica en
# 8 feeds de Adafruit IO. Botón inicia el envío, LED indica actividad.
# ===================================================================
#
# LIBRERÍAS NECESARIAS (copiar en /lib desde el bundle de CircuitPython):
#   adafruit_requests.mpy
#   adafruit_io/  (carpeta completa, incluye adafruit_io.mpy)
#   adafruit_connection_manager.mpy
#
# CREDENCIALES: van en settings.toml (no en este archivo), ver el
# archivo settings_example.toml que te dejo aparte.
 
import time
import os
import board
import digitalio
import wifi
import socketpool
import ssl
import adafruit_requests
from adafruit_io.adafruit_io import IO_HTTP, AdafruitIO_RequestError
 
# ---------------- CONFIGURACIÓN ----------------
 
BOTON_PIN = board.GP15      # Botón push 4 pines (a GND, con pull-up interno)
LED_PIN = board.GP16        # LED indicador de envío
 
# Pausa entre envíos de ciudades distintas (para no saturar la API)
PAUSA_ENTRE_CIUDADES = 1.5
 
# Después de terminar una ronda, cuánto esperar antes de permitir otra
ANTI_REBOTE_RONDA = 5
 
OPENWEATHER_API_KEY = os.getenv("OPENWEATHER_API_KEY")
AIO_USERNAME = os.getenv("AIO_USERNAME")
AIO_KEY = os.getenv("AIO_KEY")
 
# Nombre del feed en Adafruit IO + coordenadas para OpenWeatherMap
CIUDADES = {
   "Arica":          {"feed": "arica",         "lat": -18.4783, "lon": -70.3126},
   "Copiapo":        {"feed": "copiapo",        "lat": -27.3668, "lon": -70.3322},
   "Santiago":       {"feed": "santiago",       "lat": -33.4489, "lon": -70.6693},
   "Valparaiso":     {"feed": "valparaiso",      "lat": -33.0472, "lon": -71.6127},
   "Isla de Pascua": {"feed": "isla-de-pascua", "lat": -27.1127, "lon": -109.3497},
   "Juan Fernandez": {"feed": "juan-fernandez", "lat": -33.6333, "lon": -78.8333},
   "Punta Arenas":   {"feed": "punta-arenas",   "lat": -53.1638, "lon": -70.9171},
   "Antartica":      {"feed": "antartica",      "lat": -62.2167, "lon": -58.9667},
}
 
# ---------------- HARDWARE ----------------
 
boton = digitalio.DigitalInOut(BOTON_PIN)
boton.direction = digitalio.Direction.INPUT
boton.pull = digitalio.Pull.UP  # botón a GND -> presionado = False
 
led = digitalio.DigitalInOut(LED_PIN)
led.direction = digitalio.Direction.OUTPUT
led.value = False
 
# ---------------- RED ----------------
 
def conectar_wifi():
   if wifi.radio.connected:
       return
   print("Conectando a WiFi...")
   wifi.radio.connect(os.getenv("CIRCUITPY_WIFI_SSID"), os.getenv("CIRCUITPY_WIFI_PASSWORD"))
   print("WiFi conectado, IP:", wifi.radio.ipv4_address)
 
pool = socketpool.SocketPool(wifi.radio)
requests = adafruit_requests.Session(pool, ssl.create_default_context())

io = None  # se inicializa después de conectar wifi
 
def conectar_adafruit_io():
   global io
   if io is None:
       io = IO_HTTP(AIO_USERNAME, AIO_KEY, requests)
       print("Adafruit IO listo")
 
# ---------------- LÓGICA ----------------
 
def obtener_humedad(lat, lon):
   url = (
       "https://api.openweathermap.org/data/2.5/weather"
       "?lat={}&lon={}&units=metric&appid={}".format(lat, lon, OPENWEATHER_API_KEY)
   )
   try:
       respuesta = requests.get(url)
       datos = respuesta.json()
       respuesta.close()
       return datos["main"]["humidity"]
   except Exception as e:
       print("Error consultando clima:", e)
       return None
 
def enviar_ronda():
   led.value = True
   conectar_wifi()
   conectar_adafruit_io()
 
   for nombre, info in CIUDADES.items():
       humedad = obtener_humedad(info["lat"], info["lon"])
       if humedad is not None:
           try:
               feed = io.get_feed(info["feed"])
               io.send_data(feed["key"], humedad)
               print("{}: {}% -> feed '{}' OK".format(nombre, humedad, info["feed"]))
           except AdafruitIO_RequestError as e:
               print("Error publicando en feed '{}':".format(info["feed"]), e)
       else:
           print("{}: sin dato, se omite".format(nombre))
 
       time.sleep(PAUSA_ENTRE_CIUDADES)
 
   led.value = False
   print("Ronda completa.\n")
 
# ---------------- LOOP PRINCIPAL ----------------
 
print("Listo. Presiona el botón para enviar humedad de las 8 ciudades.")
 
boton_anterior = True  # no presionado (pull-up)
 
while True:
   boton_actual = boton.value
 
   # Flanco de bajada: de no-presionado a presionado
   if boton_anterior and not boton_actual:
       print("Boton presionado, iniciando ronda...")
       enviar_ronda()
       time.sleep(ANTI_REBOTE_RONDA)
 
   boton_anterior = boton_actual
   time.sleep(0.05)
 ```


Settings example


```ccp


# settings.toml
# Este archivo va en la RAÍZ del Pico 2 W (junto a code.py).
# CircuitPython lo lee automáticamente con os.getenv().
# Completa tus datos reales y renómbralo (o cópialo) a "settings.toml".


CIRCUITPY_WIFI_SSID = "NOMBRE_DE_TU_RED"
CIRCUITPY_WIFI_PASSWORD = "CONTRASEÑA_DE_TU_RED"


OPENWEATHER_API_KEY = "TU_API_KEY_DE_OPENWEATHERMAP"


AIO_USERNAME = "TU_USUARIO_DE_ADAFRUIT_IO"
AIO_KEY = "TU_AIO_KEY"

```


#### Prompt 2

en este código se administra la info de los sensores y actuadores con arreglos y bucles (arrays y for)? de no ser así, haz que lo tenga 

#### Respuesta 2

Revisando tu código, ya usa arreglos y bucles en varios lugares clave:
CIUDADES es un arreglo (lista de tuplas) con las 8 ciudades y sus datos
for nombre, lat, lon, feed in CIUDADES: es el bucle que itera sobre ese arreglo en publicar_todas()
Sin embargo, los sensores/actuadores (switch y LED) están declarados como variables sueltas, sin estructura de arreglo ni bucle. Si el proyecto crece con más switches o LEDs, eso no escala bien.
Te propongo refactorizarlo para que también los actuadores y sensores usen arreglos y bucles:
Aquí está el código refactorizado. El cambio clave es que ahora los sensores y actuadores también se administran con arreglos y bucles, igual que las ciudades:
V
visualize
V
visualize show_widget
Y aquí el código refactorizado completo:
```ccp
import time
import wifi
import socketpool
import ssl
import board
import digitalio
import adafruit_requests
import adafruit_minimqtt.adafruit_minimqtt as MQTT

# ─── COMUNICACIÓN SERIAL ─────────────────────────────────────────────────────
BAUD_RATE = 115200
print(f"Baudios: {BAUD_RATE}")

# ─── CONFIGURACIÓN ───────────────────────────────────────────────────────────
WIFI_SSID     = "si"
WIFI_PASSWORD = "mailo-6192"

AIO_USER   = "nicolasvgreve"
AIO_KEY    = "aio_key"
AIO_BROKER = "io.adafruit.com"
AIO_PORT   = 1883

OWM_BASE_URL = "https://api.open-meteo.com/v1/forecast"

# Ciudades: (Nombre, latitud, longitud, nombre-del-feed)
CIUDADES = [
    ("Arica",               -18.48, -70.33,  "arica-humidity"),
    ("Copiapo",             -27.37, -70.33,  "copiapo-humidity"),
    ("Santiago",            -33.45, -70.67,  "santiago-humidity"),
    ("Valparaiso",          -33.05, -71.62,  "valparaiso-humidity"),
    ("Isla de Pascua",      -27.11, -109.35, "isla-pascua-humidity"),
    ("Juan Fernandez",      -33.65, -78.83,  "juan-fernandez-humidity"),
    ("Punta Arenas",        -53.16, -70.91,  "punta-arenas-humidity"),
    ("Villa Las Estrellas", -62.19, -58.98,  "antartica-humidity"),
]

# ─── HARDWARE ────────────────────────────────────────────────────────────────
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

# ─── HELPERS DE HARDWARE ─────────────────────────────────────────────────────

def set_todos_actuadores(valor: bool):
    """Enciende o apaga todos los LEDs del arreglo."""
    for a in ACTUADORES:
        a["io"].value = valor

def parpadeo_actuadores(n: int = 3, intervalo: float = 0.2):
    """Hace parpadear todos los LEDs n veces."""
    for _ in range(n):
        set_todos_actuadores(True)
        time.sleep(intervalo)
        set_todos_actuadores(False)
        time.sleep(intervalo)

def leer_sensores() -> list:
    """Devuelve lista de (nombre, valor) para cada sensor."""
    return [(s["nombre"], s["io"].value) for s in SENSORES]

# ─── FUNCIONES DE RED ────────────────────────────────────────────────────────

def conectar_wifi():
    print(f"Conectando a {WIFI_SSID}...")
    intentos = 0
    while not wifi.radio.connected and intentos < 20:
        try:
            wifi.radio.connect(WIFI_SSID, WIFI_PASSWORD)
        except Exception as e:
            print(f"  Intento {intentos + 1} fallido: {e}")
        intentos += 1
        # Parpadear todos los actuadores durante la conexión
        for a in ACTUADORES:
            a["io"].value = not a["io"].value
        time.sleep(0.5)

    if wifi.radio.connected:
        set_todos_actuadores(False)
        print(f"WiFi conectado: {wifi.radio.ipv4_address}")
        return True

    print("ERROR: no se pudo conectar al WiFi")
    return False

def obtener_humedad(requests, nombre, lat, lon):
    url = (
        f"{OWM_BASE_URL}"
        f"?latitude={lat}"
        f"&longitude={lon}"
        f"&current=relative_humidity_2m"
    )
    try:
        res = requests.get(url)
        datos = res.json()
        res.close()
        humedad = datos["current"]["relative_humidity_2m"]
        print(f"  {nombre}: {humedad}%")
        return humedad
    except Exception as e:
        print(f"  {nombre}: error → {e}")
    return None

# ─── FUNCIÓN PRINCIPAL ───────────────────────────────────────────────────────

def publicar_todas(requests, mqtt):
    print("\n── Iniciando ciclo de publicación ──")
    set_todos_actuadores(True)   # encender todos los LEDs

    if not mqtt.is_connected():
        try:
            mqtt.connect()
            print("MQTT conectado a Adafruit IO")
        except Exception as e:
            print(f"Error MQTT: {e}")
            set_todos_actuadores(False)
            return

    # Iterar sobre el arreglo de ciudades (ya existía)
    for nombre, lat, lon, feed in CIUDADES:
        humedad = obtener_humedad(requests, nombre, lat, lon)
        if humedad is not None:
            topic = f"{AIO_USER}/feeds/{feed}"
            try:
                mqtt.publish(topic, str(humedad))
                print(f"  → Publicado {feed}: {humedad}%")
            except Exception as e:
                print(f"  → Error publicando {feed}: {e}")
        time.sleep(0.5)

    set_todos_actuadores(False)  # apagar todos los LEDs
    print("── Ciclo completado ──\n")

# ─── SETUP ───────────────────────────────────────────────────────────────────

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

print("Sistema listo. Activa el switch para publicar datos.")

# ─── LOOP PRINCIPAL ──────────────────────────────────────────────────────────

ultimo_estado = [True] * len(SENSORES)   # un estado por sensor
DEBOUNCE_SEG  = 0.05

while True:
    time.sleep(DEBOUNCE_SEG)

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
```
Los cambios concretos que se hicieron:

SENSORES — arreglo de dicts con pin, pull, nombre e io (el objeto DigitalInOut se guarda ahí mismo al inicializar con un for).

ACTUADORES — igual: arreglo de dicts con pin, nombre e io.

Inicialización — dos bucles for configuran todos los pines al arrancar, en vez de hacerlo a mano variable por variable.

Helpers nuevos — set_todos_actuadores(), parpadeo_actuadores() y leer_sensores() operan sobre los arreglos, así cualquier función que necesite tocar el hardware no necesita saber cuántos hay.

Loop principal — ahora itera sobre SENSORES con for i, s in enumerate(SENSORES) y mantiene ultimo_estado como arreglo paralelo.

Para agregar un segundo LED o switch basta con añadir una línea al arreglo correspondiente, sin tocar ninguna otra función


#### Prompt 3

Este prompt lo hicimos luego de que desistieramos de usar el relé, el transistor y la pantalla:

Antes de que me digas algo necesito contextualizar lo que estoy haciendo; tenemos conectada una Raspberry Pi Pico 2 W con un interruptor switch de 3 pines y una luz led con un código de python con circuit python que te podemos enviar, este usa OpenWeatherMap y por Adafruit IO usa un feed por ciudad (ciudades: Arica, Copiapó, Santiago, Valparaíso, Isla de Pascua, Juan Fernández, Punta Arenas, Antártica) y la Raspberry Pi Pico 2W publicará en esos feeds los datos de la humedad. El switch se usa para empezar a enviar los datos y la luz led para mostrar que se están enviando. Recibiendo estaría un Arduino UNO R4 WiFi conectado a un Módulo RGB led de 8 bits 505 (cada led representa una ciudad) sortea los datos de las ciudades mediante un dado digital mostrando este sorteo en el módulo rgb tipo una ruleta, se iluminarán de manera aleatoria las luces y se detendrá en una indicando la ciudad seleccionada la cual según el porcentaje de humedad actuará el KIT Humidificador USB (Placa de control para humidificador y membrana ultrasónica) conectado directamente al Arduino r4 wifi
Te enviaré el código que estamos usando en Visual Studio Code, el switch se gira a un lado para enviar, por el arduino este activa el humidificador (Ahora el humidificador está conectado sólo a ground y cinco voltios.) por sobre el 35 porciento de humedad, el Arduino ya recibe los 8 feeds antes de sortear.
circuit python.

```ccp
import time
import wifi
import socketpool
import ssl
import board
import digitalio
import adafruit_requests
import adafruit_minimqtt.adafruit_minimqtt as MQTT

# ─── COMUNICACIÓN SERIAL ─────────────────────────────────────────────────────
# PuTTY → Connection type: Serial | Speed: 115200 | Puerto: COMx
BAUD_RATE = 115200
print(f"Baudios: {BAUD_RATE}")

# ─── CONFIGURACIÓN ───────────────────────────────────────────────────────────

WIFI_SSID     = "si"
WIFI_PASSWORD = "mailo-6192"

AIO_USER      = "AIO-USER"
AIO_KEY       = "aio_Key"
AIO_BROKER    = "io.adafruit.com"
AIO_PORT      = 1883

OWM_BASE_URL  = "https://api.open-meteo.com/v1/forecast"

# Ciudades: (Nombre, latitud, longitud, nombre-del-feed)
CIUDADES = [
    ("Arica",               -18.48, -70.33,  "arica-humidity"),
    ("Copiapo",             -27.37, -70.33,  "copiapo-humidity"),
    ("Santiago",            -33.45, -70.67,  "santiago-humidity"),
    ("Valparaiso",          -33.05, -71.62,  "valparaiso-humidity"),
    ("Isla de Pascua",      -27.11, -109.35, "isla-pascua-humidity"),
    ("Juan Fernandez",      -33.65, -78.83,  "juan-fernandez-humidity"),
    ("Punta Arenas",        -53.16, -70.91,  "punta-arenas-humidity"),
    ("Villa Las Estrellas", -62.19, -58.98,  "antartica-humidity"),
]

# ─── HARDWARE ────────────────────────────────────────────────────────────────

# Switch ON/OFF en GP14 con pull-up interna
# Switch ON  → GP14 conectado a GND → valor = False
# Switch OFF → GP14 desconectado    → valor = True (pull-up)
switch = digitalio.DigitalInOut(board.GP14)
switch.direction = digitalio.Direction.INPUT
switch.pull = digitalio.Pull.UP

# LED en GP16
led = digitalio.DigitalInOut(board.GP16)
led.direction = digitalio.Direction.OUTPUT
led.value = False

# ─── FUNCIONES DE RED ────────────────────────────────────────────────────────

def conectar_wifi():
    """Conecta al WiFi y devuelve True si tiene éxito."""
    print(f"Conectando a {WIFI_SSID}...")
    intentos = 0
    while not wifi.radio.connected and intentos < 20:
        try:
            wifi.radio.connect(WIFI_SSID, WIFI_PASSWORD)
        except Exception as e:
            print(f"  Intento {intentos + 1} fallido: {e}")
        intentos += 1
        led.value = not led.value   # parpadeo durante conexión
        time.sleep(0.5)

    if wifi.radio.connected:
        led.value = False
        print(f"WiFi conectado: {wifi.radio.ipv4_address}")
        return True

    print("ERROR: no se pudo conectar al WiFi")
    return False

def obtener_humedad(requests, nombre, lat, lon):
    """Consulta Open-Meteo y devuelve la humedad (int) o None."""
    url = (
        f"{OWM_BASE_URL}"
        f"?latitude={lat}"
        f"&longitude={lon}"
        f"&current=relative_humidity_2m"
    )
    try:
        res = requests.get(url)
        datos = res.json()
        res.close()
        humedad = datos["current"]["relative_humidity_2m"]
        print(f"  {nombre}: {humedad}%")
        return humedad
    except Exception as e:
        print(f"  {nombre}: error → {e}")
    return None

# ─── FUNCIÓN PRINCIPAL ───────────────────────────────────────────────────────

def publicar_todas(requests, mqtt):
    """Obtiene humedad de todas las ciudades y las publica en Adafruit IO."""
    print("\n── Iniciando ciclo de publicación ──")
    led.value = True

    # Reconectar MQTT si es necesario
    if not mqtt.is_connected():
        try:
            mqtt.connect()
            print("MQTT conectado a Adafruit IO")
        except Exception as e:
            print(f"Error MQTT: {e}")
            led.value = False
            return

    # Recorrer ciudades
    for nombre, lat, lon, feed in CIUDADES:
        humedad = obtener_humedad(requests, nombre, lat, lon)
        if humedad is not None:
            topic = f"{AIO_USER}/feeds/{feed}"
            try:
                mqtt.publish(topic, str(humedad))
                print(f"  → Publicado {feed}: {humedad}%")
            except Exception as e:
                print(f"  → Error publicando {feed}: {e}")
        time.sleep(0.5)

    led.value = False
    print("── Ciclo completado ──\n")

# ─── SETUP ───────────────────────────────────────────────────────────────────

if not conectar_wifi():
    while True:
        led.value = not led.value
        time.sleep(0.2)

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

print("Sistema listo. Activa el switch para publicar datos.")

# ─── LOOP PRINCIPAL ──────────────────────────────────────────────────────────

# True  = switch estaba OFF (pull-up activa)
# False = switch estaba ON  (conectado a GND)
ultimo_estado = True
DEBOUNCE_SEG  = 0.05

while True:
    # Pequeña pausa para estabilizar lectura del switch
    time.sleep(DEBOUNCE_SEG)
    estado_actual = switch.value   # False = ON, True = OFF

    # Switch recién activado (OFF → ON): publicar una vez
    if not estado_actual and ultimo_estado:
        print("Switch activado → publicando datos...")
        publicar_todas(requests, mqtt)

    # Switch apagado: apagar LED
    if estado_actual and not ultimo_estado:
        led.value = False
        print("Switch apagado.")

    ultimo_estado = estado_actual
```

#### Respuesta 3
Flujo completo
