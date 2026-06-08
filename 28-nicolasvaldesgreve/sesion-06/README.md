# sesion-06

lunes 13 abril 2026

# Apuntes 13/04

### Sensor Capacitivo

Arduino tiene un sensor capacitivo de tacto, lo que significa que es capaz de identificar si hay cambios en la capacitancia debido a la fuerza o a la ausencia de ésta en el instrumento que lo detecta!! por lo que Aarón nos va a enseñar a hacerlo reaccionar a nuestro contacto o cercanía, ya que éste también puede detectar si estás cerca a pesar de que no lo toques directamente.

Para hacer el ejercicio, utilizaremos el código que nos entrega de ejemplo la página de Arduino para probar el sensor, pero ésta vez Aarón nos explicará lo que significa cada línea con comentarios dentro del código, por lo que quedó así:

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

Luego de entender lo que hace cada línea de manera poética, conectamos un cable dupont al pin D0 de la placa Arduino UNO R4 WiFi, subimos el código y la placa emepzó a recibir información sobre nuestro contacto con el cable dupont!! de hecho, hasta cuando tocabas la cubierta plástica lo detectaba, pero claramente no al mismo nivel que cuando tocábamos la punta metálica del dupont.

![Sensor funcionando](./imagenes/sensor-capacitivo.gif)
