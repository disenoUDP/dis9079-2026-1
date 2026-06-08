# sesion-05

lunes 06 abril 2026

## avance solemne 1

para actualizar/resetear el arduino, en la parte de arriba entro al tools y ahi a firmware update

recordar instalar adafruit que es lo que usaremos para la solemne

con mi user de github y luego un guion 

### codigo para enviar datos

```cpp
// reemplazar por las credenciales de aaron
// o por las de tu cuenta
#define IO_USERNAME  "bla"
#define IO_KEY       "bla"



// reemplazar por nombre y clave de la wifi
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

Al actualizar la placa de Arduino el sistema nos dejaba en la versión 0.4.1. Nos marcaba que la última era la 0.5.2, pero nos dimos cuenta de que esa tampoco era la versión final real.

El código funcionaba bien en el compu de Marlen y en el mío no, al final era simplemente porque yo arrastraba un error al copiar y pegar el texto.

Estuvimos varios intentos a ciegas porque por alguna razón no nos salía la velocidad en el programa, así que no teníamos cómo ver en qué parte del proceso estábamos. Terminamos cerrando el Arduino y volviéndolo a abrir; después de eso agarró y nos funcionó, aunque se demoró en cargar :).

Me quedé pegada tratando de conectar la placa, y resulta que en las credenciales había copiado mal la contraseña y dejé puesto el "bla" del ejemplo. Por ese puro detalle no me funcionaba nada.
