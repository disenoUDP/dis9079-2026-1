# Grupo-07

## Integrantes

* Josefa Araya 
* Débora Soto 
* Cristóbal Vergara

## Descripción del proyecto

El Arduino se conecta a una red WiFi y luego establece comunicación con Adafruit IO usando el protocolo MQTT en Arduino Ide.
Desde cualquier otro computador o celular, entras al dashboard de Adafruit IO en el navegador y presionas un botón toggle. Ese click viaja por internet hasta los servidores de Adafruit, que se lo reenvían al Arduino. El Arduino recibe el mensaje y enciende o apaga el LED.

Partimos utilizando el código de ejemplo que subió Aaron a Github, para aprender como funcionaban las conexiones en base a una nube pero de primeras no funcionaba, y tras un rato investigando, dimos con que estabamos dando mal las credenciales que habia que cambiar del código, puntualmente la clave que estabamos poniendo,era la personal para ingresar al sitio, pero resulta que era la AIO Key, que es una clave alfanumérica que te da el Adafruit IO para poder conectarte a la nube.
Luego de solucionar eso el código estaba bien, pero aún así no se conectaba, solo aparecía una serie de puntos infinitos (...........) que no nos dimos cuenta, hasta que en clases Aaron actualizó los Arduinos que tenian ese error y se solucionó, resulta que al final de los puntos habia un mensaje de "Please upgrade the WiFiS3 firmware!" pero no alcanzaba a verse.
Una vez actualizado el Arduino pudimos conectar bien con Adafruit IO y probamos con un ejercicio que nos dió Aaron, que consistía en conectarse a un feed en Adafruit IO el cual estaba conectado a una Dashboard con un contador,ese ejercicio si funcionó.

Durante la clase del lunes 06, quisimos intentar lograr prender un led conectado a una protoboard, pero ningún código nos funcionó.

Luego de esos intentos fallidos de la clase pasada, seguíamos con las ganas de controlar el LED conectado al Arduino, mediante el dashboard de Adafruit IO, así que investigamos un poco en blogs, foros y github pero no logramos crear el código desde 0 así que acudimos a Claude AI con lo que queriamos hacer.

le escribimos el siguiente prompt:

>Necesito generar un codigo para arduino ide que me permita controlar de otro computador a traves de adafruit io el arduino conectado a otro computador, este arduino tambien tendria conectado una luz led que me gustaria prender y apagar desde los dashboards de adafruit io.

Creamos un feed en Adafruit IO con el nombre de led-control y un Dashboard vinculado a este mismo feed, por el que por medio de un toggle podríamos prender y apagar la luz del LED. Con esto conseguimos el código, lo probamos y si funcionaba, pero le pedimos ayuda con como hacer las conexiones de la protoboard al Arduino, luego de lograr las conexiones probamos el código y sí se pudo conectar a Adafruit IO, de otro dispositivo con acceso al dashboard pudimos controlar la luz LED prendiendola y apagandola.




## Conexiones 
![runway](./imagenes/conexiones.jpg)

![arduino conectado al led](./imagenes/arduino-conectado-a-led.jpeg)


## Materiales usados en solemne-01
- 1 Arduino UNO R4 WIFI 
- 1 protoboard 400 puntos
- 1 pin LED 
- 1 OHM resistor de 220
- 1 cable Dupont M/M
  
## código usado con Adafruit IO

### código para enviar

```cpp
#include <WiFiS3.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"

// ─── Configuración WiFi ───────────────────────────────
#define WIFI_SSID     "TU_SSID"
#define WIFI_PASS     "TU_PASSWORD"

// ─── Configuración Adafruit IO ───────────────────────
#define AIO_SERVER    "io.adafruit.com"
#define AIO_PORT      1883
#define AIO_USERNAME  "TU_USUARIO_AIO"
#define AIO_KEY       "TU_AIO_KEY"

// ─── Pin del LED ──────────────────────────────────────
#define LED_PIN 13  // Cambia al pin que uses

// ─── Objetos MQTT ─────────────────────────────────────
WiFiClient wifiClient;
Adafruit_MQTT_Client mqtt(&wifiClient, AIO_SERVER, AIO_PORT, AIO_USERNAME, AIO_KEY);

// Feed de suscripción (recibe comandos)
Adafruit_MQTT_Subscribe ledFeed = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/led-control");

// ─────────────────────────────────────────────────────
void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

  // Conectar WiFi
  Serial.print("Conectando a WiFi...");
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\n✅ WiFi conectado!");
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());

  // Registrar suscripción
  mqtt.subscribe(&ledFeed);
}

// ─────────────────────────────────────────────────────
void loop() {
  // Mantener conexión MQTT
  MQTT_connect();

  // Escuchar mensajes entrantes (timeout 200ms)
  Adafruit_MQTT_Subscribe *subscription;
  while ((subscription = mqtt.readSubscription(200))) {

    if (subscription == &ledFeed) {
      String value = String((char *)ledFeed.lastread);
      Serial.print("Comando recibido: ");
      Serial.println(value);

      if (value == "ON" || value == "1") {
        digitalWrite(LED_PIN, HIGH);
        Serial.println("💡 LED encendido");
      } else if (value == "OFF" || value == "0") {
        digitalWrite(LED_PIN, LOW);
        Serial.println("🔴 LED apagado");
      }
    }
  }
}

// ─── Función de conexión/reconexión MQTT ─────────────
void MQTT_connect() {
  if (mqtt.connected()) return;

  Serial.print("Conectando a Adafruit IO...");
  int8_t ret;
  uint8_t retries = 5;

  while ((ret = mqtt.connect()) != 0) {
    Serial.println(mqtt.connectErrorString(ret));
    Serial.println("Reintentando en 5 segundos...");
    mqtt.disconnect();
    delay(5000);
    retries--;
    if (retries == 0) {
      Serial.println("❌ No se pudo conectar. Reiniciando...");
      while (1); // Fuerza watchdog reset
    }
  }
  Serial.println("\n✅ Conectado a Adafruit IO!");
}
```

### código para recibir

```cpp
// rellenar
```

## investigaciones individuales

rellenar en el mismo orden que los integrantes del grupo

[persona-01.md](./persona-01.md)
[persona-02.md](./persona-02.md)
[persona-03.md](./persona-03.md)

## Bibliografía
