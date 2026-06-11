# sesion-13

lunes 08 junio 2026

# Trabajo en clases en grupito - Examen 

En esta clase nos dedicamos a definir de forma más concreta lo que haríamos para el examen. Retomamos la propuesta del altar y la ordenamos mejor, separando la descripción en una parte conceptual y una técnica, que era justamente una de las correcciones que nos habían dado.

Lo que más me gustó fue la dirección que tomó el proyecto: decidimos presentarlo como una especie de muestra museográfica, dos módulos separados como si fueran objetos de exhibición. El primero tiene un sensor ultrasónico y un LED que responde progresivamente a la cercanía de una persona. El segundo tiene una pantalla OLED y un servomotor que recibe lo que detecta el primero y lo traduce en movimiento y en un mensaje. La comunicación entre ambos ocurre de forma inalámbrica a través de Adafruit IO.

También trabajamos el pseudocódigo de ambos módulos y seguimos afinando los textos del proyecto.
## Descripción conceptual proyecto

El proyecto consiste en un altar lumínico compuesto por dos tótems conectados inalámbricamente entre sí, donde la presencia física de una persona se transforma en una señal luminosa, mecánica y afectiva.

La interacción no responde a una cercanía casual, sino al gesto de quedarse: no basta con pasar frente al objeto, hay que permanecer. La luz se enciende progresivamente, como si el altar despertara lentamente ante quien se aproxima. Solo cuando la presencia se sostiene el tiempo suficiente, el altar la reconoce y la comunica al segundo tótem, que responde con movimiento y una señal de compañía.

El proyecto también contempla la ausencia. Si durante un periodo prolongado nadie se aproxima, la luz puede encenderse por sí sola de manera tenue o intermitente, como una presencia fantasma. En ese caso, el mensaje enviado al segundo tótem no sería una señal de compañía presente, sino una alusión a alguien que falta, que no ha llegado o que sigue habitando el espacio desde la distancia.

---

## Descripción técnica

El **Tótem 01** funciona como dispositivo de entrada. En su base se encuentra el Arduino, y en su estructura se integra un sensor ultrasónico que mide la distancia entre el altar y la persona que se aproxima. A partir de esa medición, el sistema interpreta distintos rangos de cercanía y los traduce en intensidad lumínica mediante LEDs. Mientras más cerca se encuentra la persona, mayor es la intensidad de la luz. Si la persona se aleja antes de completar el proceso, la luz disminuye lentamente y no se activa la comunicación.

El **Tótem 02** funciona como dispositivo receptor. Incorpora un servomotor cuyo movimiento está vinculado a la distancia registrada por el sensor del Tótem 01: a medida que la persona se acerca, el servo se mueve gradualmente. Cuando la presencia es reconocida por completo, el Tótem 02 recibe un mensaje que se muestra en pantalla como señal de compañía. La comunicación entre ambos tótems ocurre de forma inalámbrica a través de Adafruit IO.


En esta clase nos dedicamos a definir de forma más concreta lo que haríamos para el examen. Retomamos la propuesta del altar y la ordenamos mejor, separando la descripción en una parte conceptual y una técnica, que era justamente una de las correcciones que nos habían dado.

Lo que más me gustó fue la dirección que tomó el proyecto: decidimos presentarlo como una especie de muestra museográfica, dos módulos separados como si fueran objetos de exhibición. El primero tiene un sensor ultrasónico y un LED que responde progresivamente a la cercanía de una persona. El segundo tiene una pantalla OLED y un servomotor que recibe lo que detecta el primero y lo traduce en movimiento y en un mensaje. La comunicación entre ambos ocurre de forma inalámbrica a través de Adafruit IO.

También trabajamos el pseudocódigo de ambos módulos y seguimos afinando los textos del proyecto.

---

## Pseudocódigo

### Tótem 01 — Arduino

```
INICIO

Definir sensor ultrasónico
Definir LED
Definir conexión inalámbrica con Tótem 02

Definir rangos:
  distancia_lejana    → mayor a 100 cm
  distancia_media     → entre 70 cm y 100 cm
  distancia_cercana   → entre 40 cm y 70 cm
  distancia_muy_cerca → menor a 40 cm

MIENTRAS el sistema esté encendido:

  Medir distancia con sensor ultrasónico

  SI distancia > 100 cm:
    LED apagado
    Enviar al Tótem 02: "sin presencia"

  SI distancia entre 70 y 100 cm:
    LED al 25%
    Enviar al Tótem 02: "presencia lejana"

  SI distancia entre 40 y 70 cm:
    LED al 60%
    Enviar al Tótem 02: "presencia cercana"

  SI distancia < 40 cm:
    LED al 100%
    Enviar al Tótem 02: "alguien está aquí"

  Esperar antes de volver a medir

FIN
```

### Tótem 02 — Arduino

```
INICIO

Definir pantalla OLED
Definir servomotor
Definir conexión inalámbrica con Tótem 01

MIENTRAS el sistema esté encendido:

  Recibir mensaje desde Tótem 01

  SI mensaje = "sin presencia":
    Pantalla: "Sin presencia"
    Servo a 0°

  SI mensaje = "presencia lejana":
    Pantalla: "Alguien se aproxima"
    Servo a 45°

  SI mensaje = "presencia cercana":
    Pantalla: "Presencia cerca"
    Servo a 90°

  SI mensaje = "alguien está aquí":
    Pantalla: "Estoy aquí"
    Servo a 180°

  Esperar antes de volver a recibir

FIN
```
---

Diagrama representativo de distancia hecho por la magda!!

<img src="imagenes/diagrama.distancia.jpg" style="width: 50%;" alt="Mi imagen">
