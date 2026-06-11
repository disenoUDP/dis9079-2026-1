# sesion-14

lunes 15 junio 2026

Problema que se puede tener: La puerta es bidireccional, registra el dato de una persona más de una vez, si entro y salgo me registre dos veces, cómo si fueran 2 personas. El sensor es "ciego" a la dirección.

Alcance corto -> generalmente entre 2 y 30 cm.

La gente entra y sale por la misma puerta.


## Solución: 

# Opción 1: Aprovecgar el sentido de la puerta 

Colocación en ángulo: En lugar de poner el sensor apuntando recto (90° respecto a la pared), colócalo en un ángulo diagonal de 45° mirando hacia afuera (hacia el pasillo). Alguien que entra activará el sensor de frente, pero alguien que sale pasará por detrás del cono de detección del infrarrojo, reduciendo drásticamente las marcas de salida.

Tip que podría ayudar: Dirección del sensor, usa el potenciómetro pequeño (el tornillo que trae el propio sensor IR) para regular la distancia de detección. No dejes que mida todo el ancho de la puerta; ajústalo para que solo detecte objetos que pasen a un máximo de 15 o 20 cm del sensor. Así, el cambio de dirección física a 45° será sumamente eficiente separando las entradas de las salidas.


# Opción 2: Configurar la Raspberry Pi Pico 2W (mejor solución segun gemini)

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
´´´
Investigación sobre Apis
