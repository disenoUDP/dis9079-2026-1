# Investigaciones individuales — Sensor y Actuador  
**Marlén Soto**  
Github:marlensoto-lab   

# El Sensor: Pulsador (Botón)

![Botón Pulsador](imagenes/boton_pulsador.jpg)

## 1. ¿Qué aprendí sobre este sensor?

Aunque un botón parece ser uno de los componentes más simples de la electrónica, al investigarlo descubrí que su funcionamiento tiene varios aspectos importantes dentro de los sistemas digitales.

Un pulsador funciona como un sensor de contacto, ya que detecta si está siendo presionado o no y envía esa información al microcontrolador en forma de valores binarios: 1 o 0. Uno de los principales aprendizajes fue entender el problema del “estado flotante”. Cuando el botón no tiene una resistencia Pull-up o Pull-down, el pin queda inestable y puede interpretar señales aleatorias debido al ruido eléctrico del entorno.

Para evitar esto se utilizan resistencias de referencia, ya sean internas o externas, que mantienen un estado lógico estable cuando el botón no está siendo utilizado. Gracias a esto el sistema puede detectar correctamente cuándo el botón fue presionado.

En nuestro proyecto utilizamos el botón como sensor principal porque necesitábamos que el usuario decidiera cuándo enviar información hacia Adafruit IO, evitando que el sistema enviara datos constantemente.

---

## 2. Filtrado de información y visualización de datos

Otro concepto importante aprendido fue el “debouncing” o rebote mecánico del botón. Cuando una persona presiona el pulsador, los contactos metálicos internos vibran durante algunos milisegundos antes de estabilizarse. El microcontrolador interpreta estas vibraciones como múltiples pulsaciones aunque realmente solo se haya presionado una vez.

Para solucionar este problema se utiliza un pequeño delay dentro del código, permitiendo ignorar las señales repetidas generadas durante el rebote y registrando únicamente una pulsación válida.

En Adafruit IO, los datos del botón se visualizan como valores binarios:
- **0:** botón no presionado.
- **1:** botón presionado.

Sin el filtrado correcto, la plataforma muestra múltiples picos de información generados por el rebote. Con el debouncing aplicado, los datos aparecen de manera mucho más limpia y precisa.

---

## 3. Problemas comunes

### Saturación del servidor
Si el sistema envía constantemente el estado del botón en cada ciclo del programa, Adafruit IO puede saturarse con datos repetidos. Por esta razón, lo correcto es enviar información solo cuando el estado cambia.

### Conexiones incorrectas
Los botones de 4 pines pueden generar confusión en la protoboard, ya que internamente sus patas están conectadas en pares. Una conexión incorrecta puede provocar que el botón quede permanentemente activado o desactivado.

### Estado flotante
Cuando no se utilizan resistencias Pull-up o Pull-down, el pin queda inestable y el sistema comienza a detectar activaciones falsas de manera aleatoria.

---

## 4. Referentes

### Amazon Dash Buttons

![Empresa](imagenes/Amazon.png) 

Los Amazon Dash Buttons fueron botones inteligentes conectados por WiFi que permitían pedir productos automáticamente desde el hogar con una sola pulsación.

Este referente se relaciona directamente con nuestro proyecto, ya que ambos utilizan la misma lógica:
- Un botón detecta una acción.
- La señal se envía a través de internet.
- Un sistema en la nube procesa la información y ejecuta una respuesta.

Además, estos dispositivos también necesitaban controlar problemas similares a los nuestros, como el rebote del botón y la saturación de datos enviados al servidor.

---

# El Actuador: LED

![LED](imagenes/Luz_led.jfif)

## 1. ¿Qué aprendí sobre este actuador?

El LED (Light Emitting Diode) es un actuador que transforma energía eléctrica en luz. Aprendí que no funciona como una ampolleta común, ya que necesita controlar correctamente la cantidad de corriente que recibe.

Por esta razón, siempre debe utilizarse una resistencia en serie para proteger el componente y evitar daños tanto en el LED como en el microcontrolador. En nuestro proyecto utilizamos una resistencia de 220Ω para mantener un rango seguro de funcionamiento.

El Arduino controla el LED mediante señales digitales:
- **HIGH:** el LED enciende.
- **LOW:** el LED se apaga.

---

## 2. Filtrado y visualización de datos

En el caso del LED, el filtrado ocurre al momento de recibir la información desde Adafruit IO.

El Arduino se suscribe mediante el protocolo MQTT a un canal específico y únicamente responde cuando recibe el mensaje correcto. Esto evita que el actuador reaccione a información errónea o ruido dentro de la comunicación.

La visualización del sistema es inmediata: si el LED enciende, significa que la comunicación entre la Raspberry Pi Pico 2W, Adafruit IO y el Arduino UNO R4 WiFi funcionó correctamente.

---

## 3. Problemas comunes

### Polaridad invertida
El LED posee un ánodo (positivo) y un cátodo (negativo). Si se conecta al revés, no enciende aunque tampoco se daña.

### Baud rate incorrecto
Si el monitor serial y el código utilizan velocidades diferentes de comunicación, el Arduino no interpreta correctamente los mensajes recibidos.

### Resistencia inadecuada
Utilizar una resistencia demasiado baja puede provocar sobrecorriente, dañando el LED o incluso los pines de la placa.

---

## 4. Referente: The Bay Lights — Leo Villareal
![Referente](imagenes/Referente_2.jpg)

“The Bay Lights” es una instalación artística creada por Leo Villareal que utilizó miles de LEDs distribuidos en el puente Bay Bridge de San Francisco para generar patrones lumínicos dinámicos mediante programación.

Lo interesante de este referente es que utiliza exactamente el mismo principio trabajado en nuestro proyecto:
una señal digital controla el comportamiento de un LED.

La diferencia está únicamente en la escala, ya que mientras nuestro proyecto controla un solo LED mediante Adafruit IO, esta instalación coordinaba miles de LEDs en tiempo real utilizando software y redes de control.

---

## Bibliografía

- Arduino Documentation. *Digital Inputs and Pull-up Resistors*. Disponible en: https://docs.arduino.cc/

- Adafruit IO Documentation. *MQTT, Feeds and IoT Communication*. Disponible en: https://io.adafruit.com/

- MQTT.org. *MQTT Protocol Overview*. Disponible en: https://mqtt.org/

- Wikipedia. *Amazon Dash*. Disponible en: https://en.wikipedia.org/wiki/Amazon_Dash

- Leo Villareal. *The Bay Lights*. Disponible en: https://www.leovillareal.com/project/the-bay-lights/

