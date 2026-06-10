# sesion-12

lunes 01 junio 2026

---

# Introducción a Examen (22-06)

Aarón nos presentó la estructura general del examen final y aprovechó la instancia para reflexionar sobre la diferencia entre desarrollar un proyecto técnicamente funcional y desarrollar un proyecto con una intención de diseño clara. La clase estuvo menos enfocada en contenidos técnicos específicos y más orientada a comprender cómo construir una propuesta significativa que pueda convertirse posteriormente en una pieza relevante dentro de un portafolio profesional.

Aarón plantea que durante el semestre hemos aprendido a utilizar distintas tecnologías, como Arduino, Raspberry Pi Pico, comunicación inalámbrica mediante MQTT y plataformas como Adafruit IO. Sin embargo, señala que para el examen final la tecnología no debería ser el punto de partida de la propuesta. En lugar de pensar "voy a hacer algo con Arduino", recomienda comenzar preguntándose ***qué experiencia se quiere generar, qué se quiere comunicar o qué problema se desea abordar.*** La tecnología pasa a ser una herramienta para materializar una idea, no la idea misma.

También menciona que en el futuro, cuando nos enfrentemos a entrevistas laborales o prácticas profesionales, será mucho más interesante presentar un proyecto desde su propósito y significado que desde la lista de componentes utilizados. Explicar un proyecto únicamente como "una Raspberry Pi conectada mediante MQTT" aporta poco valor, mientras que describir la experiencia, el contexto y la intención detrás de la propuesta permite mostrar habilidades de diseño, pensamiento crítico y capacidad de desarrollo.

----

Uno de los conceptos más repetidos durante la clase fue la importancia de entender **el examen como una posible pieza de portafolio.**

Aarón comenta que muchos proyectos académicos terminan olvidados una vez que se obtiene la nota, pero que un buen proyecto puede seguir siendo útil durante años si logra comunicar una idea potente. Por ello recomienda pensar desde ahora cómo se explicaría el proyecto a una persona externa, a una empresa o a un posible empleador.

La pregunta principal no debería ser:

¿Qué componentes estoy usando?

Sino:

***¿Qué estoy proponiendo y por qué vale la pena?***

En este sentido, se nos invita a construir una narrativa o una intención conceptual detrás del proyecto, incluso si se trata de una propuesta sencilla desde el punto de vista técnico.

----

## Uso de arreglos (arrays) como desafío técnico

A nivel técnico, Aarón propone incorporar arreglos dentro del examen.

Explica que un arreglo no debe entenderse como una "reparación", sino como un conjunto ordenado de elementos relacionados entre sí. Utiliza ejemplos cotidianos como los arreglos florales para ilustrar la idea de múltiples elementos organizados dentro de una misma estructura.

En programación, un arreglo permite almacenar varios datos bajo una sola variable.

Por ejemplo:

```c++
int leds[] = {2, 3, 4};
```


En lugar de trabajar con múltiples variables independientes:

```c++
int led1 = 2;
int led2 = 3;
int led3 = 4;
```

La recomendación es utilizar arreglos especialmente cuando se trabaja con múltiples actuadores o sensores similares.

Aarón comenta que uno de los errores más comunes al programar consiste en copiar y pegar bloques de código. Aunque inicialmente parece una solución rápida, genera problemas cuando es necesario corregir errores o realizar modificaciones posteriores.

Por esta razón, propone que al menos uno de los dos extremos del proyecto (sensor o actuador) incorpore arreglos dentro de su implementación. No importa si se trata de dos LEDs, tres motores, varios sensores o múltiples valores relacionados; lo importante es demostrar que se comprende el uso de esta estructura de datos y sus ventajas para organizar información.

--- 

## Condicionales y lógica de programación

Durante la explicación también se mencionan las estructuras condicionales, especialmente las instrucciones if.

Aarón recuerda que gran parte de la programación consiste en tomar decisiones basadas en condiciones.

Por ejemplo:

```c++
if (temperatura > 30) {
    activarVentilador();
}
```

Si la condición se cumple, se ejecuta el bloque de instrucciones. Si no se cumple, el programa continúa normalmente.

A partir de esta lógica es posible controlar luces, motores, alarmas, pantallas y cualquier otro actuador conectado al sistema.

---

## Filtrar información

Un concepto interesante que surge durante la conversación es la idea de ***filtrar información***.

Aarón compara este proceso con un filtro de carbón utilizado para limpiar agua. De la misma forma, los sistemas digitales constantemente reciben grandes cantidades de información, pero no toda resulta útil.

Parte importante del trabajo de diseño consiste precisamente en decidir qué información vale la pena conservar y cuál debe descartarse.

Este principio puede aplicarse tanto a sensores físicos como a fuentes de datos obtenidas desde internet.

----

## Limpieza lid ;)

Se comenta que recientemente se realizó una limpieza importante del laboratorio y se encontraron numerosos sensores que permanecían almacenados desde hace años.

Entre ellos existen sensores capaces de medir:

Humedad de suelo, Temperatura, Presión, Sonido, Tacto, Luz, Distancia, Frecuencia cardíaca, Movimiento, etccc, aguante el lid !!!

***Aarón nos recomienda revisar estos materiales antes de realizar nuevas compras, ya que muchos pueden resultar útiles para los proyectos del examen.***

Mateo como siempre nos apoya personalmente a cada grupo, nos ayuda con ideas para nuestros proyectos y nos comenta sus experiencias y conocimientos, muy seco Mateo tkm

---

## APIs: sensores que viven en internet

Una parte importante de la clase estuvo dedicada a las APIs.

Aarón explica que una API puede entenderse como una forma de comunicación entre programas o servicios digitales. Gracias a ellas, es posible acceder a información disponible en internet de manera automática.

***La idea principal es que una API puede actuar como un sensor virtual.***

En lugar de medir una variable física con un dispositivo electrónico, se consulta información que ya existe en servidores externos.

Por ejemplo:

- Estado del tiempo

- Posición de aviones

- Información astronómica

- Artículos de Wikipedia

- Valores económicos

- Datos de museos

- Información de satélites

- etccc.


Esto amplía enormemente las posibilidades del examen, ya que permite construir proyectos que reaccionan a fenómenos reales sin necesidad de incorporar sensores físicos adicionales.

---

## OpenWeather y datos meteorológicos

Uno de los ejemplos mencionados corresponde a OpenWeather, una API que permite acceder a información climática.

Con ella es posible consultar:

- Temperatura actual, Humedad, Pronósticos, Lluvia, Nubosidad, Condiciones futuras, etc.

Aarón comenta que un proyecto podría reaccionar automáticamente al clima, entregar recomendaciones o modificar su comportamiento según las condiciones ambientales de una ciudad determinada.

---

## Wikipedia como fuente de datos

Otro ejemplo especialmente interesante es la API de Wikipedia.

Esta permite acceder a:

Títulos, Descripciones, Historial de cambios, Idiomas, Imágenes, Primeros párrafos de artículos.

Aarón relata una propuesta artística personal que consistía en detectar cuándo una página pasaba de estar escrita en presente a pasado.

Por ejemplo:

"Es..."

a

"Fue..."

La obra observaba estos cambios y notificaba cuándo algo dejaba de existir o cambiaba de estado.

Más allá de la implementación técnica, el ejemplo sirve para demostrar cómo una fuente de datos aparentemente simple puede convertirse en una propuesta conceptual mucho más profunda.


--- 

## La importancia de la documentación

Otro punto relevante es la ***documentación del proyecto.***

Aarón menciona que las demostraciones en vivo siempre presentan riesgos, especialmente cuando dependen de conexiones inalámbricas, internet o sistemas distribuidos.

Se considera muy valioso complementar el proyecto con evidencia documentada mediante videos.

La documentación permite mostrar que el sistema funcionó correctamente incluso si durante la presentación aparecen dificultades técnicas.

Además, sirve posteriormente para integrar el proyecto dentro del portafolio personal.

---

# Grupo Examen -> Grupo 4 + Isidora Pérez

## Interacción entre grupos vía Discord

Descripción inicial de nuestro proyecto:

Grupo 04: Queremos lograr una exploración sobre la capacidad de las tecnologías inalámbricas para transportar señales humanas más allá del cuerpo que las origina. El proyecto captura el ritmo cardíaco de una persona y lo transforma en una presencia remota, permitiendo que sus pulsaciones sean observadas en otro lugar en tiempo real. A través de esta conexión invisible, los latidos dejan de ser una experiencia íntima para convertirse en un lenguaje compartido entre dispositivos, espacios y personas. La propuesta reflexiona sobre cómo la información biológica puede viajar, ser representada y generar nuevas formas de percepción y vínculo mediante redes inalámbricas.

- Aarón nos sugiere computación inalámbrica en vez de tecnologías inalámbricas

- Aarón nos pregunta lo siguiente: van a procesar esos datos de pulso? van a enviar el pulso directamente? o un resumen en latidos por minuto?

   - Resp: Resumen en latidos por minuto

- Jesús Miranda nos pregunta: ¿qué pasa en este caso en el dispositivo receptor? ya que en el párrafo dice que los latidos "son observados" pero no queda claro si es una pantalla LED, sonido, ¿cómo se ve esa presencia remota?

    - Resp: Estamos considerando el uso de la pantalla led del arduino o anexar una pantalla LCD para la visualización de los datos, que en este caso son las pulsaciones por minuto

Estas interaccones nos sirvieron para recibir feedback de otras perspectivas e intercambiar dudas que uno puede tenerlas claras pero el resto no necesariamente.

----

### Enfoque Conceptual del proyecto

El cuerpo mantiene un diálogo constante con el mundo que lo rodea. Cada emoción, esfuerzo, sorpresa o momento de calma deja una huella física que muchas veces pasa desapercibida. Entre estas señales, el ritmo cardíaco constituye una manifestación silenciosa pero permanente de nuestra relación con el entorno, reflejando cambios internos que ocurren incluso antes de que seamos plenamente conscientes de ellos.

Este proyecto explora la posibilidad de hacer visible aquello que normalmente permanece oculto. A partir de la captura de la frecuencia cardíaca de una persona, se propone una experiencia que traduce una señal biológica en una manifestación perceptible a distancia, permitiendo que un estado corporal íntimo pueda ser observado, interpretado y compartido mediante medios tecnológicos. De esta manera, el proyecto busca reflexionar sobre las nuevas formas de conexión que emergen cuando los datos del cuerpo abandonan su dimensión privada y se convierten en un lenguaje capaz de atravesar el espacio.

### Enfoque Técnico

El proyecto consiste en el desarrollo de un sistema distribuido capaz de medir, transmitir y visualizar la frecuencia cardíaca de una persona en tiempo real. Para ello, se utiliza un sensor biométrico conectado a un microcontrolador que procesa la señal obtenida y calcula los latidos por minuto (BPM). Esta información es enviada mediante comunicación inalámbrica hacia un segundo dispositivo, encargado de recibir los datos y transformarlos en una representación visual accesible para el usuario.

A través de esta implementación se ponen en práctica conceptos relacionados con sensores, procesamiento de señales, transmisión de datos, comunicación entre dispositivos y visualización de información. El resultado es una plataforma que conecta una variable fisiológica del cuerpo humano con un sistema digital capaz de hacer visible un fenómeno que normalmente permanece invisible, permitiendo observar en tiempo real las variaciones del ritmo cardíaco y su comportamiento frente a distintos estímulos.

Seguimos avanzando y latiendo...
