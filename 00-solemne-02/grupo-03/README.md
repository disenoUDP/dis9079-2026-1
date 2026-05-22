# solemne-02

## Integrantes

- Magdalena Balart / magdalenabalart
- Jesús Miranda / jesumirandaa
- Carla Núñez / ccarlabelenn

## Descripción textual del proyecto

## Materiales usados

## Sensor usado

## Actuador usado

## Código usado para enviar

```cpp 
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
SSID = "internetmagdalena"
PASSWORD = "Magdita12345"

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
AIO_USERNAME = "usernameadafuit"
AIO_KEY = "keyadafruit"

# Feed al que se envían los mensajes
FEED_BOTON = AIO_USERNAME + "/feeds/prueba05"

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

# Contador de presiones
contador_boton = 0

# Mensajes que se enviarán en orden
mensajes = ["Sonrie por mi", "amigo", "yo sonrio por ti", "..."]

print("Sistema listo")
print("Esperando botón...")


# -------------------------
# Loop principal
# -------------------------
while True:

    try:
        mqtt.loop()

        estado_actual = boton.value

        # Detecta cuando el botón pasa de NO presionado a presionado
        if estado_anterior == True and estado_actual == False:

            mensaje = mensajes[contador_boton]

            print("Botón presionado")
            print("Enviando:", mensaje)

            mqtt.publish(FEED_BOTON, mensaje)

            print("Mensaje enviado a Adafruit IO")

            # Avanza al siguiente mensaje
            contador_boton = contador_boton + 1

            # Si ya mandó boton 03, vuelve a boton 01
            if contador_boton >= 4:
                contador_boton = 0

            # Anti-rebote
            time.sleep(0.3)

            # Espera a que sueltes el botón antes de leer otra presión
            while boton.value == False:
                mqtt.loop()
                time.sleep(0.01)

        estado_anterior = boton.value

    except Exception as e:
        print("Error:")
        print(e)

    time.sleep(0.02)  
``` 
    
## Código usado para recibir

```cpp
#include "config.h"

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// -------------------------
// Pantalla OLED
// -------------------------
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// -------------------------
// Feed Adafruit IO
// -------------------------
AdafruitIO_Feed *botonFeed = io.feed("prueba05");

// -------------------------
// Mostrar texto en pantalla
// -------------------------
void mostrarPantalla(String linea1, String linea2) {
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);

  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println(linea1);

 display.setTextSize(1);
 display.setCursor(0, 25);
 display.println(linea2);  

  display.display();
}

// -------------------------
// Cuando llega mensaje
// -------------------------
void handleMessage(AdafruitIO_Data *data) {
  String mensaje = data->toString();

  Serial.print("Mensaje recibido: ");
  Serial.println(mensaje);

  mostrarPantalla("Mensaje recibido:", mensaje);
}

// -------------------------
// Setup
// -------------------------
void setup() {
  Serial.begin(115200);
  delay(3000);

  Serial.println("Iniciando...");

  // Iniciar pantalla
  Wire.begin();

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("No se encontro pantalla OLED");
    while (true);
  }

  mostrarPantalla("Iniciando...", "");

  // Asociar feed a funcion
  botonFeed->onMessage(handleMessage);

  Serial.println("Conectando a Adafruit IO...");
  mostrarPantalla("Conectando a", "Adafruit");

  io.connect();

  while (io.status() < AIO_CONNECTED) {
    io.run();

    Serial.print("Estado: ");
    Serial.println(io.statusText());

    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 0);
    display.println("Conectando...");
    display.println(io.statusText());
    display.display();

    delay(1000);
  }

  Serial.println("Conectado a Adafruit IO");

  mostrarPantalla("Conectado!", "OK");

  delay(1500);

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("Esperando mensaje");
  display.println("del boton...");
  display.display();

  // Trae el ultimo mensaje enviado al feed
  botonFeed->get();
}

// -------------------------
// Loop
// -------------------------
void loop() {
  io.run();
}
```
## Config.h
```cpp
/** Adafruit IO Config **/

#define IO_USERNAME  "Magdalena"
#define IO_KEY       "keyadafruit"

/** WiFi Config **/

#define WIFI_SSID    "internetmagdalena"
#define WIFI_PASS    "Magdita12345"

/** Librería Adafruit IO */

#include "AdafruitIO_WiFi.h"

AdafruitIO_WiFi io(IO_USERNAME, IO_KEY, WIFI_SSID, WIFI_PASS);
```

## Imágenes del proyecto

## Animaciones del proyecto

## Bibliografía
