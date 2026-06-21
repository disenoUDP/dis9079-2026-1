# sesion-13

lunes 08 junio 2026

La clase de hoy estuvimos trabajando en nuestros exámenes, de primeras estuvimos investigando sobre las piezas que había que comprar y ver bien las cosas que ya teníamos, pero para eso primero teníamos que aterrizar mejor el proyecto y editamos la descripción por la siguiente:

A través de nuestro proyecto queremos provocar una escena inmersiva entre el agua y el usuario, para esto vamos a reinterpretar el clima de 8 localidades distintas de Chile, con la intención de mostrar de forma literal y concentrada el índice de humedad de cada sector.

Mediante una ruleta que representa las 8 localidades con distintas luces LED, se sorteará de manera aleatoria un destino respaldado con datos ambientales provenientes de una API de Meteochile.gob.cl. y dependiendo del clima actual de dicho lugar, se activará una bruma a través de un humidificador.

Así que necesitábamos los materiales para una ruleta led para lo que decidimos comprar un Módulo RGB led de 8 bits 5050 8, un KIT Humidificador USB y aprovechamos de comprar cables DuPont.

(https://www.mechatronicstore.cl/modulo-rgb-led-de-8-bits-5050/) y (https://www.mechatronicstore.cl/kit-humidificador-usb/)


En tanto al proyecto hicimos algunos cambios y especificamos algunas cosas, tal como mencione en la descripción ahora se mostrara de forma aleatoria la humedad de 8 distintas localidades en chile que son:

- Arica
- Copiapó
- Santiago
- Valparaíso
- Isla de Pascua
- Juan Fernández
- Punta Arenas
- Antártica 

También sumamos una pantallita para visualizar el porcentaje de humedad del lugar en cuestión, y remplazamos el botón que haría girar la ruleta por una palanca que hace que visualmente gire la ruleta, pero realmente hace que la Raspberry mande datos y esos son los que después visualizamos en los LEDS.

Construimos también el pseudo código de envío de la Raspberry que vendría siendo el siguiente:

```

Verificar si Wi Fi conectado
Verificar si API está funcionando
Verificar conexión con la nube

Nombre WIFI
Contraseña WIFI
User nube 
Contraseña nube
interruptor
LEDS

Al mover el interruptor de la izquierda a la derecha se encienden LEDS y empieza a enviar la información de la API al Arduino a través de AdafruitIO

Envía la información de la humedad de 8 ciudades de Chile

Arica
Copiapó
Santiago
Valparaíso
Isla de Pascua
Juan Fernández
Punta Arenas
Antártica

Deja de enviar información al girar el interruptor de derecha a izquierda

```

Y este para recibir desde el Arduino


```
Definir módulo led
Definir pantalla
Definir humidificador
Verificar si Wi Fi conectado
Verificar si API está funcionando
Verificar conexión con la nube

Definir componentes conectados al Arduino


Recibir información de la humedad de las 8 ciudades
asignarle un valor y relacionarlo a un led del módulo

Con dado digital elegir al azar un valor y encender el led correspondiente de la ciudad
detectar el porcentaje de humedad del lugar y mostrarlo en pantalla 
se activa el humidificador 

```

| Componente | Valor Unidad | Cantidad | Link |
| --- | --- | --- | --- |
| Raspberry Pi Pico 2 W | $14.990 | 1 | <https://raspberrypi.cl/products/raspberry-pi-pico-2-w-con-headers> |
| Arduino UNO R4 WiFi | $38.990 | 1 | <https://arduino.cl/producto/arduino-uno-r4-wifi/?srsltid=AfmBOopyyargcSiTQeFlT3cTN5ide380bxZlQXRZVP4u_op0O-qJcENB> |
| KIT Humidificador USB | $8.490 | 1 | <https://www.mechatronicstore.cl/kit-humidificador-usb/?srsltid=AfmBOorNqdrjHbLaQqIg_9T7v2PwFpot8zKqXUEbviGQ94X7oUZElWh9> |
| Protoboard 400 puntos | $2.425 | 1 | <https://altronics.cl/protoboard-400ptos> |
| Pack 40 cables dupont | $2.735 | 1 | <https://altronics.cl/jumper-dupont-20cm-mm?search=cables%20dupont> |
| Módulo RGB led de 8 bits 5050 | $1.990 | 1 | <https://www.mechatronicstore.cl/modulo-rgb-led-de-8-bits-5050/> |
| Interruptor Switch 2 Pines ON-OFF Corto | $570 | 1 | <https://www.katode.cl/switches/1339-interruptor-switch-2-pines-on-off-corto.html> |
| Módulo LCD 1602 con interfaz I2C | $4.490 | 1 | <https://www.katode.cl/arduino/477-modulo-lcd-1602-con-interfaz-i2c.html> |



Aún nos falta más por hacer, las cosas que pedimos deberían de llegar el viernes y el fin de semana nos juntaremos a seguir trabajando en esto.
