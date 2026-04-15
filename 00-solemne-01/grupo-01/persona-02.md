# persona-02

Monserrat Paredes Correa

investigaciones individuales

## Investigación Adafruit IO

Adafruit IO es un servicio en la nube de Adafruit para desarrollar proyectos de Internet de las Cosas (IoT). Permite a los usuarios conectar, monitorizar y controlar dispositivos y sensores IoT en línea sin escribir una sola línea de código.

También ofrece recursos y tutoriales para ayudar a los usuarios a iniciar sus proyectos de IoT.

Proyectos de IoT: son sistemas que conectan hardware (sensores/actuadores) a internet para monitorear y controlar dispositivos remotamente.

Incluye bibliotecas para lenguajes como CircuitPython, Arduino, Python y otros, lo que facilita la integración de dispositivos.
<https://io.adafruit.com/welcome>

## Investigación: Tutoriales de Adafruit IO

- Qué es Adafruit IO (plataforma IoT para almacenar y compartir datos).

- Cómo crear feeds (canales de datos).

- Cómo conectar hardware (Arduino / ESP) a internet.

- Cómo enviar (publish) y recibir (subscribe) datos.

## Conceptos clave aprendidos

- Feed: espacio donde se guardan datos (ej: contador).

- Publish: enviar datos a la nube.

- Subscribe: recibir datos desde la nube.

- Dashboard: visualización de datos.

IO_KEY: clave privada de acceso.

IO_USERNAME: usuario.

## Sirve para

- Enviar datos de sensores.

- Mandar estados o eventos.

- Ej: “botón presionado”, “LED encendido”.

- Ej: “botón presionado”, “LED encendido”.

- Visualizar datos en paneles.

- En Adafruit IO puedes ver gráficos en tiempo real.

## ¿Qué hace el código?

El ejemplo “Publicar” hace:

- Se conecta a tu WiFi.

- Se conecta a Adafruit IO con tu usuario y contraseña.

- Envía datos a un “feed” (como una variable online).

- Repita el envío cada cierto tiempo.

## Instalación en computador (MacBook Air M4)

Software utilizado:

- Arduino IDE
- Bibliotecas de Adafruit IO Arduino

## Proceso de instalación

- Abrir Arduino IDE.
- Dirigirse al menú lateral izquierdo, icono de Library Manager (ícono lateral izquierdo).
- Buscar: Adafruit IO Arduino.
- Instalar versión 4.3.4 (abril 2026) o superior.

<img width="445" height="386" alt="Libreria arduino" src="https://github.com/user-attachments/assets/d41cf0e5-0742-459a-81c9-512495ffe6f0" />


## Aprendizajes

- Las bibliotecas no funcionan solas: necesitan dependencias.

- Arduino automatiza la instalación, pero hay que aceptar manualmente.

- La versión de biblioteca puede afectar compatibilidad.


## Creación de cuenta en Adafruit IO

- Ingresar a la pagina: <https://io.adafruit.com/welcome>

- Crear cuenta gratuita (con correo UDP).

- Iniciar sesión.

- Acceder a credenciales.

Así se ve cuando creas la cuenta y configuraciones:


<img width="1244" height="785" alt="inicio sesion" src="https://github.com/user-attachments/assets/22641bc6-16a8-4bef-be95-4d321ec27b9f" />


Después de crear la cuenta se ve así el inicio de sesión:


<img width="1374" height="736" alt="inicio io" src="https://github.com/user-attachments/assets/176ee3ef-e288-40c9-aaba-d337fe1b199c" />


## Tener en cuenta por seguridad

NO subir claves a GitHub.

NO compartir públicamente.

Compartir solo por medios privados.

```cpp
#define IO_USERNAME "tu_usuario"
#define IO_KEY "tu_clave"
```

```cpp
#define WIFI_SSID "nombre_de_tu_red"
#define WIFI_PASS "password_de_tu_red"
```

Este archivo NO debe subirse completo a GitHub.

## Configuración del código

El sistema funciona con dos archivos:

- 5.1 Archivo principal .ino

## Contiene

- Conexión a Adafruit IO.

- Envío de datos.

- Lógica del programa.

- 5.2 Archivo config.h


## Desarrollo Proyecto solemne 01: En clases

Objetivo: Que los objetos "hablen" entre sí sin cables.

La idea es crear un puente invisible entre un aparato físico (Arduino r4 wifi) y un sitio en internet (Adafruit IO). Esto permite que el aparato mande información a la nube o que, desde un computador, le digas al aparato qué hacer, sin importar qué tan lejos estés.

## ¿Cómo funciona?

- Arduino (emisor): Es el "cerebro" que está en tu escritorio. Recoge datos y los traduce a un lenguaje que viaja por el aire.

- Wifi (mensajero): Es el túnel invisible que saca la información y la sube a internet.

- Adafruit IO (la central): Es como un panel de control en la web donde llegan todos los datos. Ahí se guardan, se ordenan y se muestran en una pantalla.

Objetivo: al presionar el botón enviara una señal al código para que diera la señal de 0 o 1 y luego visualizar los datos en  Adafruit IO para ver gráficos en tiempo real.

0= no presionar el botón.

1=presionar el boton.

## Elementos clave del código: usamos el wifi de la Vale

Credenciales obligatorias:

```cpp
define IO_USERNAME "vxlentiinaa"
```

```cpp
define IO_KEY "xxxx"
```

Sin esto, Arduino no puede conectarse.


## Función importante

```cpp
io.run();
```

Mantiene la conexión activa.

Permite recibir datos.


## Creación de feed

AdafruitIO_Feed *nombreFeed = io.feed("grupo01");

Define el canal de comunicación


## Envío de datos

nombreFeed->save(contador);

Envía datos a la nube


## Problemas durante el proceso

1.Caracteres extraños en monitor serial.

- Aparecían signos de interrogación (???)
  
- Causa: baudios incorrectos


<img width="621" height="530" alt="signos de interrogación arduino" src="https://github.com/user-attachments/assets/f9aefffe-a976-495b-8ea8-77d04a10206f" />


## Solución

- Código: Serial.begin(115200)

- Monitor serial estaba en 9600

- Se corrigió a 115200


<img width="1112" height="589" alt="Baudio auduino" src="https://github.com/user-attachments/assets/65ba7c18-ab59-43ae-88b0-3bdae3e7ecaf" />


## 2. El "Botón de Reset" accidental

Al conectar el pulsador al pin A0, se generó un puente eléctrico que replicó la función del botón de reinicio maestro de la placa. Esto permitió que, al presionar el botón en la protoboard, el Arduino se reiniciara por completo, tal como si hubieras presionado el botón rojo integrado en la placa.


El cableado o el contacto en la protoboard activó el sistema de Reset. Esto corta la corriente por un milisegundo y obliga al programa a empezar desde cero.


![conexiones](https://github.com/user-attachments/assets/6bfb2ee4-a20b-4b3c-a39b-f006728e982c)


![boton reset](https://github.com/user-attachments/assets/9651f897-9fdf-4552-9906-e6e76dd1af50)



Datos visualizados en Adafruit IO


<img width="1470" height="956" alt="prueba 1 grupo01" src="https://github.com/user-attachments/assets/06febfc2-47be-4c84-9614-2be0a94c92ba" />


## Código final funcional (Ya validado en clases)

- Envío de datos cada 3 segundos al presionar botón.

- Contador incremental.

- Conexión estable a Adafruit IO.


## Solución: Reasignación de Pines

Se movió la conexión del pulsador del pin A0 al Pin 1.


El conflicto eléctrico desapareció, permitiendo que el botón cumpliera su función real: enviar una señal digital que el Arduino procesa y transmite exitosamente a la nube en Adafruit IO.

<https://github.com/user-attachments/assets/7d37e7d6-8936-4bfe-80cf-9d870718c144>


Adafruit IO para ver gráficos en tiempo real con los datos enviados.


<img width="1470" height="956" alt="prueba 2 grupo01" src="https://github.com/user-attachments/assets/7f8acb54-61d5-4375-9776-09911aa10fb1" />


<img width="1470" height="956" alt="prueba 3 grupo01" src="https://github.com/user-attachments/assets/bfdf2bf6-948d-4b50-9b00-93c9e9332339" />



## Reflexión del proceso

Aprendizajes técnicos:

- Diferencia entre hardware, software y firmware.

- Importancia de la configuración de red.

- Uso de plataformas IoT.

- Comunicación entre dispositivos remotos.


Aprendizajes prácticos:

- Los errores más comunes son simples (baudios, claves).

- La conexión WiFi es el punto más crítico.

- Separar credenciales en config.h es buena práctica.

- En Adafruit IO, te da la llave para colocar en el código en arduino.

- El delay(3000) evita sobrecargar la plataforma (limitación de escritura).

Siempre hay que colocar esa línea, para que el arduino no olvide el adafruit IO


```cpp
io.run();
```

Es para ver lo que manda el otro arduino en adafruit


```cpp
io.feed();
```

## Código que si funciona + el config.hes donde se guarda la clave de Adafruit IO y la clave de wifi

```cpp
// Adafruit IO Publish Example
//
// Adafruit invests time and resources providing this open source code.
// Please support Adafruit and open source hardware by purchasing
// products from Adafruit!
//
// Written by Todd Treece for Adafruit Industries
// Copyright (c) 2016 Adafruit Industries
// Licensed under the MIT license.
//
// All text above must be included in any redistribution.

// ejemplo para enviar / publish
// por montoyamoraga
// para disenoUDP
// basado en
// Adafruit IO Publish Example

// incluir archivo config.h
// hacer las modificaciones de este archivo
// NO subir a github

# include "config.h"

// esta variable entera
// sera un contador que aumenta
// durante el funcionamiento del software
int contador = 0;

// definir una variable que se llame nombreFeed
// que tenga un cierto valor
// mantener las doble comillas, cambiar grupoXX segun tu nombre de grupo
AdafruitIO_Feed *nombreFeed = io.feed("grupo01");

void setup()
{

  // prender la conexion serial
  // ojo con la velocidad de 115200 baud
  // cuando abras el monitor serial debes configurarlo
  // a este numero, porque el standard de fabrica es 9600 baud
  Serial.begin(115200);

  // estas lineas pausan el codigo
  // hasta que prendas el monitor serial
  // la lupita arriba a la derecha en Arduino IDE
  while (!Serial)
    ;

  // imprimir en consola
  Serial.print("conectando a Adafruit IO");

  // conectarse a io.adafruit.com
  io.connect();

  // esperar la conexion
  while (io.status() < AIO_CONNECTED)
  {
    // imprimir un punto cada medio segundo
    // mientras se conecta
    Serial.print(".");
    delay(500);
  }

  // demostrar que logramos conexion
  Serial.println();
  Serial.println(io.statusText());
}

void loop()
{

  // esta linea es necesaria
  // al principio de loop()
  // para mantener la conexion
  // y procesar datos que lleguen
  io.run();

  // enviar el contador a Adafruit IO
  // primero mostrar en monitor serial
  Serial.println("enviando -> " + String(contador));
  // despues enviar a la nube
  nombreFeed->save(contador);

  // incrementar el contador en 1
  contador = contador + 1;

  // Adafruit IO tiene una velocidad limitada
  // de escritura / publishing
  // usamos delay para pausar el codigo 3 segundos
  delay(3000);
}
```

## Investigación: Arte y tecnología inalámbrica

Gilberto Esparza

Reside en San Miguel de Allende y la Ciudad de México.

Graduado de la Escuela de Artes Plásticas de la Universidad de Guanajuato y un año de intercambio en la Facultad de Bellas Artes de San Carlos en Valencia, España.

Investiga la tecnología como posibilidad para plantear preguntas y soluciones a los impactos de la huella humana sobre la vida en la tierra, a partir de una reivindicación de la inteligencia inherente a la vida y replanteando la relación de las sociedades humanas con el entorno natural.

Conocido por su proyecto: Plantas Nómadas.

Plantas Nómadas es un proyecto de investigación que surge de reflexionar sobre los impactos ambientales y sociales que genera la actividad humana.

Es una especie híbrida, conformada por diversos organismos que coexisten en simbiosis para sobrevivir en entornos contaminados. El agua, fuente de energía vital para la sobrevivencia, es uno de los recursos más afectados por la contaminación.

Sus obras son robots biotecnológicos que viven en entornos de ríos contaminados.

- La Tecnología: Utiliza celdas de combustible microbianas que generan electricidad a partir de la descomposición de materia orgánica en el agua.

- Inalámbrico/IoT: El robot se desplaza de forma autónoma buscando agua contaminada para "alimentarse". Transmite datos sobre la calidad del agua y su propia ubicación, creando un mapa vivo de la degradación ambiental. Es, literalmente, un "sensor vivo" que habita la ciudad.


Fotos del proyecto:

![plantas nomadas1](https://github.com/user-attachments/assets/4a845657-1d32-436e-b5f1-31cf06fae21d)

![plantas nomadas2](https://github.com/user-attachments/assets/12098d65-fc21-40b3-816b-1f9296989a3f)


Dibujo de la contaminación (problematica)


<img width="1470" height="956" alt="plantas nomadas4" src="https://github.com/user-attachments/assets/c39dbe2f-59db-46e8-9725-92ee6973f528" />


Planta Nómada Fitocrista errantis:


<img width="901" height="1030" alt="plantas nomadas3" src="https://github.com/user-attachments/assets/8b325e61-9955-4f7e-b968-e2413661cb5a" />


Uso de Tecnología: Robótica autónoma y sensores de agua.

Así como nosotros configuramos una clave de WiFi para que nuestro Arduino se conecte, Gilberto Esparza configura sus robots para que 'entiendan' la red de contaminación de un río, transformando un dato invisible en una acción física.

## Información sacada

Biografía: <https://gilbertoesparza.net/bio/>

Proyecto: <https://gilbertoesparza.net/portfolio/plantas-nomadas/>

Video descriptivo: <https://www.youtube.com/watch?v=US9q2ayKANk&t=2s>

Redes sociales: <https://www.instagram.com/gilbertoesparzaglez/>

