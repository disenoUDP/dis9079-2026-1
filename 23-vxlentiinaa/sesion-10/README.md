# sesion-10

lunes 18 mayo 2026

solemne 2

---

- Sensores: Dispositivo diseñado para detectar cambios en el entorno
- Actuadores: Dispositivo que recibe una orden o señal

Lo que queremos realizar en la solemne 2 es que desde la Raspberry pi envíe datos mediante un botón on/off hacía el Arduino y que este encienda una luz o emita algún sonido.

Entonces, nuestro pseudocódigo sería:

|Raspberry Pi Pico 2 W|Adafruit IO|Arduino UNO R4 wifi|
|---|---|---|
|Botón|MQTT|Led|
|ON/OFF|Feed: estado|Verde/Rojo|

1. Presionas el botón en la Raspberry > alterna entre ON y OFF
2. La Raspberry publica "ON" o "OFF" en el feed de Adafruit IO
3. El Arduino recibe el mensaje y enciende el LED correspondiente


### Raspberry Pi Pico 2W

- Cada vez que presionas el botón, alterna entre ON y OFF (no es necesario mantenerlo)
- El LED integrado de la placa te muestra el estado actual (encendido = ON, apagado = OFF)
- Publica el texto "ON" o "OFF" en el feed estado de Adafruit IO

### Arduino UNO R4 WiFi

- Recibe "ON" → enciende LED verde (D2), apaga el rojo
- Recibe "OFF" → enciende LED rojo (D3), apaga el verde
- Al arrancar, ambos LEDs parpadean 3 veces para confirmar que la conexión fue exitosa

`Recordar!!`

1. TU_NOMBRE_WIFI / TU_CLAVE_WIFI
2. TU_USUARIO_ADAFRUIT / TU_AIO_KEY
3. En el .ino, también reemplaza TU_USUARIO_ADAFRUIT en la línea del feed
4. Crear el feed llamado estado en tu cuenta de Adafruit IO antes de ejecutar

LO CAMBIAMOS!!

ahora si el oficial ↓

## Investigación

Lo que queremos realizar en la solemne 2 es que desde la Raspberry pi envíe datos mediante un potenciómetro hacía el Arduino y que este encienda una luz y mueva un servomotor. Los datos enviados se verán reflejados en el feed de Adafruit.

---

Entonces, nuestro pseudocódigo sería:

|Raspberry Pi Pico 2 W|Adafruit IO|Arduino UNO R4 wifi|
|---|---|---|
|Potenciómetro|MQTT|Led + servomotor|
|ángulo|Feed: estado|enciende led y mueve servo|

1. Giras el potenciómetro en la Raspberry > va cambiando el ángulo
2. La Raspberry publica el ángulo en el feed de Adafruit IO
3. El Arduino recibe el mensaje y mueve el servomotor, cuando llegue a cierto ángulo se prende la luz led

### Raspberry Pi Pico 2W

La Raspberry Pi Pico 2 W será utilizada para leer los datos provenientes de un potenciómetro B500K conectado a una entrada analógica.

A medida que el usuario gira el potenciómetro, la Pico interpreta las variaciones de resistencia como valores digitales. Posteriormente, estos datos serán enviados mediante conexión WiFi hacia la plataforma Adafruit IO utilizando protocolo MQTT.

El objetivo de esta etapa es visualizar en tiempo real los cambios del potenciómetro dentro del feed llamado “moluscos”, permitiendo monitorear el comportamiento del sensor desde internet.

### Adafruit IO

La plataforma Adafruit IO funcionará como intermediario de comunicación entre ambas placas.

Los datos enviados desde la Raspberry Pi Pico 2 W serán publicados en el feed “moluscos”, quedando disponibles en tiempo real para ser leídos posteriormente por el Arduino UNO R4 WiFi.

### Arduino IDE

El Arduino UNO R4 WiFi se conectará a Adafruit IO para recibir los datos publicados en el feed “moluscos”.

Una vez recibidos los valores del potenciómetro, el Arduino interpretará esta información para controlar el movimiento de un servomotor SG90. Dependiendo de los datos enviados, el servomotor modificará su ángulo de posición.

Cuando el servo alcance un ángulo previamente definido dentro del código, el Arduino activará un LED amarillo como indicador del ángulo alcanzado.

`Recordar!!`

1. TU_NOMBRE_WIFI / TU_CLAVE_WIFI
2. TU_USUARIO_ADAFRUIT / TU_AIO_KEY
3. En el .ino, también reemplaza TU_USUARIO_ADAFRUIT en la línea del feed

### Investigación del sensor: Potenciómetro B500K

`¿Qué es un potenciómetro?`

Un potenciómetro es un dispositivo electrónico. Se puede usar como resistencia o resistor variable mecánica (con cursor y de al menos tres terminales). El usuario al manipularlo, obtiene entre el terminal central (cursor) y uno de los extremos una fracción de la diferencia de potencial total, se comporta como un divisor de tensión o divisor de voltaje.

<img src="./imagenes/circuitPython.png" alt="tinkercad" width="400">

`Tipos de resistencia de variación mecánica para su uso como potenciómetros:`

Impresas, realizadas con una pista de carbón o de cermet sobre un soporte duro como papel baquelizado (cartón prespan), fibra de vidrio, baquelita, etcétera. La pista tiene sendos contactos en sus extremos y un cursor conectado a un patín que se desliza por la pista resistiva.
Bobinadas, consistentes en un arrollamiento toroidal de un hilo resistivo (por ejemplo, constantán) con un cursor que mueve un patín sobre el mismo.
Potencia: al igual que las resistencias, los potenciómetros soportarán distintas potencias, por lo general a partir de 1 W. Al reverso especifica la potencia en W. Los potenciómetros de mucha potencia reciben el nombre de reóstatos, que ya se utilizan muy poco.


- El potenciómetro es un sensor analógico de resistencia variable que permite modificar manualmente el voltaje dentro de un circuito electrónico. Al girar su eje, cambia la resistencia eléctrica y el microcontrolador puede interpretar distintos valores numéricos.
- En proyectos interactivos, los potenciómetros son ampliamente utilizados para controlar intensidad, posición, velocidad o sensibilidad de sistemas físicos y digitales.

`Funcionamiento dentro del proyecto`

1. En este proyecto, el potenciómetro B500K se conecta a la Raspberry Pi Pico 2 W mediante una entrada analógica ADC.
2. El sensor entrega valores variables dependiendo de la posición física del giro. La Raspberry pi convierte estos datos analógicos en datos digitales y posteriormente los envía mediante wifi al feed “moluscos” en Adafruit IO.
3. Estos datos son utilizados para controlar el movimiento del servomotor y el comportamiento visual del robot LUMI.

Filtrado de información

Uno de los principales problemas de los sensores analógicos es la inestabilidad de lectura causada por pequeñas variaciones eléctricas o físicas.

Para evitar movimientos bruscos del servo, se realizó:

Mapeo de valores analógicos.
Reducción del rango de lectura.
Envío de datos cada cierto tiempo.
Suavizado básico mediante promedios simples.

El filtrado permite obtener una experiencia más estable y controlada en la interacción física.

Visualización de datos

Los datos del potenciómetro fueron visualizados utilizando Adafruit IO, una plataforma IoT que permite monitorear información en tiempo real mediante dashboards y feeds.

La visualización permitió observar cómo cambiaban los valores enviados por el sensor dependiendo de la interacción física del usuario.

Problemas comunes
Ruido en la señal

Los potenciómetros pueden generar fluctuaciones pequeñas en los datos debido al desgaste físico o ruido eléctrico.

Saltos de lectura

En algunos casos aparecen cambios bruscos entre valores consecutivos.

Desgaste mecánico

Con el uso continuo, el contacto interno del potenciómetro puede deteriorarse.

Lecturas inestables

Las malas conexiones o cables largos pueden alterar los valores enviados al microcontrolador.

Artista / proyecto / empresa relacionada
Adafruit Industries

Adafruit Industries es una empresa enfocada en hardware open source, electrónica creativa e Internet of Things.

Sus proyectos educativos exploran constantemente el uso de sensores analógicos para visualización de datos interactivos, sistemas físicos y experiencias digitales. La plataforma Adafruit IO es ampliamente utilizada en proyectos de arte interactivo, educación y prototipado electrónico.

individual - INVESTIGACIÓN ACTUADOR
Investigación del actuador: Servomotor SG90
¿Qué es un actuador?

Un actuador es un componente capaz de transformar energía eléctrica en movimiento físico. Dentro de sistemas interactivos, los actuadores permiten que los datos digitales produzcan respuestas visibles o mecánicas en el mundo real.

¿Qué es el servomotor SG90?

El SG90 es un micro servomotor controlado mediante señales PWM. Permite mover su eje hacia posiciones angulares específicas, generalmente entre 0° y 180°.

Es uno de los actuadores más utilizados en proyectos de robótica, diseño interactivo y prototipado debido a:

Bajo costo.
Tamaño compacto.
Fácil programación.
Compatibilidad con Arduino y Raspberry Pi.
Funcionamiento dentro del proyecto

En este proyecto, el Arduino recibe los datos enviados desde Adafruit IO y los utiliza para controlar el ángulo del servomotor SG90.

El servo mueve el corazón giratorio del robot LUMI dependiendo de la posición del potenciómetro. Además, cuando alcanza cierto ángulo, se activa un LED amarillo como respuesta visual.

Filtrado y control de movimiento

Para evitar movimientos erráticos del servomotor se realizaron:

Límites máximos y mínimos de ángulo.
Mapeo de datos.
Actualización progresiva del movimiento.
Control de velocidad mediante retardos.

Esto permitió que el movimiento del corazón de LUMI fuera más fluido y expresivo.

Problemas comunes
Vibración del servo

Los SG90 pueden presentar pequeños movimientos involuntarios debido al ruido eléctrico o señales inestables.

Problemas de alimentación

El consumo de corriente del servo puede provocar reinicios del Arduino si no existe suficiente energía disponible.

Límites mecánicos

El servo no siempre alcanza exactamente los 180° reales.

Sobrecalentamiento

Un uso continuo o forzado puede generar temperatura excesiva en el motor.

Visualización de datos y movimiento

La relación entre visualización digital y movimiento físico fue central en el proyecto.

Los datos enviados por el sensor se transforman en movimiento mecánico dentro de LUMI, permitiendo visualizar información invisible mediante interacción cinética y luz.

Proyecto / obra relacionada
Proyectos interactivos con Arduino y servomotores

Muchos proyectos de arte interactivo utilizan servomotores para traducir datos en movimiento físico. Un ejemplo común son instalaciones robóticas que reaccionan a sensores de movimiento, sonido o internet.

En comunidades de electrónica y robótica, los SG90 son ampliamente utilizados en proyectos experimentales de interacción física y diseño de comportamiento cinético.
