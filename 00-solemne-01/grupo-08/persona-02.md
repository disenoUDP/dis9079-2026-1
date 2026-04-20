# Luisa Toro

investigaciones individuales

## Introducción

Mi investigación para la Solemne 01 no se quedó solo en el cambio de plataforma; se centró en entender cómo lograr una comunicación inalámbrica robusta integrando el Arduino R4 WiFi, la nube de Adafruit IO y el software de Arduino.

Durante las primeras pruebas en la sala, el uso de Mosquitto nos dio muchísimos problemas de conexión. Aprendí que esto pasaba por las restricciones de seguridad de la red de la universidad, que bloqueaban el puerto 1883 (el estándar de MQTT local) y más errores que algunos no logré entender bien.

La Solución: Para solucionar estas fallas, investigamos la opción de Adafruit IO. La gran ventaja es que este broker en la nube permite conexiones vía MQTT sobre WebSockets en el puerto 443. Como este puerto es el mismo que usa el tráfico web normal (HTTPS), logramos saltarnos los bloqueos del firewall y tener una comunicación fluida y estable desde cualquier computador.

## El Corazón del Proyecto: Comunicación Inalámbrica

Mi semana de Solemne partió literal desde la base. El lunes en la clase me di cuenta de que para que el Arduino haga algo "inalámbrico", primero hay que armarle todo un ecosistema en el computador y en la nube. No es llegar y conectar.

Una vez superado el problema de la red, mi investigación se volcó a la interacción en tiempo real. Aquí aprendí conceptos que son el motor de nuestro proyecto:

1. Protocolo MQTT: Es el "idioma" inalámbrico. Aprendí que es ideal para el IoT porque es súper liviano. Mi Arduino se suscribe a un canal (Feed) y se queda esperando órdenes sin saturar la red.
2. Gestión de Datos (Feeds): Entendí que la comunicación inalámbrica no es solo enviar un dato al aire; es una base de datos organizada. Adafruit guarda el último estado enviado, lo que hace que la conexión sea mucho más confiable que un mensaje simple.

Paso 0: Preparando el terreno (Software)

Aunque yo ya tenía instalado el Arduino IDE de antes, decidí revisar la página oficial para asegurarme de tener la última versión.

<div align="center"> <img src="https://github.com/user-attachments/assets/e74d5b97-7e05-4ad1-ba25-a14db8a04098" width="80%" alt="Descarga Arduino IDE"> <p><i><b>Imagen 01:</b> Punto de partida. Aunque ya tenía el programa instalado de antes, verifiqué en la página oficial que fuera la versión <b>2.3.8</b> para asegurar la compatibilidad total.</i></p> </div>

**Creando mi identidad en la nube (Adafruit IO)**

Paso 1: Lo primero que hice fue crearme la cuenta en Adafruit IO. Al principio no entendía mucho para qué servía, pero después caché que es como el "cerebro" en la nube que va a recibir los datos de mi placa.

<table style="width: 100%; border: none;"> <tr> <td style="width: 50%; border: none; text-align: center;"> <img src="https://github.com/user-attachments/assets/bdb6d761-7fd0-40e8-98f7-01da73422279" width="100%" alt="Tutorial Adafruit IO"> <p><i><b>Imagen 02:</b> Video tutorial que seguí para entender el ecosistema de Adafruit IO.</i></p> </td> <td style="width: 50%; border: none; text-align: center;"> <img src="https://github.com/user-attachments/assets/7952a9eb-b332-48ba-8df7-c20f7744efff" width="100%" alt="Cuenta Creada"> <p><i><b>Imagen 03:</b> Mi cuenta de Adafruit IO ya creada y configurada para recibir datos.</i></p> </td> </tr> </table>

* **La famosa AIO Key:** Apenas entré, busqué mi "Key". Es una clave gigante que te dan y aprendí que es súper secreta. El profe nos recalcó mil veces que si la subimos a GitHub, cualquiera puede meterse a nuestro proyecto, así que tuve que tener mucho cuidado de no dejarla pegada en el código principal.
* **Armando el "buzón" (Feeds):** Creé mi primer Feed. Me costó un poco entender el concepto, pero al final lo vi como un buzón: mi Arduino tira una carta ahí y el Dashboard la lee.

<table style="width: 100%; border: none;"> <tr> <td style="width: 50%; border: none; text-align: center;"> <img src="https://github.com/user-attachments/assets/5d380a01-39e2-4220-aaa2-e3dbbaef625e" width="100%" alt="Configuración de Feeds"> <p><i><b>Imagen 04:</b> Este es el "buzón" donde mi Arduino revisa si llegaron mensajes nuevos para mostrar en su pantalla LED.</i></p> </td> <td style="width: 50%; border: none; text-align: center;"> <img src="https://github.com/user-attachments/assets/75d786b1-3ce3-44a0-887a-860d2d3cb948" width="100%" alt="Detalles de la App"> <p><i><b>Imagen 05:</b> Vista de la App donde revisé los tokens y la información técnica de la cuenta.</i></p> </td> </tr> </table>

Paso 2: Después de las cuentas de Adafruit, me pasé al Arduino IDE. Yo ya lo tenía instalado, pero aprendí que para que la placa hable con internet, el programa necesita "superpoderes" extra que vienen en la biblioteca.

1. Instalación manual: Busqué la biblioteca Adafruit IO Arduino (versión 4.3.4).
2. Las dependencias: Cuando le di a "Install", me saltó un aviso gigante preguntando si quería instalar un montón de cosas más. Al principio me dio susto, pero entendí que son como los "ayudantes" de la biblioteca principal (como HttpClient y Adafruit_MQTT). Sin ellos, el código simplemente no compila porque le faltarían piezas clave.
3. Logro: Una vez que terminó la descarga, mi IDE ya estaba listo para escribir código que se conectara a la nube.

<table style="width: 100%; border: none;"> <tr> <td style="width: 50%; border: none; text-align: center;"> <img src="https://github.com/user-attachments/assets/5a4465ad-acee-497f-9a16-1e36107cf345" width="115%" alt="Instalación de Librerías 01"> <p><i><b>Evidencia 06:</b> Buscando la biblioteca <b>Adafruit IO Arduino</b> en el Library Manager.</i></p> </td> <td style="width: 50%; border: none; text-align: center;"> <img src="https://github.com/user-attachments/assets/8a412aa3-3d25-41ac-8fec-88104af41b5c" width="115%" alt="Instalación de Librerías 02"> <p><i><b>Imagen 07:</b> Proceso de instalación de dependencias. Se instalaron todos los "ayudantes" necesarios para la comunicación WiFi.</i></p> </td> </tr> </table>

Hallazgos Técnicos Clave:

* **Protocolo y Puertos:** A diferencia de Mosquitto local (que nos dio problemas de permisos en el puerto 1883), Adafruit IO permite conexiones vía MQTT sobre WebSockets (puerto 443). Esto es fundamental porque el tráfico se ve como tráfico web normal (HTTPS), saltándose los firewalls de Windows.
* **Arquitectura de Datos (Feeds):** Entendí que Adafruit IO organiza todo por "Feeds". No es solo enviar un dato al aire; es una base de datos de series temporales. Esto significa que si mi Arduino se desconecta un segundo de la WiFi de la U, Adafruit guarda el último estado (Last Will and Testament), lo que hace que la comunicación sea mucho más robusta que un broker simple.
* **Seguridad y AIO Key:** Investigué que la AIO Key funciona como un token de autenticación dinámico. A diferencia de un usuario/pass normal, este token permite revocar el acceso sin cambiar la cuenta, lo cual es vital si llegamos a compartir código en GitHub (aunque el profe fue súper enfático en que no las subamos).

* **Proceso de Instalación:** Configuré el entorno instalando la suite completa de Adafruit IO Arduino (v4.3.4). Tuve que gestionar manualmente las dependencias de HttpClient y Adafruit_MQTT, asegurándome de que la placa Arduino WiFiS3 sea reconocida correctamente por el Library Manager para evitar errores de compilación por falta de headers.

Bonus :)

* **Integración con Webhooks y Dashboards:** Investigué que Adafruit IO no solo recibe datos, sino que permite crear Dashboards visuales en tiempo real sin escribir código extra. Además, tiene integración con Webhooks, lo que permitiría enviar una alerta a mi celular o un correo si mi sensor detecta algo crítico, expandiendo la interacción fuera de la placa.
* **Limitaciones del Plan Free (Rate Limiting):** Es importante notar que el plan gratuito tiene un límite de 30 datos por minuto y almacenamiento de datos por 30 días. Para nuestro proyecto esto es suficiente, pero entender estas limitaciones es vital para no "spamear" el broker y evitar que la cuenta sea bloqueada por exceso de tráfico.

Bitácora del Lunes: Mis Primeros Pasos en el IoT

El lunes fue nuestro "bautismo de fuego". Hicimos dos ejercicios clave que me sirvieron para entender que en el IoT, si una pieza pequeña falla, nada funciona.
Ejercicio 1: El "Hola Mundo" en la Nube

El objetivo era conectar el Arduino R4 WiFi a Adafruit IO por primera vez.

1. Mi experiencia: Al principio fue un enredo con las credenciales. Aprendí que el código es súper sensible: una mayúscula mal puesta en el nombre del WiFi y ya no conectaba.
2. Lo que descubrí: Aquí fue cuando caché lo de los Puertos COM. Al conectar mi placa, vi que aparecía como COM14. Entendí que ese es el "asiento" que ocupa mi Arduino en el PC. También noté que si el código decía 115200 baudios y el monitor estaba en 9600, solo veía símbolos raros (rombos). Sincronizarlos fue la clave para ver el mensaje de "conectado.

## Ejercicio 1 - Resumen de primer acercamiento y configuración

Este primer día el foco estuvo en entender cómo el Arduino UNO R4 WiFi se comunica con la nube. El profesor nos entregó un código base configurado para el envío de datos hacia Adafruit IO, lo que me sirvió para familiarizarme con el entorno antes de programar algo propio.

Que aprendí:

1. **Configuración de red:** Al principio tuve problemas para que la placa detectara el WiFi de mi teléfono. Aprendí que en la programación de redes la precisión es absoluta: una mayúscula mal puesta en el SSID impide cualquier conexión.
2. **Sincronización del Monitor Serial:** Inicialmente solo veía símbolos extraños (rombos) en la pantalla. Esto me permitió entender el concepto de los baudios; si el código define 115200 y el monitor está en 9600, la comunicación se rompe. Al ajustarlos, pude verificar finalmente el estado de la conexión.
3. **Visualización en la nube:** Fue valioso ver cómo los datos enviados desde el hardware se reflejaban de inmediato en las gráficas de Adafruit. Esta base fue fundamental para los experimentos más complejos que vinieron después.

Evidencia:
<table style="width: 100%; border: none;"> <tr> <td style="border: none; text-align: center; vertical-align: top; padding: 10px;"> <img src="https://github.com/user-attachments/assets/fcc9395a-1390-4b80-a16e-d9240fd939c1" width="450"> <p><small><i>Imagen 08: Error inicial de conexión por credenciales.</i></small></p> </td> <td style="border: none; text-align: center; vertical-align: top; padding: 10px;"> <img src="https://github.com/user-attachments/assets/552a42f1-3f42-4600-b16d-f840360d1410" width="450"> <p><small><i>Imagen 09: Conexión exitosa y lectura del monitor serial.</i></small></p> </td> </tr> <tr> <td style="border: none; text-align: center; vertical-align: top; padding: 10px;"> <img src="https://github.com/user-attachments/assets/64fedba8-0fdc-4623-9671-2ed1303b7899" width="450"> <p><small><i>Imagen 10: Datos llegando correctamente a Adafruit.</i></small></p> </td> <td style="border: none; text-align: center; vertical-align: top; padding: 10px;"> <img src="https://github.com/user-attachments/assets/bb66dc20-6527-4b01-ac16-ec4bdf3f9a14" width="450"> <p><small><i>Imagen 11: Comprobación final del flujo de datos en la nube.</i></small></p> </td> </tr> </table>

## Ejercicio 2 Resumen: El Drama del LED y el Dashboard

Aquí la meta era pro pro: prender un LED físico con un botón digital desde Adafruit.

1. El "Fail" del día: ¡Se nos quemó un LED!:( Entre tanto cable y resistencia, pusimos una que no era y el pobre LED no aguantó, se puso como de colocar naranjo y salió humo.
2. Aprendizaje técnico: Usamos el multímetro para revisar el voltaje. Aprendí que no se trata de conectar por conectar; hay que entender cuánta energía aguanta cada componente. Aunque el tiempo nos pilló y no alcanzamos a ver el LED prendiendo desde el switch ese mismo lunes, me sirvió para entender la lógica bidireccional: yo aprieto un botón en la web -> viaja a la nube -> el Arduino recibe la orden -> se prende la luz.

Mis Observaciones:

Durante estos dos ejercicios, me fijé en detalles del Arduino IDE que ahora me hacen la vida más fácil:

* **Colores y Comentarios:** Descubrí que el texto en gris (con //) es mi mejor amigo para dejar notas. También que el código cambia de color cuando reconoce un comando, lo que me ayuda a saber si escribí bien una función.
* **Estructura:** Aprendí que el #include tiene que ir arriba sí o sí. Es como presentar a los invitados antes de empezar la fiesta.
* **Redes:** Me voló la cabeza entender que no todos los WiFi sirven; tuve que configurar el Hotspot en 2.4 GHz porque mi Arduino no "ve" la frecuencia de 5 GHz que suelen usar los celulares modernos.

Evidencia:

<table style="width: 100%; border: none;"> <tr> <td style="border: none; text-align: center; vertical-align: top;"> <img src="https://github.com/user-attachments/assets/3c1dc746-db01-4707-9176-1ccf272acb70" width="400" alt="Circuito LED"> <p><small><i><b>Imagen 12:</b> Setup inicial protoboard.</i></small></p> </td> <td style="border: none; text-align: center; vertical-align: top;"> <img src="https://github.com/user-attachments/assets/5e48be00-1fdf-4d84-93b0-64ed8c9add9f" width="300" alt="Dashboard Adafruit"> <p><small><i><b>Imagen 13:</b> Botón en Adafruit IO.</i></small></p> </td> <td style="border: none; text-align: center; vertical-align: top;"> <img src="https://github.com/user-attachments/assets/97e0f2c7-5540-40fd-9f60-5cc595c7be07" width="400" alt="Uso multímetro"> <p><small><i><b>Imagen 14:</b> Diagnóstico con multímetro.</i></small></p> </td> </tr> </table>

## Experimento Grupal - Resumen: Comunicación entre Nodos (Emisor y Receptor)

Después de los ejercicios del lunes, el miércoles nos tiramos a la piscina con un desafío mucho más pro: la comunicación bidireccional entre dos Arduinos R4 WiFi usando la matriz de LEDs de 12x8.
El Objetivo del Experimento

Queríamos demostrar que podíamos tener dos sistemas de hardware totalmente independientes que se comunicaran en tiempo real:

* **Arduino Emisor: Se encargaba de mandar datos numéricos a la nube de Adafruit.**
* **Arduino Receptor: Capturaba esa información desde la nube y la traducía visualmente "dibujándola" en su matriz de LEDs.**

Mis Observaciones Técnicas (Lo que aprendí en el proceso):

1. **El poder de los Feeds:** Entendí que el "feed" en Adafruit no es solo una base de datos, es el punto de encuentro. El emisor publica en el feed y el receptor se suscribe a él. Es como si el emisor dejara una carta en un buzón y el receptor la fuera a buscar apenas llega.
2. **La Matriz de LEDs (12x8):** Fue emocionante ver cómo un número que enviábamos desde el computador o desde el otro Arduino se convertía en una forma física en la matriz. Aprendí que programar la matriz requiere una lógica de "dibujo" por coordenadas, lo cual integra conceptos de programación más avanzados.
3. **Actualización de Firmware (v0.6.0):** Aquí nos dimos cuenta de que si las placas no tienen el firmware actualizado, la comunicación se cae o es súper inestable. Es como tratar de hablar por una radio antigua; si el chip de WiFi no está al día, no hay "handshake" con la nube.
4. **Red Dedicada (Hotspot 2.4 GHz):** Para que esto funcionara con dos placas a la vez, fue vital usar un punto de acceso dedicado. Descubrí que al tener dos dispositivos mandando y recibiendo datos al mismo tiempo, la estabilidad de la red es el corazón de todo el proyecto. Lo más imporatnte que aprendí es que esta comunicación se puede realizar desde cualquier parte del mundo; yo podría estar en mi casa y mi compañero en la suya, y las placas se seguirían hablando. Eso sí, siempre y cuando se cumplan estas "cláusulas" técnicas:

    Que ambos dispositivos estén en una red de 2.4 GHz.
    Que el Firmware de las placas esté actualizado (v0.6.0).
    Que las credenciales (AIO Key y Username) en el código sean las correctas para entrar al mismo "buzón" en la nube.

Resultados:
<div align="center"> <video src="https://github.com/user-attachments/assets/20e565f9-6a12-4114-818b-a9c23fc3dd31" width="600" controls> Tu navegador no soporta el elemento de video. </video> <p><i><b>Evidencia Final:</b> Handshake exitoso entre nodos. El Arduino receptor emite un flash debido al número enviado desde la nube en tiempo real.</i></p> </div>

## Mi Profundización Personal: El "Efecto Flash" ⚡

Después de lograr que los Arduinos se comunicaran con números, me obsesioné un poco con lo que podíamos hacer. Me encantó ver cómo un dato viajaba por el aire y se convertía en luz, así que quise llevarlo al siguiente nivel: el Flash.

La idea:

Mi meta era que cuando el Arduino Receptor recibiera un dato específico de la nube, no solo dibujara un numerito, sino que toda la matriz de 12x8 se prendiera al mismo tiempo, como un flashazo de luz, y luego se apagara.

El Desafío Técnico: ¿Qué cambié?

Como ya teníamos la base de la comunicación lista, me di cuenta de que no necesitaba reescribir todo el código.

* **Lo que se mantuvo:** Todo el bloque de #include, las credenciales de Adafruit y la configuración del WiFi. Esa es la "carcasa" que permite que el Arduino esté en línea.
* **Lo que cambió (El Loop):** Aquí es donde metí mano. Tuve que modificar la lógica dentro del loop() y la función que escucha al feed de Adafruit (onMessage).

## Codigo de Enviador

```cpp
#include "AdafruitIO_WiFi.h"

/*************** CREDENCIALES ************************/

#define IO_USERNAME "TU_USUARIO_AQUÍ"
#define IO_KEY "TU_KEY_AQUÍ"

#define WIFI_SSID "TU_WIFI_AQUÍ"
#define WIFI_PASS "TU_CLAVE_AQUÍ"

#if defined(USE_AIRLIFT) || defined(ADAFRUIT_METRO_M4_AIRLIFT_LITE) || \
    defined(ADAFRUIT_PYPORTAL)

  #define SPIWIFI SPI
  #define SPIWIFI_SS 10
  #define NINA_ACK 9
  #define NINA_RESETN 6
  #define NINA_GPIO0 -1

  AdafruitIO_WiFi io(IO_USERNAME, IO_KEY, WIFI_SSID, WIFI_PASS,
                     SPIWIFI_SS, NINA_ACK, NINA_RESETN, NINA_GPIO0, &SPIWIFI);

#else

  AdafruitIO_WiFi io(IO_USERNAME, IO_KEY, WIFI_SSID, WIFI_PASS);

#endif

/*************** PROGRAMA PRINCIPAL ************************/

// Conexión al feed
AdafruitIO_Feed *nombreFeed = io.feed("grupo08");

int contador = 0;

void setup() {
  Serial.begin(115200);
  while(!Serial);

  Serial.print("Conectando con Adafruit IO...");

  io.connect();


  while(io.status() < AIO_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.println();
  Serial.println(io.statusText()); 
}

void loop() {

  io.run();  

  // PRENDER el LED (pin 13)
  digitalWrite(LED_BUILTIN, HIGH);

  Serial.print("Enviando número -> ");
  Serial.println(contador);


  nombreFeed->save(contador);

 
  delay(200);
  digitalWrite(LED_BUILTIN, LOW);

  contador = contador + 2;

  // Completa los 5 segundos
  delay(4800);
}
```

## Codigo de Receptor

```cpp
#include "ArduinoGraphics.h" 
#include "Arduino_LED_Matrix.h"   // Pantalla LED integrada
#include "AdafruitIO_WiFi.h"

/*************** CREDENCIALES************************/

#define IO_USERNAME "TU_USUARIO_AQUÍ"
#define IO_KEY "TU_KEY_AQUÍ"

#define WIFI_SSID "TU_WIFI_AQUÍ"
#define WIFI_PASS "TU_CLAVE_AQUÍ"

/************************ OBJETOS ****************************/
AdafruitIO_WiFi io(IO_USERNAME, IO_KEY, WIFI_SSID, WIFI_PASS);
ArduinoLEDMatrix matrix;

// Feed 
AdafruitIO_Feed *nombreFeed = io.feed("grupo08");

/************************ SETUP ****************************/
void setup() {
  Serial.begin(115200);
  while (!Serial);

  matrix.begin();  // Iniciar matriz LED

  Serial.print("Conectando a Adafruit IO...");
  io.connect();

  // Cuando llegue el mensaje → ejecutar función
  nombreFeed->onMessage(leerMensaje);

  // Esperar conexión
  while (io.status() < AIO_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.println();
  Serial.println(io.statusText());
}

/************************ LOOP ****************************/
void loop() {
  io.run();  
}

/************************ FUNCIÓN FLASH ****************************/
void leerMensaje(AdafruitIO_Data *data) {

  Serial.print("Dato recibido: ");
  Serial.println(data->value());

  // Flash: prende toda la matriz
  uint32_t flash[] = {
    0xffffffff,
    0xffffffff,
    0xffffffff
  };

  matrix.loadFrame(flash);  // Encender LEDs
  delay(500);

  matrix.clear();  // Apagar
}
```

Resultados:

<div align="center"> <video src="https://github.com/user-attachments/assets/d06eaad2-e06d-447d-8449-0a92ef80aa91" width="600" controls> Tu navegador no soporta el elemento de video. </video> <p><i><b>Evidencia Final:</b> Handshake exitoso entre nodos. El Arduino receptor dibuja el número enviado desde la nube en tiempo real.</i></p> </div>

¿Cómo lo logré? :

1. **Identificar el mensaje:** Programar una condición (if) para que, cuando llegue el dato de "flash", el Arduino sepa que tiene que activar todos los LEDs.
2. **Llenar la matriz:** Usar una función (como matrix.fill()) para prender los 96 LEDs de un solo golpe.
3. **El manejo del tiempo:** Aquí aprendí que el orden de los comandos importa para que el flash no se quede pegado y la placa pueda seguir recibiendo más datos después.

💡 Nota de mi "obsesión": Me di cuenta de que una vez que entiendes cómo "viaja" el dato (la infraestructura), el resto es pura creatividad en el código. Pasar de un número a un flash me enseñó que puedo manipular la salida física (los LEDs) de mil formas distintas usando la misma conexión de base. ¡Fue súper satisfactorio verlo funcionar!

### Bibliografía

* Adafruit. (s.f.). *Adafruit IO basics: Digital output (Arduino setup)*. <https://learn.adafruit.com/adafruit-io-basics-digital-output/arduino-setup>

* Adafruit. (s.f.). *Adafruit IO basics: Feeds*. <https://learn.adafruit.com/adafruit-io-basics-feeds>

* Adafruit. (s.f.). *Welcome to Adafruit IO*. <https://learn.adafruit.com/welcome-to-adafruit-io>

* Adafruit IO. (s.f.). *API documentation: Limits*. <https://io.adafruit.com/api/docs/#limits>

* Arduino. (s.f.). *#include*. <https://www.arduino.cc/reference/en/language/structure/further-syntax/include/>

* Arduino. (s.f.). *Blink without delay*. <https://docs.arduino.cc/built-in-examples/digital/BlinkWithoutDelay/>

* Arduino. (s.f.). *If statement*. <https://www.arduino.cc/reference/en/language/structure/control-structure/if/>

* Arduino. (s.f.). *LED matrix API overview*. <https://docs.arduino.cc/tutorials/uno-r4-wifi/led-matrix/#api-overview>

* Arduino. (s.f.). *WiFi examples (UNO R4 WiFi)*. <https://docs.arduino.cc/tutorials/uno-r4-wifi/wifi-examples/>

* Arduino Libraries. (s.f.). *ArduinoGraphics*. <https://github.com/arduino-libraries/ArduinoGraphics>

* Intel. (s.f.). *Diferencias entre 2.4 GHz y 5 GHz*. <https://www.intel.la/content/www/xl/es/products/docs/wireless/2-4-vs-5ghz.html>

* MDN Web Docs. (s.f.). *WebSockets API*. <https://developer.mozilla.org/es/docs/Web/API/WebSockets_API>

* SparkFun Electronics. (s.f.). *Handshaking and flow control*. <https://learn.sparkfun.com/tutorials/terminal-basics/handshaking-and-flow-control>

* Wikipedia contributors. (s.f.). *Cortafuegos (informática)*. <https://es.wikipedia.org/wiki/Cortafuegos_(inform%C3%A1tica)>

---

### 🎨 Referente Artístico: Rafael Lozano-Hemmer

Para la Solemne 01 elegí a **Rafael Lozano-Hemmer**, un artista mexicano-canadiense que es pionero en el uso de la **computación distribuida** y la **electrónica** para crear intervenciones urbanas masivas.

---

### Obra Analizada: *Pulse Topology* (2021)

Esta instalación consta de **3.000 bombillas suspendidas** que parpadean al ritmo del corazón de los visitantes.  

No es una luz estática; es un **sistema vivo** que reacciona en tiempo real a los **datos biométricos** de las personas.
<img src="https://github.com/user-attachments/assets/a8eb22a0-2935-4988-a1a1-4b3c33b3af83" width="800" alt="Profundización Int Ina 06 04">
<img src="https://github.com/user-attachments/assets/09070939-b8b0-4e22-b1ec-9fe7a4322a28" width="800" alt="Profundización Int Ina 06 04">

---

### ¿Por qué es clave para Interacciones Inalámbricas?

Analizando la obra desde los conceptos técnicos del ramo, identifiqué estos puntos fundamentales:

---

### Redes de Sensores (WSN) y Latencia

Lozano-Hemmer utiliza **sensores de pulso inalámbricos**.  

Lo más relevante es el manejo de la **latencia (retraso del dato)**:

* El pulso viaja por el aire  
* Se procesa  
* Activa una luz casi instantáneamente  

Si el protocolo inalámbrico falla o tiene mucho **lag**, la conexión emocional del espectador se rompe.

---

### Datos en la Nube y Escalabilidad

Al igual que nosotros usamos **Adafruit IO**, el artista trabaja con sistemas que manejan **miles de eventos por segundo**.

Esto conecta directamente con:

* **Rate Limiting**
* Optimización de paquetes de datos  
* Fluidez del sistema  

---

### Hardware Invisible

La tecnología inalámbrica permite que el hardware **“desaparezca”**:

* No hay cables visibles  
* No hay computadores evidentes  
* Solo se percibe la interacción  

---

## Análisis de Capas de Interacción

La obra transforma un dato biológico (**pulso**) en un **dato digital**.

* Sensor → Arduino  
* Señal analógica → mensaje MQTT  
* Transmisión inalámbrica  

 La interfaz es el **cuerpo humano**, eliminando botones o teclados.

---

### Concepto de "Antimonumento"

El artista define sus obras como **antimonumentos**:

* No son estáticas  
* Dependen 100% de la conectividad  

Si la red falla → la obra desaparece  

Esto refuerza algo clave:
> En computación física, la **estabilidad de la red** es tan importante como el diseño del objeto.

---

## Nota personal de aprendizaje

Entender la infraestructura detrás de *Pulse Topology* me hizo ver que la creatividad en el **IoT** no es solo "prender luces", sino que:

* Dominar cómo viaja la información  
* Entender WiFi, puertos y brokers  
* Diseñar experiencias fluidas  

Conclusión:
Lo que aprendí con esta obra es que para que 3,000 luces parpadeen sincronizadas, no basta con mandar electricidad, hay que mandar paquetes de datos. En mi proyecto con el Arduino R4, el 'idioma' es MQTT; en la obra de Rafael, es un sistema distribuido que maneja miles de mensajes por segundo. Sin un protocolo claro, la interacción sería puro ruido visual.

Además, un gran aprendizaje de este referente es la escalabilidad. Pasar de conectar un LED en mi protoboard a conectar 3,000 bombillas en una sala gigante requiere entender la topología de la red. Si un nodo falla, ¿se cae toda la obra? Rafael diseña sistemas donde la información fluye de forma redundante, algo que me hizo repensar cómo estructuro mis propios feeds en Adafruit para que no colapsen si agrego más sensores.

Concluyo que, en Pulse Topology, la retroalimentación es inmediata: tú pones la mano y la luz parpadea. Esa respuesta instantánea es lo que valida la interacción. En mis ejercicios, tanto en clases como en casa, cuando el Monitor Serial me mostraba el mensaje de 'Conectado', sentí esa misma satisfacción, de "wow, el sistema me está confirmando que la comunicación inalámbrica tuvo éxito o que está funcionando todo bien".

* **Ruido visual:**  
  Señales eléctricas no deseadas que se superponen a la señal útil, deformándola.  
  Son perturbaciones que pueden provenir de fuentes externas (motores, luces) o internas (movimiento de electrones por calor).

* **Escalabilidad:**  
  Capacidad de un sistema para manejar una cantidad creciente de trabajo (más datos, usuarios o dispositivos) de manera eficiente, manteniendo o mejorando su rendimiento.

* **Topología de red:**  
  Disposición física y lógica de los nodos (sensores, dispositivos) y sus conexiones.  
  Define cómo fluye la información y afecta directamente el rendimiento del sistema.

* **Redundancia:**  
  Estrategia en la que componentes o sistemas se duplican para asegurar el funcionamiento en caso de fallas.

### Bibliografía

* Aerospike. (s.f.). *Database scalability*. <https://aerospike-com.translate.goog/blog/database-scalability/>

* Arduino. (s.f.). *Analog input*. <https://docs.arduino.cc/learn/microcontrollers/analog-input/>

* Cloudflare. (s.f.). *What is rate limiting?*. <https://www.cloudflare.com/es-la/learning/bots/what-is-rate-limiting/>

* IBM. (s.f.). *Network topology*. <https://www.ibm.com/mx-es/think/topics/network-topology>

* Lozano-Hemmer, R. (s.f.). *Biography*. <https://www.lozano-hemmer.com/biography.php>

* Lozano-Hemmer, R. (s.f.). *Pulse Topology*. <https://www.lozano-hemmer.com/pulse_topology.php>

* PC Hardware Pro. (s.f.). *¿Qué es el ruido en electrónica y cómo afecta a tus circuitos?*. <https://www.pchardwarepro.com/que-es-el-ruido-en-electronica-y-como-afecta-a-tus-circuitos/>

* Q2B Studio. (s.f.). *El hardware invisible de la EdTech: perspectiva de un ingeniero*. <https://www.q2bstudio.com/nuestro-blog/25527/el-hardware-invisible-de-la-edtech-perspectiva-de-un-ingeniero>

* Real Academia Española. (s.f.). *Redundante*. <https://dle.rae.es/redundante>
