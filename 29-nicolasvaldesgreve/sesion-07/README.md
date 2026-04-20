# sesion-07

# Apuntes 20/04

Se nos entregó un potenciómetro B20k, un LDR, una protoboard nueva, un motor Micro Servo 9g.

Es primera vez que veo éste motor, por lo que no entendía muy bien cómo funcionaba hasta que Aarón nos explicó que éste motor tiene tres terminales:

1. Alimentación (cable rojo)
2. Tierra (cable café)
3. Comunicación (cable amarillo)

Para poder explicar cómo ubicar los componentes dentro de la protoboard, Aarón fue mostrando paso a paso qué hacer dentro de TinkerCAD en el cual se puede hacer una simulación de circuitos!! muy buena herramienta.

En TinkerCAD, Aarón nos dijo que para conenctar el Arduino UNO R4 WiFi teníamos que conectar la alimentación en el pin que se encuentra en la sección de ``power`` llamado ``5V``, mientras que para conectar a tierra tenemos que usar el pin de la sección ``power`` llamado ``GND`` o en la sección llamada ``digital`` que también tiene un pin llamado ``GND``. Para lograr que la placa Arduino UNO R4 WiFi se pueda comunicar con el potenciómetro, conectamos un cable dupont en el pin 2 del potenciómetro al pin ``A0`` de la placa que se encuentra en la sección de ``analog``, mientras que al potenciómetro se le conecta un cable para la alimentación y otro para tierra en los extremos de éste.

Para poder ver cómo recibe la información la placa, utilizamos el siguiente código:

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

Con éste código, podemos ver los valores del potenciómetro dentro del Serial Monitor.

Luego, para poder probar el motor que se nos entregó se nos indicó que para poder conectarlo al circuito tenemos que entender para qué es cada terminal. En el caso de nuestro motor, los colores son café, rojo y amarillo, y en el mismo orden éstos significan tierra, alimentación y comunicación, por lo tanto conectamos el terminal rojo al positivo de la protoboard, el terminal café al negativo de la protoboard y el amarillo se conectó a un espacio de la protoboard donde se encuentra con otro cable que va directo al pin ``~9`` que se encuentra en la sección ``digital``.

Para poder demostrar lo que se puede hacer con el motor, se utilizó el siguiente código:

```cpp
// ejemplo servo + potenciometro

#include <Servo.h>

Servo miServo;

void setup() {
  miServo.attach(9); // D9
}

void loop() {
  int lectura = analogRead(A0);           // 0 - 1023
  int angulo  = map(lectura, 0, 1023, 0, 180); // mapea a 0°-180°
  miServo.write(angulo);
  delay(15); // pequeña pausa para estabilizar el servo
}
```

Con éste código, pudimos lograr que el motor se moviera mediante el movimiento que nosotros aplicaramos en el potenciómetro que estaba en la protoboard.

---

 Buscar cómo reemplazar el potenciómetro en el circuito por el LDR
