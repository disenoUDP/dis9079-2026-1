# sesion-13

lunes 08 junio 2026

## Trabajo en clases grupo amistad es amigo

comenzamos aclarando la idea del altar para el examen final. Retomamos la propuesta inicial y la ordenamos mejor, definiendo que el proyecto consiste en un **altar** compuesto por dos tótems conectados entre sí. La intención principal es que el objeto no reaccione solamente ante la presencia de una persona, sino ante el **gesto de permanecer frente a él**. Por eso, conversamos sobre la importancia de diferenciar una cercanía casual de una presencia sostenida, entendiendo la luz como una forma de memoria, compañía y vínculo afectivo.

### Totem 01

A partir de esta conversación, definimos que el **Tótem 01** funcionará como el punto principal de interacción. Este será construido como un pilar o altar vertical, con un Arduino resguardado en su base y un sensor ultrasónico integrado en su estructura. Este sensor permitirá medir la distancia entre la persona y el altar, para que la luz LED aumente progresivamente según el nivel de cercanía. **Si la persona se mantiene cerca durante el tiempo necesario, la luz llegará a su máxima intensidad, indicando que la presencia fue reconocida por el sistema**.

También definimos su composición, madera, impresión 3d y acrílico 

### Totem 02

También aclaramos el funcionamiento del **Tótem 02**, que actuará como receptor de la información enviada desde el primer tótem. Este segundo objeto tendrá una pantalla LED y un servomotor. La información captada por el sensor del Tótem 01 se traducirá en movimiento mediante el servo, generando una respuesta física a la distancia de la persona. Cuando la presencia se complete, el Tótem 02 recibirá un mensaje que indicará que **alguien estuvo ahí, recordó o decidió hacerse presente**.

quizas este diseño nos falta profundizar en su forma y su composición 

Durante la sesión también discutimos la pregunta que amplía el sentido del proyecto: ¿qué pasa si el altar no solo responde a quien se acerca, sino también a la ausencia de alguien? Esta idea nos permitió pensar en una segunda condición del sistema, donde la luz podría activarse de manera tenue o intermitente si pasa mucho tiempo sin que nadie se acerque. De esta forma, la ausencia también se transforma en una señal, como una presencia fantasma o una memoria que sigue habitando el espacio.

## Lista de compras 

| Elemento | Función dentro de la interacción | Precio |
|---|---|---|
| Sensor ultrasónico | Detecta la distancia entre la persona y el Tótem 01. | |
| LED | Se enciende progresivamente según la cercanía de la persona. | |
| Protoboard mini | Permite conectar y organizar los componentes electrónicos. | |
| Cables Dupont mix | Conectan los sensores, LED, servo, pantalla y Arduino. | |
| Servo | Imita físicamente la distancia detectada por el sensor. | |
| Pantalla OLED | Muestra los mensajes recibidos desde el Tótem 01. | |

## Texto proyecto

El proyecto consiste en un altar lumínico compuesto por dos tótems conectados inalámbricamente entre sí, donde la presencia física de una persona se transforma en una señal luminosa, mecánica y afectiva. La interacción principal ocurre en el Tótem 01, construido como un altar vertical. En su base se encuentra resguardado el Arduino, mientras que en su estructura se integra un sensor ultrasónico capaz de medir la distancia entre el objeto y la persona que se aproxima.

A partir de esta medición, el sistema interpreta distintos rangos de cercanía. No se trata solamente de detectar si alguien está o no está frente al altar, sino de reconocer cómo se aproxima y si decide permanecer. Cuando una persona se acerca, el sensor ultrasónico registra la distancia y envía ese dato al Arduino, que lo traduce en una condición de intensidad lumínica. Mientras más cerca se encuentra la persona, mayor es la intensidad de la luz LED del tótem. De esta manera, la luz se enciende progresivamente, como si el altar despertara lentamente ante la presencia de alguien. Cuando la persona alcanza la distancia más cercana definida por el sistema, la luz llega a su 100%, indicando que la presencia fue sostenida y reconocida.

Si la persona se aleja antes de completar este proceso, la luz disminuye lentamente y no se activa la comunicación final. Esto permite que el sistema distinga entre una cercanía casual y un gesto de permanencia. Así, el funcionamiento técnico refuerza la dimensión ritual del proyecto: no basta con pasar frente al objeto, hay que quedarse el tiempo suficiente para que el altar responda.

Mientras esta interacción ocurre, el Tótem 01 envía información al Tótem 02. Este segundo tótem funciona como un receptor de la presencia detectada en el primero. Su estructura incorpora una pantalla LED y un servomotor. El movimiento del servo está vinculado a la distancia registrada por el sensor ultrasónico del Tótem 01: si la persona está lejos, pero comienza a acercarse, el servo se mueve de manera gradual, traduciendo esa aproximación en un gesto físico. Así, la distancia de una persona frente al primer altar se convierte en movimiento en el segundo tótem.

Cuando la persona llega a la condición de mayor cercanía y la luz del Tótem 01 alcanza su máxima intensidad, el sistema envía un mensaje al Tótem 02. Este mensaje aparece en la pantalla LED como una señal de compañía, indicando que alguien estuvo ahí, recordó o decidió hacerse presente. De esta forma, el segundo tótem no solo recibe datos técnicos, sino una huella simbólica de la interacción ocurrida en el primero.

Además, el proyecto incorpora una pregunta central: ¿qué pasa si el altar no solo responde a quien se acerca, sino también a la ausencia de alguien? Desde esta idea, el sistema puede contemplar una segunda condición: si durante un periodo prolongado nadie se aproxima al altar, la luz puede encenderse por sí sola de manera tenue o intermitente, como una presencia fantasma. Esta activación no representaría una visita física, sino la memoria de una ausencia. En ese caso, el mensaje enviado al Tótem 02 sería distinto, no como señal de compañía presente, sino como una alusión a alguien que falta, que no ha llegado o que sigue habitando el espacio desde la distancia.

## Corrección 

1.Separar la descripción textual en varias secciones. Por ejemplo primero solamente conceptual, luego otra técnica que explique cómo los conceptos se implementan.    
2.Complementar con diagramas de flujo o dibujos   
3.Escribir el pseudocódigo

## Pseudocódigo

# Totem 01: Arduino
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
# Totem 02
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

