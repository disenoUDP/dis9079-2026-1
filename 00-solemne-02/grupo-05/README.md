# solemne-02

## Integrantes

- Renata De Los Ángeles Arévalo Urra / [arevalourra](<https://github.com/nicolasvaldesgreve/dis9079-2026-1/tree/main/06-arevalourra>)
- Isidora Andrea Pérez Maulén / [isipm08](<https://github.com/nicolasvaldesgreve/dis9079-2026-1/tree/main/21-isipm08>)
- Nicolás Elías Valdés Greve / [nicolasvaldesgreve](<https://github.com/nicolasvaldesgreve/dis9079-2026-1/tree/main/29-nicolasvaldesgreve>)

## Descripción textual del proyecto

Como proyecto para la segunda solemne del curso se nos indicó el, al igual que la vez pasada, lograr una comunicación inalámbrica utilizando códigos en dos microcontroladores los cuales serán una placa Arduino R4 WiFI y una Raspberry Pi Pico 2 W. En nuestro caso, se utilizará la Raspberry Pi Pico 2 W para poder enviar información hacia el Arduino UNO R4 WiFi, lo cual se hará de la siguiente manera:

#### Raspberry Pi Pico 2 W

En éste microcontrolador estarán conectados los siguientes componentes:

1. Potenciómetro B20K
2. Push button 4 pins
3. Diodo LED
4. Resistencia 220 Ω

El potenciómetro estará conectado de la siguiente manera: el pin izquierdo del potenciómetro estará conectado al pin 13 ``GND`` de la Raspberry, el pin de en medio está conectado al pin 36 ``3V3 (out)``, y el pin derecho está conectado al pin 31 ``ADC0``.

El push button está conectado al pin 28 ``GND`` de la Raspberry y al pin 1 ``GP0``.

El LED está conectado mediante una resistencia de 220 Ω al pin 2 ``GP1``, el cual llega al pin positivo del LED. El pin negativo del LED va conectado al pin 18 ``GND``.

#### Arduino UNO R4 WiFi

En éste microcontrolador solo va conectado el Micro Servo Motor SG90 9g, el cual se conecta de la siguiente manera: El cable de color rojo va al pin ``5V`` el cual está ubicado en la sección ``POWER`` del Arduino, el cable de color café va en el pin ``GND`` que está ubicado en la sección ``POWER`` o ``DIGITAL`` y el cable de color amarillo va conectado en el pin ``9~`` ubicado en la sección ``DIGITAL`` de la placa.

---

Una vez tengamos todos los componentes conectados a sus respectivos microcontroladores, podremos empezar a comunicarnos entre ellos utilizando los códigos que se mencionan más abajo, los cuales fueron creados con asistencia de las inteligencias artificiales _Claude_ y _Chat GPT_. La manera en la que funciona ésto es que, cuando mantenemos presionado el push button que está ubicado en la Raspberry, se empezarán a enviar los datos numéricos que podemos modificar moviendo el potenciómetro, el cual dependiendo del valor que se envíe el Motor Servo se moverá. Mientras todo ésto sucede, el LED nos indicará cuándo estamos manteniendo presionado el push button, ya que cuando lo presionamos se encenderá la luz, y cuando no estemos ejerciendo ninguna presión, se mantendrá apagado.

Todos los datos del potenciómetro se pueden visualizar en tiempo real en este link:

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
| Diodo LED | $70 | 1 | <https://afel.cl/products/diodo-led-5mm-ultrabrillante-azul?pr_prod_strat=jac&pr_rec_id=1cd69e264&pr_rec_pid=8382019502232&pr_ref_pid=8382019600536&pr_seq=uniform> |

## Sensor usado

Para éste proyecto se utilizó un potenciómetro y un push button como sensor, en los cuales el push button cumple la función de decidir cuándo enviar información, la cual la genera el potenciómetro y éste va cambiando cada vez que uno lo mueve --- REDACTAR MEJOR AYUDA LOL

## Actuador usado

Nuestros actuadores en éste proyecto son el Micro Servo Motor SG90 9g y una luz LED, en donde el LED cumple la función de detectar cuando estamos presionando el push button, es decir, cuándo estamos permitiendo que se envíe información. En cambio con el motor servo, éste se encarga de recibir la información que le envía el potenciómetro y reacciona en base a éste. -- NO SÉ QUE MÁS PONER ASI QUE TAMBIÉN REDACTAR MEJOR PLS AYUDA

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
SSID = "si"
PASSWORD = "mailo6192."

print("Conectando WiFi...")
wifi.radio.connect(
    SSID,
    PASSWORD
)
print("WiFi conectado")

# MQTT
pool = socketpool.SocketPool(wifi.radio)
mqtt = MQTT.MQTT(
    broker="io.adafruit.com",
    username="udpmontoyamoraga",
    password="keydeaarón",
    socket_pool=pool
)
mqtt.connect()
print("MQTT conectado")

# Potenciómetro A0
pot = analogio.AnalogIn(board.A0)

# Botón GP0
button = digitalio.DigitalInOut(board.GP0)
button.direction = digitalio.Direction.INPUT
button.pull = digitalio.Pull.UP

# LED GP1
led = digitalio.DigitalInOut(board.GP1)
led.direction = digitalio.Direction.OUTPUT

ultimo_valor = -1

while True:
    # Con PULL_UP:
    # False = presionado
    # True = suelto
    if not button.value:
        # Encender LED al presionar
        led.value = True

        valor = pot.value * 1023 // 65535
        # Evita enviar repetidos innecesarios
        if abs(valor - ultimo_valor) > 5:
            print("Enviando:", valor)
            mqtt.publish(
                "udpmontoyamoraga/feeds/potenciometro-05",
                str(valor)
            )
            ultimo_valor = valor
        time.sleep(0.2)
    else:
        # Apagar LED al soltar
        led.value = False
        time.sleep(0.01)
```

## Código usado para recibir

```cpp
#include <WiFiS3.h>
#include <Servo.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"

// WiFi
#define WLAN_SSID "si"
#define WLAN_PASS "mailo6192."

// Adafruit IO
#define AIO_SERVER     "io.adafruit.com"
#define AIO_SERVERPORT 1883
#define AIO_USERNAME   "udpmontoyamoraga"
#define AIO_KEY        "keydeaarón"

// Pin LED
#define LED_PIN 13

WiFiClient client;
Adafruit_MQTT_Client mqtt(
  &client,
  AIO_SERVER,
  AIO_SERVERPORT,
  AIO_USERNAME,
  AIO_KEY
);

// Suscribirse al feed
Adafruit_MQTT_Subscribe potenciometro =
Adafruit_MQTT_Subscribe(
  &mqtt,
  AIO_USERNAME "/feeds/potenciometro-05"
);

Servo miServo;
void MQTT_connect();

void setup() {
  Serial.begin(115200);
  miServo.attach(9);

  // LED como salida
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

  Serial.println("Conectando WiFi");
  WiFi.begin(WLAN_SSID, WLAN_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.println("WiFi conectado");

  mqtt.subscribe(&potenciometro);
}

void loop() {
  MQTT_connect();

  Adafruit_MQTT_Subscribe *subscription;
  while ((subscription = mqtt.readSubscription(1000))) {
    if (subscription == &potenciometro) {
      int valorPot = atoi(
        (char*)potenciometro.lastread
      );
      Serial.print("Recibido: ");
      Serial.println(valorPot);

      // Encender LED al recibir mensaje
      digitalWrite(LED_PIN, HIGH);
      delay(200);
      digitalWrite(LED_PIN, LOW);

      // Convertir 0-1023 a 0-180°
      int angulo = map(valorPot, 0, 1023, 0, 180);
      angulo = constrain(angulo, 0, 180);

      Serial.print("Ángulo: ");
      Serial.println(angulo);
      miServo.write(angulo);
    }
  }
}

void MQTT_connect() {
  int8_t ret;
  if (mqtt.connected()) {
    return;
  }
  Serial.print("Conectando MQTT...");
  while ((ret = mqtt.connect()) != 0) {
    Serial.println(mqtt.connectErrorString(ret));
    mqtt.disconnect();
    delay(5000);
  }
  Serial.println(" conectado");
}
```

## Imágenes del proyecto

**ENVIAR**
![titulo](./imagenes/enviar.jpeg)

**RECIBIR**
![titulo](./imagenes/recibir.jpeg)

**CONJUNTO**
![titulo](./imagenes/conjunto.jpeg)

## Animaciones del proyecto

## Bibliografía

+ <https://www.youtube.com/watch?v=d_odoKbEjgg&t=120s>, en donde nos enseñan cómo conectar un push button a una raspberry.
+ <https://www.instructables.com/Control-LED-From-Internet-Using-Raspberry-Pi-Pico-/>, en donde nos enseñan cómo conectar un LED a una raspberry.
+ 
