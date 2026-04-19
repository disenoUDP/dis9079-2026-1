# sesion-05

lunes 06 abril 2026

solemne 1 se comienza en clases

## primera parte

aprendizajes

- cada grupo hará los feed que quiera

- estamos haciendo lo del config.h, para que se incluya dentro del .ino

- para la solemne al menos la idea es explicar los errores, explicar los procesos, cómo lo hicimos? podríamos quedarnos con lo de transmitir info

- anotar todos los errores y aciertos, cada paso específico que hicimos, prendimos el botón no se cuántas veces? reiniciamos, desconectamos, cerramos arduino, desconectamos la placa

**avance lid 8 de abril**

- ver si se puede enviar un mensaje de monitor serial desde un arduino a otro en distinto computador, después, el que recibió ese mensaje lo envía a adafruit IO

- opción 2, prender un led desde un arduino al led de otro arduino en computadores distintos, cada vez que reciba un número el led parpadea

- opción 3 enviar números desde un arduino hacia la otra pantalla del otro arduino, que se dibujen los números cada vez que lo reciba, un contador

- para enviar y recibir en distintos arduinos, ambos deberían estar utilizando las mismas credenciales, no sé si es necesario que estén en el mismo wifi

- dashboard es como la forma en la que eliges el cómo manejar el dato, feed es a dónde llegan esos datos, algo así le entendí a Vania cuando me explicó

- descargar el archivo de recibir desde la página de adafruit, vania me ayudó, tengo dudas sobre cómo encontrar el config.h que debiera venir

- vania puso el mismo config.h que mandó aarón, al final incluye los seteos para el wifi y usuarios, más que nada es para eso

- al final el archivo config.h sí estaba en la librería de adafruit en github, tenía unos ajustes pequeños entonces se descargó ese para ponerlo en la carpeta del archivo recibir

- comunicar entre arduinos, uno envía, el otro recibe, el mensaje se traduce y se transforma en algo, cómo???
