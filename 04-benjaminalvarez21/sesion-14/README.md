# sesion-14

lunes 15 junio 2026

En esta clase trabajamos con el sensor de sonido MAX4466 e hicimos pruebas con los aplausos y chasquidos, con el primer código funciona pero después cuando intentábamos que funcionase con Adafruit IO ya no funciono.

![gif](./imagenes/prueba-mic.gif)

![arduino ide](./imagenes/codigo-micro.png)

Luego fuimos a comprar el df player pero no lo encontramos por ningún largo de San Diego, cuando volvimos de la aventura, Aarón nos compró el df player por mercado libre y no solo fue 1, si no que fueron 2. Muchas gracias Aarón.

### Códigos que probamos en clase

#### Código con 700 de umbral

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
#### Código con 200 de umbral

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
```

#### Código con 600 de umbral

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

#### Código con 800 de umbral

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

#### Código con 1000 de umbral

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

#### Código para probar en Adafruit IO

```cpp
#include <WiFiS3.h>
#include "AdafruitIO_WiFi.h"

// Completar con sus datos
#define WIFI_SSID "bla"
#define WIFI_PASS "bla"

#define IO_USERNAME "bla"
#define IO_KEY "bla"

AdafruitIO_WiFi io(IO_USERNAME, IO_KEY, WIFI_SSID, WIFI_PASS);

// Feed de Adafruit IO
AdafruitIO_Feed *pruebaMicro = io.feed("prueba-micro");

const int micPin = A0;
const int umbral = 700;

void setup() {
  Serial.begin(115200);

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

  if (lectura > umbral) {

    int maximo = lectura;
    unsigned long inicio = millis();

    while (millis() - inicio < 100) {
      int muestra = analogRead(micPin);

      if (muestra > maximo) {
        maximo = muestra;
      }
    }

    Serial.print("Aplauso detectado. Intensidad: ");
    Serial.println(maximo);

    // Envía el valor al feed prueba-micro
    pruebaMicro->save(maximo);

    delay(500);
  }
}
```
