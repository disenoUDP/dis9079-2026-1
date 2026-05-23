# sesion-08

lunes 27 abril 2026

En la clase de hoy por fin utilizamos la Raspberry pi Pico 2 w y también usaremos python  

<https://circuitpython.org/board/raspberry_pi_pico2_w/>

## Pasos de instalación de circuit python

Mantener presionado botón de raspberry pi pico 2 w → conectar energía a la placa raspberry pi → soltar botón de la placa → abrir unidad y se abrira una carpeta de la raspberry → instalar el circuitpython desde el link → arrastrar el archivo recién descargado terminado en 10.2.0 → se carga y queda listo 

Al parecer es más fácil escribir en python y aparte tambien es mas facil subirlo

Enseñanzas de la clase: Si el hdmi no está funcionando bien, puede ser la batería, así que siempre conecta la fuente de poder

## Trabajo en clases

Usamos este código para la clase. Lamentablemente nunca logramos realizar el ejercicio ya que cada vez que lo intentamos se nos quemaban los potenciómetro, por lo que no hay registro fotográfico del ejercicio. Fijándome bien en la foto de cómo poner bien los cables y las instrucciones que habían dado en discord, me di cuenta de que estaban mal las conexiones que nos dieron y me terminé ganando décimas por corregir el error (inserte dab ficticio)

```python
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
    username="bla",
    password="bla",
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

