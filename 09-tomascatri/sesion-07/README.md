# sesion-07

lunes 20 abril 2026

Debido a que falté la semana pasada, veré los apuntes de mi compañero Ángel y, en base a lo que entiendo, lo iré poniendo.

## Lo que entendí de la clase
Entregaron materiales para nuestro grupo. La lista es la siguiente, junto con la explicación de para qué sirve cada componente:

* **Potenciómetro**: Tiene 3 patas; usualmente se conectan la del medio (2) y uno de los dos extremos. Sirve para que uno mismo regule cuánta potencia de voltaje quiere que pase por ahí.
* **LDR**: Es un fotorresistor el cual cambia su resistencia (y por tanto el voltaje) dependiendo de la intensidad de luz entrante a sus sensores.
* **Cables**: Sirven para conectar componentes entre sí. Dependiendo del tipo de cable, la conexión es diferente.
* **Protoboard**: Es una placa de pruebas la cual tiene 4 espacios diferentes que se conectan de distintas maneras. Los buses positivos y negativos se encuentran en cada extremo; usualmente hay un negativo y un positivo arriba, y un negativo y positivo abajo. Las conexiones en el centro son verticales y se dividen en dos secciones (superior e inferior) que no están conectadas entre sí; esto se usa usualmente para los chips.
* **Servomotor**: Dispositivo eléctrico que permite controlar la posición, velocidad y aceleración de su eje; por ejemplo, se puede usar para la extremidad de un robot.
* **Arduino y Raspberry Pi**: En el Arduino, se debe conectar al voltaje positivo y el otro jumper a tierra (GND).
* **Sugerencia**: Se sugiere dividir por colores para no perderse.
* **Tinkercad**: Existe una app para hacer circuitos de manera virtual llamada Tinkercad.
* **DATO IMPORTANTE**: Todos los componentes deben estar conectados a un positivo o negativo, directa o indirectamente. Estos buses del protoboard deben estar alimentados por una fuente de poder, que puede ser desde una pila hasta el Arduino recibiendo energía desde el computador.

## Experimentación en clase
Entiendo que ahora probaron todos estos componentes juntos (o casi todos) para realizar una lectura de potenciómetro, el cual tenga un efecto en el servomotor para moverlo a voluntad del usuario. También mandaron las señales del potenciómetro a la nube de Adafruit.

Para esto realizaron lo siguiente:

* Agregaron el potenciómetro y el servomotor a la protoboard y realizaron las conexiones.
* Las patas del potenciómetro están conectadas al Arduino en la entrada **A0** y al positivo y negativo del protoboard.
* El positivo del protoboard está conectado a la conexión del Arduino llamada **5V**, que se encarga de darle energía.
* El negativo del protoboard está conectado a la conexión del Arduino llamada **GND** (tierra).
* El servomotor está conectado a la patita **9** del Arduino. El cable de señal suele ser el de la izquierda (naranja/amarillo), en el medio debe ir el positivo a la protoboard y el de la derecha al negativo de la protoboard.
* Una vez hecho esto, se tiene que cargar el código del potenciómetro y del servo al Arduino.

### Código servo Arduino:
```
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
* Código servo Arduino:
```
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
* Una vez hecho eso, ya se puede mover con el potenciómetro; además, enviamos los valores que genera el potenciómetro a la nube.
