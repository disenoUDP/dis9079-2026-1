# sesion-13

lunes 08 junio 2026

# Trabajo en clases

Esta clase fue dedicada a trabajo en clases para la última entrega del curso, por lo que con mi grupo nos dedicamos a preparar el BOM (_bill of materials_) de nuestro trabajo, para poder comprar todos los componentes que necesitamos de manera inmediata. Luego de buscar los materiales, realizamos la compra y ahora solo nos falta esperar a que estos lleguen para ponerlos a prueba!! muchos de estos componentes no los hemos usado antes, por lo que estamos emocionados y un poco confundidos.

Aquí dejo el BOM (en realidad es el como va de momento):

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

---

## Pseudocódigos

Aparte de ver los materiales, se nos recomendó el hacer un pseudocódigo para luego partir con nuestro proyecto, así de esta manera podemos entender mejor el cómo funcionaría el código en si. Al seguir los ejemplos que nos mostró Aarón de pseudocódigos, terminamos con los siguientes resultados: 

### Pseudocódigo enviar 

RASPI
código enviar: 

Verificar si Wi Fi conectado
Verificar si API está funcionando
Verificar conexión con la nube

Nombre WIFI
Contraseña WIFI
User nube 
Contraseña nube
interruptor
LEDS

Al mover el interruptor de la izq a la derecha se encienden leds y empieza a enviar la información de la API al arduino a través de aio

Envía la información de la humedad de 8 ciudades de Chile

Arica
Copiapó
Santiago
Valparaíso
Isla de Pascua
Juan Fernández
Punta Arenas
Antártica

deja de enviar información al girar el interruptor de derecha a izq


### Pseudocódigo recibir

ARDUINO
código recibir:


Definir módulo led
Definir pantalla
Definir humidificador
Verificar si Wi Fi conectado
Verificar si API está funcionando
Verificar conexión con la nube

Definir componentes conectados al arduino

Recibir información de la humedad de las 8 ciudades
asignarle un valor y relacionarlo a un led del módulo

Con dado digital elegir al azar un valor y encender el led correspondiente de la ciudad
detectar el porcentaje de humedad del lugar y mostrarlo en pantalla 
se activa el humidificador

