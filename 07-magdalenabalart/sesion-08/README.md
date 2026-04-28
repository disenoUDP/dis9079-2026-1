# sesion-08

# Idea general

En esta sesión cambiaron de una lógica tipo Arduino IDE a una lógica tipo CircuitPython. Eso es importante porque ya no se programa la placa como un sketch que se compila y se sube, sino como si la placa fuera una especie de pendrive programable.

En Arduino normalmente uno escribe código, aprieta subir, espera que compile y después la placa ejecuta. En CircuitPython, la placa aparece en el computador como una unidad llamada CIRCUITPY, y uno simplemente copia o edita archivos dentro de ella. Cuando guardas el archivo code.py, la placa lo ejecuta automáticamente.

## Qué es CircuitPython

CircuitPython es una versión de Python pensada para microcontroladores. Fue creada para facilitar la experimentación y la educación con placas pequeñas. Su gracia es que no requiere instalar un entorno pesado: la placa aparece como disco USB y uno trabaja directamente sobre sus archivos.

Esto cambia la experiencia de trabajo:

Arduino: escribir → compilar → subir → probar
CircuitPython: editar archivo → guardar → probar altiro

“eliminar lo que tenía”

“eliminar lo que tenía”, dejar limpia la placa o reemplazar los archivos anteriores por los nuevos archivos de CircuitPython.

Hay dos niveles distintos:

1. Instalar CircuitPython en la placa

Esto es cargarle el sistema base. Para eso se usa un archivo terminado en .uf2.

2. Borrar archivos viejos dentro de CIRCUITPY

Una vez instalado CircuitPython, la placa aparece como un disco llamado CIRCUITPY. Ahí pueden existir archivos anteriores, como code.py, carpetas lib, ejemplos, etc. Esos se pueden borrar o reemplazar 

Cómo hacerlo en Mac, paso a paso

Paso 1: conectar la Pico en modo BOOTSEL

Primero la placa debe entrar en modo carga.

Desenchufa la Raspberry Pi Pico del Mac.
Mantener apretado el botón BOOTSEL.
Sin soltar BOOTSEL, conectar el cable USB al Mac.
Cuando aparezca una unidad llamada RPI-RP2, soltar el botón.

Paso 2: descargar el archivo correcto

Tienes que descargar el archivo .uf2 correspondiente a la placa exacta 

Paso 3: arrastrar el archivo .uf2

Cuando aparece RPI-RP2 en Finder, arrastras el archivo .uf2 descargado hacia esa unidad.

Después de copiarlo:

la placa se reinicia sola
desaparece RPI-RP2
aparece una nueva unidad llamada CIRCUITPY

Cuando aparece CIRCUITPY, significa que CircuitPython quedó instalado. 

Paso 4: abrir CIRCUITPY

En Mac, abres Finder y buscas la unidad CIRCUITPY.

Ahí la placa funciona como si fuera un pendrive

Paso 6: subir la carpeta nueva

CIRCUITPY/
├── code.py
├── lib/
└── settings.toml


Qué hace cada parte
code.py

Es el programa principal. Es como el “sketch” de Arduino, pero en Python.

import time

while True:
    print("hola")
    time.sleep(1) 

 lib/

Es la carpeta de librerías.

Sirve para guardar bibliotecas externas. Por ejemplo, si usas sensores, pantallas, MQTT o Adafruit IO, muchas veces necesitas copiar librerías dentro de lib.

Si falta una librería, el código puede fallar aunque esté bien escrito.   

settings.toml

Este archivo suele usarse para guardar datos privados, como WiFi o claves.

Ejemplo: 

CIRCUITPY_WIFI_SSID = "nombre_de_wifi"
CIRCUITPY_WIFI_PASSWORD = "contraseña"








code.py
lib/
settings.toml 



lunes 27 abril 2026

nos vemos a la vuelta del receso

