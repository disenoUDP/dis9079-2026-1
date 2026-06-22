# persona-2

[Vania Paredes](https://github.com/paredesvania)

---

## Investigación

Primero probé un micrófono ( KY-037 )conectado a un arduino, para primero ver cómo funcionaban los datos de este en touchdesigner.

Así conecté el mic KY-037 al Arduino:

* VCC      ->   5V
* GND      ->   GND
* AO       ->   A0       (esta es la señal analógica del sonido)

Acá encontré la info para la conexión y detalles del microfono: <https://arduinomodules.info/ky-037-high-sensitivity-sound-detection-module/>

Usé este código para ver los datos del micrófono.

```cpp
const int MIC_PIN = A0;
const int MUESTRAS = 8;

int leerPromedio() {
  long suma = 0;
  for (int i = 0; i < MUESTRAS; i++) {
    suma += analogRead(MIC_PIN);
  }
  return suma / MUESTRAS;
}

void setup() {
  Serial.begin(9600);
  delay(1000);
}

void loop() {
  int nivel = leerPromedio();
  Serial.println(nivel);
  delay(30);
}
```

---

En touchdesigner primero hice una figura base simple que tuviera parámetros que pudiera deformar con el sonido, en este caso ocupé noise.

![foto](./imagenes/voice1.png)

Me vi este tutorial para ver como funcionaba la conexión arduino/touch designer: <https://www.youtube.com/watch?v=V_Q_fDukTI0>

Puse un serial DAT, y en este ajusté los parámetros para conectarlo a mi arduino, en este caso seleccionar el port y baud rate correctos. Se puede ver que me llegan datos, ahora debo limpiarlos para poder usarlos con más control en mi visual.

![foto](./imagenes/voice2.png)

Ajusté unos parámetros de mi visual para hacerla más estética. Hasta quedar satisfecha con el resultado, no quería hacer algo muy complicado visualmente, sino que enfocarme más en el código.

![foto](./imagenes/voice3.png)
![foto](./imagenes/voice4.png)

Me di cuenta que el micrófono no detecta tantos cambios en el sonido a no ser que se hagan muy cerca del micrófono, (rangos de 27 a 300) así que ajusté los parámetros para que aunque haya un cambio mínimo se note más.

![foto](./imagenes/voice5.png)

Seguía sin convencerme el diseño así que lo volví a cambiar

![foto](./imagenes/voice6.png)

Una vez esto me funcionaba empecé a investigar cómo podríamos conectar estos dos micrófonos de la manera más simple y eficiente a touchdesigner.

Hablé con claude, el prompt fué larguísimo así que dejo el link a la conversación: <https://claude.ai/share/908f5fc8-04b0-407a-ad07-761d9c147662>

Probé lo que me dijo claude:

Cuesta que se conecte al internet pero lo logra:

![foto](./imagenes/voice7.png)

Y se ve la info en el feed:

![foto](./imagenes/voice8.png)

Pero no logro hacer bien la conexión en touchdesigner para ver los datos;(.

![foto](./imagenes/voice9.png)

---

Ya lo logre!! funciona, pero aún hay problemas de conexión, cuesta que se conecte a internet y cuando se conecta se vuelve a desconectar.

![foto](./imagenes/voice10.png)
![foto](./imagenes/voice11.png)
![foto](./imagenes/voice12.png)

Mateo me ayudó con eso, me dijo que le pidió a chatgpt reforzar la conexión, este es el link de su conversación: <https://chatgpt.com/share/6a270e2e-6ed0-83e9-9219-f21ec0dc3f2f>

Y funciona!!!

![foto](./imagenes/voice13.png)

Ahora lo conecté a la cuenta de aaron, así no se me acaba tan rapido el límite de datos que puedo enviar a mi cuenta de adafruit. Los códigos finales que ocupé fueron:

## Código Raspberry

```python
# ============================================================
# SENSOR DE SONIDO — Raspberry Pi Pico 2W
# Examen interacciones inalámbricas
# ============================================================

import time
import board
import analogio
import wifi
import socketpool
import adafruit_minimqtt.adafruit_minimqtt as MQTT

# ============================================================
# CONFIGURACIÓN 
# ============================================================

EDIFICIO      = "grupo02-rep"
WIFI_SSID     = "iPhone de Mateo"
WIFI_PASSWORD = "aaron123"

# ============================================================
# ADAFRUIT IO
# ============================================================

AIO_USERNAME  = "udpmontoyamoraga"
AIO_KEY       = "secreto"
FEED          = f"{AIO_USERNAME}/feeds/{EDIFICIO}"

# ============================================================
# PARÁMETROS
# ============================================================

NUM_MUESTRAS  = 60
PAUSA_MS      = 0.001
INTERVALO_S   = 2.0

PINES_SENSORES = [board.GP26, board.GP27]

# ============================================================
# SENSORES
# ============================================================

sensores = [analogio.AnalogIn(pin) for pin in PINES_SENSORES]
buffers = [[0] * NUM_MUESTRAS for _ in sensores]

# ============================================================
# VARIABLES GLOBALES DE RED
# ============================================================

pool = None
mqtt_cliente = None

# ============================================================
# FUNCIONES WIFI / MQTT
# ============================================================

def estado_wifi():
    """
    Revisa si el WiFi sigue conectado.
    Retorna True si hay conexión, False si no.
    """
    try:
        return wifi.radio.connected
    except Exception:
        return False


def conectar_wifi():
    """
    Conecta o reconecta al WiFi con reintentos.
    """
    print(f"\nConectando a WiFi: '{WIFI_SSID}'")

    while not estado_wifi():
        try:
            wifi.radio.connect(WIFI_SSID, WIFI_PASSWORD)
            time.sleep(1)

            if estado_wifi():
                print("  ✓ WiFi conectado")
                print(f"  IP: {wifi.radio.ipv4_address}")

                try:
                    print(f"  RSSI: {wifi.radio.ap_info.rssi} dBm")
                except Exception:
                    pass

                return True

        except Exception as e:
            print(f"  ✗ Error WiFi: {e}")

        print("  Reintentando WiFi en 5 segundos...")
        time.sleep(5)

def crear_mqtt():
    """
    Crea un nuevo socketpool y un nuevo cliente MQTT.
    Esto es importante después de una caída de WiFi.
    """
    global pool, mqtt_cliente

    pool = socketpool.SocketPool(wifi.radio)

    mqtt_cliente = MQTT.MQTT(
        broker         = "io.adafruit.com",
        port           = 1883,
        username       = AIO_USERNAME,
        password       = AIO_KEY,
        socket_pool    = pool,
        socket_timeout = 1,
        keep_alive     = 30,
    )

def conectar_mqtt():
    """
    Conecta a Adafruit IO.
    Si falla, reintenta.
    """
    global mqtt_cliente

    if mqtt_cliente is None:
        crear_mqtt()

    while True:
        try:
            print("Conectando a Adafruit IO...")
            mqtt_cliente.connect()
            print(f"  ✓ MQTT conectado — feed: {EDIFICIO}")
            return True

        except Exception as e:
            print(f"  ✗ Error MQTT: {e}")

            try:
                mqtt_cliente.disconnect()
            except Exception:
                pass

            print("  Reintentando MQTT en 5 segundos...")
            time.sleep(5)

def desconectar_mqtt_seguro():
    """
    Intenta cerrar MQTT sin romper el programa.
    """
    global mqtt_cliente

    try:
        if mqtt_cliente is not None:
            mqtt_cliente.disconnect()
    except Exception:
        pass

def asegurar_conexiones():
    """
    Revisa WiFi y MQTT.
    Si el WiFi se cayó, reconecta todo desde cero.
    """
    global mqtt_cliente

    # Si WiFi se cayó, reconectar WiFi y recrear MQTT completo
    if not estado_wifi():
        print("\n⚠ WiFi desconectado. Reconectando todo...")

        desconectar_mqtt_seguro()

        conectar_wifi()
        crear_mqtt()
        conectar_mqtt()
        return

    # Si WiFi está OK, mantener vivo MQTT
    try:
        if mqtt_cliente is not None:
           mqtt_cliente.loop(timeout=1)
    except Exception as e:
        print(f"\n⚠ MQTT perdió conexión: {e}")
        print("Reconectando MQTT...")

        desconectar_mqtt_seguro()

        # Si en realidad también cayó WiFi, reconstruir todo
        if not estado_wifi():
            conectar_wifi()
            crear_mqtt()

        conectar_mqtt()

def publicar(valor):
    """
    Publica un valor en Adafruit IO.
    Si falla, reconecta y vuelve a intentar una vez.
    """
    global mqtt_cliente

    try:
        asegurar_conexiones()
        mqtt_cliente.publish(FEED, str(valor))
        print(f"  → Publicado: {valor}%  [{EDIFICIO}]")

    except Exception as e:
        print(f"  ✗ Error al publicar: {e}")
        print("  Intentando reconectar y republicar...")

        try:
            desconectar_mqtt_seguro()
            conectar_wifi()
            crear_mqtt()
            conectar_mqtt()

            mqtt_cliente.publish(FEED, str(valor))
            print(f"  → Republicado: {valor}%  [{EDIFICIO}]")

        except Exception as e2:
            print(f"  ✗ No se pudo republicar: {e2}")

# ============================================================
# MEDICIÓN
# ============================================================

def medir_nivel_sonoro():
    """
    Lee todos los sensores KY-037 conectados por AO.
    Calcula amplitud pico-a-pico y retorna el nivel más alto.
    """
    amplitudes = []

    for i in range(len(sensores)):

        for j in range(NUM_MUESTRAS):
            buffers[i][j] = sensores[i].value
            time.sleep(PAUSA_MS)

        maximo   = max(buffers[i])
        minimo   = min(buffers[i])
        amplitud = maximo - minimo

        porcentaje = min(int((amplitud / 65535) * 100 * 5), 100)

        amplitudes.append(porcentaje)

        print(f"    sensor {i + 1}: pico-a-pico={amplitud} → {porcentaje}%")

    return max(amplitudes)


# ============================================================
# INICIO
# ============================================================

conectar_wifi()
crear_mqtt()
conectar_mqtt()

ultimo_envio = 0

print(f"\n=== [{EDIFICIO.upper()}] Midiendo sonido... ===\n")


# ============================================================
# LOOP PRINCIPAL
# ============================================================

while True:
    try:
        asegurar_conexiones()

        ahora = time.monotonic()

        nivel = medir_nivel_sonoro()

        if (ahora - ultimo_envio) >= INTERVALO_S:
            publicar(nivel)
            ultimo_envio = ahora

    except Exception as e:
        print(f"\n⚠ Error general en loop principal: {e}")
        print("Reiniciando conexiones...")

        try:
            desconectar_mqtt_seguro()
        except Exception:
            pass

        conectar_wifi()
        crear_mqtt()
        conectar_mqtt()

        time.sleep(2)
```

## Codigo Mqtt client / touch designer

```python
# mqttclient1_callbacks

def onConnect(dat, *args):
    dat.subscribe('udpmontoyamoraga/feeds/grupo02-rep')
    dat.subscribe('udpmontoyamoraga/feeds/grupo02-ss')
    print('MQTT conectado')
    return

def onDisconnect(dat, *args):
    print('MQTT desconectado')
    return

def onMessage(dat, topic, payload, qos, retain):
    try:
        valor = float(payload)
        valor = max(0.0, min(100.0, valor))
    except:
        return

    if 'rep180' in topic:
        op('constant_rep').par.value0 = valor
        print(f'[rep180] {valor:.0f}%')

    elif topic.endswith('/ss'):
        op('constant_ss').par.value0 = valor
        print(f'[ss]     {valor:.0f}%')
    return

def onSubscribe(dat, *args):
    print(f'Suscrito a: {args}')
    return

def onUnsubscribe(dat, *args):
    return
```

## Parámetros del mqtt_client DAT

![foto](./imagenes/voice14.png)

### Video en funcionamiento

[![Ver video en YouTube](https://img.youtube.com/vi/eZcYLyGfErY/hqdefault.jpg)](https://youtube.com/shorts/eZcYLyGfErY)

---

También hablé con el profesor Guillermo Montecinos para saber su opinión ya que él sabe mucho de estos temas. Me recomendó quizás usar websocket, Node.js, o OSC.

Así que me puse a investigar sobre estos lenguajes.

—--

### Websocket

No lo conocía pero había escuchado de él, por lo que veo tiene que ver con APIS (bacán porque investigar sobre APIS es parte de la rúbrica)

<https://developer.mozilla.org/es/docs/Web/API/WebSocket>

Según esta página WebSocket provee la API para la creación y administración de una conexión WebSocket a un servidor, así como también para enviar y recibir datos en la conexión.

<https://www.ibm.com/docs/es/was/9.0.5?topic=applications-websocket>

WebSocket es un protocolo estándar que permite que un navegador web o una aplicación cliente y una aplicación de servidor web utilice una conexión dúplex para comunicarse.

No he encontrado mucha info sobre como usarlo con touchdesigner;(

### Node.js

<https://nodejs.org/en>

Node.js is a software environment used to run JavaScript code outside of a web browser, allowing developers to build server-side applications and backend systems.

### OSC

<https://ccrma.stanford.edu/groups/osc/index.html>

Según wikipedia Open Sound Control (OSC) es un protocolo de red altamente flexible diseñado para conectar sintetizadores, ordenadores y software multimedia. Creado para superar las limitaciones del tradicional MIDI, permite transmitir datos de control en tiempo real con mayor precisión, utilizando redes estándar como Wi-Fi o cables Ethernet.

Según <https://mct-master.github.io/networked-music/2024/03/17/thomaseo-intro_to_OSC.html>
“OSC - Open Sound Control. Like MIDI, but better.”

Osc en touchdesigner: <https://derivative.ca/UserGuide/OSC>

### Qué es una API?

<https://aws.amazon.com/es/what-is/api/>

---

Finalmente por ahora y por temas de tiempo estoy prefiriendo quedarme con la forma de enviar que hemos estado usando todo el semestre (Adafruit y circuitpython)

---

## 15 de junio

Hoy pudimos trabajar por primera vez juntas con Cami, ella compró otros micrófonos, que funcionan mejor para sonido ambiente, son estos:

<https://hubot.cl/producto/sensor-analogico-audio-max9812-sku-614/>

![mic](./imagenes/sensoraudio.png)

> los mic anteriores no detectaban tan bien los sonidos ambiente

lo primero que hicimos fue probar mi código de nuevo, funcionó.

[![Video](https://img.youtube.com/vi/fMY_MDHsqUs/maxresdefault.jpg)](https://youtu.be/fMY_MDHsqUs)

[![Short](https://img.youtube.com/vi/NO4Tx8xjosk/maxresdefault.jpg)](https://youtube.com/shorts/NO4Tx8xjosk)

Luego probamos el código que tenía Cami:

![mic](./imagenes/cami.png)

Pero el problema con su código es que enviaba 3 números distintos, cami me explicó que era porque ella modificó el como se leían los datos ambiente.

Me envió su link con su conversación con claude: <https://claude.ai/chat/7cd64083-1322-4b08-8168-85c80d8ea3de>

Le dije que era mejor ocupar el código que yo tenía para ambas Raspberry, ya que ese código estaba hecho para usarse en ambas cambiando solo el nombre del feed, siendo para una Grupo02-rep y para otra Grupo02-ss.

Lo hicimos y funcionó bien:

[![Short](https://img.youtube.com/vi/fLr_ejGx-88/maxresdefault.jpg)](https://youtube.com/shorts/fLr_ejGx-88?feature=share)

El problema era que los datos que enviaban eran iguales, uno enviaba solo datos grandes de 80 a 100 y el otro pequeos, así que le pedimos a la ia modificar esos valores para que lleguen mas limpios, el micrófono siendo más sensible al ruido.

[![Video](https://img.youtube.com/vi/3mBjlt_OSWs/maxresdefault.jpg)](https://youtu.be/3mBjlt_OSWs)

este es el link de mi conversación con claude: <https://claude.ai/share/76b89e2e-c428-4158-8f2e-ccad7250c132>

Luego, subimos este código y en una de las raspberry funcionó perfecto, pero en la otra no se conectaba al internet, estuvimos mucho rato cambiando el hotspot, formateamos la placa, cambiamos de compu y nada:

![mic](./imagenes/monitor.png)

Era raro que nos funcionara en una placa y en la otra no, siendo que era el mismo internet y mismo código, así que despues de michos intentos Mateo nos prestó su RaspBerry y funcionó de inmediato! mientras arreglabamos lo otro también edité un poquito las visuales en TD y quedó así!

[![Short](https://img.youtube.com/vi/NO4Tx8xjosk/maxresdefault.jpg)](https://youtube.com/shorts/NO4Tx8xjosk?feature=share)

## Visual final

[![Video](https://img.youtube.com/vi/n-fH_hPftp4/maxresdefault.jpg)](https://youtu.be/n-fH_hPftp4)

### Códigos

```python
# ============================================================
# SENSOR DE SONIDO — Raspberry Pi Pico 2W + MAX9812
# Examen interacciones inalámbricas
# ============================================================
# CONEXIONES MAX9812:
#   VCC  → Pin 36 (3V3)
#   GND  → Pin 38 (GND)
#   OUT  → Pin 31 (GP26)
# ============================================================

import time
import board
import analogio
import wifi
import socketpool
import adafruit_minimqtt.adafruit_minimqtt as MQTT

# ============================================================
# CONFIGURACIÓN — solo cambia esto entre los dos Picos
# ============================================================

EDIFICIO      = "grupo02-ss"
WIFI_SSID     = "iPhone-cs"
WIFI_PASSWORD = "lasagna342"

AIO_USERNAME  = "udpmontoyamoraga"
AIO_KEY       = "secretooo"

# ============================================================
# PARÁMETROS DE MEDICIÓN
# ============================================================

# El MAX9812 ya tiene 20dB de ganancia incorporada
# así que los umbrales son más bajos que con KY-037
RUIDO_PISO   = 150    # amplitud mínima para contar como sonido
AMPLITUD_MAX = 5000   # amplitud que representa 100%
                      # bajar si no llega a 100% aplaudiendo
                      # subir si se satura muy fácil

NUM_MUESTRAS = 150    # muestras por ráfaga (~15ms sin delay)
INTERVALO_S  = 2.0    # segundos entre envíos (límite Adafruit IO)

# ============================================================
# SENSOR (arreglo para el requisito del curso)
# ============================================================

PINES_SENSORES = [board.GP26]
sensores       = [analogio.AnalogIn(pin) for pin in PINES_SENSORES]

# ============================================================
# RED
# ============================================================

pool         = None
mqtt_cliente = None


def estado_wifi():
    try:
        return wifi.radio.connected
    except Exception:
        return False


def conectar_wifi():
    print(f"Conectando a WiFi: '{WIFI_SSID}'")
    while not estado_wifi():
        try:
            wifi.radio.connect(WIFI_SSID, WIFI_PASSWORD)
            time.sleep(1)
            if estado_wifi():
                print(f"  ✓ WiFi OK — IP: {wifi.radio.ipv4_address}")
                return
        except Exception as e:
            print(f"  ✗ {e}")
        print("  Reintentando en 5s...")
        time.sleep(5)


def crear_mqtt():
    global pool, mqtt_cliente
    pool = socketpool.SocketPool(wifi.radio)
    mqtt_cliente = MQTT.MQTT(
        broker         = "io.adafruit.com",
        port           = 1883,
        username       = AIO_USERNAME,
        password       = AIO_KEY,
        socket_pool    = pool,
        socket_timeout = 1,
        keep_alive     = 30,
    )


def conectar_mqtt():
    intentos = 0
    while True:
        try:
            print("Conectando a Adafruit IO...")
            mqtt_cliente.connect()
            print(f"  ✓ MQTT OK — feed: {EDIFICIO}")
            return
        except Exception as e:
            intentos += 1
            espera = min(3 * intentos, 30)
            print(f"  ✗ {e}. Reintentando en {espera}s...")
            try:
                mqtt_cliente.disconnect()
            except Exception:
                pass
            time.sleep(espera)


def asegurar_conexiones():
    if not estado_wifi():
        print("WiFi caído. Reconectando...")
        try:
            mqtt_cliente.disconnect()
        except Exception:
            pass
        conectar_wifi()
        crear_mqtt()
        conectar_mqtt()
        return
    try:
        mqtt_cliente.loop(timeout=1)
    except Exception as e:
        print(f"MQTT caído: {e}. Reconectando...")
        try:
            mqtt_cliente.disconnect()
        except Exception:
            pass
        if not estado_wifi():
            conectar_wifi()
            crear_mqtt()
        conectar_mqtt()


def publicar(valor):
    try:
        asegurar_conexiones()
        mqtt_cliente.publish(f"{AIO_USERNAME}/feeds/{EDIFICIO}", str(valor))
        print(f"  → {EDIFICIO}: {valor}%")
    except Exception as e:
        print(f"  ✗ Error: {e}")
        try:
            mqtt_cliente.disconnect()
        except Exception:
            pass
        conectar_wifi()
        crear_mqtt()
        conectar_mqtt()

# ============================================================
# MEDICIÓN — pico máximo sin promediar
# ============================================================

def medir_pico():
    """
    Recorre el arreglo de sensores con un bucle for.
    En cada sensor toma una ráfaga rápida y calcula
    la amplitud pico-a-pico SIN promediar.
    Retorna el nivel más alto entre todos los sensores.
    """
    niveles = []

    for i in range(len(sensores)):

        # Ráfaga rápida sin delays (bucle for + arreglo)
        maximo = 0
        minimo = 65535
        for j in range(NUM_MUESTRAS):
            v = sensores[i].value
            if v > maximo:
                maximo = v
            if v < minimo:
                minimo = v

        amplitud = maximo - minimo

        if amplitud < RUIDO_PISO:
            porcentaje = 0
        else:
            porcentaje = int(((amplitud - RUIDO_PISO) / AMPLITUD_MAX) * 100)
            porcentaje = max(0, min(100, porcentaje))

        niveles.append(porcentaje)

    return max(niveles)

# ============================================================
# INICIO
# ============================================================

conectar_wifi()
crear_mqtt()
conectar_mqtt()

ultimo_envio = 0
pico_maximo  = 0       # guarda el pico más alto desde el último envío

print(f"\n=== [{EDIFICIO.upper()}] Escuchando... ===\n")

# ============================================================
# LOOP PRINCIPAL
# ============================================================

while True:
    try:
        # Medir constantemente
        nivel = medir_pico()

        # Guardar el pico más alto visto (no promediar)
        if nivel > pico_maximo:
            pico_maximo = nivel
            print(f"    nuevo pico: {pico_maximo}%")

        # Enviar cada INTERVALO_S segundos
        ahora = time.monotonic()
        if (ahora - ultimo_envio) >= INTERVALO_S:
            publicar(pico_maximo)
            pico_maximo = 0        # resetear después de enviar
            ultimo_envio = ahora

    except Exception as e:
        print(f"Error: {e}. Reconectando...")
        try:
            mqtt_cliente.disconnect()
        except Exception:
            pass
        conectar_wifi()
        crear_mqtt()
        conectar_mqtt()
        time.sleep(2)
```
```python
print("Hello World!")
# ============================================================
# SENSOR DE SONIDO — Raspberry Pi Pico 2W + MAX9812
# Examen interacciones inalámbricas
# ============================================================
# CONEXIONES MAX9812:
#   VCC  → Pin 36 (3V3)
#   GND  → Pin 38 (GND)
#   OUT  → Pin 31 (GP26)
# ============================================================

import time
import board
import analogio
import wifi
import socketpool
import adafruit_minimqtt.adafruit_minimqtt as MQTT

# ============================================================
# CONFIGURACIÓN — solo cambia esto entre los dos Picos
# ============================================================

EDIFICIO      = "grupo02-rep"
WIFI_SSID     = "iPhone-cs"
WIFI_PASSWORD = "lasagna342"

AIO_USERNAME  = "udpmontoyamoraga"
AIO_KEY       = "secretoo"

# ============================================================
# PARÁMETROS DE MEDICIÓN
# ============================================================

# El MAX9812 ya tiene 20dB de ganancia incorporada
# así que los umbrales son más bajos que con KY-037
RUIDO_PISO   = 150    # amplitud mínima para contar como sonido
AMPLITUD_MAX = 5000   # amplitud que representa 100%
                      # bajar si no llega a 100% aplaudiendo
                      # subir si se satura muy fácil

NUM_MUESTRAS = 150    # muestras por ráfaga (~15ms sin delay)
INTERVALO_S  = 2.0    # segundos entre envíos (límite Adafruit IO)

# ============================================================
# SENSOR (arreglo para el requisito del curso)
# ============================================================

PINES_SENSORES = [board.GP26]
sensores       = [analogio.AnalogIn(pin) for pin in PINES_SENSORES]

# ============================================================
# RED
# ============================================================

pool         = None
mqtt_cliente = None


def estado_wifi():
    try:
        return wifi.radio.connected
    except Exception:
        return False


def conectar_wifi():
    print(f"Conectando a WiFi: '{WIFI_SSID}'")
    while not estado_wifi():
        try:
            wifi.radio.connect(WIFI_SSID, WIFI_PASSWORD)
            time.sleep(1)
            if estado_wifi():
                print(f"  ✓ WiFi OK — IP: {wifi.radio.ipv4_address}")
                return
        except Exception as e:
            print(f"  ✗ {e}")
        print("  Reintentando en 5s...")
        time.sleep(5)


def crear_mqtt():
    global pool, mqtt_cliente
    pool = socketpool.SocketPool(wifi.radio)
    mqtt_cliente = MQTT.MQTT(
        broker         = "io.adafruit.com",
        port           = 1883,
        username       = AIO_USERNAME,
        password       = AIO_KEY,
        socket_pool    = pool,
        socket_timeout = 1,
        keep_alive     = 30,
    )


def conectar_mqtt():
    intentos = 0
    while True:
        try:
            print("Conectando a Adafruit IO...")
            mqtt_cliente.connect()
            print(f"  ✓ MQTT OK — feed: {EDIFICIO}")
            return
        except Exception as e:
            intentos += 1
            espera = min(3 * intentos, 30)
            print(f"  ✗ {e}. Reintentando en {espera}s...")
            try:
                mqtt_cliente.disconnect()
            except Exception:
                pass
            time.sleep(espera)


def asegurar_conexiones():
    if not estado_wifi():
        print("WiFi caído. Reconectando...")
        try:
            mqtt_cliente.disconnect()
        except Exception:
            pass
        conectar_wifi()
        crear_mqtt()
        conectar_mqtt()
        return
    try:
        mqtt_cliente.loop(timeout=1)
    except Exception as e:
        print(f"MQTT caído: {e}. Reconectando...")
        try:
            mqtt_cliente.disconnect()
        except Exception:
            pass
        if not estado_wifi():
            conectar_wifi()
            crear_mqtt()
        conectar_mqtt()


def publicar(valor):
    try:
        asegurar_conexiones()
        mqtt_cliente.publish(f"{AIO_USERNAME}/feeds/{EDIFICIO}", str(valor))
        print(f"  → {EDIFICIO}: {valor}%")
    except Exception as e:
        print(f"  ✗ Error: {e}")
        try:
            mqtt_cliente.disconnect()
        except Exception:
            pass
        conectar_wifi()
        crear_mqtt()
        conectar_mqtt()

# ============================================================
# MEDICIÓN — pico máximo sin promediar
# ============================================================

def medir_pico():
    """
    Recorre el arreglo de sensores con un bucle for.
    En cada sensor toma una ráfaga rápida y calcula
    la amplitud pico-a-pico SIN promediar.
    Retorna el nivel más alto entre todos los sensores.
    """
    niveles = []

    for i in range(len(sensores)):

        # Ráfaga rápida sin delays (bucle for + arreglo)
        maximo = 0
        minimo = 65535
        for j in range(NUM_MUESTRAS):
            v = sensores[i].value
            if v > maximo:
                maximo = v
            if v < minimo:
                minimo = v

        amplitud = maximo - minimo

        if amplitud < RUIDO_PISO:
            porcentaje = 0
        else:
            porcentaje = int(((amplitud - RUIDO_PISO) / AMPLITUD_MAX) * 100)
            porcentaje = max(0, min(100, porcentaje))

        niveles.append(porcentaje)

    return max(niveles)

# ============================================================
# INICIO
# ============================================================

conectar_wifi()
crear_mqtt()
conectar_mqtt()

ultimo_envio = 0
pico_maximo  = 0       # guarda el pico más alto desde el último envío

print(f"\n=== [{EDIFICIO.upper()}] Escuchando... ===\n")

# ============================================================
# LOOP PRINCIPAL
# ============================================================

while True:
    try:
        # Medir constantemente
        nivel = medir_pico()

        # Guardar el pico más alto visto (no promediar)
        if nivel > pico_maximo:
            pico_maximo = nivel
            print(f"    nuevo pico: {pico_maximo}%")

        # Enviar cada INTERVALO_S segundos
        ahora = time.monotonic()
        if (ahora - ultimo_envio) >= INTERVALO_S:
            publicar(pico_maximo)
            pico_maximo = 0        # resetear después de enviar
            ultimo_envio = ahora

    except Exception as e:
        print(f"Error: {e}. Reconectando...")
        try:
            mqtt_cliente.disconnect()
        except Exception:
            pass
        conectar_wifi()
        crear_mqtt()
        conectar_mqtt()
        time.sleep(2)
```
Lo que hace este código es medir sonido constantemente, toma 150 lecturas de los micrófonos lo más rápido posible, sin pausas, esso tarda unos 15ms, de esas 150 lecturas busca el valor más alto y el más bajo, y calcula la diferencia:

amplitud = máximo - mínimo


En silencio esa diferencia es pequeña, con un aplauso por ejemplo es grande, eso lo convierte a un porcentaje 0-100, en resumen, lo que hace es que si hubo un pico en esas 150 lecturas, lo captura, guarda el pico más alto.

si nivel actual > pico guardado -> actualiza el pico

Cada 2 segundos envía ese pico y lo resetea, manda un número entre 0 y 100 al feed de Adafruit IO, y vuelve a empezar desde 0.

---

Qué llega a TouchDesigner: Un número entre 0 y 100 cada 2 segundos:

silencio total     ->  0

voz suave          -> 15–30

voz fuerte         -> 40–60

aplauso            -> 70–100

No es el nivel promedio del ambiente, es el momento más ruidoso de los últimos 2 segundos, si todo estuvo en silencio menos un aplauso, llega 85, si estuvo todo en silencio, llega 0.
