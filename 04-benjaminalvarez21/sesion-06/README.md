# sesion-06

lunes 13 abril 2026

Al comienzo de la clase se realizó la retroalimentación de la solemne 1, donde se indicaron los aspectos que debían corregirse y mejorarse para aumentar la nota del proyecto. Luego se dio un tiempo de trabajo en clases para avanzar en esas modificaciones.

Despues de eso, se trabajó con sensores capacitivos utilizando un Arduino UNO R4 WiFi y la librería `Arduino_CapacitiveTouch`.

## Sensores capacitivos

Un sensor capacitivo detecta cambios eléctricos cuando una persona acerca la mano o toca una superficie conectada al circuito. El cuerpo humano altera el campo eléctrico del sensor, permitiendo detectar presencia o cercanía sin necesidad de presión física.

Este tipo de sensores puede utilizarse para:

- Detectar contacto humano
- Medir cercanía o proximidad
- Crear interfaces táctiles
- Reemplazar botones mecánicos tradicionales

Incluso acercar la mano a un cable puede modificar los valores obtenidos por el sensor.

## Capacitive Touch en Arduino

El Arduino UNO R4 WiFi incluye soporte para detección táctil capacitiva mediante la librería `Arduino_CapacitiveTouch`. Esta librería permite realizar lecturas de capacitancia desde distintos pines compatibles de la placa.

## Funcionamiento básico

El sistema realiza lecturas eléctricas constantemente:

- Sin contacto → valores más bajos
- Con contacto o cercanía → valores más altos

Arduino interpreta estas variaciones para determinar si existe contacto o proximidad con el sensor capacitivo.

## Resultados en clase y codigos utilizados

### Codigos

```cpp
#include <Arduino_CapacitiveTouch.h>


// referencia
// https://docs.arduino.cc/tutorials/uno-r4-wifi/touch/
// por montoyamoraga para disenoUDP
// dis9079
// abril 2026
// funciona con Arduino Uno R4
// wifi o minima
// usar biblioteca Capacitive_Touch

// importar biblioteca
#include "Arduino_CapacitiveTouch.h"

// existe un constructo
// del tipo CapacitiveTouch
// que se llama touchButton, ese nombre es de fantasia
// esta conectada a la patita D0
CapacitiveTouch touchButton = CapacitiveTouch(D0);

// valor de lectura
int valorLectura = 0;

// setup() ocurre al principio una vez
void setup() {
  // prende el puerto serial
  // la velocidad es importante
  Serial.begin(9600);

  // touchButton
  // despues viene un punto
  // ese punto es como hacer doble click
  // es como entrar
  // dentro hace begin() que lo inicializa
  // el if hace que si lo logra pase algo
  // y si no, pase otra cosa
  if(touchButton.begin()){
    Serial.println(":) yay");
  } else {
    Serial.println("oh no :'( snif");
    // quedarse pegado ante el fracaso
    while(true);
  }
  
  // define el umbral o threshold
  // en 2000
  // lo que de inmediato me hace preguntarme
  // oh no
  // cuanto es el valor minimo posible
  // cuanto es el valor maximo posible
  // cuando terminara este calvario
  // por que 2000?
  // en california funciona?
  // y en este frio otono de santiago
  // que hago
  // quien soy
  // etc
  touchButton.setThreshold(2000);
}

// loop() ocurre en bucle
// despues de setup()
// hasta el fin de los tiempos
void loop() {

  // asignar a valorLectura
  // el resultado de preguntarle a touchButton
  // cuanto vale
  // read() me da el valor crudo
  valorLectura = touchButton.read();
  Serial.print("Valor crudo: ");
  // imprime valor lectura
  Serial.println(valorLectura);


  // se pregunta con if
  // si el boton esta siendo tocado
  if (touchButton.isTouched()) {
    // si lo esta, imprime
    Serial.println("hubo contacto");
  }
  
  // deja tu vida atras
  // suspendela, en pausa
  // cierra los ojos por 100 ms = 0.1 s
  // ignora todo lo que esta pasando
  // para que no ocurra tan rapido todo
  delay(100);
}
```

```cpp
#include <Arduino_CapacitiveTouch.h>


// referencia
// https://docs.arduino.cc/tutorials/uno-r4-wifi/touch/
// por montoyamoraga para disenoUDP
// dis9079
// abril 2026
// funciona con Arduino Uno R4
// wifi o minima
// usar biblioteca Capacitive_Touch

// importar biblioteca
#include "Arduino_CapacitiveTouch.h"

// existe un constructo
// del tipo CapacitiveTouch
// que se llama touchButton, ese nombre es de fantasia
// esta conectada a la patita D0
CapacitiveTouch touchButton = CapacitiveTouch(D0);

// valor de lectura
int valorLectura = 0;

// valores min y max
// que partan en el peor caso posible
int minLectura = 100000;
int maxLectura = 0;


// setup() ocurre al principio una vez
void setup() {
  // prende el puerto serial
  // la velocidad es importante
  Serial.begin(9600);

  // touchButton
  // despues viene un punto
  // ese punto es como hacer doble click
  // es como entrar
  // dentro hace begin() que lo inicializa
  // el if hace que si lo logra pase algo
  // y si no, pase otra cosa
  if (touchButton.begin()) {
    Serial.println(":) yay");
  } else {
    Serial.println("oh no :'( snif");
    // quedarse pegado ante el fracaso
    while (true)
      ;
  }

  // define el umbral o threshold
  // en 2000
  // lo que de inmediato me hace preguntarme
  // oh no
  // cuanto es el valor minimo posible
  // cuanto es el valor maximo posible
  // cuando terminara este calvario
  // por que 2000?
  // en california funciona?
  // y en este frio otono de santiago
  // que hago
  // quien soy
  // etc
  touchButton.setThreshold(2000);
}

// loop() ocurre en bucle
// despues de setup()
// hasta el fin de los tiempos
void loop() {

  // asignar a valorLectura
  // el resultado de preguntarle a touchButton
  // cuanto vale
  // read() me da el valor crudo
  valorLectura = touchButton.read();

  // actualizar valores min y max
  if (valorLectura < minLectura) {
    // actualiza el minimo con uno mejor
    minLectura = valorLectura;
  }

  if (valorLectura > maxLectura) {
    // actualizar el maximo con uno mejor
    maxLectura = valorLectura;
  }



  Serial.print("Valor crudo: ");
  // imprime valor lectura
  Serial.println(valorLectura);

  Serial.print("min: ");
  Serial.print(minLectura);
  Serial.print(", max: ");
  Serial.println(maxLectura);


  // se pregunta con if
  // si el boton esta siendo tocado
  if (touchButton.isTouched()) {
    // si lo esta, imprime
    Serial.println("hubo contacto");
  }

  // usar mi min y max para tomar conclusiones
  // tomo el valor promedio entre min y max
  // y si mi valor actual es mayor que eso
  // digo oh estoy por sobre el promedio
  if (valorLectura > (minLectura + maxLectura)/2) {
    Serial.println("sobre el promedio, dab");
  }

  // deja tu vida atras
  // suspendela, en pausa
  // cierra los ojos por 100 ms = 0.1 s
  // ignora todo lo que esta pasando
  // para que no ocurra tan rapido todo
  delay(100);
}

```

### Resultados

[![Resultados](https://img.youtube.com/vi/MQD843fGypM/hqdefault.jpg)](https://www.youtube.com/shorts/MQD843fGypM)
