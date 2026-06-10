# sesion-12

lunes 01 junio 2026

# Explicación del examen 

### 📋 Introducción y Explicación del Examen

Hoy se presentó el **examen final**: *Estudios inalámbricos poéticos*. Debemos crear un sistema que comunique información de forma inalámbrica.

**Requisitos obligatorios:**

| ✅ Requisito | Descripción |
|---|---|
| `arreglos (arrays)` | Uso obligatorio en la lógica del sistema |
| `iteraciones` | Ciclos para procesar y mapear datos |
| `transparencia` | Documentar todo: código, decisiones y prompts de IA |


## 🔍 Investigación y Referentes

Se exploró cómo las **APIs conectan sistemas**. Dos ejemplos clave:

> 🐱 **The Cat API** — un dato que gatilla acciones poéticas o visuales desde una fuente externa.

> 🏛️ **Patrimonio Bot** *(Claudio Ruiz)* — ejemplo local de datos que generan experiencias significativas de forma automatizada.


## 🌱 Propuesta del Grupo 07 — *"La Voz de las Plantas"*

El proyecto busca **traducir el mundo invisible de las plantas y hongos**, dándoles una voz sonora para mostrarlos como organismos vivos que interactúan con su entorno.

### 💬 Dinámica de Feedback en Clase

El profe planteó una actividad donde cada grupo subía su idea y el resto de los compañeros preguntaba para ayudar a aterrizarla.

<br>

**❓ `@nicolas-valdes` preguntó:**
> *"¿Qué es lo que detectará la frecuencia?"*

**💬 Respuesta del grupo:**
> Vamos a medir el **voltaje interno de la planta**. Como la Raspberry Pi Pico no tiene suficiente resolución, usaremos un módulo **ADS1115** para captar los micro-cambios eléctricos que ocurren cuando hay vibraciones o gente cerca.

<br>

**❓ `@nicolas-valdes` preguntó:**
> *"¿A qué tipo de sonidos se traduciría lo que dice la planta? ¿Algo direccionado a lo musical?"*

**💬 Respuesta de Braulio:**
> La idea es hacer **música generativa**. Si el entorno está en calma, suena suave, si hay movimiento, el sonido se vuelve activo o agudo. La planta será como un *sintetizador en vivo* reaccionando a estímulos.

<br>

> [!IMPORTANT]
> Este intercambio fue clave para decidir que el **ADS1115 es indispensable** para la propuesta técnica.

## 👥  Organización del Equipo y Roles

| Rol | Responsabilidad |
|---|---|
| 🔧 **Hardware** | Conectar el ADS1115 y estabilizar la lectura de voltajes en la planta |
| 💻 **Software** | Lógica en MicroPython: arreglos para promediar voltajes y mapearlos a sonidos |
| 📡 **Comunicación** | Transmisión inalámbrica y salida vía sintetizador |
| 📝 **Documentación** | Bitácoras, video de la demo y declaración de prompts de IA |

## 💭 Reflexión y Próximos Pasos

El feedback confirmó que la **"planta-sintetizador"** es una idea atractiva, pero requiere precisión técnica.

> [!NOTE]
> La precisión en la captura de señales eléctricas es tan importante como el diseño.

**Tareas pendientes:**

- [ ] Investigar más respecto al tema


## 📌 Anexo — Punteo del Profe *(apuntes literales de clase)*

> [!NOTE]
> Estas son las instrucciones tal como fueron entregadas en clases. Se conservan como referencia oficial del encargo.

**Presentación del proyecto:**
- Explicar en **1 párrafo de al menos 4 líneas** qué hace el proyecto 
- Encontrar referentes y palabras clave

**Grupos:**
- De 3 a 4 personas
- Excepciones puntuales si tienen notas sobre **6.7**

**Entregables individuales:**
- [ ] Investigación sobre APIs
- [ ] Bitácoras y proceso **×2**

**Entregables grupales:**
- [ ] Demo en video entre `rep180` y `salvsanf2221`
- [ ] Funcionamiento en vivo entre extremos de la sala
- [ ] Docs y código ordenado

