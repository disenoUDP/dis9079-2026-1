# sesion-06

lunes 13 abril 2026

# Idea general

En esta sesión seguimos trabajando la idea de que la solemne 02 no tenía que quedarse solo en una solución técnica, sino que debía construir una poética a partir de las conexiones inalámbricas. La tecnología ya no aparece solo como herramienta funcional, sino como un medio para generar una experiencia, un gesto o una relación sensible.
Dentro de ese proceso revisamos el uso de touch capacitivo con Arduino Uno R4, pensando el toque como una forma de activar algo sin apretar un botón mecánico. Eso cambia bastante la cualidad de la interacción: ya no es solo presionar, sino entrar en contacto. 

## Idea de poética

Lo central de esta sesión fue pensar que una interacción no vale solo porque funcione, sino por cómo se siente, qué comunica y qué relación produce.

En ese sentido, el toque tiene una carga distinta a un botón común:

**es más sutil
es más corporal
se siente más cercano
puede activar ideas de presencia, intimidad, cuidado o vínculo**

Entonces, para la solemne 02, la conexión inalámbrica puede pensarse no solo como transmisión de datos, sino como una forma de que un gesto mínimo viaje y aparezca transformado en otro lugar.

## Sensor capacitivo 

Los sensores capacitivos reaccionan ante materiales conductores y no conductores cuando se acercan o tocan una superficie activa. Lo que detectan no es una presión mecánica, sino un cambio en la capacitancia.

La detección capacitiva se usa mucho en dispositivos táctiles porque permite reconocer la presencia o ausencia de un cuerpo, como un dedo humano, sin necesidad de un switch físico tradicional.
 
<img src="./imagenes/capacitivosensor.jpg" width="50%">  

## Componentes y concepto base

una base más electrónica para entender esto:

**resistencia
condensador / capacitor
la capacidad eléctrica o capacitancia**

La idea importante es que en este tipo de sensor lo que cambia es justamente la capacitancia. Cuando una persona toca o se acerca, modifica las condiciones eléctricas del sistema y eso puede ser leído por la placa. 

## Biblioteca usada 

Para trabajar esto usamos la librería:
 
```
#include <Arduino_CapacitiveTouch.h>
```

Esta biblioteca permite crear y leer entradas táctiles capacitivas en placas compatibles como el Arduino Uno R4.

## Código revisado

El código base que vimos fue este:

```
#include <Arduino_CapacitiveTouch.h>

// importar biblioteca
#include "Arduino_CapacitiveTouch.h"

// existe un constructo
// del tipo CapacitiveTouch
// que se llama touchButton, ese nombre es de fantasia
// esta conectada a la patita D0
CapacitiveTouch touchButton = CapacitiveTouch(D0);

// valor de lectura
int valorLectura = 0;

void setup() {
  Serial.begin(9600);

  if(touchButton.begin()){
    Serial.println(":) yay");
  } else {
    Serial.println("oh no :'( snif");
    while(true);
  }

  touchButton.setThreshold(2000);
}

void loop() {
  valorLectura = touchButton.read();
  Serial.print("Valor crudo: ");
  Serial.println(valorLectura);

  if (touchButton.isTouched()) {
    Serial.println("hubo contacto");
  }

  delay(100);
}
```

## Qué significa cada parte importante 
 
 ```
 CapacitiveTouch(uint8_t pin)
```
Sirve para crear el sensor táctil capacitivo y decir en qué pin está conectado 
En este caso:
```
CapacitiveTouch touchButton = CapacitiveTouch(D0);
```
significa que la lectura táctil se hará desde el pin D0.
 

```
begin()
```
Inicializa el hardware y deja listo el sistema para empezar a leer. 


Devuelve:
true si todo funciona bien
false si hubo un problema
Por eso en el código se usa dentro de un if, para verificar si la inicialización resultó o no. 


```
read()
```
Lee el valor crudo del sensor.
```
valorLectura = touchButton.read();
```
Ese valor numérico permite observar cuánto cambia la lectura según haya o no contacto. 


```
isTouched()
```
Detecta si el sensor está siendo tocado.
```
if (touchButton.isTouched()) {
  Serial.println("hubo contacto");
}
```
Acá el sistema ya no entrega solo un número, sino una interpretación: si hubo toque o no.


```
setThreshold(int threshold)
```
Define el umbral mínimo para considerar que realmente hay contacto.
```
touchButton.setThreshold(2000);
```
Ese número no es universal. Depende del montaje, del ambiente, del cuerpo, de la humedad y de cómo esté armado el sistema. Por eso el umbral puede requerir pruebas y ajuste. 


## Qué puede afectar la lectura

La lectura capacitiva no es fija ni totalmente estable. Puede cambiar según:

**el clima
la humedad
el material que se toca
la longitud del cable
el cuerpo de la persona
el entorno eléctrico**

Por eso este tipo de sensor tiene algo más sensible y variable que un botón tradicional. Y esa misma inestabilidad puede ser parte interesante de su carácter poético.

## Relación con el proyecto

Esto se puede integrar muy bien a la lógica de las conexiones inalámbricas. El contacto puede ser el primer gatillante del sistema.

**Flujo posible:**

cuerpo toca cable o superficie → Arduino detecta touch → se activa una señal → se manda mensaje inalámbrico → otro dispositivo responde

Ahí el toque deja de ser solo una lectura técnica y pasa a ser una acción cargada de sentido. Un gesto mínimo puede activar una respuesta visual, sonora o textual en otro lugar.
