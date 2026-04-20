# grupo-10

## Interacciones inalámbricas

## integrantes

* Agustina Aceituno
* Ignacio Campos
* Antonia Fuentealba

## descripción del proyecto

El proyecto consiste en establecer una comunicación inalámbrica entre un Arduino y la plataforma en la nube Adafruit IO utilizando conexión WiFi.

El Arduino se conecta a una red WiFi y luego a Adafruit IO mediante credenciales (usuario y key). A través de esta conexión, el dispositivo puede enviar datos (por ejemplo, valores de sensores o contadores) a un feed en la nube, y también recibir información desde ese mismo feed para controlar acciones (como encender un LED).

Este sistema se basa en el paradigma de Internet de las Cosas (IoT), donde dispositivos físicos se conectan a internet para intercambiar datos en tiempo real.

![proceso](./imagenes/adafruit1.png)
![proceso](./imagenes/adafruit2.png)

## Proceso

![proceso](./imagenes/solemne1.jpg)
![proceso](./imagenes/solemne2.jpg)
![proceso](./imagenes/solemne3.jpg)

## materiales usados en solemne-01

| Cantidad | Componente / Recurso | Función |
|----------|----------------------------|---------|
| 1 | Arduino UNO R4 WiFi | Placa principal utilizada para ejecutar el programa y conectarse a WiFi |
| 1 | Cable USB-C | Permite cargar el código desde el computador y alimentar la placa |
| 1 | Computador | Dispositivo para programar y subir el código al Arduino |
| 1 | Arduino IDE | Entorno de desarrollo utilizado para escribir y cargar el código |
| 1 | Librería Adafruit IO | Permite la comunicación entre el Arduino y la plataforma en la nube |
| 1 | Cuenta en Adafruit IO | Plataforma donde se envían, reciben y visualizan los datos |
| 1 | Red WiFi / Hotspot móvil | Proporciona conexión a internet para el funcionamiento del sistema |

## código usado con Adafruit IO

### código para enviar

```cpp
// // Adafruit IO Publish Example
//
// Adafruit invests time and resources providing this open source code.
// Please support Adafruit and open source hardware by purchasing
// products from Adafruit!
//
// Written by Todd Treece for Adafruit Industries
// Copyright (c) 2016 Adafruit Industries
// Licensed under the MIT license.
//
// All text above must be included in any redistribution.

// ejemplo para enviar / publish
// por montoyamoraga
// para disenoUDP
// basado en
// Adafruit IO Publish Example

// incluir archivo config.h
// hacer las modificaciones de este archivo
// NO subir a github
#include "config.h"

// esta variable entera
// sera un contador que aumenta
// durante el funcionamiento del software
int contador = 0;

// definir una variable que se llame nombreFeed
// que tenga un cierto valor
// mantener las doble comillas, cambiar grupoXX segun tu nombre de grupo
AdafruitIO_Feed *nombreFeed = io.feed("grupo10");

void setup()
{

  // prender la conexion serial
  // ojo con la velocidad de 115200 baud
  // cuando abras el monitor serial debes configurarlo
  // a este numero, porque el standard de fabrica es 9600 baud
  Serial.begin(115200);

  // estas lineas pausan el codigo
  // hasta que prendas el monitor serial
  // la lupita arriba a la derecha en Arduino IDE
  while (!Serial)
    ;

  // imprimir en consola
  Serial.print("conectando a Adafruit IO");

  // conectarse a io.adafruit.com
  io.connect();

  // esperar la conexion
  while (io.status() < AIO_CONNECTED)
  {
    // imprimir un punto cada medio segundo
    // mientras se conecta
    Serial.print(".");
    delay(500);
  }

  // demostrar que logramos conexion
  Serial.println();
  Serial.println(io.statusText());
}

void loop()
{

  // esta linea es necesaria
  // al principio de loop()
  // para mantener la conexion
  // y procesar datos que lleguen
  io.run();

  // enviar el contador a Adafruit IO
  // primero mostrar en monitor serial
  Serial.println("enviando -> " + String(contador));
  // despues enviar a la nube
  nombreFeed->save(contador);

  // incrementar el contador en 1
  contador = contador + 1;

  // Adafruit IO tiene una velocidad limitada
  // de escritura / publishing
  // usamos delay para pausar el codigo 3 segundos
  delay(3000);
}
```

## investigaciones individuales

[agustinaaceituno](./persona-01.md)

[persona-02.md](./persona-02.md)

[antfuentealba](./persona-03.md)

## bibliografía

* Adafruit Industries. *Welcome to Adafruit IO*.  
  <https://learn.adafruit.com/welcome-to-adafruit-io>  

* Adafruit Industries. *Adafruit IO Basics: Dashboards*.  
  <https://learn.adafruit.com/adafruit-io-basics-dashboards>  

* Adafruit Industries. *Adafruit IO Basics: Digital Input*.  
  <https://learn.adafruit.com/adafruit-io-basics-digital-input>  

* Adafruit IO. *Plataforma oficial*.  
  <https://io.adafruit.com>  

* Arduino Documentation. *UNO R4 WiFi Examples*.  
  <https://docs.arduino.cc/tutorials/uno-r4-wifi/wifi-examples/>  

* Wikipedia. *MQTT (Message Queuing Telemetry Transport)*.  
  <https://en.wikipedia.org/wiki/MQTT>  

* Wikipedia. *Internet of Things (IoT)*.  
  <https://en.wikipedia.org/wiki/Internet_of_things>  

* Arduino Documentation. *Arduino IDE*.  
  <https://docs.arduino.cc/software/ide/>  

* Adafruit Learning System. *Adafruit IO Arduino Library*.  
  <https://learn.adafruit.com/adafruit-io/arduino>  
