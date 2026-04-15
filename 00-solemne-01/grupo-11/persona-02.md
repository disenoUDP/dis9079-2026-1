# persona-02

investigaciones individuales Benjamin Alvarez

## sobre adafruit i/o

### Qué es Adafruit IO

Al inicio no tenía claro qué era Adafruit IO, pensaba que era otro Arduino IDE o una aplicación para cargar códigos. Sin embargo, después de investigar, entendí que es una plataforma en la nube diseñada para proyectos de IoT, que permite conectar, visualizar y controlar sensores y dispositivos en tiempo real sin necesidad de programación compleja.

Una de las cosas más interesantes es la posibilidad de crear dashboards, donde se pueden agregar botones o interruptores para controlar dispositivos, como encender y apagar una luz de forma remota.

## Instalación de Adafruit IO en Arduino

Para comenzar a usar Adafruit IO con Arduino, se deben seguir estos pasos

1. Abrir el Arduino IDE

2. Ir a Library Manager

3. Buscar: `Adafruit IO Arduino`

![instalacion](./imagenes/adafruit-io-arduino.png)

4. Hacer clic en Instalar

5. Cuando aparezca la ventana de dependencias, presionar Aceptar para instalar todo lo necesario

![instalacion](./imagenes/install-all.png)

## Creación de cuenta en Adafruit IO

1. Ir a la página oficial de Adafruit IO

2. Crear una cuenta utilizando el correo institucional (UDP)

![cuenta](./imagenes/cuenta.png)

3. Iniciar sesión

#### Una vez dentro

- Ir a la sección IO

- Hacer clic en el ícono de la llave (key)

![contraseña](./imagenes/iniciada.png)

- Copiar la clave generada, ya que se utilizará en el código de Arduino para vincular el dispositivo con la cuenta

## Aprendizaje y dificultades

Durante este trabajo aprendí a utilizar mejor Arduino y Adafruit IO, herramientas que no había usado antes. Con el tiempo logré entender mejor cómo funcionan y cómo es posible controlar dispositivos a distancia, como encender y apagar una luz, lo cual resulta bastante interesante.  

En cuanto a las dificultades, al inicio fue complejo entender el funcionamiento general, especialmente la creación de códigos y su correcta ejecución. Esto generó cierta frustración, pero con la práctica y el avance de las clases fui comprendiendo mejor el proceso, especialmente cómo enviar datos desde un dispositivo a la nube y recibirlos correctamente.

## sobre artista, diseñadora o producto que usa electrónica o computación inalámbricas

### Anouk Wipprecht y tecnología interactiva  

Anouk Wipprecht es una diseñadora que trabaja en el ámbito del FashionTech, un campo emergente que combina diseño, robótica, ciencia y diseño de interacción para transformar la moda en una experiencia que va más allá de lo estético. Su trabajo se centra en crear prendas que no solo sean visualmente atractivas, sino que también respondan activamente al entorno y al comportamiento del usuario, integrando tecnología directamente en el cuerpo. Por esto, es reconocida como una figura clave en el desarrollo de la moda tecnológica contemporánea.

Una característica importante de su trabajo es el uso de sistemas interactivos que incorporan sensores, microcontroladores e inteligencia artificial para generar respuestas en tiempo real. Sus diseños suelen explorar temas como el espacio personal, la emoción, la comunicación no verbal y la relación entre humanos y tecnología, proponiendo una moda que “reacciona” en lugar de ser pasiva.

En este contexto, el Spider Dress 2.0 es uno de sus proyectos más representativos. Se trata de un vestido tecnológico equipado con sensores de proximidad y un chip de Intel, específicamente el módulo Intel Edison, integrado en una estructura impresa en 3D. Este sistema es capaz de captar señales biológicas, como la respiración, y analizar la cercanía y velocidad de las personas alrededor.

![vestido](./imagenes/spider-dress.jpg)

Cuando el dispositivo detecta una posible amenaza o invasión del espacio personal, activa unos brazos mecánicos que se extienden de forma automática, funcionando como un mecanismo de defensa. De esta manera, el vestido no solo cumple una función estética, sino que actúa como una interfaz entre el cuerpo y el entorno, reaccionando en tiempo real y redefiniendo la relación entre moda, tecnología e interacción.

<https://www.youtube.com/watch?v=uTTezk__Xvw>

### Otros trabajos

#### HeartBeatDress

![heartbeatdress](./imagenes/heartbeatdress.jpg)

Utiliza sensores integrados, tecnología robótica, sonido y luz para reaccionar al ritmo de los latidos del corazón de quien lo lleva puesto.

<https://www.youtube.com/watch?v=LHHXLIYTkLQ>

El HeartBeatDress también aparece en el último videoclip de la artista estadounidense Chrystabell.

<https://www.youtube.com/watch?v=_tuE52TtHWY>

#### Smoke dress

El vestido funciona como una cortina de humo portátil. Mediante tecnologías integradas, la prenda detecta la proximidad de otra persona y crea un velo de humo alrededor del usuario para camuflarlo. 

![smoke dress](./imagenes/smoke-dress.jpg)

La tecnología funciona mediante un microcontrolador y un sistema de sensores personalizados. Este sistema calcula datos sobre el espacio personal del usuario y los envía al generador de humo situado entre los omóplatos

<https://www.youtube.com/watch?v=G-0lTP90hVc>

### Bibliografia

<https://www.anoukwipprecht.nl/#intro-1>

<https://www.anoukwipprecht.nl/bio>

<https://3druck.com/es/arte/vestido-arana-2-0-creado-por-la-disenadora-anouk-wipprecht-5428243/>

<https://io.adafruit.com/#:~:text=%C2%BFQu%C3%A9%20es%20exactamente%20Adafruit%20IO,de%20las%20Cosas%20para%20todos!>

<https://3druck.com/es/arte/anouk-wipprecht-heartbeatdress-55105131/>

<https://www.digiart21.org/art/smoke-dress>
