# sesion-06

lunes 13 abril 2026

---

Esta clase vimos sensores capacitivos. Aprendimos cómo el Arduino R4 WiFi puede detectar si alguien está tocando o acercando el dedo a un pin, sin necesitar un botón físico. El principio detrás de todo eso es la **capacitancia**.

---

## Capacitancia

Según Gemini: la capacitancia es la capacidad de un componente para almacenar energía en forma de carga eléctrica por unidad de voltaje aplicado. Se define con la fórmula `C = Q/V` y se mide en Faradios (F). El valor depende de la estructura física del componente: el área de las placas y el material aislante entre ellas.

![sensor capacitivo](./imagenes/capacitive.webp)

- **Resistor:** regula el flujo de corriente eléctrica
- **Capacitor / Condensador:** almacena carga eléctrica
- **Capacitancia:** propiedad que depende del área y la distancia

---

## Referencia: Theremin

El **Theremin** es el primer instrumento musical electrónico de la historia, inventado en 1920 por Leon Theremin. Se toca sin contacto físico: dos antenas crean un campo electromagnético y las manos del músico lo alteran al moverse en el aire, controlando el tono con una mano y el volumen con la otra.

![theremin](./imagenes/theremin.jpeg)

Theremin usa exactamente el mismo principio que el sensor capacitivo, detectar la presencia de algo conductor (en ese caso la mano humana) midiendo cambios en el campo eléctrico, sin que haya contacto directo. Es básicamente lo mismo que hace el Arduino, pero inventado en 1920.

---

## Arduino UNO R4 WiFi: pines capacitivos

No todos los pines del Arduino soportan lectura capacitiva, solo algunos. Esta es la tabla de compatibilidad:

| Pin Arduino | Touch Sensor Channel (TS#) |
|-------------|---------------------------|
| D0          | 9                         |
| D1          | 8                         |
| D2          | 13                        |
| D3          | 34                        |
| D6          | 12                        |
| D8          | 11                        |
| D9          | 2                         |
| D11         | 7                         |
| D12         | 6                         |
| A1 (D15)    | 21                        |
| A2 (D16)    | 22                        |

---

## Librería: Arduino_CapacitiveTouch

Para leer el sensor se usa la librería `Arduino_CapacitiveTouch`. Sus funciones principales son:

- `CapacitiveTouch(pin)` : crea el sensor y le dice en qué pin está
- `begin()` : inicializa el hardware. Devuelve `true` si todo está bien, `false` si algo falló
- `read()` : entrega el valor crudo del sensor
- `isTouched()` : devuelve `true` si detecta que hay contacto
- `setThreshold(valor)` : define el umbral mínimo para considerar que hubo toque
- `getThreshold()` : consulta el umbral actual

---

## Códigos vistos en clase

### Código 1

```cpp
// referencia: https://docs.arduino.cc/tutorials/uno-r4-wifi/touch/
// por montoyamoraga para disenoUDP

#include "Arduino_CapacitiveTouch.h"

CapacitiveTouch touchButton = CapacitiveTouch(D0);

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

El `setThreshold(2000)` define desde qué valor en adelante se considera un toque real. El valor exacto depende del ambiente, del cable, del pin, y de un montón de factores. ¿por qué 2000?: hay que calibrarlo según cada situación.

---

### Código 2

Para no adivinar el umbral, este código va aprendiendo los valores mínimos y máximos que entrega el sensor durante la ejecución

```cpp
#include "Arduino_CapacitiveTouch.h"

CapacitiveTouch touchButton = CapacitiveTouch(D0);

int valorLectura = 0;
int minLectura = 100000;  // parte en el peor caso posible
int maxLectura = 0;

void setup() {
  Serial.begin(9600);

  if (touchButton.begin()) {
    Serial.println(":) yay");
  } else {
    Serial.println("oh no :'( snif");
    while (true);
  }

  touchButton.setThreshold(2000);
}

void loop() {
  valorLectura = touchButton.read();

  if (valorLectura < minLectura) {
    minLectura = valorLectura;
  }
  if (valorLectura > maxLectura) {
    maxLectura = valorLectura;
  }

  Serial.print("Valor crudo: ");
  Serial.println(valorLectura);
  Serial.print("min: ");
  Serial.print(minLectura);
  Serial.print(", max: ");
  Serial.println(maxLectura);

  if (touchButton.isTouched()) {
    Serial.println("hubo contacto");
  }

  if (valorLectura > (minLectura + maxLectura) / 2) {
    Serial.println("sobre el promedio, dab");
  }

  delay(100);
}
```

## Resultado

![sensor capacitivo en acción](./imagenes/magia.gif)
