# sesion-08

lunes 27 abril 2026
# Trabajo en clases: Python en Raspberry Pi

En esta clase trabajaremos con **Python** en una **Raspberry Pi**, utilizando recursos descargados.

## ¿Qué es Python?
Python es un lenguaje de programación fácil de escribir y entender. Se caracteriza por:
- Sintaxis simple (usa indentación con espacios).
- Menor cantidad de código en comparación con otros lenguajes.
- Gran cantidad de bibliotecas y herramientas disponibles.

## ¿Qué es CircuitPython?
Usaremos **CircuitPython**, una adaptación de Python diseñada para microcontroladores, que facilita la programación de dispositivos electrónicos.

![python](imagenes/circuit_python.png)
## Instalación de CircuitPython
- Instalaremos la versión **CircuitPython 10.2.0**.
- Antes de instalar, es necesario **borrar la información previa** de la Raspberry Pi.
- Luego, copiamos los archivos correspondientes al sistema.

## Uso inicial
- Abrimos la aplicación y comenzamos a explorar.
- Presionamos **Ctrl + D** para reiniciar el dispositivo y asegurar su correcto funcionamiento.

## Descarga de bibliotecas 
1. Ir al repositorio oficial de Adafruit:
- Buscar: `Adafruit CircuitPython Bundle 10.x`
2. Descargar el archivo `.zip` correspondiente.
3. Descomprimir el archivo.
4.Descargar Putty.
5.Configurar putty para ocupar nuestar Raspberry Pi y nuestro codigo.

![putty](imagenes/putty.jpg)

## Instalación de bibliotecas
1. Entrar a la carpeta `lib` dentro del bundle descargado.
2. Copiar las siguientes carpetas a la carpeta `lib`
3. adafruit_minimqtt
adafruit_connection_manager
adafruit_ticks
para que funcione el codigo
   
#### Recordatorio el grabar el codigo 
## Ejercicio en clases potenciometro en la rasperry pi pico 
![raspberry](imagenes/potenciometro.jpg)
![raspberry](imagenes/potenciometro_coneccion.jpg)
## Para la solemne 2 
agregaremos un boton para que se envien los datos de manera mas rapida 
