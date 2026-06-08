# sesion-06

lunes 13 abril 2026

---

## Apuntes

- `Resistencia:` resistor, flujo de corriente eléctrica.
- `Condensador:` capacidad eléctrica
  - capacitor
  - la capacitancia propiedad material, depende del área y la `DISTANCIA`
- <https://docs.arduino.cc/tutorials/uno-r4-wifi/touch/> cuán cerca está nuestra manos del arduino
- Bilbioteca utilizar: `Capacitive_Touch`
- Cada patita del arduino funciona de manera distina, pueden compartir vidas o no :)
  - en que patita vive
  - a que nos conectamos
  - pedir una lectura
  - hay alguien tocando o no hay (porque es un sensor capacitivo)
  
 La capacitancia no le importa el tacto extemo, pero se acerca al cable y cambia el valor
 
## [Capacitive Touch](https://docs.arduino.cc/tutorials/uno-r4-wifi/touch/)

`¿Para qué sirve el tutorial de Adafruit?` Enseña como usar un sensor táctil (touch) con el Arduino UNO R4 WIFI

1. Detectar cuando una persona toca una superficie
2. Reemplazar botones físicos por interacciones más modernas
3. Crear proyectos interactivos (luces, pantallas, IoT, etc.)

Ejemplo: tocar un cable y en el serialmonitor sale el valor 

- El sensor funciona como un botón:
  - No tocado → señal LOW (0)
  - Tocado → señal HIGH (1)

`¿Cómo se conecta?`

El Arduino UNO R4 WiFi cuenta con 14 pines digitales (D0-D13) de entrada/salida que operan a 5V, manteniendo el formato del R3 pero con un microcontrolador más rápido.

- VCC del sensor → 5V del Arduino
- GND del sensor → GND del Arduino
- DIGITAL del sensor → (D0-D13)

Estos pines digitales, son los que leen si estás tocando o no el sensor.

`¿Qué pasa realmente?`

El sensor detecta cambios eléctricos cuando tu dedo se acerca o toca.

- El cuerpo altera la capacitancia
- El sensor traduce eso en una señal digital
- Arduino interpreta la señal

El tutorial de touch en Arduino UNO R4 WiFi enseña cómo utilizar un sensor táctil como entrada digital. Este sensor detecta el contacto y envía una señal HIGH o LOW al Arduino, permitiendo reemplazar botones físicos por interacciones táctiles. Se conecta mediante pines de alimentación (VCC, GND) y un pin de señal, y se programa usando funciones como pinMode() y digitalRead().

---

Código

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

---

Stylophone: crearon un sintetizador de bolsillp raro 
Theremin: 
