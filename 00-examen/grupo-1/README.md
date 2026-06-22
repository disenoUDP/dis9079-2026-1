# grupo-1

- magdalenabalart
- jesumirandaa
- ccarlabelenn

El proyecto consiste en un altar lumínico compuesto por dos tótems conectados inalámbricamente entre sí, donde la presencia física de una persona se transforma en una señal luminosa, mecánica y afectiva. La interacción principal ocurre en el Tótem 01, construido como un altar vertical. En su base se encuentra resguardado el Arduino, mientras que en su estructura se integra un sensor ultrasónico capaz de medir la distancia entre el objeto y la persona que se aproxima.

A partir de esta medición, el sistema interpreta distintos rangos de cercanía. No se trata solamente de detectar si alguien está o no está frente al altar, sino de reconocer cómo se aproxima y si decide permanecer. Cuando una persona se acerca, el sensor ultrasónico registra la distancia y envía ese dato al Arduino, que lo traduce en una condición de intensidad lumínica. Mientras más cerca se encuentra la persona, mayor es la intensidad de la luz LED del tótem. De esta manera, la luz se enciende progresivamente, como si el altar despertara lentamente ante la presencia de alguien. Cuando la persona alcanza la distancia más cercana definida por el sistema, la luz llega a su 100%, indicando que la presencia fue sostenida y reconocida.

Si la persona se aleja antes de completar este proceso, la luz disminuye lentamente y no se activa la comunicación final. Esto permite que el sistema distinga entre una cercanía casual y un gesto de permanencia. Así, el funcionamiento técnico refuerza la dimensión ritual del proyecto: no basta con pasar frente al objeto, hay que quedarse el tiempo suficiente para que el altar responda.

Mientras esta interacción ocurre, el Tótem 01 envía información al Tótem 02. Este segundo tótem funciona como un receptor de la presencia detectada en el primero. Su estructura incorpora una pantalla LED y un servomotor. El movimiento del servo está vinculado a la distancia registrada por el sensor ultrasónico del Tótem 01: si la persona está lejos, pero comienza a acercarse, el servo se mueve de manera gradual, traduciendo esa aproximación en un gesto físico. Así, la distancia de una persona frente al primer altar se convierte en movimiento en el segundo tótem.

Cuando la persona llega a la condición de mayor cercanía y la luz del Tótem 01 alcanza su máxima intensidad, el sistema envía un mensaje al Tótem 02. Este mensaje aparece en la pantalla LED como una señal de compañía, indicando que alguien estuvo ahí, recordó o decidió hacerse presente. De esta forma, el segundo tótem no solo recibe datos técnicos, sino una huella simbólica de la interacción ocurrida en el primero.

Además, el proyecto incorpora una pregunta central: ¿qué pasa si el altar no solo responde a quien se acerca, sino también a la ausencia de alguien? Desde esta idea, el sistema puede contemplar una segunda condición: si durante un periodo prolongado nadie se aproxima al altar, la luz puede encenderse por sí sola de manera tenue o intermitente, como una presencia fantasma. Esta activación no representaría una visita física, sino la memoria de una ausencia. En ese caso, el mensaje enviado al Tótem 02 sería distinto, no como señal de compañía presente, sino como una alusión a alguien que falta, que no ha llegado o que sigue habitando el espacio desde la distancia.

## RECOMENDACIONES

1. Separar la descripción textual en varias secciones. Por ejemplo primero solamente conceptual, luego otra técnica que explique cómo los conceptos se implementan.
2. Complementar con diagramas de flujo o dibujos
3. Escribir el pseudocódigo

## Lista de compras y materiales
 
| Elemento | Función dentro de la interacción | Precio |
|---|---|---|
| Arduino | Controla el funcionamiento del Tótem 01 y procesa la información del sensor. | |
| Raspberry Pi Pico | Permite la conexión inalámbrica y el envío/recepción de datos entre tótems. | |
| Sensor ultrasónico | Detecta la distancia entre la persona y el Tótem 01. | |
| LED | Se enciende progresivamente según la cercanía de la persona. | |
| Protoboard mini | Permite conectar y organizar los componentes electrónicos. | |
| Cables Dupont mix | Conectan los sensores, LED, servo, pantalla y placas. | |
| Cable USB-C | Permite alimentar o conectar el Arduino y la Raspberry Pi Pico. | |
| Servo | Imita físicamente la distancia detectada por el sensor. | |
| Pantalla OLED | Muestra los mensajes recibidos desde el Tótem 01. | |

# Pseudocódigo

### Tótem 01
```
INICIO

Definir sensor ultrasónico
Definir LED
Definir conexión inalámbrica con Tótem 02

Definir distancia_lejana = mayor a 100 cm
Definir distancia_media = entre 70 cm y 100 cm
Definir distancia_cercana = entre 40 cm y 70 cm
Definir distancia_muy_cercana = menor a 40 cm

Definir intensidad_LED = 0%

MIENTRAS el sistema esté encendido:

Medir distancia de la persona con el sensor ultrasónico

SI la distancia es mayor a 100 cm:
    La persona está lejos
    LED apagado o con intensidad mínima
    intensidad_LED = 0%
    Enviar al Tótem 02: "sin presencia cercana"

SI la distancia está entre 70 cm y 100 cm:
    La persona comienza a acercarse
    LED se enciende suavemente
    intensidad_LED = 25%
    Enviar al Tótem 02: "presencia lejana"

SI la distancia está entre 40 cm y 70 cm:
    La persona está cerca del altar
    LED aumenta su intensidad
    intensidad_LED = 60%
    Enviar al Tótem 02: "presencia cercana"

SI la distancia es menor a 40 cm:
    La persona está muy cerca del altar
    LED alcanza su máxima intensidad
    intensidad_LED = 100%
    Enviar al Tótem 02: "presencia reconocida / alguien está aquí"

Actualizar intensidad del LED según el valor definido

Esperar un momento breve antes de volver a medir

FIN
```

### Tótem 02 

```
INICIO

Definir pantalla LED
Definir servomotor
Definir conexión inalámbrica con Tótem 01

Definir posición_servo = 0 grados

MIENTRAS el sistema esté encendido:

Esperar información enviada desde el Tótem 01

Recibir dato de distancia o condición de cercanía

SI el mensaje recibido es "sin presencia cercana":
    Mostrar en pantalla: "Sin presencia"
    Mover servo a 0 grados
    posición_servo = 0 grados

SI el mensaje recibido es "presencia lejana":
    Mostrar en pantalla: "Alguien se aproxima"
    Mover servo a 45 grados
    posición_servo = 45 grados

SI el mensaje recibido es "presencia cercana":
    Mostrar en pantalla: "Presencia cerca"
    Mover servo a 90 grados
    posición_servo = 90 grados

SI el mensaje recibido es "presencia reconocida":
    Mostrar en pantalla: "Estoy aquí"
    Mover servo a 180 grados
    posición_servo = 180 grados

Esperar un momento breve antes de volver a recibir información

FIN
```

# Códigos 

## Tótem 01 

### Qué necesitábamos lograr con el código

El objetivo principal era construir un sistema de dos tótems conectados. El **Tótem 01** debía detectar la cercanía de una persona usando un sensor ultrasónico, traducir esa distancia en estados simples, activar un LED según la condición detectada y enviar esa información a Adafruit IO. El Tótem 02 debía recibir esa información desde Adafruit y mostrar el mensaje correspondiente en una pantalla OLED. 

Al principio se pensó que el Tótem 02 también tendría un servo, pero después decidimos retirarlo porque su movimiento agregaba ruido visual y mecánico. Como el proyecto buscaba una respuesta más limpia, silenciosa y contemplativa, **se prefirió dejar solamente el mensaje en pantalla.** 

### Componentes considerados

 <ins> Para el Tótem 01, trabajamos con: </ins>
| Elemento | Función dentro del proyecto |
|---|---|
| Sensor ultrasónico HC-SR04 | Detecta la distancia o cercanía de la persona frente al tótem. |
| LED | Genera una respuesta lumínica según el estado detectado. |
| Botón demo | Permite activar manualmente los estados del sistema para la presentación. |
| Arduino con WiFi | Controla el sistema y permite enviar/recibir datos por internet. |
| Adafruit IO | Plataforma que conecta el Tótem 01 con el Tótem 02 mediante envío de datos. |


 <ins> La conexión principal quedó pensada así: </ins>

| Conexión | Pin |
|---|---|
| Sensor trig | Pin 2 |
| Sensor echo | Pin 3 |
| LED | Pin 6 |
| Botón positivo | Pin 7 |
| Botón señal | Pin 4 |
| Botón GND | GND |

 <ins> Lógica de estados </ins>

Pedimos que el sensor no enviara las distancias crudas todo el tiempo, porque eso generaba demasiada información. Por eso se transformaron las lecturas en códigos simples: 

**0** = sin presencia  
**1** = distancia 01  
**2** = distancia 02  
**3** = distancia 03  
**4** = ausencia prolongada   

 <ins> Los rangos finales quedaron así: </ins>

**100 cm o más** = sin presencia  
**70 a 99 cm** = distancia 01  
**40 a 69 cm** = distancia 02  
**menos de 40 cm** = distancia 03   

También consideramos que el sensor era sensible, por lo que estas distancias tenían que ser muy específicas. Por eso se planteó marcar el suelo con un recorrido o zonas de distancia, para que la interacción fuera más clara y limpia. 


### Funciones principales del código

| Función | Descripción |
|---|---|
| `setup()` | Prepara todo al iniciar el sistema. Configura los pines del sensor, LED y botón, inicia el monitor serial, apaga el LED, reinicia el promedio del sensor y llama a la conexión con Adafruit IO. |
| `loop()` | Es el corazón del sistema. Mantiene viva la conexión con Adafruit, lee el botón, toma lecturas del sensor si no está en modo demo, actualiza el mensaje, envía datos si cambió el estado y controla el comportamiento del LED. |
| `conectarAdafruit()` | Conecta el Arduino a Adafruit IO. Tiene un límite de espera para que el código no quede pegado si internet falla. Si conecta, el sistema puede enviar datos; si no conecta, sigue funcionando localmente con sensor, botón y LED. |
| `medirDistanciaSimple()` | Activa el sensor ultrasónico y calcula la distancia en centímetros. Si no recibe una lectura válida, devuelve `-1`. |
| `registrarLectura()` | Guarda cada lectura del sensor dentro de una lista de muestras. Solo acepta valores razonables, entre 2 y 300 cm, para evitar datos raros. |
| `calcularPromedioDistancia()` | Calcula el promedio de varias lecturas del sensor. Esto ayuda a estabilizar la respuesta, ya que el sensor puede ser sensible y saltar entre valores. |
| `reiniciarPromedioSensor()` | Limpia las muestras anteriores del sensor. Sirve especialmente cuando se vuelve desde el modo demo al modo sensor real. |
| `decodificarDistancia()` | Convierte la distancia medida en uno de los códigos del sistema. Por ejemplo, si la distancia está entre 70 y 99 cm, la transforma en `distancia 01`; si es menor a 40 cm, la transforma en `distancia 03`. |
| `confirmarEstadoSensor()` | Evita que el sistema cambie de estado demasiado rápido. El código espera a que la condición se mantenga durante un pequeño tiempo antes de aceptar el cambio. |
| `actualizarMensaje()` | Asocia cada código con un mensaje textual: `0 = Sin presencia`, `1 = Distancia 01`, `2 = Distancia 02`, `3 = Distancia 03`, `4 = Ausencia prolongada`. Esto sirve para imprimir el estado en el monitor serial y para que el Tótem 02 pueda mostrar mensajes claros. |
| `actualizarAusencia()` | Detecta si el sistema lleva mucho tiempo sin presencia. Si pasan 2 minutos sin detectar a alguien, el estado cambia a `ausencia prolongada`. |
| `leerBoton()` | Lee el botón demo y usa debounce, evitando que una sola presión se lea muchas veces por error. |
| `avanzarModoBoton()` | Permite recorrer manualmente los estados del sistema sin usar el sensor. La secuencia es: primera presión = distancia 01, segunda presión = distancia 02, tercera presión = distancia 03, cuarta presión = ausencia prolongada y quinta presión = vuelve al sensor. |
| `reiniciarValoresDemo()` | Limpia variables internas cada vez que se activa un estado desde el botón, para que el modo demo no se mezcle con lecturas anteriores del sensor. |
| `enviarEstadoSiCambio()` | Envía información solo cuando el estado cambia. Esto evita mandar miles de datos a Adafruit IO. En vez de enviar todo el tiempo la distancia exacta, solo se envía el código actual. |
| `controlarLed()` | Controla el comportamiento del LED según el estado actual: sin presencia = LED apagado, distancia 01 = titileo lento, distancia 02 = titileo más rápido, distancia 03 = LED fijo y ausencia prolongada = encendido progresivo. |
| `latirLed()` | Genera el efecto de titileo o latido del LED para las primeras distancias. La distancia 01 tiene un latido más lento y la distancia 02 uno más rápido. |
| `encendidoProgresivoAusencia()` | Genera el fade de ausencia prolongada. El LED no se prende de golpe, sino que sube progresivamente hasta llegar al brillo máximo en 10 segundos. |


Decisiones importantes que tomamos

También fuimos ajustando varias cosas durante la construcción:


-No enviar lecturas crudas del sensor.  
-Enviar solo códigos simples a Adafruit IO.   
-Usar promedio para estabilizar el sensor.  
-Usar confirmación temporal antes de cambiar de estado.  
-Agregar botón demo para el examen.  
-Hacer que el LED tenga respuestas distintas según la cercanía.  
-Hacer que la ausencia prolongada tenga un fade de 10 segundos.  
-Evitar que Adafruit bloquee el código si no hay internet.  
-Retirar el servo del Tótem 02 para dejar una respuesta más limpia.  
-Usar pantalla OLED como respuesta principal del segundo tótem.  

### Prompts utilizados para el desarrollo del código del Tótem 01

Durante el desarrollo del código del **Tótem 01**, se trabajó con ChatGPT mediante una serie de prompts orientados a construir, probar y ajustar progresivamente el funcionamiento del sistema. Estos prompts permitieron organizar el proceso por etapas, desde la lectura del sensor ultrasónico hasta la integración de respuestas lumínicas mediante LED.


### Prompts de trabajo utilizados

| Etapa / área de trabajo | Prompt utilizado |
|---|---|
| Lectura inicial del sensor | “Generar un código base en Arduino para leer un sensor ultrasónico HC-SR04, utilizando TRIG en el pin 2 y ECHO en el pin 3, e imprimir la distancia medida en centímetros a través del monitor serial.” |
| Clasificación de presencia | “Modificar el código del sensor ultrasónico para clasificar la distancia detectada en distintos estados de presencia, considerando rangos específicos de proximidad frente al tótem.” |
| Uso de `millis()` | “Ajustar el código para evitar el uso de `delay()` y reemplazarlo por `millis()`, con el objetivo de mantener una lectura fluida del sensor sin bloquear el funcionamiento general del sistema.” |
| Respuesta inmediata | “Optimizar la lectura del sensor para que el cambio de estado se actualice de manera inmediata, evitando tiempos de espera excesivos que puedan afectar la interacción del tótem.” |
| Incorporación del LED | “Incorporar un LED como salida visual del sistema, conectado a un pin PWM, para que responda según los distintos estados de distancia detectados por el sensor.” |
| Exploración lumínica | “Evaluar distintas formas de respuesta lumínica para representar la proximidad de una persona, considerando inicialmente porcentajes de intensidad y luego una lógica basada en parpadeos diferenciados.” |
| Primeros rangos de distancia | “Reformular las condiciones de distancia en tres estados principales: presencia lejana a 230 cm, acercamiento a 150 cm y presencia cercana a 50 cm.” |
| Parpadeo según cercanía | “Programar el LED para que parpadee lentamente cuando la persona esté lejos, a una velocidad media cuando se acerque y permanezca encendido de forma fija cuando esté cerca del tótem.” |
| Ausencia prolongada | “Agregar una condición de ausencia prolongada para que, si no se detecta presencia durante 2 minutos, el LED comience a encenderse progresivamente de manera lenta.” |
| Organización del código | “Mantener el código organizado por funciones, separando la lectura del sensor, la clasificación de estados y el control del LED, para facilitar futuras modificaciones e integración con Adafruit IO.” |
| Preparación para conexión inalámbrica | “Preparar la lógica del código para una futura conexión inalámbrica con el Tótem 02, considerando el envío de estados simplificados en lugar de lecturas numéricas constantes.” |
| Decodificación para Adafruit IO | “Proponer una estructura de decodificación para Adafruit IO, donde cada estado del sensor sea enviado como un valor resumido, evitando saturar la plataforma con datos innecesarios.” |
| Ajuste final de rangos | “Ajustar los rangos de distancia del sensor para trabajar con una escala más precisa: sin presencia sobre 100 cm, distancia 01 entre 70 y 99 cm, distancia 02 entre 40 y 69 cm, y distancia 03 bajo 40 cm.” |
| Códigos de estado | “Modificar la lógica del sensor para que las lecturas no se envíen en centímetros directamente, sino que se transformen en códigos simples del 0 al 4 según el estado de presencia detectado.” |
| Promedio de lecturas | “Implementar un promedio de lecturas del sensor ultrasónico para estabilizar la medición y evitar que el sistema cambie de estado por una lectura aislada o errática.” |
| Validación de muestras | “Agregar una cantidad mínima de muestras válidas antes de aceptar una distancia como correcta, considerando que el sensor puede ser sensible a objetos cercanos o variaciones del entorno.” |
| Confirmación temporal | “Incorporar una confirmación temporal del estado detectado para que el sistema solo cambie de condición cuando la lectura se mantenga durante un breve periodo.” |
| Mantener ausencia prolongada | “Modificar el código para que, en caso de ausencia prolongada, el estado no vuelva inmediatamente a sin presencia, sino que mantenga la condición de ausencia hasta que vuelva a detectarse cercanía.” |
| Botón demo | “Agregar un botón demo conectado al sistema para poder activar manualmente los estados del tótem durante la presentación, sin depender únicamente de la lectura del sensor.” |
| Secuencia del botón | “Programar el botón demo para que cada presión avance por una secuencia de estados: distancia 01, distancia 02, distancia 03, ausencia prolongada y retorno al modo sensor.” |
| Modo demo | “Configurar el modo demo para que, mientras esté activo, el sensor ultrasónico quede temporalmente desactivado y no interfiera con la demostración manual.” |
| Debounce del botón | “Agregar debounce al botón para evitar que una sola presión sea leída varias veces por error.” |
| Retorno al modo sensor | “Reiniciar los valores del sensor y del promedio cuando el sistema vuelve desde el modo demo al modo sensor, evitando que queden lecturas anteriores afectando el funcionamiento.” |
| Mensajes por estado | “Asignar un mensaje textual a cada código del sistema, de manera que cada estado pueda ser identificado claramente en el monitor serial y enviado como lógica para el Tótem 02.” |
| Comportamiento final del LED | “Ajustar el comportamiento del LED para que la distancia 01 tenga un latido lento, la distancia 02 un latido más rápido, la distancia 03 quede encendida fija y la ausencia prolongada active un encendido progresivo.” |
| Fade de ausencia | “Modificar el fade de ausencia prolongada para que el LED aumente su brillo de forma progresiva durante 10 segundos hasta llegar al máximo.” |
| Integración con Adafruit IO | “Integrar Adafruit IO al código del Tótem 01 para enviar el código del estado actual al feed correspondiente.” |
| Envío solo por cambio | “Configurar el envío a Adafruit IO para que solo ocurra cuando el estado cambia, evitando mandar datos repetidos o saturar la plataforma.” |
| Conexión no bloqueante | “Agregar una conexión a Adafruit IO con tiempo máximo de espera, para que el código no quede bloqueado si falla la conexión a internet.” |
| Funcionamiento local | “Mantener el funcionamiento local del sensor, botón y LED aunque Adafruit IO no logre conectarse, permitiendo seguir probando el tótem sin depender completamente de internet.” |
| Código modular | “Organizar el código en funciones separadas para facilitar su lectura, modificación y explicación: lectura del sensor, promedio, clasificación de distancia, botón demo, control del LED, ausencia prolongada y envío a Adafruit IO.” |
| Tótem 01 como emisor | “Preparar el código para que el Tótem 01 funcione como dispositivo emisor, enviando estados simplificados al Tótem 02 a través de Adafruit IO.” |


### Código tótem 01


```cpp
// -----------------------------
// SENSOR ULTRASÓNICO HC-SR04 + LED
// Sensor con promedio de lecturas
// Modo demo mediante botón
// Envío de datos a Adafruit IO
//
// Botón:
// positivo → pin 7
// señal    → pin 4
// GND      → GND
//
// Códigos:
// 0 = sin presencia
// 1 = distancia 01
// 2 = distancia 02
// 3 = distancia 03
// 4 = ausencia prolongada
// -----------------------------

#include "AdafruitIO_WiFi.h"

// -----------------------------
// DATOS ADAFRUIT IO
// -----------------------------

#define IO_USERNAME  "Magdalena"
#define IO_KEY       ""

#define WIFI_SSID    "internetmagdalena"
#define WIFI_PASS    "Magdita12345"

AdafruitIO_WiFi io(IO_USERNAME, IO_KEY, WIFI_SSID, WIFI_PASS);

// Este feed debe ser el mismo que escucha Arduino 02
AdafruitIO_Feed *estadoFeed = io.feed("TOTEM01");

bool adafruitConectado = false;

// -----------------------------
// PINES
// -----------------------------

const int trigPin = 2;
const int echoPin = 3;
const int ledPin = 6;

const int botonVccPin = 7;
const int botonPin = 4;

long duracion;
float distancia = -1;

// -----------------------------
// CÓDIGOS
// -----------------------------

const int COD_SIN_PRESENCIA = 0;
const int COD_DISTANCIA_01 = 1;
const int COD_DISTANCIA_02 = 2;
const int COD_DISTANCIA_03 = 3;
const int COD_AUSENCIA = 4;

int codigoActual = -1;
int codigoAnterior = -2;

String estadoActual = "";
String mensajeActual = "";

// -----------------------------
// CONTROL DEL SENSOR
// -----------------------------

unsigned long tiempoAnteriorSensor = 0;
const unsigned long intervaloSensor = 100;

// -----------------------------
// PROMEDIO DE LECTURAS
// -----------------------------

const int CANTIDAD_MUESTRAS = 6;
const int MINIMO_MUESTRAS_VALIDAS = 3;

float muestrasDistancia[CANTIDAD_MUESTRAS];

int indiceMuestra = 0;
int muestrasRegistradas = 0;

// -----------------------------
// CONFIRMACIÓN DEL ESTADO
// -----------------------------

int codigoCandidato = -1;
String estadoCandidato = "";

unsigned long tiempoInicioCandidato = 0;

const unsigned long tiempoConfirmacionEstado = 400;

// -----------------------------
// CONTROL DE ENVÍO / MONITOR SERIAL
// -----------------------------

unsigned long tiempoUltimoEnvio = 0;

// -----------------------------
// AUSENCIA PROLONGADA
// -----------------------------

unsigned long tiempoInicioSinPresencia = 0;
bool contandoAusencia = false;

const unsigned long tiempoAusencia = 120000;
// 120000 ms = 2 minutos
// Para probar rápidamente: 10000 ms = 10 segundos

// -----------------------------
// CONTROL DEL LED
// -----------------------------

unsigned long tiempoInicioLatido = 0;
int codigoLedAnterior = -99;

const unsigned long duracionPulso = 180;

const unsigned long latidoDistancia01 = 1800;
const unsigned long latidoDistancia02 = 850;

const int brilloDistancia01 = 80;
const int brilloDistancia02 = 180;
const int brilloDistancia03 = 255;

// -----------------------------
// FADE DE AUSENCIA
// -----------------------------

unsigned long tiempoInicioFade = 0;

const unsigned long duracionFadeAusencia = 10000;
// 10000 ms = 10 segundos

int brilloAusencia = 0;

// -----------------------------
// CONTROL DEL BOTÓN DEMO
// -----------------------------

bool modoDemoActivo = false;
int pasoBoton = 0;

bool ultimaLecturaBoton = LOW;
bool estadoEstableBoton = LOW;

unsigned long tiempoUltimoRebote = 0;
const unsigned long tiempoRebote = 50;

// -----------------------------
// SETUP
// -----------------------------

void setup() {
  Serial.begin(9600);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(ledPin, OUTPUT);

  pinMode(botonVccPin, OUTPUT);
  digitalWrite(botonVccPin, HIGH);

  pinMode(botonPin, INPUT);

  analogWrite(ledPin, 0);

  reiniciarPromedioSensor();

  Serial.println("Sistema iniciado");
  Serial.println("-------------------------");

  conectarAdafruit();
}

// -----------------------------
// LOOP
// -----------------------------

void loop() {
  unsigned long tiempoActual = millis();

  // Mantiene activa la conexión con Adafruit IO
  // solo si logró conectarse.
  if (adafruitConectado) {
    io.run();
  }

  leerBoton(tiempoActual);

  if (!modoDemoActivo) {
    if (tiempoActual - tiempoAnteriorSensor >= intervaloSensor) {
      tiempoAnteriorSensor = tiempoActual;

      float lecturaActual = medirDistanciaSimple();

      registrarLectura(lecturaActual);

      distancia = calcularPromedioDistancia();

      int codigoDetectado;
      String estadoDetectado;

      decodificarDistancia(
        distancia,
        codigoDetectado,
        estadoDetectado
      );

      confirmarEstadoSensor(
        codigoDetectado,
        estadoDetectado,
        tiempoActual
      );

      actualizarAusencia(tiempoActual);
    }
  }

  actualizarMensaje();

  enviarEstadoSiCambio(tiempoActual);

  controlarLed(tiempoActual);
}

// -----------------------------
// CONECTAR A ADAFRUIT IO
// SIN BLOQUEAR PARA SIEMPRE
// -----------------------------

void conectarAdafruit() {
  Serial.print("Conectando a Adafruit IO");

  io.connect();

  unsigned long inicioConexion = millis();
  const unsigned long tiempoMaximoConexion = 15000;
  // Espera máximo 15 segundos

  while (
    io.status() < AIO_CONNECTED &&
    millis() - inicioConexion < tiempoMaximoConexion
  ) {
    Serial.print(".");
    delay(500);
  }

  Serial.println();

  if (io.status() >= AIO_CONNECTED) {
    adafruitConectado = true;
    Serial.println("Conectado a Adafruit IO");
  } else {
    adafruitConectado = false;
    Serial.println("No conecto a Adafruit IO");
    Serial.println("El sistema seguira funcionando sin enviar datos");
  }

  Serial.println("-------------------------");
}

// -----------------------------
// MEDICIÓN SIMPLE DEL SENSOR
// -----------------------------

float medirDistanciaSimple() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duracion = pulseIn(echoPin, HIGH, 30000);

  if (duracion == 0) {
    return -1;
  }

  float distanciaCalculada = duracion * 0.034 / 2;

  return distanciaCalculada;
}

// -----------------------------
// REGISTRAR LECTURA EN EL PROMEDIO
// -----------------------------

void registrarLectura(float nuevaLectura) {
  if (nuevaLectura >= 2 && nuevaLectura <= 300) {
    muestrasDistancia[indiceMuestra] = nuevaLectura;
  } else {
    muestrasDistancia[indiceMuestra] = -1;
  }

  indiceMuestra++;

  if (indiceMuestra >= CANTIDAD_MUESTRAS) {
    indiceMuestra = 0;
  }

  if (muestrasRegistradas < CANTIDAD_MUESTRAS) {
    muestrasRegistradas++;
  }
}

// -----------------------------
// CALCULAR PROMEDIO
// -----------------------------

float calcularPromedioDistancia() {
  float sumaDistancias = 0;
  int cantidadValidas = 0;

  for (int i = 0; i < muestrasRegistradas; i++) {
    if (muestrasDistancia[i] >= 2) {
      sumaDistancias += muestrasDistancia[i];
      cantidadValidas++;
    }
  }

  if (cantidadValidas < MINIMO_MUESTRAS_VALIDAS) {
    return -1;
  }

  return sumaDistancias / cantidadValidas;
}

// -----------------------------
// REINICIAR PROMEDIO
// -----------------------------

void reiniciarPromedioSensor() {
  for (int i = 0; i < CANTIDAD_MUESTRAS; i++) {
    muestrasDistancia[i] = -1;
  }

  indiceMuestra = 0;
  muestrasRegistradas = 0;
  distancia = -1;
}

// -----------------------------
// DECODIFICAR EL PROMEDIO
// -----------------------------

void decodificarDistancia(
  float d,
  int &codigoDetectado,
  String &estadoDetectado
) {
  if (d < 0 || d >= 100) {
    estadoDetectado = "sin presencia";
    codigoDetectado = COD_SIN_PRESENCIA;
  }

  else if (d >= 70) {
    estadoDetectado = "distancia 01";
    codigoDetectado = COD_DISTANCIA_01;
  }

  else if (d >= 40) {
    estadoDetectado = "distancia 02";
    codigoDetectado = COD_DISTANCIA_02;
  }

  else {
    estadoDetectado = "distancia 03";
    codigoDetectado = COD_DISTANCIA_03;
  }
}

// -----------------------------
// CONFIRMAR ESTADO DEL SENSOR
// -----------------------------

void confirmarEstadoSensor(
  int codigoDetectado,
  String estadoDetectado,
  unsigned long tiempoActual
) {
  if (codigoDetectado != codigoCandidato) {
    codigoCandidato = codigoDetectado;
    estadoCandidato = estadoDetectado;
    tiempoInicioCandidato = tiempoActual;
  }

  if (
    codigoActual == COD_AUSENCIA &&
    codigoCandidato == COD_SIN_PRESENCIA
  ) {
    return;
  }

  if (
    tiempoActual - tiempoInicioCandidato >=
    tiempoConfirmacionEstado
  ) {
    if (codigoActual != codigoCandidato) {
      codigoActual = codigoCandidato;
      estadoActual = estadoCandidato;
    }
  }
}

// -----------------------------
// ACTUALIZAR MENSAJE
// -----------------------------

void actualizarMensaje() {
  if (codigoActual == COD_SIN_PRESENCIA) {
    mensajeActual = "Sin presencia";
  }

  else if (codigoActual == COD_DISTANCIA_01) {
    mensajeActual = "Distancia 01";
  }

  else if (codigoActual == COD_DISTANCIA_02) {
    mensajeActual = "Distancia 02";
  }

  else if (codigoActual == COD_DISTANCIA_03) {
    mensajeActual = "Distancia 03";
  }

  else if (codigoActual == COD_AUSENCIA) {
    mensajeActual = "Ausencia prolongada";
  }

  else {
    mensajeActual = "Esperando lectura";
  }
}

// -----------------------------
// CONTROL DE AUSENCIA PROLONGADA
// -----------------------------

void actualizarAusencia(unsigned long tiempoActual) {
  bool sinPresencia =
    codigoActual == COD_SIN_PRESENCIA;

  bool hayPresencia =
    codigoActual == COD_DISTANCIA_01 ||
    codigoActual == COD_DISTANCIA_02 ||
    codigoActual == COD_DISTANCIA_03;

  if (sinPresencia) {
    if (!contandoAusencia) {
      contandoAusencia = true;
      tiempoInicioSinPresencia = tiempoActual;
    }

    if (
      tiempoActual - tiempoInicioSinPresencia >=
      tiempoAusencia
    ) {
      estadoActual = "ausencia prolongada";
      codigoActual = COD_AUSENCIA;
    }
  }

  if (hayPresencia) {
    contandoAusencia = false;
    brilloAusencia = 0;
  }
}

// -----------------------------
// LEER BOTÓN CON DEBOUNCE
// -----------------------------

void leerBoton(unsigned long tiempoActual) {
  bool lecturaBoton = digitalRead(botonPin);

  if (lecturaBoton != ultimaLecturaBoton) {
    tiempoUltimoRebote = tiempoActual;
  }

  if (
    tiempoActual - tiempoUltimoRebote >
    tiempoRebote
  ) {
    if (lecturaBoton != estadoEstableBoton) {
      estadoEstableBoton = lecturaBoton;

      if (estadoEstableBoton == HIGH) {
        avanzarModoBoton();
      }
    }
  }

  ultimaLecturaBoton = lecturaBoton;
}

// -----------------------------
// CICLO DEL BOTÓN
// -----------------------------

void avanzarModoBoton() {
  pasoBoton++;

  if (pasoBoton == 1) {
    modoDemoActivo = true;

    estadoActual = "distancia 01";
    codigoActual = COD_DISTANCIA_01;

    reiniciarValoresDemo();

    Serial.println("Boton: modo demo distancia 01");
  }

  else if (pasoBoton == 2) {
    modoDemoActivo = true;

    estadoActual = "distancia 02";
    codigoActual = COD_DISTANCIA_02;

    reiniciarValoresDemo();

    Serial.println("Boton: modo demo distancia 02");
  }

  else if (pasoBoton == 3) {
    modoDemoActivo = true;

    estadoActual = "distancia 03";
    codigoActual = COD_DISTANCIA_03;

    reiniciarValoresDemo();

    Serial.println("Boton: modo demo distancia 03");
  }

  else if (pasoBoton == 4) {
    modoDemoActivo = true;

    estadoActual = "ausencia prolongada";
    codigoActual = COD_AUSENCIA;

    reiniciarValoresDemo();

    Serial.println("Boton: modo demo ausencia prolongada");
  }

  else if (pasoBoton == 5) {
    modoDemoActivo = false;
    pasoBoton = 0;

    contandoAusencia = false;
    brilloAusencia = 0;

    codigoActual = COD_SIN_PRESENCIA;
    estadoActual = "sin presencia";

    codigoAnterior = -2;
    codigoLedAnterior = -99;

    codigoCandidato = -1;
    estadoCandidato = "";
    tiempoInicioCandidato = 0;

    reiniciarPromedioSensor();

    Serial.println("Boton: vuelve a funcionar con sensor");
    Serial.println("-------------------------");
  }
}

// -----------------------------
// REINICIAR VALORES DEL MODO DEMO
// -----------------------------

void reiniciarValoresDemo() {
  contandoAusencia = false;
  brilloAusencia = 0;

  codigoCandidato = -1;
  estadoCandidato = "";
  tiempoInicioCandidato = 0;
}

// -----------------------------
// ENVIAR / IMPRIMIR SOLO CUANDO CAMBIA
// -----------------------------

void enviarEstadoSiCambio(unsigned long tiempoActual) {
  if (
    codigoActual != codigoAnterior &&
    codigoActual != -1
  ) {
    Serial.print("Estado actual: ");
    Serial.println(estadoActual);

    Serial.print("Mensaje: ");
    Serial.println(mensajeActual);

    if (!modoDemoActivo) {
      Serial.print("Promedio de distancia: ");

      if (distancia >= 0) {
        Serial.print(distancia);
        Serial.println(" cm");
      } else {
        Serial.println("sin lectura valida");
      }
    } else {
      Serial.println("Activado mediante boton demo");
    }

    Serial.print("Codigo enviado a Adafruit IO: ");
    Serial.println(codigoActual);

    if (adafruitConectado) {
      estadoFeed->save(codigoActual);
      Serial.println("Enviado a Adafruit IO");
    } else {
      Serial.println("No se envio a Adafruit IO porque no esta conectado");
    }

    Serial.println("-------------------------");

    codigoAnterior = codigoActual;
    tiempoUltimoEnvio = tiempoActual;
  }
}

// -----------------------------
// CONTROL DEL LED
// -----------------------------

void controlarLed(unsigned long tiempoActual) {
  if (codigoActual != codigoLedAnterior) {
    tiempoInicioLatido = tiempoActual;

    if (codigoActual == COD_AUSENCIA) {
      brilloAusencia = 0;
      tiempoInicioFade = tiempoActual;
    }

    analogWrite(ledPin, 0);

    codigoLedAnterior = codigoActual;
  }

  if (codigoActual == COD_SIN_PRESENCIA) {
    analogWrite(ledPin, 0);
  }

  else if (codigoActual == COD_DISTANCIA_01) {
    latirLed(
      tiempoActual,
      latidoDistancia01,
      brilloDistancia01
    );
  }

  else if (codigoActual == COD_DISTANCIA_02) {
    latirLed(
      tiempoActual,
      latidoDistancia02,
      brilloDistancia02
    );
  }

  else if (codigoActual == COD_DISTANCIA_03) {
    analogWrite(ledPin, brilloDistancia03);
  }

  else if (codigoActual == COD_AUSENCIA) {
    encendidoProgresivoAusencia(tiempoActual);
  }
}

// -----------------------------
// LATIDO DEL LED
// -----------------------------

void latirLed(
  unsigned long tiempoActual,
  unsigned long intervaloLatido,
  int brillo
) {
  unsigned long tiempoDentroDelLatido =
    tiempoActual - tiempoInicioLatido;

  if (tiempoDentroDelLatido >= intervaloLatido) {
    tiempoInicioLatido = tiempoActual;
    tiempoDentroDelLatido = 0;
  }

  if (tiempoDentroDelLatido < duracionPulso) {
    analogWrite(ledPin, brillo);
  } else {
    analogWrite(ledPin, 0);
  }
}

// -----------------------------
// FADE POR AUSENCIA PROLONGADA
// Llega al brillo máximo en 10 segundos
// -----------------------------

void encendidoProgresivoAusencia(
  unsigned long tiempoActual
) {
  unsigned long tiempoTranscurrido =
    tiempoActual - tiempoInicioFade;

  if (tiempoTranscurrido >= duracionFadeAusencia) {
    brilloAusencia = 255;
  } else {
    brilloAusencia = map(
      tiempoTranscurrido,
      0,
      duracionFadeAusencia,
      0,
      255
    );
  }

  analogWrite(ledPin, brilloAusencia);
}
```
