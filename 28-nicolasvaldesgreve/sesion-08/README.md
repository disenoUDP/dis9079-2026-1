# sesion-08

# Apuntes clase 27/04

dato de gente bacán: chico maker

#### Punteo sobre datos de Python!!

- Guido Van Rossum es el creador del idioma Python
- En Python los espacios importan, no son al azar. Escribes menos, pero de manera más estricta. Python es para los computadores más rápidos
- Micropython -> CircuitPython (Es un fork del original, básicamente un nieto de micropython), auspiciado por Adafruit!!

---

Vamos a usar circuit python 10.2.0 e inyectarla a nuestra raspberry pi pico 2 w para poder transformarla.

### Momento dramático de la clase

Para que aparezca la placa como disco duro, hay que mentener presionado el botón de nuestra raspberry pi pico 2 w, conectarlo al cable que está unido a nuestro computador y soltar el botón. Luego de hacer eso, nos va a aparecer el disco duro en nuestro computador, por lo que hay que abrirlo y arrastrar el archivo que descargamos llamado ``adafruit-circuitpython-raspberry_pi_pico2_w-es-10.2.0.uf2`` dentro del disco duro, lo cual hará que éste desaparezca y vuelva a aparecer con un nuevo nombre.

Dentro de CircuitPython seguir el siguiente orden:

Circuit Python -> Get started -> Latest version of PuTTY -> Descargar la última versión de PuTTY -> Abrir PuTTY

Dentro de putty, hay que cambiar el tipo de conexión a ``serial``, el port a 115200 y el host name al com en donde se encuentra nuestra raspberry pi pico 2 w (cosa que podemos revisar en Arduino IDE). Para cortar el código, hay que hacer ``ctrl + c``, y si no funciona, entonces hacemos ``ctrl + d``.

---

### Datos de los microcontroladores

- El Arduino UNO R4 WiFi tiene 5.0v de voltaje, y utilizaremos este para mover el motor servo ya que éste es un poco mañoso.
- El standart de voltaje en microcontroladores ahora es de 3.3!! para que no gasten tanta energía, razón por la que usaremos el motor servo en la Raspberry ya que esta tiene 3.3v.
- Los pines ADC de la Raspberry son un conversor análogo-digital (es como el pin A0 del arduino)

#### Diferencias entre Python y C++

| Python | C++ |
|--- | --- |
| import | include |
| (#) | (//) |
