# Grupo-4 - Examen Interacciones Inalámbricas

## Integrantes

- Renata Arévalo Urra / [arevalourra](<https://github.com/isipm08/dis9079-2026-1/tree/main/06-arevalourra>)
- Isidora Pérez Maulén / [isipm08](<https://github.com/isipm08/dis9079-2026-1/tree/main/21-isipm08>)

## Descripción del proyecto

Nuestro proyecto nace del deseo de transformar cada latido en un puente de conexión. Mediante el sensor ECG AD8232, la actividad cardíaca deja de ser una señal invisible para convertirse en información que viaja en cuestión de segundos. A través de Adafruit IO, cada pulso encuentra un camino seguro hasta una pantalla LCD conectada a un segundo microcontrolador, donde los datos cobran vida nuevamente. Así, este sistema no solo captura y transmite información: crea una nueva forma de acompañar, observar, demostrando que incluso el ritmo silencioso del corazón puede trascender la distancia y hacerse presente allí donde más se necesita.

## Materiales usados

| Componente | Valor Unidad | Cantidad | Link |
| --- | --- | --- | --- |
| Arduino UNO R4 WiFi | $38.990 | 2 | <https://arduino.cl/producto/arduino-uno-r4-wifi/?srsltid=AfmBOopyyargcSiTQeFlT3cTN5ide380bxZlQXRZVP4u_op0O-qJcENB> |
| Mini protoboard 170 puntos | $990 | 2 | <https://afel.cl/products/mini-protoboard-170-puntos?_pos=4&_sid=aa0b39e11&_ss=r |
| Cables Dupont (Pack 20 unidades) | $1.000 | 1 | <https://afel.cl/products/pack-20-cables-de-conexion-macho-macho> |
| Sensor de Frecuencia Cardíaca ECG AD8232 Electrocardiograma | $9.990 | 1 | <https://afel.cl/products/sensor-de-frecuencia-cardiaca-ecg-ad8232-electrocardiograma> |
| Pantalla TFT LCD redonda de 1.28" | $4.990 | 1 | <https://www.mechatronicstore.cl/pantalla-tft-lcd-redonda-de-1-28/?srsltid=AfmBOormrgaJyuZokh0vmjczLkHKXalCX8OpIDNKoXI-k0D8GjpyM3mX
| Electrodos PACH ECG TENS 5 unidades | $1.500 | 1 | <https://rambal.com/biometricos/1238-electrodo-ecg.html
| Cable USB C | X | 2 | X


## Proceso de Proyecto
---

### Lunes 01 Junio 

#### 3 Semanas para el examen

Inicio de ideación de examen, estuvimos leyendo e investigando sobre varios sensores, para ver si nos gustaba alguno para realizar nuestro proyecto de examen, nos decidimos por un sensor de pulso, específicamente el Sensor de Frecuencia Cardíaca ECG AD8232 Electrocardiograma,  que es un módulo diseñado para medir la actividad eléctrica del corazón y generar lecturas similares a un electrocardiograma (ECG). Funcionando como una interfaz que extrae, amplifica y filtra las señales eléctricas muy débiles que genera el cuerpo humano al latir. 

Con  este sensor teníamos la idea de obtener registros en vivo de los latidos por minuto del usuario, usaremos la API -> Adafruit IO, que ya conocemos y sabemos su funcionamiento, por el lado de recepción de datos, pensamos en una pantalla LCD que muestre los latidos por minuto, usaremos 2 arduinos, uno para enviar y otro para recibir la información.

![Modulo Sensor](./imagenes/modulo-sensor.webp)

*Modulo Sensor AD8232 - Imagen extraída de página web de AFEL*

https://afel.cl/cdn/shop/files/modulo-sensor-ad8232.jpg?v=1720904051&width=713


### Interacción entre grupos vía Discord

Descripción inicial de nuestro proyecto:

Grupo 04: Queremos lograr una exploración sobre la capacidad de las tecnologías inalámbricas para transportar señales humanas más allá del cuerpo que las origina. El proyecto captura el ritmo cardíaco de una persona y lo transforma en una presencia remota, permitiendo que sus pulsaciones sean observadas en otro lugar en tiempo real. A través de esta conexión invisible, los latidos dejan de ser una experiencia íntima para convertirse en un lenguaje compartido entre dispositivos, espacios y personas. La propuesta reflexiona sobre cómo la información biológica puede viajar, ser representada y generar nuevas formas de percepción y vínculo mediante redes inalámbricas.

- Aarón nos sugiere computación inalámbrica en vez de tecnologías inalámbricas

- Aarón nos pregunta lo siguiente: van a procesar esos datos de pulso? van a enviar el pulso directamente? o un resumen en latidos por minuto?

    -  Resp: Resumen en latidos por minuto

- Jesús Miranda nos pregunta: ¿qué pasa en este caso en el dispositivo receptor? ya que en el párrafo dice que los latidos "son observados" pero no queda claro si es una pantalla LED, sonido, ¿cómo se ve esa presencia remota?

    - Resp: Estamos considerando el uso de la pantalla led del arduino o anexar una pantalla LCD para la visualización de los datos, que en este caso son las pulsaciones por minuto

![Registro Discord 1](./imagenes/discord-1.png)

![Registro Discord 2](./imagenes/discord-2.png)

*Registro de Interacción en Discord*

-----

### Lunes 08 Junio

#### 2 Semanas para el examen

Proyecto de examen definido


###### Nombre Formal

Sistema IoT de monitoreo cardíaco en tiempo real

###### Objetivo

Diseñar un sistema capaz de capturar la actividad cardíaca de una persona mediante un sensor ECG AD8232, transmitir los datos a través de Internet utilizando Adafruit IO y visualizarlos remotamente en una pantalla LCD conectada a un segundo microcontrolador.

###### Funcionamiento

##### AD8232 → Arduino UNO R4 WiFi → Adafruit IO

##### Adafruit IO → Arduino UNO R4 WiFi → LCD 16x2

- El sensor AD8232 detecta la actividad eléctrica del corazón.

- El Arduino transmisor procesa la señal.

- Se calcula la frecuencia cardíaca en BPM.

- El dato se envía a Adafruit IO.

- Un segundo Arduino consulta la información.

- La pantalla LCD muestra los latidos por minuto en tiempo real.


### Pseudocódigo 

    INICIO

     Conectar Arduino transmisor a WiFi

     Conectar Arduino receptor a WiFi

     Mientras sistema esté activo

      - Leer señal ECG desde AD8232

      - Calcular BPM

      - Enviar BPM a Adafruit IO

    Fin Mientras

#### Arduino Receptor

    INICIO

     Conectar a WiFi

     Conectar a Adafruit IO

     Mientras sistema esté activo

      - Obtener BPM desde Adafruit IO

      - Mostrar BPM en LCD

    Fin Mientras

### Lista de materiales
    
2 Arduino UNO R4 WiFi

1 Sensor ECG AD8232

1 Pantalla LCD 16x2 con módulo I2C

Protoboard

Cables Dupont

2 Cable USB-C para Arduino

Red WiFi

Cuenta Adafruit IO

---- 

Mateo viene a nuestros puestos a consultar como va el avance de nuestro proyecto, le comentamos nuestra idea definida y le gusta, nos da la idea de hacer una carcasa para la opantalla donde se muestran los datos (BPM), y nos presta una Pantalla TFT LCD Redonda de 1,28", lo cual nos quedaría super con una carcasa, en forma de corazón, ya estamos trabajando en un modelo de impresión 3D e imprimir entre esta semana y la siguiente en el LID; Gracias Mateo!!

-----

### Nueva Lista de materiales
    
2 Arduino UNO R4 WiFi

1 Sensor ECG AD8232

Pantalla TFT LCD redonda de 1.28"

Protoboard

Cables Dupont

2 Cables USB-C para Arduino

Red WiFi

Cuenta Adafruit IO


### Martes 09 de Junio

![Compra Afel](./imagenes/compra-afel.gif)

*Compra de Sensor AD8282 en AFEL*


## Inicio de Trabajo con Sensor

### Lunes 15 Junio 

#### 1 Semana para el examen

Iniciamos en el LID, tenemos todos los materiales necesarios para poder trabajar, tenemos pendiente realizar el modelado 3D para la pantalla.

![titulo](./imagenes/conexiones-sensor-chat-gpt.png)

*Primeras conexiones del Sensor a Arduino sugeridas por ChatGPT*

Utilizamos estos Electrodos para realizar la conexión directamente entre el cuerpo de isipm --> Sensor ECG AD8232

![titulo](./imagenes/electrodos.jpeg)

*Electrodos*

Luego conectamos nuestra Pantalla TFT LCD redonda de 1.28" a una proto y luego el Sensor ECG AD8232 a otra proto y a la isipm.

![titulo](./imagenes/abdomen-isi.jpeg)

*Conexión del Sensor ECG AD8238 a abdomen de isi*

![titulo](./imagenes/clavicula-der-isi.jpeg)

*Conexión del Sensor ECG AD8238 a clavícula derecha de isi*

![titulo](./imagenes/clavicula-izq-isi.jpeg)

*Conexión del Sensor ECG AD8238 a clavícula izquierda de isi*

Entre varios intentos de códigos, llegamos a uno final para TRANSMISOR y RECEPTOR. (más adelante verán nuestro error)

---- 

Mateo y Aarón nos revisaron nuestro proyecto, nos comentaron que estaba bueno, solo que podíamos mejorar que la pantalla no refrescara.
Aún no hemos podido mejorar la pantalla (si está buena pero creemos que son los cables), además mejorar la calidad de la visualización de los datos. Estaremos informando...

---- 

![titulo](./imagenes/pantalla-letras-rojas.jpeg)

*Pantalla reflejando los datos pero con mala visualización (cambiar cables)*

![titulo](./imagenes/mateo-help.jpeg)

*Mateo ayudándonos en nuestro proyecto :) gracias Mateo!*

> CÓDIGO FALLIDO

```cpp
#include <WiFiS3.h>
#include "AdafruitIO_WiFi.h"

#include <Arduino_GFX_Library.h>

// ---------------- WIFI ----------------
#define WIFI_SSID "iPhone de Renata"
#define WIFI_PASS "arevalo1234"

// ---------------- ADAFRUIT ----------------
#define IO_USERNAME "arevalourra"
#define IO_KEY "TU_KEY"

// FEEDS
AdafruitIO_WiFi io(IO_USERNAME, IO_KEY, WIFI_SSID, WIFI_PASS);

AdafruitIO_Feed *bpmFeed =
  io.feed("examen-grupo04-bpm");

AdafruitIO_Feed *estadoFeed =
  io.feed("examen-grupo04-ecg");

// ---------------- PANTALLA GC9A01 ----------------

Arduino_DataBus *bus =
  new Arduino_HWSPI(
    9,    // DC
    10    // CS
  );

Arduino_GFX *gfx =
  new Arduino_GC9A01(
    bus,
    8,    // RESET
    0,    // rotación
    true
  );

// ---------------- VARIABLES ----------------

String bpm = "--";
String estado = "---";

void dibujarPantalla()
{
  gfx->fillScreen(0x0000);

  gfx->setTextColor(0xFFFF);

  gfx->setTextSize(2);
  gfx->setCursor(30, 40);
  gfx->println("ECG");

  gfx->setTextSize(4);
  gfx->setCursor(40, 90);
  gfx->println(bpm);

  gfx->setTextSize(2);
  gfx->setCursor(20, 170);
  gfx->println(estado);
}

// ---------- CALLBACK BPM ----------

void handleBPM(AdafruitIO_Data *data)
{
  bpm = data->toString();

  Serial.print("BPM recibido: ");
  Serial.println(bpm);

  dibujarPantalla();
}

// ---------- CALLBACK ESTADO ----------

void handleEstado(AdafruitIO_Data *data)
{
  estado = data->toString();

  Serial.print("Estado recibido: ");
  Serial.println(estado);

  dibujarPantalla();
}

void setup()
{
  Serial.begin(115200);

  gfx->begin();

  gfx->fillScreen(0x0000);

  gfx->setTextColor(0xFFFF);

  gfx->setTextSize(2);
  gfx->setCursor(20,120);
  gfx->println("Conectando...");

  Serial.println("Conectando Adafruit IO");

  io.connect();

  while(io.status() < AIO_CONNECTED)
  {
    Serial.print(".");
    delay(500);
  }

  Serial.println();
  Serial.println("Conectado!");

  bpmFeed->onMessage(handleBPM);
  estadoFeed->onMessage(handleEstado);

  bpmFeed->get();
  estadoFeed->get();

  dibujarPantalla();
}

void loop()
{
  io.run();
}
```

> CÓDIGO FALLIDO

```cpp
#include <WiFiS3.h>
#include "AdafruitIO_WiFi.h"

#include <Arduino_GFX_Library.h>

// ---------------- WIFI ----------------
#define WIFI_SSID "TU_WIFI"
#define WIFI_PASS "TU_CLAVE"

// ---------------- ADAFRUIT ----------------
#define IO_USERNAME "TU_USUARIO"
#define IO_KEY "TU_KEY"

// FEEDS
AdafruitIO_WiFi io(IO_USERNAME, IO_KEY, WIFI_SSID, WIFI_PASS);

AdafruitIO_Feed *bpmFeed =
  io.feed("examen-grupo04-bpm");

AdafruitIO_Feed *estadoFeed =
  io.feed("examen-grupo04-ecg");

// ---------------- PANTALLA GC9A01 ----------------

Arduino_DataBus *bus =
  new Arduino_HWSPI(
    9,    // DC
    10    // CS
  );

Arduino_GFX *gfx =
  new Arduino_GC9A01(
    bus,
    8,    // RESET
    0,    // rotación
    true
  );

// ---------------- VARIABLES ----------------

String bpm = "--";
String estado = "---";

void dibujarPantalla()
{
  gfx->fillScreen(0x0000);

  gfx->setTextColor(0xFFFF);

  gfx->setTextSize(2);
  gfx->setCursor(30, 40);
  gfx->println("ECG");

  gfx->setTextSize(4);
  gfx->setCursor(40, 90);
  gfx->println(bpm);

  gfx->setTextSize(2);
  gfx->setCursor(20, 170);
  gfx->println(estado);
}

// ---------- CALLBACK BPM ----------

void handleBPM(AdafruitIO_Data *data)
{
  bpm = data->toString();

  Serial.print("BPM recibido: ");
  Serial.println(bpm);

  dibujarPantalla();
}

// ---------- CALLBACK ESTADO ----------

void handleEstado(AdafruitIO_Data *data)
{
  estado = data->toString();

  Serial.print("Estado recibido: ");
  Serial.println(estado);

  dibujarPantalla();
}

void setup()
{
  Serial.begin(115200);

  gfx->begin();

  gfx->fillScreen(0x0000);

  gfx->setTextColor(0xFFFF);

  gfx->setTextSize(2);
  gfx->setCursor(20,120);
  gfx->println("Conectando...");

  Serial.println("Conectando Adafruit IO");

  io.connect();

  while(io.status() < AIO_CONNECTED)
  {
    Serial.print(".");
    delay(500);
  }

  Serial.println();
  Serial.println("Conectado!");

  bpmFeed->onMessage(handleBPM);
  estadoFeed->onMessage(handleEstado);

  bpmFeed->get();
  estadoFeed->get();

  dibujarPantalla();
}

void loop()
{
  io.run();
}
```

> Adjuntamos registro de nuestras conexiones realizadas el día Lunes, que estas despúes fueron cambiadas, ya que el día Miércoles nos dimos cuenta que los datos visualizados en Adafruit y Arduino eran datos aleatorios.

![titulo](./imagenes/conexiones-lunes.jpeg)

*Conexiones día Lunes*

> Tuvimos que considerar la compra de más parches, debido a su desgaste y la adherencia con el cuerpo, ya que sin unos parches nuevos, los datos no tomarían de buena forma.

![titulo](./imagenes/comprar-electrodos.png)

*Imagen electrodos sacada de https://rambal.com/biometricos/1238-electrodo-ecg.html*

![titulo](./imagenes/ilusas-oficial.jpeg)

*Ilusas creyendo con que los datos que se reflejaban eran reales*

### Miércoles 17 Junio 

### 5 días para el examen

El día de hoy realizamos denuevo la prueba para la pantalla y efectivamente eran los cables!!. El día anterior la Rena realizó la compra de estos cables, para así poder realizar la prueba nuevamente con la pantalla y comprobar nuestra teoría.

![titulo](./imagenes/cables-nuevos.jpeg)

*Nuevos cables*

Nos dimos cuenta que los datos que nos tiraba en el monitor serial de Arduino y en Adafruit eran solo datos aleatorios y no detectaba los pulsos reales... Tras varios intentos de nuevas pruebas con nuevos códigos no pudimos realizar que los pulsos fueran en tiempo real y de nosotras. (Por hoy nos rendimos, seguiremos en esta lucha)...

![titulo](./imagenes/frustradas-oficial.jpeg)

*Conexiones día Miércoles, probando nuevos cables*

![titulo](./imagenes/pantalla-funcionando.jpeg)

*Prueba pantalla con nuevos cables*

![titulo](./imagenes/pantalla-fondo-rojo.jpeg)

*Prueba pantalla con nuevos cables*

![titulo](./imagenes/intento-3-pantalla-tft.gif)

*Acá nos funcionó tanto la pantalla como el código, solo que este código despúes no lo utilizamos debido a los datos no reales*

![titulo](./imagenes/ilusas-pt2.jpeg)

*Foto riendo pero por dentro llorando*

> CÓDIGO DE PRUEBA PANTALLA TFT LCD redonda de 1.28"

- Utilizamos este código para probar la pantalla con los cables nuevos y si funcionó, reflejaba los colores respectivos.

```cpp
#include <Arduino_GFX_Library.h>

// Pines de control
#define TFT_DC   9
#define TFT_CS   10
#define TFT_RST  8

// Colores RGB565
#define TFT_BLACK   0x0000
#define TFT_BLUE    0x001F
#define TFT_RED     0xF800
#define TFT_GREEN   0x07E0
#define TFT_WHITE   0xFFFF
#define TFT_YELLOW  0xFFE0
#define TFT_CYAN    0x07FF
#define TFT_MAGENTA 0xF81F

// Configuración SPI por hardware
Arduino_DataBus *bus = new Arduino_HWSPI(
  TFT_DC,
  TFT_CS
);

// Configuración pantalla GC9A01
Arduino_GFX *gfx = new Arduino_GC9A01(
  bus,
  TFT_RST,
  0,      // Rotación (0-3)
  true    // IPS
);

void setup() {

  Serial.begin(115200);

  if (!gfx->begin()) {
    Serial.println("Error al iniciar la pantalla");
    while (1);
  }

  gfx->fillScreen(TFT_BLACK);

  gfx->setTextSize(2);
  gfx->setTextColor(TFT_WHITE);
  gfx->setCursor(45, 110);
  gfx->println("TEST RGB");

  delay(2000);
}

void loop() {

  mostrarColor(TFT_RED, "ROJO");
  mostrarColor(TFT_GREEN, "VERDE");
  mostrarColor(TFT_BLUE, "AZUL");
  mostrarColor(TFT_WHITE, "BLANCO");
  mostrarColor(TFT_YELLOW, "AMARILLO");
  mostrarColor(TFT_CYAN, "CIAN");
  mostrarColor(TFT_MAGENTA, "MAGENTA");
  mostrarColor(TFT_BLACK, "NEGRO");
}

void mostrarColor(uint16_t color, const char *texto) {

  gfx->fillScreen(color);

  if (color == TFT_BLACK) {
    gfx->setTextColor(TFT_WHITE);
  } else {
    gfx->setTextColor(TFT_BLACK);
  }

  gfx->setTextSize(3);

  int16_t x1, y1;
  uint16_t w, h;

  gfx->getTextBounds(
    texto,
    0,
    0,
    &x1,
    &y1,
    &w,
    &h
  );

  int16_t x = (240 - w) / 2;
  int16_t y = (240 - h) / 2;

  gfx->setCursor(x, y);
  gfx->println(texto);

  delay(2000);
}
```


### Viernes 19 de Junio 

### 3 días para el examen

El día de hoy tratamos de mejorar los códigos, tuvimos un tiempo corto para poder avanzar, debido a nuestro acotado tiempo entre clases. No pudimos mejorar el código...

**CÓDIGO TRANSMISOR**
```cpp
```

**CÓDIGO RECEPTOR**
```cpp
```

### DEMO EN VIDEO REPU-SS


