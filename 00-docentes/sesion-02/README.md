# sesion-02

lunes 16 marzo 2026

para empezar, hagamos grupos de entre 2 y 3 personas, recordar que somos 31 estudiantes. cada grupo debe responder en discord los números de lista y etiquetar

## Discord

nos unimos al servidor de discord del laboratorio de interacción digital, que es un lugar virtual y también físico, recordar que estamos en salvador sanfuentes 2221, tercer piso.

les pedimos usar nombre-apellido como nombre de usuario, para facilitar la comunicación. les etiquetamos con la sigla del curso, para poder mencionar con @ a toda la gente del curso cuando sea necesario.

## GitHub

en este curso, y en los cursos y talleres de la nueva mención de interacción digital estamos utilizando la plataforma GitHub.

una de las razones para usar GitHub es que nos da muchas facilidades para compartir archivos, mantener bitácoras públicas, escribir documentación técnica, y manejar control de versiones.

como UDP estamos certificades como GitHub Campus, por lo que tenemos acceso a herramientas profesionales de forma gratuita. también hay beneficios por usar una cuenta educacional, descritos en el apartado de GitHub Education.

les pedimos hacer fork del repositorio del curso, y que en sus forks incluyan sus apuntes, que usaremos como asistencia.

les recomendamos trabajar desde GitHub en la web, y también instalar la app en sus dispositivos móviles.

## Markdown

para la documentación de los proyectos y los apuntes del curso, usaremos Markdown, un lenguaje diseñado para escribir, formatear y jerarquizar texto de forma rápida.

existen muchos manuales de cómo escribir con markdown y en github, les recomendamos revisar repositorios de otros cursos de diseño udp, tanto de este semestre como de semestres pasados.

## Arduino IDE

para trabajar con Arduino, necesitamos instalar el software Arduino IDE, disponible en la web <https://www.arduino.cc/en/software/#ide>

en marzo 2026 al momento de escribir estos apuntes, es la versión 2.3.8, disponible para Windows, macOS y Linux. para la gente trabajando en Mac, ojo
con la versión de macOS, si es un computador con procesador Apple o Intel, que son los más antiguos.

dentro de este software estaremos investigando y usando varias bibliotecas adicionales, en particular para esta primera sesión necesitamos instalar 3 herramientas:

1. Boards Manager -> Arduino Uno R4 Boards (v1.5.3 o más reciente)
2. Library Manager -> ArduinoMQTTClient (v0.1.8 o más reciente)
3. Library Manager -> ArduinoGraphics (v1.1.4 o más reciente)

## Visual Studio Code

para los ejercicios más simples de Arduino, será suficiente con Arduino IDE, pero para proyectos más complejos, recomendamos instalar Visual Studio Code, un editor de código más avanzado, disponible en <https://code.visualstudio.com/>

## Homebrew

para la gente trabajando en un computador Mac, recomendamos instalar Homebrew, un gestor de herramientas de líneas de comandos, que facilita su instalación y actualización, disponible en <https://brew.sh/>.

con Homebrew pueden instalar herramientas que usaremos en este curso como Mosquitto, un broker de MQTT, que se puede instalar con el comando

```bash
brew install mosquitto
```

## Arduino Uno R4 Wifi

en este curso usaremos la placa de desarrollo Arduino Uno R4 WiFi.

esta placa es una nueva versión del ya clásico Arduino Uno R3, el que fue lanzado en 2011, y se convirtió en un estándar en la enseñanza y prototipado de proyectos de computación física <https://en.wikipedia.org/wiki/Physical_computing>. usa el chip ATMEGA328P.

la placa Arduino Uno R4 WiFi fue lanzada el año 2023, tiene varias mejoras como la inclusión de WiFi, conector USB-C, un procesador más potente del fabricante Renesas, y también incluye una pequeña pantalla de 12 x 8 pixeles.

## lenguaje Arduino

usaremos la palabra Arduino para referirnos a 3 cositas distintas:

1. la placa de desarrollo, en nuestro caso, el microcontrolador Arduino Uno R4 WiFi.
2. el software Arduino IDE, donde escribiremos el código que correrá en la placa.
3. el lenguaje de programación, que es un dialecto del lenguaje C++, con funciones y bibliotecas diseñadas para facilitar la programación.

Un código en Arduino tiene la siguiente estructura básica

```cpp
void setup() {

}

void loop() {

}
```

al igual que en Processing, el código en Arduino tiene dos funciones principales:

- setup(): esta función corre una sola vez, al inicio del programa. se usa para configurar estado inicial y configurar entradas y salidas.
- loop(): esta función corre después de setup(), y se repite en bucle infinito. se usa para escribir código que actualiza el estado del programa, como lectura de sensores, procesamiento de información, y control de actuadores.

## ejemplo00

```cpp
// ejemplo00
// imprime la sigla del curso en el monitor serial
// luego espera 1 segundo e imprime :)
// funciona con Arduino Uno R4 WiFi
// marzo 2026
// por montoyamoraga para disenoUDP

// crear instancia de ArduinoLedMatrix
// con nombre pantalla
ArduinoLEDMatrix pantalla;

void setup() {
  // iniciar puerto serial
  Serial.begin(9600);
}

void loop() {
  // imprimir en consola
  Serial.println("dis9079");
  // esperar un segundo
  delay(1000);

  // imprimir en consola
  Serial.println(":)");
  // esperar un segundo
  delay(1000);
}
```

## ejemplo01

```cpp
// ejemplo01
// imprime la sigla del curso en la pantalla led
// de la Arduino Uno R4 WiFi
// basado en
// https://docs.arduino.cc/tutorials/uno-r4-wifi/led-matrix/#scrolling-text-example
// marzo 2026
// por montoyamoraga para disenoUDP

// incluir bibliotecas
#include <ArduinoGraphics.h>
#include "Arduino_LED_Matrix.h"

// declarar instancia de ArduinoLEDMatrix
// con nombre pantalla
ArduinoLEDMatrix pantalla;

void setup() {

  // iniciar puerto serial
  Serial.begin(115200);

  // inicializar pantalla
  pantalla.begin();

}

void loop() {

  // definir nuevo dibujo
  pantalla.beginDraw();

  // definir trazo
  pantalla.stroke(0xFFFFFFFF);

  // definir velocidad de deslizamiento
  pantalla.textScrollSpeed(100);

  // definir texto
  const char texto[] = "    diseno udp dis9704 interacciones inalambricas    ";
  
  // definir tipo
  pantalla.textFont(Font_5x7);

  // definir inicio del texto
  pantalla.beginText(0, 1, 0xFFFFFF);

  // imprimir el texto
  pantalla.println(texto);

  // deslizar hacia la izquierda
  pantalla.endText(SCROLL_LEFT);

  // fin del dibujo
  pantalla.endDraw();
}
```

## mosquitto

mosquitto es un broker de MQTT, que se encarga de recibir y distribuir mensajes entre clientes MQTTT.

hoy nos conectaremos a mi celular que tiene una red de wifi local, y usaremos mosquitto para enviar mensajes entre dispositivos conectados a esa red.

para nuestra clase preparamos un archivo de configuración de mosquitto, que usaremos así.

```bash
mosquitto -c mosquitto.conf
```

## ejemplo02

```cpp

```

## enlaces

<https://mosquitto.org/documentation/authentication-methods/>
