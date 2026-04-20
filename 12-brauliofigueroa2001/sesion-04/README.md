# sesion-04

lunes 30 marzo 2026

## primera parte

- tplink es una empresa de routers y modems, todas esas cosas que se conectan a internet

- el router emite una red con el nombre del curso y una clave, crearon una red wifi, pero no tiene internet, solo wifi sin internet

- mateo abrió tplinkwifi.net

- antes se usaba 2.4ghz ahora 5g en general

- existe una lista de clientes "dhcp", de momento aparecen 2 ID, existe un cliente raspidis9079, tiene una dirección mac, un ip asignado y un tiempo de arrendamiento que es cuanto tiempo puedo estar conectado

- todavía no es necesario que usemos muchos computadores con la misma ip, por la complejidad que estamos manejando

- desconectó el router, la red murió, conectó el router y la red vivió

- mateo entró en la terminal y buscó el raspi, se conectó?? no entendí mucho

- tigervnc

- haremos el vlc desde el compu de aarón, esto es para poder revisar en vivo qué ocurre en la raspberry pi sin tocar nada

- se conectaron al escritorio de la raspberry pi, increíble amigos

- cuando mosquitto se prende en el raspberry, aparece como mosquitto.conf, ese era el archivo que estaba en github

- super user do, sudo, significa que todo lo que viene después del super usuario, el computador lo hará

- sudormrf enter, con esto destruyo cualquier computador?? wtf no lo hagan

CÓDIGO EN ARDUINO

- wificlient wificlient; crea una estructura computacional que es capaz de conectarse a wifi

- mqttclient mqfttClient (wifiClient); significa q es una especie de auto que anda sobre este wifi

- const char broker [] = "192.168.0.100"; es la ip de la raspberrypi

- int port = 1883; es el puerto que nos asigna generalmente el computador para comunicaciones mqtt porque los otros puertos del pc hacen otras cosas

- const char topic [], cualquier persona que envía mensajes en mqtt tiene que mandarlo en cierto topic, el que envía y el que recibe deben tener el mismo topic

- mqttClient.setUsernamePassword (mqttID,mqttPass); aquí va la ID y la password

- no pueden llamarse ambos arduinos de la misma forma, deben tener distintos nombres para poder distinguir el que envía del que recibe

- humillada en vivo, el arte de fallar espectacularmente en vivo, es la única clase en las que he estado en las que nos enfrentamos a esto, me gusta esta clase

- hay una cosa que es el ID y otra cosa es el Username, son DISTINTOS

- en el código que estaba utilizando aarón, estaba utilizando estos 2 elementos como si fueran lo mismo y no lo son

- no se pudo arreglar el código de momento, a las 15:38, ampliaremos.

corrección del error

- mosquitto no está corriendo porque acaban de cambiar el archivo de claves

- no he entendido mucho otras cosas del por qué ocurrió el error

- sudo chown, sudo cmod, es durísimo, es como la versión lector cuando entras a un excel, el modo en el que se establece eso

## BREAK Y SEGUNDA PARTE

- cosas del error, ej: en archivos encriptados del codigo no era arduinoReceive sino user1, lo raro es que lo habían cambiado pero aparecía así

- buscar formas más fáciles de usar el mqtt, filo con el mqtt? usaremos otro protocolo wifi

- UDP es un protocolo inalámbrico, los mensajes se envían y a udp no le importa si los mensajes llegan, solo se envían

- se utiliza para video, sirve, ejemplo: en imagen si pierdo 2 pixeles no importa, la imagen se ve igual. En audio si pierdo comunicación no me sirve porque audio requiere ser más estable

- ahora abrirán el puerto 2390 para UDP

- utilizaron un código que nos permite prender y apagar el led cuando nos conectamos a la red wifi sin internet "dis9079"

- cuando nos conectamos, ingresamos la ip en el navegador y se desplegará una página que dice "click here to turn on led" y "click here to turn off led"

- parece que no funcionó, nadie pudo encender el led desde su pc, solo mateo pero al parecer la idea era que todos pudiéramos

- probaron otro método en que también nos conectamos a una ip pero no me dejó entrar, pude conectarme a la red dis9079 sin internet pero no me dejó entrar a la ip

- pra la solemne 1 cada arduino haga cosas a distancia a una raspi y esa raspi a computador, eso ya es extremo, es suficiente, las cosas son difíciles

  ```cpp
#include <ArduinoMqttClient.h>
#include <WiFiS3.h>
char ssid[] = "dis9079";
char pass[] = "75288273";
WiFiClient wifiClient;
MqttClient mqttClient(wifiClient);
const char broker[] = "192.168.0.100";
int port = 1883;
const char topic[] = "dis9079/equipo/luz";
void setup() {
Serial.begin(9600);
pinMode(LED_BUILTIN, OUTPUT);
digitalWrite(LED_BUILTIN, LOW);
Serial.print("Conectando a WiFi...");
while (WiFi.begin(ssid, pass) != WL_CONNECTED) {
Serial.print(".");
delay(1000);
}
Serial.println("\nWiFi conectado!");
mqttClient.setId("CompaneroReceptor");
mqttClient.setUsernamePassword("dis9079", "dis9079");
Serial.print("Conectando al MQTT...");
if (mqttClient.connect(broker, port)) {
Serial.println("\nMQTT conectado!");
mqttClient.subscribe(topic);
Serial.print("Suscrito al topic: ");
Serial.println(topic);
} else {
Serial.println("Fallo conexion MQTT.");
while(1);
}
}
void loop() {
mqttClient.poll();
int messageSize = mqttClient.parseMessage();
if (messageSize) {
String mensaje = "";
while (mqttClient.available()) {
mensaje += (char)mqttClient.read();
}
Serial.print("He recibido la orden: ");
Serial.println(mensaje);
if (mensaje == "PRENDER") {
digitalWrite(LED_BUILTIN, HIGH);
Serial.println("Luz encendida! ");
} else if (mensaje == "APAGAR") {
digitalWrite(LED_BUILTIN, LOW);
Serial.println("Luz apagada. ");
}
}
}
```

### avances e investigación 4 de abril

- paso a paso de la instalación de la librería de adafruit IO en el software de Arduino

![instalacion](./imagenes/instalacionadafruit1.JPG)

- vamos a las bibliotecas en arduino y descargamos la de adafruit

![instalacion](./imagenes/instalacionadafruit2.JPG)

- nos pedirá eso y aceptamos todo

![cuenta](./imagenes/creandocuentadafruit1.JPG)

- creamos cuenta con nuestro correo, debiera aparecer un ícono amarillo arriba a la derecha, con mis credenciales, no me aparece nada

- descargar los archivos .ino y .h que dejo aarón en mi respectivo grupo 08 en github

- lo hice mal al principio, me dio este error

![error](./imagenes/error1config.JPG)

- después me acordé que el archivo .h debía estar al lado del .ino en pestañas, es decir, tenían que estar en la misma carpeta lol. Esto lo aprendí el año pasado pero se me había olvidado, si no estaban de esta forma el arduino no iba a encontrar el .h por más que lo tuviera descargado

![solucion](./imagenes/solucionError.JPG)

- los puse en una misma carpeta, cerré arduino y lo abrí, ahora si me incluyó el .h

- antes de esto había abierto el .h en vscode y se veía así

![vscode](./imagenes/configReemplazar.JPG)

- después caché que se abría en arduino e hice lo que mencioné anteriormente, reemplacé los enunciados IO USERNAME y IO KEY por VALORES SECRETOS

- probé el código y compiló, no me apareció el error de conectando a Adafruit IOFirmware version 0.3.0 is outdated. Latest version is 0.5.2
21:24:06.104 -> Please upgrade the WiFiS3 firmware, CORREGIR QUE SÍ ME APARECIÓ ESTE ERROR PERO LO SOLUCIONAMOS CON AARÓN LA MAÑANA DEL 6 DE ABRIL, adjuntar pantallazo de monitor serial

- evidencia

![codigo](./imagenes/codigoCompila1.JPG)

- no sé si hice algo mal o no o quizá es porque el firmware de mi placa sí estaba actualizado

- hasta ahí llegué de momento, quería ver el tutorial oficial de la página que mandaron pero el link aparece malo

actualización 6 de abril en la mañana con aarón

- en la mañana aarón me dijo que revisara bien las credenciales porque vió mi clave y efectivamente no eran las credenciales exactas, la password era la que me da la página, no la que yo le asigno a mi cuenta

- por obvios motivos no colocaré mis credenciales lol

- al colocar correctamente las credenciales y el nombre y la clave del wifi

- también tuve que actualizar el firmware, ya que, al colocar las credenciales bien, el código funcionó entonces ahora daba el error de actualizar firmware, que era lo que precisamente tenía que suceder, actualizamos la placa y pasó esto:

![fallologro](./imagenes/falloylologro.JPG)

- el código se conectó y poco a poco comenzaría a enviar

![enviando](./imagenes/enviandoAdafruit.JPG)

- ahora sí comenzó a enviar, ahora debíamos abrir nuestra página para ver estos datos que se estaban enviando

![servidorAdafruit](./imagenes/servidorAdafruit.JPG)

![servidorAdafruit](./imagenes/servidorAdafruit2.JPG)

- esto muestra en vivo los datos que están llegando desde arduino hacia el servidor en adafruit, lo logramos amigos
