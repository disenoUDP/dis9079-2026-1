# sesion-11

lunes 25 mayo 2026

---

domingo, 24 de mayo 

**Correcciones de la solemne 2 (revisar mañana lunes)**

imagenes:

- imagen pote: (Imagen de: https://afel.cl/products/potenciometro-500k-ohm?_pos=4&_psq=pote&_ss=e&_v=1.0)
- imagen servo: (Imagen de: https://afel.cl/products/micro-servomotor-sg90)
- imagen andy: Imagen sacada por nosotras

Producto con potenciómetro:

Teenage engineering - TX-6

Potenciómetro rotativo
Resistencia variable mecánica usada como sensor de posición angular. En el TX-6 hay 18 distribuidos en 6 canales estéreo, cada uno configurable a un parámetro de audio distinto.

1. Cómo funciona el sensor
Un potenciómetro rotativo es un divisor de tensión variable. Tiene tres terminales: dos extremos conectados a Vcc y GND, y un tercer terminal central llamado wiper (escobilla) que recorre una pista resistiva al girar el eje. La posición angular del eje determina qué fracción del voltaje de referencia aparece en el wiper.

2. Filtrado de la señal
Un potenciómetro analógico sin filtrar produce valores ruidosos: pequeñas variaciones eléctricas, vibración mecánica del eje, o simplemente la rugosidad de la pista resistiva. En equipos de audio como el TX-6, esto se resuelve en dos capas.

3. Visualización de datos
¿Cómo se ve la señal cruda de un potenciómetro? A continuación, tres tipos de lectura típicos en un microcontrolador con ADC de 10 bits (rango 0–1023).

### [Teenage Engineering](https://teenage.engineering)

*Potenciómetro rotativo:* Resistencia variable mecánica usada como sensor de posición angular. En el TX-6 hay 18 distribuidos en 6 canales estéreo, cada uno configurable a un parámetro de audio distinto.

1. **Cómo funciona el sensor**
Un potenciómetro rotativo es un divisor de tensión variable. Tiene tres terminales: dos extremos conectados a Vcc y GND, y un tercer terminal central llamado wiper (escobilla) que recorre una pista resistiva al girar el eje. La posición angular del eje determina qué fracción del voltaje de referencia aparece en el wiper.

En TX-6: Tiene 18 potenciómetros rotativos. Alimentados a Vcc interna, el wiper va al ADC del procesador. Resolución suficiente para 128 pasos MIDI (7 bit) o más fino según firmware.

2. **Filtrado de la señal**
Un potenciómetro analógico sin filtrar produce valores ruidosos: pequeñas variaciones eléctricas, vibración mecánica del eje, o simplemente la rugosidad de la pista resistiva. En equipos de audio como el TX-6, esto se resuelve en dos capas.

El filtrado de software es en base a: EMA — Exponential Moving Average

El firmware promedia los valores ADC en el tiempo. Cada nueva lectura se mezcla con el valor anterior según un factor α. Un α alto = respuesta rápida pero más ruido. α bajo = respuesta suave pero lenta.

En mezcladores como el TX-6 también se aplica detección de umbral: solo se reporta un cambio si el nuevo valor supera ±N pasos del anterior, evitando una inestabilidad en la posición estacionaria (jitter).

3. **Visualización de datos**
¿Cómo se ve el valor crudo de un potenciómetro? A continuación, tres tipos de lectura típicos en un microcontrolador con ADC de 10 bits (rango 0–1023).

4. **Problemas comunes**

- Pot "rascoso" (scratchy): Al girar el knob se escuchan crujidos o chasquidos.
  - Causa: oxidación o desgaste de la pista resistiva de carbono. El wiper (terminal central) pierde contacto suave y genera microinterrupciones.
  - Solución temporal: limpiador de contactos (DeoxIT).
  - Solución definitiva: reemplazo del potenciómetro.
- Jitter (inestabilidad en reposo): El valor ADC fluctúa, aumentando pasos aunque no se toque el knob.
  - Causa: ruido eléctrico del entorno, resolución del ADC, o impedancia alta del wiper.
  - Solución: filtro RC en hardware + umbral mínimo de cambio en firmware.
- Problema de rango al inicio/fin de recorrido: Los potenciómetros físicos raramente llegan al 0% o 100% exacto de Vcc en sus extremos. El firmware debe calibrar y mapear el rango real de lectura al rango deseado de parámetros, evitando zonas muertas en los extremos.

En conclusión, la distinción más crítica para el TX-6 es que sus 18 knobs son potenciómetros con inicio y fin de recorrido (no encoders). Eso significa que siempre tienen una posición absoluta, lo que es ideal para un mezclador: al encenderlo, el firmware puede leer inmediatamente en qué posición está cada knob sin necesidad de "inicialización".
