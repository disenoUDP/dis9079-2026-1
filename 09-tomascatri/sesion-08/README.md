# sesion-08

lunes 27 abril 2026

nos vemos a la vuelta del receso

## Apuntes 
* Python fue creado por una persona con carra egocentrica
* En python es obligatorio que tenga espacio todo el codigo
* Casi toda la IA de hoy en dia esta hecha con python
* se usa python en rasperry pi
* Se usa circuitpython, para esto hay que borrarle el fimware del rasperry pi
* circuitpython tiene un catalogo gigante donde se le puede agregar su codigo a muchas placas
* usaremos la version de circuitpython 10.22.0
* tenemos que inyectarla al rasperry pi
* una vez inyectado descargamos un programa llamado https://www.chiark.greenend.org.uk/~sgtatham/putty/latest.html, al hacer esto lograremos establecer una conexión serial directa (REPL) entre tu computadora y el microcontrolador a través del cable USB.
* instalamos putty y despues lo abremos
* una vez abierto la primera pestaña que abre tenemos que selecionar serial, en las opciones, luego presionar otra parte donde dice serial en una barra lateral y ahi poner el conector usb usado en el compu, en mi caso fue el usb14 y le aumentamos a la velocidad de respuesta a 115200.
* ahora en archivos de carpeta copiamos ese codigo:
  
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
    username="udpmontoyamoraga",
    password="YASELASABEN",
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

* Una vez hecho esto pegamos las librerias que pida segun el error que de, pero en si son 3 archivos
* Hecho esto ya manda señal y se visualiza en el putty
### Configurar Arduino
