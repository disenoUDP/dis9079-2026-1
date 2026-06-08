# sesion-08

lunes 27 abril 2026

---

## Apuntes

- ver comunicacion bidirecional que los dos se emitan y reciban
- `Python:` app para programar
  - los espacios si importan, así python visualiza la jerarquía de las cosas
  - Scipy / Numpy
  - `MicroPython:` para microcontroladores 
  - `circuitPython:` es un fork del original de micropython

### CircuitPython

<img src="./imagenes/circuitPython.png" alt="tinkercad" width="400">

- CircuitPython es un lenguaje de programación diseñado para simplificar la experimentación y el aprendizaje de la programación en placas de microcontroladores de bajo costo.
- Tiene 651 placas para utilizar
- Las bibliotecas mpy, son archivos muy pequeños
- volate_cc > V_CC
- 3.3 V
- 5.0 V
- ADC0 > es como la patita 0 del arduino / pasa de algo análogo a algo digital

## Pasos

1. Primero descargamos en [Circuit Python](https://circuitpython.org/board/raspberry_pi_pico2_w/) el modelo de placa que tenemos, en este caso es la `Raspberry Pi PICO 2 W`
2. Luego conectamos la raspberry pi en el computador
3. Luego, abrimos las carpetas de la raspberry pi pico2 w en el finder
4. y pasamos el archivo que descargamos, a la carpeta de la raspberry pi

<img src="./imagenes/carpeta.png" alt="carpeta" width="400">

<img src="./imagenes/visualCode.png" alt="visualcode" width="500">

5. Cambiamos en visual code la línea 9, por nuestro wifi y el nombre del feeds

```cpp
import time
import board
import analogio
import wifi
import socketpool
import adafruit_minimqtt.adafruit_minimqtt as MQTT

# WiFi
wifi.radio.connect("NOMBREWIFI", "CLAVEWIFI")

# MQTT
pool = socketpool.SocketPool(wifi.radio)
mqtt = MQTT.MQTT(
    broker="io.adafruit.com",
    username="blablabla",
    password="blablabla",
    socket_pool=pool,
)

mqtt.connect()

# Potentiometer
pot = analogio.AnalogIn(board.A0)

while True:
    value = pot.value * 1023 // 65535
    print(value)

    mqtt.publish("udpmontoyamoraga/feeds/potenciometro", str(value))

    time.sleep(5)
```
6. Luego, añadimos las carpetas a la libreria en la raspberry pi (adafruit_connection_manager.mpy / adafruit_minimqtt / adafruit_ticks.mpy)
7. En la terminal, buscamos usbmodem* (donde nos mostrará donde está conectado el usb)
8. En este caso: usbmodem11301
9. Luego, actualizamos y nos aparece los valores del potenciómetro, que deberían llegar al feed de aarón
10. [https://io.adafruit.com/udpmontoyamoraga/feeds/potenciometro-grupo08]

<img src="./imagenes/usbmodem.png" alt="usbmodem" width="800">

<img src="./imagenes/valoresPOT.png" alt="valorespot" width="400">
