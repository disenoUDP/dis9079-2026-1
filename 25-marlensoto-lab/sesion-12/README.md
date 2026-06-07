# sesion-12

lunes 01 junio 2026

# En el primer bloque de la clase 
Vimos de que iba a tratar y que debemos entregar.

## Requisitos del Examen

- Utilizar al menos un microcontrolador.
- Utilizar arrays (arreglos).
- Incorporar al menos un sensor y/o actuador, idealmente en múltiples instancias para justificar el uso de arreglos.
- Uno de los dos lados de la comunicación (envío o recepción) debe estar implementado utilizando un arreglo.
- Presentar un video demostrando el funcionamiento del proyecto entre facultades.
- Realizar una demostración en vivo durante la evaluación.

---

## Investigación: APIs

### ¿Qué es una API?

Una API (**Application Programming Interface**) es una interfaz que permite la comunicación e intercambio de información entre distintos sistemas, aplicaciones o dispositivos.

---

## Material de Referencia

Aarón nos mostró el libro que está escribiendo sobre pensamiento computacional:

- https://github.com/disenoUDP/apuntes-pensamiento-computacional

---

## Trabajo en Clases

Realizamos un ejercicio inicial para comenzar a investigar y definir el alcance del proyecto.

### Objetivo

Definir qué información vamos a enviar y recibir, utilizando una capa de abstracción más conceptual y menos técnica.

### Preguntas Guía

- ¿Qué queremos hacer?
- ¿Qué problema queremos resolver?
- ¿Qué queremos transmitir?
- ¿Quién enviará la información?
- ¿Quién recibirá la información?
- ¿Cómo se utilizará la información transmitida?

### Enfoque

Antes de definir aspectos técnicos como sensores, actuadores o protocolos de comunicación, debemos comprender claramente:

- Qué información queremos comunicar.
- Por qué es importante comunicarla.
- Cómo será utilizada por los usuarios del sistema.
- Qué impacto tendrá la comunicación entre los dispositivos.

---

## Propuesta de Proyecto

### Grupo 07

El proyecto busca visibilizar y traducir mundos que habitualmente pasan desapercibidos en la vida cotidiana, como el de las plantas y los hongos. La propuesta consiste en otorgar una voz a estos organismos y hacer perceptible su presencia, permitiendo que las personas interactúen con ellos desde una nueva perspectiva.

### ¿Qué queremos hacer?

Queremos desarrollar un sistema que capture información proveniente de una planta o un hongo y la transforme en una experiencia sonora interactiva. De esta manera, los datos obtenidos del organismo se traducen en sonidos que representan su estado y su relación con el entorno.

### ¿Qué queremos transmitir?

Buscamos transmitir la idea de que las plantas y los hongos son organismos vivos que interactúan constantemente con su ambiente. A través de la traducción de sus señales en sonido, se pretende generar una conexión más cercana entre las personas y estos seres vivos.

### ¿Qué se envía?

Se envían datos relacionados con la frecuencia o actividad registrada en la planta o el hongo, obtenidos mediante sensores conectados al sistema.

### ¿Qué se recibe?

Se recibe una traducción sonora de esos datos, interpretada como una especie de "voz" del organismo. Esta traducción se manifiesta mediante música generativa que cambia en tiempo real según las condiciones del entorno.

### Funcionamiento General

La planta actúa como un sintetizador vivo. El sistema analiza las variaciones de su actividad y las transforma en parámetros sonoros.

- Si el entorno se encuentra tranquilo y estable, la música generada presenta sonidos suaves y armónicos.
- Si existe mayor movimiento o actividad alrededor de la planta, el sonido se vuelve más dinámico, intenso o agudo.
- Los cambios ambientales modifican continuamente la composición sonora, creando una experiencia única y en constante evolución.

### Objetivo

El objetivo es hacer visible e interpretable un mundo que normalmente permanece oculto, utilizando la tecnología como un puente entre los seres humanos y los organismos vegetales, transformando datos biológicos en una experiencia sensorial y artística.
