# investigaciones individuales

Renata De Los Ángeles Arévalo Urra / github

## Sensor

# Sensor Ultrasónico HC-SR04

El sensor ultrasónico HC-SR04 es un dispositivo electrónico diseñado para medir distancias mediante el uso de ondas ultrasónicas. Su funcionamiento se basa en un principio similar al utilizado por algunos animales, como murciélagos y delfines, los cuales utilizan ondas sonoras para orientarse y reconocer objetos en su entorno.

Actualmente este sensor es ampliamente utilizado en robótica, sistemas de automatización, sensores de estacionamiento, detección de obstáculos y proyectos IoT debido a su buena precisión, facilidad de uso y bajo costo. Una de sus principales ventajas es que puede realizar mediciones sin necesidad de contacto físico con el objeto.

Durante la investigación resultó interesante observar que una tecnología basada en algo tan cotidiano como el sonido puede utilizarse para calcular distancias con bastante precisión.

## Funcionamiento

El HC-SR04 posee dos transductores circulares ubicados en la parte frontal:

Emisor ultrasónico.

Receptor ultrasónico.

El proceso de funcionamiento ocurre en varias etapas:

1. Emisión del pulso
   
El microcontrolador envía una señal eléctrica al pin Trigger durante aproximadamente 10 microsegundos.

2. Generación de ondas ultrasónicas
   
El sensor emite ocho pulsos de sonido a una frecuencia aproximada de 40 kHz, frecuencia que está fuera del rango audible humano.

3. Rebote de la señal
   
Cuando las ondas encuentran un objeto, rebotan y vuelven hacia el receptor.

4. Cálculo de distancia
   
El sensor mide cuánto tiempo tarda la señal en regresar y utiliza la velocidad del sonido para calcular la distancia:

Distancia = (Tiempo × velocidad del sonido) ÷ 2

La división entre dos se realiza porque la señal realiza un recorrido de ida y vuelta.

Al revisar este proceso llamó la atención que el sensor realmente no "ve" los objetos; en realidad calcula tiempos extremadamente pequeños y los transforma en distancia.


## Especificaciones técnicas

Algunas características importantes del HC-SR04 son:

- Voltaje de funcionamiento: 5V
  
- Corriente aproximada: 15 mA
  
- Frecuencia ultrasónica: 40 kHz
  
- Distancia mínima: 2 cm
  
- Distancia máxima: 400 cm
  
- Precisión aproximada: ±3 mm
  
- Ángulo de detección: menor a 15°
  
- Pines:
  
  - VCC
    
  - Trigger
    
  - Echo
    
  - GND

Estas características permiten que el sensor pueda integrarse fácilmente con plataformas como Arduino, Raspberry Pi Pico y otros sistemas electrónicos.


## Filtrado y procesamiento de información

Las mediciones realizadas por el HC-SR04 pueden presentar pequeñas variaciones debido a factores externos.

Por ejemplo:

Lecturas obtenidas:

- 48 cm
  
- 52 cm
  
- 49 cm
  
- 54 cm
  
- 50 cm

Aplicando promedio:

(48 + 52 + 49 + 54 + 50) ÷ 5 = 50,6 cm

El sistema utilizaría un valor más estable en lugar de trabajar con todas las mediciones individualmente.

En comunidades de desarrollo se observa frecuentemente que los usuarios reportan lecturas inesperadas o saltos repentinos de valores, por lo que suelen utilizar filtros por promedio o mediana para mejorar estabilidad.

Durante esta parte de la investigación resultó interesante descubrir que obtener un dato no siempre significa obtener un resultado completamente preciso; muchas veces es necesario procesar la información antes de utilizarla.


## Problemas y limitaciones

Aunque el HC-SR04 presenta buena precisión, existen algunas situaciones que pueden afectar su funcionamiento:

- Superficies blandas pueden absorber las ondas sonoras.
  
- Objetos pequeños pueden ser difíciles de detectar.
  
- Cambios de temperatura afectan la velocidad del sonido.
  
- Superficies inclinadas pueden desviar el rebote.
  
- Múltiples sensores cercanos pueden interferir entre sí.

Por ejemplo, una pared plana generalmente entrega resultados muy estables, mientras que una tela o una superficie irregular puede producir errores.

### Aplicaciones reales

El HC-SR04 posee aplicaciones en distintas áreas:

- Robots evitadores de obstáculos.
  
- Sensores de estacionamiento.
  
- Medidores de nivel de agua.
  
- Sistemas industriales.
  
- Automatización doméstica.
  
- Alarmas y sistemas de seguridad.

Lo interesante es que un mismo principio puede encontrarse en situaciones muy diferentes: desde un pequeño robot educativo hasta sistemas utilizados diariamente por miles de personas.


## Proyecto chileno: Sistema de ayuda al estacionamiento con sensor HC-SR04

El proyecto “Sensor por proximidad para autos” fue desarrollado por Camilo Caroca como trabajo académico para la asignatura Interacción y Performatividad en la Pontificia Universidad Católica de Valparaíso durante el año 2020. El objetivo principal fue construir un sistema de ayuda al estacionamiento capaz de advertir a un conductor sobre la cercanía de obstáculos y reducir errores al estacionar.

Lo interesante es que el proyecto buscó resolver una situación cotidiana mediante componentes simples y accesibles. La idea consistía en replicar el principio utilizado por sensores de estacionamiento presentes en muchos vehículos modernos, pero utilizando una implementación de menor costo basada en Arduino y el sensor ultrasónico HC-SR04.

### Componentes utilizados

El sistema fue construido utilizando:

- Arduino Uno R3
  
- Sensor ultrasónico HC-SR04

- Piezo eléctrico (buzzer)

- LED

- Protoboard

- Caja plástica para integrar el sistema

Todos los componentes fueron integrados en una estructura compacta para formar un prototipo funcional.

### Funcionamiento detallado

El funcionamiento comienza cuando el sensor HC-SR04 emite una onda ultrasónica mediante el pin Trigger. Esa onda viaja por el aire y, si encuentra un obstáculo, rebota y vuelve al receptor del sensor mediante el pin Echo. El sistema calcula el tiempo que tarda la señal en regresar y transforma esa información en una distancia.

Posteriormente, el Arduino procesa esos datos y ejecuta respuestas según la proximidad detectada:

Objeto lejano → sin advertencia o aviso leve.

Objeto a distancia media → aumento gradual de alerta.

Objeto muy cercano → señales luminosas y sonoras más intensas.

Este funcionamiento es muy parecido al utilizado por sensores reales de estacionamiento en vehículos. La diferencia principal es que en automóviles comerciales normalmente se utilizan varios sensores simultáneamente para ampliar el rango de detección.

### Ventajas observadas en el proyecto

El desarrollo presentó varias ventajas:

- Bajo costo de implementación.
  
- Componentes fáciles de conseguir.
  
- Programación relativamente sencilla.
  
- Posibilidad de ampliar funciones futuras.

Por ejemplo, el sistema podría complementarse con:

una pantalla LCD;
conexión a aplicaciones móviles;
registro de datos;
indicadores visuales adicionales.

Durante la revisión del proyecto llamó la atención cómo un sistema relativamente simple logra reproducir una función que normalmente se asocia a tecnologías más complejas. Además, permite visualizar de manera práctica cómo un sensor puede interpretar información física y transformarla en respuestas automáticas.



## Actuador

## Bibliografía

Sensor

