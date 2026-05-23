# investigaciones individuales

Antonella Lavalle / antolavalle

## Sensor

## Sensor Ultrasónico HC-SR04

## ¿Qué es y cómo funciona?

El HC-SR04 es un sensor de distancia que funciona con ultrasonido. Básicamente emite un sonido que nosotros no podemos escuchar, ese sonido rebota en un objeto y vuelve, y el sensor mide cuánto tardó en regresar. Con ese tiempo calcula la distancia, igual que el eco en una cueva.

Para usarlo hay que conectar cuatro pines: alimentación, tierra, uno para disparar el pulso (Trigger) y otro para recibir la respuesta (Echo). Desde el microcontrolador se manda un pulso brevísimo al Trigger, el sensor lanza las ondas, y cuando el eco regresa el pin Echo se queda en alto durante exactamente el tiempo que duró el viaje. Con ese tiempo y la velocidad del sonido (unos 343 m/s a temperatura normal) se calcula la distancia dividiendo por dos, porque el sonido fue y volvió.

La fórmula que se usa en el código es simplemente dividir la duración del Echo entre 58 para obtener centímetros, o entre 148 para pulgadas. Es uno de los sensores más fáciles de implementar, lo que lo hace muy popular en proyectos de electrónica y robótica.

<img width="800" height="800" alt="Sensor_ultrasonico_HCSR04_1" src="https://github.com/user-attachments/assets/f2a45cb4-4a5c-45fe-bc4e-e37888a4edc8" />


## Filtrado de información

El problema con el HC-SR04 es que las lecturas crudas son bastante ruidosas. Aunque el objeto esté completamente quieto, la distancia que reporta el sensor varía un poco en cada medición. Para trabajar con datos confiables hay que aplicar algún tipo de filtro.

El más simple es el promedio móvil, que consiste en guardar las últimas N lecturas y promediarlas. Funciona bien para objetos estáticos pero responde un poco lento si el objeto se mueve. El filtro de mediana es más robusto: en lugar de promediar, ordena las lecturas y toma la del medio, lo que elimina los picos raros sin que afecten el resultado. Esto es útil cuando hay objetos pasando frente al sensor o reflexiones extrañas en el ambiente.

También existe el filtro EMA, que da más peso a las lecturas recientes y menos a las antiguas. Es más eficiente en memoria que el promedio móvil y reacciona mejor al movimiento. Y como capa base siempre conviene descartar lecturas que estén fuera del rango físico del sensor, es decir, menos de 2 cm o más de 400 cm, o que cambien demasiado de golpe entre una medición y la siguiente.

En la práctica casi siempre se combinan dos o tres de estas técnicas para obtener un resultado limpio.

## Visualización de datos

Dependiendo del proyecto hay varias formas de visualizar lo que mide el sensor. La más inmediata es el Serial Plotter que trae el Arduino IDE, que grafica la distancia en tiempo real sin necesidad de instalar nada extra. Para análisis más detallados, Python con matplotlib permite ver el historial de lecturas y comparar los datos con y sin filtro, lo que ayuda mucho a entender cómo se comporta el sensor y a ajustar los parámetros.

Para proyectos más visuales o interactivos, p5.js es una buena opción porque permite crear gráficos en el navegador: círculos que crecen o se achican según la distancia, colores que cambian, barras de proximidad. Y si se quiere algo más elaborado, se puede montar un pequeño servidor con Flask o Node.js y mostrar los datos en un dashboard accesible desde cualquier dispositivo conectado a la red local.

## Problemas comunes

El primer problema que aparece cuando uno empieza a usar este sensor es la variación por temperatura. La velocidad del sonido cambia con el calor o el frío del ambiente, así que en espacios con cambios de temperatura las lecturas pierden precisión. La solución es agregar un sensor de temperatura como el DHT11 y usarlo para corregir el cálculo en tiempo real.

Otro problema bastante frecuente es el ángulo de incidencia. El sensor solo detecta bien objetos que estén más o menos de frente a él, dentro de un cono de unos 15 grados. Si el objeto está muy inclinado, las ondas rebotan hacia otro lado y no vuelven, así que el sensor no registra nada o registra un valor incorrecto.

También hay que tener cuidado con los ecos múltiples en espacios cerrados o con muchas superficies. El sensor puede captar el segundo o tercer rebote en vez del primero y reportar una distancia mayor a la real. Se puede solucionar limitando el tiempo máximo que se espera la respuesta del Echo.

Un error clásico cuando uno recién empieza es medir demasiado rápido. Si se hacen lecturas con menos de 60 ms de separación, el sensor puede confundir el eco de una medición con el de la siguiente. Y por último, materiales blandos como telas o espumas simplemente absorben las ondas en lugar de reflejarlas, así que el sensor no los detecta bien. Para esos casos hay que usar otro tipo de sensor.

## Obras, proyectos y empresas

Myron Krueger es uno de los referentes más importantes del arte interactivo y fue pionero en usar sensores de proximidad con ese fin. Desde los años 70, su instalación Videoplace permitía que los movimientos del cuerpo del espectador generaran imágenes y sonidos en tiempo real. No había ningún control físico, el cuerpo entero era la interfaz. Esa idea anticipó décadas antes todo lo que hoy conocemos como arte reactivo o instalaciones inmersivas.

<img width="320" height="247" alt="Sistema Videoplace" src="https://github.com/user-attachments/assets/34750281-6994-4faf-b879-7571951e9dab" />

<img width="714" height="475" alt="videoplace_espacios" src="https://github.com/user-attachments/assets/a74b65cc-ff01-447d-a9b0-d2681a8db4c0" />

En el ámbito industrial, los robots de almacén de Amazon usan este mismo principio, aunque con sensores mucho más sofisticados, para navegar entre estanterías, evitar personas y coordinarse con otros robots sin chocar. Y el sensor de reversa de cualquier auto moderno también funciona con ultrasonido, solo que fabricado a escala industrial por empresas como Bosch o Continental. Es básicamente el mismo principio del HC-SR04 pero empaquetado para aguantar lluvia, polvo y temperaturas extremas.

<img width="1200" height="675" alt="f elconfidencial com_original_e69_bd0_f39_e69bd0f39deefd3dbac0dbc29b265a46" src="https://github.com/user-attachments/assets/1ebe95fd-b85c-4aae-8705-87595b33a77f" />

<img width="1366" height="749" alt="1366_2000" src="https://github.com/user-attachments/assets/f3625341-4a5e-4f18-90f4-1d25be866c0f" />

## Actuador

## Servo Motor SG90

## ¿Qué es y cómo funciona?

El SG90 es un servo motor de pequeño formato, muy usado en proyectos de electrónica, robótica y arte interactivo. A diferencia de un motor DC común que gira sin parar, un servo se mueve a un ángulo específico y se queda ahí. Esa capacidad de posicionarse con precisión es lo que lo hace útil.

Internamente tiene tres cosas: un motor DC pequeño, una caja reductora de engranajes que reduce la velocidad pero aumenta la fuerza, y un potenciómetro que mide en qué posición está el eje en cada momento. Un circuito interno compara la posición actual con la posición deseada y ajusta el motor hasta que coincidan. Ese mecanismo de corrección constante es lo que se llama un sistema de control en lazo cerrado.

La comunicación con el microcontrolador se hace mediante PWM (modulación por ancho de pulso). Se envía una señal que se repite cada 20 ms, y la duración del pulso dentro de ese ciclo le dice al servo a qué ángulo moverse: un pulso de 1 ms corresponde a 0 grados, uno de 1.5 ms a 90 grados, y uno de 2 ms a 180 grados. El servo tiene un rango de movimiento de 180 grados en total y tres cables: alimentación (rojo), tierra (marrón o negro) y señal (naranja o amarillo).

<img width="1200" height="1372" alt="servo-motor-sg90-9g" src="https://github.com/user-attachments/assets/f1832de6-6cce-44f2-a1c2-6bde802063fa" />

## Control de la señal

El equivalente al filtrado en un sensor es el control de la señal de salida en un actuador. Si se le manda al servo posiciones que saltan bruscamente de 0 a 180 grados, el movimiento es violento, los engranajes se fuerzan y la estructura mecánica vibra. Para evitar eso hay distintas técnicas.

La más simple es el barrido gradual: en lugar de enviar directamente el ángulo destino, se incrementa el ángulo de a poco en cada ciclo del loop hasta llegar al valor deseado. Eso suaviza el movimiento considerablemente. Una versión más sofisticada es la interpolación, donde se calcula una trayectoria suave entre la posición actual y la destino usando una curva en lugar de una línea recta, lo que genera movimientos que aceleran al inicio y frenan al final, mucho más naturales. También se puede limitar la velocidad máxima de cambio, es decir, definir cuántos grados por segundo puede moverse el servo como máximo, independientemente de lo que pida el código. Esto protege tanto al servo como a lo que esté unido mecánicamente.

## Visualización de datos

Con un servo la visualización es un poco diferente que con un sensor, porque lo interesante no es tanto graficar datos sino visualizar el estado y el comportamiento del actuador. Lo más útil en desarrollo es mostrar en tiempo real el ángulo actual, el ángulo objetivo y la diferencia entre ambos, lo que permite detectar si el servo está llegando bien a la posición o si hay algo que lo está frenando.

En proyectos más elaborados se pueden graficar trayectorias de movimiento para ver si el servo sigue el perfil esperado o si hay oscilaciones y vibraciones. Processing y p5.js son buenas herramientas para esto porque permiten dibujar un brazo virtual que refleja el movimiento real del servo, lo que es muy útil para depurar sin tener que mirar el hardware todo el tiempo. Para proyectos con varios servos, como un brazo robótico, visualizar todos los ángulos simultáneamente en un dashboard ayuda a entender cómo interactúan entre sí.

## Problemas comunes

El problema más frecuente cuando uno empieza es alimentar el servo desde el pin de 5V del Arduino. El SG90 bajo carga puede pedir hasta 500 mA, y el Arduino no aguanta eso en su regulador interno. El resultado es que el Arduino se resetea solo, los servos se mueven de forma errática o directamente no responden. La solución es alimentar el servo directamente desde la fuente de poder y compartir solo la tierra con el Arduino.

Otro error clásico es no definir bien los límites del rango. Aunque el servo dice que va de 0 a 180 grados, en la práctica muchos SG90 no llegan exactamente a esos extremos con los pulsos estándar y forzarlos hace que los engranajes de plástico craqueen o se rompan. Hay que calibrar los valores mínimo y máximo para cada servo individual.

El zumbido constante es algo que desconcierta bastante al principio. Si el servo emite un zumbido aunque no esté moviéndose, generalmente significa que está recibiendo una señal PWM con algo de ruido o que está intentando mantener una posición contra una carga que lo empuja. En el primer caso ayuda usar la función detach() de la librería Servo de Arduino para dejar de enviar la señal cuando no se necesita movimiento. En el segundo caso hay que revisar el diseño mecánico.

Por último los engranajes de plástico del SG90 son su punto más débil. No está diseñado para cargas laterales ni para ser forzado manualmente cuando está energizado. Para aplicaciones con más peso o esfuerzo mecánico hay que subir a servos con engranajes metálicos como el MG90S o similares.

## Obras, proyectos y empresas

Theo Jansen es un artista y escultor holandés conocido por sus Strandbeesten, criaturas mecánicas gigantes que caminan por las playas impulsadas solo por el viento. Aunque las originales usan mecanismos puramente mecánicos, las versiones educativas y replicadas por makers de todo el mundo usan servos para controlar el movimiento de las patas. Jansen exploró de forma poética la idea de que la mecánica simple puede generar comportamiento que parece vivo, algo que sigue siendo referencia en robótica blanda y arte cinético.

<img width="1100" height="525" alt="correplayas-theo-jansen-1100x525" src="https://github.com/user-attachments/assets/fff230f3-f8c1-49bc-af3c-1c97853b27fc" />

<img width="4032" height="3024" alt="IMG_4175" src="https://github.com/user-attachments/assets/e7d7dbf8-a9fb-4061-a281-a0d5a704c479" />

El colectivo japonés teamLab usa servos y motores en muchas de sus instalaciones para crear superficies que se mueven, flores mecánicas que se abren y cierran, o estructuras que responden a la presencia del público. La combinación de actuadores físicos con proyección de luz les permite crear mundos donde lo digital y lo material se fusionan de forma que cuesta distinguir uno del otro.  

<img width="3840" height="2160" alt="public" src="https://github.com/user-attachments/assets/957974dd-8e43-4950-8aa5-14428ab503ac" />

<img width="900" height="450" alt="display" src="https://github.com/user-attachments/assets/e65cf0ba-7204-41f0-92fa-7b61db61eb99" />

## Bibliografía

Boxall, J. (2014). Arduino: Taller de proyectos. Anaya Multimedia.

Jansen, T. (2007). The great pretender. 010 Publishers.

Margolis, M. (2011). Arduino cookbook. O'Reilly Media.

McRoberts, M. (2013). Beginning Arduino (2.ª ed.). Apress.

McRoberts, M. (2014). Arduino básico. Anaya Multimedia.

Parallax Inc. (s.f.). Servo motor control with PWM. Recuperado de <https://learn.parallax.com/tutorials/robot/shield-bot/robotics-board-education-shield-arduino/chapter-6-servo-1>

teamLab. (s.f.). Works. Recuperado de <https://www.teamlab.art/works>

Torre Pro. (s.f.). SG90 micro servo datasheet. Recuperado de <http://www.towerpro.com.tw/product/sg90-7>

Torrente Artero, Ó. (2013). Arduino: Curso práctico de formación. RC Libros.

Herzog, L., Jansen, T. y Weschler, L. (2014). Strandbeest: The dream machines of Theo Jansen. Taschen.

Krueger, M. W. (1983). Artificial reality. Addison-Wesley.

Li, J. y Liu, H. (2016). Design optimization of Amazon robotics. Automation, Control and Intelligent Systems, 4(2), 48–52. <https://doi.org/10.11648/j.acis.20160402.17>

teamLab. (s.f.). Works. Recuperado de <https://www.teamlab.art/es/art/>
