# sesion-03

lunes 23 marzo 2026

---

## Apuntes

En dos semanas más es la `solemne 1` 

- Cuidar las patitas del Arduino Uno R4

Ver el primer capítulo de Monty Python

Usaremos un nuevo microcontrolador (Raspberry pi / Pico 2 W) donde solo recibiremos mensajes y el Arduino Uno R4 solo enviaremos mensajes. 

### Microcontrolador: Raspberry Pi Pico 2 W

- La fundación inglesa Raspberry Pi partió lanzando computadores en el 2009. No tiene periféricos (no mouse, etc). Raspberry Pi lanzó su propio chip microcontrolador, el RP2040 y la sucesora RP2050, que son el corazón de las placas Raspberry Pi Pico y Raspberry Pi Pico 2 respectivamente.
- La Raspberry Pi Pico 2 W es una placa de desarrollo de microcontroladores de bajo costo y alto rendimiento, diseñada por Raspberry Pi. Es la segunda generación de su serie "Pico", destacando por integrar conectividad Wi-Fi 802.11n y Bluetooth 5.2. Basada en el nuevo chip RP2350, ofrece doble núcleo, mayor potencia y seguridad mejorada para proyectos IoT y electrónica.

Personal Computer (PC)

- `Harvard Mark 1:` computador del año de la pera que con suerte sumaba (jajaja)
- `Computer mainframe:` unidad central
- `Atari 2600:` computador para jugar
- `Commodore 64`
- `Spectrum ZX`
- Microcontrolador (Arduino): cosas cumas y lentas
- Computadores (Raspberry): cosas sostificadas y bacanes

[RASPBERRY PI](https://www.raspberrypi.com/)

Raspberry Pi Compute Module 5

- Korg raspberry
- Monome.org > <https://monome.org/>
- Critter and guitari > <https://www.critterandguitari.com/>

RP2350 chip

|unidades de medida|
|---|
|centi|
|milli|
|micro|
|nano|
|pico|
|fento|

- `Beagleboard.org:` hizo una alianza con un arte en inglaterra.
- `Bela.io:` es un be adaptado pero solo para audios.
- `NIME.org:` donde hay papers (como entender hacer audios extraños, investigar)
- `Meet Daisy:` es un microcontrolador para audios (un mega microcontrolador)
- Electro-smith
- `Chompi sampler:` hay un electro-smith de 20 lucas

### Descargar: Visual Studio Code

Claude code: Ia para generar códigos

- Extensions: lugar para descargar
- Rust: lenguaje por el cual quieren cambiar C++, es más seguro
- Python: lenguaje para computadores
  - micropython: es más sencillo
- Board type: seleccionar la placa
- Select Pico SDK version: seleccionar la veersion
- SPI: se conecta a una pantalla
- I2C: menos conexiones
- Stdio support: input / ouptup
- Pico W onboard LED
- Build: es como el subproducto del final, donde hago cambios y ahí quedan
- Lo importante es que tenga el: `nombre.cpp` (apretar el botón de hacerlo con c++)
- Raspberry Pi, tiene un Main, todo lo que esta adentro de main ocurre,

`Usaremos Visual Studio Code`

Este funciona con C++ y con Phyton.

### Folders
- .vscode: Cosas que necesita nuestro compu
- build: Compilados de, no lo tocamos
- .gitignore: No se comparten
- nombreDelArchivo.cpp: El archivo que creamos. (el importante)
- CMakeLists.txt: Cosas que pasan, bacan x ti.
- Arduino: Setup y Loop
- Raspberry pi: Main -> Todo lo que esta dentro de main ocurre en ese orden.


### Ejemplo 

Prendió una lucecita permanente

```cpp
#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/spi.h"
#include "pico/cyw43_arch.h"

// SPI Defines
// We are going to use SPI 0, and allocate it to the following GPIO pins
// Pins can be changed, see the GPIO function select table in the datasheet for information on GPIO assignments
#define SPI_PORT spi0
#define PIN_MISO 16
#define PIN_CS   17
#define PIN_SCK  18
#define PIN_MOSI 19




int main()
{
    stdio_init_all();

    // Initialise the Wi-Fi chip
    if (cyw43_arch_init()) {
        printf("Wi-Fi init failed\n");
        return -1;
    }

    // SPI initialisation. This example will use SPI at 1MHz.
    spi_init(SPI_PORT, 1000*1000);
    gpio_set_function(PIN_MISO, GPIO_FUNC_SPI);
    gpio_set_function(PIN_CS,   GPIO_FUNC_SIO);
    gpio_set_function(PIN_SCK,  GPIO_FUNC_SPI);
    gpio_set_function(PIN_MOSI, GPIO_FUNC_SPI);
    
    // Chip select is active-low, so we'll initialise it to a driven-high state
    gpio_set_dir(PIN_CS, GPIO_OUT);
    gpio_put(PIN_CS, 1);
    // For more examples of SPI use see https://github.com/raspberrypi/pico-examples/tree/master/spi

    // Example to turn on the Pico W LED
    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1);

    while (true) {
        printf("Hello, world!\n");
        sleep_ms(1000);
    }
}
```

Prender la lucecita 3 veces y que qued encendida :)

```cpp
#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/spi.h"
#include "pico/cyw43_arch.h"

// SPI Defines
// We are going to use SPI 0, and allocate it to the following GPIO pins
// Pins can be changed, see the GPIO function select table in the datasheet for information on GPIO assignments
#define SPI_PORT spi0
#define PIN_MISO 16
#define PIN_CS   17
#define PIN_SCK  18
#define PIN_MOSI 19




int main()
{
    stdio_init_all();

    // Initialise the Wi-Fi chip
    if (cyw43_arch_init()) {
        printf("Wi-Fi init failed\n");
        return -1;
    }

    // SPI initialisation. This example will use SPI at 1MHz.
    spi_init(SPI_PORT, 1000*1000);
    gpio_set_function(PIN_MISO, GPIO_FUNC_SPI);
    gpio_set_function(PIN_CS,   GPIO_FUNC_SIO);
    gpio_set_function(PIN_SCK,  GPIO_FUNC_SPI);
    gpio_set_function(PIN_MOSI, GPIO_FUNC_SPI);
    
    // Chip select is active-low, so we'll initialise it to a driven-high state
    gpio_set_dir(PIN_CS, GPIO_OUT);
    gpio_put(PIN_CS, 1);
    // For more examples of SPI use see https://github.com/raspberrypi/pico-examples/tree/master/spi

    // Example: turn on the Pico W LED and blink it 3 times
    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1);
    printf("LED encendida. Parpadeo 3 veces...\n");

    for (int i = 0; i < 3; i++) {
        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 0); // LED off
        sleep_ms(250);
        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1); // LED on
        sleep_ms(250);
    }

    printf("Listo: parpadeo completado. LED queda encendida.\n");

    while (true) {
        tight_loop_contents();
    }
}
```

Que la luz parpadee constantemente

```cpp
#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/spi.h"
#include "pico/cyw43_arch.h"

// SPI Defines
// We are going to use SPI 0, and allocate it to the following GPIO pins
// Pins can be changed, see the GPIO function select table in the datasheet for information on GPIO assignments
#define SPI_PORT spi0
#define PIN_MISO 16
#define PIN_CS   17
#define PIN_SCK  18
#define PIN_MOSI 19




int main()
{
    stdio_init_all();

    // Initialise the Wi-Fi chip
    if (cyw43_arch_init()) {
        printf("Wi-Fi init failed\n");
        return -1;
    }

    // SPI initialisation. This example will use SPI at 1MHz.
    spi_init(SPI_PORT, 1000*1000);
    gpio_set_function(PIN_MISO, GPIO_FUNC_SPI);
    gpio_set_function(PIN_CS,   GPIO_FUNC_SIO);
    gpio_set_function(PIN_SCK,  GPIO_FUNC_SPI);
    gpio_set_function(PIN_MOSI, GPIO_FUNC_SPI);
    
    // Chip select is active-low, so we'll initialise it to a driven-high state
    gpio_set_dir(PIN_CS, GPIO_OUT);
    gpio_put(PIN_CS, 1);
    // For more examples of SPI use see https://github.com/raspberrypi/pico-examples/tree/master/spi

    // Example: turn on the Pico W LED and blink it continuously
    printf("LED parpadeando constantemente...\n");

    while (true) {
        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 0); // LED off
        sleep_ms(250);
        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1); // LED on
        sleep_ms(250);
    }
}
```

## Rúbrica solemne 1 / 06-04

la nota tiene 1 punto base más 6 puntos evaluados.

`Individual:`

1 punto por calidad de la presentación oral
1 punto por bitácora personal textual y visual del trabajo en clases e investigación personal
1 punto por aportes al README.md grupal de texto y visuales explicativas, por las referencias

`Grupal:`

1 punto por diagrama de flujo del proyecto
1 punto por calidad del código fuente para enviar y para recibir
1 punto por funcionamiento del sistema
1 punto: el sistema puede enviar y recibir mensajes
0.5 puntos: el sistema solamente envía o recibe mensajes
0.3 puntos: intentos de enviar o recibir mensajes, aunque no funcionen
0.0 puntos: los intentos no se entienden, no tienen comentarios, están desordenados
