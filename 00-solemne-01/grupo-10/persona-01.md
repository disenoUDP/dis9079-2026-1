# persona-01

investigaciones individuales

## sobre adafruit i/o

### Aprendido sobre Arduino IO

Como mi primer ramos sobre conexiones, al principio todo es muy nuevo entonces empecé a investigar sobre arduino IO y su método de uso. Ya que va siendo una plataforma para la creación de proyectos y controlar placas Arduino haciendo posible controlar dispositivos como sensores y luces. Al momento de instalar Arduino y las bibliotecas solicitadas hubo un momento donde me encontré con un error el cual al momento de corregirlo quise ver que más se podía llegar a hacer con la placa asi que busque codigos para ver que todo funcionara bien además de subir los códigos de la clase, de esta manera fui aprendiendo sobre los códigos como es que se suben a la plataforma y sobre qué se puede ir modificando para personalizarlo.

![proceso](./imagenes/aa_aprendido_1.jpg)

![proceso](./imagenes/aa_aprendido_2.jpg)

![proceso](./imagenes/aa_aprendido_3.jpg)

### Proceso de instalación

Al momento de instalar Arduino lo fui haciendo siguiendo la clase cada momento y a la vez leyendo la clase del dia, luego fijarse bien si instale la version correcta para el mac e instalar las bibliotecas Library Manager -> ArduinoMQTTClient (v0.1.8 o más reciente) y Library Manager -> ArduinoGraphics, ademas de Boards Manager -> Arduino Uno R4 Boards (v1.5.3 o más reciente).

![instalacion](./imagenes/aa_instalacion_arduino.png)
![instalacion](./imagenes/aa_instalacion_bibliotecas.png)

### Dificultades encontradas

Al momento de instalar Arduino IO y las bibliotecas no me encontré con ningún problema, hasta que mande un código al Arduino y me aparece este error, luego de la clase intente solucionarlo pero no me funcionaba, asi que a la semana siguiente considere en volver a instalar la aplicación y todo de nuevo, pero me seguia apareciendo este error asi que segui investigando, toda la información que buscaba me salia que el programa que Arduino está intentando ejecutar no es compatible con el tipo de procesador de tu computador. Entonces seguí buscando hasta que me salio Rosetta que era algo que le faltaba a mi computador y que se lo instalara a la aplicación, en el momento no sabía lo que era hasta que lo comente en clases que solucione mi error y ahi me comentaron que Rosetta en Mac permite ejecutar el IDE de Arduino (basado en Intel) en computadoras con procesador Apple Silicon (M1/M2/M3).

```txt
/Users/agustina/Library/Arduino15/packages/arduino/tools/arm-none-eabi-gcc/7-2017q4/bin/arm-none-eabi-g++: bad CPU type in executable Compilation error: fork/exec /Users/agustina/Library/Arduino15/packages/arduino/tools/arm-none-eabi-gcc/7-2017q4/bin/arm-none-eabi-g++: bad CPU type in executable
```

## sobre artista, diseñadora o producto que usa electrónica o computación inalámbricas

### Sougwen Chung

#### La marca recursiva

La artista pinta en conjunto a dos brazos robóticos conectados a su cuerpo mediante datos de ondas cerebrales EEG en tiempo real. En la obra, esta estructura es tanto computacional como genealógica donde el sistema se basa en una red neuronal que entrenó con sus archivos artísticos, mientras pinta, lleva un sensor EEG personalizado que captura su actividad cerebral en tiempo real ya que diferentes ondas modulan la respuesta gestual del modelo, creando un bucle recursivo en el que los gestos anteriores generan nuevas trayectorias a las que el artista responda.

Su trabajo combina dibujo tradicional, inteligencia artificial y robótica para crear piezas donde la máquina no es solo una herramienta, sino un colaborador activo. Esto genera una nueva forma de creación en la que el proceso artístico se vuelve compartido, desafiando la idea clásica del artista como único autor.

A nivel conceptual, su trabajo aborda temas como la autoría, el control y la colaboración entre humanos y sistemas tecnológicos. Plantea preguntas sobre quién crea realmente la obra y hasta qué punto la inteligencia artificial puede considerarse creativa. Además, investiga cómo los gestos humanos pueden ser traducidos a lenguaje digital, generando una fusión entre lo físico y lo virtual.

![artista](./imagenes/aa_Sougwen_Chung.png)

## Bibliografía

* Adafruit Industries. Welcome to Adafruit IO.

<https://learn.adafruit.com/welcome-to-adafruit-io>

* Adafruit Industries. Overview – Adafruit IO.

<https://learn.adafruit.com/welcome-to-adafruit-io/overview>

* Arduino.cl. ¿Qué es Arduino?

<https://arduino.cl/que-es-arduino/?srsltid=AfmBOor0ej-rGLhlM8f_la78G_qm3S8-8UQ18gRQRC8L37uKfZ8_er8E>

* Adafruit Industries. Adafruit IO Basics: Dashboards.

<https://learn.adafruit.com/adafruit-io-basics-dashboards>

* Arduino.cl. Arduino Uno R4 WiFi.

<https://arduino.cl/producto/arduino-uno-r4-wifi/?srsltid=AfmBOopoBEQvXbbSHon7xpm72ttyMdjYAgu8pn7mpKxAITS9lm2aqAUZ>

* Arduino. Getting Started with Arduino Uno R4 WiFi.

<https://docs.arduino.cc/tutorials/uno-r4-wifi/r4-wifi-getting-started/>

* Sougwen Chung. Sitio oficial.

<https://sougwen.com/>

* The Art Newspaper. The human-machine creative entanglement: Sougwen Chung.

<https://www.theartnewspaper.com/2026/03/26/the-human-machine-creative-entanglement-artist-sougwen-chung-on-her-technology-based-practice>
