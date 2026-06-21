# grupo-5

* Antonella Aguilar / antokiaraa
* Tomás Catrileo / tomascatri
* Angel Sabogal / angel-udp

## Archivo Retro

### Descripción del proyecto

Es un proyecto electrónico interactivo que fusiona la fotografía digital con el estilo gráfico de las consolas antiguas. Funciona de manera inalámbrica mediante 2 microcontroladores; un Arduino (UNO R4 WiFi) y una Raspberry (PI Pico 2W), y además un módulo ESP32 con cámara integrada que funciona de manera independiente. 

Por un lado cuenta con un potenciómetro que permite elegir un filtro, y un botón que al mantenerlo presionado cambias el estilo del tramado. Al pulsarlo rápidamente se envía la orden de disparo a la cámara y la pantalla OLED muestra una animación para avisarte que la foto se está subiendo a la nube. 

Las fotos procesadas se suben a un script de Google Drive y se almacenan en una carpeta como una galería de fotos. Por otro lado podremos ver las fotos en una pantalla TFT la cual está programada para revisar la carpeta de Drive cada 60 segundos y descargar automáticamente las últimas fotos tomadas, y cuenta con dos botones que permiten navegar hacia adelante o hacia atrás en este archivo de fotos estilo retro.

### Lista de materiales

| Componente | Cantidad |
| :--- | :--- |
| Arduino UNO R4 WiFi | 1 |
| Raspberry Pi Pico 2W | 1 |
| ESP32-CAM | 1 |
| Módulo / Tarjeta SD | 1 |
| Pantalla OLED I2C | 1 |
| Pantalla TFT SPI | 1 |
| Potenciómetro | 1 |
| Protoboard | 2 |
| Botón pulsador | 3 |
| Cables dupont | 20 |

### Proceso 

Nos basamos en un proyecto llamado "Pixela" de rai_lander que es una cámara DIY de código abierto. Tomamos como base su lógica interna para la captura y el procesamiento de las imágenes (la reducción de resolución, las paletas de colores y el efecto de dithering). 

![Proyecto Pixela](./imagenes/pixela.png)

*Web proyecto Pixela: [Pixela rai_lander](https://rai-lander.itch.io/pixela)*

Utiliza un script de Google Drive como nube para almacenar las imágenes y así nosotros también poder hacer nuestra propia galería pública. A partir de esa base lo pensamos para hacerlo interactivo, una persona en el lugar 1 (Rep180) pueda seleccionar una paleta de color (vibe) y tratado de imagen (dither), tome una foto sin saber cómo se verá y que la persona en el lugar 2 (SalvSanf2221) pueda navegar en la galería y ver las últimas imágenes que se van tomando.

1. Paletas de Colores (Vibe):

El sistema descarta los colores reales de la foto y busca el tono más cercano dentro de una paleta de 4 colores predefinidos. Estas son las paletas (tomadas de Pixela) que puedes seleccionar girando el potenciómetro:

- wish-gb
- kirokaze-gameboy
- ayy4
-  ice-cream-gb
- hollow
- crimson

2. Tratado de imagen (Dither):

Como la imagen ahora tiene solo 4 colores se generan cortes cromáticos muy bruscos. Para suavizar esto y dar la textura clásica de "pixel art", se aplica un algoritmo de dithering (dispersión de error), que mezcla matemáticamente los píxeles para simular nuevas texturas. Se puede cambiar este efecto manteniendo presionado el botón. Estos son los estilos disponibles:

- bayer
- floyd
- atkinson
- sierra
- ordered2
- halftone
- block
-  random
-  earest

```text
Arduino UNO R4 WiFi [Lugar 1: Rep180]
   │
   ├── Selecciona vibe y dither
   └── Envía la orden de disparo
         │
         ▼
Módulo ESP32-CAM (cámara)
   │
   ├── Toma y procesa la foto internamente
   └── Envía la imagen mediante una petición POST
         │
         ▼
Google Apps Script (nube)
   │
   ├── Genera el archivo .jpg (xx-pics-vibe-dith.jpg)
   └── Guarda la imagen en la carpeta de Google Drive
         │
         ▼
Raspberry Pi Pico 2W [Lugar 2: SalvSanf2221]
   │
   ├── Realiza una consulta HTTPS cada 60 segundos
   ├── Descarga las fotos nuevas automáticamente
   └── Muestra la galería en la pantalla TFT
```
### Conexiones

#### ESP32-CAM

El módulo funciona de manera independiente en cuanto a procesamiento de imagen y envío de datos, se monta en su placa adaptadora (ESP32-CAM-MB) y se conecta directamente al computador mediante un cable Micro-USB a USB.

#### Arduino UNO R4 WiFi

| Componente | Pin componente | Pin Arduino |
| :--- | :--- | :--- |
| **Potenciómetro** | VCC | 5V |
| | Patita 1 | GND |
| | Patita 2 | A0 |
| **Botón**| Patita 1 | Pin 2 |
| | Patita 2 | GND |
| **Pantalla OLED I2C** | VCC | 3.3V |
| | GND | GND |
| | SDA | A4 |
| | SCL | A5 |

#### Raspberry Pi Pico 2W

| Componente | Pin componente | Pin Raspberry |
| :--- | :--- | :--- |
| **Pantalla TFT (SPI0)**| GND | GND (38) |
| | VCC | 3V3_OUT (36) |
| | SCL | GP18 (SPI0 SCK - 24) |
| | SDA | GP19 (SPI0 TX - 25) |
| | RST | GP12 (16) |
| | DC | GP11 (15) |
| | CS | GP10 (14) |
| | BL | GP14 (19) |
| **Botón 1** | Patita 1 | GP5 (7) |
| | Patita 2 | GND (8) |
| **Botón 2** | Patita 1 | GP6 (9) |
| | Patita 2 | GND (13) |

### Errores y soluciones

En un principio ya teníamos armado lo que sería la parte de la Raspberry con la pantalla OLED en la cual podíamos seleccionar los parámetros de la foto a sacar y enviar la señal de disparo, revisamos que correctamente se subieran al drive pero nos faltaba implementar el otro microcontrolador, el Arduino, y teníamos 2 ideas: ver en tiempo real la cámara o poder visualizar la galería, para esto sí o sí necesitábamos un módulo para implementar una SD ya que la memoria del Arduino no era suficiente para ninguna de las 2 opciones, a pesar de conseguir el módulo no logramos hacerlo funcionar con el Arduino por lo que tuvimos que reorganizar las funciones de los microcontroladores, es decir mover el sistema de la pantalla OLED con el potenciómetro y el botón al Arduino y así otorgarle la tarea menos pesada. Así pudimos conectar la pantalla TFT a la Raspberry y poder implementar la segunda idea que era lo de poder ver la galería y además navegar en esta como un archivo de fotos.

Para lograr que el Arduino y la cámara se comuniquen sin cables en el lugar 1, implementamos el protocolo UDP, programamos la cámara para que actúe emitiendo su IP actual a toda la red local cada 5 segundos, el Arduino solo escucha la señal, se enlaza de forma automática y queda listo para enviar la orden de disparo.
Tuvimos algunos problemas con esto porque a veces la IP llegaba con "basura" o letras raras al final (como 172.30.75.96P) Lo solucionamos agregando un filtro que revisa la información recibida carácter por carácter, dejando pasar únicamente números y puntos (c >= '0' && c <= '9' || c == '.') para limpiar la IP antes de usarla.

En la cámara (ESP32) al principio intentamos que las fotos se guardaran en una tarjeta SD antes de subirse a la nube, pero nos daba errores de lectura. La mejor solución fue eliminar la dependencia de la tarjeta SD y usar una instrucción (ps_malloc) para guardar los bytes de la foto directamente en la memoria RAM externa (PSRAM) del módulo.

Algunos errores con la Raspberry fue al descargar las fotos de Google Drive porque estábamos usando una función estándar de Python (.isalnum()) para limpiar los nombres de los archivos y la versión de MicroPython de Pimoroni que instalamos no incluye esa función para ahorrar espacio de memoria, así que el código colapsaba. Lo arreglamos creando un filtro manual que verifica si las letras están en el rango correcto ('a' <= c <= 'z'). 

Otro fue que el texto que te indica el número de la foto en la pantalla no aparecía porque le estábamos asignando coordenadas muy altas y el texto se estaba dibujando fuera del límite visual de la pantalla. 

### Fotos proceso

![proceso 1](./imagenes/proceso_1.jpeg)

![proceso 2](./imagenes/proceso_2.jpeg)

![proceso 3](./imagenes/proceso_4.jpeg)

![proceso 4](./imagenes/proceso_5.jpeg)

![proceso 5](./imagenes/proceso_5.jpeg)

![proceso 6](./imagenes/proceso_6.jpeg)

![proceso 7](./imagenes/proceso_7.jpeg)

![proceso 8](./imagenes/proceso_8.gif)

![proceso filtros 0](./imagenes/prueba_sin_filto.jpg)
![proceso filtros 1](./imagenes/prueba_con_filtro_1.jpg)
![proceso filtros 2](./imagenes/prueba_con_filtro_2.jpg)
![proceso filtros 3](./imagenes/prueba_con_filtro_3.jpg)
![proceso filtros 4](./imagenes/prueba_con_filtro_4.jpg)
![proceso filtros 6](./imagenes/prueba_con_filtro_6.jpg)
![proceso filtros 7](./imagenes/prueba_con_filtro_7.jpg)


### Códigos 

#### ESP32-CAM

#### Arduino

#### Raspberry

### Fotos finales y video demo

### Bibliografía
