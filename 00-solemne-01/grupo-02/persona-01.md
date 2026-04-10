# persona-01

investigaciones individuales

## sobre adafruit i/o

**Adafruit** es una empresa y comunidad de tecnología enfocada en la electrónica DIY, en aprender, armar y programar proyectos propios con placas, sensores y componentes. Fue fundada en 2005 por la ingeniera Limor “Ladyada” Fried. Su objetivo desde el inicio fue crear el mejor lugar en línea para aprender electrónica y ofrecer productos bien diseñados para personas de distintas edades y niveles de experiencia.
 
**Adafruit IO**, es la plataforma en la nube de Adafruit para proyectos de Internet of Things o IoT. Sirve para conectar dispositivos, recibir datos de sensores, guardar esos datos y también interactuar con ellos desde internet. La propia documentación de Adafruit la describe como una plataforma pensada para mostrar, responder e interactuar con los datos de un proyecto, con foco en que sea fácil de usar.

Dentro de **Adafruit IO**, un **dashboard** es el panel visual donde se ve y controla un proyecto desde el navegador. Ahí puedes poner bloques como gráficos, botones, sliders, indicadores o medidores para observar lo que está pasando. 
 
Un **feed** es el canal donde se guarda una variable o flujo de datos. almacenan los datos y metadatos enviados a IO. osea el sensor de pulso, podría tener un feed llamado pulsometro donde se van guardando los valores BPM luego ese feed se conecta a un gráfico o indicador dentro del dashboard para poder verlo en tiempo real.

<ins>los feeds son el núcleo del sistema y que los bloques del dashboard se enlazan a uno o más feeds.</ins>

**Arduino** = quien manda el mensaje   
**Adafruit IO** = la nube que lo recibe  
**Dashboard** = la pantalla donde se ve 

Arduino detecta algo.  
Por ejemplo: el sensor de pulso siente un latido.  
Entonces el Arduino dice:  
“voy a mandar este dato a internet”  
Ese dato llega a Adafruit IO, que sería como una cajita en la nube donde se guarda,
el dashboard mira esa cajita y muestra lo que hay dentro. 

**config.h** es el archivo de configuración donde se guardan los datos que el programa necesita para conectarse sin mezclar todo con el código principal.   
**archivo principal .ino** → hace funcionar el sensor, envía datos, controla la lógica  
**archivo config.h** → guarda claves, usuario y red
**THROTTLE WARNING** → cuenta que alcanzó el límite de velocidad de envío de datos en Adafruit IO

algunos apuntes  
 
pulsometro **Threshold** → qué valor de señal voy a considerar que esto ya cuenta como latido // subir si sigue detectando sin dedo el bpm  
**void setup()** → Sirve para preparar todo antes de que empiece el programa principal.
                   se preparan cosas como:

                   iniciar comunicación serial
                   definir si un pin será entrada o salida
                   conectar Wi-Fi
                   iniciar una pantalla
                   iniciar sensores

**void loop** → Es donde va la parte del programa que se repite constantemente. por ejemplo:

                leer un sensor
                prender y apagar un LED
                revisar si llegó un mensaje
                actualizar una pantalla
                mandar datos a Adafruit

 en adafruit, va void loop acompañado de io.run

**io.connect** → es la instrucción que le dice al Arduino:conéctate a Adafruit IO
**mensajeFeed->onMessage(handleMessage)**  → cuando llegue un mensaje nuevo a este feed, ejecuta la función
**void handleMessage(AdafruitIO_Data data)String texto = data->toString**  → estoy creando una función llamada handleMessage que recibe un dato de Adafruit IO   
**Serial.begin(115200)** → 
                Serial
                es el objeto que maneja la comunicación serial.

                .begin()
                significa iniciar

                (115200)
                es la velocidad de comunicación, llamada baud rate
                  
**mensajeFeed->onMessage(handleMessage)** → deja este feed escuchando, y cuando llegue un mensaje nuevo, ejecuta la función handleMessage

Variables: 
**int tipo nombre = valor;**

               int = tipo de dato  
               contador = nombre de la variable   
               0 = valor inicial   
  


  
## sobre artista, diseñadora o producto que usa electrónica o computación inalámbricas

**Carla Diana**, su trabajo cruza diseño, robótica e interacción, explorando cómo los objetos inteligentes pueden comunicarse con nosotros no solo por su función, sino también por su comportamiento, movimiento y presencia.tiene trabajos y propuestas con respecto el diseño, el objeto y lo tecnológico que me parecen una locura, pero me interesó por sobretodo porque propone una forma de pensar la tecnología desde lo cotidiano. Llegué a ella leyendo una entrevista en _Vice_ y me llamó mucho la atención cómo habla de objetos comunes que podrían volverse más activos, expresivos e incluso más atentos a nosotros en el día a día. Cuando dice en su entrevista que _comenzamos a ver comportamientos mucho más sofisticados por parte de nuestros productos cotidianos_, apuntando a un futuro donde las cosas ya no solo funcionan sino que buscan una forma de relacionarse con nosotros de maneras nuevas. ella propone ideas como un micrófono que se inclina para mostrar que está escuchando, una cámara que gira para dar privacidad o una cafetera que te presenta la taza no son solo aparatos útiles, sino objetos que empiezan a tener una especie de gesto, una presencia.
 
con lo que propone, se me viene mucho a la cabeza **Wallace y Gromit**. Cuando era chica, veía esa escena en que se levantan y toda la tecnología de la casa se adapta a su rutina cotidiana y a mis ojos eso era perfecto, me fascinaba esa idea de que lo casero, lo automático y lo cotidiano pudieran convivir de una manera tan natural. Y creo que eso es justamente lo que me atrae de Carla Diana: que toma algo que parecía fantasía y lo plantea como una posibilidad real, no desde una promesa exagerada, sino desde el diseño, la experimentación y la demostración de que ese tipo de relación con los objetos podría efectivamente formar parte del futuro y convertirlo en una participación sutil pero que conecta con uno en un día normal.

También queria rescatar que en la entrevista ella habla de tener que _permanecer fieles a nuestros valores humanos y decidir qué productos pertenecen a nuestras vidas y qué productos no_, _En lugar de huir o ignorar el potencial, necesitamos centrarnos en lo bueno que puede traer y rechazar en nuestras vidas esas cosas que nos alejan de lo que nos importa._ me hace mucho sentido ella como se desenvuelve en la disciplina y lo que enseña al respecto, a mi me daría miedo que los humanos terminemos como en *+WALL-E**, pero saber que hay personas que observan la computación o la robótica desde una vereda mucho mas artística o sensible con lo que ya está vivo, me parece bello.



<img src="https://github.com/magdalenabalart/dis9079-2026-1/blob/main/00-solemne-01/grupo-02/imagenes/carladiana.jpg" width=30% height=30%> <img src="https://github.com/magdalenabalart/dis9079-2026-1/blob/main/00-solemne-01/grupo-02/imagenes/carladiana02.png" width=30% height=30%>

Tiene formación tanto en ingeniería como en diseño: estudió Mechanical Engineering en The Cooper Union y luego hizo un MFA en 3D Design en Cranbrook Academy of Art.
