# investigaciones individuales

Monserrat Paredes / https://github.com/Monserrat-Paredes

## Investigación

Sensores: Dispositivo diseñado para detectar cambios en el entorno.

Actuadores: Dispositivo que recibe una orden o señal.

Lo que queremos realizar en la solemne 2 es que desde la Raspberry pi envíe datos de un botón on/off hacia el Arduino y que este encienda una luz o emita algún sonido.

---

### Pseudocódigo

|Raspberry Pi Pico 2 W|Adafruit IO|Arduino UNO R4 wifi|
|--|--|--|
|Botón|MQTT|LED|
|ON/OFF|feed:estado|verde/rojo|


1. Presionar elbotón en la raspberry > alterna entre ON y OFF
2. La Raspberry publica "ON" "OFF" en el feed de Adafruit IO
3. El Arduino recibe el mensaje y enciende el LED correspondiente

---

#### Raspberry Pi Pico 2W

- Cada vez que presionas el botón, alterna entre ON y OFF (no es necesario mantenerlo)
- El LED integrado de la placa te muestra el estado actual (encendido=ON, apagado=OFF)
- Publica el texto "ON" u "OFF" en el feed estado de Adafruit IO

 ---
 
#### Arduino UNO R4 Wifi

- Recibe "ON" -> Enciende LED verde (D2), apaga el rojo
- Recibe "OFF" -> enciende LED rojo (D3), apaga el verde
- Al arrancar, ambos  LEDS parpadean 3 veces para confirmar que la conexión fue exitosa

---

NO OLVIDAR!

TU_NOMBRE_WIFI / TU_CLAVE_WIFI

TU_USUARIO_ADAFRUIT / TU_AIO_KEY

En el .ino, también reemplaza TU_USUARIO_ADAFRUIT en la línea del feed

Crear el feed llamado estado en tu cuenta de Adafruit IO antes de ejecutar


Después decidimos cambiarlo 

---

## sensor

Investigación del sensor: Potenciómetro B500K


<img width="414" height="434" alt="sensorPotenciómetro" src="https://github.com/user-attachments/assets/c62d049b-a491-4db0-8a17-3d5d3ed09a3b" />

Imagen sacada de https://afel.cl/products/potenciometro-500k-ohm?_pos=4&_psq=pote&_ss=e&_v=1.0

### ¿Qué es un potenciómetro?

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

## Proyecto o referente artístico (sensor y robótica musical)

### Andrea Gregorini “ARKeytar”

Es un desarrollador independiente italiano reconocido en la comunidad de música electrónica por su trabajo en el diseño y creación de instrumentos MIDI de tipo hazlo tú mismo (DIY). Su enfoque combina ingeniería electrónica, programación creativa y diseño sonoro, fomentando la accesibilidad tecnológica para músicos y aficionados.


### Trabaja mezclando:

- Luthería digital.

- Robótica musical.

- Performance en vivo.

- Diseño industrial.

- Interacción física.
  

### Sobre el proyecto: ARKeytar

Es un enorme instrumento MIDI tipo keytar construido con madera, sensores táctiles y controles analógicos.

La idea para la creación de este controlador MIDI surgió tras observar lo que algunas personas podían lograr combinando softpots, Arduino e instrumentos musicales. Descubrí que algunas aplicaciones eran realmente interesantes.

Para crear un único instrumento capaz de ofrecer estas características, opté por la forma de una guitarra, para que sea fácil de manejar tanto de pie como sentado. En este caso, un ángulo de ejecución elevado favorece la posición de la mano derecha al tocar el teclado.


### Tecnologías utilizadas:

- Arduino
 
- Potenciómetros analógicos.
 
- SoftPot membrane potentiometers.

- MIDI USB.

- Sensores táctiles.

- Shift registers

- LEDs.

- programación Arduino IDE.


### ¿Por qué genera impacto?

Porque parece un instrumento futurista híbrido entre guitarra, sintetizador e interfaz robótica.

El uso de potenciómetros permite manipular sonido en tiempo real de forma corporal y performática.


### Imagenes de proyecto

<img width="734" height="456" alt="ARKeytar01" src="https://github.com/user-attachments/assets/912a8d2d-420d-45a0-9cd0-7a8ee93ec3f0" />


<img width="528" height="414" alt="ARKeytar02" src="https://github.com/user-attachments/assets/85168c32-fa35-4b0e-804e-877c9f951b03" />


<img width="579" height="123" alt="ARKeytar03" src="https://github.com/user-attachments/assets/659c881e-3cdc-4508-a9be-71cadded17fa" />

Imagenes sacadas de https://projecthub.arduino.cc/andreagregorini/arkeytar-arduino-based-midi-controller-keytar-45b72d

---

## Actuador

Investigación Actuador: Servomotor SG90


<img width="700" height="688" alt="ServoMotor" src="https://github.com/user-attachments/assets/03161dfa-04ff-409a-b512-b08a26b9ecae" />

Imagen sacada de https://arduino.cl/producto/micro-servo-motor-sg90-9g/ 


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


### Es utilizado en:

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

## Proyecto o referente artístico (actuador)

### Igor Fonseca “Robot de la Alegría”

Ingeniero eléctrico y mecánico, máster en automatización y control. Especialista en instrumentación industrial. Científico loco e inventor.

Es principalmente conocido por crear el proyecto “Robô da Alegria” (Joy Robot), un robot humanoide diseñado para interactuar con niños en hospitales infantiles y apoyar iniciativas educativas y sociales en Brasil.


### Trabaja mezclando:

- Robótica social.

- Diseño emocional.

- Impresión 3D.

- Interacción humano-robot.

- Electrónica DIY.

- Programación interactiva.


### Sobre el proyecto:

Es un robot humanoide construido para interactuar con niños en hospitales y generar experiencias lúdicas y emocionales positivas. 

El robot:

- Mueve brazos y cabeza.

- Responde mediante movimiento.

- Puede desplazarse.

- Genera expresiones corporales.

- Interactúa remotamente vía WiFi.

El diseño está inspirado en robots sociales educativos y utiliza múltiples servomotores SG90 para producir movimientos suaves y expresivos.


### Tecnologías utilizadas:

- Arduino UNO.

- 6 servomotores SG90.

- ESP8266.

- Controlador PCA9685.

- Impresión 3D.

- Motores DC.

- Driver L298N.

- Programación Arduino IDE.


### ¿Por qué genera impacto?

Porque transforma componentes simples y baratos en un robot humanoide expresivo.

El movimiento generado por los SG90 hace que el robot parezca “vivo” y cercano emocionalmente, especialmente en contextos infantiles y sociales.



### Imágenes del proyecto:

<img width="498" height="531" alt="Joy Robot01" src="https://github.com/user-attachments/assets/03da11ac-2a48-43f7-83fd-46fa81cacf11" />


<img width="400" height="273" alt="Joy Robot03" src="https://github.com/user-attachments/assets/51e3a26d-b9e5-45e5-8941-9bb1175386dd" />


<img width="555" height="549" alt="Joy Robot02" src="https://github.com/user-attachments/assets/5aa09049-7a3b-4d7f-8cc2-06862e18f855" />

Imagenes y gif sacados de https://www.hackster.io/igorF2/joy-robot-robo-da-alegria-bba54f 


## Código que envía, en Raspberry PI Pico 2 W


```cpp
#  LIBRERIA necesaria en /lib:
#    - adafruit_minimqtt
# ============================================================

import time
import board # type: ignore
import analogio # type: ignore
import digitalio # type: ignore
import wifi # type: ignore
import socketpool # type: ignore
import adafruit_minimqtt.adafruit_minimqtt as MQTT # type: ignore

#  cambiar claves wifi
WIFI_SSID     = "blablabla"
WIFI_PASSWORD = "blablabla"

AIO_USERNAME  = "blablabla"
AIO_KEY       = "blablabla"

FEED_ANGULO   = f"{AIO_USERNAME}/feeds/moluscos"

# definir potenciometro + led
potenciometro = analogio.AnalogIn(board.GP27)

led = digitalio.DigitalInOut(board.LED)
led.direction = digitalio.Direction.OUTPUT
led.value = False

# lee los valores en angulo, del potenciometro
def leer_angulo():
    # ADC devuelve 0-65535, convertimos a 0-180
    return int(potenciometro.value * 180 / 65535)

# verificar conexion wifi
print("Conectando a WiFi...")
try:
    wifi.radio.connect(WIFI_SSID, WIFI_PASSWORD)
    print("  ✓ IP:", wifi.radio.ipv4_address)
except Exception as e:
    print("  ✗ Error WiFi:", e)
    while True:
        pass

# verificar conexion mqtt
pool = socketpool.SocketPool(wifi.radio)

mqtt = MQTT.MQTT(
    broker="io.adafruit.com",
    port=1883,
    username=AIO_USERNAME,
    password=AIO_KEY,
    socket_pool=pool,
)

try:
    mqtt.connect()
    print("  ✓ Conectado a Adafruit IO")
    print("  Feed:", FEED_ANGULO)
    print("\nListo. Gira el potenciómetro...\n")
except Exception as e:
    print("  ✗ Error MQTT:", e)
    while True:
        pass

# aqui se define todo 
angulo_anterior = -1

while True:
    try:
        mqtt.loop()

        angulo = leer_angulo()

        # Publica solo si cambi0 mas de 2 grados (filtra ruido del ADC)
        if abs(angulo - angulo_anterior) > 2:
            print("Angulo:", angulo, "° → publicando...")
            mqtt.publish(FEED_ANGULO, str(angulo))
            angulo_anterior = angulo

            # Parpadeo del LED al publicar
            led.value = True
            time.sleep(0.05)
            led.value = False

    except Exception as e:
        print("Error:", e, "— reconectando...")
        try:
            mqtt.reconnect()
        except Exception:
            pass

    time.sleep(0.1)

```


## Código que recibe, en Arduino IDE


```cpp
// Grupo 08
// Arduino UNO R4 WiFi — Adafruit IO → Servo SG90 + LED rojo

//  Recibe ángulo (0-180°) desde Adafruit IO
//  → Mueve el servo SG90 a ese ángulo
// si el ángulo pasa los 125° → enciende LED amarillo
#include <WiFiS3.h>
#include <ArduinoMqttClient.h>
#include <Servo.h>

// configuracion de los datos
const char* WIFI_SSID     = "blablabla";
const char* WIFI_PASSWORD = "blablabla";

const char* AIO_SERVER    = "io.adafruit.com";
const int   AIO_PORT      = 1883;
const char* AIO_USERNAME  = "blablabla";
const char* AIO_KEY       = "blablabla";

const char* FEED_ANGULO   = "blablabla/feeds/moluscos";

// definir pines del servo y led
const int PIN_SERVO    = 9;
const int PIN_LED_ROJO = 3; // ya no es rojo, upsi

// angulo a partir del cual enciende el LED (señal de termino)
const int ANGULO_TERMINO = 125;

// wifi + servo
WiFiClient   wifiClient;
MqttClient   mqttClient(wifiClient);
Servo        miServo;

// se ejecuta al recibir el mensaje
void onMqttMessage(int messageSize) {
  String payload = "";
  while (mqttClient.available()) {
    payload += (char)mqttClient.read();
  }

  int angulo = payload.toInt();
  angulo = constrain(angulo, 0, 180);  // seguridad: limita al rango del servo

  Serial.print("Ángulo recibido: ");
  Serial.print(angulo);
  Serial.println("°");

  // mueve el servo
  miServo.write(angulo);

  // LED rojo: enciende si llego al angulo de termino
  if (angulo >= ANGULO_TERMINO) {
    digitalWrite(PIN_LED_ROJO, HIGH);
    Serial.println("  → LED ROJO encendido ✓ (término alcanzado)");
  } else {
    digitalWrite(PIN_LED_ROJO, LOW);
    Serial.print("  → Servo en ");
    Serial.print(angulo);
    Serial.print("° (falta ");
    Serial.print(ANGULO_TERMINO - angulo);
    Serial.println("° para término)");
  }
}

// setup
void setup() {
  Serial.begin(115200);
  delay(1500);

  // pines
  pinMode(PIN_LED_ROJO, OUTPUT);
  digitalWrite(PIN_LED_ROJO, LOW);

  miServo.attach(PIN_SERVO);
  miServo.write(0);   // posicion inicial: 0°

  Serial.println("=== Arduino UNO R4 WiFi — Servo SG90 + LED ===\n");

  // wifi
  Serial.print("Conectando a WiFi");
  while (WiFi.begin(WIFI_SSID, WIFI_PASSWORD) != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
  }
  Serial.println();
  Serial.print("  ✓ IP: ");
  Serial.println(WiFi.localIP());

  // mqtt
  mqttClient.setId("ArduinoUNOR4_servo");
  mqttClient.setUsernamePassword(AIO_USERNAME, AIO_KEY);
  mqttClient.onMessage(onMqttMessage);

  Serial.print("Conectando a Adafruit IO...");
  while (!mqttClient.connect(AIO_SERVER, AIO_PORT)) {
    Serial.print(".");
    delay(1000);
  }
  Serial.println();
  Serial.println("  ✓ Conectado a Adafruit IO");

  mqttClient.subscribe(FEED_ANGULO);
  Serial.println("  ✓ Suscrito al feed: moluscos");
  Serial.print("\nEsperando datos... LED enciende al llegar a ");
  Serial.print(ANGULO_TERMINO);
  Serial.println("°\n");

  // parpadeo de confirmacion
  for (int i = 0; i < 3; i++) {
    digitalWrite(PIN_LED_ROJO, HIGH); delay(150);
    digitalWrite(PIN_LED_ROJO, LOW);  delay(150);
  }
}

// loop
void loop() {
  // reconexion automatica
  if (!mqttClient.connected()) {
    Serial.println("[MQTT] Desconectado. Reconectando...");
    digitalWrite(PIN_LED_ROJO, LOW);
    miServo.write(0);

    while (!mqttClient.connect(AIO_SERVER, AIO_PORT)) {
      Serial.print(".");
      delay(2000);
    }
    mqttClient.subscribe(FEED_ANGULO);
    Serial.println("\n  ✓ Reconectado");
  }

  mqttClient.poll();
}

```
## Bibliografía

- Arduino.cl. (sf). Micro Servomotor SG90 9g. Arduino.cl. https://arduino.cl/producto/micro-servo-motor-sg90-9g

- Arduino.cl. (sf). Ejemplo análogo con potenciómetro. Arduino.cl. https://arduino.cl/ejemplo-analogo-con-potenciometro/?srsltid=AfmBOopNZdWYQtTXaZWpSAN4Bjrw3WSeNnmfDP10xmWbFMU7vnoCf1vW

- Arduino.cl. (s.f.). Arduino UNO R4 WiFi. [https://arduino.cl/producto/arduino-uno-r4-wifi/](https://arduino.cl/producto/arduino-uno-r4-wifi/)

- Adafruit.com.(sf).Adafruit.com. https://learn.adafruit.com/welcome-to-adafruit-io?view=all

- Circuitpython.org.(sf).Raspberry_pi_pico2_w. Circuitpython.org https://circuitpython.org/board/raspberry_pi_pico2_w/

- Afel.cl.(s.f).micro servomotor sg90. Afel.cl.https://afel.cl/products/micro-servomotor-sg90?_pos=1&_psq=servomotor&_ss=e&_v=1.0
  
- Afel.cl.(s.f).potenciometro 500k-ohm. Afel.cl. https://afel.cl/products/potenciometro-500k-ohm?_pos=4&_psq=pote&_ss=e&_v=1.0

- Andrea Gregorini. (2021). ARKeytar – Arduino based MIDI controller keytar. Project Hub Arduino. https://projecthub.arduino.cc/andreagregorini/arkeytar-arduino-based-midi-controller-keytar-45b72d

- Igor Fonseca. (2018). Joy Robot (Robô Da Alegria). Hackster.io. https://www.hackster.io/igorF2/joy-robot-robo-da-alegria-bba54f

- Igor Fonseca. (s.f.). IgorF2 Profile. Hackster.io. https://www.hackster.io/igorF2


