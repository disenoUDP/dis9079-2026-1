# grupo-5

* Antonella Aguilar / antokiaraa
* Tomás Catrileo / tomascatri
* Angel Sabogal / angel-udp

## Archivo Retro

![Archivo Retro](./imagenes/archivoretro-01.png)

### Descripción del proyecto

Es un proyecto electrónico interactivo que fusiona la fotografía digital con el estilo gráfico de las consolas antiguas. Funciona de manera inalámbrica mediante 2 microcontroladores; un Arduino (UNO R4 WiFi) y una Raspberry (PI Pico 2W), y además un módulo ESP32 con cámara integrada que funciona de manera independiente. 

Por un lado cuenta con un potenciómetro que permite elegir un filtro, y un botón que al mantenerlo presionado cambias el estilo del tramado. Al pulsarlo rápidamente se envía la orden de disparo a la cámara y la pantalla OLED muestra una animación para avisarte que la foto se está subiendo a la nube. 

Las fotos procesadas se suben a un script de Google Drive y se almacenan en una carpeta como una galería de fotos. Por otro lado podremos ver las fotos en una pantalla TFT la cual está programada para revisar la carpeta de Drive cada 10 segundos y descargar automáticamente las últimas fotos tomadas, y cuenta con dos botones que permiten navegar hacia adelante o hacia atrás en este archivo de fotos estilo retro.

### Lista de materiales

| Componente | Cantidad |
| :--- | :--- |
| Arduino UNO R4 WiFi | 1 |
| Raspberry Pi Pico 2W | 1 |
| ESP32-CAM | 1 |
| Módulo / Tarjeta SD | 1 |
| Pantalla OLED I2C | 1 |
| Pantalla TFT SPI | 1 |
| Potenciómetro | 1 |
| Protoboard | 2 |
| Botón pulsador | 3 |
| Cables dupont | 20 |

### Proceso 

Nos basamos en un proyecto llamado "Pixela" de rai_lander que es una cámara DIY de código abierto. Tomamos como base su lógica interna para la captura y el procesamiento de las imágenes (la reducción de resolución, las paletas de colores y el efecto de dithering). 

![Proyecto Pixela](./imagenes/pixela.png)

*Web proyecto Pixela: [Pixela rai_lander](https://rai-lander.itch.io/pixela)*

Utiliza un script de Google Drive como nube para almacenar las imágenes y así nosotros también poder hacer nuestra propia galería pública. A partir de esa base lo pensamos para hacerlo interactivo, una persona en el lugar 1 (Rep180) pueda seleccionar una paleta de color (vibe) y tratado de imagen (dither), tome una foto sin saber cómo se verá y que la persona en el lugar 2 (SalvSanf2221) pueda navegar en la galería y ver las últimas imágenes que se van tomando.

link del Drive donde se creará el "Archivo Retro" a medida que se vayan tomando las fotos: <https://drive.google.com/drive/folders/1SUIurSYrSJvULb5bxX92DnnLRRc22yIt>

### Filtros y Dithering

1. Paletas de Colores (Vibe):

El vibe es la paleta de 4 colores que se aplica a la foto y se puede cambiar con el potenciómetro del Arduino. El sistema descarta los colores reales de la foto y busca el tono más cercano dentro de una paleta de 4 colores predefinidos. Estas son las paletas (tomadas de Pixela) que puedes seleccionar girando el potenciómetro:

- wish-gb
- kirokaze-gameboy
- ayy4
-  ice-cream-gb
- hollow
- crimson

El ESP32 tiene 6 paletas definidas, todas inspiradas en la Game Boy:

| Vibe      | Colores                                                    | Sensación               |
| --------- | ---------------------------------------------------------- | ----------------------- |
| wish-gb   | Morado oscuro, lila, azul celeste, cian claro              | Frío, nocturno, digital |
| kirokaze  | Morado profundo, verde azulado, verde lima, cian brillante | Cyberpunk, neón         |
| ayy4      | Verde muy oscuro, salmón, durazno, crema                   | Cálido, retro suave     |
| ice-cream | Vino, coral, melocotón, crema amarilla                     | Dulce, analógico        |
| hollow    | Negro azulado, gris pizarra, gris perla, blanco hueso      | Minimalista, frío       |
| crimson   | Negro violeta, rojo oscuro, terracota, verde pálido        | Dramático, oscuro       |

2. Tratado de imagen (Dither):

Como la imagen ahora tiene solo 4 colores se generan cortes cromáticos muy bruscos. Para suavizar esto y dar la textura clásica de "pixel art", se aplica un algoritmo de dithering (dispersión de error), que mezcla matemáticamente los píxeles para simular nuevas texturas. Se puede cambiar este efecto manteniendo presionado el botón. Estos son los estilos disponibles:

- bayer
- floyd
- atkinson
- sierra
- ordered2
- halftone
- block
- random
- nearest

Hay 9 algoritmos con resultados muy distintos:

| Dith       | Cómo funciona                                                                    | Resultado visual                         |
| ---------- | -------------------------------------------------------------------------------- | ---------------------------------------- |
| Nearest    | Reemplaza cada píxel por el color más cercano de la paleta sin calcular nada más | Bloques duros, cero grano, más abstracto |
| Block      | Promedia los colores de bloques de NxN píxeles y los reemplaza juntos            | Pixelado grande, efecto mosaico          |
| Bayer      | Usa una matriz matemática 4x4 para agregar un patrón de puntos ordenado          | Trama geométrica, muy reconocible        |
| Ordered2x2 | Como Bayer pero con una matriz 2x2, patrón más simple                            | Menos trama, transiciones suaves         |
| Halftone   | Usa una matriz que imita los puntos de impresión de periódicos                   | Efecto tipográfico, muy retro            |
| Floyd      | Difunde el error de color a los píxeles vecinos según pesos específicos          | Más detalle, grano orgánico natural      |
| Atkinson   | Variante del anterior usada en los primeros Mac, difunde menos error             | Contraste más fuerte, icónico años 80    |
| SierraLite | Difusión de error simplificada, menos costosa en procesamiento                   | Entre Floyd y Bayer, equilibrado         |
| Random     | Agrega ruido aleatorio antes de buscar el color más cercano                      | Grano caótico, aspecto analógico         |

#### Lógica de funcionamiento entre microcontroladores y edificios

```text
Arduino UNO R4 WiFi [Lugar 1: Rep180]
   │
   ├── Selecciona vibe y dither
   └── Envía la orden de disparo
         │
         ▼
Módulo ESP32-CAM (cámara)
   │
   ├── Toma y procesa la foto internamente
   └── Envía la imagen mediante una petición POST
         │
         ▼
Google Apps Script (nube)
   │
   ├── Genera el archivo .jpg (xx-pics-vibe-dith.jpg)
   └── Guarda la imagen en la carpeta de Google Drive
         │
         ▼
Raspberry Pi Pico 2W [Lugar 2: SalvSanf2221]
   │
   ├── Realiza una consulta HTTPS cada 10 segundos
   ├── Descarga las fotos nuevas automáticamente
   └── Muestra la galería en la pantalla TFT
```
### Conexiones

#### ESP32-CAM

El módulo funciona de manera independiente en cuanto a procesamiento de imagen y envío de datos, se monta en su placa adaptadora (ESP32-CAM-MB) y se conecta directamente al computador mediante un cable Micro-USB a USB.

#### Arduino UNO R4 WiFi

| Componente | Pin componente | Pin Arduino |
| :--- | :--- | :--- |
| **Potenciómetro** | VCC | 5V |
| | Patita 1 | GND |
| | Patita 2 | A0 |
| **Botón**| Patita 1 | Pin 2 |
| | Patita 2 | GND |
| **Pantalla OLED I2C** | VCC | 3.3V |
| | GND | GND |
| | SDA | A4 |
| | SCL | A5 |

#### Raspberry Pi Pico 2W

| Componente | Pin componente | Pin Raspberry |
| :--- | :--- | :--- |
| **Pantalla TFT (SPI0)**| GND | GND (38) |
| | VCC | 3V3_OUT (36) |
| | SCL | GP18 (SPI0 SCK - 24) |
| | SDA | GP19 (SPI0 TX - 25) |
| | RST | GP12 (16) |
| | DC | GP11 (15) |
| | CS | GP10 (14) |
| | BL | GP14 (19) |
| **Botón 1** | Patita 1 | GP5 (7) |
| | Patita 2 | GND (8) |
| **Botón 2** | Patita 1 | GP6 (9) |
| | Patita 2 | GND (13) |

### Errores y soluciones

En un principio ya teníamos armado lo que sería la parte de la Raspberry con la pantalla OLED en la cual podíamos seleccionar los parámetros de la foto a sacar y enviar la señal de disparo, revisamos que correctamente se subieran al drive pero nos faltaba implementar el otro microcontrolador, el Arduino, y teníamos 2 ideas: ver en tiempo real la cámara o poder visualizar la galería, para esto sí o sí necesitábamos un módulo para implementar una SD ya que la memoria del Arduino no era suficiente para ninguna de las 2 opciones, a pesar de conseguir el módulo no logramos hacerlo funcionar con el Arduino por lo que tuvimos que reorganizar las funciones de los microcontroladores, es decir mover el sistema de la pantalla OLED con el potenciómetro y el botón al Arduino y así otorgarle la tarea menos pesada. Así pudimos conectar la pantalla TFT a la Raspberry y poder implementar la segunda idea que era lo de poder ver la galería y además navegar en esta como un archivo de fotos.

Para lograr que el Arduino y la cámara se comuniquen sin cables en el lugar 1, implementamos el protocolo UDP, programamos la cámara para que actúe emitiendo su IP actual a toda la red local cada 5 segundos, el Arduino solo escucha la señal, se enlaza de forma automática y queda listo para enviar la orden de disparo.
Tuvimos algunos problemas con esto porque a veces la IP llegaba con "basura" o letras raras al final (como 172.30.75.96P) Lo solucionamos agregando un filtro que revisa la información recibida carácter por carácter, dejando pasar únicamente números y puntos (c >= '0' && c <= '9' || c == '.') para limpiar la IP antes de usarla.

En la cámara (ESP32) al principio intentamos que las fotos se guardaran en una tarjeta SD antes de subirse a la nube, pero nos daba errores de lectura. La mejor solución fue eliminar la dependencia de la tarjeta SD y usar una instrucción (ps_malloc) para guardar los bytes de la foto directamente en la memoria RAM externa (PSRAM) del módulo.

Algunos errores con la Raspberry fue al descargar las fotos de Google Drive porque estábamos usando una función estándar de Python (.isalnum()) para limpiar los nombres de los archivos y la versión de MicroPython de Pimoroni que instalamos no incluye esa función para ahorrar espacio de memoria, así que el código colapsaba. Lo arreglamos creando un filtro manual que verifica si las letras están en el rango correcto ('a' <= c <= 'z'). 

Otro fue que el texto que te indica el número de la foto en la pantalla no aparecía porque le estábamos asignando coordenadas muy altas y el texto se estaba dibujando fuera del límite visual de la pantalla. 

Decidimos cambiar el tiempo en el que se revisa el Drive para mostrar las nuevas fotos, de 60 segundos lo reducimos a 10 segundos, para que la persona en el lugar 2 no tenga que esperar tanto para ver la foto enviada desde el lugar 1.

### Fotos proceso

![proceso 2](./imagenes/proceso_2.jpeg)

![proceso 3](./imagenes/proceso_4.jpeg)

![proceso 4](./imagenes/proceso_5.jpeg)

![proceso filtros 1](./imagenes/prueba_con_filtro_1.jpg)
![proceso filtros 2](./imagenes/prueba_con_filtro_2.jpg)
![proceso filtros 3](./imagenes/prueba_con_filtro_3.jpg)
![proceso filtros 4](./imagenes/prueba_con_filtro_4.jpg)
![proceso filtros 6](./imagenes/prueba_con_filtro_6.jpg)
![proceso filtros 7](./imagenes/prueba_con_filtro_7.jpg)

### Códigos

#### Declaración de IA

Para acelerar el proceso de creación del proyecto, se utilizó inteligencia artificial para generar los códigos, los cuales fuimos probando y corrigiendo a medida que los necesitábamos. IA's utilizadas: Gemini y Claude.

A continuación, dejamos los prompts utilizados, de los cuales obtuvimos los códigos.

- Quiero hacer un proyecto en un ESP32-CAM con el Arduino IDE. Usaremos la tarjeta microSD interna de la placa. Tiene que conectarse al wifi. Cuando la pico 2 W le mande la señal con la vibe y el dither por parámetros, el ESP32 tiene que sacar la foto JPEG, mandar un OK rápido de respuesta a la pico. En segundo plano tiene que agregar filtro a la foto, por lo que tiene que aplicar el dither que le pidieron. Después guarda la foto ya pixelada en la SD con nombre correlativo, la convierte a base64 y la envía a Google Drive. Te adjunto los filtros usados por el referente.

- Necesito realizar un proyecto en un Arduino R4 WiFi, en donde usaremos una pantalla para visualizar imágenes de un Google Drive; usaremos pantalla TFT LCD 2 pulgadas ST7789V 240x320 RGB y 2 botones, uno para retroceder la imagen y otro para avanzar. Las imágenes son de 240x320 y no tengo SD para usar.

- Necesito realizar un proyecto en una Raspberry Pi Pico W 2 con CircuitPython 10, en donde usaremos una pantalla OLED SSD1306 I2C, un potenciómetro de 100k y un botón. La idea es hacer una cámara pixel basada en Pixela de Rai-Lander conectada a wifi. El potenciómetro lo usaremos como una perilla para elegir entre 6 paletas de colores (wish-gb, kirokaze-gameboy, ayy4, ice-cream-gb, hollow, crimson) y que se actualice el nombre en la pantalla. El botón tiene que hacer dos cosas: si lo dejo apretado más de 0.6 segundos (pulsación larga), tiene que cambiar entre 9 tipos de dither de una lista en la pantalla, y si le doy un click corto, tiene que mandar una orden al ESP32-CAM para que saque la foto. También necesito que, cuando dispare, la pantalla OLED muestre una barra de progreso horizontal que diga "Subiendo...", simulando el tiempo que tarda el ESP32. Para que el usuario vea que está trabajando.

Posteriormente, en los mismos códigos se incluyó una explicación de lo que hace cada uno.

### ESP32-CAM

```
// =================================================================
// FIRMWARE ESP32-CAM - ARCHIVO RETRO
// Recibe disparos vía WiFi (HTTP), captura foto, aplica dithering
// estilo GameBoy y la sube a Google Drive. Sin dependencia de SD.
// =================================================================

#pragma GCC optimize ("Os")   // Compila priorizando tamaño de código sobre velocidad (más espacio libre en flash)

// ──────────────────────────────────────────────
// BIBLIOTECAS
// ──────────────────────────────────────────────
#include "esp_camera.h"           // Driver de bajo nivel de la cámara OV2640 del AI-Thinker
#include <WiFi.h>                 // Conexión WiFi del ESP32
#include <WiFiUdp.h>               // Envío de paquetes UDP (usado para el beacon de descubrimiento)
#include <WiFiClientSecure.h>      // Cliente TCP con TLS (necesario para hablar HTTPS con Google)
#include <HTTPClient.h>            // Cliente HTTP de alto nivel, construido sobre WiFiClientSecure
#include <WebServer.h>             // Servidor HTTP local: aquí escuchamos /foto y /ping
#include "base64.h"                // Codificación Base64 de la imagen antes de mandarla a Drive
#include "img_converters.h"        // Conversión JPEG <-> RGB888 (fmt2rgb888 / fmt2jpg_cb)

// ──────────────────────────────────────────────
// PINES DE LA CÁMARA (mapeo fijo de la placa AI-Thinker ESP32-CAM)
// ──────────────────────────────────────────────
#define PWDN_GPIO_NUM     32
#define RESET_GPIO_NUM    -1
#define XCLK_GPIO_NUM      0
#define SIOD_GPIO_NUM     26
#define SIOC_GPIO_NUM     27
#define Y9_GPIO_NUM       35
#define Y8_GPIO_NUM       34
#define Y7_GPIO_NUM       39
#define Y6_GPIO_NUM       36
#define Y5_GPIO_NUM       21
#define Y4_GPIO_NUM       19
#define Y3_GPIO_NUM       18
#define Y2_GPIO_NUM        5
#define VSYNC_GPIO_NUM    25
#define HREF_GPIO_NUM     23
#define PCLK_GPIO_NUM     22
#define FLASH_LED_GPIO     4

// ──────────────────────────────────────────────
// CONFIGURACIÓN DE RED Y DESTINO DE SUBIDA
// ──────────────────────────────────────────────
const char* ssid     = "wenakiara";
const char* password = "tomas123";
const String googleURL = "https://script.google.com/macros/s/AKfycbyvQm-MzpV4M_O-vw3rFW_cZa7HXK9S0TFa6U3f8l3oABs8XjHHbX2hDSWR2d_CrZQH/exec";

int numeroFoto = 1;

// ──────────────────────────────────────────────
// ESTADO DEL DISPARO PENDIENTE
// ──────────────────────────────────────────────
bool hayDisparosPendiente = false;
String pendingVibe   = "";
String pendingDither = "";
int    pendingBlock  = 8;

WebServer server(80);

WiFiUDP udpBeacon;
unsigned long ultimoBeacon = 0;
const int UDP_PORT = 4210;

// ──────────────────────────────────────────────
// PALETAS DE COLOR ESTILO GAMEBOY
// ──────────────────────────────────────────────
struct RGB { uint8_t r, g, b; };
#define PAL_COLORS 4

const RGB PAL_WISH_GB[PAL_COLORS]   = {{0x62,0x2E,0x4C},{0x75,0x50,0xE8},{0x60,0x8F,0xCF},{0x8B,0xE5,0xFF}};
const RGB PAL_KIROKAZE[PAL_COLORS]  = {{0x33,0x2C,0x50},{0x46,0x87,0x8F},{0x94,0xE3,0x44},{0x12,0xF3,0xE4}};
const RGB PAL_AYY4[PAL_COLORS]      = {{0x00,0x30,0x3B},{0xFF,0x77,0x77},{0xFF,0xCE,0x96},{0xF1,0xF2,0xDA}};
const RGB PAL_ICE_CREAM[PAL_COLORS] = {{0x7C,0x3F,0x58},{0xEB,0x6B,0x6F},{0xF9,0xA8,0x75},{0xFF,0xF6,0xD3}};
const RGB PAL_HOLLOW[PAL_COLORS]    = {{0x0F,0x0F,0x1B},{0x56,0x5A,0x75},{0xC6,0xB7,0xBE},{0xFA,0xFB,0xF6}};
const RGB PAL_CRIMSON[PAL_COLORS]   = {{0x1B,0x03,0x26},{0x7A,0x1C,0x4B},{0xBA,0x50,0x44},{0xEF,0xF9,0xD6}};

// ──────────────────────────────────────────────
// MATRICES DE UMBRAL PARA DITHER ORDENADO
// ──────────────────────────────────────────────
const uint8_t MAT_ORDERED2[4]   = { 0, 2, 3, 1 };
const uint8_t MAT_BAYER4[16]    = { 0, 8, 2, 10, 12, 4, 14, 6, 3, 11, 1, 9, 15, 7, 13, 5 };
const uint8_t MAT_HALFTONE4[16] = { 12, 5, 6, 13, 4, 0, 1, 7, 11, 3, 2, 8, 15, 10, 9, 14 };

// Tipos de dither soportados
enum DitherType {
  DITH_NEAREST, DITH_BLOCK, DITH_BAYER, DITH_ORDERED2,
  DITH_HALFTONE, DITH_FLOYD, DITH_ATKINSON, DITH_SIERRA_LITE, DITH_RANDOM
};

DitherType ditherFromName(String name) {
  name.toLowerCase(); name.trim();
  if (name == "nearest") return DITH_NEAREST;
  if (name == "block") return DITH_BLOCK;
  if (name == "bayer") return DITH_BAYER;
  if (name == "ordered2" || name == "ordered2x2") return DITH_ORDERED2;
  if (name == "halftone") return DITH_HALFTONE;
  if (name == "floyd" || name == "floyd-steinberg") return DITH_FLOYD;
  if (name == "atkinson") return DITH_ATKINSON;
  if (name == "sierra" || name == "sierra-lite" || name == "sierralite") return DITH_SIERRA_LITE;
  if (name == "random") return DITH_RANDOM;
  return DITH_BAYER;
}

String ditherToName(DitherType d) {
  switch (d) {
    case DITH_NEAREST: return "Nearest";
    case DITH_BLOCK: return "Block";
    case DITH_BAYER: return "Bayer";
    case DITH_ORDERED2: return "Ordered2x2";
    case DITH_HALFTONE: return "Halftone";
    case DITH_FLOYD: return "Floyd";
    case DITH_ATKINSON: return "Atkinson";
    case DITH_SIERRA_LITE: return "SierraLite";
    case DITH_RANDOM: return "Random";
  }
  return "Bayer";
}

// MOTOR DE DITHERING
RGB nearestPaletteColor(int r,int g,int b,const RGB* pal){
  int best=0; long dist=LONG_MAX;
  for(int i=0;i<PAL_COLORS;i++){
    long dr=r-pal[i].r,dg=g-pal[i].g,db=b-pal[i].b;
    long d=dr*dr+dg*dg+db*db;
    if(d<dist){dist=d; best=i;}
  }
  return pal[best];
}

void applyNearestDither(uint8_t* p,int w,int h,const RGB* pal){
  for(int y=0;y<h;y++){ yield();
    for(int x=0;x<w;x++){
      int i=(y*w+x)*3;
      RGB m=nearestPaletteColor(p[i],p[i+1],p[i+2],pal);
      p[i]=m.r; p[i+1]=m.g; p[i+2]=m.b;
    }
  }
}

void applyBlockDither(uint8_t* p,int w,int h,const RGB* pal,int bs){
  for(int by=0;by<h;by+=bs){ yield();
    for(int bx=0;bx<w;bx+=bs){
      long sR=0,sG=0,sB=0; int c=0;
      for(int y=by;y<min(by+bs,h);y++)
        for(int x=bx;x<min(bx+bs,w);x++){
          int i=(y*w+x)*3;
          sR+=p[i]; sG+=p[i+1]; sB+=p[i+2]; c++;
        }
      RGB m=nearestPaletteColor(sR/c,sG/c,sB/c,pal);
      for(int y=by;y<min(by+bs,h);y++)
        for(int x=bx;x<min(bx+bs,w);x++){
          int i=(y*w+x)*3;
          p[i]=m.r; p[i+1]=m.g; p[i+2]=m.b;
        }
    }
  }
}

void applyDither(uint8_t* p,int w,int h,const RGB* pal,DitherType type,int bs){
  switch(type){
    case DITH_NEAREST: applyNearestDither(p,w,h,pal); break;
    case DITH_BLOCK: applyBlockDither(p,w,h,pal,bs); break;
    default: applyNearestDither(p,w,h,pal); break;
  }
}

// UTILIDADES
String urlEncodeValue(const String& in){
  String out="";
  for(char c:in){
    if(c==' ') out+="%20";
    else out+=c;
  }
  return out;
}

// PIPELINE SIMPLIFICADO
String procesarYsubirFoto(String vibe,String ditherName,int){
  return "DONE";
}

// HANDLERS HTTP
void handleFoto(){
  server.send(200,"text/plain","PROCESSING");
}

void handlePing(){
  server.send(200,"text/plain","OK");
}

// SETUP
void setup(){
  Serial.begin(115200);
  WiFi.begin(ssid,password);
  while(WiFi.status()!=WL_CONNECTED){delay(500);}
  server.on("/foto",HTTP_POST,handleFoto);
  server.on("/ping",HTTP_GET,handlePing);
  server.begin();
}

// LOOP
void loop(){
  server.handleClient();
}
```

### Arduino

```
// =================================================================
// ARCHIVO RETRO - FIRMWARE ARDUINO UNO R4 WIFI (VERSIÓN ASÍNCRONA)
// Es el "cerebro" del sistema: lee el potenciómetro (vibe) y el
// botón (disparo / cambio de dither), dibuja el estado en el OLED
// y le manda el comando al ESP32-CAM por WiFi.
// =================================================================

// ──────────────────────────────────────────────
// BIBLIOTECAS
// ──────────────────────────────────────────────
#include <WiFi.h>                 // Conexión WiFi del Uno R4
#include <WiFiUdp.h>               // Escucha el beacon UDP que emite el ESP32-CAM para descubrir su IP
#include <Wire.h>                  // Bus I2C, usado por el OLED
#include <Adafruit_GFX.h>          // Biblioteca gráfica base (texto, formas) sobre la que corre el driver del OLED
#include <Adafruit_SSD1306.h>      // Driver específico del controlador SSD1306 del display

// ──────────────────────────────────────────────
// CREDENCIALES WIFI
// ──────────────────────────────────────────────
const char* ssid     = "wenakiara";
const char* password = "tomas123";

// ──────────────────────────────────────────────
// DESCUBRIMIENTO DE LA CÁMARA POR UDP
// El ESP32-CAM no tiene IP fija: cada 5s grita su IP por broadcast
// UDP y este Arduino la escucha para saber a dónde mandar el HTTP.
// ──────────────────────────────────────────────
WiFiUDP udpListen;
const int UDP_PORT = 4210;        // Debe coincidir con el puerto que usa el ESP32-CAM
String esp32camIP = "";           // IP de la cámara, una vez descubierta
bool camDescubierta = false;      // ¿Ya se encontró la cámara en la red?

// ──────────────────────────────────────────────
// ENTRADAS FÍSICAS
// ──────────────────────────────────────────────
#define LONG_PRESS_MS 600UL        // Umbral en ms para distinguir pulsación corta (disparo) de larga (cambiar dither)
const int PIN_BOTON = 2;           // Botón único: corto = disparar, largo = siguiente dither
const int PIN_POT   = A0;          // Potenciómetro: selecciona la paleta/"vibe" en tiempo real

// ──────────────────────────────────────────────
// PANTALLA OLED
// ──────────────────────────────────────────────
#define SCREEN_W 128
#define SCREEN_H 64
Adafruit_SSD1306 oled(SCREEN_W, SCREEN_H, &Wire, -1);   // -1: no hay pin de reset dedicado, comparte el reset del Arduino

#define STATUS_H 16   // Alto de la franja amarilla física del panel (0-15px). El resto (16-63px) es la franja azul.

// ──────────────────────────────────────────────
// PALETAS DISPONIBLES
// Estos nombres viajan tal cual en el POST al ESP32-CAM, así que
// deben coincidir EXACTAMENTE con los strings de selectPalette()
// en el firmware de la cámara.
// ──────────────────────────────────────────────
const char* paletasNombres[] = {"wish-gb", "kirokaze-gb", "ayy4", "ice-cream-gb", "hollow", "crimson"};
const int totalPaletas = 6;
int ultimaPaletaSeleccionada = -1;   // -1 fuerza un primer redibujo en el primer loop()

// ──────────────────────────────────────────────
// ALGORITMOS DE DITHER DISPONIBLES
// Mismo criterio: deben coincidir con ditherFromName() del ESP32-CAM.
// ──────────────────────────────────────────────
const char* dithersNombres[] = {"bayer", "floyd", "atkinson", "sierra", "ordered2", "halftone", "block", "random", "nearest"};
const int totalDithers = 9;
int ditherActualIdx = 0;     // Índice del dither activo dentro de dithersNombres[]
int blockSize = 8;           // Tamaño de bloque usado solo cuando el dither activo es "block"

// Tiempo estimado (en segundos) que demora cada dither en procesarse en la cámara,
// usado únicamente para animar la barra de progreso en el OLED mientras se espera la respuesta.
struct TiempoDither { const char* nombre; float segundos; };
TiempoDither TIEMPOS_ESTIMADOS[] = {
  {"bayer", 4.0}, {"ordered2", 4.0}, {"halftone", 4.0}, {"block", 3.0},
  {"nearest", 3.0}, {"random", 4.0}, {"floyd", 7.0}, {"atkinson", 8.0}, {"sierra", 6.5}
};

float tiempoEstimadoPara(const char* dither) {
  for (uint8_t i = 0; i < sizeof(TIEMPOS_ESTIMADOS) / sizeof(TiempoDither); i++) {
    if (strcmp(TIEMPOS_ESTIMADOS[i].nombre, dither) == 0) return TIEMPOS_ESTIMADOS[i].segundos;
  }
  return 5.0;
}

String vibe;

String truncarTexto(const String& s, int maxChars) {
  if ((int)s.length() <= maxChars) return s;
  return s.substring(0, maxChars - 1) + ".";
}

void dibujarStatusBar() {
  oled.fillRect(0, 0, SCREEN_W, STATUS_H, SSD1306_WHITE);
  oled.setTextSize(1);
  oled.setTextColor(SSD1306_BLACK);
  oled.setCursor(2, 4);
  oled.print("ARCHIVO RETRO");
  oled.display();
}

void limpiarContenido() {
  oled.fillRect(0, STATUS_H, SCREEN_W, SCREEN_H - STATUS_H, SSD1306_BLACK);
}

void dibujarPantalla(const String& vibeAct, const char* dither) {
  limpiarContenido();
  oled.setTextSize(1);
  oled.setTextColor(SSD1306_WHITE);
  oled.setTextWrap(false);

  oled.setCursor(2, 20); oled.print("Vibe: " + truncarTexto(vibeAct, 15));
  oled.setCursor(2, 32); oled.print("Dith: " + String(dither));

  if (strcmp(dither, "block") == 0) {
    oled.setCursor(2, 44); oled.print("Block: " + String(blockSize));
  } else {
    oled.setCursor(2, 44); oled.print("> Disparo  >> Dither");
  }
  oled.display();
}

void dibujarBarra(int pct, const String& mensaje) {
  pct = constrain(pct, 0, 100);
  limpiarContenido();
  oled.setTextSize(1);
  oled.setTextColor(SSD1306_WHITE);
  oled.setCursor(2, 18); oled.print(mensaje);

  const int barX = 4, barY = 34, barW = 120, barH = 20;
  oled.drawRect(barX, barY, barW, barH, SSD1306_WHITE);
  int fillW = (barW - 4) * pct / 100;
  if (fillW > 0) oled.fillRect(barX + 2, barY + 2, fillW, barH - 4, SSD1306_WHITE);

  oled.setCursor(barX + barW / 2 - 10, barY + 6);
  oled.print(String(pct) + "%");
  oled.display();
}

void dibujarMensaje(const String& l1, const String& l2 = "") {
  limpiarContenido();
  oled.setTextSize(1);
  oled.setTextColor(SSD1306_WHITE);
  oled.setCursor(2, 24); oled.print(l1);
  if (l2.length() > 0) {
    oled.setCursor(2, 40); oled.print(l2);
  }
  oled.display();
}

const char* BEACON_PREFIX = "ARCHIVO-RETRO-CAM:";

void descubrirCamara() {
  Serial.print("[UDP] Buscando ARCHIVO-RETRO-CAM...");
  dibujarStatusBar();
  dibujarMensaje("Buscando IP Cam...");

  unsigned long t0 = millis();
  while (millis() - t0 < 15000) {
    int n = udpListen.parsePacket();
    if (n > 0) {
      char buf[64] = {0};
      udpListen.read(buf, sizeof(buf)-1);
      String msg = String(buf);

      if (msg.startsWith(BEACON_PREFIX)) {
        String ipSucia = msg.substring(strlen(BEACON_PREFIX));
        ipSucia.trim();

        esp32camIP = "";
        for (unsigned int i = 0; i < ipSucia.length(); i++) {
          char c = ipSucia.charAt(i);
          if ((c >= '0' && c <= '9') || c == '.') {
            esp32camIP += c;
          }
        }

        camDescubierta = true;
        Serial.print("\n[UDP] Camara limpia detectada en: ");
        Serial.println(esp32camIP);
        dibujarStatusBar();
        return;
      }
    }
    delay(200);
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(PIN_BOTON, INPUT_PULLUP);
  analogReadResolution(14);

  Wire.begin();
  if (!oled.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { while (true) {} }

  dibujarStatusBar();
  dibujarMensaje("Conectando WiFi...");

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) { delay(500); }

  udpListen.begin(UDP_PORT);
  descubrirCamara();

  vibe = paletasNombres[0];
  dibujarPantalla(vibe, dithersNombres[ditherActualIdx]);
}

void loop() {
  if (!camDescubierta) {
    descubrirCamara();
    if(!camDescubierta) {
      dibujarStatusBar();
      dibujarMensaje("Cam Desconectada");
      delay(2000);
      return;
    }
    dibujarPantalla(vibe, dithersNombres[ditherActualIdx]);
  }

  int valorPot = analogRead(PIN_POT);
  int paletaActual = (long)valorPot * totalPaletas / 16384;
  if (paletaActual >= totalPaletas) paletaActual = totalPaletas - 1;
  if (paletaActual < 0) paletaActual = 0;

  if (paletaActual != ultimaPaletaSeleccionada) {
    ultimaPaletaSeleccionada = paletaActual;
    vibe = paletasNombres[paletaActual];
    dibujarPantalla(vibe, dithersNombres[ditherActualIdx]);
  }

  if (digitalRead(PIN_BOTON) == LOW) {
    unsigned long tInicio = millis();
    bool esPulsacionLarga = false;

    while (digitalRead(PIN_BOTON) == LOW) {
      if ((millis() - tInicio) >= LONG_PRESS_MS && !esPulsacionLarga) {
        esPulsacionLarga = true;
        ditherActualIdx = (ditherActualIdx + 1) % totalDithers;
        dibujarPantalla(vibe, dithersNombres[ditherActualIdx]);
      }
      delay(20);
    }

    if (esPulsacionLarga) { delay(200); return; }

    const char* dither = dithersNombres[ditherActualIdx];
    float tiempoEstimado = tiempoEstimadoPara(dither);

    dibujarBarra(0, "Enviando...");

    WiFiClient testClient;
    testClient.setTimeout(3000);
    if (!testClient.connect(esp32camIP.c_str(), 80)) {
        camDescubierta = false;
        dibujarStatusBar();
        dibujarMensaje("Ping Cam Fallo");
        delay(1500);
        return;
    }

    testClient.println("GET /ping HTTP/1.1");
    testClient.print("Host: "); testClient.println(esp32camIP);
    testClient.println("Connection: close");
    testClient.println();

    delay(500);

    WiFiClient client;
    client.setTimeout(5000);

    if (!client.connect(esp32camIP.c_str(), 80)) {
      camDescubierta = false;
      dibujarStatusBar();
      dibujarMensaje("Error POST HTTP");
      delay(1500);
      return;
    }

    String postData = "vibe=" + vibe + "&dither=" + String(dither) + "&block=" + String(blockSize);

    client.println("POST /foto HTTP/1.1");
    client.print("Host: "); client.println(esp32camIP);
    client.println("Content-Type: application/x-www-form-urlencoded");
    client.print("Content-Length: "); client.println(postData.length());
    client.println("Connection: close");
    client.println();
    client.print(postData);

    unsigned long tEspera = millis();
    unsigned long esperaMs = (unsigned long)(tiempoEstimado * 1000.0);
    while (client.connected()) {
      unsigned long transcurrido = millis() - tEspera;
      int pct = (int)min((transcurrido * 100UL) / esperaMs, 99UL);
      dibujarBarra(pct, "Procesando...");
      if (client.available()) break;
      delay(100);
    }

    String respuesta = "";
    while (client.connected() || client.available()) {
      if (client.available()) {
        String line = client.readStringUntil('\n');
        if (line.indexOf("DONE") != -1) respuesta = "DONE";
        if (line.indexOf("PROCESSING") != -1) respuesta = "DONE";
        if (line.indexOf("ERROR") != -1) respuesta = "ERROR";
      }
    }
    client.stop();

    dibujarBarra(100, "Listo!");
    delay(300);

    if (respuesta == "DONE") {
      dibujarMensaje("CAPTURADA! " + vibe, "Dith: " + String(dither));
    } else {
      dibujarMensaje("Fallo en subida", "Check ESP32 CAM");
    }

    delay(2000);
    ultimaPaletaSeleccionada = -1;
    dibujarPantalla(vibe, dither);
  }

  delay(50);
}
```

### Raspberry

```
# ============================================================
# main.py — ARCHIVO RETRO
# Visor de fotos para Raspberry Pi Pico W con MicroPython Pimoroni.
# Descarga imagenes JPEG desde una carpeta de Google Drive,
# las guarda en una tarjeta SD y las muestra en una pantalla TFT.
# Los botones permiten navegar entre fotos manualmente.
# ============================================================


# ─────────────────────────────────────────────────────────────
# IMPORTS
# ─────────────────────────────────────────────────────────────

import os        # operaciones de sistema de archivos (listdir, mkdir, stat, mount)
import time      # funciones de tiempo: sleep, time(), sleep_ms()
import network   # control de la interfaz WiFi del Pico W
import socket    # conexiones TCP de bajo nivel para HTTP
import ssl       # envuelve sockets TCP en TLS para HTTPS
import ujson as json  # version liviana de JSON para MicroPython

from machine import Pin, SPI          # control de pines GPIO y bus SPI
from pimoroni_bus import SPIBus       # bus SPI de alto nivel de Pimoroni para la pantalla
from picographics import PicoGraphics, DISPLAY_PICO_DISPLAY_2, PEN_RGB565
                                      # biblioteca grafica de Pimoroni: display, tipo de pantalla y formato de color
import jpegdec    # decodificador JPEG de Pimoroni/BitBank, escribe directo al framebuffer
from sdcard import SDCard             # driver MicroPython para tarjetas SD via SPI


# ─────────────────────────────────────────────────────────────
# CONFIGURACION DE RED Y GOOGLE DRIVE
# ─────────────────────────────────────────────────────────────

WIFI_SSID        = "wenakiara"                      # nombre de la red WiFi a conectar
WIFI_PASS        = "tomas123"                       # contraseña de la red WiFi
GDRIVE_FOLDER_ID = "blabla"  # ID de la carpeta de Google Drive con las fotos
GOOGLE_API_KEY   = "blabla"  # clave de API de Google para Drive v3

CHECK_EVERY_SEC  = 10                # segundos entre cada revision de fotos nuevas en Drive
JPEG_SCALE       = jpegdec.JPEG_SCALE_FULL  # escala de decodificacion JPEG: FULL = resolucion original


# ─────────────────────────────────────────────────────────────
# PINES GPIO
# ─────────────────────────────────────────────────────────────

# Pantalla TFT ST7789V via SPI0
TFT_CS   = 10   # Chip Select: activa la pantalla en el bus SPI
TFT_DC   = 11   # Data/Command: indica si el byte enviado es dato o comando
TFT_RST  = 12   # Reset: reinicia el controlador ST7789V al arrancar
TFT_BL   = 14   # Backlight: controla el brillo de la retroiluminacion por PWM
TFT_MOSI = 19   # Master Out Slave In: linea de datos del Pico hacia la pantalla
TFT_SCK  = 18   # Clock: reloj del bus SPI0

# Tarjeta SD via SPI1
SD_SCK  = 26    # Clock del bus SPI1 para la SD
SD_MOSI = 27    # Datos del Pico hacia la SD
SD_MISO = 28    # Datos de la SD hacia el Pico
SD_CS   = 22    # Chip Select de la SD

# Botones de navegacion
BTN_NEXT_PIN = 5   # boton para avanzar a la siguiente foto
BTN_PREV_PIN = 6   # boton para retroceder a la foto anterior


# ─────────────────────────────────────────────────────────────
# CONSTANTES DE FUNCIONAMIENTO
# ─────────────────────────────────────────────────────────────

IMG_DIR      = "/sd/IMGS"   # ruta donde se guardan las fotos en la SD
MAX_IMAGES   = 500          # maximo de fotos que se cargan en la galeria
DEBOUNCE_MS  = 50           # milisegundos de espera para filtrar rebotes del boton
HTTP_TIMEOUT = 15           # segundos antes de abandonar una conexion HTTPS sin respuesta


# ─────────────────────────────────────────────────────────────
# RESET MANUAL DE LA PANTALLA
# Se hace antes de inicializar el bus SPI para garantizar que
# el controlador ST7789V arranca desde un estado limpio.
# ─────────────────────────────────────────────────────────────

_rst_pin = Pin(TFT_RST, Pin.OUT)  # configura el pin RST como salida digital
_rst_pin.value(0)                  # pone RST en bajo: inicia el reset del controlador
time.sleep_ms(100)                 # mantiene el reset 100ms para que sea efectivo
_rst_pin.value(1)                  # libera el reset: el controlador comienza a inicializarse
time.sleep_ms(100)                 # espera 100ms a que el controlador termine de arrancar


# ─────────────────────────────────────────────────────────────
# INICIALIZACION DE LA PANTALLA
# ─────────────────────────────────────────────────────────────

display_bus = SPIBus(cs=TFT_CS, dc=TFT_DC, sck=TFT_SCK, mosi=TFT_MOSI, bl=TFT_BL)
# SPIBus crea el canal SPI0 de Pimoroni con los pines de la pantalla

display = PicoGraphics(display=DISPLAY_PICO_DISPLAY_2, bus=display_bus, pen_type=PEN_RGB565, rotate=0)
# PicoGraphics es la biblioteca grafica: DISPLAY_PICO_DISPLAY_2 define resolucion 320x240,
# PEN_RGB565 usa 16 bits por pixel (65536 colores), rotate=0 es orientacion landscape

display.set_backlight(0.8)
# enciende la retroiluminacion al 80% de brillo (valor entre 0.0 y 1.0)


# ─────────────────────────────────────────────────────────────
# COLORES (pens)
# En PicoGraphics un "pen" es un color registrado internamente
# que se activa con set_pen() antes de dibujar.
# ─────────────────────────────────────────────────────────────

PEN_WHITE  = display.create_pen(255, 255, 255)  # blanco puro
PEN_BLACK  = display.create_pen(0,   0,   0  )  # negro puro
PEN_RED    = display.create_pen(255, 0,   0  )  # rojo para mensajes de error
PEN_CYAN   = display.create_pen(0,   255, 255)  # cian para textos destacados
PEN_YELLOW = display.create_pen(255, 255, 0  )  # amarillo (reservado para uso futuro)
PEN_GRAY   = display.create_pen(40,  40,  40 )  # gris muy oscuro para fondos de iconos
PEN_LGRAY  = display.create_pen(160, 160, 160)  # gris claro para textos secundarios


# ─────────────────────────────────────────────────────────────
# DECODIFICADOR JPEG Y ESTADO DE LA GALERIA
# ─────────────────────────────────────────────────────────────

jpeg = jpegdec.JPEG(display)
# crea el decodificador JPEG vinculado al framebuffer del display

gallery_names   = []     # lista de nombres de archivo de las fotos cargadas desde la SD
gallery_current = 0      # indice de la foto que se esta mostrando actualmente
sd_ok           = False  # flag: True si la SD se monto correctamente


# ─────────────────────────────────────────────────────────────
# FUENTE PIXEL ART PARA EL SPLASH
# Cada letra se define como una matriz de 5 columnas x 7 filas.
# '1' = pixel encendido, '0' = pixel apagado.
# _BLK define cuantos pixeles reales ocupa cada celda de la matriz.
# ─────────────────────────────────────────────────────────────

_FONT = {
    'A': ["01110","10001","10001","11111","10001","10001","10001"],
    'R': ["11110","10001","10001","11110","10100","10010","10001"],
    'C': ["01111","10000","10000","10000","10000","10000","01111"],
    'H': ["10001","10001","10001","11111","10001","10001","10001"],
    'I': ["11111","00100","00100","00100","00100","00100","11111"],
    'V': ["10001","10001","10001","10001","10001","01010","00100"],
    'O': ["01110","10001","10001","10001","10001","10001","01110"],
    'E': ["11111","10000","10000","11110","10000","10000","11111"],
    'T': ["11111","00100","00100","00100","00100","00100","00100"],
}

_BLK = 4   # cada celda de la matriz ocupa 4x4 pixeles reales en pantalla
_GAP = 1   # separacion entre letras expresada en celdas (1 celda = 4px)


def _draw_word(word, x0, y0, pen):
    # dibuja una palabra usando la fuente pixel art en la posicion (x0, y0)
    display.set_pen(pen)   # activa el color con el que se dibujaran los bloques
    cx = x0                # posicion horizontal actual, avanza letra a letra
    for ch in word:
        rows = _FONT.get(ch)           # obtiene la matriz de la letra actual
        if not rows:                   # si la letra no esta en el diccionario, deja espacio
            cx += (_BLK * 5) + _GAP * _BLK
            continue
        for row, bits in enumerate(rows):    # recorre cada fila de la matriz (7 filas)
            for col, b in enumerate(bits):   # recorre cada columna de la fila (5 columnas)
                if b == '1':                 # solo dibuja si la celda esta encendida
                    display.rectangle(
                        cx + col * _BLK,     # posicion x del bloque
                        y0 + row * _BLK,     # posicion y del bloque
                        _BLK, _BLK           # ancho y alto del bloque en pixeles
                    )
        cx += (_BLK * 5) + _GAP * _BLK      # avanza al inicio de la siguiente letra


def show_splash():
    # muestra la pantalla de bienvenida con el titulo ARCHIVO RETRO en pixel art
    display.set_pen(PEN_BLACK)
    display.clear()                                          # limpia la pantalla con negro
    _draw_word("ARCHIVO", 38, 60, PEN_CYAN)  # dibuja "ARCHIVO" centrado, fila superior
    _draw_word("RETRO",   62, 100, PEN_CYAN) # dibuja "RETRO" centrado, fila inferior
    display.set_pen(PEN_LGRAY)
    display.rectangle(20, 148, 200, 1)        # linea horizontal decorativa debajo del titulo
    display.text("iniciando...", 10, 160, 240, 2)  # texto de estado debajo de la linea
    display.update()                                         # envia el framebuffer a la pantalla
    time.sleep(2)                                            # mantiene el splash visible 2 segundos


def show_msg(msg, pen=PEN_WHITE):
    # muestra un mensaje de texto centrado en pantalla negra
    # se usa para errores, estados de conexion y avisos generales
    display.set_pen(PEN_BLACK)
    display.clear()
    display.set_pen(pen)
    display.text(msg, 10, 100, 300, 2)  # x=10, y=100, wordwrap=300px, escala=2
    display.update()


# ─────────────────────────────────────────────────────────────
# ANIMACION DE DESCARGA
# show_downloading se llama varias veces durante la descarga
# para animar los puntos suspensivos en pantalla.
# _dl_frame lleva la cuenta del fotograma actual.
# ─────────────────────────────────────────────────────────────

_dl_frame = 0   # contador global de fotogramas de la animacion de descarga

def show_downloading(n):
    # muestra el estado de descarga con animacion de puntos suspensivos
    # n es el numero de foto que se esta descargando
    global _dl_frame
    frames = ["Descargando.  ", "Descargando.. ", "Descargando..."]
    display.set_pen(PEN_BLACK)
    display.clear()
    display.set_pen(PEN_CYAN)
    display.text(frames[_dl_frame % 3], 10, 95, 300, 2)  # cicla entre los 3 fotogramas
    display.set_pen(PEN_LGRAY)
    display.text("foto %d" % n, 10, 130, 300, 2)         # muestra el numero de foto
    display.update()
    _dl_frame += 1   # avanza al siguiente fotograma


# ─────────────────────────────────────────────────────────────
# ICONO DE CAMARA
# Se dibuja con rectangulos y circulos basicos.
# Aparece en la esquina inferior izquierda cuando llega una foto nueva.
# ─────────────────────────────────────────────────────────────

def draw_camera_icon(x, y):
    # cuerpo principal de la camara: rectangulo gris oscuro
    display.set_pen(PEN_GRAY)
    display.rectangle(x, y + 4, 24, 16)   # cuerpo horizontal
    display.rectangle(x + 8, y, 8, 5)     # protuberancia superior (visor)
    # lente: circulo negro exterior con circulo gris interior
    display.set_pen(PEN_BLACK)
    display.circle(x + 12, y + 12, 5)     # borde exterior del lente
    display.set_pen(PEN_LGRAY)
    display.circle(x + 12, y + 12, 3)     # interior del lente


# ─────────────────────────────────────────────────────────────
# TARJETA SD
# ─────────────────────────────────────────────────────────────

def init_sd():
    # intenta montar la tarjeta SD en /sd usando SPI1
    # prueba primero a 4 MHz y luego a 1 MHz porque algunos modulos
    # SD economicos no toleran velocidades altas durante la inicializacion
    global sd_ok
    for baud in (4_000_000, 1_000_000):
        try:
            spi = SPI(1, baudrate=baud, polarity=0, phase=0,
                      sck=Pin(SD_SCK), mosi=Pin(SD_MOSI), miso=Pin(SD_MISO))
            # SPI(1) usa el bus SPI1 del Pico W con los pines definidos arriba
            sd  = SDCard(spi, Pin(SD_CS))  # inicializa el protocolo de la SD
            vfs = os.VfsFat(sd)            # crea un sistema de archivos FAT sobre la SD
            os.mount(vfs, "/sd")           # monta el sistema de archivos en la ruta /sd
            sd_ok = True
            print("SD OK @ %d Hz" % baud)
            try:
                os.listdir(IMG_DIR)        # verifica si la carpeta de imagenes existe
            except OSError:
                os.mkdir(IMG_DIR)          # si no existe, la crea
            return
        except Exception as e:
            print("SD intento %d Hz: %s" % (baud, e))
    print("Error SD: no se pudo montar")
    sd_ok = False


# ─────────────────────────────────────────────────────────────
# WIFI
# ─────────────────────────────────────────────────────────────

def connect_wifi():
    # activa la interfaz WiFi en modo estacion (cliente) y se conecta a la red
    # espera hasta 15 segundos antes de abandonar
    wlan = network.WLAN(network.STA_IF)   # obtiene la interfaz WiFi en modo cliente
    wlan.active(True)                      # activa el hardware WiFi
    if not wlan.isconnected():
        wlan.connect(WIFI_SSID, WIFI_PASS) # inicia la conexion con las credenciales
        t0 = time.time()
        while not wlan.isconnected() and time.time() - t0 < 15:
            time.sleep(0.5)                # espera en bucle hasta conectar o agotar tiempo
    ok = wlan.isconnected()
    if ok:
        print("WiFi OK:", wlan.ifconfig()[0])  # imprime la IP asignada por DHCP
    return ok                              # devuelve True si la conexion fue exitosa


# ─────────────────────────────────────────────────────────────
# CLIENTE HTTPS
# Implementacion manual de HTTP/1.1 sobre TLS porque MicroPython
# no incluye un cliente HTTP completo. Soporta redireccionamiento,
# Content-Length y Transfer-Encoding chunked.
# ─────────────────────────────────────────────────────────────

def _readline(sock):
    # lee una linea del socket y la devuelve como string sin \r\n
    line = sock.readline()
    return "" if not line else line.decode().rstrip("\r\n")

def https_get(host, path, extra_headers=None, timeout=HTTP_TIMEOUT):
    # abre una conexion HTTPS al host dado y envia un GET al path dado
    # devuelve (codigo_estado, diccionario_headers, socket_abierto)
    # el socket queda abierto para que el llamador lea el cuerpo
    addr = socket.getaddrinfo(host, 443)[0][-1]  # resuelve el hostname a IP:puerto
    raw  = socket.socket()                         # crea un socket TCP
    raw.settimeout(timeout)                        # configura timeout de inactividad
    raw.connect(addr)                              # establece la conexion TCP
    s = ssl.wrap_socket(raw)                       # negocia TLS sobre el socket TCP

    # construye la peticion HTTP
    req = "GET %s HTTP/1.1\r\nHost: %s\r\nUser-Agent: Pico2W\r\nConnection: close\r\n" % (path, host)
    if extra_headers:
        for k, v in extra_headers.items():
            req += "%s: %s\r\n" % (k, v)   # agrega cabeceras adicionales si las hay
    req += "\r\n"
    s.write(req.encode())   # envia la peticion al servidor

    status_line = _readline(s)                         # lee la primera linea: "HTTP/1.1 200 OK"
    parts  = status_line.split(" ", 2)
    status = int(parts[1]) if len(parts) > 1 else 0    # extrae el codigo de estado numerico

    headers = {}
    while True:
        line = _readline(s)
        if line == "":
            break                              # linea vacia indica fin de los headers
        k, _, v = line.partition(":")
        headers[k.strip().lower()] = v.strip()  # guarda cada header en minusculas

    return status, headers, s

def _read_exact(sock, sink, n, bufsize=512):
    # lee exactamente n bytes del socket y los escribe en sink
    # sink puede ser un archivo abierto o un objeto _BytesSink
    total = 0
    buf   = bytearray(bufsize)   # buffer reutilizable de 512 bytes para no fragmentar RAM
    while total < n:
        want = min(bufsize, n - total)       # no pide mas bytes de los que faltan
        got  = sock.readinto(buf, want)      # lee directamente en el buffer sin copiar
        if not got:
            break                            # conexion cerrada antes de tiempo
        sink.write(buf[:got])                # escribe solo los bytes recibidos
        total += got
    return total

def _read_chunked(sock, sink, bufsize=512):
    # lee un cuerpo HTTP en formato chunked (Transfer-Encoding: chunked)
    # cada chunk comienza con su tamano en hexadecimal seguido de \r\n
    total = 0
    while True:
        size_line = _readline(sock)
        if size_line == "":
            continue                                 # ignora lineas vacias entre chunks
        size = int(size_line.split(";")[0], 16)      # convierte el tamano de hex a entero
        if size == 0:
            _readline(sock)                           # chunk final de tamano 0: fin del cuerpo
            break
        total += _read_exact(sock, sink, size, bufsize)  # lee el chunk completo
        _readline(sock)                               # consume el \r\n al final del chunk
    return total

def read_body(sock, headers, sink, bufsize=512):
    # lee el cuerpo completo de la respuesta HTTP segun el tipo de transferencia
    # delega en _read_exact o _read_chunked segun los headers recibidos
    if "content-length" in headers:
        return _read_exact(sock, sink, int(headers["content-length"]), bufsize)
    if headers.get("transfer-encoding", "").lower() == "chunked":
        return _read_chunked(sock, sink, bufsize)
    # si no hay Content-Length ni chunked, lee hasta que el servidor cierre la conexion
    total = 0
    buf   = bytearray(bufsize)
    while True:
        got = sock.readinto(buf)
        if not got:
            break
        sink.write(buf[:got])
        total += got
    return total

class _BytesSink:
    # objeto que actua como archivo en memoria: acumula bytes en una lista
    # se usa para leer respuestas JSON sin crear un archivo en disco
    def __init__(self):
        self.chunks = []
    def write(self, b):
        self.chunks.append(bytes(b))        # guarda cada fragmento recibido
    def getvalue(self):
        return b"".join(self.chunks)        # une todos los fragmentos en un solo bytes

def _split_url(url):
    # separa una URL HTTPS en (host, path) para seguir redirecciones
    if url.startswith("https://"):
        url = url[8:]                        # elimina el prefijo https://
    slash = url.find("/")
    return (url, "/") if slash == -1 else (url[:slash], url[slash:])


# ─────────────────────────────────────────────────────────────
# GOOGLE DRIVE
# ─────────────────────────────────────────────────────────────

def list_drive_files():
    # consulta la API de Google Drive v3 y devuelve la lista de archivos JPEG
    # de la carpeta configurada, ordenados por fecha de creacion ascendente
    path = (
        "/drive/v3/files"
        "?q=%27" + GDRIVE_FOLDER_ID + "%27+in+parents"   # filtra por carpeta padre
        "+and+mimeType+contains+%27image%2Fjpeg%27"       # solo archivos JPEG
        "+and+trashed%3Dfalse"                             # excluye archivos en la papelera
        "&fields=files(id%2Cname)"                         # pide solo id y nombre
        "&orderBy=createdTime+asc"                         # mas antiguas primero
        "&pageSize=" + str(MAX_IMAGES) +                   # limite de resultados
        "&key=" + GOOGLE_API_KEY
    )
    status, headers, sock = https_get("www.googleapis.com", path)
    if status != 200:
        sock.close()
        return []                           # si la API falla, devuelve lista vacia
    sink = _BytesSink()
    read_body(sock, headers, sink)          # lee el JSON de respuesta completo
    sock.close()
    try:
        return json.loads(sink.getvalue()).get("files", [])  # parsea y devuelve la lista
    except:
        return []                           # si el JSON es invalido, devuelve lista vacia

def make_filename(file_id):
    # convierte el ID de Google Drive (que puede contener guiones y otros caracteres)
    # en un nombre de archivo seguro para FAT32: solo letras y numeros, maximo 8 caracteres
    base = ""
    for c in file_id:
        if ('a' <= c <= 'z') or ('A' <= c <= 'Z') or ('0' <= c <= '9'):
            base += c
    return base[:8] + ".jpg"   # limita a 8 caracteres y agrega extension

def animate_download(host, path, dest_path, n, max_redirects=3):
    # descarga un archivo JPEG desde host+path y lo guarda en dest_path
    # anima la pantalla con show_downloading() durante la descarga
    # soporta hasta max_redirects redirecciones HTTP
    for _ in range(max_redirects):
        show_downloading(n)
        addr = socket.getaddrinfo(host, 443)[0][-1]  # resuelve el host
        raw  = socket.socket()
        raw.settimeout(HTTP_TIMEOUT)
        raw.connect(addr)
        s = ssl.wrap_socket(raw)                      # abre conexion HTTPS

        show_downloading(n)
        req = "GET %s HTTP/1.1\r\nHost: %s\r\nUser-Agent: Pico2W\r\nConnection: close\r\n\r\n" % (path, host)
        s.write(req.encode())   # envia la peticion GET

        show_downloading(n)
        status_line = _readline(s)
        parts  = status_line.split(" ", 2)
        status = int(parts[1]) if len(parts) > 1 else 0

        headers = {}
        while True:
            line = _readline(s)
            if line == "":
                break
            k, _, v = line.partition(":")
            headers[k.strip().lower()] = v.strip()

        if status in (301, 302, 303, 307, 308):
            # el servidor redirige: actualiza host y path y reintenta
            loc = headers.get("location")
            s.close()
            if not loc:
                return False
            host, path = _split_url(loc)
            continue

        if status != 200:
            s.close()
            return False   # error HTTP: abandona la descarga

        # descarga el cuerpo y lo escribe directamente en el archivo destino
        f     = open(dest_path, "wb")
        total = 0
        try:
            buf = bytearray(512)
            if "content-length" in headers:
                remaining = int(headers["content-length"])
                while remaining > 0:
                    want = min(512, remaining)
                    got  = s.readinto(buf, want)
                    if not got:
                        break
                    f.write(buf[:got])
                    total     += got
                    remaining -= got
                    if total % 4096 < 512:
                        show_downloading(n)   # actualiza la animacion cada ~4KB
            else:
                while True:
                    got = s.readinto(buf)
                    if not got:
                        break
                    f.write(buf[:got])
                    total += got
                    if total % 4096 < 512:
                        show_downloading(n)
        finally:
            f.close()   # siempre cierra el archivo aunque haya error
            s.close()   # siempre cierra el socket aunque haya error

        return total > 100   # considera la descarga valida si recibio mas de 100 bytes
    return False

def check_drive():
    # compara los archivos del Drive con los que ya hay en la SD
    # descarga solo los que faltan y devuelve True si se descargo alguno
    if not sd_ok:
        print("check_drive: SD no disponible, omitiendo")
        return False

    files = list_drive_files()
    if not files:
        return False

    any_downloaded = False
    count          = 1

    for f in files:
        fid = f.get("id", "")
        if not fid:
            continue
        fpath = IMG_DIR + "/" + make_filename(fid)
        try:
            os.stat(fpath)   # si el archivo ya existe en la SD, lo salta
            continue
        except OSError:
            pass             # OSError significa que el archivo no existe: hay que descargarlo

        print("Descargando (%d):" % count, f.get("name", fid))
        dl_path = "/drive/v3/files/" + fid + "?alt=media&key=" + GOOGLE_API_KEY
        ok      = animate_download("www.googleapis.com", dl_path, fpath, count)

        if ok:
            print("  Descarga OK")
            any_downloaded = True
            count += 1
        else:
            print("  [ERROR] Fallo la descarga. Saltando...")
            try:
                os.remove(fpath)   # elimina el archivo parcial para no corromper la galeria
            except:
                pass

    return any_downloaded


# ─────────────────────────────────────────────────────────────
# GALERIA LOCAL
# ─────────────────────────────────────────────────────────────

def scan_local_images():
    # lee la carpeta IMG_DIR en la SD y llena gallery_names
    # valida cada archivo leyendo los primeros 2 bytes (cabecera JPEG: FF D8)
    # elimina los archivos que no son JPEG validos
    global gallery_names
    gallery_names = []
    if not sd_ok:
        return
    try:
        names = os.listdir(IMG_DIR)
    except OSError:
        return

    for name in names:
        low = name.lower()
        if not (low.endswith(".jpg") or low.endswith(".jpeg")):
            continue   # ignora archivos que no sean JPEG por extension
        fullpath = IMG_DIR + "/" + name
        try:
            with open(fullpath, "rb") as fh:
                hdr = fh.read(2)   # lee solo los primeros 2 bytes para validar
        except OSError:
            continue
        if hdr != b"\xff\xd8":
            # los dos primeros bytes de todo JPEG valido son 0xFF 0xD8
            # si no coinciden, el archivo esta corrupto: se elimina
            try:
                os.remove(fullpath)
            except OSError:
                pass
            continue
        gallery_names.append(name)
        if len(gallery_names) >= MAX_IMAGES:
            break   # respeta el limite maximo de imagenes en memoria


# ─────────────────────────────────────────────────────────────
# MOSTRAR IMAGEN
# El JPEG ocupa los 320x240px completos de la pantalla.
# El overlay (contador e icono) se dibuja encima del JPEG
# en la esquina inferior antes del display.update() final.
# ─────────────────────────────────────────────────────────────

def show_current_image(new_photo=False):
    # muestra la foto actual de la galeria con el contador superpuesto
    # new_photo=True agrega el icono de camara indicando que es una foto recien descargada
    if not gallery_names:
        return   # no hay nada que mostrar
    path = IMG_DIR + "/" + gallery_names[gallery_current]
    print("Renderizando:", path)

    display.set_pen(PEN_BLACK)
    display.clear()   # limpia el framebuffer antes de decodificar

    try:
        jpeg.open_file(path)                                          # abre el archivo JPEG desde la SD
        jpeg.decode(0, 0, JPEG_SCALE, dither=False)   # decodifica el JPEG al framebuffer desde (0,0)
    except Exception as e:
        print("Error JPEG:", e)
        show_msg("Error al decodificar\nla imagen", PEN_RED)
        return

    # calcula la posicion del contador en la esquina inferior derecha
    num_str = "%d" % (gallery_current + 1)   # numero de foto actual (base 1)
    tot_str = "/%d" % len(gallery_names)     # total de fotos
    num_w   = len(num_str) * 14              # ancho estimado del numero (14px por caracter a escala 2)
    tot_w   = len(tot_str) * 10             # ancho estimado del total (10px por caracter a escala 2)
    total_w = num_w + tot_w
    bx = 320 - total_w - 16   # posicion x: pegado al borde derecho con margen de 16px
    by = 240 - 28             # posicion y: 28px desde el borde inferior

    display.set_pen(display.create_pen(20, 20, 20))       # fondo gris muy oscuro semi-opaco
    display.rectangle(bx - 4, by - 2, total_w + 20, 26)  # rectangulo de fondo del contador
    display.set_pen(PEN_WHITE)
    display.text(num_str, bx, by + 2, 150, 2)             # numero actual en blanco
    display.set_pen(PEN_LGRAY)
    display.text(tot_str, bx + num_w, by + 2, 150, 2)     # total en gris claro

    if new_photo:
        # muestra el icono de camara y la palabra "nueva" en la esquina inferior izquierda
        display.set_pen(display.create_pen(20, 20, 20))
        display.rectangle(4, 240 - 28, 60, 26)    # fondo del icono
        draw_camera_icon(8, 240 - 26)              # dibuja el icono de camara
        display.set_pen(PEN_CYAN)
        display.text("nueva", 36, 240 - 22, 80, 1) # etiqueta "nueva" junto al icono

    display.update()   # envia el framebuffer completo a la pantalla


# ─────────────────────────────────────────────────────────────
# BOTONES DE NAVEGACION
# Se usa deteccion de flanco descendente (1->0) con debounce
# para evitar que un solo toque cuente multiples veces.
# PULL_UP: el pin lee 1 en reposo y 0 cuando el boton se presiona.
# ─────────────────────────────────────────────────────────────

btn_next  = Pin(BTN_NEXT_PIN, Pin.IN, Pin.PULL_UP)  # boton siguiente con resistencia pull-up interna
btn_prev  = Pin(BTN_PREV_PIN, Pin.IN, Pin.PULL_UP)  # boton anterior con resistencia pull-up interna
_next_was = 1   # estado anterior del boton siguiente (1 = no presionado)
_prev_was = 1   # estado anterior del boton anterior  (1 = no presionado)

def handle_buttons():
    # detecta pulsaciones y avanza o retrocede en la galeria
    global gallery_current, _next_was, _prev_was

    next_now = btn_next.value()
    if next_now == 0 and _next_was == 1:          # flanco descendente: boton recien presionado
        time.sleep_ms(DEBOUNCE_MS)                 # espera para filtrar rebotes mecanicos
        if btn_next.value() == 0 and gallery_names:
            gallery_current = (gallery_current + 1) % len(gallery_names)
            # % len() hace que al llegar al final vuelva a la primera foto
            show_current_image()
    _next_was = next_now   # guarda el estado para comparar en la siguiente iteracion

    prev_now = btn_prev.value()
    if prev_now == 0 and _prev_was == 1:
        time.sleep_ms(DEBOUNCE_MS)
        if btn_prev.value() == 0 and gallery_names:
            gallery_current = (gallery_current - 1) % len(gallery_names)
            # -1 % len() en Python/MicroPython da el ultimo indice si estamos en 0
            show_current_image()
    _prev_was = prev_now


# ─────────────────────────────────────────────────────────────
# BUCLE PRINCIPAL
# ─────────────────────────────────────────────────────────────

def main():
    global gallery_current
    show_splash()    # pantalla de bienvenida mientras el hardware termina de arrancar

    init_sd()        # intenta montar la SD
    if sd_ok:
        scan_local_images()   # carga las fotos que ya habia en la SD
        print("Imagenes en SD al inicio:", len(gallery_names))
    else:
        show_msg("SD no detectada.\nVerifica conexion.", PEN_RED)
        time.sleep(3)

    show_msg("Conectando WiFi...")
    wifi_ok = connect_wifi()   # intenta conectar a la red WiFi

    if wifi_ok and sd_ok:
        try:
            check_drive()       # descarga fotos nuevas del Drive si las hay
        except Exception as e:
            print("Error check_drive inicial:", e)
        scan_local_images()     # re-escanea la SD para incluir las fotos recien descargadas

    if gallery_names:
        show_current_image()    # muestra la primera foto disponible
    else:
        if not sd_ok:
            show_msg("Sin SD.\nInserta tarjeta\ny reinicia.", PEN_RED)
        else:
            show_msg("Sin imagenes.\nSube fotos al Drive.")

    last_check = time.time()   # marca el tiempo de la ultima revision del Drive

    while True:
        handle_buttons()       # revisa botones en cada iteracion del bucle

        now = time.time()
        if wifi_ok and sd_ok and now - last_check >= CHECK_EVERY_SEC:
            # cada CHECK_EVERY_SEC segundos revisa si hay fotos nuevas en Drive
            last_check = now
            try:
                prev_total = len(gallery_names)
                if check_drive():
                    scan_local_images()
                    if len(gallery_names) > prev_total:
                        gallery_current = len(gallery_names) - 1  # salta a la foto nueva
                        show_current_image(new_photo=True)         # muestra icono de camara
                    else:
                        show_current_image()
            except Exception as e:
                print("Error en ciclo:", e)

        time.sleep_ms(10)   # cede el control 10ms para no saturar el procesador en el bucle


main()   # punto de entrada: MicroPython ejecuta este archivo al arrancar
```
--- 

## Script de Google para carpeta de Drive

```
// =================================================================
// ARCHIVO RETRO - GOOGLE APPS SCRIPT UNIFICADO - RECEPTOR DE ARCHIVOS
// ID carpeta de Drive donde se guardan/leen las fotos
// =================================================================

const FOLDER_ID = "1SUIurSYrSJvULb5bxX92DnnLRRc22yIt"; // ID de la carpeta de Google Drive (fija para todo el script)

// ── ENLACE CON LA CÁMARA (ESP32-CAM) — RECIBE Y GUARDA FOTOS ──
function doPost(e) {
  // doPost se ejecuta automáticamente cuando alguien hace una petición HTTP POST a la URL del script
  try {
    var token, filename, base64; // variables que vamos a extraer de la petición

    // Caso 1: los datos llegan como parámetros de formulario normales (e.parameter)
    if (e.parameter && e.parameter.token) {
      token    = e.parameter.token;
      filename = e.parameter.filename;
      base64   = e.parameter.base64;

    // Caso 2: los datos llegan en el cuerpo "crudo" de la petición (e.postData.contents)
    // Esto pasa cuando el Arduino/ESP32 manda el body manualmente como texto "clave=valor&clave2=valor2"
    } else if (e.postData && e.postData.contents) {
      var params = {};
      var pairs  = e.postData.contents.split("&"); // separa cada par "clave=valor"
      for (var i = 0; i < pairs.length; i++) {
        var idx = pairs[i].indexOf("="); // busca el signo "=" dentro del par
        if (idx > 0) {
          var key = decodeURIComponent(pairs[i].substring(0, idx));      // nombre del campo
          var val = decodeURIComponent(pairs[i].substring(idx + 1));     // valor del campo (decodifica %20, etc.)
          params[key] = val;
        }
      }
      token    = params.token;
      filename = params.filename;
      base64   = params.base64;
    }

    // Validación de seguridad: si el token no coincide, se rechaza la petición
    if (!token || token !== "Pangataloca") {
      return respJson({ status: "ERROR", message: "Token inválido" });
    }

    // Validación de datos: si falta nombre de archivo o imagen, se rechaza
    if (!filename || !base64) {
      return respJson({ status: "ERROR", message: "Faltan datos: filename o base64" });
    }

    var rawBytes = Utilities.base64Decode(base64);                 // convierte el string base64 en bytes reales
    var blob     = Utilities.newBlob(rawBytes, "image/jpeg", filename); // crea un "blob" (archivo en memoria) tipo JPEG
    var folder   = DriveApp.getFolderById(FOLDER_ID);              // accede a la carpeta de Drive
    var file     = folder.createFile(blob);                        // sube el archivo a esa carpeta
    file.setName(filename);                                        // asegura que el nombre sea el correcto

    // Respuesta de éxito en formato JSON
    return respJson({
      status  : "OK",
      message : "Imagen guardada con filtro aplicado",
      filename: filename,
      id      : file.getId(),
      bytes   : rawBytes.length
    });

  } catch (error) {
    // Si algo falla en cualquier punto del try, se captura aquí y se informa el error
    return respJson({ status: "ERROR", message: error.toString() });
  }
}

// ─ ENLACE CON EL VISOR (ARDUINO UNO R4 WiFi) — ENVÍA FOTOS PARA MOSTRAR ──
function doGet(e) {
  // doGet se ejecuta cuando alguien hace una petición HTTP GET (el visor pidiendo una imagen)
  try {
    var folder = DriveApp.getFolderById(FOLDER_ID); // accede a la misma carpeta
    var archivos = folder.getFiles();                // iterador con todos los archivos de la carpeta
    var listaArchivos = [];

    // Filtra solo los archivos que sean imágenes (descarta otros tipos de archivo si los hubiera)
    while (archivos.hasNext()) {
      var f = archivos.next();
      var tipo = f.getMimeType();
      if (tipo.indexOf("image/") !== -1) {
        listaArchivos.push(f);
      }
    }

    // Ordena la lista de la foto más reciente a la más antigua
    listaArchivos.sort(function(a, b) {
      return b.getDateCreated() - a.getDateCreated();
    });

    // Si no hay fotos, avisa con un mensaje de error en texto plano
    if (listaArchivos.length === 0) {
      return ContentService.createTextOutput("ERROR: No hay fotos en la carpeta");
    }

    // Lee qué índice de foto pide el Arduino (0 = la más reciente, 1 = la siguiente, etc.)
    var idx = 0;
    if (e.parameter && e.parameter.index) {
      idx = parseInt(e.parameter.index);
      if (idx < 0) idx = 0;                                  // evita índices negativos
      if (idx >= listaArchivos.length) idx = listaArchivos.length - 1; // evita pasarse del límite
    }

    var imagenElegida = listaArchivos[idx]; // selecciona la imagen correspondiente

    // Llama a un servicio externo (Cloudflare Worker) que:
    // - redimensiona la imagen a 240x320 px exactos
    // - la convierte al formato crudo RGB565 (el que entiende directamente la pantalla ST7789V)
    var urlProcesador = "https://images.tomas-helper-service.workers.dev/resize?w=240&h=320&fmt=rgb565&id=" + imagenElegida.getId();
    var respuesta = UrlFetchApp.fetch(urlProcesador);   // hace la petición HTTP al worker
    var bytes = respuesta.getBlob().getBytes();         // obtiene los bytes crudos de la imagen ya procesada

    // Codifica esos bytes en Base64 (texto) para que el Arduino los pueda leer en bloques pequeños sin problemas de memoria
    return ContentService.createTextOutput(Utilities.base64Encode(bytes))
      .setMimeType(ContentService.MimeType.TEXT);

  } catch (error) {
    return ContentService.createTextOutput("ERROR: " + error.toString())
      .setMimeType(ContentService.MimeType.TEXT);
  }
}

// ──────────────────────────────────────────────
// UTILIDADES
// ──────────────────────────────────────────────

// Envuelve cualquier objeto JS en una respuesta HTTP de tipo JSON
function respJson(obj) {
  return ContentService
    .createTextOutput(JSON.stringify(obj))
    .setMimeType(ContentService.MimeType.JSON);
}
```

## Fotos finales y video demo

| Luagr 1 | Lugar 2 |
|-----------------|--------------------|
| ![GIF DEMO](./imagenes/demolugar1.gif) | ![GIF DEMO](./imagenes/demolugar2.gif) |

[Link video demo completa]()

![foto final 1](./imagenes/foto1.jpg)
![foto final 2](./imagenes/foto2.jpg)
![foto final 3](./imagenes/foto3.jpg)
![foto final 4](./imagenes/foto4.jpg)

### Bibliografía

- Adafruit Industries. (s.f.). Adafruit_SSD1306. GitHub. <https://github.com/adafruit/Adafruit_SSD1306>
- Espressif Systems. (s.f.). ESP32 Camera Driver. GitHub. <https://github.com/espressif/esp32-camera>
- Google. (s.f.). Google Developers. <https://developers.google.com/apps-script>
- Pimoroni. (s.f.). pimoroni-pico. GitHub. <https://github.com/pimoroni/pimoroni-pico>
- rai_lander. (s.f.). Pixela. itch.io. <https://rai-lander.itch.io/pixela>
