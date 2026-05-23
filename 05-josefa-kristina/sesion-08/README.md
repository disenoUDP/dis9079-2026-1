# sesion-08

En esta sesión veremos actuadores

Mu editor sigue funcionando pero no le hacen mantención así que no lo usaremos (RIP)

Python: Lenguaje muy fácil de escribir por que se escribe menos pero es muy estricto, hay que tner mucho ojo con los espacios por esto puede ser poco eficiente. 

##### Algunas de las librerías de python:

![librerias python](./imagenes/libreriaspyton.png)

Se usaba micropython pero vamos a usar Circuit Python.

1. tenemos que eliminar el filmware de la raspi
2. Descargar CircuitPython 10.2.0
3. Insertar el archivo descargado al disco duro de la raspi
4. Descargar la última versión de PuTTY
5. En PuTTY, conexión a serial, cambiar el port a 115200 y el host name al com en donde se encuentra nuestra raspberry pi pico 2 w
6. Hacer ctrl + c Sino funciona lo anterior hacer ctrl + d.

<https://learn.adafruit.com/welcome-to-circuitpython/advanced-serial-console-on-windows>

usar arduino para mover el servo

enviar potenciometro de la raspi

ADC conversor analogo a digital (como las patitas AX en arduino)

poner potenciometro en la raspi 

| CONEXIÓN 1 | CONEXIÓN 2 | CONEXIÓN 3 |
|------------|------------|------------|
| PIN IZQUIERDO POTENCIÓMETRO | PIN MEDIO POTENCIÓMETRO | PIN DERECHO POTENCIÓMETRO |
|     CABLE VERDE   |CABLE ROJO | CABLE AMARILLO  |
| PIN 23- GROUND     | PIN 36- 3V3 (OUT) | PIN 31- GP26 ADCO 12C1 SDA |

Siempre grabar para que funcione el código en Visual studio y tiene que decir code.pi

import = include

```
# configuración

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
    password="aioKEY",
    socket_pool=pool,
)

mqtt.connect()

# Potentiometer
pot = analogio.AnalogIn(board.A0)

while True:
# Convertir el valor del potenciometro a un rango de 0 - 1023

    value = pot.value * 1023 // 65535
    print(value)

    mqtt.publish("udpmontoyamoraga/feeds/potenciometro", str(value))
# Descansa por 5 s 
    time.sleep(5)
```

lunes 27 abril 2026

nos vemos a la vuelta del receso

