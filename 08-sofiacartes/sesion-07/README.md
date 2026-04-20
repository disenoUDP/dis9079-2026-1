# sesion-07

lunes 20 abril 2026

Solemne 2: 

Grupo 8

Integrantes:
- Monserrat Paredes
- Valentina Ruz
- Sofía Cartes

Materiales a utiizar: 

- Protoboard tiene dos emiferios, son sectores independientes tiene vcc y gnd para guiarnos 
- servomotor tiene 3 terminales vcc, señal (amarilla) posición a dónde va.
- LDR (sensor) pasa por todos los valores intermedios 
- Potenciómetro tiene 3 patitas, la 1 y la 2 o la 2 y la 3 se conectará, así detectaremos nuestro giro.

entre mas voltaje utilizamos, 

rasberrypi ocupa 3.3 de voltaje

veremos datos, estrategias para mandarle a la nube

## Tinkercad 

Ejemplo visto en clases: <https://www.tinkercad.com/things/8DYKKECMAMm/editel?returnTo=%2Fdashboard>

```cpp
// C++ code
//


// queremos que nuestro Arduino
// sea capaz de leer un potenciometro
// conectado a la entrada A0.

int lectura = 0;


void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  lectura = analogRead(A0);
  Serial.println(lectura);
}
```

arduino

```cpp
// ejemplo lectura potenciometro

// queremos que nuestro Arduino
// sea capaz de leer un potenciometro
// conectado a la entrada A0.

int lectura = 0;


void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  lectura = analogRead(A0);
  Serial.println(lectura);
}
```

include servo 

```cpp
// ejemplo lectura potenciometro

// queremos que nuestro Arduino
// sea capaz de leer un potenciometro
// conectado a la entrada A0.


#include <Servo.h>


Servo miServo;

int lectura = 0;
int angulo = 0;


void setup()
{
  pinMode(9, OUTPUT);
  Serial.begin(9600);
  // en que patita esta conectado el servo
  // conectemos a patita 9 digital
  miServo.attach(9);
  
}

void loop()
{
  // leer
  lectura = analogRead(A0);
  
  // imprimir en consola
  Serial.println(lectura);
  
  
  // toma el valor de lectura
  // que va originalmente entre 0 y 1023
  // y mapealo al rango 0 a 180
  angulo = map(lectura, 0, 1023, 0, 180);
    
  // pidele por favor al servo
  // que vaya a ese angulo
  miServo.write(angulo);
  
  // servo descansa un poquito
  // 15 milisegundos
  // la vida es dura
  delay(15);
    
}
```

