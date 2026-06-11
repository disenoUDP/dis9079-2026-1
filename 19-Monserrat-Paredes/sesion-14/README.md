# sesion-14

lunes 15 junio 2026

Problema que se puede tener: La puerta es bidireccional, registra el dato de una persona más de una vez, si entro y salgo me registre dos veces, cómo si fueran 2 personas. El sensor es "ciego" a la dirección.

Alcance corto -> generalmente entre 2 y 30 cm.

La gente entra y sale por la misma puerta.


# Solución: 

## Opción 1: Aprovecgar el sentido de la puerta 

Colocación en ángulo: En lugar de poner el sensor apuntando recto (90° respecto a la pared), colócalo en un ángulo diagonal de 45° mirando hacia afuera (hacia el pasillo). Alguien que entra activará el sensor de frente, pero alguien que sale pasará por detrás del cono de detección del infrarrojo, reduciendo drásticamente las marcas de salida.

Tip que podría ayudar: Dirección del sensor, usa el potenciómetro pequeño (el tornillo que trae el propio sensor IR) para regular la distancia de detección. No dejes que mida todo el ancho de la puerta; ajústalo para que solo detecte objetos que pasen a un máximo de 15 o 20 cm del sensor. Así, el cambio de dirección física a 45° será sumamente eficiente separando las entradas de las salidas.


## Opción 2: Configurar la Raspberry Pi Pico 2W (mejor solución segun gemini)

Para que cada pasada cuente como un único "movimiento", se puede hacer que la base de datos o el Arduino UNO R4 divida el total de detecciones por 2.

Si el sensor detecta 20 movimientos en total (entre entradas y salidas) durante la hora de almuerzo, tu código asume que el flujo real de ocupación aumentó en 10 personas. Para un proyecto que busca mostrar el ritmo y las fluctuaciones, este margen de aproximación funciona bastante bien.

Para asegurar que una sola persona no marque dos veces seguidas al cruzar, necesitas implementar el delay inteligente en el código de tu Pico (usualmente programada en MicroPython). Este script usa un bloqueo de 2 segundos:

Para que cualquiera de las dos opciones de dirección funcione, necesitas este código en tu Pico. Incluye un tiempo de bloqueo personalizable (lo ideal para este flujo es configurarlo entre 2.0 y 3.0 segundos) para asegurar que, tras la detección inicial en la dirección correcta, el sensor ignore el resto del paso de la persona.


El código para tu Raspberry Pi Pico 2W:

```cpp
import machine
import time

# Configuración del pin del sensor (ajusta el número de pin GP según tu circuito)
PIN_SENSOR = 2  
sensor = machine.Pin(PIN_SENSOR, machine.Pin.IN, machine.Pin.PULL_UP)

contador_entradas = 0
ultimo_registro = 0

# TIEMPO DE BLOQUEO (En segundos):
# Ajusta este tiempo según lo que tarda una persona en terminar de pasar la puerta.
TIEMPO_BLOQUEO = 2.5  

print("--- Puente Digital: Conteo de Entradas LID ---")

while True:
    # Los sensores evasores de obstáculos FC-51 entregan 0 (LOW) al detectar presencia
    if sensor.value() == 0:
        tiempo_actual = time.time()
        
        # Filtro de delay inteligente: Solo cuenta si pasó el tiempo de bloqueo
        if (tiempo_actual - ultimo_registro) >= TIEMPO_BLOQUEO:
            contador_entradas += 1
            print(f"[NUEVA ENTRADA] Total personas en LID: {contador_entradas}")
            
            # --- AQUÍ CONECTAS TU ENVÍO A LA API / ADAFRUIT IO ---
            # Ejemplo: enviar_dato_wifi(contador_entradas)
            # -----------------------------------------------------
            
            # Registra el momento exacto de la entrada para activar la "ceguera"
            ultimo_registro = tiempo_actual
            
    # Pequeño delay de estabilidad para evitar que el bucle sature el procesador
    time.sleep(0.05)
```

## Opción 3: Cambiar de conteo numérico -> Métrica de intensidad o pulso

Torniquete -> termómetro que mide la vitalidad del LID (en tiempo real, flujo constante)

Cada vez que el sensor del LID detecta un paso (sea entrada o salida), manda un pulso. Si hay muchos pulsos seguidos, el anillo LED se enciende rápido y cambia a colores cálidos/alerta (el espacio está "hirviendo" de movimiento). Si nadie pasa, el anillo se va apagando lentamente. Esto calza perfecto con la idea de mostrar el "ritmo" y el desborde del lugar.

Ejemplo del funcionamiento del anillo led:

- 0% de Energía: Sala en calma. El anillo está apagado o en un azul/verde muy tenue.

- 50% de Energía: Flujo constante. El anillo se llena hasta la mitad con colores amarillos y naranjas.

- 100% de Energía: ¡LID desbordado! Las 16 luces del anillo brillan intensamente en color rojo vivo o parpadean.


Código para el Arduino UNO R4 WiFi:

```cpp
#include <Adafruit_NeoPixel.h>

#define PIN_NEOPIXEL  6   // Pin de datos conectado al anillo LED
#define NUM_LEDS      16  // Tu anillo de 16 LEDs

Adafruit_NeoPixel anillo(NUM_LEDS, PIN_NEOPIXEL, NEO_GRB + KHZ800);

int pulsosAnteriores = 0;
int pulsosActuales = 0; // Este valor lo debes actualizar con lo que recibas por Wi-Fi

float energia = 0.0;           // Nivel de energía actual de la sala (0 a 100)
float tasaDesgaste = 0.15;     // Qué tan rápido se enfría la sala (ajustable)
unsigned long ultimoTiempo = 0;

void setup() {
  anillo.begin();
  anillo.show(); // Inicializa todos los LEDs apagados
  Serial.begin(9600);
}

void loop() {
  // --- SIMULACIÓN DE RECEPCIÓN WI-FI ---
  // Aquí debes integrar tu código que lee desde Adafruit/API y actualiza 'pulsosActuales'
  // -------------------------------------

  // 1. Monitorear si llegaron nuevos pulsos desde el LID
  if (pulsosActuales > pulsosAnteriores) {
    int nuevosPulsos = pulsosActuales - pulsosAnteriores;
    
    // Cada pulso nuevo inyecta 25 unidades de energía
    energia = energia + (nuevosPulsos * 25.0); 
    if (energia > 100.0) energia = 100.0; // Límite máximo
    
    pulsosAnteriores = pulsosActuales;
  }

  // 2. Lógica de Desgaste (Enfriamiento constante del espacio)
  if (millis() - ultimoTiempo >= 50) { // Se ejecuta cada 50 milisegundos
    ultimoTiempo = millis();
    
    if (energia > 0.0) {
      energia = energia - tasaDesgaste;
    } else {
      energia = 0.0;
    }
    
    // 3. Actualizar la visualización del anillo LED según la energía
    actualizarAnillo(energia);
  }
}

void actualizarAnillo(float nivelEnergia) {
  // Calculamos cuántos LEDs se deben encender (de 0 a 16)
  int ledsPrendidos = map(nivelEnergia, 0, 100, 0, NUM_LEDS);
  
  // Definir color según la temperatura de la energía
  uint32_t colorActual;
  
  if (nivelEnergia < 35.0) {
    colorActual = anillo.Color(0, 255, 100);   // Verde/Cian: Sala calmada, ritmo lento
  } else if (nivelEnergia < 75.0) {
    colorActual = anillo.Color(255, 130, 0);   // Naranja: Ritmo constante, ocupación media
  } else {
    colorActual = anillo.Color(255, 0, 0);     // Rojo: ¡Desborde, movimiento intenso!
  }

  // Encender los LEDs que correspondan
  for (int i = 0; i < NUM_LEDS; i++) {
    if (i < ledsPrendidos) {
      anillo.setPixelColor(i, colorActual);
    } else {
      anillo.setPixelColor(i, anillo.Color(0, 0, 0)); // Apagar el resto
    }
  }
  anillo.show();
}
```

Resultado visual: Si el LID está vacío, el anillo estará completamente apagado. Si entra un grupo de 3 personas seguidas, el anillo se encenderá de golpe hasta la mitad en color naranja. Si el flujo se detiene, se vera cómo los LEDs se van apagando uno a uno, como un eco que se desvanece, reflejando que el ritmo bajó. Si la sala se llena por completo de eventos, los 16 LEDs brillarán en un rojo intenso estático.

# Opción 4: Agregar el segundo Sensor Infrarrojo

Agregar un segundo sensor idéntico resuelve esto de forma limpia, económica y sin alterar la puerta. Anillo de LEDs en la FADD pretende mostrar qué tan "lleno" o "desbordado" está el LID, necesitas calcular el aforo neto 

Gente adentro = Entradas - Salidas.

Para que el sistema funcione, los dos sensores deben instalarse en fila (en serie), siguiendo la línea de la dirección en la que camina la gente.

Los llamaremos Sensor A (Exterior / Pasillo) y Sensor B (Interior / LID).


PASILLO (Exterior)
---------------------------------

       [ Sensor A ]  <-- Lado Pasillo
         |  10-15 cm de distancia
       [ Sensor B ]  <-- Lado LID
       
---------------------------------
   INTERIOR DEL LID


   Requisitos:
   
- Distancia entre sensores (10 a 15 cm).

- Altura de montaje (1.10 a 1.20 metros - Altura de la cadera/torso).

- Calibración del rango (Con el potenciómetro): Los sensores traen un pequeño tornillo. Ajústalos para que solo detecten objetos a una distancia de 20 a 30 cm.


[LID: Paso de persona] 
   --> Si activa A primero y luego B = ENTRADA (+1)
   --> Si activa B primero y luego A = SALIDA (-1)
   --> Raspberry Pi Pico 2W calcula: Aforo_Neto
   
[Internet]
   --> Pico 2W sube el valor "Aforo_Neto" por Wi-Fi a Adafruit IO o tu API.

[FADD: Rep180]
   --> El Arduino UNO R4 WiFi descarga el valor "Aforo_Neto" desde internet.
   --> Mapea ese número (ej. de 0 a 30 personas) en tus 16 LEDs del anillo.


Si el aforo es 0, el anillo en la FADD está apagado. Si el aforo sube a 15, el anillo se enciende hasta la mitad. Si hay un evento en el LID y entra mucha gente, el anillo se completará y brillará por completo en República 180, alertando del "desborde".
       


## Investigación sobre Apis

Información sacada de: 

https://openweathermap.org/api

https://www.ibm.com/es-es/think/topics/api

