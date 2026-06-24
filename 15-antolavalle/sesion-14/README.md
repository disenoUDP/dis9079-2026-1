# sesion-14

lunes 15 junio 2026

# Semáforo de Ocupación — Sala Alpha

## ¿Qué hace?

Dos botones en un Arduino cuentan personas que entran/salen de la Sala Alpha. Según el contador, una Raspberry Pi Pico 2 W prende un LED de semáforo. Todo se comunica por WiFi usando Adafruit IO (MQTT).

| Personas | Color |
|----------|-------|
| 0–5 | 🟢 Verde |
| 6–10 | 🟡 Amarillo |
| 11+ | 🔴 Rojo |

---

## Materiales

- Arduino UNO R4 WiFi → Edificio A (botones)
- Raspberry Pi Pico 2 W → Edificio B (semáforo)
- 2 botones pulsadores
- Módulo semáforo RGB (trae GND, R, Y, G integrados, no necesita resistencias extra)
- Protoboards y jumpers
- Resistencias de 10 kΩ

---

## Tipos de conexión de botones

Sin una resistencia que ancle el pin a HIGH o LOW, el pin queda **flotante** y lee basura. Hay varias formas de evitarlo:

### Pull-Down (la que usamos primero)

```
VCC ──[Botón]──┬── Pin
               │
             [10kΩ]
               │
              GND
```

- Botón suelto → LOW. Botón presionado → HIGH
- Lógica directa e intuitiva
- **Problema:** si el GND no está bien conectado, el pin flota igual (nos pasó)

### Pull-Up externo

```
VCC ──[10kΩ]──┬── Pin
              │
           [Botón]
              │
             GND
```

- Botón suelto → HIGH. Botón presionado → LOW (lógica invertida)
- Más robusto ante ruido que el pull-down

### Pull-Up interno (`INPUT_PULLUP`)

Sin resistencias externas. El Arduino tiene una resistencia interna de ~20–50 kΩ que se activa por software:

```cpp
pinMode(PIN, INPUT_PULLUP);
```

- Botón presionado → LOW (lógica invertida)
- La más simple: solo un cable del botón al pin y otro a GND
- No funciona bien con cables muy largos (resistencia interna demasiado alta)
- **Esta es la que terminamos usando en el código final**

### Schmitt Trigger

Usa un comparador con histéresis (ej: CI 74HC14). El pin solo cambia de estado cuando la señal cruza un umbral, lo que elimina el rebote por hardware.

- Útil en cables largos o entornos muy ruidosos
- Requiere componentes adicionales

### Optoacoplador

Transmite la señal con luz (LED IR + fototransistor). Aísla eléctricamente el botón del microcontrolador.

- Útil cuando el botón y la placa operan a tensiones distintas
- Más caro y complejo

### Comparativa rápida

| Tipo | Lógica | Componentes extra | Cuándo usarlo |
|------|--------|-------------------|---------------|
| Pull-Down | HIGH = presionado | Resistencia externa | Prototipado con 5V |
| Pull-Up externo | LOW = presionado | Resistencia externa | Más robusto ante ruido |
| Pull-Up interno | LOW = presionado | Ninguno | La opción más simple |
| Schmitt Trigger | Depende | CI adicional | Ruido extremo o cables largos |
| Optoacoplador | Depende | CI + circuito | Diferentes tensiones/tierras |

### Debouncing

Los botones mecánicos "rebotan" al presionarse y generan varios pulsos en vez de uno. Se soluciona de dos formas:

- **Hardware:** condensador de 100 nF en paralelo con el botón, o Schmitt Trigger
- **Software:** ignorar cambios durante ~50 ms tras detectar el primer flanco (lo que usamos)

---

## Arduino UNO R4 WiFi

### Cableado (pull-down, versión 1)

| Componente | Pin Arduino | Notas |
|------------|-------------|-------|
| Botón SUMA | D2 | Resistencia 10 kΩ de D2 a GND |
| Botón RESTA | D3 | Resistencia 10 kΩ de D3 a GND |
| GND | GND | Riel negativo de la protoboard |
| 5V | 5V | Riel positivo de la protoboard |

### Cableado (INPUT_PULLUP, versión 2)

Mucho más simple. Sin resistencias:
- Un pin del botón → D2 o D3
- El otro pin → GND

### Librerías

- `Adafruit MQTT Library`
- `WiFiS3` (viene incluida con el paquete Arduino R4)

### Lógica

1. Conectar al WiFi y al broker MQTT de Adafruit IO
2. Leer D2 y D3 buscando flancos (HIGH→LOW con INPUT_PULLUP)
3. Flanco en SUMA → contador +1
4. Flanco en RESTA → contador -1 (mínimo 0)
5. Publicar el nuevo valor en el feed `contador` de Adafruit IO

### Problemas

**iPhone solo comparte en 5 GHz**
El Arduino solo soporta 2,4 GHz. El hotspot de iPhone por defecto usa 5 GHz.
→ Solución: activar "Maximizar compatibilidad" en el hotspot del iPhone.

**Botones no respondían (señal flotante)**
El contador cambiaba solo al mover el Arduino pero no al presionar los botones.
→ Causa probable: el GND del circuito pull-down no estaba bien conectado.
→ Estado: resuelto migrando a `INPUT_PULLUP`.

---

## Raspberry Pi Pico 2 W

### Cableado del módulo semáforo

| Pin Pico | Pin módulo | LED |
|----------|------------|-----|
| GP16 | G | Verde |
| GP17 | Y | Amarillo |
| GP18 | R | Rojo |
| GND | GND | — |

El módulo ya trae resistencias integradas, no se necesitan externas.

### CircuitPython vs MicroPython

La Pico tenía instalado CircuitPython pero el código inicial estaba en MicroPython → no ejecutaba nada. Se reescribió todo en CircuitPython.

### Lógica

1. Conectar al WiFi
2. Suscribirse al feed de Adafruit IO
3. Al recibir un valor:
   - 0–5 → enciende GP16 (verde)
   - 6–10 → enciende GP17 (amarillo)
   - ≥11 → enciende GP18 (rojo)

### Problemas

**Pico no conectaba al WiFi**
Se probaron varios hotspots sin éxito.
→ El problema real era el conflicto MicroPython/CircuitPython. Al corregir el código, la conexión debería funcionar.

**LEDs no encendían aunque recibía datos**
Se probaron los LEDs uno por uno con código simple. Tampoco encendían conectando directo a 3.3V.
→ Causa: el cable de GND del módulo semáforo no estaba bien insertado en la protoboard.
→ Solución: corregir la conexión de GND. Los tres LEDs funcionaron correctamente.
→ Pendiente: probar el código completo con Adafruit IO conectado.

---

## Arquitectura general

```
[Botón SUMA/RESTA]
       │
[Arduino UNO R4 WiFi]
       │ MQTT / WiFi
[Adafruit IO (nube)]
       │ MQTT / WiFi
[Raspberry Pi Pico 2 W]
       │
[Módulo semáforo 🟢🟡🔴]
```

Los dos edificios se comunican solo por internet, sin cables físicos entre ellos.

---

## Estado actual

### Listo
- Feed creado en Adafruit IO
- Hardware del semáforo verificado (los 3 LEDs funcionan)
- Código CircuitPython de la Pico reescrito
- Conexión WiFi del Arduino resuelta
- Botones funcionando con INPUT_PULLUP

### Pendiente
- Probar código completo de la Pico con Adafruit IO en vivo
- Prueba de integración end-to-end: botón en Arduino → semáforo en Pico
