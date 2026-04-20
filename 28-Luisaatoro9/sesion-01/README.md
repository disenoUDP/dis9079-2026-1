# sesion-01 - lunes 09 marzo 2026
Sesión 01: Introducción a la Computación Física e IoT

La primera clase fue una inmersión a lo que será el semestre. Presentaron al equipo (Aarón Montoya y Mateo Arce) y nos dieron el contexto de la metodología: trabajar en equipo con el Arduino Uno R4 WiFi, instalando nuestros propios entornos de desarrollo.

## Conceptos Clave y Protocolos

Aprendimos sobre la infraestructura que permite que los objetos se "hablen" entre sí. Estos fueron los puntos que más me llamaron la atención para investigar:

* **IoT (Internet of Things):** Es la red de objetos físicos con sensores y software que intercambian datos. La idea es conectar lo físico a la nube para tomar decisiones en tiempo real.
* **Protocolos de Comunicación:**

   * **MQTT:** Es un protocolo "ligero" diseñado para que dispositivos con poca batería o internet inestable (como nuestro Arduino) manden mensajes cortos de forma eficiente. Funciona con un sistema de Publicar/Suscribir, lo que permite que muchos aparatos se hablen entre sí a través de un servidor central sin colapsar la red.
   * **OSC (Open Sound Control):** Es un sistema ultra rápido para que el Arduino se comunique con computadores y equipos de música por WiFi. Lo mejor es que usa mensajes fáciles de leer (como carpetas de archivos) y es mucho más preciso que el antiguo MIDI para controlar interacciones en tiempo real.

* **Semiótica en el diseño:** Se trata de entender cómo los elementos (iconos, colores, luces) actúan como signos que el usuario interpreta. En nuestro proyecto, la semiótica es clave para que cuando el Arduino prenda una luz o cambie un gráfico, la persona entienda de inmediato qué está pasando sin tener que leer un manual.En resumen, Cómo interpretamos los signos y qué significan en la interacción digital.

## Referentes 

El profe mencionó nombres y herramientas que son base para lo que viene:

  * **Rafael Lozano-Hemmer:** Es un artista electrónico que usa la tecnología para que las obras interactúen directamente con la gente. Lo que más me llamó la atención es su concepto de que "la obra mira al público"; usa sensores, cámaras y datos (como los latidos del corazón o la sombra de las personas) para que el arte cambie y responda en tiempo real a quien lo está viendo.
<div align="center"> <img src="https://github.com/user-attachments/assets/ed65b26f-9796-43b9-94b6-812822d057cb" width="400"><p><b>Imagen 01</p> </div> 
 
  * **Casey Reas:** Es uno de los padres de Processing, el lenguaje de programación que nos permite "dibujar con código". Me llamó la atención que para él, el código no es solo para que un computador funcione, sino que es una herramienta artística para generar sistemas visuales que cambian solos.
  <div align="center"> <img src="https://github.com/user-attachments/assets/5974be5b-2766-4cf7-b7de-87fdfea39417" width="400"><p><b>Imagen 02</p> </div>
    
  * **Muriel Cooper:** Fue una visionaria del diseño en el MIT que, mucho antes de que existieran las pantallas modernas, ya estaba experimentando con cómo mezclar el diseño gráfico con la computación. Me impresionó que ella fue de las primeras en pensar que el diseño digital no tenía que ser plano, sino que podía tener movimiento, profundidad y capas, cambiando para siempre cómo interactuamos con las interfaces hoy en día.
  <div align="center"> <img src="https://github.com/user-attachments/assets/626e14f9-f0d8-4bcf-9170-e40ce420e0c2" width="400"><p><b>Imagen 03</p> </div>
    
  * **Flutter:** Es una herramienta que nos permite crear apps "nativas" (que corren rápido) tanto para Android como para iOS, pero usando un solo código base. Para nuestro curso es clave porque nos permite armar dashboards en el celular para controlar el Arduino de forma fácil y con una interfaz fluida.
  <div align="center"> <img src="https://github.com/user-attachments/assets/23d48830-1abd-405a-8d65-555acd25288d" width="400"><p><b>Imagen 04</p> 
  

<div align="left">

### Referencias

* AcademiaLab. (s.f.). *Casey Reas: Biografía y obra*. https://academia-lab.com/enciclopedia/casey-reas/

* Amazon Web Services (AWS). (s.f.). *¿Qué es Flutter? - Explicación técnica*. https://aws.amazon.com/what-is/flutter/

* El Universal. (s.f.). *Ahora son las obras las que miran al público: Rafael Lozano-Hemmer*. https://confabulario.eluniversal.com.mx/ahora-son-las-obras-las-que-miran-al-publico-rafael-lozano-hemmer/

* Future Music España. (s.f.). *El protocolo Open Sound Control (OSC) enriquece la producción musical*. https://www.futuremusic-es.com/protocolo-open-sound-control-osc-enriquece-produccion-musical/

* MIT Press. (s.f.). *Celebrating Muriel Cooper’s legacy on World Design Day*. https://mitpress.mit.edu/celebrating-muriel-coopers-legacy-on-world-design-day/

* MQTT.org. (s.f.). *MQTT: The Standard for IoT Messaging*. https://mqtt.org/

* UNIR México. (s.f.). *¿Qué es la semiótica en el diseño gráfico?*. https://mexico.unir.net/noticias/ingenieria/que-es-semiotica-diseno-grafico/
