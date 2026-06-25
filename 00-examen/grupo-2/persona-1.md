# ‧₊˚✧ Investigaciones individuales ✧˚₊‧

Lunes 22 Junio 2026 - [Camila Parada](https://github.com/Camila-Parada)

***

(_Estas son las investigaciones para el proyecto Acu-Visual_)

## Introducción

La propuesta inicial fue dada por parte de Vania. Al yo haberle propuesto el encargo anterior acepté a hacer algo que fuera más de su interés.
En un inicio nos surgió el interés de captar información en vivo, por lo que el sonido es un "recurso" venidero y temporal: aparece a partir de una presencia (humano, animal, máquina autónoma, etc), tiene una duración y en el cotidiano no se guardan registros. Una dimensión que a su vez se usa continuamente para la comunicación, pero pasa desapercibida.

Ante ello es que tomamos la decisión de captar ruidos y sonidos sin discriminar el tipo de información que entra. Para ello requerimos de sensores capaces de recoger estos datos ambientales a la par de un computador con Touchdesigner, el programa utilizado para la creación de la visualización.
Este último es un software que, personalmente, conozco por información asociada a proyectos más que por experiencia y manejo. Por ello consideré que mi aporte sería muy poco en este ámbito (recepción y traducción de información) y decidí el apoyar al proyecto en la investigación enfocada en el sensor y conversión de datos.

### En un inicio: ¿KY-037 o KY-038?

En un comienzo se consiguió un sensor del laboratorio de interacción digital, tratándose de un módulo que posee un circuito con un potenciómerto en conjunto con un micrófono. Desconozco el tipo de sensor que era, dado que no poseía nombre en la placa, pero se asemejaba al KY-037.

Pese a las dudas, con este módulo surgieron los primeros intentos para captar información sonora a través de la raspberry pi pico 2w. 
Para poder asegurarnos que el módulo se centrara en obtener de sonido ambiental, es que decidí adquirir este producto de Afel basándome en su descripción: [“Sensor de Sonido Analógico Digital KY-038”](https://afel.cl/products/sensor-de-sonido-analogico-digital).

<img width="1920" height="875" alt="modulo_ky_38" src="https://github.com/user-attachments/assets/279722ea-9950-4119-ba9a-5311ede09b6a" />

Ya al momento de trabajar con código es que trabajé en conjunto con la ia de [Claude](https://github.com/Camila-Parada/dis9079-2026-1/blob/main/00-examen/grupo-2/ia/claude-cami.pdf), preguntándole acerca de cuál era el mejor módulo a usar entre los que tenía y pidiendole un código de prueba para probar los módulos.

```cpp
import time
import board
import analogio
import digitalio

# Configuración de pines
analog_in = analogio.AnalogIn(board.GP26)   # Señal analógica (volumen)
digital_in = digitalio.DigitalInOut(board.GP15)  # Señal digital (umbral)
digital_in.direction = digitalio.Direction.INPUT

def get_voltage(pin):
    # Convierte el valor ADC (0-65535) a voltaje (0-3.3V)
    return (pin.value * 3.3) / 65535

while True:
    voltage = get_voltage(analog_in)
    digital = digital_in.value

    print(f"Voltaje: {voltage:.3f}V | Sonido detectado: {digital}")
    time.sleep(0.1)
```

Tras este primer intento (siguiendo los pasos indicados) fui mostrandole los resultados a la ia, para poder ir verificando si el funcionamiento del módulo era el esperado. Tras algunas ideas, es que decidí el pedirle a la ia que agregara un sistema de calibración y un tiempo para aplicarlo con la finalidad de primero detectar el sonido ambiente y establecer un valor promedio a registrar. 

Tras varios errores y problemas con respecto a este módulo, se llegó a un punto en el que fue necesario cambiar de sensor de audio dada las limitantes de estos módulos, dado que pese a contar con amplificadores incluidos sólo podían detectar sonido para "activar o desactivar" similar al funcionamiento de un botón.

Para ello, Claude me entrego un listado de sensores que podían servir para el proyecto.

| Módulo | Amplificador | Rango dinámico | Precio aprox | Ideal para |
| ------ | ------------ | -------------- | ------------ | ---------- |
| MAX4466 | Sí, ganancia ajustable | Muy amplio~ | $3–5 USD | Nivel de sonido ambiente |
| MAX9814 | Sí, AGC automático | Excelente~ | $5–8 USD | Ambientes con ruido variable |
| INMP441 | Digital I2S | Excelente~ | $3–6 USD | Alta precisión, sin ruido |
| ADCSPH0645 | Digital I2S | Excelente~ | $5–8 USD | Similar al INMP441 |

De todas las alternativas, me sugirió usar el "MAX9814". 

Entre la búsqueda de dicho sensor di con la variante "MAX9812" en la tienda ["hubot"](https://hubot.cl/).
Tras una consulta rápida me dio el visto bueno para usar la pieza en el proyecto.

***

### [MAX9812]( https://hubot.cl/producto/sensor-analogico-audio-max9812-sku-614/)


<img width="1920" height="860" alt="modulo_max9812" src="https://github.com/user-attachments/assets/cce5be45-1c34-4538-97e8-de3609999e37" />


Con el sensor adquirido, procedí a consultar sobre cómo hacer las conexiones y pedirle el código anterior, pero modificado.

| Pin MAX9812 | Pin Pico 2W |
| ----------- | ----------- |
| VCC | 3V3 (Pin 36) |
| GND | GND (Pin 38) |
| OUT | GP26 (Pin 31) |

```cpp
import time
import board
import analogio

analog_in = analogio.AnalogIn(board.GP26)

def get_voltage(pin):
    return (pin.value * 3.3) / 65535

# --- CALIBRACIÓN AUTOMÁTICA ---
print("Calibrando... No hagas ruido por 2 segundos")
time.sleep(0.5)

muestras = []
inicio = time.monotonic()

while time.monotonic() - inicio < 2.0:
    muestras.append(analog_in.value)
    time.sleep(0.05)  # ~40 muestras en 2s

promedio = sum(muestras) / len(muestras)
maximo = max(muestras)

print(f"Muestras tomadas: {len(muestras)}")
print(f"Promedio ambiente: {promedio:.0f}")
print(f"Máximo ambiente: {maximo}")
print(f"Umbral sugerido: {promedio * 1.3:.0f}  (promedio + 30%)")
print("--- Calibración lista ---")

UMBRAL = promedio * 1.3

# --- LOOP PRINCIPAL ---
while True:
    raw = analog_in.value
    voltage = get_voltage(analog_in)
    nivel = int((raw / 65535) * 100)
    sonido = raw > UMBRAL

    print(f"Voltaje: {voltage:.3f}V | Raw: {raw} | Nivel: {nivel}% | Sonido: {sonido}")
    time.sleep(0.1)
```

Tras tener inconvenientes con la "calibración", los "umbrales" y el "envío de información en tiempo real" es que decidí pedirle una serie de modificaciones al código. A la par, la ia me sugirió crear un visualizador web (usando "html" como código base) que se conecta la placa mediante una solicitud de conexión al puerto del computador.

El resultado de una serie de cambios, modificaciones y demás acciones registradas en el documento ["claude-cami.pdf"](https://github.com/Camila-Parada/dis9079-2026-1/blob/main/00-examen/grupo-2/ia/claude-cami.pdf), entregó un código para la placa y el [visualizador web](https://github.com/Camila-Parada/sound-plotter) modificado para mostrar información.

#### Código resultante

```cpp
import time
import board
import analogio
import wifi
import socketpool
import adafruit_minimqtt.adafruit_minimqtt as MQTT

analog_in = analogio.AnalogIn(board.GP26)

# --- CREDENCIALES (reemplaza con las tuyas) ---
WIFI_SSID     = "nombre_de_tu_red"
WIFI_PASSWORD = "contraseña_wifi"

AIO_USERNAME  = "tu_usuario_adafruit"
AIO_KEY       = "tu_aio_key"
AIO_FEED      = AIO_USERNAME + "/feeds/espacio.modulo-a"  # modulo-b para el segundo módulo

# --- CONFIGURACIÓN ---
VENTANA = 50          # muestras para el promedio móvil
SENSIBILIDAD = 1.4    # desviación respecto al promedio móvil
INTERVALO_ENVIO = 0.1 # publicar a Adafruit IO cada 0.1s (no saturar)

# --- WIFI ---
print("Conectando WiFi...")
wifi.radio.connect(WIFI_SSID, WIFI_PASSWORD)
print(f"IP: {wifi.radio.ipv4_address}")

pool = socketpool.SocketPool(wifi.radio)

# --- MQTT ---
mqtt_client = MQTT.MQTT(
    broker      = "io.adafruit.com",
    port        = 1883,
    username    = AIO_USERNAME,
    password    = AIO_KEY,
    socket_pool = pool,
)

def conectar_mqtt():
    print("Conectando MQTT...")
    mqtt_client.connect()
    print("MQTT conectado")

conectar_mqtt()

# --- BUFFER CIRCULAR ---
buffer = [0] * VENTANA
idx = 0
suma = 0

print("Iniciando...")
for i in range(VENTANA):
    buffer[i] = analog_in.value
    suma += buffer[i]
    time.sleep(0.001)
print("LISTO")

ultimo_envio = time.monotonic()

# --- STREAM EN VIVO ---
while True:
    try:
        raw = analog_in.value

        # Promedio móvil de las últimas VENTANA lecturas
        suma -= buffer[idx]
        buffer[idx] = raw
        suma += raw
        idx = (idx + 1) % VENTANA
        promedio_movil = suma / VENTANA

        # Desviación respecto al promedio reciente
        if promedio_movil > 0:
            ratio = raw / promedio_movil
        else:
            ratio = 1.0

        es_anomalia = ratio > SENSIBILIDAD

        # Nivel normalizado (0-100)
        if es_anomalia:
            nivel = int((ratio - SENSIBILIDAD) / (4.0 - SENSIBILIDAD) * 50) + 50
            nivel = max(50, min(100, nivel))
        else:
            nivel = int((ratio - 0.5) / (SENSIBILIDAD - 0.5) * 49)
            nivel = max(0, min(49, nivel))

        base_norm = int((promedio_movil / 65535) * 100)
        payload = f"{nivel},{int(es_anomalia)},{base_norm}"

        # Imprimir local (para el visualizador web por USB)
        print(payload)

        # Publicar en Adafruit IO cada INTERVALO_ENVIO segundos
        ahora = time.monotonic()
        if ahora - ultimo_envio >= INTERVALO_ENVIO:
            mqtt_client.publish(AIO_FEED, payload)
            ultimo_envio = ahora

        # Mantener viva la conexión MQTT
        mqtt_client.loop(timeout=0.01)

        time.sleep(0.001)

    except Exception as e:
        print(f"Error: {e} - reconectando...")
        time.sleep(2)
        try:
            conectar_mqtt()
        except:
            pass
```

#### Página web

<img width="1456" height="735" alt="web_sound-plotter" src="https://github.com/user-attachments/assets/68c71520-d8cb-4c4b-8ae0-029b8764095d" />

### Continuación

Tras todos estos avances, pues al llegar a la clase me di cuenta que Vania ya tenía su propio código, por lo que decidimos realizar algunos ajustes a la versión que captara mejor información, quedandonos con la versión de Vania pero con modificaciones de mi código.

Tras ello sólo hubo que ponerle a prueba. Aunque, en un momento una placa tuvo inconvenientes con la conexión de internet, por lo que opté a pedir una placa extra a Mateo para seguir trabajando y resetear la placa problemática.

Para ello tuve que pillar un archivo "_nuke_" que se suele utilizar para borrar todo el contenido e información del "pi pico 2 w", dejándola de fábrica. Dentro de la investigación  encontré un proyecto de un ["_nuke_ de tipo universal"](https://github.com/Gadgetoid/pico-universal-flash-nuke), puesto que para formatear la placa suele usarse un archivo en específico según el tipo de placa.

Ya con nuestra placa lista sólo la configuré nuevamente, le agregué las librerías utilizadas y el código final. Tras ponerlo a prueba funcionó de forma correcta.

### Foto placa

<img width="1280" height="1009" alt="placa_acu-visual" src="https://github.com/user-attachments/assets/d5a5319e-a6d4-4c79-9669-9f5feaef1d85" />

### Mini-case

Para la última parte del proyecto, tuve el interés de desarrollar una mini carcasa a partir de un [modelo 3D existente](https://www.printables.com/model/1368704-raspberry-pi-pico-case-1-2-wireless/files). Lo que pude hacer por tiempo fue adaptar la carcasa para que no tuviera inconvenientes en encajar.

<img width="1920" height="1021" alt="case_raspberry-pi-pico-2w" src="https://github.com/user-attachments/assets/b437a7dc-1540-44ed-ac7e-a31aca006c78" />

