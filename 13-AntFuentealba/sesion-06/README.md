# sesion-06

lunes 13 abril 2026

Esa clase nos dedicamos a arreglar los errores de la retroalimentación y corregirlos antes del miércoles 15 de abril.

## Sensores capacitivos y Arduino UNO R4

### Componentes básicos

- Resistencia (resistor): regula el flujo de corriente eléctrica dentro del circuito.  
- Condensador / capacitor: componente que almacena energía eléctrica.  
- Capacitancia: propiedad física que depende principalmente del área y la distancia entre elementos conductores.  


### ¿Qué es un sensor capacitivo?

Un sensor capacitivo detecta cambios en la capacitancia cuando un objeto (como la mano) se acerca o toca una superficie.

- No necesita presión física directa  
- Puede detectar materiales conductores y no conductores  
- El cuerpo humano altera el campo eléctrico del sensor  

En términos simples: cuando acercas la mano, el valor eléctrico cambia y el sistema lo interpreta.

### Capacitive Touch (detección táctil)

La detección capacitiva es una tecnología usada en interfaces táctiles modernas.

Permite:
- Detectar contacto humano  
- Reemplazar botones físicos  
- Crear interfaces interactivas  

#### Funcionamiento básico

- Sin contacto → valor bajo  
- Con contacto → valor alto  

Arduino lee estos cambios y los interpreta como eventos.

### Librería utilizada

Se utiliza la librería:

- `Arduino_CapacitiveTouch`

#### Funciones principales

- `CapacitiveTouch(pin)` → define el sensor en un pin  
- `begin()` → inicializa el sensor  
- `read()` → obtiene el valor crudo  
- `isTouched()` → detecta si hay contacto  
- `setThreshold(valor)` → define el umbral de detección  
- `getThreshold()` → consulta el umbral actual  

### Conexión en Arduino UNO R4

Los pines digitales van desde D0 a D13.

Ejemplo de conexión:

- Sensor → pin digital (ej: D0)  
- VCC → 5V  
- GND → GND  

Cada pin puede comportarse de forma distinta, por lo que es importante probar y calibrar.

### ¿Qué ocurre realmente?

1. El sensor genera un campo eléctrico  
2. El cuerpo humano altera ese campo  
3. Cambia la capacitancia  
4. Arduino lee ese cambio  
5. Se interpreta como interacción  

### Lógica de programación

#### Estructura básica

- `setup()` → inicialización (una vez)  
- `loop()` → ejecución continua  

#### Flujo general

1. Inicializar sensor  
2. Leer valor  
3. Comparar con umbral  
4. Detectar contacto  

### Lectura y calibración

El valor del sensor no es fijo, por lo que se debe observar:

- Valores mínimos  
- Valores máximos  
- Promedio  

Esto permite ajustar mejor el umbral (threshold).

#### Estrategia de calibración

- Registrar valores en reposo  
- Registrar valores al tocar  
- Definir un punto intermedio  

### Ejemplo de código básico

```cpp
#include <Arduino_CapacitiveTouch.h>

CapacitiveTouch touchButton = CapacitiveTouch(D0);

void setup() {
  Serial.begin(9600);

  if (touchButton.begin()) {
    Serial.println("Sensor listo");
  } else {
    Serial.println("Error al iniciar");
    while(true);
  }

  touchButton.setThreshold(2000);
}

void loop() {
  int valor = touchButton.read();

  Serial.print("Valor: ");
  Serial.println(valor);

  if (touchButton.isTouched()) {
    Serial.println("Detectado toque");
  }

  delay(100);
}
```

### Ejemplo con calibración

```cpp
int minLectura = 100000;
int maxLectura = 0;

void loop() {
  int valor = touchButton.read();

  if (valor < minLectura) minLectura = valor;
  if (valor > maxLectura) maxLectura = valor;

  Serial.print("Valor: ");
  Serial.println(valor);

  Serial.print("Min: ");
  Serial.print(minLectura);
  Serial.print(" Max: ");
  Serial.println(maxLectura);

  if (valor > (minLectura + maxLectura) / 2) {
    Serial.println("Sobre promedio");
  }

  delay(100);
}
```

### Relación con instrumentos electrónicos

#### Theremin

- Instrumento inventado por :contentReference[oaicite:0]{index=0} en 1920  
- Se toca sin contacto físico  
- Usa campos electromagnéticos  

Control:
- Mano derecha → tono  
- Mano izquierda → volumen  

Funciona con el mismo principio: cambios en capacitancia y campos eléctricos.


#### Stylophone

- Sintetizador portátil  
- Se toca con un lápiz conductor  
- Ejemplo de interfaz electrónica simple  


### Aplicaciones

- Interfaces táctiles  
- Instalaciones interactivas  
- Instrumentos digitales  
- IoT  
- Control de dispositivos  


### Ideas clave

- La capacitancia depende de la distancia y el entorno  
- No es necesario tocar, basta acercarse  
- Cada sensor necesita calibración  
- El comportamiento cambia según condiciones del entorno  
