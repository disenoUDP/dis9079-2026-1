# solemne-02

## Integrantes
- Braulio Figueroa / github: [brauliofigueroa2001](https://github.com/brauliofigueroa2001)
- Luisa Toro / github: [Luisaatoro9](https://github.com/Luisaatoro9)
- Marlén Soto / github: [marlensoto-lab](https://github.com/marlensoto-lab)
- Marcela Zúñiga / github: [marcezm](https://github.com/marcezm)


## Descripción textual del proyecto Trabajo en clases 
Inicialmente, nuestro proyecto consistía en desarrollar un sistema IoT distribuido utilizando una Raspberry Pi, un Arduino UNO R4 WiFi, un sensor ultrasónico HC-SR04 y un micro servo motor SG90, conectados mediante la plataforma Adafruit IO utilizando el protocolo MQTT.

La Raspberry Pi tendría la función de controlar el sensor ultrasónico HC-SR04, medir la distancia de un objeto y enviar periódicamente los datos obtenidos hacia Adafruit IO a través de internet. Posteriormente, el Arduino UNO R4 WiFi consultaría la información almacenada en la plataforma y, según la distancia recibida, controlaría el movimiento del servo motor SG90.

El objetivo principal del proyecto era demostrar la comunicación inalámbrica entre distintos dispositivos mediante tecnologías IoT, integrando la adquisición de datos físicos, la transmisión en la nube y el control remoto de actuadores en tiempo real. Además, para evitar saturar el servicio gratuito de Adafruit IO, el sistema incorporaría intervalos de tiempo entre cada envío de datos.

## Proceso realizado en clases

Durante el desarrollo del proyecto comenzamos realizando el cableado de la Raspberry Pi junto con el sensor de distancia. Debido a que no teníamos experiencia previa trabajando con este tipo de sensores ni con la Raspberry Pi, fue necesario investigar profundamente el funcionamiento del hardware y sus conexiones, proceso que nos tomó aproximadamente una hora.

Posteriormente, trabajamos en la programación del sensor y del botón, pero surgieron diversas dificultades relacionadas con librerías necesarias para el funcionamiento del sistema y múltiples errores en el código. Intentamos resolver estos problemas durante otra hora adicional, investigando posibles soluciones y realizando distintas pruebas, pero no logramos que el sistema funcionara correctamente dentro del tiempo disponible.

Finalmente, debido a la falta de tiempo para continuar avanzando con nuestro proyecto inicial, tuvimos que incorporarnos al Grupo 10, integrado por Braulio Figuerio y Luisa Torres, con el fin de continuar el trabajo práctico de la clase.

## Materiales usados en clases 
| Material | Cantidad | Precio aproximado (CLP) |
|---|---:|---:|
| Raspberry Pi | 1 | $151.790 |
| Arduino UNO R4 WiFi | 1 | $34.990 |
| HC-SR04 Ultrasonic Sensor | 1 | $3.290 |
| SG90 Micro Servo Motor | 1 | $1.830 |
| Protoboard | 1 | $2.590 |
| Cables Dupont | 1 pack | $1.990 |
| Cable USB | 1 | $3.000 |
| Fuente de alimentación USB | 1 | $8.000 |

## Descripción textual del proyecto

## Sensor usado
### Botón pulsador de 4 pines

El sensor utilizado en esta etapa del proyecto fue un botón pulsador de 4 pines, empleado como entrada digital para activar o desactivar el envío de datos hacia Adafruit IO.

Su función principal dentro del sistema es actuar como una “puerta de control”, permitiendo decidir cuándo la Raspberry Pi Pico 2W puede enviar información a la nube. De esta manera, se evita la saturación del servidor gratuito de Adafruit IO y se optimiza la comunicación entre los dispositivos IoT.

## Actuador usado
### Luz LED

El actuador utilizado en el proyecto fue una luz LED, empleada para representar visualmente la recepción de datos enviados desde la Raspberry Pi Pico 2W hacia el Arduino UNO R4 WiFi mediante Adafruit IO.

Su función principal dentro del sistema es encenderse o apagarse dependiendo del estado del botón conectado a la Raspberry Pi Pico 2W, permitiendo demostrar la comunicación inalámbrica y el control remoto de actuadores en tiempo real mediante tecnologías IoT.
## Código usado para enviar

### Proceso
Durante las primeras pruebas realizamos la ejecución del código inicial, pero el sistema no funcionó correctamente, ya que la luz LED no lograba encenderse. Debido a esto, fue necesario revisar y modificar el código para identificar el problema.

Con ayuda de nuestro compañero, nos dimos cuenta de que nuestra Raspberry Pi Pico 2W no contaba con algunas librerías necesarias para el correcto funcionamiento del programa, por lo que procedimos a instalarlas y configurar nuevamente el entorno de trabajo.

Además, observamos que la visualización del proyecto en Visual Studio Code aparecía con el ícono de Adobe Illustrator, lo que inicialmente nos generó confusión respecto al tipo de archivo y su configuración dentro del programa. Luego de revisar esto, continuamos realizando ajustes hasta lograr avanzar correctamente con el desarrollo del proyecto.

## Código usado para recibir 

### Proceso
Al inicio realizamos una prueba utilizando un código desarrollado previamente por Luisa Toro, el cual ya había sido comprobado y funcionaba correctamente. Sin embargo, quisimos intentar realizar el proceso por nuestra cuenta, lo que provocó que durante el desarrollo surgieran distintos errores, principalmente relacionados con el cableado.

Uno de los primeros problemas fue que tuvimos que cambiar la conexión del cable desde 5V a 3.3V, ya que la conexión inicial solo permitía comprobar si la luz LED funcionaba, pero no era la adecuada para el comportamiento esperado del sistema.

Posteriormente, observamos que la luz LED no lograba apagarse correctamente. Para intentar resolver este problema realizamos dos códigos nuevos, modificando distintas partes de la programación y realizando varias pruebas. Finalmente, decidimos volver a utilizar el mismo código inicial, ya que descubrimos que el problema no estaba en nuestra programación, sino en la configuración de la Raspberry Pi Pico 2W.

La Raspberry había sido modificada previamente y únicamente mantenía activa la señal correspondiente al encendido del LED, representada por el valor “1”, mientras que la señal de apagado, correspondiente al valor “0”, ya no se encontraba funcionando correctamente. Luego de identificar este problema pudimos comprender el origen del error y continuar avanzando con el proyecto. 

## Imágenes del proyecto

## Animaciones del proyecto

## Bibliografía
