# sesion-08

lunes 27 abril 2026

En esta sesión empezamos a usar Python aplicado a hardware.

Python es un lenguaje muy usado y flexible, que funciona con espacios (indentación) para ordenar el código.

También vimos:
- NumPy - cálculos
- SciPy - cálculos más avanzados

Después revisamos versiones de Python para placas:

- MicroPython - versión liviana para microcontroladores
- CircuitPython - más fácil de usar y pensado para electrónica

Trabajamos con CircuitPython 10.2.0, que permite programar directamente componentes como sensores o botones.

Permite:
- Leer sensores
- Controlar LEDs, pantallas, etc

### Instalación  CircuitPython en la Raspberry Pi Pico:

Pasos principales
- Descargar CircuitPython desde el sitio oficial según la placa: <https://circuitpython.org/board/raspberry_pi_pico2_w/>
- Conectar la Raspberry Pi Pico al computador.
- Abrir la unidad de la placa en el explorador de archivos.
- Copiar el archivo descargado (firmware .uf2) dentro de la carpeta de la Raspberry Pi.
- La placa se reinicia automáticamente con CircuitPython instalado.

### Librerías necesarias

Se deben agregar manualmente a la carpeta lib de la placa:
- adafruit_minimqtt.mpy
- adafruit_connection_manager.mpy
- adafruit_ticks.mpy

### Aspectos técnicos

### Voltajes:
- Arduino funciona con 5V
- Raspberry Pi con 3.3V
- No mezclar para no dañar componentes
### ADC:
- Convierte señales reales en datos que la placa puede leer
- En la Raspberry Pi Pico se usa el pin ADC0
### Pines en la Raspberry Pi Pico:
- GND es tierra
- ADC0 es entrada analógica
- 3V3 entrega 3.3V para alimentar componentes

### Trabajo en clases

En esta clase no tenemos registros fotográficos T T 

Usamos el código que nos dieron, pero nos dieron mal unas indicaciones. Por eso, cada vez que armábamos el circuito, se nos quemaban los potenciómetros ( •᷄ᯅ•᷅ )

Intentamos varias veces hasta que mi compañero se dio cuenta del error, pero ya no quedaba tiempo para probar de nuevo, así que no pudimos terminar la actividad.

### Código usado:

```python
import time
import board
import analogio
import wifi
import socketpool
import adafruit_minimqtt.adafruit_minimqtt as MQTT

# Conexión WiFi
wifi.radio.connect("NOMBREWIFI", "CLAVEWIFI")

# MQTT
pool = socketpool.SocketPool(wifi.radio)
mqtt = MQTT.MQTT(
    broker="io.adafruit.com",
    username="usuario",
    password="clave",
    socket_pool=pool,
)

mqtt.connect()

# Sensor
pot = analogio.AnalogIn(board.A0)

while True:
    value = pot.value * 1023 // 65535
    print(value)

    mqtt.publish("usuario/feeds/potenciometro", str(value))

    time.sleep(5)
```
