# sesion-08

lunes 27 abril 2026


https://circuitpython.org/

https://circuitpython.org/board/raspberry_pi_pico2_w/

# CircuitPython en Raspberry Pi Pico: instalación, conexión y carga de código

## Introducción a MicroPython y CircuitPython

Python es un lenguaje de programación muy utilizado en computadores tradicionales, pero debido a su popularidad surgió la necesidad de adaptarlo para dispositivos pequeños como los microcontroladores. De ahí nace **MicroPython**, una versión optimizada de Python diseñada para funcionar en hardware con recursos limitados.

A partir de MicroPython surge **CircuitPython**, desarrollado por [Adafruit](https://www.adafruit.com?utm_source=chatgpt.com) como una variante enfocada principalmente en facilitar el aprendizaje y el trabajo con hardware.

Relación entre ambos:

```text
Python
   ↓
MicroPython
   ↓
CircuitPython
```

CircuitPython destaca por:

* Sintaxis simple.
* Instalación sencilla.
* Ejecución inmediata del código.
* Amplia compatibilidad con placas de desarrollo.
* Gran enfoque educativo y de prototipado.

Actualmente es compatible con cientos de placas distintas y existe un ecosistema abierto donde múltiples fabricantes modifican diseños para crear variantes más pequeñas, eficientes o especializadas.

Algunos ejemplos:

* Placas con Bluetooth.
* Wearables y textiles inteligentes.
* Cámaras programables.
* Proyectos IoT.
* Automatización y robótica.

---

## Instalación de CircuitPython en Raspberry Pi Pico

La Raspberry Pi Pico incluye un firmware de fábrica que debe reemplazarse para trabajar con CircuitPython.

### Descargar el firmware

Se debe descargar la versión correspondiente a la placa utilizada.

Se recomienda utilizar:

* Versiones **estables**
* Evitar versiones experimentales (*nightly builds*)

El archivo descargado posee extensión:

```text
.UF2
```

---

### Entrar en modo BOOTSEL

La Raspberry Pi Pico posee un modo especial para cargar firmware.

Secuencia:

```text
Mantener presionado BOOTSEL
↓
Conectar USB
↓
Soltar botón
```

Al realizarlo correctamente aparecerá un disco externo con un nombre similar a:

```text
RP2350
```

---

### Instalar el firmware

Simplemente:

1. Arrastrar el archivo `.UF2`
2. Soltarlo dentro del disco detectado
3. Esperar unos segundos

La placa se reiniciará automáticamente y aparecerá un nuevo disco:

```text
CIRCUITPY
```

Esto indica que CircuitPython fue instalado correctamente.

---

## Diferencia entre Arduino y CircuitPython

### Flujo tradicional en Arduino

```text
Escribir código
↓
Compilar
↓
Subir programa
↓
Ejecutar
```

### Flujo con CircuitPython

```text
Editar archivo
↓
Guardar
↓
Ejecutar automáticamente
```

CircuitPython funciona prácticamente como un pendrive.

Dentro del disco aparece un archivo principal:

```text
code.py
```

Todo lo escrito dentro de ese archivo se ejecutará automáticamente.

Ejemplo:

```python
print("Hola mundo")
```

Al guardar el archivo, el programa se ejecuta inmediatamente sin necesidad de compilar.

---

## Comunicación mediante puerto serial

Para visualizar mensajes del microcontrolador se utiliza comunicación serial.

Parámetros utilizados:

```text
Velocidad: 115200 baudios
```

La configuración debe realizarse en la herramienta de conexión serial (ejemplo: Putty).

---

### Identificación del puerto

Los nombres cambian dependiendo del sistema operativo.

**Windows**

```text
COM3
COM9
COM10
```

**MacOS**

```text
/dev/cu.usbmodem1401
```

El número o nombre puede cambiar cuando:

* Se cambia el puerto USB
* Se desconecta la placa
* Se reinstala firmware

Por eso siempre debe verificarse antes de conectarse.

---

## Restricción importante del puerto serial

El puerto serial solo puede ser utilizado por un programa a la vez.

Por ejemplo:

Si Arduino IDE está usando:

```text
COM9
```

otra aplicación no podrá acceder al mismo puerto simultáneamente.

La solución:

1. Revisar el puerto
2. Cerrar Arduino IDE
3. Conectarse nuevamente

---

## Uso del intérprete interno

Al conectarse correctamente aparece:

```python
>>>
```

Esto significa que CircuitPython está esperando instrucciones.

Permite:

* Ejecutar comandos directamente
* Revisar resultados
* Diagnosticar errores
* Probar código rápidamente

---

## Comandos importantes

### Ctrl + C

Detiene la ejecución actual.

```text
Ctrl + C
```

---

### Ctrl + D

Reinicia CircuitPython y ejecuta nuevamente el archivo principal.

```text
Ctrl + D
```

Al reiniciarse se vuelve a ejecutar:

```text
code.py
```

---

## Edición del archivo principal

Dentro de:

```text
CIRCUITPY
```

se encuentra:

```text
code.py
```

Puede abrirse con editores como:

* Bloc de notas
* Notepad++
* Visual Studio Code

El flujo es:

```text
Abrir code.py
↓
Borrar contenido anterior
↓
Pegar nuevo código
↓
Guardar
↓
Ejecutar automáticamente
```

---

## Configuración del código para Wi-Fi y Adafruit IO

El nuevo programa requería modificar ciertos parámetros.

Nombre de red:

```python
WIFI_SSID="NombreRed"
```

Contraseña:

```python
WIFI_PASSWORD="Contraseña"
```

Feed del grupo:

```python
usuario/potenciometro
```

Cada grupo debía reemplazar esos valores por sus propios datos.

El objetivo era:

* Conectar Raspberry Pi Pico a Wi-Fi
* Conectarse a Adafruit IO
* Enviar datos desde sensores
* Crear un sistema IoT

Flujo esperado:

```text
Sensor
↓
Raspberry Pi Pico
↓
Wi-Fi
↓
Adafruit IO
↓
Visualización de datos
```

---

## Errores comunes observados en la práctica

**La placa no aparece**

Posibles causas:

* Cable defectuoso
* BOOTSEL mal ejecutado
* Drivers faltantes

**No conecta al puerto serial**

Posibles causas:

* Puerto incorrecto
* Puerto ocupado
* Configuración incorrecta

**El código no funciona**

Posibles causas:

* Error de sintaxis
* Wi-Fi incorrecto
* Contraseña errónea
* Feed mal escrito

**El dispositivo cambia de nombre**

Posibles causas:

* Cambio de puerto USB
* Reinstalación del firmware
* Reconexión del dispositivo

***Los errores forman parte normal del proceso y ayudan a entender el funcionamiento del sistema.***



