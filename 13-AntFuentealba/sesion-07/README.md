# sesion-07

lunes 20 abril 2026

Apuntes

En esta sesión se trabajó con sensores, actuadores y comunicación con la nube usando Arduino. El objetivo principal fue entender cómo leer señales del mundo físico (como luz o posición) y transformarlas en movimiento o datos enviados a internet.


## Materiales utilizados

### Protoboard
La protoboard es una base para montar circuitos sin necesidad de soldar.

- Está dividida en dos hemisferios independientes.
- Cada lado tiene líneas de **VCC (+)** y **GND (-)**.
- Los orificios están conectados internamente en filas o columnas.
- Lo que conectas en una fila se replica en toda la línea.
- Los dos lados no se comunican entre sí sin un cable externo.

En Arduino normalmente se trabaja con 5V, mientras que en Raspberry Pi se usa 3.3V.



### Servomotor
Es un motor que permite controlar posición angular.

- Tiene 3 cables:
  - VCC (rojo)
  - GND (negro)
  - Señal (amarillo)
- Permite moverse típicamente entre 0° y 180°.
- Se usa para movimientos controlados (robótica, mecanismos, etc).


### LDR (sensor de luz)
Es una resistencia que cambia según la luz.

- A más luz → cambia su resistencia.
- Entrega valores analógicos variables.
- Permite medir intensidad de iluminación ambiental.


### Potenciómetro
Es un controlador manual de posición.

- Tiene 3 patitas:
  - Una a VCC
  - Una a GND
  - Una central de señal
- Se usa como entrada analógica.
- Para lectura se usa la patita central + una de los extremos (no ambos extremos juntos).


### Otros materiales
- Cables jumper
- Arduino
- Sensores
- Servomotores
- Protoboard


## Arduino

### Lectura de potenciómetro

El Arduino puede leer señales analógicas usando `analogRead()`.

```cpp
int lectura = 0;

void setup() {
  Serial.begin(9600);
}

void loop() {
  lectura = analogRead(A0);
  Serial.println(lectura);
}
```

### Servo con potenciometro
```cpp
#include <Servo.h>

Servo miServo;

int lectura = 0;
int angulo = 0;

void setup() {
  Serial.begin(9600);
  miServo.attach(9);
}

void loop() {
  lectura = analogRead(A0);

  Serial.println(lectura);

  angulo = map(lectura, 0, 1023, 0, 180);
  miServo.write(angulo);

  delay(15);
}
```
