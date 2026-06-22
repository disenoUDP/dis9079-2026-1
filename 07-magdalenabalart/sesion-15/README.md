# sesion-15

lunes 22 junio 2026

## Sesión 15: pruebas finales, fallas del sistema y ajustes de emergencia

En esta sesión realizamos las pruebas finales del sistema antes del examen. La idea era llegar con ambos tótems funcionando de manera conectada: el Tótem 01 debía detectar presencia, activar el LED y enviar datos a Adafruit IO; mientras que el Tótem 02 debía recibir esa información y mostrar el mensaje correspondiente en la pantalla OLED.

Sin embargo, durante esta sesión prácticamente todo comenzó a fallar sin una causa clara. El Tótem 01, que el día jueves sí lograba conectarse a Adafruit IO, dejó de conectarse correctamente. A pesar de que el código mantenía la estructura de conexión, el feed y los datos de red, el sistema no lograba enviar información a Adafruit. Esto fue especialmente problemático porque el examen era ese mismo día y el sistema ya había funcionado previamente.

### Revisión del Tótem 01

En el Tótem 01 revisamos primero que el problema no estuviera en el sensor, el botón o el LED. Para eso realizamos distintas pruebas por separado. Probamos el LED externo conectado al pin 6, revisamos su polaridad, la conexión a GND y la salida PWM. También hicimos pruebas simples de encendido y apagado para comprobar que el LED respondiera de forma independiente al resto del sistema.

Además, verificamos que el botón demo siguiera funcionando, ya que este era clave para activar manualmente los estados del sistema durante la presentación. Revisamos que cada presión avanzara correctamente por la secuencia de estados: distancia 01, distancia 02, distancia 03, ausencia prolongada y retorno al modo sensor.

También revisamos el comportamiento lumínico del LED según cada estado: apagado en sin presencia, titileo lento en distancia 01, titileo más rápido en distancia 02, encendido fijo en distancia 03 y fade progresivo en ausencia prolongada. A nivel local, el sistema parecía responder correctamente, por lo que el problema principal se concentró en la conexión con Adafruit IO.

### Checklist de Adafruit IO

Para intentar encontrar el problema hicimos una revisión completa de conexión:

* revisamos el nombre del WiFi y la contraseña,
* comprobamos que el Arduino sí estuviera conectado a internet,
* revisamos el usuario de Adafruit IO,
* revisamos la IO Key,
* probamos con los datos escritos directamente en el código,
* probamos separar los datos en un archivo `config.h`,
* revisamos que el feed tuviera el mismo nombre en ambos tótems,
* probamos usar el feed como `TOTEM01` y luego como `totem01`,
* revisamos que no hubiera diferencias de mayúsculas, espacios o errores de escritura,
* probamos códigos mínimos solo para conectar a Adafruit,
* revisamos el monitor serial para leer los mensajes de error,
* y consideramos que la librería utilizada podía no estar funcionando bien con la placa.

Aun así, todo parecía estar correctamente escrito, pero la conexión no se lograba. Esto generó mucha confusión porque el mismo sistema había funcionado antes y no había una razón evidente para que dejara de hacerlo.

### Revisión del Tótem 02

El Tótem 02 también presentó problemas importantes. Inicialmente este tótem iba a recibir el dato desde Adafruit IO y mostrar el mensaje en una pantalla OLED. En versiones anteriores también habíamos probado el uso de un servo, pero decidimos eliminarlo porque no aportaba a una respuesta limpia y silenciosa. Por lo tanto, el Tótem 02 quedó pensado únicamente como una pantalla receptora.

Durante esta sesión, la pantalla OLED dejó de funcionar correctamente. Primero probamos con código para pantallas SSD1306, pero luego identificamos que la pantalla era SH1106, por lo que instalamos y probamos la librería U8g2. Aun así, la pantalla no mostraba texto de forma estable.

### Checklist de la pantalla OLED

Realizamos varias pruebas para detectar el problema:

* revisamos la conexión de VDD y GND,
* probamos alimentación con 3.3V y con 5V,
* revisamos que SCK de la pantalla fuera conectado a SCL de la placa,
* revisamos que SDA fuera conectado a SDA,
* probamos invertir SDA y SCK por si estaban cruzados,
* usamos código mínimo para mostrar “Iniciando...”,
* probamos con dirección I2C `0x3C` y `0x3D`,
* probamos escáner I2C,
* probamos conexión directa sin protoboard,
* cambiamos cables,
* cambiamos pantallas,
* probamos librerías distintas,
* bajamos la velocidad de comunicación I2C,
* ajustamos contraste,
* y probamos versiones de código sin Adafruit para aislar el problema.

En algún momento la pantalla alcanzó a prender, pero mostró texto distorsionado y luego dejó de mostrar información. También hubo momentos en que la pantalla se calentó, por lo que tuvimos que desconectarla inmediatamente para evitar dañarla más. Esto nos hizo pensar que podía existir un problema físico de conexión, alimentación, corto o daño en el módulo.

### Problemas de infraestructura

Además de los problemas electrónicos y de código, tampoco resultó como esperábamos el plan de infraestructura de los tótems con piezas 3D. La idea era integrar los componentes dentro de una estructura más limpia y terminada, pero el montaje no alcanzó a resolverse de la forma esperada. Esto afectó la estabilidad general del prototipo y la presentación física del sistema.

### Resolver desde el hechizo

Frente a este escenario, tuvimos que resolver desde lo que teníamos a mano. Al no funcionar la estructura planificada ni la conexión completa entre ambos tótems, apareció la idea de trabajar desde lo “hechizo”, tomando como referencia *Hechizos, por mientras para siempre*. Es decir, construir una solución provisoria, hecha con retazos, materiales encontrados y decisiones rápidas, pero que aun así pudiera sostener el sentido del proyecto.

Fuimos a buscar elementos disponibles para generar una nueva estructura a partir de fragmentos, soportes y piezas que no estaban pensadas originalmente para el montaje final. Esta solución no correspondía al plan inicial de infraestructura 3D, pero permitió mantener vivo el proyecto y responder al examen desde la realidad material del momento. En vez de insistir en una estructura que ya no estaba resultando, decidimos aceptar la falla y transformarla en parte del proceso.

El resultado final fue una especie de tótem resuelto desde la emergencia: armado con retazos, ajustes manuales y decisiones tomadas en el mismo momento. Aunque no era el montaje ideal, sí representaba muy bien lo que ocurrió durante la sesión: un sistema que tuvo que adaptarse, improvisar y encontrar una forma de existir incluso cuando todo parecía fallar.

### Conclusión final del proceso

Esta última sesión confirmó algo que suele repetirse en los procesos de creación y prototipado: todo lo que puede salir mal, probablemente va a salir mal, y muchas veces ocurre justo en el momento menos esperado. El día del examen, nada quiso resultar como estaba previsto. El Tótem 01 dejó de conectarse a Adafruit IO, el Tótem 02 perdió la estabilidad de la pantalla OLED, la estructura 3D no funcionó como esperábamos y tuvimos que resolver el montaje con soluciones de emergencia.

A pesar de eso, esta falla final no define todo el proceso. Durante el semestre sí logramos avanzar, probar, aprender y construir un sistema que en distintos momentos funcionó. Aprendimos a trabajar con sensores, LED, pantallas, botones, Adafruit IO, códigos de estado, conexión entre dispositivos y lógica de interacción física. También aprendimos a enfrentarnos a errores, a revisar conexiones, a hacer checklists, a probar por partes y a entender que un prototipo no solo se construye cuando funciona, sino también cuando falla.

Más allá del resultado técnico de este último día, nos quedamos con mucho más de lo que perdimos. Nos quedamos con los aprendizajes, con las pruebas, con los vínculos que se formaron en el proceso, con la compañía entre compañeras y compañeros, con la ayuda recibida, con las risas, el cansancio compartido y la experiencia de haber sostenido el proyecto hasta el final.

Aunque hoy nada quiso resultar, el semestre sí resultó. El proceso nos permitió aprender haciendo, equivocarnos, acompañarnos y entender que un proyecto no siempre se mide solo por su funcionamiento final, sino también por todo lo que se construye alrededor: las decisiones, los errores, los ajustes, los lazos y la capacidad de seguir resolviendo incluso cuando el sistema completo parece caerse.
