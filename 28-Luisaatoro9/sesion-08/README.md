# Sesión 08 - lunes 27 abril 2026

Hoy la clase se puso interesante porque jubilamos el Arduino y nos pasaron la **Raspberry Pi Pico 2 W**. Es como cambiar de planeta, el hardware es distinto, el lenguaje es distinto, todo cambia. Se empezó a usar **CircuitPython** y, la verdad, una vez que se le agarra el ritmo es bastante más amigable de lo que parece al principio.


### Conociendo la Raspberry Pi Pico 2 W

Antes de conectar cualquier cosa, hay que entender con qué se está trabajando. La **Raspberry Pi Pico 2 W** es una placa de desarrollo pequeña (como un chicle largo) basada en el chip **RP2350**. La "W" significa que tiene **WiFi integrado**, lo que la hace perfecta para mandar datos a la nube sin cables extra.

Lo que más confunde al principio es que tiene muchos pines y cada uno puede cumplir varios roles dependiendo de cómo se configure en el código. Mirando el mapa de pines se ven varios colores, y cada uno significa algo distinto:

- 🔴 **Rojo (Power):** Pines de alimentación el `VBUS` entrega 5V directo desde el USB, y el `3V3(OUT)` entrega los 3.3V que se usan para los componentes.
- ⬛ **Negro (Ground/GND):** La tierra. Hay varios repartidos por la placa y son los pines **cuadrados** en el mapa, fácil de identificar.
- 🟢 **Verde claro (GPIO/PWM):** Los pines de propósito general. Son los más usados para conectar sensores y componentes.
- 🟢 **Verde oscuro (ADC):** Los pines analógicos. El `ADC0` (pin 31), `ADC1` (pin 32) y `ADC2` (pin 34) son los únicos que pueden leer señales analógicas como las del potenciómetro.

La diferencia clave con el Arduino es que la Raspberry **trabaja a 3.3V**, no a 5V. Si se conecta algo que necesita más voltaje directamente, se daña  y no hay vuelta atrás.

<img width="1000" height="700" alt="image" src="https://github.com/user-attachments/assets/6aba48c2-ddbf-424e-9c7b-83ea161fb1fc" />


### wowww

Lo primero que advirtieron es que en Python **los espacios son sagrados**. Si no se deja la sangría correcta al principio de cada línea, el código simplemente se rompe, es su forma de ordenar quién manda a quién.

Un dato que me quedó dando vueltas: Python no se llama así por la serpiente. Su creador, **Guido van Rossum**, le puso ese nombre en honor al grupo de comedia británico **Monty Python**, porque quería que el lenguaje fuera entretenido y accesible, no tan rígido como los de la época. El logo de la serpiente vino después y se quedó porque pega igual. Hoy Python es el lenguaje rey de la IA, así que algo bueno tendrá.

---

### Configurando el "cerebro"

Para que la Raspberry funcionara, hubo que hacerle una especie de cirugía antes de tocar cualquier código:

1. **Limpiar y cargar:** Se le borró todo lo que traía y se le "inyectó" el firmware de CircuitPython (versión 10.22.0). Lo entretenido es que la placa aparece en el computador como si fuera un pendrive, así que es literalmente llegar y arrastrar archivos.

2. **Las bibliotecas:** No es llegar y programar directo. Hay que cargarle sus "ayudantes" manualmente archivos `.mpy` para que la placa sepa conectarse al WiFi y hablar con Adafruit IO. Las que se usaron fueron:
   - `adafruit_minimqtt/` (carpeta completa)
   - `adafruit_connection_manager.mpy`
   - `adafruit_ticks.mpy`

3. **PuTTY:** Se usó este programa para ver qué estaba pasando por dentro de la placa en tiempo real. Encontrar el puerto costó un poco (era el `usb14`), pero una vez que se puso la velocidad en `115200` los datos aparecieron en pantalla y todo tuvo más sentido.

---

### El circuito ojito
Se conectó un potenciómetro de **20k Ohm** directo en la protoboard junto a la Raspberry Pi Pico 2 W. Los cables quedaron así:
<table align="center">
  <tr>
    <td align="center">
      <img src="https://github.com/user-attachments/assets/a65e8fb5-8947-4810-99d6-960339fb56eb" width="400"/><br>
      <em>Lo que hicimos.</em>
    </td>
    <td align="center">
      <img src="https://github.com/user-attachments/assets/361c7293-17d5-4364-97af-b0f6e1ab8c94" width="400"/><br>
      <em>Ayuda entregada por el profesor.</em>
    </td>
  </tr>
</table>

- **Rojo → 3.3V (VCC):** Se alimenta con 3.3V. En Arduino se usaban 5V sin drama, pero si le metes eso a la Raspi era un gusto conocerla, se quema.
- **Negro → GND:** La tierra, siempre tiene que estar bien conectada o el sensor empieza a tirar valores nada que ver.
- **Amarillo → ADC0 (pin 31):** El pin que traduce el movimiento físico del potenciómetro (girar la ruleta) en números digitales que el código puede leer.

---

### Lo que pasó en la práctica

Al momento de correr el código en VS Code saltó este error:

```
ModuleNotFoundError: No module named 'board'
```

El problema era que VS Code estaba corriendo el archivo en el computador, no en la Raspberry. Los módulos como `board`, `analogio` o `wifi` son propios de CircuitPython y no existen en Python normal, solo funcionan si el código está dentro de la placa. La solución fue asegurarse de que el archivo `code.py` estuviera guardado directamente en la Raspberry (que aparece como pendrive) y no en el escritorio del computador.
<img width="1000" height="331" alt="image" src="https://github.com/user-attachments/assets/6cc926ad-92d3-4178-82d8-b994719b1f95" />

---

### El código el loop infinito

El código usa `while True:`, que es básicamente el mismo loop de siempre pero con onda Python. Se dejó configurado con un `time.sleep(5)` para que mande la info a Adafruit cada 5 segundos. Así se mantiene la paz con el servidor y no te bloquean por intensas.
```python
import time
import board
import analogio
import wifi
import socketpool
import adafruit_minimqtt.adafruit_minimqtt as MQTT

# WiFi
wifi.radio.connect("NOMBREWIFI", "CLAVEWIFI")

# MQTT
pool = socketpool.SocketPool(wifi.radio)

mqtt = MQTT.MQTT(
    broker="io.adafruit.com",
    username="TU_USUARIO",
    password="TU_KEY_OCULTA",  
    socket_pool=pool,
)

mqtt.connect()

# Potentiometer
pot = analogio.AnalogIn(board.A0)

while True:

    # Mapeamos el valor
    # de 16 bits a 10 bits
    # para obtener valores entre 0 y 1023
    value = pot.value * 1023 // 65535

    print(value)

    # Publicamos al feed de Adafruit
    mqtt.publish(
        "TU_USUARIO/feeds/potenciometro",
        str(value)
    )

    # Espera de 5 segundos
    # para no saturar el servidor
    time.sleep(5)
```
**Demostración de como deben ir las carpetas**

<img width="555" height="238" alt="image" src="https://github.com/user-attachments/assets/52bbf32d-0712-437e-aa7a-802a3347f085" />

### 📂 La arquitectura de carpetas 

No basta con tirar el código a la placa, la Raspberry Pi Pico es súper ordenada y necesita que los archivos estén en su lugar para no "marearse". Aprendí que la estructura interna debe ser así:

  * **Carpeta lib:** Es como la mochila de herramientas de la placa. Dentro de ella tenemos que copiar sí o sí las bibliotecas que descargamos:
       - La carpeta adafruit_minimqtt (que controla la charla con Adafruit).
       - Los archivos .mpy como adafruit_connection_manager.mpy y adafruit_ticks.mpy.
       - Ojo aquí: Si dejas estos archivos sueltos fuera de la carpeta lib, la Raspberry no los encuentra y el código simplemente no parte.

* **Archivo code.py:** Algo que me llamó la atención es que la Raspberry es súper estricta con los nombres. El archivo principal tiene que llamarse code.py. Es como su señal de 'play' automática, si le pones cualquier otro nombre, la placa no sabe por dónde empezar y no corre el código.

* **El flujo de trabajo:** Lo que más me gustó es que la Raspberry se comporta como un pendrive. Para actualizar el programa, solo guardas los cambios en el archivo code.py dentro de la placa y ¡pum!, se reinicia sola y aplica los cambios enseguida. 
---

### Tip

No estresarse con los nombres de los pines. En la Raspberry se llaman distinto (como `ADC0`) pero la lógica es exactamente la misma que antes: captar una señal y mandarla a la nube para que alguien o algo la lea del otro lado. Y si aparece un `ModuleNotFoundError`, lo primero que reviso es dónde está guardado el archivo.

### Investigación propia para entender mejor el funcionamiento de las placas y componentes con los que estamos trabajando :)
<img width="575" height="350" alt="image" src="https://github.com/user-attachments/assets/a3443ef5-9928-4284-afdd-db3b82eb1fbd" />
<img width="575" height="350" alt="image" src="https://github.com/user-attachments/assets/702d5e0b-3f5d-4da4-a2be-971edb36f12b" />
<img width="575" height="350" alt="image" src="https://github.com/user-attachments/assets/07f10c4f-152f-40ae-bd36-460fce06794a" />
<img width="575" height="350" alt="image" src="https://github.com/user-attachments/assets/b2da2288-1a3d-492d-81ef-57279d7ea9a1" />
<img width="575" height="350" alt="image" src="https://github.com/user-attachments/assets/a833d2ca-3ba9-4930-a073-cc221e6d1665" />

---
 ### Resumen

Para que este proyecto no fuera solo "conectar y rezar", me metí a la documentación oficial y estas son mis 3 conclusiones clave:

* **Hardware Protegido (Datasheet):** Entendí que la Raspberry es más delicada que el Arduino. Los pines ADC (del 26 al 29) solo aguantan hasta 3.3V. Pasarse de eso es sentencia de muerte para la placa, por eso la alimentamos con cuidado y usamos resistencias.
* **Software Optimizado (.mpy):** No usamos archivos .py comunes porque los .mpy están comprimidos. Ocupan menos espacio y hacen que la placa corra el código mucho más rápido, lo cual es clave cuando estamos mandando datos por WiFi.
* **Base Confiable (Ejemplos):** El código no salió de la nada. Usamos la carpeta examples de Adafruit como mapa. Aprendí que usar bibliotecas oficiales y ejemplos probados es la mejor forma de asegurar que la conexión MQTT con la nube sea estable y no se caiga.

Al grano: Respetar los 3.3V, mantener el orden en la carpeta lib y usar las versiones de bibliotecas que calzaran justo con nuestro sistema.


### Referencias

- [Introducción a Raspberry Pi Pico 2 W](https://cursos.mcielectronics.cl/2025/08/12/introduccion-a-raspberry-pi-pico-2-y-pico-2-w/)
- [Pinout oficial Raspberry Pi Pico 2 W](https://datasheets.raspberrypi.com/picow/pico-2-w-datasheet.pdf)
- [CircuitPython: Beginner's Guide](https://circuitpython.org/)
- [Adafruit IO con CircuitPython](https://learn.adafruit.com/welcome-to-circuitpython/circuitpython-libraries)
- [Bibliotecas de Adafruit para CircuitPython](https://circuitpython.org/libraries)

