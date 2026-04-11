# grupo-11

## integrantes

* Anays Valentina Cornejo Candia
  
* Benjamín Alonso Álvarez Pavez

## descripción del proyecto

Al inicio del proyecto, como dupla no sabíamos muy bien qué hacer, estábamos bastante perdidos. En la última clase, trabajando al unísono con Aaron, pudimos entender mejor cómo usar el programa y ver qué cosas se podían lograr.

Al principio teníamos otras ideas, pero como aún no entendíamos bien cómo hacerlas, preferimos partir con algo más simple para aprender mejor cómo funcionan los programas y las placas.

Tras investigar por los tutoriales de la página Adafruit IO, nos llamó la atención uno que mostraba cómo prender y apagar una luz y decidimos hacer esa idea.

Cuando ya teníamos claro qué queríamos hacer, copiamos el código de config.h de GitHub y le pedimos a Chat GPT que lo modificara para poder prender y apagar un led, después también le pedimos ayuda para crear el código para enviar las instrucciones.

Para eso, conectamos un led a una protoboard e hicimos un circuito usando un Arduino UNO R4 WiFi. Conectamos el GND de la placa al negativo de la protoboard y el pin de 3.3V al positivo, luego conectamos la pata positiva del led al positivo de la protoboard y la pata negativa al negativo de la protoboard.

El Arduino estaba conectado al computador y las instrucciones de ON y OFF se enviaban desde el iPad a través del dashboard que creamos en Adafruit.

El led encendía y el código se recibía, pero al principio no logramos controlarlo porque no respondía a la instrucción de ON y OFF.

Por eso le pedimos ayuda a Chat GPT para modificar el código, para que el led respondiera bien a las instrucciones de ON y OFF desde el iPad.  En ese cambio reemplazamos la línea ledPin = 2 por int ledPin = LED_BUILTIN;, pasamos de usar un led externo a usar el led integrado del Arduino.

Y finalmente resultó, el código funcionó y logramos prender y apagar el led desde el iPad, incluso a distancia. (ദ്ദി˙ᗜ˙)

También en el mismo dashboard de ON y OFF encontramos otros blocks de adafruit que permite mandar mensajes que luego aparecen en el arduino ide 

## materiales usados en solemne-01

| Componentes Resultado Final | Precio | Cantidad | Link |
| :--------------------------- | ------ | -------- | :---- |
| Arduino UNO R4 Wifi         | $38.990 | x1      | <https://mcielectronics.cl/shop/product/43402/> |
| Cable C a C                 | $14.990 | x1      | <https://www.falabella.com/falabella-cl/product/149750952/> |

| Componentes Proceso | Precio | Cantidad | Link | 
| :------------------ | ------ | -------- | :---- |
| Protoboard          | $1.500 | x1       | <https://afel.cl/products/mini-protoboard-400-puntos> |
| Cable Dupont (pack 40 uni.) | $2.900 | x4       | <https://mcielectronics.cl/shop/product/cable-dupont> |
| Led                 | $70    | x1       | <https://afel.cl/products/diodo-led-5mm-ultrabrillante-blanco> |

## código usado con Adafruit IO

### código para enviar

```cpp
// rellenar
```

### código para recibir

```cpp
// rellenar
```

## investigaciones individuales

[persona-01.md](./persona-01.md) Anays Cornejo

[persona-02.md](./persona-02.md) Benjamín Álvarez

## bibliografía

<https://learn.adafruit.com/series/adafruit-io-basics>

<https://learn.adafruit.com/adafruit-io-basics-digital-output>
