# sesion-08

lunes 27 abril 2026

nos vemos a la vuelta del receso

# Editor Mu (R.I.P.) y uso de Python

Python es un lenguaje de programación sencillo de aprender porque permite escribir menos código en comparación con otros lenguajes. Sin embargo, es muy importante respetar la indentación (espacios y tabulaciones), ya que estos definen la estructura del programa.

Se utiliza ampliamente en proyectos con microcontroladores como la Raspberry Pi Pico, especialmente en entornos educativos y de prototipado.

Algunas librerías importantes en Python son:

NumPy (no “nympy”): usada para cálculos matemáticos y manejo de arreglos.
SciPy: complementa a NumPy con herramientas más avanzadas para ciencia e ingeniería.
CircuitPython

CircuitPython es una versión de Python diseñada para microcontroladores como la Raspberry Pi Pico.

## Instalación
* Descargar la versión 10.2.0 (u otra compatible).
* Conectar la Raspberry Pi Pico al computador en modo BOOTSEL.
* Copiar el archivo .uf2 a la placa.
* La placa aparecerá como una unidad llamada CIRCUITPY.

## Uso básico
El archivo principal es code.py.
En este archivo puedes escribir y modificar el código directamente.
Cada vez que guardas cambios, el programa se ejecuta automáticamente en la placa.
Comandos útiles

* Ctrl + C: detiene la ejecución del programa.
* Ctrl + D: reinicia el microcontrolador.
  
## Indicadores en el editor
Un círculo blanco indica que el archivo no está guardado.
Una X indica que los cambios ya fueron guardados.
Instalación de librerías

## Para usar funcionalidades avanzadas (como conexión a internet o sensores):

* Descargar el bundle de librerías para la versión 10.x.
* Descomprimir el archivo.
* Ir a la carpeta lib dentro de CIRCUITPY.
* Copiar las siguientes librerías necesarias:
* adafruit_minimqtt
* adafruit_connection_manager.mpy
* adafruit_ticks.mpy

Estas librerías permiten, por ejemplo, enviar datos a internet.

Proyecto: Potenciómetro → Raspberry Pi Pico → Adafruit IO

## Flujo básico:

El potenciómetro envía valores analógicos.
La Raspberry Pi Pico lee esos valores.
Los datos se envían a la plataforma Adafruit IO.
En Adafruit IO puedes visualizar los datos en gráficos o dashboards.

Esto permite crear proyectos de monitoreo en tiempo real, como sensores de luz, temperatura o control de dispositivos.
  <img width="1347" height="780" alt="placa pico2" src="https://github.com/user-attachments/assets/3dbe075c-8f73-4ca3-815a-1e05f7d64b18" />

* los comentarios en Python se hacen con # 
