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

#define WIFI_SSID    "Jesu"
#define WIFI_PASS    "slay321"

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