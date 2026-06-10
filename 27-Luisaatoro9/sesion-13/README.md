# sesion-13

lunes 08 junio 2026

# Avance 

### 🧠 El Concepto: La Planta como Nodo Biológico

Hoy definimos que nuestro proyecto no es solo una "traducción sonora", sino un **sistema de bio-monitoreo ambiental**: convertir una planta en un sensor de presencia y actividad para la facultad, **sin usar cámaras**.

> 🌱 **¿Por qué es especial?**
> Aprovechamos la **bio-conductividad**. Las plantas cambian sus micro-voltajes internos según estímulos externos: vibraciones del suelo, ruido ambiental, estática de personas pasando cerca. La planta actúa como una **antena biológica** que "siente" el ritmo de la facultad.

### ⚙️ Arquitectura de Hardware y Justificación

Tuvimos una discusión técnica sobre si usar Raspberry o Arduino. Decidimos por un **sistema híbrido** que aprovecha lo mejor de cada mundo:

| # | Componente | Rol | Justificación |
|---|---|---|---|
| 1 | **Planta + ADS1115** | Captura de señal | ADC de **16 bits** — la Raspberry Pi Pico solo tiene 12 bits, insuficiente para detectar cambios de micro-voltios (μV) |
| 2 | **Arduino UNO R4 WiFi** | Cerebro emisor | WiFi integrado + estabilidad para mantener conexión constante a la red de la facultad |
| 3 | **Raspberry Pi Pico 2 W / PC** | Nodo receptor | Recibe los paquetes inalámbricos y genera la experiencia visual/sonora final |

> [!NOTE]
> Los electrodos irán clavados tanto en el **sustrato** como en las **hojas** de la planta para maximizar la captura de señal.

### 🔁 Flujo Lógico y Seudocódigo Detallado

Diseñamos un flujo que asegura que los datos no se pierdan en el camino.

### Flujo General del Sistema

```
Planta
  ↓
Electrodos
  ↓
ADS1115
  ↓
Arduino UNO R4 WiFi
  ↓
Transmisión WiFi
  ↓
Computador / Raspberry Pi Pico 2 W
  ↓
Procesamiento de datos
  ↓
Visualización y sonido
```

### Lógica del Proyecto

```
1. Capturar señales eléctricas de la planta
2. Convertir señales en datos digitales
3. Transmitir datos de forma inalámbrica
4. Recibir y procesar la información
5. Transformar los datos en imágenes, luces o sonidos
6. Mostrar en tiempo real la actividad detectada por la planta
```

---

### A. Emisor *(Arduino UNO R4 WiFi)*

```
INICIO

  Inicializar ADS1115
  Conectar a la red WiFi

  MIENTRAS el sistema esté activo

    Leer señal eléctrica de la planta
    Convertir lectura analógica a valor digital
    Enviar dato mediante WiFi
    Esperar un breve intervalo

  FIN MIENTRAS

FIN
```

### B. Receptor *(Computador o Raspberry Pi Pico 2 W)*

```
INICIO

  Conectarse a la red WiFi
  Inicializar sistema de visualización

  MIENTRAS el sistema esté activo

    Recibir dato enviado por Arduino
    Analizar intensidad del valor recibido

    SI valor alto ENTONCES
      Aumentar movimiento visual
      Aumentar cantidad de elementos gráficos
      Aumentar intensidad sonora

    SI valor medio ENTONCES
      Mantener comportamiento normal

    SI valor bajo ENTONCES
      Disminuir movimiento visual
      Disminuir cantidad de elementos gráficos
      Disminuir intensidad sonora

    Actualizar visualización

  FIN MIENTRAS

FIN
```

**Visualización Generativa:**

| Estado | Valores | Visual | Sonido |
|---|---|---|---|
| 🔴 **Excitación** | Altos | Movimiento rápido, colores intensos, más elementos gráficos | Agudo y rítmico |
| 🟡 **Normal** | Medios | Comportamiento estable | Sin cambios |
| 🟢 **Calma** | Bajos | Formas orgánicas lentas | Ambiental / suave |


### 🗂️ Plan de Trabajo y Logística *(Acuerdos de Grupo)*

Como esta semana no podemos coincidir físicamente, establecimos una hoja de ruta estricta para llegar con avances a la próxima clase.

### 📦 Gestión de Materiales

| Persona | Tarea |
|---|---|
| **Luisa** *(yo)* | Compra del **ADS1115** — componente crítico, debe estar listo para las primeras pruebas de soldadura y lectura |
| **Compañera** | Traer la planta — buscamos una de **hojas grandes** para mejor conductividad |

### ⚙️ Desarrollo en Paralelo

**Subgrupo A — Código Emisor:**
> Trabajará en la librería del **ADS1115 para Arduino R4**, asegurando que la conexión WiFi sea robusta.

**Subgrupo B — Código Receptor y Visualización:**
> Investigará cómo crear una **página web o interfaz que funcione como API de visualización**, para que los datos de la planta se "dibujen" en tiempo real en la pantalla del PC.

### 💭 Reflexión Técnica

El mayor desafío identificado hoy fue la **abstracción de los datos**. No queremos mostrar solo un gráfico de líneas aburrido; queremos que la visualización se sienta *"viva"*.

> [!IMPORTANT]
> El trabajo de esta semana en buscar **APIs de visualización** es clave para cumplir con el concepto de *"Estudios inalámbricos poéticos"*. La pregunta que guía el diseño no es *¿cómo graficamos el dato?* sino *¿cómo hacemos que el dato se sienta?*

**Tareas pendientes:**

- [ ] Comprar el ADS1115 *(Luisa)*
- [ ] Conseguir planta de hojas grandes
- [ ] Investigar librería ADS1115 para Arduino R4
- [ ] Probar conexión WiFi básica en Arduino UNO R4
- [ ] Explorar APIs / librerías de visualización en tiempo real *(p5.js, D3, Canvas API)*
- [ ] Definir protocolo de red: WebSockets vs HTTP POST
