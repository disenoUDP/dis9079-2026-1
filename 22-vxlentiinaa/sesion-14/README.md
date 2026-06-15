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

