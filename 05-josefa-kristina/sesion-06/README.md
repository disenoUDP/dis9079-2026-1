# sesion-06

## Capacitive sensing (sensar con capacitancia)

Capacitancia como manera de medir distancia.

UNO R4 Capacitive touch
Biblioteca necesaria: Capacitive_touch

Arduino UNO R4 wifi pinout:

![pinout](./imagenes/uno-r4-pinout.png)

Library Functions:

`CapacitiveTouch(uint8_t pin)` Construye un sensor capacitivo de tacto por el pin elegido.

`bool begin()` Inicializa el sensor y configura ek pin y el hardware.

`int read()` Lee el valor crudo del sensor y lo devuelve.

`bool isTouched()`  Chequea si el sensor está siendo tocado basado en los umbrales.

`void setThreshold(int threshold)` Determina los umbrales de detección para la sensibilidad del tacto.

`int getThreshold()` Recupera el umbral de detección actual.

Aarón nos enseña que significa cada línea del ejemplo de capacitive touch en Arduino IDE.

Antes de correr el código conectar una sola pieza de cualquier material conductor al pin D0 de la placa.

```cpp
//incluir la biblioteca de capacitive touch
#include "Arduino_CapacitiveTouch.h"

//touch button nombre fantasía que refiere a la patita D0
CapacitiveTouch touchButton = CapacitiveTouch(D0);
//
void setup() {
//prende el puerto serial en una velocidad especifica
  Serial.begin(9600);
  //si pasa algo dice "" y sino dice ""
  if(touchButton.begin()){
    Serial.println("Capacitive touch sensor initialized.");
  } else {
    Serial.println("Failed to initialize capacitive touch sensor. Please use a supported pin.");
    //quedarse pegado frente el fracaso
    while(true);
  }
// define el umbral o threshold en 2000

  touchButton.setThreshold(2000);
}
//loop ocurre en bucle despues del setup
void loop() {
  //asignar a valor lectura
  //el resultado de oreguntarle a touch button
  //read() me da el valor crudo
  // Read the raw value from the capacitive touch sensor.

  int sensorValue = touchButton.read();
  Serial.print("Raw value: ");
 //imprime valor lectura
  Serial.println(sensorValue);

  // Check if the sensor is touched (raw value exceeds the threshold).
  //se pregunta si el botón está siendo tocado
  if (touchButton.isTouched()) {
    //si lo está, imprime
    Serial.println("Button touched!");
  }
  //detente por 0,1 segundos.
  delay(100);
}


```

Aarón nos enseña como hacer un ejemplo calibrado de lo anterior, intenté seguirle la velocidad pero no pude escribirlo todo pero entendí :)
(creo)

Ejemplo Calibrado:

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

lunes 13 abril 2026
