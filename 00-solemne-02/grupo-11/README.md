# solemne-02

## Integrantes

- Martina Alegria / AlegriaColoma
- Antonella Lavalle / antolavalle
- Catalina Salinas / catasal

## Descripción textual del proyecto

* Para lograr la comunicación entre ambas placas, se utilizó la plataforma Adafruit IO como intermediario en la nube, empleando el protocolo de mensajería MQTT. Este protocolo permite enviar y recibir mensajes pequeños a través de internet de forma eficiente.

### Lado de la Raspberry Pi Pico W

La Raspberry Pi Pico W se conecta a una red WiFi y luego establece conexión con Adafruit IO mediante MQTT. Un botón físico está conectado al pin GP0 de la placa. Cuando se presiona el botón, el programa detecta el cambio de estado y publica un mensaje en el feed correspondiente. Para evitar lecturas falsas por rebote mecánico del botón, se agregó una pequeña pausa de 250 milisegundos tras cada pulsación.

### Lado del Arduino Uno R4 WiFi

El Arduino se conecta a la misma red WiFi y al mismo feed de Adafruit IO. Cada vez que llega un mensaje al feed, se ejecuta automáticamente una función que lee el contenido del mensaje. Si el mensaje dice "ON", enciende un LED; si dice "OFF", lo apaga.
  
## Materiales usados
* Raspberry Pi pico 2
* Arduino R4
* el LEDBotón pulsador (push button 4 patas)
* LED (cualquier color)
* Resistencia 220Ω1Protege el LED de sobrecorriente
* Protoboard (placa de pruebas)
* Cables puente macho-macho
* Cable micro-USB1
* Cable USB-C

## Prueba de códigos

### Problemas encontrados durante el desarrollo

Durante las pruebas se presentaron algunos inconvenientes. El código del Arduino funcionaba correctamente en un computador, pero al intentar usarlo desde otro equipo, el programa cargaba pero no lograba recibir los mensajes del feed. Para resolver esto, se optó por mantener el Arduino conectado al computador donde el código había sido verificado, y la Raspberry Pi Pico W se operó desde el otro equipo. Con esta configuración el sistema comenzó a funcionar correctamente.

Respecto al LED, se observó que el LED externo no encendía, pero sí lo hacía el LED de transmisión (TX) de la placa al momento de recibir cada mensaje, lo que confirmó que la comunicación entre ambos dispositivos estaba operando con éxito.

### Prueba a distancia

Finalmente, el sistema fue probado con ambas placas separadas aproximadamente 6 metros entre sí, logrando una comunicación exitosa, lo que demostró que el envío de información funciona de forma inalámbrica sin necesidad de proximidad física entre los dispositivos.

<img width="1600" height="1200" alt="Placas y cables 22-05" src="https://github.com/user-attachments/assets/7f1432c7-e8b8-49f1-b60d-52b68aa59e93" />

## Sensor usado

Botón 

 Un botón pulsador normal tiene 4 patas pero solo 2 circuitos internos: las patas A-B están siempre conectadas entre sí, y las patas C-D están siempre conectadas entre sí. Cuando apretás el botón, A-B se conecta con C-D. Por eso solo usás una pata de cada lado.
No necesitás resistencia externa porque el código usa Pin.PULL_UP, que activa una resistencia interna del Pico que mantiene GP15 en nivel alto (HIGH) cuando el botón no está presionado. Al presionar, GP15 cae a nivel bajo (LOW) y el Pico detecta ese cambio.

<img width="487" height="460" alt="boton" src="https://github.com/user-attachments/assets/27a12dc5-1013-4e0c-a581-41366887edde" />

<img width="504" height="579" alt="pico2w" src="https://github.com/user-attachments/assets/7bf40e4d-8da1-4b7d-9845-838e607ed848" />

<img width="880" height="463" alt="inalambrico" src="https://github.com/user-attachments/assets/881f277e-f0f4-46e5-ac69-5ec51a5124f7" />

durante la clase se probo con enviar datos al adafruit
<img width="1882" height="861" alt="io adafruit" src="https://github.com/user-attachments/assets/a86efa48-aaeb-46b4-947a-0579609b8873" />

## Actuador usado

- LEDS
  
## Código usado para enviar

import time
import board
import digitalio
import wifi
import socketpool
import adafruit_minimqtt.adafruit_minimqtt as MQTT

print("Iniciando programa...")

# -------------------------
# WiFi
# -------------------------
SSID = "cata"
PASSWORD = "blabla"

print("Conectando WiFi...")

try:
    wifi.radio.connect(SSID, PASSWORD)
    print("WiFi conectado")
    print("IP:", wifi.radio.ipv4_address)

except Exception as e:
    print("Error WiFi:")
    print(e)

    while True:
        pass


# -------------------------
# Adafruit IO
# -------------------------
AIO_USERNAME = "AlegriaColoma"
AIO_KEY = "blabla"

FEED_BOTON = AIO_USERNAME + "/feeds/prueba"

print("Creando conexión MQTT...")

pool = socketpool.SocketPool(wifi.radio)

mqtt = MQTT.MQTT(
    broker="io.adafruit.com",
    username=AIO_USERNAME,
    password=AIO_KEY,
    socket_pool=pool,
)

print("Conectando a Adafruit IO...")

try:
    mqtt.connect()
    print("Conectado a Adafruit IO")

except Exception as e:
    print("Error MQTT:")
    print(e)

    while True:
        pass


# -------------------------
# Botón GP0
# -------------------------
boton = digitalio.DigitalInOut(board.GP0)
boton.direction = digitalio.Direction.INPUT
boton.pull = digitalio.Pull.UP

estado_anterior = True

print("Sistema listo")

# -------------------------
# Loop principal
# -------------------------
while True:

    try:
        mqtt.loop()

        estado_actual = boton.value

        # Detecta transición:
        # sin presionar -> presionado
        if estado_anterior and not estado_actual:

            print("Botón presionado")
            print("Enviando impulso...")

            mqtt.publish(FEED_BOTON, "1")

            print("Impulso enviado")

            # anti-rebote
            time.sleep(0.25)

        estado_anterior = estado_actual

    except Exception as e:
        print("Error:")
        print(e)

    time.sleep(0.02)

## Código usado para recibir

´´´cpp

/******
   PROYECTO: CONTROL LED DESDE ADAFRUIT IO
******/

#include "AdafruitIO_WiFi.h"

// ==========================================
// CREDENCIALES WIFI Y ADAFRUIT IO
// ==========================================

#define IO_USERNAME  "AlegriaColoma"
#define IO_KEY       "blabla"

#define WIFI_SSID    "cata"
#define WIFI_PASS    "blabla"

// ==========================================
// CONEXIÓN ADAFRUIT IO
// ==========================================

AdafruitIO_WiFi io(
  IO_USERNAME,
  IO_KEY,
  WIFI_SSID,
  WIFI_PASS
);

// ==========================================
// CONFIGURACIÓN
// ==========================================

// Pin LED
const int ledPin = 13;

// Feed
AdafruitIO_Feed *controlLED = io.feed("prueba");

// ==========================================
// SETUP
// ==========================================

void setup() {

  // Iniciar LED
  pinMode(ledPin, OUTPUT);

  // Monitor serial
  Serial.begin(115200);

  while(!Serial);

  Serial.println("Conectando a Adafruit IO...");

  // Conexión
  io.connect();

  // Evento al recibir mensaje
  controlLED->onMessage(cambiarEstadoLED);

  // Esperar conexión
  while(io.status() < AIO_CONNECTED) {

    Serial.print(".");
    delay(500);
  }

  Serial.println();
  Serial.println("¡Conectado correctamente!");
}

// ==========================================
// LOOP PRINCIPAL
// ==========================================

void loop() {

  // Mantener conexión
  io.run();
}

// ==========================================
// FUNCIÓN PARA PRENDER/APAGAR LED
// ==========================================

void cambiarEstadoLED(AdafruitIO_Data *data) {

  String estado = data->toString();

  Serial.print("Dato recibido: ");
  Serial.println(estado);

  // PRENDER LED
  if(estado == "ON") {

    digitalWrite(ledPin, HIGH);

    Serial.println("LED ENCENDIDO");
  }

  // APAGAR LED
  else if(estado == "OFF") {

    digitalWrite(ledPin, LOW);

    Serial.println("LED APAGADO");
  }
}
  
## Imágenes del proyecto
<img width="900" height="1600" alt="WhatsApp Image 2026-05-21 at 19 02 01" src="https://github.com/user-attachments/assets/fc3011c3-77e6-49eb-8ea7-3f1cd5e51e51" />

<img width="807" height="642" alt="luz led" src="https://github.com/user-attachments/assets/79fb90f6-19b8-4cad-97b7-6ded2a79117a" />

## Animaciones del proyecto
al principo probamos sin colocar un cable puente en la entrada 13
https://github.com/user-attachments/assets/a0d115bc-8573-45b9-bbcb-b2d1fac5d7e9 

https://github.com/user-attachments/assets/ff885a3a-38ae-4f76-9ec6-ffaf2f524898

## Bibliografía
chat gpt

claude 

Mateo 

compañeros
