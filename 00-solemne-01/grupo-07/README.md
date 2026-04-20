# Grupo-07

## Integrantes

* Josefa Araya
* Débora Soto
* Cristóbal Vergara

## Descripción del proyecto

Nuestro proyecto grupal partió desde entender como funcionan las conexiones básicas de un Arduino UNO R4 WIFI, que es una placa de desarrollo que permite a los usuarios aprovechar tanto Wi-Fi como Bluetooth para manejar dispositivos de forma remota mediante ARDUINO IDE, que es un software a través del cual se puede escribir código y subirlo a la placa sin necesidad de internet. Por otro lado trabajamos con Adafruit IO, que es la nube virtual que permite agregar, almacenar, visualizar y transmitir datos con otros dispositivos a través de internet, propiedad de Adafruit que es una empresa de Hardware de código abierto.

El Arduino se conecta a una red Wi-Fi y establece comunicación con Adafruit IO mediante el protocolo MQTT en el Arduino IDE. Desde cualquier otro computador o celular, se accede al *dashboard* de Adafruit IO en el navegador que es un panel que permite visualizar y controlar dispositivos, al cual se pueden agregar "Blocks" que son paneles con los cuales se pueden interactuar y que van conectados a un "Feed" que es la base donde se almacenan los datos que se están traspasando y por último se presiona un botón *toggle*. Ese click viaja por internet hasta los servidores de Adafruit, los cuales lo reenvían al Arduino. Finalmente, la placa recibe el mensaje y enciende o apaga el LED.

![Diagrama conexiones](./imagenes/Capturadepantalla.png)

### Proceso conexiones inalámbricas

![Diagrama conexiones](./imagenes/diagrama-nube.png)

Comenzamos utilizando el código de ejemplo que Aarón subió a GitHub para aprender cómo funcionaban las conexiones basadas en la nube. Al principio no funcionaba y, tras un tiempo investigando, descubrimos que las credenciales eran incorrectas: estábamos usando la contraseña personal del sitio en lugar de la AIO Key (una clave alfanumérica que proporciona Adafruit IO para la conexión).

Tras solucionar esto, el código era correcto, pero la conexión seguía fallando; solo aparecía una serie de puntos infinitos en el monitor serial.

![Puntos](./imagenes/puntos-suspensivos.png)

No notamos el error hasta que, en clase, Aarón actualizó el firmware  de los Arduinos,resulta que al final de los puntos habia un mensaje que decía:

>"Please upgrade the WiFiS3 firmware!"

Una vez actualizados, logramos conectar con Adafruit IO y probamos con éxito un ejercicio de contador.

![funcionó!!](./imagenes/conectado-a-adafruit.png)

Durante la clase del lunes 6, intentamos encender un LED conectado a una protoboard, pero ningún código funcionó. Ante esto, investigamos en blogs y GitHub sin éxito, por lo que decidimos acudir a Claude AI.
Le proporcionamos el siguiente *prompt*:

>"Necesito generar un código para Arduino IDE que me permita controlar, a través de Adafruit IO, un Arduino conectado a otro computador. Este Arduino tendrá un LED que deseo encender y apagar desde los dashboards de Adafruit IO".

Creamos un feed llamado "led-control" y un dashboard vinculado. Con el código generado por la IA, realizamos las conexiones en la protoboard,con ayuda de Claude AI, y finalmente logramos controlar el LED de forma remota desde otros dispositivos.

## Conexiones

![runway](./imagenes/conexiones.jpg)

![arduino conectado al led](./imagenes/arduino-conectado-a-led.jpeg)

| Componente | Cantidad | Valor Unidad | Link |
| --- | --- | --- | --- |
| Protoboard 400 puntos | 1 | $2.100 | <https://prodelab.cl/productos/didacticos/nivel-superior-y-ensenanza-media/robotica-y-programacion/accesorios-robotica-y-programacion/protoboard-breadboard-400-pines/>
| Pin LED | 1 | $70 |<https://afel.cl/products/diodo-led-5mm-ultrabrillante-blanco>|
| Ohm resistor de 220 | 1 | $413 | <https://altronics.cl/pack-10-resistencias-220ohm-025watt-1porciento> |
| Cables Dupont | 1 | $65 | <https://mcielectronics.cl/shop/product/cable-dupont-macho-macho-20cm-pack-40-unidades/> |
| Arduino UNO R4 WiFi | 1 | $38.990 | <https://arduino.cl/producto/arduino-uno-r4-wifi/> |

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

![codigo funcionando](./imagenes/codigo-funcionando.gif)

## investigaciones individuales

rellenar en el mismo orden que los integrantes del grupo

[persona-01.md](./persona-01.md)
[persona-02.md](./persona-02.md)
[persona-03.md](./persona-03.md)

## Bibliografía

**Adafruit IO** <https://learn.adafruit.com/adafruit-io/arduino>

**Arduino libraries Adafruit IO** <https://docs.arduino.cc/libraries/adafruit-io-arduino/>

**Github Adafruit IO** <https://github.com/adafruit/Adafruit_IO_Arduino>

**Adafruit IO basics color** <https://learn.adafruit.com/adafruit-io-basics-color>

**Arduino cheat sheet** <https://docs.arduino.cc/tutorials/uno-r4-wifi/cheat-sheet/>

**Tutorial Adafruit IO** <https://mkelectronica.com/aprende-a-utilizar-la-plataforma-adafruit-io-para-tus-dispositivos-iot-parte-1/>
