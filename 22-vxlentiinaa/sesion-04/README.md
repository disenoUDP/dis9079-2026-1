# sesion-04

lunes 30 marzo 2026

---

## Apuntes

- **HiveMQ:** es una plataforma de mensajería empresarial basada en el protocolo MQTT diseñada para conectar dispositivos IoT (Internet de las Cosas) con sistemas en la nube de manera rápida, confiable y segura. Actúa como un broker o intermediario que gestiona el intercambio de datos en tiempo real entre millones de dispositivos, facilitando la integración de tecnología operativa (OT) y de información (TI).
- sistema de almacenamiento
- Conectar a wifi > dis9079
- **TigerVNC** > sistema de escritorio gráfico para visualizar la raspberry pi
  -  brew install tigerVNC
- 5g es rápida pero de bajo alcance
- Sudo es una palabra peligrosa, usar admin
- el broker siempre vive en el raspberry pi > MQTT
- arduino 01 > clave encriptada > dis0979
- 52 > arduino01
- **Claude Shannon** ¿quién es? buscar!
- ¿Qué se necesita para conectarse a otro arduino?
  - arduino se conecta al wifi > arduino conectado al router
  -  IP de wifi
  - tener el broker en mosquitto 
- Model OSI > capas de comunicación
- sobre wifi se usa la estrategia mqtt
- UDP: mensajes entre canales > [UDP](https://en.wikipedia.org/wiki/User_Datagram_Protocol)
  - UDP (User Datagram Protocol): Sobre Wi-Fi es un protocolo de transporte rápido y sin conexión, ideal para streaming, juegos en línea y VoIP. Envía paquetes (datagramas) directamente sin establecer sesión ni verificar recepción, priorizando la velocidad y baja latencia sobre la fiabilidad. Se usa cuando la rapidez es crítica.
- `Simple webserver` en arduino docs > [SIMPLE WEBSERVER WIFI](https://docs.arduino.cc/retired/library-examples/wifi-library/SimpleWebServerWiFi/)

`Rosetta:` Es un emulador de software desarrollado por Apple que permite a las computadoras Mac con procesadores Apple Silicon (chips M1, M2, M3) ejecutar aplicaciones diseñadas originalmente para procesadores Intel. Funciona automáticamente en segundo plano, traduciendo el código durante la primera ejecución para garantizar la compatibilidad.

`HiveMQ:` Es una plataforma de mensajería MQTT diseñada para el Internet de las Cosas (IoT) empresarial, permitiendo la comunicación rápida, confiable y segura entre dispositivos y aplicaciones. Funciona como un "broker" de mensajes que gestiona, filtra y distribuye datos en tiempo real a gran escala, ideal para proyectos industriales y de misión crítica.

Wifi es como una carretera, le puedes poner internet, tambien puedes no ponerle ;).

Ya no tenemos que tener una IP distinta cada uno, sino que será siempre la misma IP.

sudo: Super usuario hacer (no usar)

---

- Mandar cosas raras desde el arduino a la raspberry pi y que el computador responda.

---

Código que genera un punto en la pantalla OLED SSD1306

```cpp
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setup() {
  Wire.begin();

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    while (true);
  }

  display.clearDisplay();

  // Punto grande en la parte inferior
  display.fillCircle(64, 55, 4, SSD1306_WHITE);
  // (x, y, radio)

  display.display();
}

void loop() {
}
```

> MQTT es un protocolo de mensajería ligero (publicación/suscripción) ideal para IoT que funciona sobre TCP, garantizando la entrega de datos, alta fiabilidad y orden de mensajes. En cambio, UDP es un protocolo de transporte sin conexión que prioriza la velocidad máxima, sin garantizar la entrega ni el orden, ideal para streaming en tiempo real.
