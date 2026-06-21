# sesion-13

lunes 08 junio 2026

### Qué es nuestro proyecto?

#### Semáforo de Ocupación Remota

Este proyecto consiste en un sistema de monitoreo de ocupación en tiempo real, diseñado para indicar visualmente desde una ubicación remota si hay espacios disponibles en la sala o si se encuentra parcialmente ocupada o llena.

El sistema utiliza dos microcontroladores conectados a internet de forma independiente y comunicados a través de la plataforma en la nube Adafruit IO. En el primer edificio, una persona utilizando un Arduino R4 registra la entrada y salida de personas mediante dos botones físicos, llevando un conteo actualizado de cuántas personas hay en la sala. Este dato se envía automáticamente a Adafruit IO cada vez que alguien entra o sale.

En el segundo edificio, una Raspberry Pi Pico 2 recibe ese dato en tiempo real y lo traduce en una señal visual a través de un módulo semáforo RGB. Si la sala está vacía o con poca gente, el semáforo muestra verde. Si está a media capacidad, muestra amarillo. Si está llena, muestra rojo.

El objetivo del proyecto es evitar desplazamientos innecesarios, permitiendo saber de antemano si vale la pena ir a una sala antes de caminar hasta allá.





### Materiales

Arduino

- Cables macho macho (varios)
- 2 Botones 
- 1 Protoboard
- 2 Resistencias 10kΩ*

Raspberry

- módulo del semaforo RGB
- 2 resistencias 220Ω
- cables macho macho (varios)
- 1 Protoboard 



















### Pseudo Código

#### Arduino

INICIO
  contador = 0
  conectarse a WiFi
  conectarse a Adafruit IO

  REPETIR SIEMPRE:
    SI se aprieta botón "entró":
      contador = contador + 1
      publicar contador en Adafruit IO

    SI se aprieta botón "salió":
      SI contador > 0:
        contador = contador - 1
      publicar contador en Adafruit IO
FIN

#### Raspberry

INICIO
  conectarse a Adafruit IO (por el PC)

  REPETIR SIEMPRE:
    leer valor del feed "ocupacion" desde Adafruit IO

    SI valor es 0, 1 a 4:
      encender LED VERDE
      apagar LED amarillo
      apagar LED rojo

    SI valor es 5 o 9:
      apagar LED verde
      encender LED AMARILLO
      apagar LED rojo

    SI valor es 10 o más:
      apagar LED verde
      apagar LED amarillo
      encender LED ROJO
FIN
