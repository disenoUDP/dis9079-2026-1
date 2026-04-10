# vxlentiinaa

investigaciones individuales

## sobre adafruit i/o

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

<img src="./imagenes/vxlentiinaa_imagenes/adafruit_install.png" alt="install" width="700">

> instalé todas laslibrerías que me pedía (eran muchas)

<img src="./imagenes/vxlentiinaa_imagenes/adafruit_examples.png" alt="example" width="700">

> busqué que ejemplo me servía y en la página salía que el publish

<img src="./imagenes/vxlentiinaa_imagenes/adafruit_publish.png" alt="publish" width="700">

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

<img src="./imagenes/vxlentiinaa_imagenes/adafruit_fail.png" alt="fail" width="700">

- Podría haber sido por el baud, que en el código estaba a 115200 y en el monitor serial estaba a 9600
- Lo cambié y después solo salían puntitos, no el mensaje de que ya estaba conectado

<img src="./imagenes/vxlentiinaa_imagenes/adafruit_error.png" alt="error" width="700">

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

- Aqui está el `config.h` del código, donde se guarda el wifi y la clave, además de tu sesión en adafruit

```cpp
// reemplazar por las credenciales de aaron
// o por las de tu cuenta
// el usuario y la key son de adafruit.com 
#define IO_USERNAME  "vxlentiinaa"
#define IO_KEY       "blabla"


// reemplazar por nombre y clave de la wifi
#define WIFI_SSID "iPhone de Valentina"
#define WIFI_PASS "blabla"

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
```
Luego probamos el código en clases, donde si compiló y enviaba los datos correspondientes, además se veía en la data en Adafruit :) yei

<img src="./imagenes/vxlentiinaa_imagenes/adafruit_compiling.png" alt="compiling" width="700">

<img src="./imagenes/vxlentiinaa_imagenes/adafruit_enviando.png" alt="enviando" width="700">

<img src="./imagenes/vxlentiinaa_imagenes/adafruit_data.png" alt="data" width="700">

## sobre artista, diseñadora o producto que usa electrónica o computación inalámbricas

### Hedy Lamarr

<img src="./imagenes/vxlentiinaa_imagenes/hedy_lamarr.jpg" alt="hedy" width="300">

`¿Quién es Hedy Lamarr?`

- Hedwig Eva Maria Kiesler, conocida como Hedy Lamarr, fue una ingeniera, actriz de cine e inventora austriaca. Más alla de ser conocida como actriz, fue una inventora que, junto a George Antheil, desarrolló una tecnología revolucionaria en la cual se convertiría en la base para las comunicaciones inalámbricas modernas. Inventó la primera versión del wifi, que permitiría las comunicaciones inalámbricas a largas distancias. Su invento, basado en el uso del espectro ensanchado por salto de frecuencia, ha influido enormemente en el desarrollo de redes inalámbricas como el wifi, el Bluetooth y otros sistemas de transmisión de datos.

- A comienzos de la Segunda Guerra Mundial, inventó, desarrolló y patentó un sistema de guía por radio para torpedos aliados que utilizaba el espectro ensanchado y la tecnología de salto de frecuencia para vencer la amenaza de interferencias por parte de las Potencias del Eje.

`¿Qué inventó Hedy Lamarr?`

- Durante la Segunda Guerra Mundial, Lamarr y Antheil patentaron un sistema para controlar torpedos de manera inalámbrica y segura, evitando que fueran interceptados o bloqueados por el enemigo. Este sistema usaba una técnica llamada espectro ensanchado por salto de frecuencia, que permite que una señal de radio cambie rápidamente entre diferentes frecuencias dentro del espectro de frecuencias.

<img src="./imagenes/vxlentiinaa_imagenes/hedy_wifi.png" alt="wifi" width="250">

`¿Cómo funciona el espectro ensanchado por salto de frecuencia?`

- El funcionamiento del espectro ensanchado se basa en la transmisión de señales a través de múltiples frecuencias, en lugar de usar una única frecuencia fija.
  - el salto de frecuencia permiten que una señal "salte" rápidamente diferentes canales dentro del espectro de frecuencias, evitando interferencias y haciendo que las comunicaciones sean más seguras.

- Esto no solo mejora la resistencia de la señal contra ruidos o interferencias externas, sino que también dificulta que terceros intercepten o bloqueen la comunicación, ya que necesitarían conocer la secuencia exacta de frecuencias utilizadas para saltar. Esta técnica desarrollada por la inventora del wifi, es fundamental en tecnologías inalámbricas modernas como el wifi, Ethernet inalámbrico y Bluetooth, además de aplicaciones militares y comerciales.

`¿Qué aplicaciones actuales se utiliza su invento?`

1. Redes wifi domésticas y empresariales que permiten la transmisión rápida de datos sin cables.
2. Conexiones Bluetooth para dispositivos como auriculares, teclados o parlantes inalámbricos.
3. Sistemas de comunicación en el sector militar que requieren alta seguridad y resistencia a interferencias.
4. Tecnología Ethernet inalámbrica y otras formas de conexión digital que usan el espectro de frecuencias para transferir datos.
5. Plataformas de activismo digital en redes sociales que se apoyan en conexiones seguras para transmisión y protección de la información.

> Transformó la manera en que los dispositivos se comunican sin cables y sin interrupciones.

secaa!
