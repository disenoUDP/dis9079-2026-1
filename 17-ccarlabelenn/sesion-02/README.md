# sesion-02

lunes 16 marzo 2026

## Grupo de trabajo

+ Jesu, Magda, Carla

## Introducción a arduino UNO r4 wifi

usaremos distintas terminos

1. la placa de desarrollo, microcontrolador arduino UNO R4
2. el software, arduino IDE por donde pasaran los codigos a la placa
3. lenguaje de programación, c++, hay bibliotecas y funciones para facilitar aun más el proceso

## Estructura de un codigo de arduino

```cpp
void setup() {

}

void loop() {

}
```

## las funciones principales que utiliza el arduinito son

+ setup(): al inicio del programa para configurar entradas y salidas
+ loop(): despujes del setup se repite en bucle infinito, se ubtiliza para actualizar el estado del progama

# ejemplos de codigoooooo 00

```cpp
// ejemplo00
// imprime la sigla del curso en el monitor serial
// luego espera 1 segundo e imprime :)
// funciona con Arduino Uno R4 WiFi
// marzo 2026
// por montoyamoraga para disenoUDP

// crear instancia de ArduinoLedMatrix
// con nombre pantalla
ArduinoLEDMatrix pantalla;

void setup() {
  // iniciar puerto serial
  Serial.begin(9600);
}

void loop() {
  // imprimir en consola
  Serial.println("dis9079");
  // esperar un segundo
  delay(1000);

  // imprimir en consola
  Serial.println(":)");
  // esperar un segundo
  delay(1000);
}
```

# ejemplo 01 :)

```cpp
// ejemplo00
// imprime la sigla del curso en el monitor serial
// luego espera 1 segundo e imprime :)
// funciona con Arduino Uno R4 WiFi
// marzo 2026
// por montoyamoraga para disenoUDP

// crear instancia de ArduinoLedMatrix
// con nombre pantalla
ArduinoLEDMatrix pantalla;

void setup() {
  // iniciar puerto serial
  Serial.begin(9600);
}

void loop() {
  // imprimir en consola
  Serial.println("dis9079");
  // esperar un segundo
  delay(1000);

  // imprimir en consola
  Serial.println(":)");
  // esperar un segundo
  delay(1000);
}
```
