# sesion-12

lunes 01 junio 2026

## Lo que trabajamos en clase

En esta clase comenzamos a pensar la idea para el proyecto de examen. Partimos conversando sobre cosas que suceden en la naturaleza y que normalmente pasan desapercibidas, como el movimiento de las hojas por el viento o los cambios que ocurren en las plantas durante el día sin que las personas los noten.

A partir de eso surgieron varias preguntas, por ejemplo: ¿cómo se mueve una hoja durante el día?, ¿las plantas reaccionan a lo que ocurre a su alrededor?, ¿es posible mostrar esos procesos de una forma visible para las personas?

## Ideas que aparecieron

Una de las primeras ideas fue trabajar con el movimiento de las hojas y transformar esos movimientos en dibujos o patrones visuales.

Después comenzamos a investigar sobre las señales eléctricas presentes en las plantas y surgió la idea de "darles voz", es decir, traducir sus impulsos o cambios internos a algún lenguaje que las personas pudieran percibir.

Pensamos en distintas posibilidades:

- Traducir los datos a sonidos.
- Crear imágenes generativas.
- Utilizar patrones de luces.
- Combinar elementos visuales y sonoros.

## Desarrollo de la propuesta

La idea fue tomando forma hasta llegar a la propuesta actual: utilizar una planta viva como sensor del entorno.

En vez de usar cámaras o micrófonos, queremos captar pequeñas variaciones eléctricas de la planta para observar cómo responde a distintos estímulos presentes en la facultad, como movimiento de personas, vibraciones o actividad general del espacio.

La intención es mostrar que la planta también forma parte de ese entorno y que constantemente está reaccionando a lo que ocurre a su alrededor.

## Funcionamiento pensado hasta ahora

La planta se conectaría a electrodos para obtener señales eléctricas.

Estas señales serían leídas mediante un módulo ADS1115 y enviadas a un Arduino UNO R4 WiFi.

Luego los datos viajarían por WiFi hacia otro dispositivo, como una Raspberry Pi Pico 2 W o un computador.

Finalmente, esos datos se transformarían en visualizaciones o sonidos que cambiarían según la actividad detectada.

```text
Planta
 ↓
ADS1115
 ↓
Arduino UNO R4 WiFi
 ↓
WiFi
 ↓
Raspberry Pi Pico / PC
 ↓
Visualización o sonido
```

## Dudas y decisiones

Durante la conversación surgió la duda de si trabajar únicamente con sonido o con elementos visuales.

La opción de los sonidos es interesante porque refuerza la idea de que la planta tiene una "voz", pero también puede ser más difícil de implementar y de interpretar.

Por eso también consideramos utilizar visualizaciones generativas o luces que cambien según los datos recibidos.

Todavía estamos evaluando cuál de estas opciones funcionaría mejor para el examen.

## Próximos pasos

- Investigar mejor cómo obtener señales eléctricas de una planta.
- Definir si la visualización será sonora, visual o una combinación de ambas.
- Revisar qué componentes necesitamos para realizar las primeras pruebas.
- Comenzar a planificar el flujo completo del sistema.
