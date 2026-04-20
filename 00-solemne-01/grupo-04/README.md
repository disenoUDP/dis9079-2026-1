# grupo-04

## Integrantes

* Antonella Lavalle
* Catalina Salinas
* Martina Alegria

## Descripción del proyecto

Este proyecto se desarrolló como un ejercicio práctico para la primera etapa de la solemne, con el objetivo de introducirnos en el uso de tecnologías IoT a través de Arduino. En un comienzo el enfoque estuvo en preparar el entorno de trabajo, instalando los programas necesarios y logrando que el Arduino UNO R4 WiFi se conectara correctamente a internet.

Una vez resuelta esa parte, se estableció una comunicación inalámbrica con la plataforma Adafruit IO. Mediante credenciales de acceso, el Arduino puede enviar datos como lecturas de sensores o valores simples a un feed en la nube, y también recibir información desde este para ejecutar acciones.

En general el proyecto permite entender de forma práctica cómo funciona el internet de las cosas, ya que se trabaja con un sistema donde un dispositivo físico se conecta a internet para intercambiar datos en tiempo real con una plataforma digital.

## Materiales/Software usados en solemne-01

| Cantidad | Componente / Recurso | Función en esta Etapa |
| --- | --- | --- |
| 1 | Arduino UNO R4 WiFi | Placa principal permite leer datos y conectarse a internet por WiFi. |
| 1 | Cable USB-C | Conexión principal que permite cargar el codigo y transmitirlo a la placa. |
| 1 | Arduino IDE | Software para programar codigos a la placa. |
| 1 | Librería Adafruit IO | Simplifica la comunicación entre la placa Arduino y la nube. |
| 1 | Cuenta de Adafruit IO | Plataforma de registro y visualización de datos. |
| 1 | Red WiFi / Hotspot móvil | Permite la conexión a internet para el funcionamiento del sistema. |

## Proceso

<img width="1900" height="940" alt="Captura de pantalla 2026-04-06 160014" src="https://github.com/user-attachments/assets/a316168d-0b0f-4ed2-9a27-c916991a1805" />

<img width="1920" height="1008" alt="image" src="https://github.com/user-attachments/assets/5ee5e857-3a3e-42a0-8ace-0b8725b25f91" />

El código nos estuvo fallando repetidamente, tratamos con 3 hotspot diferentes, también cambiando los usuarios de adafruit, creemos que falló por el uso de mayúsculas y minúsculas mal puestas en los nombres de los hotspot, mismos nombres que aveces tenían un espacio en su nombre, además de que las contraseñas eran solo de 8 caracteres. Pero luego de cambiar la contraseña de internet a una más larga (mas de 8 caracteres y solo con minúsculas y números) y con ese cambio resultó al enviar datos.

<img width="1920" height="1008" alt="imagen1" src="https://github.com/user-attachments/assets/634f3f8f-8182-4513-914b-58559216b30c" />

## Código usado con Adafruit IO

### Código para enviar

```cpp
#include "AdafruitIO_WiFi.h"

#define IO_USERNAME  "bla"
#define IO_KEY       "bla"

#define WIFI_SSID "bla"
#define WIFI_PASS "bla"

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

## investigaciones individuales

* antonella lavalle-persona 01
* catalina salinas-persona 02
* martina alegria-persona 03

rellenar en el mismo orden que los integrantes del grupo

[persona-01.md](./persona-01.md)
[persona-02.md](./persona-02.md)
[persona-03.md](./persona-03.md)

## bibliografía

Arduino. (s.f.). *WiFi examples (UNO R4 WiFi)*. [https://docs.arduino.cc/tutorials/uno-r4-wifi/wifi-examples/](https://docs.arduino.cc/tutorials/uno-r4-wifi/wifi-examples/)

Arduino. (s.f.). *Arduino IDE*. [https://docs.arduino.cc/software/ide/](https://docs.arduino.cc/software/ide/)

Adafruit. (s.f.). *Adafruit IO for Arduino*. Adafruit Learning System. [https://learn.adafruit.com/adafruit-io/arduino](https://learn.adafruit.com/adafruit-io/arduino)

Adafruit. (s.f.). *Adafruit IO Basics: Digital input*. Adafruit Learning System. [https://learn.adafruit.com/adafruit-io-basics-digital-input](https://learn.adafruit.com/adafruit-io-basics-digital-input)
