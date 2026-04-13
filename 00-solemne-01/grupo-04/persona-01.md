# persona-01
# Antonella Lavalle

investigaciones individuales

## sobre adafruit i/o

Adafruit IO es una plataforma en la nube diseñada para gestionar datos de dispositivos físicos conectados a internet (IoT), poniendo énfasis en la visualización, interacción en tiempo real y facilidad de uso. Fue desarrollada por Adafruit, una empresa muy conocida en el mundo del hardware abierto y la educación tecnológica.

Adafruit IO funciona como un intermediario entre el mundo físico y el mundo digital.

+ Traduce fenómenos físicos (temperatura, luz, sonido, presencia, etc.) en datos digitales
+ Permite almacenar esos datos en servidores remotos (la nube)
+ Te deja interactuar con esos datos desde interfaces visuales o desde otros sistemas

## Estructura interna

## Feeds (flujos de datos)

+ Cada feed almacena una variable
+ Funciona como una línea temporal de datos
+ Puedes leer y escribir en ellos

## Dashboards (interfaces visuales)

* Ver datos en gráficos (líneas, gauges, indicadores)
* Crear botones o sliders para enviar comandos

Es básicamente una interfaz gráfica conectada a los feeds

## Blocks (componentes visuales)

Dentro de los dashboards

* Gráficos
* Interruptores
* Indicadores
* Mapas, texto, etc.

Cada block está vinculado a un feed

## Triggers (automatización)

Permiten crear reglas del tipo:

+ *Si pasa X → entonces hacer Y*

Ejemplo: Si temperatura > 30°C → enviar notificación o activar dispositivo

## Integraciones

Adafruit IO se puede conectar con:

+ Dispositivos físicos (Arduino, ESP8266, ESP32)
+ APIs externas
+ Otras plataformas (como IFTTT)

## Comunicación (parte técnica clave)

## MQTT (Message Queuing Telemetry Transport)

+ Protocolo ligero, ideal para dispositivos con poca potencia
+ Funciona por publish/subscribe:

  + Un dispositivo “publica” datos
  + Otros “se suscriben” para recibirlos

## HTTP

+ Más simple pero menos eficiente en tiempo real
+ Funciona con solicitudes tipo GET/POST

## Ventajas

+ Muy accesible 
+ Visualización rápida sin programar interfaces complejas
+ Integración directa con hardware educativo

## Limitaciones

+ No es tan potente como soluciones industriales
+ Tiene límites en la versión gratuita
+ Dependes de conexión a internet

## sobre artista, diseñadora o producto que usa electrónica o computación inalámbricas

## Golan Levin

Golan Levin es un artista, programador y diseñador estadounidense clave en el campo del arte digital interactivo. Su trabajo se sitúa entre el arte, la tecnología y la comunicación, explorando cómo las personas pueden interactuar con sistemas computacionales en tiempo real.

+ Se enfoca en la interacción humana con máquinas: sus obras reaccionan al movimiento, la voz o el comportamiento del público.
+ Mezcla código, imagen, sonido y participación.
+ Sus proyectos suelen ser lúdicos, pero también críticos: cuestionan cómo nos relacionamos con la tecnología.

Tipos de obras que hace.

+ Instalaciones interactivas: espacios donde el espectador activa la obra.
+ Performance audiovisual: combina música, visuales generados en vivo y programación.
+ Software creativo: desarrolla herramientas para artistas y diseñadores.

## Messa di Voce
2003 | Tmema (Golan Levin y Zachary Lieberman) con Jaap Blonk y Joan La Barbara

<img width="665" height="356" alt="image" src="https://github.com/user-attachments/assets/ef4a5584-97c9-4634-a408-e85405b5580c" />

+ Messa di Voce combina la voz humana (habla, canto y sonidos) con visualizaciones interactivas en tiempo real, donde un software transforma los matices vocales en gráficos expresivos. La obra explora temas como la comunicación, la sinestesia y el lenguaje, situándose entre la interpretación humana y la tecnología. A través de esta fusión, genera una experiencia audiovisual que reflexiona sobre el significado y los efectos del sonido y el lenguaje en un entorno inmersivo.

+ La obra evidencia la invisibilidad de la infraestructura tecnológica, ya que la interacción se realiza únicamente mediante la voz, lo que se vincula con la computación inalámbrica como un sistema integrado y transparente en el entorno.

+ Funciona a través de un flujo continuo de datos en tiempo real, donde la voz es capturada, procesada y transformada inmediatamente en visualizaciones, siguiendo la lógica de los sistemas conectados actuales además, propone una interacción continua, en la que la voz actúa como un flujo constante de información que modula el sistema, en contraste con interfaces basadas en acciones puntuales.

## Bibliografía

https://www.flong.com/archive/bio/en/index.html

https://www.flong.com/archive/projects/messa_inst/index.html

https://learn.adafruit.com/welcome-to-adafruit-io

https://learn.adafruit.com/series/adafruit-io-basics

https://learn.adafruit.com/mqtt-adafruit-io-and-you/getting-started-on-adafruit-io
