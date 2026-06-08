# sesion-07

lunes 20 abril 2026

# Sensores, servos y comunicación IoT con Arduino y Adafruit IO

El objetivo de las actividades desarrolladas fue comprender el flujo completo de un sistema interactivo: capturar información del entorno mediante sensores, procesarla utilizando un microcontrolador y utilizar esos datos para generar una respuesta física local o remota. La lógica utilizada corresponde a la misma base presente en muchos sistemas de automatización e Internet de las Cosas (IoT).

El flujo general trabajado durante la clase fue:

```text
Sensor
↓
Lectura del microcontrolador
↓
Procesamiento de datos
↓
Comunicación Wi-Fi / MQTT
↓
Nube (Adafruit IO)
↓
Dispositivo receptor
↓
Actuador (Servo)
↓
Movimiento físico
```

En términos simples, el sistema toma un fenómeno físico (movimiento de una perilla, cantidad de luz, posición, etc.), lo transforma en un dato digital y luego utiliza ese dato para ejecutar una acción determinada.

---

## Sensores analógicos

Los sensores son dispositivos capaces de detectar cambios físicos del entorno y convertirlos en señales eléctricas que un sistema puede interpretar. Existen distintos tipos de sensores, pero en estas actividades se trabajó principalmente con sensores analógicos.

Los sensores analógicos generan valores continuos dentro de un rango determinado. A diferencia de sensores digitales, que entregan únicamente estados definidos como encendido/apagado o verdadero/falso, los sensores analógicos permiten obtener múltiples valores intermedios.

Ejemplo:

```text
Sensor digital:

0 → apagado
1 → encendido


Sensor analógico:

0 → 1023
```

Esto permite obtener información más precisa y generar respuestas graduales.

---

## Potenciómetro

El potenciómetro es un componente electrónico que permite variar una resistencia interna mediante una perilla o eje giratorio. Al modificar esa resistencia cambia el voltaje entregado en su salida y ese cambio puede ser leído por el Arduino.

Su función principal en esta experiencia fue actuar como una entrada física controlable por el usuario.

Conexión:

```text
5V ------ Potenciómetro ------ GND
                  |
                  |
                 A0
```

Las tres terminales cumplen distintas funciones:

* Extremo 1 → alimentación positiva (5V)
* Terminal central → salida analógica
* Extremo 2 → tierra (GND)

La lectura generada normalmente se encuentra dentro del rango:

```text
0 → 1023
```

Interpretación:

```text
Giro mínimo → valor cercano a 0

Giro máximo → valor cercano a 1023
```

El potenciómetro se utiliza ampliamente en sistemas electrónicos debido a que permite representar acciones humanas mediante valores numéricos.

Aplicaciones comunes:

* Control de volumen
* Regulación de intensidad
* Ajuste de velocidad
* Interfaces físicas de usuario

---

## LDR (Light Dependent Resistor)

El LDR o fotorresistor es un sensor cuya resistencia cambia dependiendo de la cantidad de luz que recibe.

Su comportamiento se basa en un principio simple:

```text
Más luz
↓
Menor resistencia


Menos luz
↓
Mayor resistencia
```

A través de esta variación el sistema puede detectar condiciones del entorno relacionadas con iluminación.

Aplicaciones frecuentes:

* Alumbrado automático
* Sensores ambientales
* Domótica
* Sistemas inteligentes

Sin embargo, durante la práctica se observó un problema importante: las lecturas obtenidas mediante LDR pueden cambiar constantemente debido a pequeñas variaciones del ambiente.

Ejemplo:

```text
350
351
349
352
350
351
```

Aunque las diferencias parecen pequeñas, pueden generar comportamientos erráticos cuando esos datos controlan motores o son enviados continuamente a internet.

---

## Procesamiento y estabilización de datos

Uno de los conceptos más enfatizados fue que los sensores no siempre entregan información perfectamente estable. Los datos pueden contener ruido o fluctuaciones que producen respuestas inesperadas.

Por esta razón se mencionó la necesidad de "domesticar" los sensores antes de utilizar sus datos.

Esto consiste en procesar la información antes de enviarla o utilizarla.

Algunas estrategias utilizadas:

**Promediado**

Consiste en tomar varias lecturas y calcular un valor promedio.

Ejemplo:

```text
350
352
349
351
348

Promedio = 350
```

---

**Media móvil**

Consiste en calcular el promedio únicamente de las últimas lecturas obtenidas.

Permite suavizar cambios bruscos.

---

**Umbrales**

Solo se envía un dato cuando el cambio supera cierto límite.

Ejemplo:

```text
Si cambia más de 20 unidades
↓
Enviar información
```

---

**Control de frecuencia**

Evita transmitir datos continuamente.

Por ejemplo:

```cpp
intervalPublish=500;
```

Significa:

```text
Enviar datos cada 500 milisegundos
```

Estas estrategias permiten disminuir errores y evitar sobrecarga en la comunicación.

---

## Protoboard

La protoboard es una herramienta utilizada para crear circuitos electrónicos temporales sin necesidad de soldar componentes.

Internamente posee conexiones metálicas ocultas que permiten distribuir alimentación y señales eléctricas.

Estructura:

```text
+ ---------------- +

- ---------------- -

A B C D E    F G H I J
A B C D E    F G H I J
```

Características importantes:

* A–E están conectadas internamente.
* F–J están conectadas internamente.
* Existe una separación central.
* Las líneas laterales distribuyen alimentación.

El uso de la protoboard permite modificar diseños rápidamente y facilita el proceso de experimentación.

---

## Lectura analógica mediante Arduino

Arduino posee entradas analógicas destinadas a leer voltajes variables generados por sensores.

Entradas típicas:

```cpp
A0
A1
A2
A3
```

La función utilizada es:

```cpp
analogRead(A0);
```

Esta función convierte un voltaje en un valor numérico.

Rango:

```text
0 → 1023
```

Ejemplo:

```cpp
int lectura;

void setup(){

Serial.begin(9600);

}

void loop(){

lectura=analogRead(A0);

Serial.println(lectura);

}
```

El monitor serial permite visualizar los datos en tiempo real y verificar el correcto funcionamiento del circuito.

---

## Servo

El servo es un motor especializado que funciona mediante control de posición angular.

A diferencia de un motor tradicional que recibe velocidad, el servo recibe una posición específica.

Comparación:

**Motor DC**

```text
Entrada → velocidad
```

**Servo**

```text
Entrada → posición
```

Ejemplo:

```text
0° → extremo izquierdo

90° → centro

180° → extremo derecho
```

Aplicaciones:

* Robótica
* Automatización
* Brazos mecánicos
* Sistemas interactivos

---

## Conexión del servo

Los servos normalmente incluyen tres cables:

| Cable            |           Función |
| ---------------- | ----------------: |
| Rojo             | Alimentación (5V) |
| Negro/Café       |      Tierra (GND) |
| Amarillo/Naranja |         Señal PWM |

Ejemplo:

```text
Servo

Rojo -------- 5V
Negro ------- GND
Amarillo ---- Pin 9
```

Es fundamental compartir tierra entre todos los dispositivos:

```text
Arduino GND
      │
      │
Servo GND
```

Sin una referencia común las señales pueden interpretarse incorrectamente.

---

## Conversión de valores mediante map()

Un problema observado es que el rango del potenciómetro y el rango del servo son distintos.

Potenciómetro:

```text
0 → 1023
```

Servo:

```text
0° → 180°
```

Para solucionar esto se utiliza la función:

```cpp
angulo=map(lectura,0,1023,0,180);
```

La función toma un valor de un rango y lo transforma proporcionalmente a otro.

Proceso:

```text
Lectura sensor
↓
Conversión
↓
Ángulo equivalente
↓
Movimiento servo
```

---

## Biblioteca Servo

Arduino incluye una biblioteca que simplifica el control del motor:

```cpp
#include <Servo.h>
```

Funciones principales:

Asignar pin:

```cpp
miServo.attach(9);
```

Mover servo:

```cpp
miServo.write(angulo);
```

Código utilizado:

```cpp
#include <Servo.h>

Servo miServo;

int lectura;
int angulo;

void setup(){

    miServo.attach(9);

}

void loop(){

    lectura=analogRead(A0);

    angulo=map(lectura,0,1023,0,180);

    miServo.write(angulo);

    delay(15);

}
```

---

## Comunicación IoT con Adafruit IO y MQTT

Una vez comprobado el funcionamiento local del sistema, el siguiente paso fue enviar la información a internet.

Flujo:

```text
Potenciómetro
↓
Arduino
↓
Wi-Fi
↓
MQTT
↓
Adafruit IO
↓
Feed
```

### MQTT

MQTT (*Message Queue Telemetry Transport*) es un protocolo diseñado para dispositivos IoT.

Características:

* Bajo consumo
* Liviano
* Comunicación rápida
* Bajo uso de recursos

---

### Feed

Un feed corresponde a un canal donde se almacenan datos enviados por sensores.

Ejemplo:

```text
potenciometro01
```

Cada grupo debía trabajar con un feed propio.

Buenas prácticas:

```text
grupo_1
potenciometro01
sensor-pot
```

Evitar:

```text
grupo😂
potenciómetro🔥
sensor#
```

---

## Seguridad de credenciales

Se enfatizó la importancia de proteger información privada.

Nunca publicar:

* usuarios
* claves
* tokens
* archivos de configuración

No realizar:

```cpp
USER="usuario_real"

KEY="clave_real"
```

en:

* GitHub público
* Discord público
* redes sociales

---

## Flujo completo del proyecto

Sistema local:

```text
Potenciómetro
↓
Arduino
↓
map()
↓
Servo
```

Sistema IoT:

```text
Potenciómetro local
↓
Arduino emisor
↓
Adafruit IO
↓
Arduino receptor
↓
map()
↓
Servo remoto
```
