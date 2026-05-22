# sesion-10

lunes 18 mayo 2026

Preparación Solemne 2 — Sistemas de comunicación y rediseño de proyecto

---

## Desarrollo de la clase

En esta sesión nos dedicamos principalmente a la preparación de la Solemne 2 del ramo, trabajando en conjunto con Agustina Aceituno. El foco estuvo en definir la arquitectura del sistema que íbamos a implementar, especialmente en relación con la comunicación entre placas y el uso de sensores y actuadores.


## Idea inicial del proyecto

En una primera instancia, la propuesta consistía en un sistema dividido en dos partes:

### Emisor (Arduino)
- Un Arduino funcionando como emisor de datos.
- Conectado a un potenciómetro.
- El potenciómetro entregaba valores analógicos según su posición (izquierda/derecha).
- Estos valores serían enviados hacia otro dispositivo.

### Receptor (Raspberry Pi Pico 2 W)
- Una Raspberry Pi Pico 2 W funcionando como receptor.
- Recibía los datos enviados por el Arduino.
- Un servomotor se movía en función de la posición del potenciómetro:
  - Movimiento hacia la derecha
  - Movimiento hacia la izquierda

La idea general era simular un sistema de control remoto donde una placa controla físicamente a otra.



## Ajuste de la arquitectura del sistema

Más adelante, Aarón sugirió un cambio en la estructura del proyecto.

### Nueva propuesta:
- El Arduino pasaría a ser el receptor.
- La Raspberry Pi Pico 2 W pasaría a ser el emisor.

Este cambio se propuso para mejorar la lógica del flujo de datos y simplificar la integración con la nube y la comunicación entre dispositivos.


## Dificultades técnicas

Durante la clase surgieron algunas dificultades relacionadas con:

- Instalación de Python en los equipos.
- Configuración de CircuitPython en la Raspberry Pi Pico 2 W.
- Problemas iniciales de conexión y entorno de desarrollo.

Estas dificultades hicieron que el avance del proyecto fuera más lento de lo esperado.

## Decisión de trabajo en grupo

Debido a las complicaciones técnicas y para optimizar el desarrollo del proyecto, se decidió fusionar los grupos.

### Nuevo grupo:
- Agustina Aceituno
- Benjamín Álvarez
- Anays Cornejo
- Antonia Fuentealba

Esta decisión permitió reorganizar tareas, compartir conocimientos y avanzar de forma más eficiente en la preparación de la solemne.


# Conclusión de la sesión

La clase estuvo centrada en la planificación del proyecto final más que en la implementación directa. Se definieron posibles arquitecturas de comunicación entre dispositivos, se discutieron mejoras en la lógica del sistema y se reorganizó el trabajo en equipo para enfrentar de mejor manera la complejidad técnica del proyecto.
