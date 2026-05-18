# solemne-02

## Integrantes

- Renata De Los Ángeles Arévalo Urra / [arevalourra](<https://github.com/nicolasvaldesgreve/dis9079-2026-1/tree/main/06-arevalourra>)
- Isidora Andrea Pérez Maulén / [isipm08](<https://github.com/nicolasvaldesgreve/dis9079-2026-1/tree/main/21-isipm08>)
- Nicolás Elías Valdés Greve / [nicolasvaldesgreve](<https://github.com/nicolasvaldesgreve/dis9079-2026-1/tree/main/29-nicolasvaldesgreve>)

## Descripción textual del proyecto

<https://io.adafruit.com/udpmontoyamoraga/feeds/potenciometro-05>

## Materiales usados

| Componente | Valor Unidad | Cantidad | Link |
| --- | --- | --- | --- |
| Raspberry Pi Pico 2 W | $14.990 | 1 | <https://raspberrypi.cl/products/raspberry-pi-pico-2-w-con-headers> |
| Arduino UNO R4 WiFi | $38.990 | 1 | <https://arduino.cl/producto/arduino-uno-r4-wifi/?srsltid=AfmBOopyyargcSiTQeFlT3cTN5ide380bxZlQXRZVP4u_op0O-qJcENB> |
| Protoboard 400 puntos | $2.100 | 2 | <https://prodelab.cl/productos/didacticos/nivel-superior-y-ensenanza-media/robotica-y-programacion/accesorios-robotica-y-programacion/protoboard-breadboard-400-pines/> |
| Potenciómetro B20K | $495 | 1 | <https://altronics.cl/potenciometro-lineal-20k-b20k> |
| Cables Dupont (Pack 40 unidades) | $2.590 | 1 | <https://mcielectronics.cl/shop/product/cable-dupont-macho-macho-20cm-pack-40-unidades/> |
| Micro Servo Motor SG90 9g | $3.290 | 1 | <https://arduino.cl/producto/micro-servo-motor-sg90-9g/?srsltid=AfmBOoqZlsZtwx6MP23bWquVf5u5zZnS9a5CEJFEFpIcFrlUZCnyhxc5> |
| Botón Pulsador 4 pines | $570 | 1 | <https://www.victronics.cl/interruptores/boton-pcb-4-pines-spst-negro-redondo/> |

## Sensor usado

## Actuador usado

## Código usado para enviar

```cpp

import time
import board
import analogio
import digitalio
import wifi
import socketpool
import adafruit_minimqtt.adafruit_minimqtt as MQTT

# WiFi
wifi.radio.connect("si", "mailo6192")

# MQTT
pool = socketpool.SocketPool(wifi.radio)
mqtt = MQTT.MQTT(
    broker="io.adafruit.com",
    username="udpmontoyamoraga",
    password="keydeaarón",
    socket_pool=pool,
)

mqtt.connect()

# se configura el pin A0 como entrada para leer el potenciómetro
pot = analogio.AnalogIn(board.A0)

# se configura el pin GP0 para el botón,
# le dice a GP0 que es una entrada para que pueda leer datos
# se activa una resistencia interna que mantiene el pin en false cuando aún no presionamos el botón
button = digitalio.DigitalInOut(board.GP0)
button.direction = digitalio.Direction.INPUT
button.pull = digitalio.Pull.DOWN # aquí menciona que el botón funciona con el sistema pull down que menciona el video que está en nuestra bibliografía

while True:
    if button.value:  # solo envía si el botón fue presionado
        value = pot.value * 1023 // 65535
        print(f"Botón presionado - Enviando valor: {value}") # nos va a mencionar en putty cuando presionamos el botón, y el valor del potenciómetro

        mqtt.publish("udpmontoyamoraga/feeds/potenciometro-05", str(value))

        time.sleep(0.5)  # descanso pequeño jiji
```

## Código usado para recibir

```cpp
#include <Servo.h>
#include <WiFiS3.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"


#define WIFI_SSID    "si"
#define WIFI_PASS    "mailo6192"
#define AIO_SERVER   "io.adafruit.com"
#define AIO_PORT     1883
#define AIO_USERNAME "udpmontoyamoraga"
#define AIO_KEY      "keydeaarón"
#define AIO_FEED     AIO_USERNAME "/feeds/potenciometro-05"

const int SERVO_PIN = 9; // se indica dónde está el motor servo (pin 9 del arduino)
Servo miServo;

WiFiClient wifiClient;
Adafruit_MQTT_Client mqtt(&wifiClient, AIO_SERVER, AIO_PORT, AIO_USERNAME, AIO_KEY);

Adafruit_MQTT_Subscribe potFeed = Adafruit_MQTT_Subscribe(&mqtt, AIO_FEED);


// se conecta a wifi, y si no puede lo vuelve a intentar
void connectWiFi() {
  if (WiFi.status() == WL_CONNECTED) return;
  Serial.print("Conectando a WiFi");
  while (WiFi.begin(WIFI_SSID, WIFI_PASS) != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
  }
  Serial.println("\n WiFi conectado");
}


void connectMQTT() {
  int8_t ret;
  if (mqtt.connected()) return;
  Serial.print("Conectando a Adafruit IO");
  while ((ret = mqtt.connect()) != 0) {
    Serial.println(mqtt.connectErrorString(ret));
    mqtt.disconnect();
    delay(3000);
  }
  Serial.println("\n✓ Adafruit IO conectado");
}


void setup() {
  Serial.begin(115200); // cambiar el serial monitor a 115200 en caso de que no esté en ese valo
  delay(500);
  myServo.attach(SERVO_PIN);
  myServo.write(0); // posición inicial del servo
  connectWiFi();
  connectMQTT();
  mqtt.subscribe(&potFeed);
}

void loop() { // ésto es en caso de que se caiga la conexión
  connectWiFi();
  connectMQTT();

  Adafruit_MQTT_Subscribe* subscription = mqtt.readSubscription(500);

  if (subscription == &potFeed) {
    char* payload = (char*)potFeed.lastread;

    int rawValue = atoi(payload);
    rawValue = constrain(rawValue, 0, 1023);

    int angle = map(rawValue, 0, 1023, 0, 180);
    myServo.write(angle); // servo se mueve jijijiji
  }
}
```

## Imágenes del proyecto

## Animaciones del proyecto

## Bibliografía

+ <https://www.youtube.com/watch?v=d_odoKbEjgg&t=120s>, en donde nos enseñan cómo conectar un push button a una raspberry.
