# sesion-07

lunes 20 abril 2026

Grupo solemne 2: 

Grupo 8: Sofía Cartes - Monserrat Paredes - Valentina Ruz

Materiales que usaremos en clases:

- potencíometro, tres patitas, los extremos no se conectan (detecta el giro y revisar el valor)

- Sensor LDR (reaacciona a la luz), es poco estable 

- protoboard

- Cables

- Motor servo (servomotores), tiene 3 terminales:

Terminal positivo: Recibe la alimentación del motor (4 a 8 voltios)

Terminal negativo: Referencia tierra del motor (0 voltios)

Entrada de señal: Recibe la señal de control del motor

## APUNTES
Apuntes maquinas: Libro de todos los conocimientos que pasan el ramo de taller de Maquinas electronicas

Placa de pruebas (protoboard): circulan electrones


Contiene 2 emisferios:

Emisferio izquierdo, emisferio derecho, funcionan independiente

Lo que conectas en uno sigue para todos, ya sea positivo o negativo


Voltaje de alimentacion:
positivo, se usa generalmente un cable rojo (positivo)
negativo: negro, cafe y verde 

Letras y numeros:
columnas (letras) y filas (numeros)

GND: tierra


Tinkercad

https://www.tinkercad.com/

Es una plataforma en línea gratuita de Autodesk diseñada para facilitar el modelado 3D, la simulación de circuitos electrónicos y la programación por bloques.

La usaremos para hacer el codigo para ver que funcione en el arduino 

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


<img width="904" height="501" alt="SESION6" src="https://github.com/user-attachments/assets/a0e2fb09-c48b-40c0-9df9-2f3ee2902da0" />




<img width="631" height="636" alt="TICKERCAD" src="https://github.com/user-attachments/assets/023f0809-6819-4d0e-b945-770ce3fe7345" />


Despues de probarlo, fuimos mejorando el codigo en clases para seguir avanzando y que el motor servo funcione

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


## Vista digital

<img width="420" height="224" alt="FuncionaMotor" src="https://github.com/user-attachments/assets/faa28267-72da-40b8-8c3f-cca39016d038" />


## Vista anolaga 


<img width="288" height="512" alt="FuncionaAnalogo" src="https://github.com/user-attachments/assets/8ea91e9d-bb93-4a18-9b9b-e5206f1e7d6e" />



## ¿Cómo pasar este dato a la nube?
