# sesion-12

lunes 01 junio 2026

# Explicación del examen

### Introducción

En la clase de hoy el profesor explicó el examen final del curso, llamado **"Estudios inalámbricos poéticos"**. El objetivo general es desarrollar un sistema capaz de comunicar información de forma inalámbrica y presentar una experiencia o interacción a partir de esos datos.

También se explicaron algunos requisitos mínimos que deben estar presentes en el proyecto.

| Requisito         | Descripción                                                                              |
| ----------------- | ---------------------------------------------------------------------------------------- |
| Arreglos (arrays) | Deben utilizarse dentro de la lógica del sistema.                                        |
| Iteraciones       | Uso de ciclos para procesar información.                                                 |
| Transparencia     | Documentar el proceso, decisiones tomadas, código utilizado y uso de herramientas de IA. |

## Investigación y referentes

Durante la clase se mostraron algunos ejemplos relacionados con APIs y sistemas que utilizan información proveniente de fuentes externas.

Uno de los ejemplos fue **The Cat API**, que sirve para entender cómo un sistema puede recibir datos desde internet y utilizarlos para generar distintas acciones.

También se mencionó **Patrimonio Bot**, un proyecto que utiliza información disponible en línea para generar contenido de manera automática.

Estos ejemplos ayudaron a entender cómo los datos pueden convertirse en experiencias o interacciones más allá de una simple visualización.

## Propuesta del Grupo 07: "La Voz de las Plantas"

Nuestro grupo presentó la idea llamada **"La Voz de las Plantas"**.

La propuesta consiste en captar señales eléctricas provenientes de una planta y utilizar esos datos para generar respuestas visuales o sonoras. La idea inicial es que los cambios detectados puedan transformarse en sonido, permitiendo representar de alguna forma la actividad de la planta y su relación con el entorno.

## Conversación y retroalimentación

Después de presentar la propuesta, los demás grupos hicieron preguntas para ayudarnos a definir mejor algunos aspectos técnicos.

### Pregunta

> ¿Qué es lo que va a detectar la frecuencia?

### Respuesta

Explicamos que la idea es medir pequeñas variaciones de voltaje presentes en la planta. Para lograrlo será necesario utilizar un módulo ADS1115, ya que ofrece una mayor precisión que la disponible directamente en la Raspberry Pi Pico.

### Pregunta

> ¿A qué tipo de sonidos se traducirían esos datos? ¿Tendría un enfoque musical?

### Respuesta

Se comentó que la intención es trabajar con música generativa. Dependiendo de las variaciones registradas por la planta, el sistema podría modificar parámetros como intensidad, ritmo o tono para producir diferentes resultados sonoros.

A partir de esta conversación quedó más claro que el ADS1115 será una pieza importante dentro del proyecto, ya que permitirá obtener lecturas más precisas para las pruebas.

## Organización del equipo

Durante la clase también conversamos sobre las áreas principales de trabajo.

| Área          | Responsabilidad                                                          |
| ------------- | ------------------------------------------------------------------------ |
| Hardware      | Conectar el ADS1115 y realizar pruebas de lectura.                       |
| Software      | Procesar los datos obtenidos y transformarlos en información utilizable. |
| Comunicación  | Resolver la transmisión inalámbrica entre dispositivos.                  |
| Documentación | Mantener las bitácoras y registrar el proceso de trabajo.                |

## Reflexión

La retroalimentación de los compañeros ayudó a identificar algunos puntos que todavía necesitan mayor definición, especialmente en la forma en que los datos serán interpretados y transformados en sonido.

Por ahora, uno de los desafíos principales será conseguir mediciones estables y entender qué información realmente estamos obteniendo desde la planta antes de diseñar la experiencia final.

## Tareas pendientes

* [ ] Investigar más sobre medición de señales eléctricas en plantas.
* [ ] Revisar opciones de generación sonora.
* [ ] Profundizar en el uso del ADS1115.
* [ ] Definir la comunicación inalámbrica entre dispositivos.

---

### Anexo: Apuntes de clase

Estas son las indicaciones entregadas por el profesor para el examen.

## Presentación del proyecto

* Explicar el proyecto en un párrafo de al menos cuatro líneas.
* Buscar referentes relacionados.
* Definir palabras clave para orientar la propuesta.

## Organización de grupos

* Grupos de 3 a 4 integrantes.
* Excepciones puntuales para estudiantes con promedio superior a 6,7.

## Entregables individuales

* [ ] Investigación sobre APIs.
* [ ] Dos bitácoras de proceso.

## Entregables grupales

* [ ] Video demostrativo.
* [ ] Funcionamiento en vivo entre dos extremos de la sala.
* [ ] Código y documentación ordenados.


