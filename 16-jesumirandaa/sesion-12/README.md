# sesion-12

lunes 01 junio 2026

## Preparación para Examen

**Grupo 01**
- [magdalenabalart](https://github.com/magdalenabalart)
- [jesumirandaa](https://github.com/jesumirandaa)
- [ccarlabelenn](https://github.com/ccarlabelenn)

---

## ¿Qué es una API?

Aarón nos habla sobre API como introducción a la clase.

Una **API** (Application Programming Interface) es un puente que permite que dos sistemas se comuniquen entre sí. En el caso de Adafruit IO, su API permite que tu microcontrolador (Raspberry, Arduino, etc.) envíe y reciba datos desde la nube de Adafruit usando reglas definidas.

---

## Propuesta 01 — Inicial

*pensando... y pensando... y pensando...*

El proyecto consiste en una lámpara-altar que reacciona ante la cercanía de una persona, transformando su presencia física en una señal luminosa y afectiva. A medida que alguien se acerca, la luz comienza a encenderse progresivamente, como si el objeto despertara o reconociera esa presencia. Cuando la luz alcanza su máxima intensidad, se envía una señal a un segundo dispositivo, comunicando que alguien estuvo ahí, recordó o se hizo presente. La propuesta convierte la luz en un espacio de memoria y compañía, donde acercarse al objeto no solo activa un sistema, sino que construye una forma poética de decir: estoy aquí, te recuerdo o sigo vinculado a ti.

---

## Correcciones y preguntas

**[montoyamoraga](https://github.com/montoyamoraga)**
> En vez de lámpara-altar, creo que es bello dejarlo en altar, porque un altar no es una figura concreta definida o incluso comercial, entonces puede tener una lámpara / luz sin tener que por eso dejar de ser un altar, no necesita el nombre lámpara-altar.

> Pensar en límites, contexto, bordes, comportamientos esperados.

**Grupo 06 — Valentina Ruz, Sofía Cartes, Monserrat Paredes**
> Nos gusta la idea, pero tal vez debería tener condiciones o límites de proximidad o que se encienda cuando realmente pase algo.

> Tenemos una duda: si me alejo y me acerco constantemente, ¿la luz comenzará a encender y apagar o quedará prendida?

**Grupo 01 — Respuesta**

Vamos a crear una condición que, después de cierta cantidad de segundos que la persona se mantiene cerca, la luz se enciende. De lo contrario queda apagada.

---

## Propuesta 02 — Corregida

El proyecto consiste en un altar que reacciona ante la cercanía de una persona, transformando su presencia física en una señal luminosa y afectiva. Sin embargo, la luz no responde a una cercanía casual, sino al gesto de quedarse: no basta con pasar cerca, hay que permanecer. A medida que alguien se aproxima y sostiene su presencia dentro de ciertos límites definidos, la luz comienza a encenderse progresivamente, como si el objeto despertara o reconociera una intención. Si la persona se aleja antes de tiempo, la luz vuelve lentamente a apagarse y no se envía ninguna señal. Solo cuando la presencia se mantiene hasta que la luz alcanza su máxima intensidad, se comunica a un segundo dispositivo que alguien realmente estuvo ahí, recordó o decidió hacerse presente. La propuesta convierte la luz en un ritual de memoria y compañía, donde acercarse al objeto no solo activa un sistema, sino que construye una forma poética de decir: estoy aquí, te recuerdo o sigo vinculado a ti.
