# grupo-09

## integrantes

* Marlén Soto Soto
* Marcela Zúñiga

## descripción del proyecto
El proyecto consiste en crear un sistema de comunicación entre dos dispositivos electrónicos ubicados en distintos computadores, utilizando internet como medio de conexión a través de Adafruit IO.

La idea principal es demostrar cómo funcionan el Internet de las Cosas (IoT): dispositivos que pueden enviar y recibir información en tiempo real sin estar conectados físicamente entre sí.

En este caso, se utiliza una sola placa Arduino, la cual cumple tanto el rol de emisor como de receptor.

Como emisor: detecta una acción o mide un valor.
Como receptor: recibe datos desde la nube y ejecuta una acción.

El funcionamiento se basa en el uso de un feed dentro de Adafruit IO:

El Arduino envía datos al feed.
Adafruit IO los almacena y gestiona en la nube.
El mismo Arduino lee esos datos desde el feed y actúa en consecuencia.

## materiales usados en solemne-01
•1 placa de Arduino uno R4 

•2 computadores 

•Cable USB para conectar la placa

## código usado con Adafruit IO

### código para enviar

```cpp
#include "AdafruitIO_WiFi.h"

#define WIFI_SSID "bla"
#define WIFI_PASS "bla"

#define IO_USERNAME "bla"
#define IO_KEY "bla"

AdafruitIO_WiFi io(IO_USERNAME, IO_KEY, WIFI_SSID, WIFI_PASS);

AdafruitIO_Feed *feed = io.feed("prueba02");

void handleMessage(AdafruitIO_Data *data) {
  String mensaje = data->toString();

  Serial.print("Mensaje recibido: ");
  Serial.println(mensaje);

  // ejemplos
  if (mensaje == "ON") {
    digitalWrite(LED_BUILTIN, HIGH);
  }
  else if (mensaje == "OFF") {
    digitalWrite(LED_BUILTIN, LOW);
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);

  io.connect();

  while (io.status() < AIO_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.println("\nConectado!");

  feed->onMessage(handleMessage);
  feed->get();
}

void loop() {
  io.run();
  delay(100);  
}
```

### código para recibir

```cpp
// rellenar
```


## proceso

El día lunes 06 fuimos los últimos en lograr conectarnos a Adafruit. Después de varios intentos, finalmente lo conseguimos. Inicialmente tuvimos problemas con la velocidad de conexión, lo que nos impedía visualizar correctamente en qué estado se encontraba el proceso. Con la ayuda de Aaron, decidimos cerrar Arduino y volver a abrirlo. Tras hacer esto, el sistema funcionó correctamente, aunque demoró un poco en cargar:)

Para continuar con la solemne, intentamos utilizar un toggle en Adafruit, el cual, al encenderse y apagarse, debía controlar los LED del Arduino. Sin embargo, a pesar de modificar el código en múltiples ocasiones, no logramos que funcionara. Estuvimos aproximadamente dos horas intentando que el Arduino recibiera la información, pero no obtuvimos resultados.

<img width="1321" height="670" alt="Captura de pantalla 2026-04-10 171922" src="https://github.com/user-attachments/assets/05b5501a-405c-4afa-b1cf-f5befeb445f7" />

Además, cometimos algunos errores en el código. Por ejemplo, en la contraseña del WiFi habíamos escrito mal la última letra, lo que impedía la conexión. Debido a esto, el sistema quedaba intentando conectarse sin éxito y solo mostraba puntos en la carga.

<img width="1364" height="280" alt="Captura de pantalla 2026-04-10 171808" src="https://github.com/user-attachments/assets/03cb497b-328c-4b27-a2ee-dbb118e62056" />

Al final, buscamos otra forma de enviar y recibir información. Para esto, en Adafruit agregamos un nuevo bloque de tipo “text”. A partir de esto, trabajamos con otro código que fuimos ajustando hasta que finalmente logramos recibir datos en el Arduino. Marlen se encargó de enviar la información desde Adafruit y Marcela de recibirla desde el Arduino. Sin embargo, solo logramos recibir un mensaje, “ON”. Intentamos enviar también un “OFF”, pero este nunca llegó. Aun así, seguiremos ajustando el código, ya que estamos muy contentos de haber logrado al menos la recepción de un dato.

<img width="1365" height="675" alt="Captura de pantalla 2026-04-10 183756" src="https://github.com/user-attachments/assets/b0ad36c3-a5ff-49c7-b800-f50b2473cf50" />

También queremos mencionar que, al parecer, debido al internet, muchas veces no logramos conectarnos a Adafruit y el sistema quedaba cargando. En esos casos teníamos que desconectar y volver a conectar el Arduino, además de tener paciencia hasta que se reconectara nuevamente. Al principio nos asustamos, ya que estábamos usando el mismo código que antes sí funcionaba, pero dejó de conectar. Sin embargo, al final nos dimos cuenta de que el problema probablemente era solo la conexión a internet.

## investigaciones individuales

rellenar en el mismo orden que los integrantes del grupo

[persona-01.md](./persona-01.md)
[persona-02.md](./persona-02.md)
[persona-03.md](./persona-03.md)

## bibliografía
