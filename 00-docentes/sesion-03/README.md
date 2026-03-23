# sesion-03

lunes 23 marzo 2026

esta semana seguimos trabajando con los grupos de la semana pasada.

hicimos 11 grupos, y repartimos los Arduino Uno R4 WiFi entre ellos, para que puedan trabajar con ellos durante el semestre.

## lista de gente

| github                | grupo |
| --------------------- | ----- |
| agustinaaceituno      | 10    |
| antokiaraa            | 03    |
| AlegriaColoma         | 04    |
| benjaminalvarez21     | 11    |
| josefa-kristina       | 07    |
| arevalourra           | 06    |
| magdalenabalart       | 02    |
| sofiacartes           | 01    |
| tomascatri            | 03    |
| felipecaurapan        | 05    |
| Anaysval              | 11    |
| brauliofigueroa2001   | TBD   |
| AntFuentealba         | 10    |
| Guilleibanez          | TBD   |
| antolavalle           | 04    |
| jesumirandaa          | 02    |
| ccarlabelenn          | 02    |
| Camila-Parada         | 05    |
| Monserrat-Paredes     | 01    |
| paredesvania          | 05    |
| isipm08               | 06    |
| TBD                   | TBD   |
| vxlentiinaa           | 01    |
| angel-udp             | 03    |
| catasal               | 04    |
| marlensoto-lab        | TBD   |
| DebSkar               | 07    |
| Luisaatoro9           | TBD   |
| nicolasvaldesgreve    | 06    |
| cristobalvergarasilva | 07    |
| marcezm               | TBD   |

## lista por grupos

### grupo-01

* sofiacartes
* Monserrat-Paredes
* vxlentiinaa

### grupo-02

* magdalenabalart
* jesumirandaa
* ccarlabelenn

### grupo-03

* antokiaraa
* tomascatri
* angel-udp

### grupo-04

* AlegriaColoma
* antolavalle
* catasal

### grupo-05

* felipecaurapan
* Camila-Parada
* paredesvania

### grupo-06

* arevalourra
* isipm08
* nicolasvaldesgreve

### grupo-07

* josefa-kristina
* DebSkar
* cristobalvergarasilva

### grupo-08

| brauliofigueroa2001   | TBD   |
| Guilleibanez          | TBD   |
| TBD                   | TBD   |
| marlensoto-lab        | TBD   |
| Luisaatoro9           | TBD   |
| marcezm               | TBD   |

### grupo-09

| brauliofigueroa2001   | TBD   |
| Guilleibanez          | TBD   |
| TBD                   | TBD   |
| marlensoto-lab        | TBD   |
| Luisaatoro9           | TBD   |
| marcezm               | TBD   |

### grupo-10

* agustinaaceituno
* AntFuentealba

### grupo-11

* benjaminalvarez21
* Anaysval

## recordatorios metolodogía de trabajo conjunto

* estar en discord
* justificar inasistencias
* silenciar los temas que no les son relevantes
* cuidar los materiales

## nueva placa con microcontrolador: raspberry pi pico 2 w

la fundación inglesa Raspberry Pi partió lanzando computadores de bajo costo en el año 2009. hoy van en la versión 5 de su computador Raspberry Pi, también existe una versión 500+ que está embebida dentro de un teclado, y existe también el modelo Compute Module 5, que está diseñado para su incorporación en otros productos, y el modelo Raspberry Pi Zero, que es una versión aún más barata y pequeña.

* Raspberry Pi 5:
  * $205 USD
  * <https://www.raspberrypi.com/products/raspberry-pi-5/>
* Raspberry Pi 500+:
  * $260 USD
  * <https://www.raspberrypi.com/products/raspberry-pi-500-plus/>
* Raspberry Pi Compute Module 5:
  * $55 USD
  * <https://www.raspberrypi.com/products/compute-module-5/>
* Raspberry Pi Zero 2 W:
  * $15 USD
  * <https://www.raspberrypi.com/products/raspberry-pi-zero-2-w/>
  * Obsolecencia: enero 2030

además de estos computadores, Raspberry Pi lanzó su propio chip microcontrolador, el RP2040 y la sucesora RP2050, que son el corazón de las placas Raspberry Pi Pico y Raspberry Pi Pico 2 respectivamente.

Ambas placas tienen una versión con comunicaciones inalámbricas que reciben el sufijo W, en este curso usaremos la Raspberry Pi Pico 2 W, la más reciente de esta familia y la más completa.

* Raspberry Pi Pico 2 W:
  * desde 5 USD
  * <https://www.raspberrypi.com/products/raspberry-pi-pico-2/>
  * inalámbrico: 2.4GHz 802.11n wireless LAN, Bluetooth 5.2
  * programable con C, C++ o Python
  * Usa el chip RP2050.

## otros microcomputadores y microcontroladores

* BeagleBoard <https://www.beagleboard.org/>
* Bela Platform <https://bela.io/>
* Electro-Smith <https://electro-smith.com/>

## instalación de entorno de desarrollo para Raspberry Pi Pico 2 W

para la placa Arduino usaremos el software Arduino IDE que ya instalamos.

para la placa Raspberry Pi usaremos una herramienta de desarrollo profesional llamada Visual Studio Code.

dentro de Visual Studio Code, entramos a sección `Extensions`, y buscamos la extensión `Raspberry Pi Pico` de autores `Raspberry Pi`, y la instalamos.

revisamos el documento `Getting Started` que está en esta misma carpeta. también se incluye la versión completa de la documentación.

## solemne-01

estos grupos de trabajo se mantendrán hasta el fin de la solemne-01, que es en 2 semanas más.

el desafío es enviar un mensaje desde la placa Raspberry Pi Pico 2W, y recibirla en la placa Arduino Uno R4 WiFi, y mostrarla en el monitor serial o similar.

este desafío es de código y orden, no de conexiones con cables.

el mínimo que esperamos es que la placa Arduino envíe mensajes a una cierta frecuencia, y que estos mensajes prendan y apaguen la luz incorporada de la placa Raspberry Pi.

queremos que cada grupo sea divergente, que envíen mensajes distintos, que funcionen a distintas frecuencias, o que incluso si quieren expandan la interacción, agregando un botón en la Raspberry Pi para enviar distintos mensajes, o agregando un LED extra o un motor o similar a la placa Arduino para que reaccione a los mensajes.

esta solemne será difícil y se valorará el orden, el esfuerzo, el intento.

para la solemne 02

cada persona tendrá una nota, que tendrá una mitad grupal y la otra mitad individual.
