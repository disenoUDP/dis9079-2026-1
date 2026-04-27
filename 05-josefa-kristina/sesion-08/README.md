# sesion-08

Actuadores

Mu editor RIP

Python: Lenguaje muy fácil de escribir

Se escribe menos pero muy estricto, hay que tner mucho ojo con los espacios 

Poco eficiente

![librerias python](./imagenes/libreriaspyton.png)


se usaba micropython

vamos a usar circuit python 

tenemos que eliminar el filmware de la raspi

Descargar CircuitPython 10.2.0 e insertarlo al disco duro de la raspi

<https://learn.adafruit.com/welcome-to-circuitpython/advanced-serial-console-on-windows>

usar arduino para mover el servo

enviar potenciometro de la raspi

ADC conversor analogo a digital (como las patitas AX en arduino)

poner potenciometro en la raspi 

| CONEXIÓN 1 | CONEXIÓN 2 | CONEXIÓN 3 |
|------------|------------|------------|
| PIN IZQUIERDO POTENCIÓMETRO | PIN MEDIO POTENCIÓMETRO | PIN DERECHO POTENCIÓMETRO |
|     CABLE VERDE   |CABLE ROJO | CABLE AMARILLO  |
| PIN 23- GROUND  resistor 1%   | PIN 36- 3V3 (OUT) | PIN 31- GP26 ADCO 12C1 SDA |

Siempre grabar para que funcione el código en Visual studio

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

