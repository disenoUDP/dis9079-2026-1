# solemne-02

## Integrantes

- Magdalena Balart / magdalenabalart
- Jesús Miranda / jesumirandaa
- Carla Núñez / ccarlabelenn

## Descripción textual del proyecto

## Materiales usados
+ Raspberry pi pico 2w
+ Arduino R4 Wifi
+ Protoboard
+ Cables dupont
+ Botón - pulsador
+ Pantalla OLED
+ Cable USB-C
+ Cable Micro USB
## Sensor usado  
```
pulsador táctil
``` 
Para el sensor decidimos utilizar un botón pulsador conectado a nuestra Raspberry Pi, ya que nos permitía transformar una acción física muy simple en el envío de un mensaje a la nube. En este caso, el botón funciona como el punto de inicio del sistema: al presionarlo, la Raspberry detecta la acción y envía un mensaje al feed de Adafruit IO.

El sistema está pensado como una secuencia de cuatro mensajes. Cada vez que se presiona el botón, se envía una parte distinta: primero “Sonríe por mí”, luego “amigo”, después “yo sonrío por ti” y finalmente “...”. Después de la cuarta pulsación, la secuencia vuelve a empezar desde el primer mensaje.

Durante las pruebas nos dimos cuenta de que la forma de presionar el botón también influía en el funcionamiento. No bastaba con tocarlo muy rápido, porque a veces costaba que se enviara correctamente el siguiente mensaje. En nuestro caso, funcionaba mejor mantenerlo presionado hasta que el mensaje se enviara y luego soltarlo, para que el sistema pudiera reconocer bien una pulsación antes de pasar a la siguiente. Esto nos ayudó a entender que la interacción con el sensor no era solo técnica, sino también corporal. El botón necesitaba un gesto claro: presionar, esperar y soltar. Así, cada pulsación se volvía una pequeña acción de comunicación, donde el contacto físico activaba el envío de una parte del mensaje. 

## Actuador usado 
``` 
Display OLED de 128 x 64 Pixeles Controlable por I2C
```

Para el actuador utilizamos una pantalla OLED conectada a nuestro Arduino, permitiendo que se proyectaran visualmente los cuatro mensajes enviados desde la Raspberry. En este caso, la pantalla funcionaba como la salida del sistema: recibía la información desde Adafruit IO y la transformaba en texto visible.

Durante el proceso tuvimos algunos problemas con el código encargado de recibir el texto. En un momento, el Arduino no lograba conectarse correctamente a Adafruit IO, por lo que la pantalla mostraba un mensaje de error. Después de resolver la conexión, nos dimos cuenta desde el software de Arduino que el código ya estaba funcionando y que el Arduino sí estaba recibiendo los mensajes. Sin embargo, la pantalla OLED se había quedado pegada con el mensaje de error anterior, por lo que visualmente parecía que el sistema seguía fallando.

Para solucionar eso, tuvimos que ajustar el código con Chatgpt para que la pantalla se limpiara y actualizara cada vez que llegara un nuevo mensaje. La parte clave fue agregar una función que reiniciara lo que estaba mostrando la pantalla antes de escribir el nuevo contenido: 
```
display.clearDisplay();
```
Esa instrucción limpia la pantalla antes de mostrar un nuevo mensaje 
```
display.display();
```
la pantalla se actualiza y muestra el contenido nuevo. Gracias a eso, la OLED dejó de quedarse pegada con el mensaje de error y empezó a mostrar correctamente los mensajes recibidos desde Adafruit IO.

Esto nos permitió entender que la pantalla no se actualiza sola: necesita que el código primero borre lo anterior, escriba el nuevo mensaje y finalmente lo proyecte. 

| Material              | Descripción / Función                                                                 |
|-----------------------|---------------------------------------------------------------------------------------|
| Raspberry Pi Pico 2W  | Microcontrolador principal con conectividad Wi-Fi y Bluetooth; ejecuta la lógica del sistema |
| Arduino UNO R4 WiFi   | Placa de desarrollo con conectividad Wi-Fi integrada; permite comunicación inalámbrica y procesamiento adicional |
| Protoboard            | Tablero de prototipado sin soldadura; permite conectar componentes de forma temporal y ordenada |
| Cables Dupont         | Cables de conexión macho-macho, macho-hembra o hembra-hembra; utilizados para interconectar componentes en la protoboard |
| Botón / Pulsador      | Componente de entrada digital; permite al usuario enviar señales al microcontrolador mediante presión |
| Pantalla LCD OLED 1.3 | Display de salida visual; muestra información del sistema como datos, estados o mensajes |

## Sensor usado
Para el sensor decidimos utilizar un botón - pulsador de cuatro pines de 7mm conectado a nuestra Raspberry Pi Pico 2 W, permitiendonos enviar el mensaje a la nube con tan solo presionarlo, se presiona cuatro veces para proyectar los cuatro mensajes. (agregar info)

## Actuador usado
Para el actuador utilizamos una panatalla OLED, conectada a nuestro Arduino UNO R4 WiFi permitiendo así que se proyecten los cuatro mensajes. (agregar más info)

## Código usado para enviar

```cpp 
import time
import board
import digitalio
import wifi
import socketpool
import adafruit_minimqtt.adafruit_minimqtt as MQTT

print("Iniciando programa...")

# WiFi

SSID = "internetmagdalena"
PASSWORD = "Magdita12345"

print("Conectando WiFi...")

try:
    wifi.radio.connect(SSID, PASSWORD)
    print("WiFi conectado")
    print("IP:", wifi.radio.ipv4_address)

except Exception as e:
    print("Error WiFi:")
    print(e)

    while True:
        pass

# Adafruit IO

AIO_USERNAME = "usernameadafuit"
AIO_KEY = "keyadafruit"

# Feed al que se envían los mensajes
FEED_BOTON = AIO_USERNAME + "/feeds/prueba05"

print("Creando conexión MQTT...")

pool = socketpool.SocketPool(wifi.radio)

mqtt = MQTT.MQTT(
    broker="io.adafruit.com",
    username=AIO_USERNAME,
    password=AIO_KEY,
    socket_pool=pool,
)

print("Conectando a Adafruit IO...")

try:
    mqtt.connect()
    print("Conectado a Adafruit IO")

except Exception as e:
    print("Error MQTT:")
    print(e)

    while True:
        pass

# Botón GP0

boton = digitalio.DigitalInOut(board.GP0)
boton.direction = digitalio.Direction.INPUT
boton.pull = digitalio.Pull.UP

estado_anterior = True

# Contador de presiones
contador_boton = 0

# Mensajes que se enviarán en orden
mensajes = ["Sonrie por mi", "amigo", "yo sonrio por ti", "..."]

print("Sistema listo")
print("Esperando botón...")



# Loop principal

while True:

    try:
        mqtt.loop()

        estado_actual = boton.value

        # Detecta cuando el botón pasa de NO presionado a presionado
        if estado_anterior == True and estado_actual == False:

            mensaje = mensajes[contador_boton]

            print("Botón presionado")
            print("Enviando:", mensaje)

            mqtt.publish(FEED_BOTON, mensaje)

            print("Mensaje enviado a Adafruit IO")

            # Avanza al siguiente mensaje
            contador_boton = contador_boton + 1

            # Si ya mandó boton 03, vuelve a boton 01
            if contador_boton >= 4:
                contador_boton = 0

            # Anti-rebote
            time.sleep(0.3)

            # Espera a que sueltes el botón antes de leer otra presión
            while boton.value == False:
                mqtt.loop()
                time.sleep(0.01)

        estado_anterior = boton.value

    except Exception as e:
        print("Error:")
        print(e)

    time.sleep(0.02)  
```

## **<ins>Configuración del botón</ins>** 

```
boton = digitalio.DigitalInOut(board.GP0)
boton.direction = digitalio.Direction.INPUT
boton.pull = digitalio.Pull.UP
```

**boton.direction** = INPUT significa que ese pin va a leer información, no enviar.   
**boton.pull** = Pull.UP activa una resistencia interna pull-up.  

Eso significa:

**Botón sin presionar** = True  
**Botón presionado** = False    
 
**<ins>Estado anterior y contador</ins>** 
 
```
estado_anterior = True
contador_boton = 0
```
estado_anterior guarda cómo estaba el botón antes.
Esto sirve para detectar el momento exacto en que se presiona, no para estar leyendo todo el rato que está apretado.
contador_boton sirve para saber qué mensaje toca enviar. 

**<ins>Loop principal</ins>**  
```
while True:
``` 
Esto significa que el programa se repite para siempre.
```
mqtt.loop()
``` 
Esto mantiene viva la conexión con Adafruit IO
```
estado_actual = boton.value
```
**<ins>Detección de presión</ins>**  
```
if estado_anterior == True and estado_actual == False:
```
> “Si antes el botón no estaba presionado y ahora sí está presionado, entonces acaba de ocurrir una pulsación”.

Si antes el botón estaba sin presionar y ahora está presionado, entonces detectamos una nueva pulsación. 

Sin presionar:
GP0 lee True
  
Presionado:
GP0 lee False 

el código está buscando el momento exacto en que pasa de: 
botón suelto → botón presionado
True → False 

el pull-up evita lecturas falsas y deja claro cuándo el botón está suelto y cuándo fue presionado. 

**<ins>Elegir y enviar mensaje</ins>**   

Para que el botón enviara mensajes distintos, usamos un contador de pulsaciones. Este contador parte desde cero y va aumentando cada vez que el botón es presionado. En el código, los mensajes están guardados dentro de una lista, y cada posición de esa lista corresponde a un mensaje diferente.   
```
estado_anterior = True
contador_boton = 0
```
Como Python empieza a contar desde cero, el primer mensaje está en la posición 0, el segundo en la posición 1, el tercero en la posición 2 y el cuarto en la posición 3. Entonces, cuando se presiona el botón, el código revisa en qué número va el contador y envía el mensaje correspondiente. 
 
```
mensaje = mensajes[contador_boton] 
```
Aquí se elige el mensaje que corresponde según el contador.

Si contador_boton vale 0, manda el primer mensaje.
Si vale 1, manda el segundo.
Si vale 2, manda el tercero.   
  
```
mqtt.publish(FEED_BOTON, mensaje)
```
Esta línea envía el mensaje a Adafruit IO  

**<ins>Avanzar al siguiente mensaje</ins>**  
```
contador_boton = contador_boton + 1 
```
Después de enviar un mensaje el contador sube en 1 para que la próxima pulsación mande el siguiente 
```
if contador_boton >= 4:
    contador_boton = 0
```
cuando el contador llega a 4, vuelve a 0, eso significa que vuelve a empezar la secuencia. 

si tenemos más de 4 mensajes el codigo podría cambiar para no tener que cambiar manualmente el número: 
```
if contador_boton >= len(mensajes):
    contador_boton = 0
```
**<ins>Anti-rebote</ins>**   
```
time.sleep(0.3)
```
Esta pausa evita que una sola presión se lea muchas veces por el rebote del botón 

```
while boton.value == False:
    mqtt.loop()
    time.sleep(0.01)
```
Espera a que soltemos el botón antes de permitir otra lectura
> “Ya mandé el mensaje. Ahora no voy a mandar otro hasta que el botón se suelte”.

**<ins>Actualizar estado anterior</ins>** 
```
estado_anterior = boton.value
```
Guarda el estado actual del botón 

**<ins>RESUMEN DE LO QUE HACE NUESTRO CODIGOr</ins>**
```  
Presiono botón 
↓  
Raspberry detecta la presión  
↓  
Busca qué mensaje toca enviar  
↓  
Lo publica en Adafruit IO  
↓  
El contador avanza  
↓  
Espera a que suelte el botón  
↓  
Queda lista para la siguiente presión   
```

## Código usado para recibir

```cpp
#include "config.h"

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// -------------------------
// Pantalla OLED
// -------------------------
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// -------------------------
// Feed Adafruit IO
// -------------------------
AdafruitIO_Feed *botonFeed = io.feed("prueba05");

// -------------------------
// Mostrar texto en pantalla
// -------------------------
void mostrarPantalla(String linea1, String linea2) {
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);

  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println(linea1);

 display.setTextSize(1);
 display.setCursor(0, 25);
 display.println(linea2);  

  display.display();
}

// -------------------------
// Cuando llega mensaje
// -------------------------
void handleMessage(AdafruitIO_Data *data) {
  String mensaje = data->toString();

  Serial.print("Mensaje recibido: ");
  Serial.println(mensaje);

  mostrarPantalla("Mensaje recibido:", mensaje);
}

// -------------------------
// Setup
// -------------------------
void setup() {
  Serial.begin(115200);
  delay(3000);

  Serial.println("Iniciando...");

  // Iniciar pantalla
  Wire.begin();

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("No se encontro pantalla OLED");
    while (true);
  }

  mostrarPantalla("Iniciando...", "");

  // Asociar feed a funcion
  botonFeed->onMessage(handleMessage);

  Serial.println("Conectando a Adafruit IO...");
  mostrarPantalla("Conectando a", "Adafruit");

  io.connect();

  while (io.status() < AIO_CONNECTED) {
    io.run();

    Serial.print("Estado: ");
    Serial.println(io.statusText());

    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 0);
    display.println("Conectando...");
    display.println(io.statusText());
    display.display();

    delay(1000);
  }

  Serial.println("Conectado a Adafruit IO");

  mostrarPantalla("Conectado!", "OK");

  delay(1500);

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("Esperando mensaje");
  display.println("del boton...");
  display.display();

  // Trae el ultimo mensaje enviado al feed
  botonFeed->get();
}

// -------------------------
// Loop
// -------------------------
void loop() {
  io.run();
}
```
## **<ins>Configuración de la pantalla OLED</ins>** 
```
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1 
```
Aquí se define el tamaño de la pantalla 

**<ins>Cómo lee el mensaje</ins>**  
```
AdafruitIO_Feed *botonFeed = io.feed("prueba05");
```
Eso significa: “voy a estar atento al feed llamado prueba05”.
Ese feed es el mismo donde la Raspberry está publicando los mensajes.  

```
botonFeed->onMessage(handleMessage);
```
> “Cada vez que llegue un mensaje nuevo al feed prueba05, ejecuta la función handleMessage”.

De esta forma nuestro arduino queda suscrito al feed, esperando que llegue algo.

 **<ins>La función que recibe el mensaje es:</ins>**  
```
void handleMessage(AdafruitIO_Data *data) {
  String mensaje = data->toString();

  Serial.print("Mensaje recibido: ");
  Serial.println(mensaje);

  mostrarPantalla("Mensaje recibido:", mensaje);
}
```

Cuando llega un dato desde Adafruit IO, ese dato entra como **data** 
Pero **data** viene en un formato propio de Adafruit, no como texto directo. Por eso se usa esta línea
```
String mensaje = data->toString();
```
Eso convierte el dato recibido en texto normal, para que Arduino pueda mostrarlo o imprimirlo. 

**<ins>RESUMEN DE LO QUE HACE NUESTRO CODIGOr</ins>** 
```
Raspberry presiona botón  
↓  
Raspberry publica mensaje en Adafruit IO  
↓  
Feed prueba05 recibe el mensaje  
↓  
Arduino está escuchando ese feed  
↓  
Llega el mensaje y se activa handleMessage  
↓ 
Arduino convierte el dato a texto  
↓  
OLED muestra el mensaje  
```

## Config.h
```cpp
/** Adafruit IO Config **/

#define IO_USERNAME  "Magdalena"
#define IO_KEY       "keyadafruit"

/** WiFi Config **/

#define WIFI_SSID    "internetmagdalena"
#define WIFI_PASS    "Magdita12345"

/** Librería Adafruit IO */

#include "AdafruitIO_WiFi.h"

AdafruitIO_WiFi io(IO_USERNAME, IO_KEY, WIFI_SSID, WIFI_PASS);
```

## Imágenes del proyecto

<img src="./imagenes/fotorasp01.png" alt="hacerbien" width="40%"> <img src="./imagenes/foto raps02.png" alt="hacerbien" width="40%">  

<img src="./imagenes/fotoadafruit.jpg" alt="hacerbien" width="40%"> <img src="./imagenes/fotooled01.png" alt="hacerbien" width="40%"> <img src="./imagenes/fotooled02.jpg" alt="hacerbien" width="40%">   <img src="./imagenes/fotooled03.jpg" alt="hacerbien" width="40%">   

## Animaciones del proyecto

<img src="./imagenes/pantalla02.gif" alt="hacerbien" width="30%">  
<img src="./imagenes/pantallamensaje.gif" alt="hacerbien" width="30%">  


## Bibliografía 
<img src="./imagenes/patti.jpg" alt="hacerbien" width="30%">  
<img src="./imagenes/metodouniverlsal.jpg" alt="hacerbien" width="30%">    

https://www.instructables.com/Arduino-Button-with-no-resistor/
## Bibliografía
Smith, Patti. Éramos unos niños. Lumen, 2010

https://docs.arduino.cc/tutorials/generic/digital-input-pullup/

https://learn.adafruit.com/mqtt-in-circuitpython/overview?utm_source=chatgpt.com
