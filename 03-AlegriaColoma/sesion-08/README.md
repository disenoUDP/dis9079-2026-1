# sesion-08

lunes 27 abril 2026

## Python

menos escritura, pero más delicado.  

+ micropython  

+ sub variante: circuit python   https://circuitpython.org/

Descargamos el CircuitPython 10.2.0 

-> conectar la raspberry pi pico w al usb (apretar el botón, conectar y soltar el botón) 

-> Abrir el disco duro 

-> arrastrar el archivo de Circuit python (UF2) a la carpeta del disco duro 

-> Debería desaparecer 

-> al volver a conectar aparecería con el con el nombre 

para salir es control+C, si no funciona control+D

## Instalación Putty 

abrir el archivo descargado desde aquí (https://www.chiark.greenend.org.uk/~sgtatham/putty/latest.html), configurar para poder ver lo que está haciendo la raspberry pi (ojo con el puerto) 


## prueba de Código 

En el archivo code.py colocar el código 

+ control + S = grabar (si aparece el círculo blanco es por que no está grabado) 

abir putty y verificar el error, el error es que no esxiste la minilibrarymqtt

instalar la biblioteca de cirtuit python (la 10x) 

descomprimir el archivo - abrir y buscar las carpetas y archivos a instalar en la carpeta lib dentro del discoduro 

adafruit_minimqtt-> biblioteca que debemos instalar
