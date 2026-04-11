# Luisa Toro
investigaciones individuales

## Introducción

Mi investigación para la Solemne 01 no se quedó solo en el cambio de plataforma; se centró en entender cómo lograr una comunicación inalámbrica robusta integrando el Arduino R4 WiFi, la nube de Adafruit IO y el software de Arduino.

Durante las primeras pruebas en la sala, el uso de Mosquitto nos dio muchísimos problemas de conexión. Aprendí que esto pasaba por las restricciones de seguridad de la red de la universidad, que bloqueaban el puerto 1883 (el estándar de MQTT local) y más errores que algunos no logré entender bien.

La Solución: Para solucionar estas fallas, investigamos la opción de Adafruit IO. La gran ventaja es que este broker en la nube permite conexiones vía MQTT sobre WebSockets en el puerto 443. Como este puerto es el mismo que usa el tráfico web normal (HTTPS), logramos saltarnos los bloqueos del firewall y tener una comunicación fluida y estable desde cualquier computador.

## 1. El Corazón del Proyecto: Comunicación Inalámbrica
Mi semana de Solemne partió literal desde la base. El lunes en la clase me di cuenta de que para que el Arduino haga algo "inalámbrico", primero hay que armarle todo un ecosistema en el computador y en la nube. No es llegar y conectar. 

Una vez superado el problema de la red, mi investigación se volcó a la interacción en tiempo real. Aquí aprendí conceptos que son el motor de nuestro proyecto:

1. Protocolo MQTT: Es el "idioma" inalámbrico. Aprendí que es ideal para el IoT porque es súper liviano. Mi Arduino se suscribe a un canal (Feed) y se queda esperando órdenes sin saturar la red.
2. Gestión de Datos (Feeds): Entendí que la comunicación inalámbrica no es solo enviar un dato al aire; es una base de datos organizada. Adafruit guarda el último estado enviado, lo que hace que la conexión sea mucho más confiable que un mensaje simple.


Paso 0: Preparando el terreno (Software)

Aunque yo ya tenía instalado el Arduino IDE de antes, decidí revisar la página oficial para asegurarme de tener la última versión.

<div align="center"> <img src="https://github.com/user-attachments/assets/e74d5b97-7e05-4ad1-ba25-a14db8a04098" width="80%" alt="Descarga Arduino IDE"> <p><i><b>Imagen 01:</b> Punto de partida. Aunque ya tenía el programa instalado de antes, verifiqué en la página oficial que fuera la versión <b>2.3.8</b> para asegurar la compatibilidad total.</i></p> </div>

**Creando mi identidad en la nube (Adafruit IO)**

Paso 1: Lo primero que hice fue crearme la cuenta en Adafruit IO. Al principio no entendía mucho para qué servía, pero después caché que es como el "cerebro" en la nube que va a recibir los datos de mi placa.

<table style="width: 100%; border: none;"> <tr> <td style="width: 50%; border: none; text-align: center;"> <img src="https://github.com/user-attachments/assets/bdb6d761-7fd0-40e8-98f7-01da73422279" width="100%" alt="Tutorial Adafruit IO"> <p><i><b>Imagen 01:</b> Video tutorial que seguí para entender el ecosistema de Adafruit IO.</i></p> </td> <td style="width: 50%; border: none; text-align: center;"> <img src="https://github.com/user-attachments/assets/7952a9eb-b332-48ba-8df7-c20f7744efff" width="100%" alt="Cuenta Creada"> <p><i><b>Imagen 02:</b> Mi cuenta de Adafruit IO ya creada y configurada para recibir datos.</i></p> </td> </tr> </table>

* **La famosa AIO Key:** Apenas entré, busqué mi "Key". Es una clave gigante que te dan y aprendí que es súper secreta. El profe nos recalcó mil veces que si la subimos a GitHub, cualquiera puede meterse a nuestro proyecto, así que tuve que tener mucho cuidado de no dejarla pegada en el código principal.
* **Armando el "buzón" (Feeds):** Creé mi primer Feed. Me costó un poco entender el concepto, pero al final lo vi como un buzón: mi Arduino tira una carta ahí y el Dashboard la lee.


<table style="width: 100%; border: none;"> <tr> <td style="width: 50%; border: none; text-align: center;"> <img src="https://github.com/user-attachments/assets/5d380a01-39e2-4220-aaa2-e3dbbaef625e" width="100%" alt="Configuración de Feeds"> <p><i><b>Imagen 03:</b> Este es el "buzón" donde mi Arduino revisa si llegaron mensajes nuevos para mostrar en su pantalla LED.</i></p> </td> <td style="width: 50%; border: none; text-align: center;"> <img src="https://github.com/user-attachments/assets/75d786b1-3ce3-44a0-887a-860d2d3cb948" width="100%" alt="Detalles de la App"> <p><i><b>Imagen 04:</b> Vista de la App donde revisé los tokens y la información técnica de la cuenta.</i></p> </td> </tr> </table>

Paso 2: Después de las cuentas de Adafruit, me pasé al Arduino IDE. Yo ya lo tenía instalado, pero aprendí que para que la placa hable con internet, el programa necesita "superpoderes" extra que vienen en las Librerías.

1. Instalación manual: Busqué la librería Adafruit IO Arduino (versión 4.3.4).
2. Las dependencias: Cuando le di a "Install", me saltó un aviso gigante preguntando si quería instalar un montón de cosas más. Al principio me dio susto, pero entendí que son como los "ayudantes" de la librería principal (como HttpClient y Adafruit_MQTT). Sin ellos, el código simplemente no compila porque le faltarían piezas clave.
3. Logro: Una vez que terminó la descarga, mi IDE ya estaba listo para escribir código que se conectara a la nube.

<table style="width: 100%; border: none;"> <tr> <td style="width: 50%; border: none; text-align: center;"> <img src="https://github.com/user-attachments/assets/5a4465ad-acee-497f-9a16-1e36107cf345" width="100%" alt="Instalación de Librerías 01"> <p><i><b>Evidencia 05:</b> Buscando la librería <b>Adafruit IO Arduino</b> en el Library Manager.</i></p> </td> <td style="width: 50%; border: none; text-align: center;"> <img src="https://github.com/user-attachments/assets/8a412aa3-3d25-41ac-8fec-88104af41b5c" width="100%" alt="Instalación de Librerías 02"> <p><i><b>Evidencia 06:</b> Proceso de instalación de dependencias. Se instalaron todos los "ayudantes" necesarios para la comunicación WiFi.</i></p> </td> </tr> </table>

Hallazgos Técnicos Clave:

* **Protocolo y Puertos:** A diferencia de Mosquitto local (que nos dio problemas de permisos en el puerto 1883), Adafruit IO permite conexiones vía MQTT sobre WebSockets (puerto 443). Esto es fundamental porque el tráfico se ve como tráfico web normal (HTTPS), saltándose los firewalls de Windows que nos bloquearon en la clase pasada.
* **Arquitectura de Datos (Feeds):** Entendí que Adafruit IO organiza todo por "Feeds". No es solo enviar un dato al aire; es una base de datos de series temporales. Esto significa que si mi Arduino se desconecta un segundo de la WiFi de la U, Adafruit guarda el último estado (Last Will and Testament), lo que hace que la comunicación sea mucho más robusta que un broker simple.
* **Seguridad y AIO Key:** Investigué que la AIO Key funciona como un token de autenticación dinámico. A diferencia de un usuario/pass normal, este token permite revocar el acceso sin cambiar la cuenta, lo cual es vital si llegamos a compartir código en GitHub (aunque el profe fue súper enfático en que no las subamos).

* **Proceso de Instalación:** Configuré el entorno instalando la suite completa de Adafruit IO Arduino (v4.3.4). Tuve que gestionar manualmente las dependencias de HttpClient y Adafruit_MQTT, asegurándome de que la placa Arduino WiFiS3 sea reconocida correctamente por el Library Manager para evitar errores de compilación por falta de headers.

Bonus :)
* **Integración con Webhooks y Dashboards:** Investigué que Adafruit IO no solo recibe datos, sino que permite crear Dashboards visuales en tiempo real sin escribir código extra. Además, tiene integración con Webhooks, lo que permitiría enviar una alerta a mi celular o un correo si mi sensor detecta algo crítico, expandiendo la interacción fuera de la placa.
* **Limitaciones del Plan Free (Rate Limiting):** Es importante notar que el plan gratuito tiene un límite de 30 datos por minuto y almacenamiento de datos por 30 días. Para nuestro proyecto esto es suficiente, pero entender estas limitaciones es vital para no "spamear" el broker y evitar que la cuenta sea bloqueada por exceso de tráfico.

🗓️ Bitácora del Lunes: Mis Primeros Pasos en el IoT

El lunes fue nuestro "bautismo de fuego". Hicimos dos ejercicios clave que me sirvieron para entender que en el IoT, si una pieza pequeña falla, nada funciona.
Ejercicio 1: El "Hola Mundo" en la Nube

El objetivo era conectar el Arduino R4 WiFi a Adafruit IO por primera vez.

1. Mi experiencia: Al principio fue un enredo con las credenciales. Aprendí que el código es súper sensible: una mayúscula mal puesta en el nombre del WiFi y ya no conectaba.
2. Lo que descubrí: Aquí fue cuando caché lo de los Puertos COM. Al conectar mi placa, vi que aparecía como COM14. Entendí que ese es el "asiento" que ocupa mi Arduino en el PC. También noté que si el código decía 115200 baudios y el monitor estaba en 9600, solo veía símbolos raros (rombos). Sincronizarlos fue la clave para ver el mensaje de "conectado.

# Ejercicio 2: El Drama del LED y el Dashboard

Aquí la meta era pro pro: prender un LED físico con un botón digital desde Adafruit.

1. El "Fail" del día: ¡Se nos quemó un LED!:( Entre tanto cable y resistencia, pusimos una que no era y el pobre LED no aguantó, se puso como de colocar naranjo y salió humo. 
2. Aprendizaje técnico: Usamos el multímetro para revisar el voltaje. Aprendí que no se trata de conectar por conectar; hay que entender cuánta energía aguanta cada componente. Aunque el tiempo nos pilló y no alcanzamos a ver el LED prendiendo desde el switch ese mismo lunes, me sirvió para entender la lógica bidireccional: yo aprieto un botón en la web -> viaja a la nube -> el Arduino recibe la orden -> se prende la luz.

Mis Observaciones de Programadora Novata 

Durante estos dos ejercicios, me fijé en detalles del Arduino IDE que ahora me hacen la vida más fácil:

* **Colores y Comentarios:** Descubrí que el texto en gris (con //) es mi mejor amigo para dejar notas. También que el código cambia de color cuando reconoce un comando, lo que me ayuda a saber si escribí bien una función.
* **Estructura:** Aprendí que el #include tiene que ir arriba sí o sí. Es como presentar a los invitados antes de empezar la fiesta.
* **Redes:** Me voló la cabeza entender que no todos los WiFi sirven; tuve que configurar el Hotspot en 2.4 GHz porque mi Arduino no "ve" la frecuencia de 5 GHz que suelen usar los celulares modernos.

## Experimento Final - Grupal - Resumen: Comunicación entre Nodos (Emisor y Receptor)

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

## Codigo de Enviador:
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
## Codigo de Receptor:
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


## 🎨 Referente Artístico: Rafael Lozano-Hemmer

Para la Solemne 01 elegí a Rafael Lozano-Hemmer (mexicano-canadiense), un artista que es pionero en el uso de la computación distribuida y la electrónica para crear intervenciones urbanas masivas.

Obra Analizada: Pulse Topology (2021) Esta instalación consta de 3,000 bombillas suspendidas que parpadean al ritmo del corazón de los visitantes. No es una luz estática; es un sistema vivo que reacciona en tiempo real.

<img src="https://github.com/user-attachments/assets/a8eb22a0-2935-4988-a1a1-4b3c33b3af83" width="800" alt="Profundización Int Ina 06 04">
<img src="https://github.com/user-attachments/assets/09070939-b8b0-4e22-b1ec-9fe7a4322a28" width="800" alt="Profundización Int Ina 06 04">

¿Por qué es clave para Interacciones Inalámbricas?

* **Redes de Sensores (WSN):** Lozano-Hemmer utiliza sensores de pulso inalámbricos. Lo que me fascina es la latencia (el retraso del dato). En esta obra, el dato del corazón debe viajar por el aire, procesarse y encender una luz casi instantáneamente. Si el protocolo inalámbrico falla o tiene mucho "lag", la conexión emocional del espectador con la obra se rompe.
* **Datos en la Nube y Escalabilidad:** Al igual que nosotros usamos Adafruit IO para gestionar datos, él usa sistemas que manejan miles de eventos por segundo. Esto me hace reflexionar sobre el Rate Limiting: ¿Cómo escalas una interacción para 3,000 luces sin colapsar la red?
* **Hardware Invisible:** La tecnología inalámbrica permite que el hardware "desaparezca". El espectador no ve cables, solo ve la reacción. Mi meta en este ramo es lograr esa misma fluidez: que el protocolo (MQTT/Adafruit) sea el puente invisible que permita que mi diseño se sienta orgánico y no "mecánico".

Y para finalizar :)
## Análisis de Capas de Interacción:

1. Biometría Inalámbrica: Lo que hace única a esta obra es que transforma un dato biológico (el pulso) en un paquete de datos digital. En nuestro curso, esto es equivalente a lo que haremos al conectar un sensor al Arduino: convertir una señal analógica en un mensaje MQTT que viaja por el aire. Lozano-Hemmer usa la biometría para que la interfaz sea el propio cuerpo, eliminando teclados o botones.
2. El Concepto de "Antimonumento": El artista define sus obras como antimonumentos porque no son estáticos. Dependen 100% de la conectividad. Si el sistema inalámbrico se cae, la obra desaparece. Esto refuerza lo que aprendimos con los "chascarros" del profe: en la computación física, la estabilidad de la red es tan importante como el diseño del objeto mismo.
