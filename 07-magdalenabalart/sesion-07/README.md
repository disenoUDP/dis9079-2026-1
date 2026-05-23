# sesion-07

lunes 20 abril 2026

# Idea general

En esta sesión se comenzó a aterrizar la Solemne 02 desde lo material y técnico. Se entregaron componentes para prototipar y se trabajó con la idea de que una conexión inalámbrica no solo transmite datos, sino que puede transformar un gesto, una variación o una condición del entorno en una respuesta física.

La clase se movió entre tres niveles: armar circuitos, leer datos con Arduino y convertir esas lecturas en movimiento o información enviada por red. 

## Materiales entregados

Para comenzar con la Solemne 02 recibimos:

protoboard  
cables  
servomotor  
potenciómetro  
LDR  

## Protoboard como sistema

La protoboard, también llamada breadboard, permite armar circuitos sin soldar. En Chile suele llamarse protoboard, mientras que en Estados Unidos se conoce como breadboard.

Tiene dos secciones principales de alimentación: una línea positiva (+) y una línea negativa (–). Funciona como una especie de “máquina de repetición”, porque ciertos puntos están conectados internamente entre sí.

Generalmente se trabaja con una lógica de colores:

positivo: rojo
negativo / tierra: verde, café o negro

Arduino también tiene una señal de GND, que corresponde a la tierra. Esa tierra debe conectarse a la línea negativa de la protoboard para que todos los componentes compartan una misma referencia eléctrica.

La arquitectura interna de la protoboard es clave: no todos los agujeros son independientes. Por ejemplo, los puntos de 1A a 1E están conectados entre sí. 

## Potenciómetro y lectura análoga

El primer ejercicio fue conectar un potenciómetro a Arduino. El potenciómetro permite generar un rango continuo de valores, no solo un encendido/apagado.

Para conectarlo:

una pata extrema va al positivo (+)
la otra pata extrema va al negativo / GND
la pata del medio va a una entrada análoga del Arduino, por ejemplo A0

La idea del código era decirle al Arduino que fuera capaz de leer un potenciómetro conectado a la entrada A0. 

```
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
La función importante es: 
 
```
lectura = analogRead(A0); 
```

Esto lee el valor análogo que llega desde el potenciómetro. Arduino devuelve un valor entre 0 y 1023, dependiendo de la posición de la perilla.

La idea clave es que ya no trabajamos con un estado binario, sino con un gradiente. 

## Servo: traducir datos en movimiento 

Después conectamos un servomotor, que tiene tres patitas o cables:

rojo: voltaje
negro/café: GND
amarillo: señal, donde le llega la instrucción

El servo permite controlar un movimiento en ángulos, generalmente entre 0° y 180°.

Código revisado: 
```
#include <Servo.h>

Servo miServo;

int lectura = 0;
int angulo = 0;

void setup()
{
  pinMode(9, OUTPUT);
  Serial.begin(9600);
  miServo.attach(9);
}

void loop()
{
  lectura = analogRead(A0);
  Serial.println(lectura);

  angulo = map(lectura, 0, 1023, 0, 180);

  miServo.write(angulo);

  delay(15);
} 

angulo = map(lectura, 0, 1023, 0, 180);
miServo.write(angulo); 
```
La función map() toma el valor del potenciómetro, que va entre 0 y 1023, y lo transforma en un ángulo entre 0 y 180.

Acá ocurre algo central: un número se convierte en movimiento.  

<img src="./imagenes/servo.gif" alt="Pantalla OLED" width="30%">  
 
## De lectura a comportamiento

Luego el ejercicio avanzó desde el movimiento directo hacia la construcción de un comportamiento. Ya no se trataba solo de que el servo se moviera según la perilla, sino de que pudiera “saludar” o “cohibirse”. 
```
if (lectura > 700) {
  saludar = true;
}
else {
  saludar = false;
} 
```
Y después: 
```
if (saludar) {
  moverLaManitoTimidamente();
}
else {
  meCohibi();
} 
```
Esto muestra que programar también implica describir en palabras, quitar ambigüedades y convertirlas a código.

Por ejemplo, “saludar tímidamente” debe transformarse en una serie de instrucciones precisas: cuánto se mueve, hacia dónde, cuándo se detiene y a qué velocidad. 

## Funciones y gestos

En el código aparecieron funciones como: 
```
void moverLaManitoTimidamente() {
  if (anguloActual < 90 )
  {
    miServo.write(anguloActual);
    anguloActual++;
    delay(15);
  }
} 
```
y: 
```
void meCohibi() {
  anguloActual--;
  miServo.write(anguloActual);
  delay(15);
} 
```
El servo deja de ser solo un motor. Pasa a actuar como una pequeña “mano” o cuerpo mecánico que puede tener una actitud.

La tecnología empieza a comunicar algo más que funcionamiento: comunica intención, gesto y carácter. 

## Conexión inalámbrica y Adafruit IO

También se trabajó con el envío de información mediante WiFi y Adafruit IO. Mateo compartió un código para enviar la información del potenciómetro al feed de Aarón.

La lógica general era:

potenciómetro → lectura análoga → servo → envío de dato → Adafruit IO

En el código aparecían librerías como: 
```
#include <WiFiS3.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h" 
```
Y la publicación al feed ocurría con: 
```
feedPot.publish((int32_t)lectura);   
viaja por internet hacia un feed 
```
## Enviar solo cuando corresponde

El código también incluía una condición para no enviar información todo el tiempo, sino solo cuando el valor cambiaba y cuando había pasado cierto intervalo. 
```
if (lectura != lecturaAnterior && (ahora - ultimoPublish >= INTERVALO_PUBLISH)) {
  feedPot.publish((int32_t)lectura);
} 
```
Esto introduce una lógica importante: no todo dato debe transmitirse siempre. El sistema puede decidir cuándo comunicar. 

## LDR: cambiar el potenciómetro por luz

Después se conectó un LDR, reemplazando el potenciómetro.

### El cambio es conceptual:

potenciómetro: control directo de una persona
LDR: lectura del ambiente, especialmente de la luz

Con esto, el sistema ya no responde solo a una mano que gira una perilla, sino a una condición externa del entorno.

## Lectura poética

La sesión permite pensar que:

un giro puede volverse movimiento
una luz puede volverse señal
un número puede volverse gesto
un gesto puede viajar por internet
una máquina puede parecer tímida, sensible o expresiva
