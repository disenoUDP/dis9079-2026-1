# grupo-11

## integrantes

* Anays Valentina Cornejo Candia
  
* Benjamín Alonso Álvarez Pavez

## descripción del proyecto

Al inicio del proyecto, como dupla no sabíamos muy bien qué hacer, estábamos bastante perdidos. En la última clase, trabajando al unísono con Aaron, pudimos entender mejor cómo usar el programa y ver qué cosas se podían lograr.

Al principio teníamos otras ideas, pero como aún no entendíamos bien cómo hacerlas, preferimos partir con algo más simple para aprender mejor cómo funcionan los programas y las placas.

Tras investigar por los tutoriales de la página Adafruit IO, nos llamó la atención uno que mostraba cómo prender y apagar una luz y decidimos hacer esa idea.

Cuando ya teníamos claro qué queríamos hacer, copiamos el código de config.h de GitHub y le pedimos a Chat GPT que lo modificara para poder prender y apagar un led, después también le pedimos ayuda para crear el código para enviar las instrucciones.

Para eso, conectamos un led a una protoboard e hicimos un circuito usando un Arduino UNO R4 WiFi. Conectamos el GND de la placa al negativo de la protoboard y el pin de 3.3V al positivo, luego conectamos la pata positiva del led al positivo de la protoboard y la pata negativa al negativo de la protoboard.

![circuito](./imagenes/ilustracion.jpg)

El Arduino estaba conectado al computador y las instrucciones de ON y OFF se enviaban desde el iPad a través del dashboard que creamos en Adafruit.

El led encendía y el código se recibía, pero al principio no logramos controlarlo porque no respondía a la instrucción de ON y OFF.

![on y off](./imagenes/config.png)

Por eso le pedimos ayuda a Chat GPT para modificar el código, para que el led respondiera bien a las instrucciones de ON y OFF desde el iPad. En ese cambio reemplazamos la línea ledPin = 2 por int ledPin = LED_BUILTIN;, pasamos de usar un led externo a usar el led integrado del Arduino.

Y finalmente resultó, el código funcionó y logramos prender y apagar el led desde el iPad, incluso a distancia. (ദ്ദി˙ᗜ˙)

https://github.com/user-attachments/assets/60f147d6-ef7a-4355-82a9-db9ce9517e1d

Se veía reflejado en el  feed de Adafruit IO

![feed](./imagenes/led.png)

También en el mismo dashboard de ON y OFF encontramos otros blocks de adafruit que permite mandar mensajes que luego aparecen en el arduino ide y en el feed de Adafruit IO

https://github.com/user-attachments/assets/134a4b66-3015-498e-9406-94555eb84eab

Otro de los blocks que encontramos es un slide que al moverlo hacia la izquierda y derecha dan distintos números según la posición en donde lo dejemos y estos números luego se ven reflejados en el gráfico de líneas que hay en el feed de Adafruit IO y también aparecen en el arduino ide.

![grafico](./imagenes/grafico-feed-slide.png)

![dashboards](./imagenes/dashboard.png)

De a poco estamos entendiendo mejor el funcionamiento del arduino y de Adafruit IO y las posibilidades de hacer cosas nuevas, estamos muy motivados y emocionados de realizar las ideas que tenemos en mente. 

## materiales usados en solemne-01

| Componentes Resultado Final | Precio | Cantidad | Link |
| :--------------------------- | ------ | -------- | :---- |
| Arduino UNO R4 Wifi         | $38.990 | x1      | <https://mcielectronics.cl/shop/product/43402/> |
| Cable C a C                 | $14.990 | x1      | <https://www.falabella.com/falabella-cl/product/149750952/> |

| Componentes Proceso | Precio | Cantidad | Link | 
| :------------------ | ------ | -------- | :---- |
| Protoboard          | $1.500 | x1       | <https://afel.cl/products/mini-protoboard-400-puntos> |
| Cable Dupont (pack 40 uni.) | $2.900 | x4       | <https://mcielectronics.cl/shop/product/cable-dupont> |
| Led                 | $70    | x1       | <https://afel.cl/products/diodo-led-5mm-ultrabrillante-blanco> |

## código usado con Adafruit IO

### código para enviar

```cpp
// #include "config.h"


// Crear feed (nombre: led)
AdafruitIO_Feed *led = io.feed("led");


// Pin del LED
int ledPin = LED_BUILTIN;


void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);


  // Conectar a Adafruit IO
  Serial.print("Conectando...");
  io.connect();


  // Esperar conexión
  while(io.status() < AIO_CONNECTED) {
    Serial.print(".");
    delay(500);
  }


  Serial.println();
  Serial.println("Conectado a Adafruit IO");


  // Escuchar cambios en el feed
  led->onMessage(handleMessage);


  // Obtener último valor guardado
  led->get();
}


void loop() {
  io.run();
}


// Función que se ejecuta cuando llega dato
void handleMessage(AdafruitIO_Data *data) {
  Serial.print("Valor recibido: ");
  Serial.println(data->value());


  if (data->toString() == "ON") {
    digitalWrite(ledPin, HIGH);
  }
  else if (data->toString() == "OFF") {
    digitalWrite(ledPin, LOW);
  }
}

```
### codigo config.h

```cpp
//// Descomenta SOLO si usas placas con AirLift o WiFi especial
// #define USE_AIRLIFT


// Librería
#include "AdafruitIO_WiFi.h"


// 🔐 Tus datos (CAMBIAR)
#define WIFI_SSID "monkiboy"
#define WIFI_PASS "benja123"


#define IO_USERNAME "benjaminalvarez21"
#define IO_KEY "blabla"




#if defined(USE_AIRLIFT) || defined(ADAFRUIT_METRO_M4_AIRLIFT_LITE) || \
    defined(ADAFRUIT_PYPORTAL)


// Pines para ESP32 AirLift
#if !defined(SPIWIFI_SS)
#define SPIWIFI SPI
#define SPIWIFI_SS 10
#define NINA_ACK 9
#define NINA_RESETN 6
#define NINA_GPIO0 -1
#endif


AdafruitIO_WiFi io(IO_USERNAME, IO_KEY, WIFI_SSID, WIFI_PASS,
                   SPIWIFI_SS, NINA_ACK, NINA_RESETN, NINA_GPIO0, &SPIWIFI);


#else


// 🔵 ESTE ES EL MÁS COMÚN (ESP8266 / ESP32 / UNO R4 WIFI)
AdafruitIO_WiFi io(IO_USERNAME, IO_KEY, WIFI_SSID, WIFI_PASS);


#endif

```

### código para recibir

```cpp
// rellenar
```

## investigaciones individuales

[persona-01.md](./persona-01.md) Anays Cornejo

[persona-02.md](./persona-02.md) Benjamín Álvarez

## bibliografía

<https://learn.adafruit.com/series/adafruit-io-basics>

<https://learn.adafruit.com/adafruit-io-basics-digital-output>
