# investigaciones individuales

Marcela Zúñiga / marcezm

## Sensor
HC-SR04 Ultrasonic Sensor

## ¿Qué es?

El HC-SR04 es un sensor ultrasónico utilizado para medir distancias mediante ondas de sonido. Funciona enviando un pulso ultrasónico y calculando el tiempo que tarda el eco en regresar al sensor.

Este tipo de sensor es ampliamente utilizado en proyectos de robótica, automatización e Internet de las Cosas (IoT).

---

## Funcionamiento

El sensor posee cuatro pines:

| Pin | Función |
|---|---|
| VCC | Alimentación |
| TRIG | Envía el pulso ultrasónico |
| ECHO | Recibe el eco |
| GND | Tierra |

El sensor envía una onda ultrasónica y mide el tiempo de retorno del sonido para calcular la distancia entre el sensor y un objeto.

---

## Filtrado de información

Uno de los problemas más comunes del HC-SR04 es que puede entregar datos inestables o erróneos debido a:

- interferencias,
- rebotes del sonido,
- superficies irregulares,
- objetos demasiado pequeños.

Para solucionar esto, normalmente se aplican filtros como:

- promedio de múltiples lecturas,
- eliminación de valores extremos,
- retrasos entre mediciones.

Esto permite obtener datos más precisos y estables.

---

## Visualización de datos

Los datos del sensor pueden visualizarse mediante:

- Monitor Serial de Arduino IDE,
- gráficos en tiempo real,
- plataformas IoT como Adafruit IO,
- LEDs o pantallas LCD.

En nuestro proyecto, los datos eran enviados mediante MQTT hacia Adafruit IO.

---

## Problemas comunes

| Problema | Causa |
|---|---|
| Lecturas incorrectas | Rebote ultrasónico |
| Valores inestables | Interferencias |
| No detecta objetos | Distancia fuera de rango |
| Error de código | Bibliotecas faltantes |
| Fallo en Raspberry Pi Pico | Librerías CircuitPython no instaladas |

---

## Proyecto o empresa que utiliza este sensor

Los sensores ultrasónicos similares al HC-SR04 son utilizados en sistemas de estacionamiento de automóviles.

Empresas automotrices como Tesla, Toyota y Hyundai utilizan sensores ultrasónicos para:

- asistencia de estacionamiento,
- detección de obstáculos,
- medición de proximidad,
- automatización de maniobras.

Estos sensores permiten mejorar la seguridad y evitar colisiones durante el movimiento del vehículo.

---

## Aprendizajes obtenidos

Durante el desarrollo del proyecto aprendimos:

- cómo funciona un sensor ultrasónico,
- cómo medir distancias,
- cómo filtrar datos incorrectos,
- cómo integrar sensores en sistemas IoT,
- la importancia de instalar correctamente bibliotecas en CircuitPython,
- la diferencia entre errores reales y advertencias de Visual Studio Code.

## Actuador
LED (Light Emitting Diode)

## ¿Qué es?

Un LED es un actuador electrónico que transforma energía eléctrica en luz.

Se utiliza ampliamente en electrónica debido a su bajo consumo energético, larga duración y facilidad de control mediante microcontroladores como Arduino o Raspberry Pi Pico.

---

## Funcionamiento

El LED funciona permitiendo el paso de corriente eléctrica en un solo sentido.

Posee dos terminales:

| Terminal | Función |
|---|---|
| Ánodo (+) | Entrada de corriente |
| Cátodo (-) | Salida de corriente |

Cuando recibe corriente, el LED emite luz.

---

## Filtrado de información

En sistemas electrónicos, el LED puede utilizarse para representar estados filtrados previamente por el sistema.

Por ejemplo:

- indicar si un sensor detecta movimiento,
- representar conexión WiFi,
- mostrar estados ON/OFF,
- indicar errores o alertas.

En nuestro proyecto, el LED respondía únicamente a datos válidos recibidos mediante MQTT desde Adafruit IO.

---

## Visualización de datos

El LED permite visualizar información de manera rápida y sencilla mediante:

- encendido,
- apagado,
- parpadeo,
- cambios de color (RGB).

En nuestro proyecto:

- botón presionado → LED encendido,
- botón liberado → LED apagado.

---

## Problemas comunes

| Problema | Causa |
|---|---|
| LED no enciende | Polaridad invertida |
| LED quemado | Exceso de corriente |
| Parpadeo incorrecto | Error de programación |
| No responde | Problemas de conexión |
| LED siempre encendido | Error en recepción de datos MQTT |

---

## Proyecto o empresa que utiliza este actuador

Los LEDs son utilizados en prácticamente toda la industria tecnológica.

Empresas como Philips, Samsung y LG utilizan LEDs en:

- pantallas,
- televisores,
- iluminación inteligente,
- señalización electrónica,
- dispositivos IoT.

También son fundamentales en sistemas de automatización y hogares inteligentes.

---

## Aprendizajes obtenidos

Durante el proyecto aprendimos:

- cómo controlar un LED mediante Arduino,
- uso de pines digitales,
- importancia de las resistencias,
- comunicación MQTT para activar actuadores,
- integración entre Raspberry Pi Pico y Arduino,
- solución de errores de cableado y programación.

## Bibliografía
1. Arduino. *Arduino Documentation*.  
https://docs.arduino.cc/

2. Raspberry Pi Foundation. *Raspberry Pi Pico Documentation*.  
https://www.raspberrypi.com/documentation/microcontrollers/

3. CircuitPython. *Official Documentation*.  
https://circuitpython.org/

4. Adafruit IO. *MQTT and Adafruit IO Documentation*.  
https://io.adafruit.com/

5. Components101. *HC-SR04 Ultrasonic Sensor Datasheet*.  
https://components101.com/sensors/ultrasonic-sensor-working-pinout-datasheet
