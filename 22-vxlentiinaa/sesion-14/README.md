# sesion-14

lunes 15 junio 2026

---

## Apuntes

### Correciones

**Sensor IR → Raspberry Pi Pico 2W**

|Pin del sensor|Pin de la Pico 2W|
|---|---|
|VCC|3.3V (pin 36)|
|GND|GND (cualquier pin GND)|
|OUT (señal digital)|GP15 (pin 20)|

**Anillo LED WS2812 → Arduino UNO R4 WiFi**

|Pin del anillo|Pin del Arduino|
|---|---|
|VCC (5V)|5V|
|GND|GND|
|DIN (dato)|Pin digital 6|

`Puntos importantes a considerar:`

- Adafruit IO: generar un feed llamado lid-conteo, y obtener mi AIO Username y AIO Key desde la sección "My Key" del dashboard. Reemplazar esos valores en ambos códigos junto con el SSID/contraseña de WiFi.
- Lógica del sensor: el código actual incrementa el contador cada vez que detecta un objeto (cada persona = +1) y reinicia a 0 al llegar a 16. Si quieren un conteo neto real (entradas - salidas), necesitarían dos sensores (uno detectando dirección de entrada, otro de salida) ya que un solo sensor IR no puede distinguir la dirección del movimiento.
- Colores del anillo: verde (1-5 personas), amarillo (6-10), rojo (11-16). Pueden cambiar los rangos o usar un solo color según su mensaje visual.

## Pasos para conectar todo :)

1. Conectar el anillo led al arduino

|Pin del anillo|Pin del Arduino|
|---|---|
|VCC (5V)|5V|
|GND|GND|
|INPUT (dato)|Pin digital 6|

2. Conectar el sensor infrarojo a la Raspberry PI
   
|Pin del sensor|Pin de la Pico 2W|
|---|---|
|VCC|3.3V (pin 36)|
|GND|GND (cualquier pin GND)|
|OUT (señal digital)|GP15 (pin 20)|

3. Mantener presionado el botón `BOOTSEL` de la Pico mientras lo conectamos al Mac por USB.

4. Descargar el archivo *.uf2* de `CircuitPython` para Pico 2W desde su página oficial. 
5. Arrastrar el archivo *.uf2* a la carpeta de la Raspberry desde el Finder.
6. La Pico se reiniciará y aparecerá como una nueva unidad llamada CIRCUITPY.
7. Subir el código UNA vez con Circuit python de la siguiente manera

```bash
# Ver dónde está montada
ls /Volumes/

# Copiar tu código (debe llamarse exactamente "code.py")
cp pico_sensor_entrada.py /Volumes/CIRCUITPY/code.py
```

8. Para instalar la librería adafruit_minimqtt, desde la terminal

```bash
bashcp -r adafruit_minimqtt /Volumes/CIRCUITPY/lib/
```

9. Para ver donde se ubica el usb es:

```bash
# Encuentra el puerto serie
ls /dev/tty.*

# Conéctate (ajusta el nombre del puerto)
screen /dev/tty.usbmodem* 115200
```

10. Para verificar que el archivo esté ahí:

```bash
ls /Volumes/CIRCUITPY/
```

11. Revisar los mensajes (logs) en tiempo real:

```bash
ls /dev/tty.*
```

Y luego buscar algo tipo:

```cpp
screen /dev/tty.usbmodem14201 115200
```

12. Para verificar el nombre exacto del archivo:

- Presionar Ctrl+D para recargar
- Revisa el contenido de CIRCUITPY desde otra terminal (sin cerrar screen, abre una pestaña nueva en Terminal):

```bash
ls -la /Volumes/CIRCUITPY/
ls /Volumes/CIRCUITPY/lib/
```

13. Si queremos ejecutarlo manualmente desde el REPL para ver el error exacto:

```bash
import code
```





