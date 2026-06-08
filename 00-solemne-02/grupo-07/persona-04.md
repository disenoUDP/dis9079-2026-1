# investigaciones individuales

Antonia Fuentealba / [AntFuentealba](https://github.com/AntFuentealba)

## Sensor

### ¿Qué es un sensor PIR?

El sensor PIR (Passive Infrared Sensor) es un sensor electrónico diseñado para detectar movimiento mediante cambios en la radiación infrarroja emitida por cuerpos calientes, especialmente personas y animales. Se llama “pasivo” porque no emite energía propia, sino que solamente detecta la radiación infrarroja presente en el entorno.

En el proyecto desarrollado, el sensor PIR funciona como el elemento de entrada del sistema. Cuando detecta movimiento, la Raspberry Pi Pico 2 W envía la información hacia Adafruit IO, iniciando la comunicación inalámbrica con el Arduino Uno R4 WiFi.

### Conexiones del sensor PIR

El sensor PIR HC-SR501 posee tres pines principales que permiten su funcionamiento junto a la Raspberry Pi Pico 2 W:

#### VCC
Corresponde a la alimentación del módulo.

- Se conecta al pin de 5V o 3.3V de la Raspberry Pi Pico 2 W.
- Permite energizar el sensor para que pueda detectar movimiento.

#### GND
Es la conexión a tierra del circuito.

- Se conecta al pin GND de la Raspberry Pi Pico 2 W.
- Completa el circuito eléctrico y estabiliza la alimentación.

#### OUT
Es la salida digital del sensor.

- Se conecta a un pin GPIO de entrada de la Raspberry Pi Pico 2 W.
- Envía un valor:
   - HIGH (1) cuando detecta movimiento.
   - LOW (0) cuando no detecta movimiento.

#### Conexión del botón
El botón utilizado para habilitar el funcionamiento del sensor también posee conexiones simples:

- Un terminal del botón se conecta a un pin GPIO de la Raspberry Pi Pico 2 W.
- El otro terminal se conecta a GND.
- Mediante programación se utiliza una resistencia pull-up interna para detectar cuándo el botón es presionado.

Cuando el usuario presiona el botón:

1. La Raspberry habilita la lectura del sensor PIR.
2. El sensor comienza a detectar movimiento.
3. Si detecta presencia, se envía información a Adafruit IO.
4. El Arduino Uno R4 WiFi recibe los datos.
5. La pantalla OLED reproduce la animación pixel art.

### Funcionamiento 

El sensor PIR detecta variaciones de radiación infrarroja utilizando dos sensores internos de material piroeléctrico. Cuando un objeto caliente, como una persona, se mueve frente al sensor, cambia la cantidad de radiación infrarroja que recibe cada lado del detector. Esa diferencia genera una señal eléctrica que el microcontrolador interpreta como movimiento.

El módulo más utilizado es el HC-SR501, que incluye:

- Sensor piroeléctrico
- Lente Fresnel para ampliar el rango de detección
- Potenciómetros para ajustar sensibilidad y tiempo
- Salida digital HIGH/LOW

#### Estados del sensor

- HIGH (1): se detecta movimiento
- LOW (0): no se detecta movimiento


### Uso del sensor en el proyecto

En este proyecto, el sensor PIR se encuentra conectado a una Raspberry Pi Pico 2 W. Su activación está controlada mediante un botón para evitar enviar información constantemente a Adafruit IO y saturar el canal de comunicación.

La lógica implementada fue:

1. El usuario presiona un botón para habilitar el sensor.
2. El sensor PIR comienza a detectar movimiento.
3. Si detecta movimiento, la Pico 2 W envía un valor a Adafruit IO.
4. El Arduino Uno R4 WiFi recibe la información.
5. La pantalla OLED reproduce una animación pixel art del alien caminando.

Este sistema transforma un evento físico (movimiento) en una respuesta visual interactiva.

### Filtrado de información

Uno de los principales desafíos del proyecto fue evitar el envío excesivo de datos a Adafruit IO.

Para solucionar esto se aplicaron distintas técnicas de filtrado:

1. Activación mediante botón

El sensor solo funciona mientras el botón está presionado. Esto reduce considerablemente la cantidad de datos enviados.

2. Delay entre envíos

Se utilizó un tiempo de espera entre lecturas para evitar múltiples envíos consecutivos por una sola detección.

Ejemplo:
- Esperar 1 o 2 segundos antes de volver a enviar información.

3. Cambio de estado

La información se envía solamente cuando ocurre un cambio:
- De “sin movimiento” a “movimiento detectado”.

Esto evita enviar continuamente el mismo valor.

4. Filtrado de falsas detecciones

Los sensores PIR pueden activarse por:
- cambios bruscos de temperatura,
- luz solar directa,
- corrientes de aire caliente.

Por eso es importante:
- calibrar sensibilidad,
- ubicar correctamente el sensor,
- evitar fuentes térmicas cercanas.

### Visualización de datos

La información enviada desde el sensor se transforma en una visualización gráfica mediante una pantalla OLED conectada al Arduino Uno R4 WiFi.

Cuando el Arduino recibe el valor desde Adafruit IO:
- activa la animación del alien,
- muestra los frames en secuencia,
- genera la ilusión de movimiento tipo GIF.

La visualización cumple una función importante:
- convierte datos invisibles en una representación entendible,
- mejora la interacción entre usuario y sistema,
- permite verificar visualmente que la comunicación inalámbrica funciona correctamente.


### Problemas comunes 

#### Falsas detecciones

El sensor puede activarse aunque no haya personas presentes.

Causas:
- calor ambiental,
- luz solar,
- objetos calientes,
- ventiladores.

#### Tiempo de calibración

Muchos sensores PIR necesitan entre 30 y 60 segundos para estabilizarse al encenderse.

#### Sensibilidad excesiva

Si está mal configurado, puede detectar movimiento demasiado lejos o constantemente.

#### Retardo entre lecturas

El sensor puede mantener la salida en HIGH durante algunos segundos después de detectar movimiento.

#### Ruido eléctrico

Cables largos o mala alimentación pueden producir señales erráticas.

### Aplicaciones reales del sensor PIR

Los sensores PIR son ampliamente utilizados en:

- Alarmas de seguridad
- Luces automáticas
- Puertas automáticas
- Domótica
- Sistemas IoT
- Automatización industrial
- Cámaras de vigilancia

### Enseñanzas

Durante el desarrollo del proyecto se aprendió que:

- Los sensores PIR son simples pero muy útiles para sistemas interactivos.
- El filtrado de información es fundamental en IoT.
- Los botones ayudan a controlar tráfico de datos.
- Adafruit IO puede saturarse si se envían demasiados mensajes.
- La comunicación inalámbrica requiere optimizar frecuencia de envío.
- La visualización gráfica mejora mucho la experiencia del usuario.

### Empresa que utiliza sensores PIR

Una empresa reconocida que utiliza sensores PIR es Philips mediante su sistema de iluminación inteligente Philips Hue Motion Sensor.

Este dispositivo detecta movimiento dentro de una habitación y activa automáticamente luces inteligentes. También permite automatizar rutinas de ahorro energético y seguridad doméstica.

Otro ejemplo es Ring, que incorpora sensores PIR en cámaras y timbres inteligentes para detectar personas y activar grabaciones de seguridad.

---

## Actuador
### ¿Qué es una pantalla OLED?

OLED significa “Organic Light Emitting Diode”. Es una pantalla formada por diodos orgánicos emisores de luz que pueden iluminarse individualmente sin necesidad de retroiluminación.

En el proyecto, la pantalla OLED actúa como el actuador principal del sistema, ya que responde visualmente a la información recibida desde Adafruit IO.

### Conexión de la pantalla OLED

La pantalla OLED utilizada funciona mediante comunicación I2C, por lo que requiere cuatro conexiones principales:

#### VCC
- Alimentación de la pantalla.
- Conectado a 3.3V o 5V.
#### GND
- Tierra del circuito.
#### SDA
- Línea de datos I2C.
- Envía la información gráfica hacia la pantalla.
#### SCL
- Línea de reloj I2C.
- Sincroniza la comunicación entre el Arduino y la pantalla OLED.

En el Arduino Uno R4 WiFi:

- SDA se conecta al pin SDA.
- SCL se conecta al pin SCL.

Gracias a esta conexión, el Arduino puede enviar los frames de la animación y mostrar el GIF del alien caminando en la pantalla.


### Funciones

La pantalla OLED utilizada probablemente corresponde al modelo SSD1306 de 128x64 píxeles, uno de los más usados en proyectos con Arduino y Raspberry Pi Pico.

Características:
- Bajo consumo energético
- Alto contraste
- Tamaño compacto
- Comunicación I2C
- Buena visibilidad

Cada píxel puede encenderse individualmente, permitiendo mostrar:
- texto,
- íconos,
- gráficos,
- animaciones frame por frame.

## Forma de uso del actuador en el proyecto

La pantalla OLED recibe información desde el Arduino Uno R4 WiFi.

Cuando llega el dato de “movimiento detectado”:
1. El Arduino interpreta el valor recibido.
2. Se activa la animación.
3. Los frames del alien se reproducen en secuencia.
4. La pantalla muestra movimiento tipo GIF.

La pantalla también utiliza un botón para controlar cuándo recibe información desde Adafruit IO, evitando consultas constantes.

### Visualizaciones

La pantalla OLED permitió trabajar con pixel art y animaciones.

El alien fue dividido en seis frames diferentes:
- cada frame representa una posición distinta,
- al mostrarlos rápidamente, se crea la ilusión de movimiento.

Este método funciona de forma similar a:
- GIFs,
- sprites en videojuegos,
- animación cuadro por cuadro.
- 
### Control de información

La pantalla OLED no debe actualizarse constantemente porque:
- puede producir parpadeos,
- aumenta el uso de red,
- genera sobrecarga en Adafruit IO.

Para solucionar esto:
- la recepción se activó con botón,
- se limitaron las consultas,
- se actualiza solo cuando cambia el estado.

### Dificultades de pantallas OLED

1. Burn-in

Si una imagen permanece fija mucho tiempo, puede quedar marcada.

2. Memoria limitada

Las animaciones consumen RAM rápidamente.

3. Flickering

Actualizar demasiadas veces la pantalla produce parpadeo.

4. Problemas I2C

Direcciones incorrectas o cables sueltos impiden la comunicación.

5. Bajo refresco

Si la velocidad de actualización es lenta, la animación se ve cortada.

### Aplicaciones reales de pantallas OLED

Las pantallas OLED se utilizan en:
- Smartwatches
- Smartphones
- Consolas portátiles
- Instrumentos médicos
- Sistemas automotrices
- Dispositivos IoT

### Aprendizajes 

Durante el proyecto se aprendió que:

- Las pantallas OLED son excelentes para proyectos interactivos.
- Las animaciones requieren optimización de memoria.
- El control de frecuencia de actualización es importante.
- La integración entre IoT y visualización gráfica mejora la experiencia del usuario.
- Un actuador puede transformar datos simples en respuestas visuales atractivas e intuitivas.

### Proyectos que utilizan pantallas OLED 

Consolas retro portátiles

Existen múltiples proyectos de consolas mini retro que usan pantallas OLED SSD1306 de 128x64 píxeles para ejecutar juegos simples estilo arcade o pixel art.

Estas pantallas son ideales porque:
- tienen buena visibilidad,
- consumen poca energía,
- permiten gráficos monocromáticos rápidos.

Ejemplos:
- mini Game Boy DIY,
- juegos tipo Snake,
- Tetris,
- Flappy Bird en Arduino.

## Bibliografía

- Adafruit. (s.f.). *Adafruit IO documentation*. Adafruit Learning System. https://io.adafruit.com/

- DatasheetCafe. (2023). *HC-SR501 datasheet – PIR motion detector sensor module*. https://www.datasheetcafe.com/hc-sr501-datasheet-detector/

- MicroPython Documentation. (s.f.). *Using a SSD1306 OLED display*. MicroPython. https://docs.micropython.org/en/latest/esp8266/tutorial/ssd1306.html

- Moddable Tech, Inc. (2024). *SSD1306 display driver documentation*. Moddable Documentation. https://www.moddable.com/documentation/drivers/ssd1306/ssd1306

- PIRHOME. (2026). *HC-SR501 PIR sensor: Complete datasheet and pinout guide*. https://www.pirhome.com/?p=1001

- Simulator86 Documentation. (2026). *SSD1306 OLED display*. https://docs.simulator86.com/components/ssd1306/

- Soldered Electronics. (s.f.). *SSD1306 OLED display overview*. Soldered Documentation. https://docs.soldered.com/ssd1306/overview/

- UTMEL. (2021). *HC-SR501 PIR motion sensor: Datasheet, pinout and specifications*. https://www.utmel.com/components/hc-sr501-pir-motion-sensor-datasheet-pinout-and-specifications?id=696

- Reddit. (2026). *PIR firing false triggers*. Reddit. https://www.reddit.com/r/arduino/comments/1taytcs/pir_firing_false_triggers/

- Reddit. (2020). *[HELP] HC-SR501 PIR motion sensor*. Reddit. https://www.reddit.com/r/esp8266/comments/ifwphe/

- Reddit. (2022). *Is there any way to completely eliminate OLED flicker on an SSD1306 display?* Reddit. https://www.reddit.com/r/arduino/comments/xcsxnx/
