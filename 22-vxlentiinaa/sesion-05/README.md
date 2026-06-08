# sesion-05

lunes 06 abril 2026

solemne 1

---

## Investigación Adafruit IO

`¿Qué es Adafruit IO?`

- Adafruit IO es una plataforma en la nube para Internet de las Cosas (IoT) que permite conectar dispositivos (como Arduino, ESP8266, Raspberry Pi, etc.) a Internet para enviar, recibir y visualizar datos.
  - <https://learn.adafruit.com/welcome-to-adafruit-io>

`¿Qué hace la biblioteca Adafruit IO?`
 
 Permite:

- Enviar datos (sensores, valores, etc.) a la nube
- Recibir datos (por ejemplo, para controlar LEDs o motores)
- Conectar tu dispositivo a Internet fácilmente
- Mantener comunicación en tiempo real con feeds (canales de datos)

*Esta librería simplifica el uso, como MQTT*

`¿Cómo funciona?`

- Tu dispositivo se conecta a WiFi (arduino)
- Usa la librería Adafruit IO para conectarse al servidor
- Envía o recibe datos a través de feeds
- Puedes ver esos datos en gráficas, etc

<https://learn.adafruit.com/adafruit-io-basics-digital-input/getting-started-with-adafruit-io>

**Instalé la librería Adafruit IO en Arduino IDE y usé de ejemplo `adafruitio_00_publish**

<https://io.adafruit.com/welcome>

- el ejemplo Publish, es un ejemplo de código que sirve para enviar datos desde el microcontrolador hacia la plataforma Adafruit IO
  - es para publicar (mandar) información a internet.

`¿Para qué se usa exactamente?`

Sirve para:

- Enviar datos de sensores
  - Ej: temperatura, luz, humedad.
- Mandar estados o eventos
  - Ej: “botón presionado”, “LED encendido”.
- Visualizar datos en dashboards

En Adafruit IO puedes ver gráficos en tiempo real.

`¿Qué hace el código?`

El ejemplo “Publish” hace:

1. Se conecta a tu WiFi
2. Se conecta a Adafruit IO con tu usuario y contraseña
3. Envía datos a un “feed” (como una variable online)
4. Repite el envío cada cierto tiempo

Ya sabiendo esto, descargué la librería. 
 > fui a `File` luego a `Examples` --> abrí `Adafruit IO Arduino` --> abrí el primer ejemplo `adafrutio_00_publish`

<img src="./imagenes/adafruit_install.png" alt="install" width="700">

> instalé todas laslibrerías que me pedía (eran muchas)

<img src="./imagenes/adafruit_examples.png" alt="example" width="700">

> busqué que ejemplo me servía y en la página salía que el publish

<img src="./imagenes/adafruit_publish.png" alt="publish" width="700">

> le pregunté a chatgpt que era lo que tenía que cambiar para que me funcionara el ejemplo.

Y cambié 

```cpp
#define IO_USERNAME "your_username"
#define IO_KEY "your_key"
```
por

```cpp
#define IO_USERNAME "arduino01"
#define IO_KEY "dis9079"
```

esto igual lo cambié

```cpp
#define WIFI_SSID "your_ssid"
#define WIFI_PASS "your_pass"
```

por mi wifi

```cpp
#define WIFI_SSID "Ruz Pizarro 5G"
#define WIFI_PASS "blabla"
```

Luego probé el ejemplo para ver si en el monitor serial salía el mensaje de **"Connecting to Adafruit IO"** , pero solo me aparecía signos de interrogación

<img src="./imagenes/adafruit_fail.png" alt="fail" width="700">

- Podría haber sido por el baud, que en el código estaba a 115200 y en el monitor serial estaba a 9600
- Lo cambié y después solo salían puntitos, no el mensaje de que ya estaba conectado

<img src="./imagenes/adafruit_error.png" alt="error" width="700">

## Apuntes 

CÓDIGO SI FUNCIONOOOO YEI

- `Firmware updater:` Capa límite entre el Software y el Hardware; es el pegamento que hace que las dos convivan.
 - según gemini: El Firmware Updater en el IDE de Arduino es una herramienta especializada diseñada para actualizar el software interno (el firmware) de los módulos de conectividad (Wi-Fi o Bluetooth) que vienen integrados en ciertas placas de Arduino.

En Adafruit IO, te da la llave para colocar en el código en arduino

```cpp
#define IO_USERNAME  "vxlentiinaa"
#define IO_KEY       "blablabla"
```

siempre hay que colocar esa línea, para que el arduino no olvide el adafruit IO

```cpp
io.run();
```

Es para ver lo que manda el otro arduino en adafruit 

```
io.feed();
```

Código que si funciona + el `config.h` es donde se guarda la clave de Adafruit IO y la clave de wifi

```cpp
// Adafruit IO Publish Example
//
// Adafruit invests time and resources providing this open source code.
// Please support Adafruit and open source hardware by purchasing
// products from Adafruit!
//
// Written by Todd Treece for Adafruit Industries
// Copyright (c) 2016 Adafruit Industries
// Licensed under the MIT license.
//
// All text above must be included in any redistribution.

// ejemplo para enviar / publish
// por montoyamoraga
// para disenoUDP
// basado en
// Adafruit IO Publish Example

// incluir archivo config.h
// hacer las modificaciones de este archivo
// NO subir a github
#include "config.h"

// esta variable entera
// sera un contador que aumenta
// durante el funcionamiento del software
int contador = 0;

// definir una variable que se llame nombreFeed
// que tenga un cierto valor
// mantener las doble comillas, cambiar grupoXX segun tu nombre de grupo
AdafruitIO_Feed *nombreFeed = io.feed("grupo01");

void setup()
{

  // prender la conexion serial
  // ojo con la velocidad de 115200 baud
  // cuando abras el monitor serial debes configurarlo
  // a este numero, porque el standard de fabrica es 9600 baud
  Serial.begin(115200);

  // estas lineas pausan el codigo
  // hasta que prendas el monitor serial
  // la lupita arriba a la derecha en Arduino IDE
  while (!Serial)
    ;

  // imprimir en consola
  Serial.print("conectando a Adafruit IO");

  // conectarse a io.adafruit.com
  io.connect();

  // esperar la conexion
  while (io.status() < AIO_CONNECTED)
  {
    // imprimir un punto cada medio segundo
    // mientras se conecta
    Serial.print(".");
    delay(500);
  }

  // demostrar que logramos conexion
  Serial.println();
  Serial.println(io.statusText());
}

void loop()
{

  // esta linea es necesaria
  // al principio de loop()
  // para mantener la conexion
  // y procesar datos que lleguen
  io.run();

  // enviar el contador a Adafruit IO
  // primero mostrar en monitor serial
  Serial.println("enviando -> " + String(contador));
  // despues enviar a la nube
  nombreFeed->save(contador);

  // incrementar el contador en 1
  contador = contador + 1;

  // Adafruit IO tiene una velocidad limitada
  // de escritura / publishing
  // usamos delay para pausar el codigo 3 segundos
  delay(3000);
}
```

Luego probamos el código en clases, donde si compiló y enviaba los datos correspondientes, además se veía en la data en Adafruit :) yei

<img src="./imagenes/adafruit_compiling.png" alt="compiling" width="700">

<img src="./imagenes/adafruit_enviando.png" alt="enviando" width="700">

<img src="./imagenes/adafruit_data.png" alt="data" width="700">
