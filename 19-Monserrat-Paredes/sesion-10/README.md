# sesion-10

lunes 18 mayo 2026

solemne 2

## Apuntes en clases

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

TU_NOMBRE_WIFI / TU_CLAVE_WIFI

TU_USUARIO_ADAFRUIT / TU_AIO_KEY

En el .ino, también reemplaza TU_USUARIO_ADAFRUIT en la línea del feed

Crear el feed llamado estado en tu cuenta de Adafruit IO antes de ejecutar


Después decidimos cambiarlo 


## Investigación

Lo que queremos realizar en la solemne 2 es que desde la Raspberry pi envíe datos mediante un potenciómetro hacía el Arduino y que este encienda una luz y mueva un servomotor. Los datos enviados se verán reflejados en el feed de Adafruit.

|Raspberry Pi Pico 2 W|Adafruit IO|Arduino UNO R4 wifi|
|---|---|---|
|Potenciómetro|MQTT|Led + servomotor|
|ángulo|Feed: estado|enciende led y mueve servo|

1. Girar el potenciómetro en la Raspberry -> va cambiandi el ángulo
2. La Raspberry publica e ángulo en el feed de Adafruit IO
3. El Arduino recibe el mensaje y mueve el servomotor. Al llegar a cierto ángulo se enciende el LED


### Raspberry Pi Pico 2 W

La placa **Raspberry Pi Pico 2 W** será la encargada de capturar los datos generados por un potenciómetro B500K conectado a una de sus entradas analógicas.

A medida que el usuario gira el potenciómetro, se producen variaciones de resistencia que la Raspberry interpreta como distintos valores analógicos. Estos valores son convertidos a datos digitales y posteriormente enviados de manera inalámbrica mediante conexión WiFi hacia la plataforma **Adafruit IO**, utilizando el protocolo de comunicación MQTT.

El propósito de esta etapa es transmitir y visualizar en tiempo real los cambios del potenciómetro dentro del feed denominado *“moluscos”*, permitiendo monitorear el comportamiento del sensor de forma remota a través de internet. Además, esta comunicación servirá como puente para controlar otros dispositivos conectados al sistema.


---

### Adafruit IO

La plataforma **Adafruit IO** funcionará como intermediario de comunicación entre ambas placas del proyecto.

Los datos enviados desde la Raspberry Pi Pico 2 W serán publicados continuamente en el feed *“moluscos”*, donde quedarán almacenados y disponibles en tiempo real. Posteriormente, estos valores podrán ser leídos y procesados por el Arduino UNO R4 WiFi para ejecutar distintas acciones físicas dentro del sistema.

Gracias a esta plataforma, es posible establecer una comunicación remota entre dispositivos IoT, facilitando la transmisión y sincronización de datos desde cualquier red con acceso a internet.


---

### Arduino IDE y Arduino UNO R4 WiFi

El **Arduino UNO R4 WiFi** será programado mediante el software **Arduino IDE** y se conectará a Adafruit IO para recibir los datos publicados en el feed *“moluscos”*.

Una vez recibidos los valores provenientes del potenciómetro, el Arduino interpretará esta información para controlar el movimiento de un servomotor SG90. Dependiendo de los datos enviados por la Raspberry Pi Pico 2 W, el servomotor ajustará su ángulo de posición de manera dinámica.

Además, cuando el servo alcance un ángulo específico previamente definido dentro del código, el sistema activará un LED amarillo como indicador visual, señalando que se alcanzó la posición programada. Esto permitirá generar una respuesta física inmediata a partir de los datos transmitidos por internet.

---

### Importante

Antes de cargar el código en las placas, es necesario reemplazar correctamente los siguientes datos de configuración:

* `TU_NOMBRE_WIFI`
* `TU_CLAVE_WIFI`
* `TU_USUARIO_ADAFRUIT`
* `TU_AIO_KEY`

Además, dentro del archivo `.ino`, se debe reemplazar el texto `TU_USUARIO_ADAFRUIT` en la línea correspondiente al feed para asegurar la correcta conexión con la cuenta de Adafruit IO.



## Investigación del sensor: Potenciómetro B500K


### ¿Qué es un potenciómetro?

<img width="414" height="434" alt="sensorPotenciómetro" src="https://github.com/user-attachments/assets/c62d049b-a491-4db0-8a17-3d5d3ed09a3b" />


El potenciómetro es un componente electrónico utilizado para variar manualmente la resistencia dentro de un circuito. Funciona como un resistor variable que permite modificar valores eléctricos, principalmente voltaje o corriente, dependiendo de la posición de su perilla o eje giratorio.

El modelo B500K posee una resistencia máxima de 500 kilo-ohmios y una curva lineal (“B”), lo que significa que el cambio de resistencia ocurre de manera proporcional al movimiento realizado por el usuario.

El potenciómetro es ampliamente utilizado en proyectos interactivos, diseño de interfaces físicas, instrumentos musicales, sistemas de control y proyectos de arte electrónico, ya que permite traducir movimientos humanos en datos digitales fáciles de interpretar por microcontroladores como Arduino o Raspberry Pi.


---

### Funcionamiento del sensor

El potenciómetro posee tres terminales:

- Un terminal conectado a voltaje (VCC).
  
- Un terminal conectado a tierra (GND).

- Un terminal central que entrega el valor variable.

Cuando el usuario gira la perilla, cambia la resistencia interna del componente, generando distintos niveles de voltaje en la salida analógica. Estos cambios son leídos por una entrada analógica del microcontrolador y convertidos en valores digitales.

Por ejemplo:

Giro mínimo → valor cercano a 0.
Giro medio → valor intermedio.
Giro máximo → valor cercano al máximo permitido por la placa.


Esto permite utilizar el potenciómetro como interfaz de control para modificar parámetros como:

- Intensidad lumínica.

- Velocidad de motores.

- Volumen.

- Posición de servos.

- Variables visuales o sonoras.

---

### Filtrado de información

Uno de los aprendizajes importantes al trabajar con sensores analógicos es el filtrado de datos.

Aunque el potenciómetro entrega valores relativamente estables, pueden aparecer pequeñas fluctuaciones debido a:

- Ruido eléctrico.

- Variaciones de alimentación.

- Movimiento inestable del usuario.

- Sensibilidad de lectura analógica.


Para evitar lecturas erráticas, es común aplicar técnicas de filtrado, como:


Promedio de lecturas:

Consiste en tomar varias muestras consecutivas y calcular un promedio para suavizar las variaciones.

Rango mínimo de cambio:

Permite ignorar pequeños cambios irrelevantes entre lecturas.

Delay o tiempo de estabilización:

Reduce la velocidad de actualización para evitar lecturas excesivamente sensibles.

Estas técnicas ayudan a obtener datos más estables y confiables, especialmente en proyectos interactivos o visualizaciones en tiempo real.

---

### Visualización de datos

Los datos del potenciómetro pueden visualizarse de distintas maneras:

- Monitor Serial de Arduino IDE.
  
- Plataformas IoT como Adafruit IO.

- Gráficos en tiempo real.

- Interfaces audiovisuales en TouchDesigner.

- Sistemas interactivos de iluminación o sonido.


La visualización de datos permite observar cómo las acciones físicas del usuario afectan el sistema en tiempo real, facilitando el análisis, la interacción y el entendimiento del comportamiento del sensor.

En proyectos de diseño interactivo, el potenciómetro suele utilizarse como una interfaz tangible que conecta el movimiento físico con respuestas digitales.

---

### Problemas comunes

Lecturas inestables: 

Pueden producirse por conexiones deficientes o ruido eléctrico.

Saltos bruscos en los valores:

Suceden cuando el potenciómetro está desgastado o tiene suciedad interna.

Mala conexión de tierra (GND):

Puede provocar datos incorrectos o fluctuaciones extremas.

Rango de lectura incorrecto:

Ocurre cuando la alimentación o la programación no coinciden con las capacidades del microcontrolador.

Desgaste mecánico:

El uso constante puede deteriorar la pista resistiva interna del potenciómetro.

---

### Proyecto o referente artístico (sensor y robótica musical)

Erin Gee “Swarming Emotional Pianos”

Nacida en 1983, es una artista y compositora canadiense cuyo trabajo se centra en la voz, la emoción y la tecnología. Desarrolla instrumentos de biorretroalimentación personalizados que conectan el cuerpo humano con el sonido y los sistemas interactivos. Al crear estos sistemas, considera la manipulación emocional como una capa técnica que complementa el hardware y el software, vinculándola con la teoría feminista.

trabaja mezclando:

- biometría.
  
- sensores corporales.

- robótica sonora.
  
- emociones humanas.

- sistemas interactivos.

Sobre el proyecto: Swarming Emotional Pianos

Una imponente proyección de un artista humano rodeado de seis robots musicales con campanillas: su música está impulsada por los ritmos cambiantes del cuerpo emocional del artista, transformados en datos y señales que activan los motores del conjunto.

Instalación robótica que presenta la documentación de una actuación de una actriz que experimenta emociones extremas en intervalos de cinco minutos. Durante estas actuaciones cronometradas de sorpresa, ira, miedo, tristeza, excitación sexual y alegría extremas, Gee utilizó biosensores diseñados a medida para capturar cómo cada emoción afecta el ritmo cardíaco, la sudoración y la respiración de la actriz. Los datos de esta sesión impulsan las explosiones musicales de la robótica que rodea la documentación en video de la sesión emocional.


Tecnologías utilizadas:
- Arduino.
- biosensores.
- servomotores.
- microcontroladores.
- sistemas de sonido robótico.
  
Es interesante, ya que trabaja directamente con emociones humanas convertidas en comportamiento robótico, eso genera una experiencia mucho más sensible y perturbadora.


Imagenes de proyecto

<img width="1058" height="697" alt="Erin Gee01" src="https://github.com/user-attachments/assets/6a9c5427-fe75-4f54-91b4-936e655f0ad6" />


<img width="898" height="550" alt="Erin Gee02" src="https://github.com/user-attachments/assets/3ad32ca8-4457-4766-9f4a-6b5eabac43e0" />


---


## Investigación Actuador: Servomotor SG90


<img width="657" height="473" alt="actuadorServomotor" src="https://github.com/user-attachments/assets/e1c20bee-a216-41b8-b5b7-c23dd17c73b0" />


### ¿Qué es un actuador?

Un actuador es un componente capaz de transformar energía eléctrica en movimiento físico o acciones mecánicas.

A diferencia de los sensores, que capturan información del entorno, los actuadores responden a datos o instrucciones generando una acción concreta.

Dentro de los actuadores más utilizados en proyectos interactivos se encuentran:

- Motores DC.
  
- Servomotores.

- LEDs.

- Relés.

- Buzzers.

- Solenoides.

---

### ¿Qué es el servomotor SG90?

El SG90 Micro Servo es un micro servomotor utilizado para controlar posiciones angulares con precisión.

Puede girar normalmente entre 0° y 180°, dependiendo de la señal enviada desde un microcontrolador.


---


### Es ampliamente utilizado en:

- Robótica.

- Automatización.

- Instalaciones interactivas.

- Proyectos de diseño físico.

- Sistemas cinéticos.

- Funcionamiento del servomotor

---

### El servo posee tres conexiones:

- Alimentación (5V).
- Tierra (GND).
- Señal PWM.

El microcontrolador envía pulsos PWM (modulación por ancho de pulso), y el servo interpreta estos pulsos como posiciones angulares específicas.


Por ejemplo:

0° → posición inicial.
90° → posición media.
180° → posición máxima.

Esto permite controlar movimientos precisos de manera simple y eficiente.

---

### Filtrado y control de movimiento

Al trabajar con actuadores, también es importante controlar la estabilidad de los datos recibidos.

Si el sensor entrega información muy variable, el servo puede:

- Vibrar constantemente.

- Moverse de forma brusca.

- Generar ruido mecánico.

- Sobrecalentarse.


Para evitar esto, se utilizan estrategias como:

Suavizado de movimiento:

Realizar transiciones graduales entre posiciones.

Limitación de rango:

Evitar movimientos extremos innecesarios.

Filtrado de datos del sensor:

Reducir fluctuaciones antes de enviar información al servo.

Tiempo de actualización controlado:

Evita movimientos excesivamente rápidos.

---

### Visualización de datos y comportamiento

El movimiento del servo puede utilizarse como una forma física de visualización de datos.

Por ejemplo:

- Representar intensidad sonora.

- Mostrar variaciones lumínicas.

- Indicar proximidad.

- Traducir información digital en movimiento tangible.

Esto convierte al servomotor en un elemento importante dentro de proyectos interactivos y experiencias físicas de datos.

---

### Problemas comunes

Vibración constante:

Generalmente causada por ruido en la señal o alimentación insuficiente.

Falta de fuerza:

Ocurre cuando el servo intenta mover demasiado peso.

Reinicios del microcontrolador:

Suceden cuando el servo consume más corriente de la disponible.

Movimiento impreciso:

Puede deberse a errores en la señal PWM o interferencias eléctricas.

Sobrecalentamiento:

Provocado por movimientos forzados o uso continuo.

---

### Proyecto o referente artístico (actuador)

Moritz Simon Geist “Vibrations”

Moritz Simon Geist es un artista visual, investigador y productor musical cuyo trabajo se centra en la intersección de la robótica, el sonido físico y la agencia algorítmica. Su práctica explora la transición de instrumentos mecánicos funcionales a entidades autónomas, examinando la materialidad y las condiciones psicológicas y estéticas de la interacción humano-máquina.

Con una sólida formación en física de semiconductores y robótica, Geist deconstruye sistemas técnicos complejos para investigar la fragilidad de los materiales y el comportamiento algorítmico. Su evolución artística ha pasado de instalaciones cinéticas performativas a esculturas autónomas a gran escala que utilizan inteligencia artificial y visión artificial para interactuar con su entorno.



