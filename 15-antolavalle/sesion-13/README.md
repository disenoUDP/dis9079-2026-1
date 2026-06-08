# sesion-13

lunes 08 junio 2026

clase para trabajar en el proyecto del examen

Cambiamos la idea principal de hacer un semáforo con un estado de emergencia, vamos a seguir utilizando el modulo de luz led de semáforo pero con otro objetivo, el cual es notificar cuando se puedan ocupar ciertas salas, nuestra primera idea era con el casino pero al ser una sala grande y de mucho transito de gente decidimos pasar a la biblioteca más especificamente a las salas de estudio pero no sentimos que sea muy conveniente asi que al final nos decidimos con la sala de computadores, un lugar pequeño donde cada cierto tiempo hay harto transito de gente pero posible para poder seguir con el proyecto.

¿De que trata el proyecto? Este proyecto consiste en un sistema de monitoreo de ocupación en tiempo real, diseñado para indicar visualmente desde una ubicación remota si una sala está disponible, parcialmente ocupada o llena.

El sistema utiliza dos microcontroladores conectados a internet de forma independiente y comunicados a través de la plataforma en la nube Adafruit IO. En el primer edificio, una persona utilizando un Arduino R4 registra la entrada y salida de personas mediante dos botones físicos, llevando un conteo actualizado de cuántas personas hay en la sala. Este dato se envía automáticamente a Adafruit IO cada vez que alguien entra o sale.

En el segundo edificio, una Raspberry Pi Pico 2 recibe ese dato en tiempo real y lo traduce en una señal visual a través de un módulo semáforo RGB. Si la sala está vacía o con poca gente, el semáforo muestra verde. Si está a media capacidad, muestra amarillo. Si está llena, muestra rojo.

El objetivo del proyecto es evitar desplazamientos innecesarios, permitiendo saber de antemano si vale la pena ir a una sala antes de caminar hasta allá.
