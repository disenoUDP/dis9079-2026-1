# solemne-02

## Integrantes
 
- Josefa Araya / [josefa-kristina](https://github.com/josefa-kristina)
- Débora Soto / [DebSkar](https://github.com/DebSkar)
- Cristóbal Vergara / [cristobalvergarasilva](https://github.com/cristobalvergarasilva)
  
## Descripción textual del proyecto
 
Para la segunda solemne, el encargo consistió en usar microcontroladores para realizar una comunicación inalámbrica a través de Adafruit IO, usando sensores y actuadores.
 
Para la realización de nuestro proyecto, usamos un potenciómetro conectado a una Raspberry Pi Pico 2W, que envía valores a un motor servo, el cual va conectado a un Arduino R4 WiFi. El motor servo recibe los valores y los transforma en ángulos; además, utilizamos un botón pulsador de 4 pines que permite dejar de enviar datos para no sobrecargar la nube.
 
Toda esta interacción se realiza mediante un feed de Adafruit IO.
 
El primer paso fue eliminar el firmware de la Raspberry; este se tiene que reemplazar por el archivo `code.py` de CircuitPython 10.2.0. Luego practicamos con un código que nos dio Aarón para conectarla a Adafruit IO, el mismo que después usamos como base para comenzar a modificar el nuestro.
 
Le dimos a Claude AI el siguiente prompt:
 
> *"Estamos haciendo un proyecto en el cual tenemos que conectar una Raspberry controlada por un potenciómetro, a través de una nube en Adafruit IO, a un Arduino UNO R4 con un motor servo. ¿Cómo podríamos hacer que el potenciómetro conectado a la Raspberry controle el servo conectado al Arduino a través de Adafruit?"*
 
Cuando tratamos de modificar el código en Visual Studio Code, no nos funcionaba. Después de un rato nos dimos cuenta de que lo estábamos ejecutando en el computador y no en la Raspberry. Solucionado eso, guardamos el código en su carpeta interna y lo comenzamos a correr y vimos si funcionaba usando PuTTY para visualizar el puerto serial.
 
En PuTTY tuvimos el siguiente problema: *"Error de módulo (no module named...)"*.
 
Estuvimos un buen rato estancados en eso hasta que le preguntamos a Claude y nos dio lo siguiente para escribir en PuTTY:

import sys
print(sys.version)

import wifi
print("wifi OK")

import adafruit_minimqtt.adafruit_minimqtt
print("mqtt OK")

import adafruit_io.adafruit_io
print("adafruit_io OK")

<img src="./imagenes/terminalputty.jpeg " alt="install" width="500">


Así se solucionó el problema y comenzó a correr exitosamente.
En la clase siguiente, le comentamos a Aarón lo que habíamos hecho y nos dijo que cambiaríamos la temática de nuestro proyecto, puesto que queríamos hacer una 
guillotina que le cortara la cabeza a Kast, y nos comentó que él no merecía nuestra atención. Se nos sugirió hacer algo más interesante con el movimiento del
motor servo, el cual teníamos con un movimiento estándar entre los 0° y 180°. Este movimiento lo cambiamos con un código para que se moviera entre los 45° y 135°.
Con este código solo se publicaba en Adafruit cuando el ángulo cambiaba más de 2° para no superar el límite de los 30 mensajes por minuto. Aun con esto logramos 
sobrecargar nuestro feed, por lo que modificamos el código para que enviara los datos cada 5 segundos.

Línea modificada:

`if abs(angle - last_angle) = 2 and (now - last_send_time) = 5`

Aarón nos sugirió que hiciéramos algo más tangible para controlar la sobrecarga de datos y que habláramos con el grupo 05, quienes estaban usando un botón push 
para controlar el envío de datos. Nicolás nos explicó cómo lo querían hacer funcionar, creando un RPullDown, asegurando que la entrada lea un estado bajo 
constante hasta que, al presionar el botón, la lleve a un voltaje alto; esto para no tener que usar una resistencia en las conexiones físicas. También nos explicó 
cómo hacer la conexión del botón a la Raspi.

Por recomendación de Aarón buscamos documentos que tuvieran un código parecido al que necesitábamos. 

Encontramos:
<https://docs.sunfounder.com/projects/pico-2w-kit/en/latest/cproject/ar_button.html>

En un inicio tratamos de hacer la conexión con un resistor de 220 ohms, a recomendación de Aarón:
<img src="./imagenes/intentoresistor.jpeg" alt="install" width="500">

Luego vimos la posibilidad de hacerlo con un RPullUp o un RPullDown, como aparecía en el documento y como lo hicieron en el grupo 05; decidimos esto último para que la protoboard no estuviera tan saturada de conexiones.

<img src="./imagenes/intentoboton.jpeg" alt="install" width="500">

Luego de implementar en nuestro código los fragmentos del sitio, lo corrimos y ahora solo se enviaban datos cuando movíamos el potenciómetro (antes se enviaban siempre cada 0,2 segundos).

Seguimos trabajando en el envío de datos y comenzamos a probar con distintos fragmentos del primer código que nos funcionó. Le pedimos a nuestros compañeros del grupo 05 si nos podían ayudar, así que nos mostraron cómo era la parte de su código que hacía funcionar el botón. Entonces comenzamos a modificarlo y fuimos sumando las partes que nos servían a nuestro código.

Finalmente dio resultado y PuTTY reconoció el botón, pero nos daba el siguiente error:

> *"('Unable to receive 1 bytes within 10 seconds. ', None) - reconectando…"*

<img src="./imagenes/error.jpeg" alt="install" width="500">

Así que le preguntamos a Claude qué significaba ese error y nos dijo que el problema se encontraba en `mqtt.loop()`, porque el broker corta la conexión por inactividad. También teníamos otro problema:

> *MMQTTException: ('Connection Refused - Unauthorized', 5)*

<img src="./imagenes/errorindentacion.jpeg" alt="install" width="500">

Resultó que el problema era que el nombre de usuario de Adafruit, "Kaiikou", estaba escrito en minúscula. Lo corregimos y ahí funcionó: el botón detenía el envío de información cuando era presionado.

<img src="./imagenes/prueba.gif" alt="install" width="500">

<img src="./imagenes/feedservo.jpeg" alt="install" width="500">

Luego de poder integrar el botón y que funcionara en el código, decidimos darle una intención al movimiento del motor servo. Primero intentamos con un movimiento
más rápido definiendo 3 ejes: derecha, centro e izquierda, controlando el `MOVING_TIME` y poniéndolo en 300 ms. El resultado no nos satisfizo, por lo que 
ralentizamos el movimiento subiendo los milisegundos a 1000, y este resultado nos dejó satisfechos.

## Materiales usados
| Componente | Cantidad | Valor Unidad | Link |
| --- | --- | --- | --- |
| Raspberry Pi Pico 2W | 1 | $14.990 | <https://raspberrypi.cl/products/raspberry-pi-pico-2-w-con-headers>|
| AArduino UNO R4 WiFi | 1 | $$38,990 |<https://arduino.cl/producto/arduino-uno-r4-wifi/?srsltid=AfmBOoqwfINu-FJZk1WDnGEYJtedpDJvTJDexifC6sv4sWK-dkDemYzB>|
| Micro Servo Motor SG90 9g | 1 | $3.290 | <https://mcielectronics.cl/shop/product/micro-servo-motor-sg90-9g-25775/?gad_source=1&gad_campaignid=21444224314&gbraid=0AAAAADijL1VxzGcSMKlmDhlqY2cOAjRxf&gclid=Cj0KCQjw_b_QBhCSARIsAP6hR4elepSjJKN4jPfIKgfN_K-b6ohCxZjZjnqn1VFlP0gA9_3-oqqY5n0aAmWzEALw_wcB> |
| Cables Dupont | 1 | $65 | <https://mcielectronics.cl/shop/product/cable-dupont-macho-macho-20cm-pack-40-unidades/> |
| Potenciometro 20K Ohm | 1 | $500 | <https://afel.cl/products/potenciometro-20k-ohm?_pos=3&_sid=bc780bb62&_ss=r/> |
| Boton pulsador switch de 4 pines push button 6x6x4.3mm | 1 | $290 | <https://www.mechatronicstore.cl/push-button-4-pines/> |

## Sensor usado

**Potenciómetro 20K Ohm**
Resistencia que puede variar su valor de forma manual. Está compuesta de tres puntos de conexión, de los cuales dos son fijos y están conectados a un elemento
resistivo, y el otro está conectado a una pieza que se desliza de lado a lado. Puntualmente, el que utilizamos va desde 0 ohm hasta 20K ohm.

<img src="./imagenes/potenciometro.png" alt="install" width="500">

**Botón pulsador**
Los botones push son componentes que sirven para controlar el flujo de corriente al ser accionados.
<img src="./imagenes/botonpush.jpg" alt="install" width="500">

## Actuador usado

**Micro Servo Motor SG90 9g**
Es un actuador controlable que recibe señales especificando los ángulos en los que tiene que girar. Puntualmente, el nuestro va de 0° a 180°.

## Código usado para enviar

```cpp
import time
import board
import analogio
import digitalio
import wifi
import socketpool
import adafruit_minimqtt.adafruit_minimqtt as MQTT


# ── Configuración ──────────────────────────────────────────────────────────────
WIFI_SSID    = "NombreRedWifi"
WIFI_PASS    = "ContraseñaWifi"
AIO_USERNAME = "UsernameAio"
AIO_KEY      = "KeyAio"
FEED         = f"{AIO_USERNAME}/feeds/AioFeed"
INTERVALO        = 0.2   # segundos entre lecturas del loop
INTERVALO_ENVIO  = 3.0   # segundos máximos sin enviar (aunque no haya cambio)


# ── Hardware ───────────────────────────────────────────────────────────────────
pot = analogio.AnalogIn(board.A0)


button = digitalio.DigitalInOut(board.GP0)
button.direction = digitalio.Direction.INPUT
button.pull = digitalio.Pull.UP


# ── Helpers ────────────────────────────────────────────────────────────────────
def map_value(x, in_min, in_max, out_min, out_max):
    return int((x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min)


def conectar_wifi():
    if not wifi.radio.connected:
        print("Conectando a WiFi...")
        wifi.radio.connect(WIFI_SSID, WIFI_PASS)
        print(f"WiFi OK — IP: {wifi.radio.ipv4_address}")


def crear_mqtt():
    pool = socketpool.SocketPool(wifi.radio)
    cliente = MQTT.MQTT(
        broker="io.adafruit.com",
        port=1883,
        username=AIO_USERNAME,
        password=AIO_KEY,
        socket_pool=pool,
    )
    return cliente


def reconectar(mqtt):
    try:
        conectar_wifi()
        mqtt.reconnect()
        print("Reconectado a MQTT!")
        return True
    except Exception as e:
        print(f"Reintento fallido: {e}")
        return False


# ── Conexión inicial ───────────────────────────────────────────────────────────
conectar_wifi()
mqtt = crear_mqtt()
mqtt.connect()
print("MQTT conectado!")


# ── Estado ─────────────────────────────────────────────────────────────────────
ultimo_valor        = -1
pausado_antes       = False
ultimo_envio        = time.monotonic()  # <-- temporizador


# ── Loop principal ─────────────────────────────────────────────────────────────
while True:
    try:
        mqtt.loop()


        boton_presionado = not button.value
        ahora = time.monotonic()


        if boton_presionado:
            if not pausado_antes:
                print("Envío pausado (botón presionado)")
                pausado_antes = True
        else:
            if pausado_antes:
                print("Reanudando envío...")
                pausado_antes = False
                ultimo_envio = ahora  # reinicia el temporizador al reanudar


            angulo = map_value(pot.value, 0, 65535, 0, 180)


            hay_cambio        = abs(angulo - ultimo_valor) >= 2
            tiempo_cumplido   = (ahora - ultimo_envio) >= INTERVALO_ENVIO


            if hay_cambio or tiempo_cumplido:  # <-- la clave del cambio
                print(f"Publicando: {angulo}°")
                mqtt.publish(FEED, str(angulo))
                ultimo_valor = angulo
                ultimo_envio = ahora  # reinicia el temporizador


        time.sleep(INTERVALO)


    except (MQTT.MMQTTException, OSError, RuntimeError) as e:
        print(f"Conexión perdida: {e}")
        print("Esperando 5 segundos antes de reconectar...")
        time.sleep(5)
        reconectar(mqtt)
```




## Código usado para recibir

```cpp
#include <WiFiS3.h>
#include <Servo.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"


// WiFi


#define WIFI_SSID "NombreRedWifi"
#define WIFI_PASS "ContraseñaWifi"


// Adafruit IO


#define AIO_SERVER     "io.adafruit.com"
#define AIO_PORT        1883
#define AIO_USERNAME   "UsernameAio"
#define AIO_KEY        "KeyAio"






//  Servo


Servo myServo;
const int SERVO_PIN = 9;


// limitantes de movimiento
#define IZQUIERDA  45
#define DERECHA   135
#define CENTRO     90


// variables de movimiento
unsigned long MOVING_TIME = 1000;   // ms para llegar al destino (más bajo = más rápido)
unsigned long moveStartTime;
int startAngle  = CENTRO;          // ángulo desde donde parte
int targetAngle = CENTRO;          // ángulo destino recibido por MQTT
int currentAngle = CENTRO;         // ángulo actual del servo


// --- MQTT ---
WiFiClient wifiClient;
Adafruit_MQTT_Client mqtt(&wifiClient, AIO_SERVER, AIO_PORT, AIO_USERNAME, AIO_KEY);
Adafruit_MQTT_Subscribe servoFeed = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/AioFeed");


void connectWiFi() {
  Serial.print("Conectando a WiFi");
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500); Serial.print(".");
  }
  Serial.println("\nWiFi conectado: " + WiFi.localIP().toString());
}


void connectMQTT() {
  int8_t ret;
  while ((ret = mqtt.connect()) != 0) {
    Serial.print("Error MQTT :( ");
    Serial.println(mqtt.connectErrorString(ret));
    Serial.println("Reintentando en 3s...");
    mqtt.disconnect();
    delay(3000);
  }
  Serial.println("MQTT conectado :D!");
}


int mapearRango(int angle) {
  return map(angle, 0, 180, IZQUIERDA, DERECHA);
}


void setup() {
  Serial.begin(115200);
  myServo.attach(SERVO_PIN);
  myServo.write(CENTRO);
  moveStartTime = millis();


  Serial.println("Izquierda = " + String(IZQUIERDA) + "°");
  Serial.println("Centro    = " + String(CENTRO)    + "°");
  Serial.println("Derecha   = " + String(DERECHA)   + "°");


  connectWiFi();
  mqtt.subscribe(&servoFeed);
  connectMQTT();
}


void loop() {
  if (!mqtt.connected()) connectMQTT();


  //Ping cada 60s para no bloquear el loop
  static unsigned long lastPing = 0;
  if (millis() - lastPing > 60000) {
    mqtt.ping();
    lastPing = millis();
  }


  //Leer nuevo ángulo desde Adafruit IO
  Adafruit_MQTT_Subscribe* subscription;
  while ((subscription = mqtt.readSubscription(5))) {
    if (subscription == &servoFeed) {
      int received = atoi((char*)servoFeed.lastread);
      int mapped   = constrain(mapearRango(received), IZQUIERDA, DERECHA);


      // Solo actualizar si el ángulo cambió
      if (mapped != targetAngle) {
        startAngle    = currentAngle;  // parte desde donde está ahora
        targetAngle   = mapped;
        moveStartTime = millis();      // reinicia el movimiento
        Serial.println("Destino: " + String(targetAngle) + "°");
      }
    }
  }


  // Mover servo progresivamente hacia el destino
  unsigned long progress = millis() - moveStartTime;


  if (progress <= MOVING_TIME) {
    currentAngle = map(progress, 0, MOVING_TIME, startAngle, targetAngle);
    myServo.write(currentAngle);
  } else {
    currentAngle = targetAngle;
    myServo.write(currentAngle);
  }
}

```


## Imágenes del proyecto


<img src="./imagenes/fotoproyecto.jpeg" alt="install" width="500">


<img src="./imagenes/raspirosa.jpeg" alt="install" width="500">


<img src="./imagenes/pasillo.jpeg" alt="install" width="500">


<img src="./imagenes/monitorserial.jpeg " alt="install" width="500">




## Animaciones del proyecto


<img src="./imagenes/enviar.gif " alt="install" width="500">

Enviando 

<img src="./imagenes/recibir.gif " alt="install" width="500">

Recibiendo







## Bibliografía

<https://eepower.com/resistor-guide/resistor-types/potentiometer/#>

<https://www.youtube.com/watch?v=sWbSeJmUFfw>

<https://docs.sunfounder.com/projects/pico-2w-kit/en/latest/cproject/ar_button.html>

<https://raspberrypi.cl/products/raspberry-pi-pico-2-w-con-headers>

<https://www.codigoiot.com/base-de-conocimiento/botones/>


