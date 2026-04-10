# grupo-03

## integrantes

* Antonella Aguilar
* Tomás Catrileo
* Angel Sabogal

## descripción del proyecto

Consiste en un circuito que permite controlar un LED RGB de forma remota. A través de un dashboard en la nube (Adafruit IO), el usuario selecciona un color que se transmite vía Wi-Fi a un Arduino, el cual procesa la información y activa los pines físicos para igualar el color digital en un LED a tiempo real.

## proceso

Empezamos el proyecto explorando la biblioteca de aprendizaje de Adafruit IO, encontramos un tutorial en [Adafruit IO](https://learn.adafruit.com/adafruit-io-basics-color) explicando la posibilidad de enviarle una señal desde Adafruit al Arduino, de forma que se puede lograr cambiar los colores RGB de manera remota, sin cables y hasta desde otro dispositivo electrónico.

Dicho esto, unimos las conexiones del RGB al protoboard y del protoboard al Arduino:

Lo primero sería conectar las 4 patas del LED RGB al protoboard, después poner 3 resistencia 220Ω, estas deben estar así:

* **R** - La luz roja o luz red es la de izquierda inicial; esta tiene que ir acompañada de una resistencia de 220Ω conectada a R y a su vez conectada al pin 4 del Arduino.
* **GND** - La segunda pata (asumiendo la izquierda R) es la de a tierra, debe ir conectada directo al Arduino en el pin 3V.
* **G** - La luz verde o luz green es la siguiente después de la GND, esta tiene que ir con una resistencia de 220 Ω y a su vez conectada al pin 5 del Arduino.
* **B** - La luz azul o luz blue es la siguiente después de la G, esta tiene que ir con una resistencia de 220 Ω y a su vez conectada al pin 2 del Arduino.

Debe quedar así:

![LED conectado a arduino](./imagenes/circuitoled.jpg)

conexiones:

patas del LED

- patita 1 (R) a pin 4
- patita 2 (ánodo) a vcc
- patita 3 (G) a pin 5
- patita 4 (B) a pin 2

Para llegar a la conexión del LED RGB primero tuvimos que tener una cuenta de Adafruit que en este caso nos proporcionó una mejora el profesor para tener la cuenta de pago y esta la hicimos cada uno para testear individualmente con nuestros correos UDP.

Habiendo iniciado sesión vamos a configuraciones para darle al botón que nos da la clave AIO que necesitaremos más tarde.

Procedimos a la creación del flujo del color creando una Feed llamada específicamente "color".

A continuación en la sección de "Dashboards" agregamos un bloque de color ingresando a la pestaña de Dashboards y haciendo clic adentro del apartado color que también hay que crear manualmente en esta misma sección lo que nos daría como resultado el bloque en el panel de control de esta manera:

![Ejemplo de Bloque de color](./imagenes/bloquecolorgrupo.png)

### Configuración de arduino

En nuestro caso usaremos Arduino UNO R4 WIFI, por ende tiene una configuración correspondiente al hardware y, como dice el nombre, sí tiene "wifi", que también usaremos, y antes de continuar asegurarnos de tener instalada al menos la versión 2.4.0 de la biblioteca Adafruit IO Arduino.

Y como nos indicaba la instrucción, descargamos adafruitio_13_rgb en la biblioteca Adafruit IO Arduino, que es el que tiene el código RGB para el LED.

![Código del RGB](./imagenes/adafruito13rgb.png)

Ahora pocedemos a hacer

### La configuración de red arduino

Primero vamos a la App de Arduino IDE y presionamos config.h, ahí tenemos que poner nombre de usuario de Adafruit IO en la sección de IO_USERNAME y la clave de Adafruit IO en la sección IO_KEY.

Ya que usamos unas placas de WIFI compatibles, aparece para modificar las opciones WIFI_SSID y WIFI_PASS en config.h. "Existen más opciones de conexión, pero como solo usaremos WIFI, esta es la que necesitamos".

Acá ejemplos de dónde debería ir lo que mencionamos:

![username ejemplo](./imagenes/usernameandkey.png)

![wifi contraseña ejemplo](./imagenes/wifipassword.png)

Los valores aparecen tanto en el monitor serial como en la sección de Feeds mientras que se cambia el color en el dashboard de Adafruit.

![valores serial monitor](./imagenes/serialmonitorrgb.png)

![valores feeds](./imagenes/valoresfeeds2.png)

## materiales usados en solemne-01

- 1x Arduino UNO R4 WiFi
- 1x LED RGB
- 1x Protoboard
- 3x Resistencias 220Ω
- 4x Cables dupont (m-m)

## código usado con Adafruit IO

### código para enviar

### código base de biblioteca de Adafruit IO 

example: adafruitio_13_rgb

```cpp
// Adafruit IO RGB LED Output Example
// Tutorial Link: https://learn.adafruit.com/adafruit-io-basics-color
//
// Adafruit invests time and resources providing this open source code.
// Please support Adafruit and open source hardware by purchasing
// products from Adafruit!
//
// Written by Todd Treece for Adafruit Industries
// Copyright (c) 2016-2017 Adafruit Industries
// Licensed under the MIT license.
//
// All text above must be included in any redistribution.

/************************** Configuration ***********************************/

// edit the config.h tab and enter your Adafruit IO credentials
// and any additional configuration needed for WiFi, cellular,
// or ethernet clients.
#include "config.h"

/************************ Example Starts Here *******************************/

// default PWM pins for ESP8266.
// you should change these to match PWM pins on other platforms.
#define RED_PIN 4
#define GREEN_PIN 5
#define BLUE_PIN 2

// set up the 'color' feed
AdafruitIO_Feed *color = io.feed("color");

void setup() {

  // start the serial connection
  Serial.begin(115200);



  // wait for serial monitor to open
  while (!Serial)
    ;

#if defined(ARDUINO_ARCH_ESP32) // ESP32 pinMode
#if ESP_IDF_VERSION >= ESP_IDF_VERSION_VAL(5, 1, 1)
  // New ESP32 LEDC API
  ledcAttach(RED_PIN, 12000, 8); // 12 kHz PWM, 8-bit resolution
  ledcAttach(GREEN_PIN, 12000, 8);
  ledcAttach(BLUE_PIN, 12000, 8);
#else
  // Legacy ESP32 LEDC API
  ledcAttachPin(RED_PIN, 1);
  ledcAttachPin(GREEN_PIN, 2);
  ledcAttachPin(BLUE_PIN, 3);
  ledcSetup(1, 12000, 8);
  ledcSetup(2, 12000, 8);
  ledcSetup(3, 12000, 8);
#endif
#else
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);
#endif

  // connect to io.adafruit.com
  Serial.print("Connecting to Adafruit IO");
  io.connect();

  // set up a message handler for the 'color' feed.
  // the handleMessage function (defined below)
  // will be called whenever a message is
  // received from adafruit io.
  color->onMessage(handleMessage);

  // wait for a connection
  while (io.status() < AIO_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  // we are connected
  Serial.println();
  Serial.println(io.statusText());
  color->get();

// set analogWrite range for ESP8266
#ifdef ESP8266
  analogWriteRange(255);
#endif
}

void loop() {

  // io.run(); is required for all sketches.
  // it should always be present at the top of your loop
  // function. it keeps the client connected to
  // io.adafruit.com, and processes any incoming data.
  io.run();
}

// this function is called whenever a 'color' message
// is received from Adafruit IO. it was attached to
// the color feed in the setup() function above.
void handleMessage(AdafruitIO_Data *data) {

  // print RGB values and hex value
  Serial.println("Received:");
  Serial.print("  - R: ");
  Serial.println(data->toRed());
  Serial.print("  - G: ");
  Serial.println(data->toGreen());
  Serial.print("  - B: ");
  Serial.println(data->toBlue());
  Serial.print("  - HEX: ");
  Serial.println(data->value());

  // invert RGB values for common anode LEDs
  analogWrite(RED_PIN, 255 - data->toRed());
  analogWrite(GREEN_PIN, 255 - data->toGreen());
  analogWrite(BLUE_PIN, 255 - data->toBlue());
}

```
config.h

```cpp
/************************ Adafruit IO Config *******************************/

// visit io.adafruit.com if you need to create an account,
// or if you need your Adafruit IO key.
#define IO_USERNAME "udpmontoyamoraga"
#define IO_KEY "blabla"

#define WIFI_SSID "iPhone-Antonella"
#define WIFI_PASS "blabla"

// uncomment the following line if you are using airlift
// #define USE_AIRLIFT

// uncomment the following line if you are using winc1500
// #define USE_WINC1500

// uncomment the following line if you are using mrk1010 or nano 33 iot
// #define ARDUINO_SAMD_MKR1010

// comment out the following lines if you are using fona or ethernet
#include "AdafruitIO_WiFi.h"

#if defined(USE_AIRLIFT) || defined(ADAFRUIT_METRO_M4_AIRLIFT_LITE) ||         \
    defined(ADAFRUIT_PYPORTAL)
// Configure the pins used for the ESP32 connection
#if !defined(SPIWIFI_SS) // if the wifi definition isnt in the board variant
// Don't change the names of these #define's! they match the variant ones
#define SPIWIFI SPI
#define SPIWIFI_SS 10 // Chip select pin
#define NINA_ACK 9    // a.k.a BUSY or READY pin
#define NINA_RESETN 6 // Reset pin
#define NINA_GPIO0 -1 // Not connected
#endif
AdafruitIO_WiFi io(IO_USERNAME, IO_KEY, WIFI_SSID, WIFI_PASS, SPIWIFI_SS,
                   NINA_ACK, NINA_RESETN, NINA_GPIO0, &SPIWIFI);
#else
AdafruitIO_WiFi io(IO_USERNAME, IO_KEY, WIFI_SSID, WIFI_PASS);
#endif

/**************************** ETHERNET ************************************/

// the AdafruitIO_Ethernet client will work with the following boards:
//   - Ethernet FeatherWing -> https://www.adafruit.com/products/3201

// uncomment the following two lines for ethernet,
// and comment out the AdafruitIO_WiFi client in the WIFI section
// #include "AdafruitIO_Ethernet.h"
// AdafruitIO_Ethernet io(IO_USERNAME, IO_KEY);
```

### código para recibir

```cpp
// rellenar
```

## LED a tiempo real

![led a tiempo real](./imagenes/ledenclase.gif)

## investigaciones individuales

rellenar en el mismo orden que los integrantes del grupo

[persona-01.md](./persona-01.md)
[persona-02.md](./persona-02.md)
[persona-03.md](./persona-03.md)

## bibliografía

Adafruit. (s. f.). Adafruit IO. https://io.adafruit.com/

Surbyte. (2017). Arduino Forum. https://forum.arduino.cc/t/solucionado-ayuda-monitor-serial-con-caracteres-ilegibles/473044/5

MK Electrónica. (s. f.). Aprende a utilizar la plataforma Adafruit IO para tus dispositivos IoT. https://mkelectronica.com/aprende-a-utilizar-la-plataforma-adafruit-io-para-tus-dispositivos-iot-parte-1/

Adafruit. (s. f.). Adafruit IO Basics: Color. Adafruit Learning System. https://learn.adafruit.com/adafruit-io-basics-color
