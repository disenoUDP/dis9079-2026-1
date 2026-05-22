# sesion-10

lunes 18 mayo 2026

solemne 2

## Investigación

- Sensores: Dispositivo diseñado para detectar cambios en el entorno.
- Actuadores: Dispositivo que recibe una orden o señal.

Lo que queremos realizar en la solemne 2 es que desde la Raspberry pi envíe datos de un botón on/off  hacia el Arduino
y que este encienda una luz o emita algún sonido.

### Pseudocódigo
|Raspberry Pi Pico 2 W|Adafruit IO|Arduino UNO R4 wifi|
|--|--|--|
|Botón|MQTT|LED|
|ON/OFF|feed:estado|verde/rojo|

1. Presionar elbotón en la raspberry > alterna entre ON y OFF
2. La Raspberry publica "ON" "OFF" en el feed de Adafruit IO
3. El Arduino recibe el mensaje y enciende el LED correspondiente

#### Raspberry Pi Pico 2W

- Cada vez que presionas el botón, alterna entre ON y OFF (no es necesario mantenerlo)
- El LED integrado de la placa te muestra el estado actual (encendido=ON, apagado=OFF)
- Publica el texto "ON" u "OFF" en el feed estado de Adafruit IO
  
#### Arduino UNO R4 Wifi

- Recibe "ON" -> Enciende LED verde (D2), apaga el rojo
- Recibe "OFF" -> enciende LED rojo (D3), apaga el verde
- Al arrancar, ambos  LEDS parpadean 3 veces para confirmar que la conexión fue exitosa
  
#### Arduino UNO R4 Wifi

- Recibe "ON" -> Enciende LED verde (D2), apaga rojo
- Recibe "OFF" -> enciende LED rojo (D3), apaga verde
- Al arrancar, ambos LEDS parpadean 3 veces para confirmar que l aconexión fue existosa

NO OLVIDAR!

1. TU_NOMBRE_WIFI / TU_CLAVE_WIFI
2. TU_USUARIO_ADAFRUIT / TU_AIO_KEY
3. En el .ino, también reemplaza TU_USUARIO_ADAFRUIT en la línea del feed
4. Crear el feed llamado estado en tu cuenta de Adafruit IO antes de ejecutar

Después de hablar como grupo, decidimos cambiarlo 

## Investigación 2

Lo que queremos realizar en la solemne 2 es que desde la Raspberry pi envíe datos mediante un potenciómetro hacía el Arduino y que este encienda una luz y mueva un servomotor. Los datos enviados se verán reflejados en el feed de Adafruit.

|Raspberry Pi Pico 2 W|Adafruit IO|Arduino UNO R4 wifi|
|---|---|---|
|Potenciómetro|MQTT|Led + servomotor|
|ángulo|Feed: estado|enciende led y mueve servo|

1. Girar el potenciómetro en la Raspberry -> va cambiandi el ángulo
2. La Raspberry publica e ángulo en el feed de Adafruit IO
3. El Arduino recibe el mensaje y mueve el servomotor. Al llegar a cierto ángulo se enciende el LED

### Raspberry Pi Pico 2W

- La Raspberry Pi  Pico 2W será utilizada para leer los datos del potenciómetro B500k conectandose a una entrada analógica.
- A medida de se gire el potenciómetro, esta interpreta las variaciones de recistencia como valores digitales. Estos datos  serán enviados mediante conexión Wifi hacia la plataforma Adafruit IO con el protocolo MQTT.
- El objetivo es visualizar en tiempo real los cambios del potenciómetro dentro del feed llamado "moluscos", permitiendo monitorear el comportamiento del sensor desde internet.

### Adafruit IO 

- Funcionará como intermediario de comunicación entre ambas placas.
- Los datos enviados desde la Raspberry Pi Pico 2 W serán publicados en el feed “moluscos”, quedando disponibles en tiempo real para ser leídos posteriormente por el Arduino UNO R4 WiFi.

### Arduino IDE 

- Arduino UNO R4 WiFi se conectará a Adafruit IO para recibir los datos publicados en el feed “moluscos”.
- Una vez recibidos los valores del potenciómetro, el Arduino interpretará la información para controlar el movimiento de un servomotor SG90. Dependiendo de los datos enviados, el servomotor modificará su ángulo de posición.
- Cuando el servo alcance un ángulo previamente definido dentro del código, el Arduino activará un LED amarillo como indicador del ángulo alcanzado.

NO OLVIDAR!

1. TU_NOMBRE_WIFI / TU_CLAVE_WIFI
2. TU_USUARIO_ADAFRUIT / TU_AIO_KEY
3. En el .ino, también reemplaza TU_USUARIO_ADAFRUIT en la línea del feed

### Investigación del sensor: Potenciómetro B500K

Es un componente electrónico pasivo compuesto por una resistencia de valor fijo y un contacto móvil. Al mover la perilla, modificamos la longitud de la pista resistiva por la que pasa la corriente, lo que nos permite variar mecánicamente la cantidad de resistencia en un circuito.

Tipos de resistencia de variación mecánica para su uso como potenciómetros:

- Impresas: hechas con una pista de carbón o cermet sobre una base rígida (baquelita, fibra de vidrio). Tienen contactos en los extremos y un cursor con un patín que se desliza por la pista.
- Bobinadas: formadas por un hilo resistivo enrollado en anillo, sobre el cual se mueve un cursor con un patín.
- Potencia: soportan distintos vatios, generalmente a partir de 1 W (indicado al reverso). Los de gran potencia se llaman reóstatos.

Como sensor de posición rotacional o lineal, su funcionamiento se basa en el principio de un divisor de voltaje, actuando como un transductor que transforma de manera directa un movimiento mecánico en una señal eléctrica analógica. Al alimentar los extremos de su pista con un voltaje fijo, el pin central entrega una tensión de salida que varía de forma continua y proporcional a la ubicación física del eje.


