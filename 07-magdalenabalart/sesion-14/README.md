# sesion-14

lunes 15 junio 2026

La sesión pasada quedamos con este codigo: 

```cpp
// -----------------------------
// SENSOR ULTRASÓNICO HC-SR04 + LED
// 3 condiciones + parpadeo + ausencia prolongada
// -----------------------------

const int trigPin = 2;
const int echoPin = 3;
const int ledPin = 6; // Pin PWM

long duracion;
float distancia;

String estadoActual = "";
String estadoAnterior = "";

// Control lectura sensor
unsigned long tiempoAnteriorSensor = 0;
const unsigned long intervaloSensor = 80;

// Control parpadeo LED
unsigned long tiempoAnteriorParpadeo = 0;
bool ledEncendido = false;

// Control ausencia prolongada
unsigned long tiempoInicioSinPresencia = 0;
bool contandoAusencia = false;
bool ausenciaProlongadaActivada = false;

const unsigned long tiempoAusencia = 120000;
// 120000 ms = 2 minutos

// Control encendido progresivo por ausencia
unsigned long tiempoAnteriorFade = 0;
const unsigned long intervaloFade = 200;
// Mientras más alto este número, más lento prende

int brilloAusencia = 0;

void setup() {
  Serial.begin(9600);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(ledPin, OUTPUT);

  analogWrite(ledPin, 0);

  Serial.println("Sistema iniciado");
}

void loop() {
  unsigned long tiempoActual = millis();

  // -----------------------------
  // LECTURA DEL SENSOR
  // -----------------------------
  if (tiempoActual - tiempoAnteriorSensor >= intervaloSensor) {
    tiempoAnteriorSensor = tiempoActual;

    distancia = medirDistancia();

    if (distancia < 0) {
      estadoActual = "No se detecta lectura valida";
    }

    else if (distancia > 230) {
      estadoActual = "sin presencia";
    }

    else if (distancia > 150 && distancia <= 230) {
      estadoActual = "hay alguien lejano";
    }

    else if (distancia > 50 && distancia <= 150) {
      estadoActual = "alguien se acerca";
    }

    else if (distancia <= 50) {
      estadoActual = "hay alguien cerca";
    }

    if (estadoActual != estadoAnterior) {
      Serial.print("Distancia medida: ");
      Serial.print(distancia);
      Serial.println(" cm");

      Serial.print("Mensaje para Totem 02: ");
      Serial.println(estadoActual);

      Serial.println("-------------------------");

      estadoAnterior = estadoActual;
    }
  }

  // -----------------------------
  // DETECTAR SI HAY O NO PRESENCIA
  // -----------------------------

  bool sinPresencia = 
    estadoActual == "sin presencia" || 
    estadoActual == "No se detecta lectura valida";

  if (sinPresencia) {
    if (contandoAusencia == false) {
      tiempoInicioSinPresencia = tiempoActual;
      contandoAusencia = true;
      ausenciaProlongadaActivada = false;
      brilloAusencia = 0;
    }

    if (tiempoActual - tiempoInicioSinPresencia >= tiempoAusencia) {
      ausenciaProlongadaActivada = true;
    }
  }

  else {
    contandoAusencia = false;
    ausenciaProlongadaActivada = false;
    brilloAusencia = 0;
  }

  // -----------------------------
  // CONTROL DEL LED
  // -----------------------------

  if (sinPresencia) {
    if (ausenciaProlongadaActivada) {
      encenderProgresivamentePorAusencia();

      if (estadoActual != "ausencia prolongada") {
        estadoActual = "ausencia prolongada";

        Serial.println("Mensaje para Totem 02: ausencia prolongada");
        Serial.println("LED encendiendose lentamente por ausencia");
        Serial.println("-------------------------");
      }
    }

    else {
      analogWrite(ledPin, 0);
      ledEncendido = false;
    }
  }

  else if (estadoActual == "hay alguien lejano") {
    parpadearLED(1000, 80);
    // parpadeo lento
  }

  else if (estadoActual == "alguien se acerca") {
    parpadearLED(400, 150);
    // parpadeo medio
  }

  else if (estadoActual == "hay alguien cerca") {
    analogWrite(ledPin, 255);
    // encendido fijo al máximo
    ledEncendido = true;
  }
}

// -----------------------------
// FUNCIÓN PARA MEDIR DISTANCIA
// -----------------------------
float medirDistancia() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duracion = pulseIn(echoPin, HIGH, 25000);

  if (duracion == 0) {
    return -1;
  }

  float distanciaCalculada = duracion * 0.0343 / 2;

  return distanciaCalculada;
}

// -----------------------------
// FUNCIÓN PARA PARPADEAR LED
// -----------------------------
void parpadearLED(unsigned long intervalo, int brillo) {
  unsigned long tiempoActual = millis();

  if (tiempoActual - tiempoAnteriorParpadeo >= intervalo) {
    tiempoAnteriorParpadeo = tiempoActual;

    ledEncendido = !ledEncendido;

    if (ledEncendido) {
      analogWrite(ledPin, brillo);
    } else {
      analogWrite(ledPin, 0);
    }
  }
}

// -----------------------------
// FUNCIÓN PARA AUSENCIA PROLONGADA
// -----------------------------
void encenderProgresivamentePorAusencia() {
  unsigned long tiempoActual = millis();

  if (tiempoActual - tiempoAnteriorFade >= intervaloFade) {
    tiempoAnteriorFade = tiempoActual;

    if (brilloAusencia < 255) {
      brilloAusencia++;
    }

    analogWrite(ledPin, brilloAusencia);
  }
}
```

y quedamos en que teníamos que corregir esto: 

esta correccion: También queda pendiente mejorar la lógica de envío de datos hacia Adafruit IO. Actualmente, el código trabaja con los valores del sensor en su estado natural, es decir, con lecturas numéricas constantes de distancia. Sin embargo, para no enviar demasiada información a Adafruit, la idea es simplificar y decodificar esos datos. En vez de mandar todas las mediciones del sensor, se podría enviar solo un valor o código por condición, por ejemplo:

0 = sin presencia
1 = alguien lejano
2 = alguien se acerca
3 = alguien cerca
4 = ausencia prolongada 

y agregar un modo demo con botón. 

