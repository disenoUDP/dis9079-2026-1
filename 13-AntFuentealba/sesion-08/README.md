# sesion-08

lunes 27 abril 2026

Apuntes

## Concepto 

En esta clase se revisa el concepto de comunicación bidireccional entre dispositivos, es decir, sistemas que pueden tanto enviar como recibir información. La idea es que los microcontroladores no solo ejecuten acciones locales, sino que también interactúen con la nube o con otros sistemas en tiempo real.


## Lenguajes y herramientas utilizadas

### Python
Python es un lenguaje de programación de alto nivel, interpretado y de propósito general. Es uno de los lenguajes más utilizados por su versatilidad.

- La indentación (espacios) es fundamental, ya que define la jerarquía del código.
- Permite trabajar en áreas como análisis de datos, automatización e IoT.


### SciPy y NumPy
- **NumPy**: librería para cálculos numéricos y manejo de arreglos.
- **SciPy**: librería construida sobre NumPy para cálculos científicos más avanzados.


### MicroPython
Versión ligera de Python diseñada para microcontroladores.

- Permite ejecutar Python en placas pequeñas.
- Fue una de las primeras opciones para IoT en hardware simple.


### CircuitPython
Fork de MicroPython desarrollado para facilitar aún más el aprendizaje en electrónica.

- Enfocado en educación y experimentación.
- Compatible con muchas placas (más de 600 modelos).
- Usa archivos `.mpy` como librerías livianas.

Sitio oficial: https://circuitpython.org/


## Aspectos técnicos

### Voltajes
- VCC en Arduino: 5V
- VCC en Raspberry Pi: 3.3V
- Es importante no mezclar voltajes incorrectamente.


### ADC (Analog to Digital Converter)
- Permite convertir señales analógicas en valores digitales.
- En Raspberry Pi Pico se usa el pin **ADC0** (equivalente a A0 en Arduino).


### Pines en Raspberry Pi Pico
- Los pines GND suelen ser cuadrados en el esquema físico.
- ADC0 es la entrada analógica principal.
- 3V3 es la salida de alimentación de 3.3V.


## CircuitPython

CircuitPython es un lenguaje diseñado para simplificar la programación de microcontroladores de bajo costo, facilitando la conexión entre hardware y software.


## Instalación en Raspberry Pi Pico / Pico W

### Pasos principales

1. Descargar CircuitPython desde el sitio oficial según la placa:
   https://circuitpython.org/board/raspberry_pi_pico2_w/

2. Conectar la Raspberry Pi Pico al computador.

3. Abrir la unidad de la placa en el explorador de archivos.

4. Copiar el archivo descargado (firmware `.uf2`) dentro de la carpeta de la Raspberry Pi.

5. La placa se reinicia automáticamente con CircuitPython instalado.


## Librerías necesarias

Se deben agregar manualmente a la carpeta `lib` de la placa:

- adafruit_minimqtt.mpy
- adafruit_connection_manager.mpy
- adafruit_ticks.mpy

Estas librerías permiten la conexión a WiFi y MQTT.


## Conexión WiFi y MQTT (CircuitPython)

Ejemplo de estructura de código utilizada:

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
