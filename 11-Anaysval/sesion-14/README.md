# sesion-14

lunes 15 junio 2026

Aprovechamos la clase para ir a comprar el sensor de sonido MAX4466, el módulo PAM8403 y el DFPlayer, aunque este último no logramos encontrarlo ˙◠˙

El código del micrófono está funcionando ദ്ദി(˵ •̀ ᴗ - ˵ ) ✧, pero marca valores de 1023 muuuy seguido. Por eso estamos evaluando si nos conviene seguir usando el aplauso como input o cambiarlo por un chasquido. 

También probamos cambiando el valor del umbral para ir ajustando la sensibilidad del micrófono frente a distintos sonidos, además de la distancia a la que se debe activar para evitar que se sature constantemente. 

Finalmente, nos quedamos con el chasquido de dedos, ya que funcionaba mejor y entregaba valores más variados. Esta decisión la tomamos un día en que nos quedamos trabajando después de clases, tras un buen rato de prueba y error hasta llegar a ese resultado.

![foto](./imagenes/prueba-mic.gif)

#### Prueba de códigos

```cpp
const int micPin = A0;

// Ajustar según las pruebas
const int umbral = 700;

void setup() {
  Serial.begin(115200);
  pinMode(micPin, INPUT);

  Serial.println("Sistema listo.");
  Serial.println("Aplaude para probar el sensor.");
}

void loop() {

  int lectura = analogRead(micPin);

  if (lectura > umbral) {

    int maximo = lectura;
    unsigned long inicio = millis();

    // Captura el valor máximo durante 100 ms
    while (millis() - inicio < 100) {

      int muestra = analogRead(micPin);

      if (muestra > maximo) {
        maximo = muestra;
      }
    }

    Serial.print("Aplauso detectado. Intensidad: ");
    Serial.println(maximo);

    // Evita múltiples detecciones del mismo aplauso
    delay(500);
  }
}
```

```cpp
const int micPin = A0;

// Ajustar según las pruebas
const int umbral = 200;

void setup() {
  Serial.begin(115200);
  pinMode(micPin, INPUT);

  Serial.println("Sistema listo.");
  Serial.println("Aplaude para probar el sensor.");
}

void loop() {

  int lectura = analogRead(micPin);

  if (lectura > umbral) {

    int maximo = lectura;
    unsigned long inicio = millis();

    // Captura el valor máximo durante 100 ms
    while (millis() - inicio < 100) {

      int muestra = analogRead(micPin);

      if (muestra > maximo) {
        maximo = muestra;
      }
    }

    Serial.print("Aplauso detectado. Intensidad: ");
    Serial.println(maximo);

    // Evita múltiples detecciones del mismo aplauso
    delay(500);
  }
}


—-----------------------

const int micPin = A0;

// Ajustar según las pruebas
const int umbral = 400;

void setup() {
  Serial.begin(115200);
  pinMode(micPin, INPUT);

  Serial.println("Sistema listo.");
  Serial.println("Aplaude para probar el sensor.");
}

void loop() {

  int lectura = analogRead(micPin);

  if (lectura > umbral) {

    int maximo = lectura;
    unsigned long inicio = millis();

    // Captura el valor máximo durante 100 ms
    while (millis() - inicio < 100) {

      int muestra = analogRead(micPin);

      if (muestra > maximo) {
        maximo = muestra;
      }
    }

    Serial.print("Aplauso detectado. Intensidad: ");
    Serial.println(maximo);

    // Evita múltiples detecciones del mismo aplauso
    delay(500);
  }
}

```

```cpp
const int micPin = A0;

// Ajustar según las pruebas
const int umbral = 600;

void setup() {
  Serial.begin(115200);
  pinMode(micPin, INPUT);

  Serial.println("Sistema listo.");
  Serial.println("Aplaude para probar el sensor.");
}

void loop() {

  int lectura = analogRead(micPin);

  if (lectura > umbral) {

    int maximo = lectura;
    unsigned long inicio = millis();

    // Captura el valor máximo durante 100 ms
    while (millis() - inicio < 100) {

      int muestra = analogRead(micPin);

      if (muestra > maximo) {
        maximo = muestra;
      }
    }

    Serial.print("Aplauso detectado. Intensidad: ");
    Serial.println(maximo);

    // Evita múltiples detecciones del mismo aplauso
    delay(500);
  }
}

```

```cpp
const int micPin = A0;

// Ajustar según las pruebas
const int umbral = 800;

void setup() {
  Serial.begin(115200);
  pinMode(micPin, INPUT);

  Serial.println("Sistema listo.");
  Serial.println("Aplaude para probar el sensor.");
}

void loop() {

  int lectura = analogRead(micPin);

  if (lectura > umbral) {

    int maximo = lectura;
    unsigned long inicio = millis();

    // Captura el valor máximo durante 100 ms
    while (millis() - inicio < 100) {

      int muestra = analogRead(micPin);

      if (muestra > maximo) {
        maximo = muestra;
      }
    }

    Serial.print("Aplauso detectado. Intensidad: ");
    Serial.println(maximo);

    // Evita múltiples detecciones del mismo aplauso
    delay(500);
  }
}

```

```cpp

const int micPin = A0;

// Ajustar según las pruebas
const int umbral = 1000;

void setup() {
  Serial.begin(115200);
  pinMode(micPin, INPUT);

  Serial.println("Sistema listo.");
  Serial.println("Aplaude para probar el sensor.");
}

void loop() {

  int lectura = analogRead(micPin);

  if (lectura > umbral) {

    int maximo = lectura;
    unsigned long inicio = millis();

    // Captura el valor máximo durante 100 ms
    while (millis() - inicio < 100) {

      int muestra = analogRead(micPin);

      if (muestra > maximo) {
        maximo = muestra;
      }
    }

    Serial.print("Aplauso detectado. Intensidad: ");
    Serial.println(maximo);

    // Evita múltiples detecciones del mismo aplauso
    delay(500);
  }
}

```

#### Código con Adafruit

```cpp
#include <WiFiS3.h>
#include "AdafruitIO_WiFi.h"


// Tus datos
#define WIFI_SSID "xxx"
#define WIFI_PASS "xxx"


#define IO_USERNAME "xxx"
#define IO_KEY "xxx"


AdafruitIO_WiFi io(IO_USERNAME, IO_KEY, WIFI_SSID, WIFI_PASS);


// Nombre exacto del feed en Adafruit IO
AdafruitIO_Feed *pruebaMicro = io.feed("xxx");


const int micPin = A0;
const int umbral = 200; // Más sensible


unsigned long ultimoEnvio = 0;


void setup() {
 Serial.begin(115200);


 while (!Serial) {
   delay(10);
 }


 Serial.println("Conectando a Adafruit IO...");


 io.connect();


 while (io.status() < AIO_CONNECTED) {
   Serial.print(".");
   delay(500);
 }


 Serial.println();
 Serial.println("Conectado a Adafruit IO");
}


void loop() {
 io.run();


 int lectura = analogRead(micPin);


 // Ver valor del micrófono
 Serial.print("Lectura: ");
 Serial.println(lectura);


 if (lectura > umbral) {


   Serial.print("Sonido detectado. Enviando: ");
   Serial.println(lectura);


   pruebaMicro->save(lectura);


   delay(500); // evita múltiples envíos
 }


 delay(50);
}

```
