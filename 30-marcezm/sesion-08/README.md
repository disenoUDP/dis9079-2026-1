# sesion-08

lunes 27 abril 2026

# Trabajo en clases: Python en Raspberry Pi

## Introducción

Durante esta clase trabajamos con **Python** en una **Raspberry Pi Pico**, utilizando recursos descargados y distintas herramientas necesarias para comenzar a programar dispositivos electrónicos mediante CircuitPython.

---

## ¿Qué es Python?

Python es un lenguaje de programación fácil de escribir y entender. Se caracteriza por:

- Sintaxis simple utilizando indentación con espacios.
- Menor cantidad de código en comparación con otros lenguajes.
- Gran cantidad de bibliotecas y herramientas disponibles.
- Facilidad para trabajar con proyectos electrónicos y automatización.

---

## ¿Qué es CircuitPython?

Usamos **CircuitPython**, una adaptación de Python diseñada especialmente para microcontroladores, permitiendo programar dispositivos electrónicos de manera más simple y rápida.

CircuitPython facilita el trabajo con sensores, actuadores y distintos componentes conectados a la Raspberry Pi Pico.

![python](imagenes/circuit_python.png)

---

## Instalación de CircuitPython

Durante la clase realizamos la instalación de **CircuitPython 10.2.0**.

Pasos realizados:

- Borrar la información previa almacenada en la Raspberry Pi Pico.
- Instalar la nueva versión de CircuitPython.
- Copiar los archivos correspondientes al sistema.
- Verificar el correcto funcionamiento del dispositivo.

---

## Uso inicial

Una vez instalado el sistema:

- Abrimos la aplicación correspondiente.
- Exploramos el entorno de programación.
- Probamos la conexión entre el computador y la Raspberry Pi Pico.
- Reiniciamos el dispositivo utilizando:

```python
Ctrl + D
```
## Descarga de bibliotecas

Para continuar con el desarrollo del proyecto trabajamos con distintas bibliotecas necesarias para el correcto funcionamiento del código en CircuitPython.

### Pasos realizados

1. Ingresar al repositorio oficial de Adafruit.
2. Buscar:
   `Adafruit CircuitPython Bundle 10.x`
3. Descargar el archivo `.zip`.
4. Descomprimir el archivo descargado.
5. Descargar Putty.
6. Configurar Putty para utilizar la Raspberry Pi Pico y monitorear el funcionamiento del código.

### Configuración de Putty

Putty fue utilizado para establecer comunicación entre el computador y la Raspberry Pi Pico, permitiendo visualizar la ejecución del código y detectar posibles errores.

![putty](imagenes/putty.jpg)

---

## Instalación de bibliotecas

Dentro de la carpeta `lib` del bundle descargado copiamos las siguientes bibliotecas necesarias para el proyecto:

- `adafruit_minimqtt`
- `adafruit_connection_manager`
- `adafruit_ticks`

Estas bibliotecas permiten agregar funcionalidades relacionadas con conexión, comunicación y administración de datos dentro del sistema.

---

## Recordatorio importante

Es importante guardar correctamente el archivo `code.py`, ya que la Raspberry Pi Pico ejecuta automáticamente ese archivo al conectarse o reiniciarse.

---

## Ejercicio en clases: Potenciómetro en Raspberry Pi Pico

Finalmente realizamos un ejercicio práctico conectando un potenciómetro a la Raspberry Pi Pico para leer valores analógicos desde el código.

Durante esta actividad:

- Armamos el circuito utilizando protoboard.
- Realizamos conexiones entre la Raspberry Pi Pico y el potenciómetro.
- Probamos la lectura de datos analógicos.
- Revisamos errores de conexión y alimentación.
- Verificamos el correcto funcionamiento del circuito mediante pruebas prácticas.

### Ejercicio práctico

![raspberry](imagenes/potenciometro.jpg)

### Conexión del circuito

![raspberry](imagenes/potenciometro_conexion.jpg)

Este ejercicio permitió comprender mejor la interacción entre hardware y software utilizando sensores analógicos y programación en Python.
