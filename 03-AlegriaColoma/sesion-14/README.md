# sesion-14

lunes 15 junio 2026

## Desarrollo examen

### ¿Qué hace nuestro semáforo?

Es un sistema que detecta cuántas personas entran/salen de la Sala Alpha (sala de computación pública de la universidad Diego Portales) mediante dos botones en un Arduino UNO R4 WiFi, y muestra la ocupación de la sala en un semáforo remoto conectado a una Raspberry Pi Pico 2 W, comunicados a través de Adafruit IO.

### Materiales 

* Arduino UNO R4 WiFi (Edificio A — botones)
* Raspberry Pi Pico 2 W (Edificio B — semáforo)
* 2 botones
* 1 módulo semáforo RGB (con pines GND, R, Y, G integrados, no necesita resistencias extra)
* Protoboards y cables jumper
* Resistencias de 10kΩ 

### Proceso 

Creamos un feed en Adafruit IO llamado ```pruebasemaforo```, posteriormente pasamos a el desarrollo de códigos en con ayuda de la IA.

#### Proceso Raspberry Pi Pico 2 w 

Como primer problema, la placa no se conectaba al WiFi. Se probó con distintos hotspots y ninguno dio resultados. Sin embargo, durante un momento creemos que sí logró conectarse a uno de ellos. No obstante, al volver a intentarlo con el teléfono de mi compañera, nuevamente no se conectaba.

Al revisar el monitor serial, cuya instalación nos ayudó a realizar una compañera, nos dimos cuenta de que el código que estábamos utilizando no estaba ejecutando ninguna función. Esto se debía a que el código inicial estaba escrito en MicroPython, mientras que la placa tenía instalado CircuitPython. Finalmente, se reescribió todo el código en CircuitPython.

Procedimos con la conexion del cableado y moódulo de semáforo: GP16→G, GP17→Y, GP18→R, GND→GND.

Segundo problema, la Pico recibía bien los valores de Adafruit IO, pero ningún LED encendía.

Se probó un código simple LED por LED, descartando errores de código. Se probó conectar un cable directo a 3.3V → tampoco prendía → se sospechó del GND y el cable de GND no estaba bien conectado. Al corregirlo, los 3 LEDs (verde, amarillo, rojo) parpadearon correctamente con un código de prueba simple.

*Aún pendiente: probar el código completo (con conexión a Adafruit IO) ahora que el hardware del semáforo funciona.*

Parámetros del semáforo 

- 0-5 personas → 🟢 Verde
- 6-10 personas → 🟡 Amarillo
- 11+ personas → 🔴 Rojo

#### Proceso Arduino UNO R4 WiFI

Conexión de cableado y botones con pull-down** (resistencia a GND, botón a 5 V)

Primer problema, necesitábamos hacer que el Arduino se conectara al hotspot de un iPhone, pero no lo lograba. Por lo que averiguamos, una posible causa era que los iPhone comparten la conexión en 5 GHz, mientras que las placas se conectan en 2,4 GHz. Por ello, procedimos a activar la opción **"Maximizar compatibilidad"** en el teléfono.

Segundo problema (aún sin resolver), el contador se actualiza si se conecta o desconecta el cable manualmente, pero no responde al presionar el botón físico. Al mover el Arduino, los valores fluctúan por sí solos (señal "flotante"), lo que indica que el circuito de pull-down no está cerrando correctamente hacia GND, aunque se revisó la disposición del circuito (A3 conectado a D2, B3 con una resistencia de 10 kΩ, C3 y E3 con las patitas del botón, y A8 conectado al riel positivo) y parecía estar correcta.

Por lo tanto, este problema se mantiene activo y sin resolver.

<img width="610" height="350" alt="image" src="https://github.com/user-attachments/assets/3775a569-6400-44fe-b34b-5b121efba16b" />


