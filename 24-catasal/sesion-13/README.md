# sesion-13

lunes 08 junio 2026

## proyecto 

Este proyecto consiste en un sistema de monitoreo de ocupación en tiempo real, diseñado para indicar visualmente desde una ubicación remota si una sala está disponible, parcialmente ocupada o llena.

El sistema utiliza dos microcontroladores conectados a internet de forma independiente y comunicados a través de la plataforma en la nube Adafruit IO. En el primer edificio, una persona utilizando un Arduino R4 registra la entrada y salida de personas mediante dos botones físicos, llevando un conteo actualizado de cuántas personas hay en la sala. Este dato se envía automáticamente a Adafruit IO cada vez que alguien entra o sale.

En el segundo edificio, una Raspberry Pi Pico 2 recibe ese dato en tiempo real y lo traduce en una señal visual a través de un módulo semáforo RGB. Si la sala está vacía o con poca gente, el semáforo muestra verde. Si está a media capacidad, muestra amarillo. Si está llena, muestra rojo.
El objetivo del proyecto es evitar desplazamientos innecesarios, permitiendo saber de antemano si vale la pena ir a una sala antes de caminar hasta allá.

| materiales | costo | cantidad|
|------------|-------|---------|
|Modulo Luz Led de Semaforo| 1.500 | 1       |
|pack de resistencias | 4.990 |600|
|pico 2w         |   | 1        |
|arduino         |   | 1        |
