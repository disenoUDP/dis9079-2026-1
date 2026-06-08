# sesion-12

lunes 01 junio 2026

---

Ramo Aprobado!

Hemos aprendido distintos lenguajes de programación!

   - Circuit Python
   - Python
   - C++

> _EJECUTAR_ es una palabra muy violenta, intentar no usarla.

Aarón nos mostró el libro que está escribiendo <https://github.com/disenoUDP/apuntes-pensamiento-computacional>

---

## Desafío para el examen:
- Que uno de los dos lados (enviar o recibir) que esté hecho con un arreglo (_array_)
- Video del funcionamiento entre facultades y demostracion en vivo en la sala.

### Hoy
Definir que es lo que vamos a enviar y recibir. Usar una capa de abstracción mayor y menos técnica.

- ¿Qué queremos hacer?
- ¿Qué queremos transmitir?

Trabajar en el lenguaje.

<https://yeseul.com>
<https://yeseul.com/Slow-Dimming-Study-Rice-Dimmer>

## API

Según Gemini: Una API (por sus siglas en inglés, Application Programming Interface o Interfaz de Programación de Aplicaciones) es un conjunto de reglas y protocolos que permite que diferentes aplicaciones de software se comuniquen y compartan información entre sí. Funciona como un puente o traductor entre dos sistemas independientes, permitiendo que uno use las funciones o datos del otro sin necesidad de conocer su código interno.

<https://github.com/public-apis/public-apis>

Investigar APIS!! puede ser interesante.

----

Pienso en ocupar Touch Designer, quizas ocupar alguna API o algún sensor conectado a una rapsberry, y que estos datos lleguen a un arduino que estrá conectaado al pc, esta info le llegará a Touch designer y afectará las visuales.

Referentes:

[![Video 1](https://img.youtube.com/vi/X7gKUreB_QY/maxresdefault.jpg)](https://www.youtube.com/shorts/X7gKUreB_QY)

[![Video 2](https://img.youtube.com/vi/TW8g6cFRIf4/maxresdefault.jpg)](https://www.youtube.com/shorts/TW8g6cFRIf4)

[![Video 3](https://img.youtube.com/vi/3t0iMW1m9ro/maxresdefault.jpg)](https://www.youtube.com/watch?v=3t0iMW1m9ro)

[![Video 4](https://img.youtube.com/vi/ZQyavSANa14/maxresdefault.jpg)](https://www.youtube.com/watch?v=ZQyavSANa14)

### Nuestro Proyecto

Queremos explorar el ruido de la facultad y visualizarlo. Para esto ocuparemos dos Rasberry Pi Pico W, cada una conectada a un sensor de sonido (micrófono), que serán colocadas en distintas partes de la facultad.

Estas Raspberry, cada una conectada a su propio Feed en Adafruit IO, enviarán información a un feed en conjunto, el cual enviará estos datos a un Arduino UNO R4 mínima Wifi, que estará conectado a Touch designer, lo que hará que estos sonidos detectados modifiquen las visuales en vivo.

---

#### "¿Cómo presenciamos el "habitar" de los espacios a través del sonido presente en ambas facultades?"

Este proyecto surge de esa pregunta. Más que medir niveles de ruido, nos interesa observar las huellas sonoras que dejan las personas al ocupar un lugar. Cada conversación, paso, risa, momento de estudio o silencio forma parte de una identidad acústica que cambia constantemente y que habla de cómo se vive y se comparte un espacio.

Para explorar esta idea, instalaremos sensores de sonido en dos edificios de la facultad. Los sonidos capturados serán traducidos en una visualización generativa en tiempo real, donde el movimiento, las formas y los colores responderán a la actividad sonora de cada lugar. De esta manera, aquello que normalmente percibimos solo con el oído podrá manifestarse visualmente frente a nosotros.

La propuesta busca hacer visible una dimensión cotidiana que suele pasar desapercibida: la manera en que habitamos los espacios y cómo nuestra presencia los transforma. A través de la relación entre sonido e imagen, la visualización funcionará como un retrato vivo de ambos lugares.

#### Arreglado

### Grupo 02. Pa-Pa's
Nombre del Proyecto: Acu-Visual.

#### "¿Cómo presenciamos el "habitar" de los espacios a través del sonido presente en los edificios de la FAAD?"

Nos interesa observar en vivo las huellas sonoras (conversaciones, pasos, risas, silencios, etc) que dejan las personas al ocupar o transitar un lugar (espacio físico). Esta "identidad acústica" cambiante nos habla de cómo se vive y se comparte un espacio . Estos registros en tiempo real son la materia prima para la producción de visualizaciones experimentales producidas en Touchdesigner,

La dimensión material del proyecto abarca el uso de 2 placas rapsberry pi pico 2W, cada una con un "Sensor de Sonido (LM393)" que reúne información y la sube en 2 feeds en Adafruit IO. Cada uno de estos módulos se encuentran ubicados en uno de los edificios de la Facultad de Artes, Arquitectura y Diseño (República 180 y Salvador Sanfuentes 2221). 

Por otra parte, el computador (o el Arduino) recibirá dichos datos para posteriormente entregarlos a Touchdesigner. La visualización generativa en tiempo real posee variables como el movimiento, las formas y los colores que responden a la actividad sonora de cada lugar.

De esta manera, aquello que normalmente percibimos solo con el oído podrá manifestarse visualmente frente a nosotros.

Buscamos hacer visible una dimensión cotidiana que suele pasar desapercibida: la manera en que habitamos los espacios y cómo nuestra presencia los transforma a través de la relación entre sonido e imagen, la visualización funcionará como un retrato vivo de ambos lugares. 
