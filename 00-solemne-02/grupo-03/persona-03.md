# investigaciones individuales

carla núñez / ccarlabelenn

# investigación sensor: botón 

+ botón - pulsador
  
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
# Actuador

## investigación actuador: pantalla OLED

+ pantalla OLED
  
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

> ## **Texto en pantalla como poesía — Yucef Merhi**
> Yucef Merhi es un artista, poeta y programador venezolano radicado en Nueva York, conocido por crear obras que usan circuitos electrónicos, computadores y pantallas para presentar sus palabras escritas. Lo que hace especial su trabajo es que no usa la tecnología como soporte neutro, sino como parte del lenguaje mismo. Su obra más emblemática, *The Poetic Clock*, muestra tres líneas de poesía en pantalla: la primera cambia cada hora, la segunda cada minuto y la tercera cada segundo, generando 86.400 poemas distintos en un solo día. Lo bacán de su trabajo es que trata la restricción técnica (una pantalla, texto simple, sin imágenes) como una decisión estética y no como una limitación.

 + Atari Poetry
En su serie *Atari Poetry*, Merhi reprogramó consolas Atari 2600 usando código binario y lenguaje ensamblador para explorar las conexiones entre tecnología y lenguaje. El resultado son poemas que emergen desde las entrañas de una máquina de videojuegos, expandiendo los límites del lenguaje y del contexto tradicional de la poesía. Su trabajo demuestra que cualquier pantalla, por pequeña o simple que sea, puede convertirse en un lugar donde ocurre algo significativo.

## Bibliografía
+ Stojanović, M. (2010). Konkretizator — Interactive audiovisual installation. <https://markostojanovic.me/works-2/>
+ Merhi, Y. (s.f.). The Poetic Clock 2.0. The Bonnier Gallery. <https://www.thebonniergallery.com/artworks/268-yucef-merhi-the-poetic-clock-2.0-2000/>
+ ArtBurst Miami. (2021). The Bonnier Gallery presents digital art in 'Yucef Merhi: Open'. <https://www.artburstmiami.com/visual_arts/the-bonnier-gallery-presents-digital-art-in-yucef-merhi-open>
