# investigaciones individuales

Anays Cornejo - [Anaysval](https://github.com/Anaysval)

## Sensor

### Sensor PIR 

### ¿Qué es un sensor PIR?

Un sensor PIR (Passive Infrared Sensor) es un dispositivo electrónico que detecta movimiento mediante cambios en la radiación infrarroja emitida por personas, animales u objetos calientes. 

Estos sensores se utilizan principalmente para identificar si una persona se ha movido dentro o fuera de su rango de detección. Son dispositivos pequeños, económicos, de bajo consumo energético, fáciles de usar y con una larga vida útil, ya que no tienen partes mecánicas que se desgasten.

Por estas características, son muy comunes en electrodomésticos, sistemas de iluminación automática y equipos de seguridad en hogares o negocios. También se conocen como sensores PIR, sensores infrarrojos pasivos, sensores piroeléctricos o sensores de movimiento infrarrojo.

### Uso del sensor PIR

El sensor PIR detecta movimiento cuando percibe cambios en la radiación infrarroja del ambiente. Esto ocurre cuando una persona u objeto caliente entra en su zona de detección.

Está compuesto principalmente por una lente Fresnel, un sensor infrarrojo y tres pines de conexión: VCC, OUT y GND.

Se utiliza principalmente en:

- Alarmas de seguridad
- Luces automáticas
- Sistemas de domótica
- Robots
- Puertas automáticas

### Filtrado de información
  
El sensor PIR puede generar errores o falsas detecciones debido a factores externos, por lo que se aplican técnicas de filtrado para mejorar la precisión.

Los principales problemas que afectan la lectura son la luz solar directa, cambios bruscos de temperatura, movimiento de mascotas e interferencias eléctricas.

Para reducir estos errores se utilizan:

- Uso de retardos de tiempo
- Verificación de varias lecturas consecutivas
- Ajuste de sensibilidad del sensor

### Visualización de datos

Los datos entregados por el sensor pueden visualizarse de distintas formas dependiendo del sistema utilizado.

Se puede mostrar información mediante:

- Monitor serial en Arduino (ej: “Movimiento detectado” o “Sin movimiento”)
- LEDs indicadores
- Pantallas LCD
- Pantallas OLED (más pequeñas, de bajo consumo y con mejor contraste)
- Plataformas IoT para monitoreo remoto

### Problemas comunes

El sensor PIR puede presentar distintos problemas que afectan su funcionamiento correcto.

Los más frecuentes son:

- Falsas detecciones provocadas por calor ambiental, ventiladores o luz solar
- Alcance limitado de detección (generalmente entre 3 y 7 metros)
- Tiempo de espera entre activaciones del sensor
- Errores por mala instalación o mala orientación
- Interferencias eléctricas o alimentación inestable

### Obra

### Made to Measure 

La instalación Made to Measure del estudio Process Studio es una obra de arte interactivo donde el espacio responde a la presencia del público mediante sensores de movimiento instalados en el techo. Según la documentación oficial del proyecto, la obra utiliza 15 sensores PIR para detectar la presencia y el desplazamiento de los visitantes dentro de la sala.

“Al acercarse a los objetos expuestos o al caminar por la sala, el visitante activaba 15 sensores de movimiento montados en el techo, activando bucles en 8 altavoces diferentes y el parpadeo o conmutación de 5 tubos de neón. Dependiendo de las acciones de los visitantes, surgieron diferentes paisajes sonoros y situaciones de iluminación.” (Process Studio, n.d.) 

El sensor PIR es un dispositivo que detecta movimiento a partir de cambios en la radiación infrarroja emitida por el cuerpo humano. Su función principal es identificar la presencia de personas en un espacio sin contacto directo, lo que lo hace ideal para sistemas de iluminación automática, seguridad y entornos interactivos. En este caso, los sensores permiten que la instalación reaccione al público en tiempo real, activando luz y sonido según su movimiento.

No encontré más información sobre la instalación Made to Measure del estudio Process Studio además de lo que aparece en su página oficial. La información es bastante limitada y solo describe la obra de forma general, Tampoco encontré videos oficiales ni documentación técnica más detallada sobre cómo funciona el proyecto. La quise utilizar igualmente porque se ve interesante y un poco misteriosa, donde no hay mucha más información y queda un poco a la imaginación. 

### Bibliografía

- Adafruit Learning System. (n.d.). PIR sensor guide. <https://learn.adafruit.com/pir-passive-infrared-proximity-motion-sensor/overview>
- Process Studio. (n.d.). Made to measure. <https://process.studio/works/made-to-measure/>
- Random Nerd Tutorials. (n.d.). Arduino with PIR motion sensor. <https://randomnerdtutorials.com/arduino-with-pir-motion-sensor/>
- SparkFun Electronics. (n.d.). PIR motion sensor hookup guide. <https://learn.sparkfun.com/tutorials/pir-motion-sensor-hookup-guide/all>

## Actuador

### Pistón electromecánico

### ¿Qué es un pistón electromecánico?

Un actuador electromecánico es un dispositivo electrónico que convierte energía eléctrica en movimiento físico. En este caso, el pistón electromecánico (lineal) es un tipo de actuador que genera movimiento en línea recta, es decir, empuja o retrae un eje.

Estos actuadores se utilizan principalmente para mover objetos de forma automática y controlada. Son precisos, pueden soportar carga y permiten repetir movimientos muchas veces sin intervención manual constante.

También se conocen como actuadores lineales, pistones eléctricos o sistemas de movimiento lineal automatizado.

### Uso del pistón electromecánico

El actuador electromecánico funciona cuando recibe una señal eléctrica que activa su motor interno. Ese motor transforma la energía eléctrica en movimiento mecánico lineal.

Se utiliza principalmente en:

- robótica
- automatización de sistemas
- mecanismos de elevación
- movimiento controlado de objetos
-sistemas mecánicos interactivos

### Filtrado de información

El actuador puede presentar errores o fallas si no se controla correctamente, por lo que se deben considerar ciertos factores para su buen funcionamiento.

Los principales problemas que afectan su rendimiento son:

- sobrecarga del peso que debe mover
- desgaste mecánico por uso continuo
- errores de calibración del movimiento
- variación en la potencia eléctrica

Para mejorar su funcionamiento se utilizan:

- control preciso de la señal eléctrica
- calibración del recorrido del pistón
- regulación de la carga mecánica
- mantenimiento periódico
- Visualización de datos

Los actuadores no muestran datos directamente, pero convierten información digital en movimiento físico.

Esto se realiza mediante:

- señales eléctricas enviadas desde un sistema de control
- programación de movimientos específicos
- conversión de datos en acción mecánica (ej: subir, bajar o mantener posición)

### Problemas comunes

El actuador electromecánico puede presentar distintos problemas durante su uso.

Los más frecuentes son:

- desgaste de engranajes internos
- sobrecalentamiento del motor
- pérdida de precisión con el tiempo
- ruido mecánico durante el funcionamiento
- fallos si recibe cargas mayores a las recomendadas

### Información importante adicional

- Tiene alta precisión en movimientos lineales
- Permite automatización sin intervención humana
- Puede funcionar con microcontroladores (Arduino, PLC, etc.)
- Su velocidad depende del voltaje y la carga aplicada
- Es más silencioso que sistemas hidráulicos en algunos casos
- Su vida útil depende del uso y mantenimiento

### Ventajas y desventajas

Ventajas:

- control preciso del movimiento
- fácil integración con sistemas electrónicos
- bajo mantenimiento comparado con sistemas hidráulicos
- repetición de movimientos sin fatiga humana

Desventajas:

- fuerza limitada según el modelo
- puede sobrecalentarse con uso continuo
- depende totalmente de energía eléctrica
-desgaste mecánico interno con el tiempo

### Obra

### Wavefunction / Subsculpture 9 – Rafael Lozano-Hemmer (UMMA)  

Rafael Lozano-Hemmer es un artista contemporáneo mexicano-canadiense nacido en 1967 en Ciudad de México. Su trabajo se enfoca en la creación de instalaciones interactivas que combinan arte, tecnología y participación del público. Sus obras utilizan sistemas computacionales, sensores y mecanismos automatizados para generar experiencias donde el espectador es parte activa de la obra 

Su enfoque artístico se basa en la idea de la “arquitectura relacional”, donde el espacio expositivo deja de ser estático y responde a la presencia de las personas. Esto permite que el comportamiento del público influya directamente en el funcionamiento de la instalación, transformando la obra en un sistema dinámico en tiempo real.

Wavefunction / Subsculpture 9 es una instalación cinética creada por Rafael Lozano-Hemmer que combina escultura, tecnología y participación del público. La obra está formada por sillas organizadas en una estructura de rejilla que responde al movimiento de los visitantes dentro del espacio expositivo.

“La instalación consta de cuarenta y dos sillas de plástico moldeadas (diseñadas por los Eames en 1948) dispuestas en una rejilla y sujetas a pistones electromecánicos. Cuando los visitantes se acercan a las sillas, un sistema de vigilancia detecta su presencia y las sillas más cercanas se levantan suavemente del suelo. Las sillas adyacentes siguen la silla y un movimiento de ola se extiende por la matriz. El software que controla los pistones se basa en la dinámica de fluidos, por lo que a medida que más visitantes se acercan a la cuadrícula, las sillas —cuyos icónicos contornos curvos también se generaron matemáticamente— imitan la compleja interacción de múltiples ondas en el agua” (University of Michigan Museum of Art, 2017).

“La idea de una ‘función’ como campo de experimentación artística es una motivación para esta pieza. Otras referencias incluyen: las matemáticas de los sistemas dinámicos, capaces de generar comportamientos complejos no lineales, la materialización de la vigilancia y la turbulencia, y la reinterpretación antimodular del trabajo de diseñadores modernos como Charles y Ray Eames. Cuando alguien se acerca a la obra, un sistema de vigilancia informatizado detecta su presencia y las sillas más cercanas comienzan automáticamente a elevarse del suelo, creando la cresta de una ola que luego se extiende por toda la sala. Un sistema de pistones electromecánicos eleva cada silla cuarenta centímetros del suelo. Los pistones son controlados por un ordenador que ejecuta las matemáticas de la dinámica de fluidos, haciendo que las ondas interfieran entre sí, creando turbulencias o calmándose, igual que el agua real.” (Lozano-Hemmer, 2007).

Aún me impresiona cómo algo digital puede transformarse a ese nivel en un efecto físico y visual real dentro del espacio. Es interesante ver cómo la obra mezcla arte y tecnología de  quizás una manera más simple, pero muy visual, logrando que la presencia de las personas genere movimientos reales en las sillas y cambie completamente la experiencia del lugar.

## Bibliografía

- Lozano-Hemmer, R. (2007). Wavefunction (Subsculpture 9). <https://lozano-hemmer.com/wavefunction.php>
- MechDaily. (2025). Linear actuators: types, processes and applications. <https://www.mechdaily.com/what-is-linear-actuators/>
- University of Michigan Museum of Art. (2017). Rafael Lozano-Hemmer: Wavefunction, Subsculpture 9. <https://umma.umich.edu/exhibitions/rafael-lozano-hemmer-wavefunction-subsculpture-9/>
