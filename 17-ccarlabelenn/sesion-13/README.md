# sesion-13

lunes 08 junio 2026

## trabajo en grupo para examen!!!

En esta clase decidimos lo que haríamos de forma definitiva. Nos enfocamos mucho en cómo sería nuestra exposición para que fuera algo muy nuestro y que evidenciara todo el proceso de aprendizaje que tuvimos a lo largo del curso, el cual fue muchas veces frustrante pero sobre todo lleno de cariño y pasión por algo que por lo menos para mí, era muy desconocido.

Dentro de nuestra lluvia de ideas nos encantó el hacer una especie de muestra museográfica que dado los criterios de nuestro examen, tuviera todo lo que se nos pedía. El proyecto se divide en módulos, que en este caso pensamos en dos: el primero es una vitrina exenta (como la de los museos donde ponen obras muy bacanes o preciadas), que contiene un sensor ultrasónico capaz de medir la distancia entre este objeto y una persona, también un led que dependiendo de la distancia de la persona aumenta o disminuye su luz. El segundo contiene una pantalla que mostrará un mensaje, funcionando como receptor de la presencia detectada por el primer módulo; incorpora también un servomotor que está vinculado a la distancia registrada por el sensor, moviéndose de manera gradual, traduciendo esa información en un gesto físico (¿super cute o no?).

> Esta explicación es muy a grandes rasgos, ya que en nuestra bitácora de grupo detallaremos a profundidad nuestro proyecto jeje. 

![imagenes](./imagenes/muestra.jpg)
> créditos a la magdita por esta fotito representativa

# pseudocódigo
**módulo 01**

```
INICIO

Definir sensor ultrasónico
Definir LED
Definir conexión inalámbrica con Tótem 02

Definir distancia_lejana = mayor a 100 cm
Definir distancia_media = entre 70 cm y 100 cm
Definir distancia_cercana = entre 40 cm y 70 cm
Definir distancia_muy_cercana = menor a 40 cm

Definir intensidad_LED = 0%

MIENTRAS el sistema esté encendido:

Medir distancia de la persona con el sensor ultrasónico

SI la distancia es mayor a 100 cm:
    La persona está lejos
    LED apagado o con intensidad mínima
    intensidad_LED = 0%
    Enviar al Tótem 02: "sin presencia cercana"

SI la distancia está entre 70 cm y 100 cm:
    La persona comienza a acercarse
    LED se enciende suavemente
    intensidad_LED = 25%
    Enviar al Tótem 02: "presencia lejana"

SI la distancia está entre 40 cm y 70 cm:
    La persona está cerca del altar
    LED aumenta su intensidad
    intensidad_LED = 60%
    Enviar al Tótem 02: "presencia cercana"

SI la distancia es menor a 40 cm:
    La persona está muy cerca del altar
    LED alcanza su máxima intensidad
    intensidad_LED = 100%
    Enviar al Tótem 02: "alguien está aquí"

Actualizar intensidad del LED según el valor definido

Esperar un momento breve antes de volver a medir

FIN
```
**módulo 02**

```
INICIO

Definir pantalla LED
Definir servomotor
Definir conexión inalámbrica con Tótem 01

Definir posición_servo = 0 grados

MIENTRAS el sistema esté encendido:

Esperar información enviada desde el Tótem 01

Recibir dato de distancia o condición de cercanía

SI el mensaje recibido es "sin presencia cercana":
    Mostrar en pantalla: "Sin presencia"
    Mover servo a 0 grados
    posición_servo = 0 grados

SI el mensaje recibido es "presencia lejana":
    Mostrar en pantalla: "Alguien se aproxima"
    Mover servo a 45 grados
    posición_servo = 45 grados

SI el mensaje recibido es "presencia cercana":
    Mostrar en pantalla: "Presencia cerca"
    Mover servo a 90 grados
    posición_servo = 90 grados

SI el mensaje recibido es "presencia reconocida":
    Mostrar en pantalla: "Estoy aquí"
    Mover servo a 180 grados
    posición_servo = 180 grados

Esperar un momento breve antes de volver a recibir información

FIN 
```

## avance durante la semana con amistad es amigo

Durante la semana nos dedicamos a probar los códigos y los elementos que utilizaremos para la muestra: LED, sensor ultrasónico, Arduino y un corazón muy lindo que imprimimos en 3D en el LID jejeje.

![imagenes](./imagenes/corazonled.gif)

