# investigaciones individuales

Débora Soto/ DebSkar

## Sensor

### ¿Qué es un sensor?

Un sensor es un dispositivo diseñado para detectar estímulos, magnitudes físicas o variaciones químicas en su entorno inmediato, como luz, temperatura, presión, distancia o presencia y transformar esa información analógica en una señal eléctrica cuantificable, generalmente voltaje o corriente, que puede ser leída y procesada por un sistema electrónico o microcontrolador.

## Sensor Chip MPR121
* #### Sensor de proximidad y tacto capacitivo por comunicación I2C de 12 canales.

### ¿Cómo funciona?

Este sensor funciona midiendo las variaciones en la capacitancia eléctrica,la capacidad de un cuerpo para almacenar una carga eléctrica. 
El chip aplica una pequeña corriente a un material conductor conectado a él,que actúa como un electrodo,creando un campo electrostático a su alrededor. Cuando un cuerpo con propiedades conductivas y dieléctricas (materiales con muy baja conductividad eléctrica),como la piel humana, que está compuesta mayoritariamente por agua, se aproxima o toca este electrodo, interfiere con el campo electrostático, absorbiendo parte de la carga y alterando la capacitancia del circuito. El chip MPR121 detecta este micro-cambio físico en tiempo real, lo filtra digitalmente y lo envía como un dato numérico preciso a un microcontrolador mediante el protocolo de comunicación I^2C. Lo interesante es que su alta sensibilidad permite registrar variaciones por proximidad (antes del contacto físico real) si el electrodo es lo suficientemente grande.

## Artista

Colectivo francés Scenocosme: compuesto por Grégory Lasserre y Anaïs met den Ancxt.

Es un dúo de artistas contemporáneos franceses, que  trabaja en conjunto desde 2003. Su propuesta artística se centra en la combinación entre la naturaleza y la tecnología digital.

Son reconocidos internacionalmente por crear obras interactivas y entornos de inmersión donde elementos vivos y orgánicos, como plantas, agua, madera y piedras reaccionan a estímulos sutiles del cuerpo humano, el calor corporal, el aliento o la energía electrostática,para generar paisajes sonoros y visuales poéticos.

* Anaïs met den Ancxt nació en Lyon, en el año 1981.Estudió Antropología en la Universidad de Lyon y posteriormente se graduó de la École Nationale des Beaux-Arts de Lyon con una especialización en diseño de espacios. Aporta a la obra una fuerte visión estética, conceptual y de circulación espacial.

* Grégory Lasserre, nació en Annecy, en el año 1976.Cuenta con una formación técnica y científica robusta. Estudió Electrónica e Informática, y posteriormente obtuvo una maestría en Multimedia y Artes Digitales en la Universidad de Valenciennes.
Él se encarga del desarrollo del software propio, el diseño de hardware y la calibración de los circuitos interactivos.

## Obra: Akousmaflore

En esta instalación interactiva, las artistas conectan los cables de los sensores capacitivos directamente a las raíces y la tierra húmeda de plantas vivas colgadas en la sala. Dado que la planta es conductora, toda su estructura vegetal se convierte en la extensión del sensor. 

Cuando el público se acerca a las hojas o las acaricia, el sensor MPR121 registra la alteración de capacitancia producida por el cuerpo del espectador, enviando los datos al sistema informático para activar la respuesta de la obra. Cuando alguien se aproxima o toca las plantas estas reaccionan emitiendo sonidos, cantos o murumullos, dependiendo de como se interactuen con ellas.

### Para lograr que las plantas funcionen como una interfaz digital, se realiza la siguiente instalación de hardware:

El microcontrolador y el circuito capacitivo, utilizan un circuito electrónico, que puede ser un microcontrolador o placas de desarrollo específicas para detección táctil capacitiva, similares a la tecnología que hace funcionar las pantallas de los celulares,es capaz de medir variaciones diminutas en la capacitancia eléctrica. Luego se  conecta  un cable eléctrico muy delgado desde las entradas analógicas/capacitivas del circuito directo a la tierra húmeda, muy cerca de las raíces de la planta. Dado que las plantas vivas están llenas de agua, savia y sales minerales, son excelentes conductoras de electricidad. Al conectar el cable a las raíces, toda la estructura de la planta (raíces, tallo, ramas y hojas) se electrifica sutilmente, convirtiéndose en una extensión del propio circuito, es decir, en una gran "antena" o electrodo biológico.

### ¿Cómo funciona la interacción física con los espectadores?

El cuerpo humano produce y almacena energía electrostática de manera constante. Aunque es imperceptible para nosotros, nos rodea una especie de campo eléctrico débil. Cuando un espectador se acerca, pasa la mano cerca o acaricia las hojas de la planta, el campo eléctrico del cuerpo interactúa con el de la planta. Esto altera la capacitancia del sistema (la capacidad de almacenar carga eléctrica en ese espacio intermedio). El circuito detecta instantáneamente este micro-cambio en la carga eléctrica. 

Lo interesante de la tecnología capacitiva es que no requiere un choque eléctrico ni un interruptor mecánico, y es tan sensible que puede registrar variaciones antes de que se produzca un contacto físico real por proximidad, aumentando el valor de la lectura a medida que el toque se vuelve más firme.

Una vez que el circuito registra los datos del cambio eléctrico, el proceso sigue estos pasos:

El microcontrolador transforma la variación de capacitancia analógica en datos digitales (valores numéricos de intensidad, velocidad y cercanía).Estos datos se envían en tiempo real a una computadora que ejecuta un software de diseño sonoro.
Cada planta tiene asignada una "voz" o comportamiento digital distinto según su morfología y la textura de sus hojas. Si se aproximan despacio, el sonido puede ser un murmullo, si se acaricia con fuerza, la textura del sonido cambia a un canto o una vibración acústica compleja, logrando que el público actúe como el director de una orquesta botánica y viva.

### Video de la instalación:
https://youtu.be/eq0gsRlq6QQ?si=2Ot1rfZ0_YO14i3S


## Actuador

### ¿Qué es un actuador?

Un actuador es un dispositivo capaz de transformar una señal eléctrica o digital proveniente de un sistema de control (como un microcontrolador o una computadora) en una acción física real que modifica o interviene directamente en el entorno. A diferencia del sensor,que recibe información del mundo, el actuador ejecuta una respuesta en el mundo tangible mediante fuerza mecánica, movimiento, emisión de luz o generación de calor.

## Servomotor de corriente continua (DC Servomotor)
* #### Servomotor de posición rotativa controlado por modulación por ancho de pulsos (PWM).

### ¿Cómo funciona? 

Este actuador transforma la energía eléctrica en energía mecánica rotacional con un control  preciso de la posición angular.
Internamente, un servomotor combina cuatro elementos clave:
Un motor de corriente continua común, un conjunto de engranajes reductores, para aumentar la fuerza  y reducir la velocidad, un potenciómetro conectado al eje de salida que actúa como un sensor interno para saber la posición exacta en todo momento y una pequeña placa de circuito de control.

El microcontrolador envía una señal eléctrica digital tipo PWM (Pulse Width Modulation). Dependiendo del ancho o duración de los pulsos eléctricos que recibe, el circuito interno del servomotor calcula el ángulo exacto al que debe girar, por ejemplo: entre 0° y 180°. El motor gira y el potenciómetro interno avisa al circuito cuando ha llegado a la posición deseada para detenerse ahí.


## Artista 01

Daniel Rozin 
Nació en Jerusalén en 1961.Daniel Rozin es un artista, desarrollador y educador israelí-estadounidense radicado en Nueva York. Es considerado una de las figuras más influyentes del arte cinético interactivo. 
Es famoso por su serie de "espejos mecánicos" creados desde finales de la década de los noventa. Su filosofía artística busca que la computadora y los cables permanezcan ocultos para que el espectador conecte directamente con la mecánica y el material físico (madera, metal, basura), convirtiendo al propio usuario en el "contenido" de la obra.
Se formó originalmente como Diseñador Industrial en la Bezalel Academy of Arts and Design en Jerusalén. Actualmente compagina su producción artística en su estudio de Long Island con la docencia, siendo Profesor de Artes titular en el ITP (Interactive Telecommunications Program) de la Tisch School of the Arts de la Universidad de Nueva York (NYU), donde enseña computación física y escultura cinética.

## Obra: Wooden Mirror

En esta  instalación de arte cinético,el artista utiliza 830 servomotores como actuadores principales.

La obra está compuesta por una matriz de 830 pequeñas piezas cuadradas de madera, y cada una de ellas está acoplada directamente al eje de un servomotor independiente.Una cámara central oculta el sensor, captura la silueta y los movimientos de la persona que se para frente a la obra. Después una computadora procesa esa imagen en tiempo real, calcula los niveles de luz y sombra de cada zona, y envía comandos eléctricos individuales a los 830 servomotores.
Al recibir la señal, los motores actúan de inmediato rotando cada pieza de madera hacia arriba o hacia abajo y como la luz del techo incide de manera distinta según la inclinación de la madera, está va generando zonas claras y oscuras, entonces los actuadores logran como “dibujar” mecánicamente el reflejo y la sombra del espectador en tiempo real.

### Video de la instalación:
https://youtu.be/kV8v2GKC8WA?si=m1vpbGqpopvJbepU

## Artista 02

David Bowen es un reconocido artista visual, escultor y educador que investiga las relaciones estéticas y funcionales entre los sistemas naturales y los mecánicos. Obtuvo su Maestría en Bellas Artes (MFA) en la Universidad de Minnesota y actualmente se desempeña como profesor asociado de Escultura y Computación Física en la Universidad de Minnesota, Duluth.
A lo largo de su trayectoria, Bowen ha expuesto en centros artísticos y tecnológicos de gran prestigio internacional, como el ZKM Center for Art and Media , el NTT InterCommunication Center, el Centro de Cultura Contemporánea de Barcelona (CCCB) y la Fundación Telefónica. Ha sido galardonado con distinciones de alto nivel en el campo del arte electrónico, incluyendo la beca McKnight Visual Artist Fellowship y premios en el Japan Media Arts Festival, Ars Electronica y la competición internacional de vida artificial VIDA.

Su propuesta artística consiste en extraer flujos de datos cambiantes, como el movimiento de las olas marinas, la fuerza del viento, el andar de insectos o el crecimiento de plantas y convertirlos en instrucciones mecánicas de movimiento mediante hardware y software de código libre.

## Obra: underwater 

La obra consiste en una gran malla geométrica suspendida en el espacio que flota y se deforma suavemente frente al espectador. Para generar este movimiento, Bowen instaló una cámara con sensores infrarrojos de profundidad (un sistema similar a Microsoft Kinect) en una sección del Lago Superior. La cámara capturó en tiempo real los sutiles cambios tridimensionales, la frecuencia y la intensidad de las olas, digitalizando e importando esta información física como una nube de puntos tridimensionales.

La instalación cobra vida gracias a 729 servomotores individuales distribuidos de manera equidistante a lo largo de todo el entramado de aluminio. El sistema informático de control recibe las coordenadas espaciales de la superficie del agua y las traduce instantáneamente en señales eléctricas de modulación por ancho de pulsos (PWM) independientes para cada motor. Al activarse de forma coordinada, los servomotores rotan sus ejes milimétricamente para subir o bajar los brazos articulados de la estructura. Al observar la obra, el espectador puede notar cómo el "ronroneo" o zumbido colectivo de los 729 servomotores elimina la rigidez de la rejilla cuadriculada, transformándola en una onda líquida y fluida que imita fielmente la coreografía autónoma del lago.

### Video entrevista a David Bowen:
https://youtu.be/o3OJAZzcIB4?si=BSyVsKiQvT4uupeT

## Bibliografía
* https://www.nxp.com/products/MPR121?hl=es-CL
* https://learn.adafruit.com/adafruit-mpr121-12-key-capacitive-touch-sensor-breakout-tutorial?hl=es-CL
* https://www.scenocosme.com/akousmaflore_en.htm?hl=es-CL
* https://docs.arduino.cc/libraries/servo/#Usage/Examples
* https://www.smoothware.com/danny/?hl=es-CL
* https://www.bitforms.art/artwork/wooden-mirror-2
* https://mmam.org/david-bowen?hl=es-CL










