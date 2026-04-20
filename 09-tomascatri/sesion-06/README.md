# sesion-06

lunes 13 abril 2026

## Apuntes

### Sensor de capatitancia

* la capacidad depende del material y el area
* No necesariamente tienen que ser 2 metales puede ser carne human y el capacitor actuará
* Como los dispositivos touch screen

### Arduino UNO R4 WiFi

* Es posible hacer que con una mano dependiendo de la distancia de la mano con el sensor cambien valores del arduino.
* Casi todas las patitas del arduino tienen diferentes funciones
* Arduino tiene una pantallita y abajo esta power donde se le puede dar potencia o prender

**Para hacerlo necesitamos:**

* cualquierr cable
* algo que afecte al campo electromagnetico

Ejemplo del codigo y como funciona en el arduino

* Añadir libreria de CapacitiveTouch arduino
* **CapacitiveTouch(uint8_t pin)** Constructs a capacitive touch sensor for the given pin.
* **bool begin()** Initializes the sensor and configures the pin and hardware.
* **int read()** Reads the raw sensor value and returns it.
* **bool isTouched()** Checks if the sensor is touched based on the threshold.
* **void setThreshold(int threshold)** Sets the detection threshold for touch sensitivity.
* **int getThreshold()** Retrieves the current detection threshold.
* El ejemplo dice conectar el sensor al D0
* Actualizar valores maximos y minimos

### stylophone

* STYLOPHONE S1
* Theremin usa antenas para producir sonidos,mas lejos la mano suena mas el volumen, si lo toca se apaga con la otra antena vertical se detecta la distancia y con eso oscila las notas, hay un chileno que usa esto llamado martin benavides
![Gato usando theremin](./imagenes/cat_plays_theremin.gif)
