# investigaciones individuales

carla núñez / ccarlabelenn

# investigación sensor: botón 

## botón - pulsador
el botón es uno de los sensores más simples que existen. detecta únicamente dos estados: presionado o no presionado, entregando un valor digital de *0* o *1*. es la forma más directa entre una persona y un sistema electrónico.

## funcionamiento 
internamente tiene dos contactos metálicos que se unen cuando se presiona, permitiendo el paso de la corriente. cuando se suelta, el circuito se abre y la señal vuelve a su estado original. para que esa lectura sea estable se usa una resistencia **pull-up** o **pull-down**, que mantiene el valor fijo cuando el botón no está siendo presionado.

## atados/problemas comúnes 
el problema más común al trabajar con botones es el **rebote**: al presionar, los contactos vibran por unos milisegundos generando muchas señales falsas. esto se soluciona con el **debounce**, que puede aplicarse de dos formas:

+ **por software:** simplemente ignorar lecturas durante un tiempo corto después del primer cambio
+ **por hardware:** agregar un condensador en paralelo al botón, que suaviza esas vibraciones eléctricas

## visualización de datos
al ser un sensor digital, su visualización es bastante directa:
- un **LED** que enciende al presionar
- un **gráfico de señal cuadrada** que muestra los cambios entre 0 y 1 en el tiempo
- un **contador de pulsaciones** desplegado en pantalla

## atados 

| atado | causa | solución |
|---|---|---|
| muchas lecturas por una sola presióm | rebote eléctrico | debounce por software o hardware |
| siempre lee el mismo valor | sin resistencia pull-up/down | activar `Pull.UP` en el código |
| no detectar ninguna pulsación | posible cable suelto o pin mal configurado | revisar conexión y dirección del pin |

> ## **"Konkretizator" — Marko Stojanović (2010)**
Konkretizator es una instalación de arte interactivo audiovisual donde el botón es el elemento central de la experiencia. cada botón tiene un sonido y un video vinculado que al presionarlo se dispara ese contenido en unas pantallas, al presionar otro, se agrega una nueva capa. de esta forma el usuario va construyendo su propia composición musical en tiempo real, sin necesidad de saber sobre música (demasiado cool). la obra se inspira en los principios de la "música concreta" del compositor Pierre Schaeffer, que proponía crear música a partir de sonidos grabados del entorno real. lo que resulta súper interesante es que el botón se convierte un gesto creativo, presionar es componer. fue exhibida por primera vez en diciembre de 2010 en la Galería del Banco Nacional de Serbia, durante el festival S.U.T.R.A.
## Actuador

# investigación actuador: pantalla OLED

## pantalla OLED
una pantalla OLED (organic light-emitting diode) es un actuador visual que permite mostrar texto, gráficos e información. a diferencia de las LCD, cada píxel genera su propia luz, lo que elimina la necesidad de retroiluminación y da como resultado imágenes con un contraste muy marcado. las más usadas en proyectos con microcontroladores son de **128x64 píxeles**, monocromáticas, y se comunican por **I2C o SPI**.

## funcionamiento 
recibe datos del microcontrolador y los traduce en imágenes píxel a píxel.

## filtrado de información
cuando se muestran datos de sensores en una OLED hay que tener en cuenta algunos criterios:
+ **redondear valores** para que la pantalla no se llene de decimales innecesarios 
+ **actualizar solo cuando el dato cambia**, para evitar que parpadee constantemente 

## visualización de datos
a pesar de ser pequeña y limitación de dos colores la OLED permite bastante:
+ texto plano, estados o mensajes
+ barras de progreso
+ íconos simples en blanco y negro

## atados

| atado | causa | solución |
|---|---|---|
| el texto se superpone | no se limpia antes de escribir | revisar `oled.fill(0)` antes de cada actualización |
| parpadeo constante | `.show()` llamado demasiado seguido | actualizar solo cuando el dato cambia |
| no enciende | voltaje incorrecto | verificar que sea 3.3V y no 5V |

> ## **Relojes y visualizaciones poéticas en OLED — Joey Castillo**
Joey Castillo es diseñadora de hardware que ha explorado las pantallas OLED como objeto de diseño en sí mismo. su proyecto *Sensor Watch* usa una pantalla diminuta para mostrar no solo la hora, sino datos del entorno de forma minimalista. lo bacán de su trabajo es que trata la restricción técnica (pocos píxeles, solo blanco y negro) como una decisión estética y no como una limitación.
## Bibliografía
+ Stojanović, M. (2010). *Konkretizator — Interactive audiovisual installation*. <https://markostojanovic.me/works-2/>
+ Castillo, J. (s.f.). *Sensor Watch project*. <https://www.sensorwatch.net>
