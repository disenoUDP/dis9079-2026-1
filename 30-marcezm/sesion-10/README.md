# sesion-10

lunes 18 mayo 2026

# Inicio del proyecto

En esta clase comenzamos planteando nuestro proyecto IoT utilizando:

- Raspberry Pi Pico 2W
- Arduino UNO R4 WiFi
- Sensor ultrasónico HC-SR04
- Servo motor SG90
- Adafruit IO
- MQTT

La idea era que la Raspberry Pi midiera distancias y enviara esos datos mediante internet para que el Arduino controlara un servo dependiendo de la distancia detectada.

---

# Primeras pruebas

Comenzamos realizando el cableado del sensor ultrasónico HC-SR04 junto a la Raspberry Pi Pico 2W.

Tuvimos que investigar:

- funcionamiento del sensor,
- conexiones TRIG y ECHO,
- uso de CircuitPython,
- cómo cargar código en la Raspberry Pi Pico.

Inicialmente el código no funcionaba y Visual Studio Code mostraba muchos errores relacionados con bibliotecas faltantes.

Ejemplo:

```python
import wifi
import socketpool
import board
import adafruit_hcsr04
import adafruit_minimqtt.adafruit_minimqtt as MQTT
```

---

# Problemas encontrados

Descubrimos que CircuitPython necesita instalar librerías manualmente dentro de:

```text
CIRCUITPY/lib
```

Las librerías faltantes eran:

- adafruit_minimqtt
- adafruit_requests.mpy
- adafruit_connection_manager.mpy
- adafruit_ticks.mpy
- adafruit_hcsr04.mpy

También confundimos varias advertencias amarillas de Visual Studio Code con errores reales.

---

# Cambio de proyecto

Debido al tiempo disponible y a la complejidad del proyecto original, el profesor Aarón nos integró al Grupo 10 para continuar con un sistema más estable.

El nuevo proyecto utilizaba:

- Raspberry Pi Pico 2W
- Arduino UNO R4 WiFi
- botón pulsador
- LED
- Adafruit IO
- MQTT

---

# Funcionamiento del proyecto final

La Raspberry Pi Pico 2W enviaba datos mediante MQTT cuando se presionaba un botón.

Luego el Arduino UNO R4 WiFi recibía esos datos desde Adafruit IO y encendía o apagaba un LED.

---

# Conexiones realizadas

## Raspberry Pi Pico 2W

| Botón | Raspberry Pi Pico |
|---|---|
| Señal | GP0 |
| Positivo | 3V3 |
| Negativo | GND |

---

## Arduino UNO R4 WiFi

| LED | Arduino |
|---|---|
| Positivo | Pin 13 |
| Negativo | Resistencia 220Ω + GND |

---

# Problemas durante el armado

Uno de los principales problemas fue el cableado del LED.

Primero conectamos el LED directamente a 5V solamente para comprobar que funcionaba, pero luego olvidamos cambiarlo correctamente al pin 13 para controlarlo mediante código.

También tuvimos problemas donde el LED quedaba permanentemente encendido porque el sistema solo recibía correctamente el valor `1` pero no el `0`.

Después de varias pruebas descubrimos que el problema no estaba en el código, sino en configuraciones previas de la Raspberry Pi Pico 2W.

---

# Código Raspberry Pi Pico 2W (Emisor)

```python
import time
import board
import digitalio
import wifi
import socketpool
import adafruit_minimqtt.adafruit_minimqtt as MQTT

SSID = "wifi"
PASSWORD = "clave"

wifi.radio.connect(SSID, PASSWORD)

AIO_USERNAME = "udpmontoyamoraga"
AIO_KEY = "clavecredencial"

FEED_BOTON = AIO_USERNAME + "/feeds/boton-prueba-grupo10"

pool = socketpool.SocketPool(wifi.radio)

mqtt = MQTT.MQTT(
    broker="io.adafruit.com",
    username=AIO_USERNAME,
    password=AIO_KEY,
    socket_pool=pool,
)

mqtt.connect()

boton = digitalio.DigitalInOut(board.GP0)
boton.direction = digitalio.Direction.INPUT
boton.pull = digitalio.Pull.UP

estado_anterior = True

while True:

    mqtt.loop()

    estado_actual = boton.value

    if estado_anterior and not estado_actual:
        mqtt.publish(FEED_BOTON, "1")

    if not estado_anterior and estado_actual:
        mqtt.publish(FEED_BOTON, "0")

    estado_anterior = estado_actual

    time.sleep(0.02)
```

---

# Código Arduino UNO R4 WiFi (Receptor)

```cpp
#include "AdafruitIO_WiFi.h"

#define IO_USERNAME  "udpmontoyamoraga"
#define IO_KEY       "clavecredencial"
#define WIFI_SSID    "wifi"
#define WIFI_PASS    "clave"

AdafruitIO_WiFi io(IO_USERNAME, IO_KEY, WIFI_SSID, WIFI_PASS);

const int ledPin = 13;

AdafruitIO_Feed *botonFeed = io.feed("boton-prueba-grupo10");

void setup() {

  pinMode(ledPin, OUTPUT);

  Serial.begin(115200);

  io.connect();

  botonFeed->onMessage(handleMessage);

  while(io.status() < AIO_CONNECTED) {
    delay(500);
  }
}

void loop() {

  io.run();
}

void handleMessage(AdafruitIO_Data *data) {

  int comando = data->toInt();

  if (comando == 1) {
    digitalWrite(ledPin, HIGH);
  }

  else {
    digitalWrite(ledPin, LOW);
  }
}
```

---

# Aprendizajes obtenidos

Durante esta solemne aprendí:

- funcionamiento básico de MQTT,
- uso de Adafruit IO,
- instalación de bibliotecas en CircuitPython,
- conexión entre Raspberry Pi Pico y Arduino,
- control de actuadores mediante internet,
- resolución de errores de hardware y software,
- importancia del cableado y las conexiones.

También aprendí a investigar problemas técnicos y trabajar colaborativamente para resolver errores durante el desarrollo del proyecto.

---

# Resultado final

Finalmente logramos hacer funcionar correctamente el sistema IoT.

El botón conectado a la Raspberry Pi Pico 2W lograba controlar remotamente un LED conectado al Arduino UNO R4 WiFi mediante internet utilizando Adafruit IO y MQTT.

También realizamos pruebas de larga distancia utilizando distintas redes WiFi para comprobar el correcto funcionamiento del sistema.
