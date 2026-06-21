# sesion-13

lunes 08 junio 2026

## Apuntes

Cambios en Github del profesor 

y en 00-examen

se muestran los requisitos de la prueba

Investigación individual y lo que hicimos la semana pasada quedó de referente, por ahora lo importante es escribir el pseudo codigo del proyecto: son comentarios o diagramas que digan "has esto tantass veces" o "Como encontrar un maximo de un número", "encontrar el maximo de un número"

son como los planos de la casa antes de construir la casa y tiene valor en si mismo armar el pseudo codigo, con lista de materiales y dibujos si es que eso ayuda
y colocar un código de prueba con comentarios en consola simulando

Esto es programar (Varios días de planificación)

Y ahora procederemos a avanzar en clase

### Pseudocódigo

Nuestra idea está inspirada en el proyecto Pixela. El objetivo es tomar una fotografía y transformarla en una imagen con estilo retro, parecida a los videojuegos antiguos que están hechos con píxeles.

Cuando una persona toma una foto desde una aplicación web, la imagen se envía a una Raspberry Pi. La Raspberry Pi procesa la fotografía y la convierte en una versión pixelada utilizando una paleta de colores limitada para darle una apariencia retro.

Después de procesar la imagen, esta se guarda en la nube para que pueda ser vista desde otros dispositivos. Además, la Raspberry Pi mostrará la imagen en una pantalla conectada al sistema.

También queremos utilizar un Arduino para crear una galería pública de imágenes. Cada vez que se genere una nueva fotografía pixelada, esta se agregará automáticamente a la galería. Con botones físicos, las personas podrán cambiar entre las distintas imágenes guardadas y ver tanto las más nuevas como las más antiguas.

De esta forma, el proyecto permite transformar fotografías en arte pixelado y compartirlas en una galería que se actualiza constantemente.

INICIO

Tomar foto

Enviar foto a la Raspberry Pi

La Raspberry Pi convierte la foto en pixel art

Guardar imagen

Subir imagen a la galería

Mostrar imagen en la pantalla

SI se presiona el botón siguiente
    Mostrar siguiente imagen
FIN SI

SI se presiona el botón anterior
    Mostrar imagen anterior
FIN SI

SI llega una nueva foto
    Convertirla a pixel art
    Agregarla a la galería
FIN SI

REPETIR TODO EL TIEMPO

### Lista de materiales

| Cantidad | Material                          | Función                                          |
| -------- | --------------------------------- | ------------------------------------------------ |
| 1        | Raspberry Pi Pico 2 W             | Controla la interfaz, menús y comunicación Wi-Fi |
| 1        | ESP32-CAM (con cámara OV2640)     | Captura las fotografías                          |
| 1        | Antena Wi-Fi externa IPEX         | Mejora el alcance de la conexión inalámbrica     |
| 1        | Pantalla OLED SSD1306 128×64      | Muestra menús e información de la cámara         |
| 1        | Potenciómetro de 1 kΩ             | Permite navegar por las opciones                 |
| 1        | Botón pulsador                    | Disparador de la cámara                          |
| 1        | Batería LiPo 3.7 V                | Alimentación portátil del sistema                |
| 1        | Módulo TP4056 con protección      | Carga segura de la batería                       |
| 1        | Interruptor deslizante de 3 pines | Encendido y apagado del sistema                  |
| 1        | Arduino UNO R4 WiFi               | Recibe y muestra las fotografías                 |
| 1        | Pantalla TFT LCD SPI 320×240      | Visualización de imágenes en la galería          |
| 3        | Botones pulsadores                | Navegación y generación de código QR             |
| 1        | Cable USB de alimentación         | Alimentación permanente de la galería            |
| 1        | Adaptador FTDI USB a TTL          | Programación del ESP32-CAM                       |
| 1        | Jumper de cortocircuito           | Configuración del FTDI y modo grabación          |
| 1        | Protoboard grande (o 2 medianas)  | Montaje temporal del circuito                    |
| Varios   | Cables Dupont macho-macho         | Conexiones en la protoboard                      |
| Varios   | Cables Dupont macho-hembra        | Conexiones entre módulos                         |

y en la carpeta del exámen está la investigación de que es una API y cal utilizamos nosotros en nuestro proyecto (Grupo-5)
