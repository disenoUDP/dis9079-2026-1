# sesion-15

lunes 22 junio 2026

Examen-grupo 6


### criterios individuales

- Investigación textual sobre API.
- Bitácoras junio: evaluación de 4 sesiones (25 mayo, 01 junio, 08 de junio, 15 junio).
- Bitácoras junio (la misma nota que punto anterior).


## Conexiones finales -> Puente digital 

1. Conectar el anillo led al arduino

|Pin del anillo|Pin del Arduino|
|---|---|
|VCC (5V)|5V|
|GND|GND|
|INPUT (dato)|Pin digital 6|

2. Conectar el sensor infrarojo a la Raspberry PI
   
|Pin del sensor|Pin de la Pico 2W|
|---|---|
|VCC|3.3V (pin 36)|
|GND|GND (cualquier pin GND)|
|OUT (señal digital)|GP15 (pin 20)|

3. Mantener presionado el botón `BOOTSEL` de la Pico mientras lo conectamos al Mac por USB.

4. Descargar el archivo *.uf2* de `CircuitPython` para Pico 2W desde su página oficial. 
5. Arrastrar el archivo *.uf2* a la carpeta de la Raspberry desde el Finder.
6. La Pico se reiniciará y aparecerá como una nueva unidad llamada CIRCUITPY.
7. Subir el código UNA vez con Circuit python de la siguiente manera

```bash
# Ver dónde está montada
ls /Volumes/

# Copiar tu código (debe llamarse exactamente "code.py")
cp pico_sensor_entrada.py /Volumes/CIRCUITPY/code.py
```

8. Para instalar la librería adafruit_minimqtt, desde la terminal

```bash
bashcp -r adafruit_minimqtt /Volumes/CIRCUITPY/lib/
```

9. Para ver donde se ubica el usb es:

```bash
# Encuentra el puerto serie
ls /dev/tty.*

# Conéctate (ajusta el nombre del puerto)
screen /dev/tty.usbmodem* 115200
```

10. Para verificar que el archivo esté ahí:

```bash
ls /Volumes/CIRCUITPY/
```

11. Revisar los mensajes (logs) en tiempo real:

```bash
ls /dev/tty.*
```

Y luego buscar algo tipo:

```cpp
screen /dev/tty.usbmodem14201 115200
```

12. Para verificar el nombre exacto del archivo:

- Presionar Ctrl+D para recargar
- Revisa el contenido de CIRCUITPY desde otra terminal (sin cerrar screen, abre una pestaña nueva en Terminal):

```bash
ls -la /Volumes/CIRCUITPY/
ls /Volumes/CIRCUITPY/lib/
```

13. Si queremos ejecutarlo manualmente desde el REPL para ver el error exacto:

```bash
import code
```


## Investigación sobre API

Información sacada de: 

https://openweathermap.org/api

https://www.ibm.com/es-es/think/topics/api

Una API (por sus siglas en inglés, Application Programming Interface o Interfaz de Programación de Aplicaciones) es un componente fundamental en el desarrollo de software moderno.


## Origen

Aunque hoy asociamos las API a las páginas web, el concepto nació en 1968. Los científicos de computación Ira Cotton y Frank Greatorex crearon un sistema para que diferentes programas de software pudieran interactuar dentro de una misma computadora principal. Internet ni siquiera existía tal como lo conocemos.


## ¿Qué es una API?

Según la documentación de IBM, una API es un conjunto de reglas, protocolos y especificaciones que permite que diferentes aplicaciones informáticas se comuniquen entre sí para intercambiar datos, características y funcionalidades.

En lugar de crear cada herramienta u origen de datos desde cero, las API permiten a los desarrolladores conectar e integrar sistemas existentes de forma rápida y segura. Actúan como un puente o intermediario invisible para el usuario final, ofreciendo una conexión fluida dentro del software.


## El concepto de "Caja Negra" y Seguridad

Las API permiten compartir únicamente la información necesaria para una solicitud específica, manteniendo ocultos los detalles internos del código, el servidor o la base de datos. Esto añade una capa crítica de seguridad, ya que los dispositivos externos no tienen acceso total al sistema, sino solo a pequeños paquetes de datos autorizados.


## ¿Cómo funciona una API?

El funcionamiento básico de una API sigue el modelo de Cliente y Servidor a través de la infraestructura de Internet, normalmente mediante el protocolo HTTP (sistema de reglas mediante el cual un cliente (como una app o web) y un servidor se comunican). 


IBM lo ejemplifica de manera sencilla a través de los siguientes pasos:

Cliente / App  --- (1) Envía Petición (URI/HTTP) --->  API ---> (2) Llama al programa externo

Cliente / App <--- (4) Entrega Datos en Pantalla <-- Bridge  <--- (3) Responde con la información <--- Servidor Externo


1. La Petición (Request): Una aplicación (el cliente) envía una solicitud de datos a través de una dirección específica (URI). Esta petición incluye un verbo de solicitud (como GET para leer datos o POST para enviar datos) y una cabecera.

2. El Procesamiento: La API toma la solicitud y llama al servidor web o programa externo que contiene la información.

3. La Respuesta (Response): El servidor procesa la orden y envía los datos de vuelta a la API (generalmente organizados en formatos estandarizados y ligeros como JSON o XML).

4. La Entrega: La API transfiere estos datos a la aplicación inicial, que los interpreta y los muestra al usuario en su interfaz.


Un ejemplo cotidiano es cuando compras en una tienda online y seleccionas "Pagar con PayPal". La tienda no conoce tus claves bancarias; utiliza una API para comunicarse con PayPal, procesar el pago de forma segura y recibir de vuelta la confirmación de que el pago fue exitoso.


## Tipos de API

IBM clasifica las API principalmente bajo dos criterios: su accesibilidad (casos de uso en la web) y su arquitectura técnica.

- API Abiertas (o Públicas): Son de código abierto y cualquier desarrollador puede acceder a ellas a través del protocolo HTTP. Tienen puntos de conexión (endpoints) y formatos de respuesta definidos públicamente.

- API de Socios (Partner APIs): Diseñadas para conectar con socios estratégicos de negocio. Se accede a ellas mediante portales específicos de desarrolladores, pero requieren un proceso de validación y credenciales de inicio de sesión específicas.

- API Internas (o Privadas): Permanecen ocultas para el público general. Las empresas las utilizan internamente para comunicar diferentes componentes o departamentos de desarrollo y mejorar la productividad.

- API Compuestas: Combinan múltiples API de datos o servicios diferentes. Permiten que un programador haga una única llamada y obtenga información de varias fuentes a la vez (muy útil en arquitecturas de microservicios).


## Protocolos y estilos arquitectónicos:

- REST (Representational State Transfer): Es el estilo más común en las API web modernas. Utiliza el protocolo HTTP, es ligero y es compatible con múltiples lenguajes de programación y formatos como JSON.

- SOAP (Simple Object Access Protocol): Un protocolo de mensajería rígido y altamente estructurado basado estrictamente en XML, muy utilizado en entornos empresariales que requieren alta seguridad y contratos de datos estrictos.

- RPC (Remote Procedure Call): Protocolos orientados a ejecutar procedimientos o tareas en sistemas remotos como si fuesen locales (pueden basarse en XML o JSON).


## ¿Cómo se empieza a usar una API?

La plataforma de OpenWeather muestra los tres pasos estándar de la industria para trabajar con este recurso:

- Registro y API Key: El desarrollador crea una cuenta y la plataforma le otorga una API Key (una clave o token alfanumérico). Esta clave funciona como una firma digital o contraseña para rastrear quién hace la petición y controlar los límites de consumo.

- Consulta de la documentación: Se revisa el manual técnico para saber exactamente cómo escribir la dirección URI de la consulta.

- Integración: Se programa la llamada dentro del código de la aplicación para automatizar la solicitud de datos.

En resumen, las API son el tejido conectivo de internet. Permiten que un diseñador o programador cree una aplicación que muestre mapas interactivos, procese pagos o dé el pronóstico del tiempo en tiempo real, delegando la complejidad de los datos a servicios expertos externos.


## Pueste digital: Codigo y proceso

### Entrada - Sensor Infrarrojo (código en Raspberry) / código que envía

Recomendaciones:

No subir tu clave Adafruit a github, ni a ninguna parte!!
Utilizar un wifi solo para la Raspberry
No pasar tan lejos del sensor
Pasar de a poquitos y lento, porque el Sensor Infrarojo le cuesta un poquito, pero se puede!!
No te estreses con la Raspberry, a veces no se conecta a WIFI, pero solo reinicialo y funcionará

```cpp
# PUENTE DIGITAL - Grupo 6 - Examen
# Lunes 22 de junio
# Raspberry Pi Pico 2W (CircuitPython)
# Lee el Sensor Infrarrojo Evasor de Obstaculos y publica el
# conteo de personas ("entrada") a Adafruit IO via MQTT.

import time
import board # type: ignore
import digitalio # type: ignore
import wifi # type: ignore
import socketpool # type: ignore
import ssl
import adafruit_minimqtt.adafruit_minimqtt as MQTT # type: ignore

# CONFIGURACION WIFI 
WIFI_SSID = "blabla"
WIFI_PASSWORD = "blabla"

# CONFIGURACION ADAFRUIT IO 
ADAFRUIT_IO_USER = "blabla"
ADAFRUIT_IO_KEY  = "blabla"
FEED_ID = "lid-conteo"   # nombre del feed creado en Adafruit IO

# CONFIGURACION SENSOR 
# El sensor IR evasor de obstaculos entrega:
#  - HIGH (3.3V) cuando NO hay obstaculo
#  - LOW  (0V)   cuando detecta un obstaculo (persona pasando)
ir_sensor = digitalio.DigitalInOut(board.GP15)
ir_sensor.direction = digitalio.Direction.INPUT
ir_sensor.pull = digitalio.Pull.UP

# VARIABLES DE CONTEO 
contador = 0
MAX_CONTEO = 16          # tope = cantidad de LEDs del anillo
estado_anterior = True   # True = sin obstaculo (reposo)
ANTIREBOTE = 0.2         # segundos; baja si necesitas detectar personas muy rapidas

# FUNCION DE CONEXION (sirve para reconectar)
def conectar_wifi():
    print("Conectando a WiFi...")
    intentos = 0
    while not wifi.radio.connected and intentos < 10:
        try:
            wifi.radio.connect(WIFI_SSID, WIFI_PASSWORD)
        except ConnectionError as e:
            print("Fallo WiFi, reintentando...", e)
            intentos += 1
            time.sleep(2)
    print("WiFi conectado. IP:", wifi.radio.ipv4_address)

# FUNCION DE CONEXION MQTT (adafruit io)
def conectar_mqtt(client):
    print("Conectando a Adafruit IO...")
    intentos = 0
    conectado = False
    while not conectado and intentos < 5:
        try:
            client.connect()
            conectado = True
            print("Conectado a Adafruit IO.")
        except (MQTT.MMQTTException, OSError) as e:
            intentos += 1
            print("Fallo MQTT (intento {}), reintentando...".format(intentos), e)
            time.sleep(3)
    return conectado


# CONEXION WIFI
conectar_wifi()

# CONEXION MQTT (ADAFRUIT IO)
# Puerto 1883 (sin SSL): mas compatible con redes universitarias
# que suelen bloquear el puerto 8883 (SSL/TLS) para MQTT.
pool = socketpool.SocketPool(wifi.radio)
mqtt_client = MQTT.MQTT(
    broker="io.adafruit.com",
    port=1883,
    username=ADAFRUIT_IO_USER,
    password=ADAFRUIT_IO_KEY,
    socket_pool=pool,
)

conectar_mqtt(mqtt_client)

# aqui se define el topic completo para publicar el conteo en el feed de Adafruit IO
feed_topic = ADAFRUIT_IO_USER + "/feeds/" + FEED_ID

# BUCLE PRINCIPAL / FUNCION PRINCIPAL DEL CODIGO
while True:
    try:
        mqtt_client.loop()

        estado_actual = ir_sensor.value

        # detecta flanco de bajada: HIGH -> LOW = persona pasando
        if estado_anterior is True and estado_actual is False:
            contador += 1

            # si llega al maximo, vuelve a 0 (ciclo)
            if contador > MAX_CONTEO:
                contador = 0

            print("Persona detectada -> conteo:", contador)
            mqtt_client.publish(feed_topic, contador)

            # antirebote reducido: evita contar la misma persona dos
            # veces sin perder detecciones rapidas consecutivas
            time.sleep(ANTIREBOTE)

        estado_anterior = estado_actual
        time.sleep(0.02)  # lectura mas frecuente del sensor

# si llegase a fallar la conexion MQTT, intenta reconectar sin reiniciar el dispositivo
    except (ValueError, RuntimeError, OSError, MQTT.MMQTTException) as e:
        print("Error de conexión, reintentando...", e)
        time.sleep(2)
        try:
            mqtt_client.reconnect()
        except (RuntimeError, OSError, MQTT.MMQTTException):
            # si reconnect() falla, reintenta conexion completa
            if not wifi.radio.connected:
                conectar_wifi()
            conectar_mqtt(mqtt_client)
```


### Resumen del código entrada (para que se entienda mejor)

INICIO
    Configurar WiFi, MQTT, Sensor IR y Contador = 0
    Conectar a WiFi y Servidor MQTT (Adafruit IO)

    BUCLE PRINCIPAL:
        INTENTAR:
            Leer sensor IR
            SI cambia de Reposo a Obstáculo (Persona pasando) ENTONCES
                Incrementar Contador (si supera 16, vuelve a 0)
                Publicar Contador en Adafruit IO vía MQTT
                Esperar antirebote (0.2s)
            FIN SI
            Esperar 0.02s
        
        EXCEPCIÓN (Si cae la red):
            Esperar 2s e intentar reconectar WiFi y MQTT
FIN



### SALIDA - Anillo LED (código en Arduino) / código que recibe

Recomendaciones:

Tratar con cariño y calma el Arduino...
Se demora en leer los valores de Adafruit, así que no se estresen!!
Le pueden cambiar los colores

```cpp
// PUENTE DIGITAL — Grupo 6 - Examen
// Lunes 22 de junio
// Recibe el conteo desde Adafruit IO (MQTT) y lo representa
// encendiendo el Anillo LED RGB WS2812 de 16 LEDs ("salida").
// Librerias necesarias:
//  - WiFiS3 (incluida con el core de UNO R4)
//  - ArduinoMqttClient
//  - Adafruit NeoPixel

#include <WiFiS3.h>
#include <ArduinoMqttClient.h>
#include <Adafruit_NeoPixel.h>

// CONFIGURACION ANILLO LED
// definir el pin digital al que va conectado
#define LED_PIN   6
#define NUM_LEDS  16

Adafruit_NeoPixel ring(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);

// CONFIGURACION WIFI - anota tu wifi
char ssid[] = "blabla";
char pass[] = "blabla";

// CONFIGURACION ADAFRUIT IO - anota tu adafruit
const char broker[]  = "io.adafruit.com";
int        port      = 1883;
const char* aio_user = "blabla";
const char* aio_key  = "blabla";

// se crea el feed en Adafruit
String feedTopic = String(aio_user) + "/feeds/lid-conteo";

WiFiClient   wifiClient;
MqttClient   mqttClient(wifiClient);

// COMENZAMOS CON LOS PASOS DEL CODIGO
void setup() {
  Serial.begin(115200);

   // inicializar anillo LED
  ring.begin();
  ring.setBrightness(50);
  ring.show(); // apagado al inicio

  // conectar WiFi
  Serial.print("Conectando a WiFi");
  while (WiFi.begin(ssid, pass) != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
  }

  // se imprime en el serial monitor si esta conectado o no
  Serial.println();
  Serial.println("WiFi conectado");
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());

  // conectar a Adafruit IO via MQTT
  mqttClient.setUsernamePassword(aio_user, aio_key);

  Serial.print("Conectando a Adafruit IO");
  while (!mqttClient.connect(broker, port)) {
    Serial.print(".");
    delay(1000);
  }
  Serial.println();
  Serial.println("Conectado a Adafruit IO");

  // suscribirse al feed
  // imprime si ya se conecto al feed correspondiente
  mqttClient.subscribe(feedTopic);
  Serial.print("Suscrito a: ");
  Serial.println(feedTopic);
}

// esto fue lo que se agrego para que arduino leyera
// mejor los valores de adafruit
// sirve para estabilizar la conexion wifi
unsigned long ultimaRevisionConexion = 0;
const unsigned long INTERVALO_REVISION = 5000; // revisa conexión cada 5s, no cada loop

// COMENZAMOS CON LAS FUNCIONES DEL CODIGO
void loop() {
  // mqttClient.poll() debe llamarse lo mas seguido posible,
  // sin delays que la bloqueen entremedio.
  mqttClient.poll();

// se realiza la conexion mqtt para captar los datos de Adafruit IO
  int messageSize = mqttClient.parseMessage();
  if (messageSize > 0) {
    String payload = "";
    while (mqttClient.available()) {
      payload += (char)mqttClient.read();
    }

    // al recibir los datos, los imprime como "conteo recibido"
    int conteo = payload.toInt();
    Serial.print("Conteo recibido: ");
    Serial.println(conteo);

    actualizarAnillo(conteo);

    // revisa si quedo otro mensaje mas encolado
    messageSize = mqttClient.parseMessage();
  }

  // revisa la conexion solo cada cierto intervalo, no en cada
  // vuelta del loop -> evita overhead y delays innecesarios
  unsigned long ahora = millis();
  if (ahora - ultimaRevisionConexion >= INTERVALO_REVISION) {
    ultimaRevisionConexion = ahora;

    if (WiFi.status() != WL_CONNECTED) {
      Serial.println("WiFi perdido, reconectando...");
      WiFi.begin(ssid, pass);
    }

    if (!mqttClient.connected()) {
      Serial.println("MQTT desconectado, reconectando...");
      if (mqttClient.connect(broker, port)) {
        mqttClient.subscribe(feedTopic);
      }
    }
  }
}

// Enciende los LEDs correspondientes según el conteo recibido
// Relacion directa: 1 persona = 1 LED encendido
//   1 persona  -> LED 1 encendido
//   2 personas -> LEDs 1 y 2 encendidos
//   ...
//   16 personas -> los 16 LEDs encendidos (anillo lleno)
// Color segun nivel de ocupacion:
//   1-5   -> verde   (poco ocupado)
//   6-10  -> amarillo (ocupación media)
//   11-16 -> rojo    (casi lleno / lleno)
void actualizarAnillo(int conteo) {
  int ledsActivos = constrain(conteo, 0, NUM_LEDS);

  for (int i = 0; i < NUM_LEDS; i++) {
    if (i < ledsActivos) {
      if (ledsActivos <= 5) {
        ring.setPixelColor(i, ring.Color(0, 255, 0));     // verde
      } else if (ledsActivos <= 10) {
        ring.setPixelColor(i, ring.Color(255, 255, 0));   // amarillo
      } else {
        ring.setPixelColor(i, ring.Color(255, 0, 0));     // rojo
      }
    } else {
      ring.setPixelColor(i, ring.Color(0, 0, 0));         // apagado
    }
  }
  ring.show();
}
```

### Resumen del código de salida (para que se entienda mejor)

INICIO
    Configurar WiFi, MQTT y Anillo de 16 LEDs
    Conectar a WiFi y Servidor MQTT (Adafruit IO)
    Suscribirse al feed "lid-conteo"

    BUCLE PRINCIPAL:
        Mantener activa la sesión MQTT
        
        SI llega un mensaje nuevo de Adafruit IO ENTONCES
            Leer el valor (Conteo)
            Actualizar Anillo LED:
                - Encender cantidad de LEDs igual al Conteo
                - Si es de 1-5: Color Verde
                - Si es de 6-10: Color Amarillo
                - Si es de 11-16: Color Rojo
                - Apagar el resto de los LEDs
        FIN SI

        CADA 5 SEGUNDOS:
            SI se pierde la señal de WiFi o MQTT ENTONCES
                Intentar reconectar y volver a suscribirse
            FIN SI
FIN


### Demostraciones en vivo (gif/foto)


<img width="3024" height="4032" alt="puenteDigital" src="https://github.com/user-attachments/assets/93ffa165-1479-45a8-aa22-d4abb6830eb3" />



<img width="576" height="1024" alt="digiprueba" src="https://github.com/user-attachments/assets/6bc2e232-1aa4-4880-9632-bc30a04dd6e3" />


### Demostraciones en vivo de Peñalolén y Quilicura :)

Decidimos elevar el nivel de dificultad del proyecto probando la conexión inalámbrica a grandes distancias. La infraestructura se distribuyó geográficamente de esta forma:

EDIFICIO A → LID (Salvador Sanfuentes) → Peñalolén (casa sofi)

EDIFICIO B → Rep180 (oficina Aarón) → Quilicura (casa vale)

Lo destacable es que la conexión remota funcionó perfectamente a pesar de los kilómetros de distancia. Además, el sistema demostró ser altamente adaptable, ya que para cambiarlo de lugar solo se requiere modificar la red Wi-Fi y contraseña en el código, sin perder la vinculación ni el flujo de datos hacia Adafruit IO.


<img width="576" height="1024" alt="locura1" src="https://github.com/user-attachments/assets/3c4e01f6-ccc0-4fb0-a544-3f559d06d3bd" />


## Bibliografía

Instituto Superior Tecnológico Quito Metropolitano [ITSQMET]. (sf). ¿Qué es una API y para qué sirve? https://itsqmet.edu.ec/api/

Outvio. (sf). ¿Qué es una API y cómo funciona en desarrollo y logística? https://outvio.com/es/blog/que-es-una-api/

OpenWeatherMap. (sf). API meteorológica: Datos meteorológicos actuales y pronóstico. https://openweathermap.org/api

Wikipedia. (2026, 21 de junio). API. https://en.wikipedia.org/wiki/API

Reclutar. (sf). Historia y evolución de las API. https://recluit.com/historia-y-evolucion-de-las-api/

Akamai. (sf). ¿Cómo funcionan las API? Conceptos básicos y seguridad. Recuperado el 21 de junio de 2026, de https://www.akamai.com/es/glossary/how-do-apis-work

Afel Electrónica. (s.f.). Inicio: Componentes electrónicos y robótica en Chile. Recuperado el 21 de junio de 2026, de https://afel.cl/

Adafruit Industries. (s.f.). Adafruit: Electronics, kits, and open-source hardware. Recuperado el 21 de junio de 2026, de https://www.adafruit.com/

Arduino. (s.f.). Arduino: Open-source electronic prototyping platform. Recuperado el 21 de junio de 2026, de https://www.arduino.cc/

MCI Electronics. (s.f.). MCI Electronics: Soluciones tecnológicas y componentes para ingeniería. Recuperado el 21 de junio de 2026, de https://mcielectronics.cl/

Raspberry Pi Foundation. (s.f.). Raspberry Pi: Computing for everyone. Recuperado el 21 de junio de 2026, de https://www.raspberrypi.com/
