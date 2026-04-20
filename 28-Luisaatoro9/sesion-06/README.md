# sesion-06 - lunes 13 abril 2026

Hoy dejamos de lado la pantalla y nos enfocamos en el **hardware puro: sensores capacitivos**.  
Aprendimos cómo el **Arduino R4 WiFi** puede detectar la presencia de un objeto conductor (como nuestro dedo) sin necesidad de un botón mecánico, usando el principio de la **capacitancia**.

---

### Conceptos Clave: Capacitancia

- **Capacitor / Condensador:**  
  Es un componente que almacena energía en forma de carga eléctrica.

- **Capacitive Touch:**  
  Tecnología que detecta cambios en la capacitancia.  
  Lo usamos en el día a día en las pantallas de los celulares.

- **Referente Musical: Theremin**  
  Es un instrumento inventado en 1920 que se toca sin contacto físico, usando antenas que crean un campo electromagnético.  

---

### Desarrollo en Clase (Código)

Revisamos el **Pinout del Arduino R4 Minima/WiFi** para identificar los pines digitales.  
Usamos la biblioteca `Arduino_CapacitiveTouch`.

---

###  Ejemplo 1: Lectura Básica

Configuramos un sensor en el pin `D0`.  
La función `touchButton.begin()` es la que inicializa el hardware.

> **Tip de código:**  
> Si `begin()` devuelve `false`, es porque algo anda mal con la conexión física.

---

###  Ejemplo 2: Calibración (Min y Max)

Para que el sensor sea preciso, aprendimos a **mapear los valores**.

- Usamos variables para guardar:
  - `minLectura`
  - `maxLectura`

- Ajustamos el **threshold (umbral)** para decidir cuándo una señal cuenta como un "toque" real.

Esto permite:
- Evitar falsos positivos  
- Reducir el ruido del ambiente  

## Referencias

* Arduino. (s.f.). *Pinout Arduino UNO R4 WiFi*. https://docs.arduino.cc/resources/pinouts/ABX00087-full-pinout.pdf

* Arduino. (s.f.). *Touch (UNO R4 WiFi)*. https://docs.arduino.cc/tutorials/uno-r4-wifi/touch

* Lemelson-MIT Program. (s.f.). *Leon Theremin*. https://lemelson-mit-edu.translate.goog/resources/leon-theremin

* SparkFun Electronics. (s.f.). *Capacitors*. https://learn.sparkfun.com/tutorials/capacitors/all

