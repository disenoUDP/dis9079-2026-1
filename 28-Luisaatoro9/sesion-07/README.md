# Sesión 07 - lunes 20 abril 2026

Hoy el profe nos entregó el kit para la Solemne 2 y cambia harto la cosa porque ahora no es solo código, hay que mover piezas físicas. Nos pasaron una protoboard, un servo, un potenciómetro y una LDR. Yo me puse en modo concentrada y traté de captar todo antes de tocar algo.

Grupo Proyecto 2 : Braulio Figuero y yo.

### Conceptos Clave

**Servo:**
Es un motor pequeño que gira a un ángulo específico según lo que le diga el Arduino. Tiene tres cables y eso es lo importante de entender:

- El **rojo** es para darle energía (alimentarlo, va al 5V)
- El **negro** va al GND (el negativo, para cerrar el circuito)
- El **amarillo** es el que recibe la información, este es el que va directo a un pin digital del Arduino y es el que le dice al servo a qué posición moverse según lo que ponga en el código.

O sea, si en el código le digo 'muévete 90 grados', esa instrucción viaja por el cable amarillo. Para que eso pase, tengo que especificar en el código qué pin voy a ocupar para que el servo reciba la información; por ejemplo, usando miServo.attach(9) le digo que use el pin 9. Si conecto el cable en otro pin y no lo cambio en el código, el motor no va a recibir ninguna orden y se va a quedar quieto
<img width="940" height="750" alt="image" src="https://github.com/user-attachments/assets/d69f66f1-00d6-4c85-bf2c-68a2408b4481" />

**Protoboard:** Las líneas de los costados son los buses de poder (ahí conectas el 5V5V y el GNDGND desde el Arduino) y el área del medio es donde armas el circuito. Si no alimentas los buses, nada funciona.
<img width="1000" height="513" alt="image" src="https://github.com/user-attachments/assets/2cfd3ce7-b327-4a2e-9c55-e0c837e0455c" />


**Potenciómetro:**
Tiene 3 patas y sirve para regular voltaje. Lo usamos para controlar el giro del servo, básicamente es la "ruleta" que le manda la señal.


## Lo que hicimos

La idea era que al girar el potenciómetro, el servo se moviera al mismo tiempo. Suena simple pero en el código hay un truco: la función `map`.

¿Por qué? Porque el potenciómetro tira valores de hasta 1023 y el servo solo entiende de 0° a 180°. Si no traduces esos números con `map`, el servo no sabe qué hacer. 

### Código de pruebas en clases

Lectura de Potenciómetro y Control de Servo con Arduino

Este ejemplo nos permitió que un Arduino lea un potenciómetro conectado a la entrada `A0` y controle un servo motor conectado al pin digital `9`.

Cuando la lectura del potenciómetro supera cierto valor, el servo mueve la “manito tímidamente”.  
Si el valor baja, el servo vuelve lentamente a su posición inicial.

 **Componentes necesarios**

- Arduino UNO 
- Servo motor
- Potenciómetro
- Cables
- Protoboard

### Conexiones

**Potenciómetro**
- Pin izquierdo → `5V`
- Pin central → `A0`
- Pin derecho → `GND`

**Servo Motor**
- Cable señal → Pin `9`
- VCC → `5V`
- GND → `GND`


### Código Arduino

```cpp
// ejemplo lectura potenciometro

// queremos que nuestro Arduino
// sea capaz de leer un potenciometro
// conectado a la entrada A0.

#include <Servo.h>

Servo miServo;

int lectura = 0;
int anguloActual = 0;
int anguloDeseado = 0;

bool saludar = false;

void setup()
{
  pinMode(9, OUTPUT);
  Serial.begin(9600);

  // en que patita esta conectado el servo
  // conectemos a patita 9 digital
  miServo.attach(9);
}

void loop()
{
  // leer
  lectura = analogRead(A0);

  // imprimir en consola
  Serial.println(lectura);

  // toma el valor de lectura
  // que va originalmente entre 0 y 1023
  // y mapealo al rango 0 a 180
  // anguloActual = map(lectura, 0, 1023, 0, 180);

  if (lectura > 700) {
    saludar = true;
  }
  else {
    saludar = false;
  }

  if (saludar) {

    // lo que pasa cuando hay que saludar
    moverLaManitoTimidamente();

  }
  else {

    // lo que pasa cuando NO :(
    meCohibi();

  }
}

void moverLaManitoTimidamente() {

  if (anguloActual < 90)
  {
    miServo.write(anguloActual);
    anguloActual++;

    // servo descansa un poquito
    // 15 milisegundos
    // la vida es dura
    delay(15);
  }
}

void meCohibi() {

  anguloActual--;
  miServo.write(anguloActual);
  delay(15);

}
```
**Funcionamiento**

- El Arduino lee constantemente el valor del potenciómetro.
- Si el valor es mayor a `700`, el servo comienza a moverse lentamente hasta `90°`.
- Si el valor es menor o igual a `700`, el servo vuelve lentamente hacia atrás.
- Los valores se muestran en el Monitor Serial.

**Monitor Serial**

Velocidad configurada:

```txt
9600 baudios
```
En el código, no es llegar y mandar la posición. También le pusimos un delay de 15ms para darle tiempo al motor a reaccionar. Aprendí que los componentes físicos no son tan rápidos como el código, y sin ese pequeño tiempo de espera, el movimiento del servo no se vería fluido.
```
#include <Servo.h>
#include <WiFiS3.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"

// ── Credenciales ───────────────────────────────────────────
#define WIFI_SSID    "bla"
#define WIFI_PASS    "bla"
#define AIO_SERVER   "io.adafruit.com"
#define AIO_PORT     1883
#define AIO_USERNAME 
#define AIO_KEY      
#define AIO_FEED     AIO_USERNAME 

#define INTERVALO_PUBLISH 500

Servo miServo;
WiFiClient wifiClient;
Adafruit_MQTT_Client mqtt(&wifiClient, AIO_SERVER, AIO_PORT, AIO_USERNAME, AIO_KEY);
Adafruit_MQTT_Publish feedPot(&mqtt, AIO_FEED);

int lecturaAnterior = -1;
unsigned long ultimoPublish = 0;

void conectarMQTT() {
  while (!mqtt.connected()) {
    Serial.print("Conectando a Adafruit IO...");
    int8_t ret = mqtt.connect();
    if (ret == 0) {
      Serial.println(" OK");
    } else {
      Serial.print(" Error: ");
      Serial.println(mqtt.connectErrorString(ret));
      mqtt.disconnect();
      delay(3000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  miServo.attach(9);

  Serial.print("Conectando WiFi");
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.print(" IP: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  conectarMQTT();
  mqtt.ping();

  int lectura = analogRead(A0);
  int angulo  = map(lectura, 0, 1023, 0, 180);
  miServo.write(angulo);

  unsigned long ahora = millis();
  if (lectura != lecturaAnterior && (ahora - ultimoPublish >= INTERVALO_PUBLISH)) {
    Serial.print("Publicando lectura: ");
    Serial.println(lectura);

    if (feedPot.publish((int32_t)lectura)) {
      Serial.println("  ✓ OK");
      lecturaAnterior = lectura;
      ultimoPublish   = ahora;
    } else {
      Serial.println("  ✗ Fallo");
    }
  }

  delay(15);
}
```
Hallazgo del día: El experimento del potenciómetro

Mientras trabajaba con mi compañero de grupo, nos dimos cuenta de algo súper importante: probamos usar un potenciómetro distinto al que venía en el kit original (un B20K) y la fluidez del movimiento del servo cambió totalmente.

¿Qué aprendimos? Que no da lo mismo cualquier componente. Al usar uno con una resistencia distinta, el voltaje que recibe el Arduino varía y eso se nota directo en el servo. Hicimos la prueba y notamos que el movimiento no se sentía igual de suave que con el original. Fue un buen "ensayo y error" para entender que la electrónica también depende de la precisión de las piezas, si cambias el sensor, el resultado final en el actuador también cambia.

### 💡 Nota mental

Todos los componentes tienen que estar bien conectados al GND. Si un cable queda suelto o mal puesto en la protoboard, el sensor empieza a tirar valores basura y te quedas un buen rato buscando un error que no existe en el código.

Un poco de investigación propia acerca de los componentes para tener una idea más clara con lo que trabajamos.
<img width="500" height="513" alt="image" src="https://github.com/user-attachments/assets/797caa86-d7e8-44ce-b9e5-3fe0021b7add" />
<img width="500" height="513" alt="image" src="https://github.com/user-attachments/assets/45a3c40f-a466-43ec-a4f6-6f687b984fa7" />
<img width="500" height="513" alt="image" src="https://github.com/user-attachments/assets/80009775-2329-486e-a553-d97b72b7e16f" />
<img width="500" height="513" alt="image" src="https://github.com/user-attachments/assets/f9eb41df-0fcd-47f3-8a34-99576a068051" />

### Referencias

- [¿Qué es un servo motor y cómo funciona?](https://www.arduino.cc/en/Reference/Servo)
- [Cómo conectar un servo al Arduino (pines y cableado)](https://docs.arduino.cc/learn/electronics/servo-motors/)
- [Cómo conectar una LDR](https://learn.adafruit.com/photocells/using-a-photocell)
- [Adafruit IO y MQTT](https://io.adafruit.com/api/docs/mqtt.html)
