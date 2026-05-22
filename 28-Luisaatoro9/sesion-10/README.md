# Sesión 10 - lunes 18 mayo 2026

Esta sesión fue la que juntó todo. El objetivo era armar un proyecto de interacción inalámbrica usando lo que se aprendió durante el semestre, Raspberry Pi Pico 2 W mandando una señal y Arduino UNO R4 WiFi recibiéndola. Me hice cargo de toda la parte del Arduino (el receptor) y del circuito físico, porque la verdad es que con esta placa me siento en casa y disfruto harto el proceso de armar y programar con ella.

### Cómo nos organizamos

Se trabajó en dupla: mi compañero se encargó de la parte de la Raspberry Pi Pico 2 W (el emisor) y yo me concentré en el Arduino UNO R4 WiFi y el circuito. Antes de tocar la comunicación inalámbrica, decidí verificar que todo funcionara por partes, así si algo falla, sé exactamente dónde buscar.

**Paso 1: Validar el hardware primero:**
Monté el LED con su resistencia de **220Ω** en la protoboard. Primero hice una prueba de alimentación directa a 5V para confirmar que el LED encendía, y después una prueba de control con un código de parpadeo en el **pin 13**. Ver que el LED respondía bien fue la señal para avanzar a la parte inalámbrica con confianza.

<p align="center">
  <img width="515" height="600" alt="image" src="https://github.com/user-attachments/assets/3cc83dbb-cc79-4aae-9ffd-962d6fffddac" />
</p>

<p align="center">
  <em>
    Esta imagen muestra la conexión del positivo del LED al pin 5V del Arduino para corroborar el correcto encendido del LED.
  </em>
</p>

<p align="center">
  <img width="315" height="315" alt="image" src="https://github.com/user-attachments/assets/ed620dc2-e814-4bce-b9a1-3d4bfbaab040" />
  <img width="315" height="315" alt="image" src="https://github.com/user-attachments/assets/8e4876e2-d6e3-4979-992b-0810f95a0df1" />
  <img width="315" height="315" alt="image" src="https://github.com/user-attachments/assets/5771b7a4-2d57-4942-b04b-82de08ae5800" />
</p>

<p align="center">
  <em>
    Estas imágenes muestran el proceso de conexión del LED al pin de la placa.
  </em>
</p>

### Código utilizado para la prueba de encendido y apagado en el pin 13 reflejándolo en un led
```cpp
void setup() {

  Serial.begin(115200);

  pinMode(13, OUTPUT);
}

void loop() {

  digitalWrite(13, HIGH);

  Serial.println("LED ENCENDIDO");

  delay(500);

  digitalWrite(13, LOW);

  Serial.println("LED APAGADO");

  delay(500);
}
```
<div align="center"> <video src="https://github.com/user-attachments/assets/24d8ffe0-9134-476e-ae22-cc474dfec71e" width="315" autoplay loop muted playsinline></video> <p><em>Este GIF muestra la prueba realizada en el pin 13, enviando un código de encendido y apagado para corroborar tanto el correcto funcionamiento de la conexión del LED como la recepción del código enviado desde Arduino al pin 13.</em></p> </div> 

**Paso 2: Controlar el envío de datos:**
Se usó un botón físico para decidir cuándo mandar información a Adafruit IO. Así no se satura el canal con datos constantes, el tráfico queda limpio y la conexión se mantiene estable.
<p align="center">
  <img width="770" height="348" alt="image" src="https://github.com/user-attachments/assets/6881ddfc-664e-4bce-ac3e-c526681bc3ab" />
</p>

<p align="center">
  <em>
    En esta imagen se evidencia la conexión del botón con la Raspberry Pi Pico 2 W.
  </em>
</p>
<p align="center">
  <img width="505" height="536" alt="image" src="https://github.com/user-attachments/assets/0c588408-ef90-4bf2-bb73-f0c7b15d95b1" />
</p>

<p align="center">
  <em>
    En esta imagen se visualiza la conexión final del Arduino UNO R4 WiFi con el LED y de la Raspberry Pi Pico 2 W con el botón.
  </em>
</p>

---
### Los detalles que marcan la diferencia

Lo que más se cuidó en esta sesión fue anticiparse a los errores típicos que hacen perder tiempo:

**Estructura del IDE:** Cada código guardado en su carpeta específica con el nombre exacto. Suena obvio pero es de los errores más comunes, si el archivo no se llama como el IDE espera, no compila y uno se queda dando vueltas sin saber por qué.

**Baudios desde el inicio:** Se configuró a `115200` desde el principio, sabiendo que era la velocidad necesaria para comunicarse con la Raspberry Pi Pico 2 W. El error clásico es dejarlo en `9600` y después preguntarse por qué los datos llegan como caracteres raros o no llegan.

**Mayúsculas, minúsculas y espacios:** Se revisó cada `#include`, cada credencial de red y cada nombre de biblioteca con cuidado. Una letra mal puesta en el nombre del WiFi o en el token de Adafruit y la conexión no se establece y ese error es difícil de ver a simple vista.

---

### Cómo resultó

Gracias a ese nivel de detalle, antes del primer recreo el sistema ya estaba funcionando: la Raspberry Pi Pico 2 W mandaba la señal al presionar el botón y el Arduino UNO R4 WiFi encendía el LED al recibirla. Sin vueltas innecesarias.

---

### Colaboración y Trabajo en Equipo

Casi al término de la clase, se integraron dos compañeras a nuestro grupo. Ellas tenían una propuesta distinta con otros sensores, pero se les estaba dificultando la implementación.

Como equipo, decidimos unir fuerzas. Les explicamos nuestra lógica del botón y el LED para que pudieran entender la base de la interacción inalámbrica. Fue una instancia muy buena para ayudarlas a identificar qué errores evitar (como la sintaxis o los baudios) para que sus propias ideas funcionen en el futuro.

*Debido al tiempo, acordamos juntarnos durante la semana para:*

* *Explicarles a fondo el funcionamiento de nuestro código y conexiones.*
* *Realizar pruebas conjuntas para que todos estemos preparados para el examen.*
* *Refinar la propuesta final del proyecto.*

---
### Lo que me llevo

Me doy cuenta de que ya no armo circuitos por armar. Ahora tengo un proceso, verifico por etapas, me anticipo a los errores y sé dónde suelen fallar las cosas. Eso me permite avanzar más rápido y, honestamente, disfrutar más el proceso. Además, me motiva mucho ver que no solo puedo resolver mis propios desafíos técnicos con rapidez, sino que también puedo transmitir ese conocimiento a mis compañeras. Me siento muy conectada con Arduino y me entusiasma seguir explorando sus posibilidades para el examen final.

---

### Referencias

- [Arduino y comunicación WiFi con Adafruit IO](https://learn.adafruit.com/adafruit-io-basics-analog-output)
- [Control de LED con Arduino](https://docs.arduino.cc/built-in-examples/basics/Blink/)
- [Configuración de baudios en Arduino IDE](https://docs.arduino.cc/software/ide-v2/tutorials/ide-v2-serial-monitor/)
- [Adafruit IO y MQTT](https://io.adafruit.com/api/docs/mqtt.html)
