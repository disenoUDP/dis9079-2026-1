# sesion-11

lunes 25 mayo 2026

solemne 2

En esta sesión nos enfocamos en arreglar los errores que habían quedado de la solemne 2, principalmente relacionados con el código y el funcionamiento de los LEDs.

Al principio nos dimos cuenta de que el problema estaba en el código de la Raspberry Pi, ya que no se estaba enviando correctamente el mensaje. Después de corregir eso y hacer que enviara “ON”, logramos encender el LED interno del Arduino UNO R4. Aun así, todavía no podíamos apagarlo una vez encendido, y tampoco funcionaba el LED externo.

Luego mejoramos el código agregando una condición según el estado del botón. Con esto, mientras el botón está presionado se envía “ON” y cuando se suelta se envía “OFF”. Gracias a este cambio, el LED interno empezó a funcionar correctamente, encendiéndose y apagándose según el botón.

Después de eso nos enfocamos en el LED externo, que seguía sin funcionar. Revisando el circuito, nos dimos cuenta de que el problema era de conexiones y de la resistencia.

Finalmente, al corregir el cableado y conectar bien la resistencia, logramos que el LED externo funcionara como debía. El resultado final fue que al mantener presionado el botón el LED se enciende, y al soltarlo se apaga, cumpliendo con lo que se esperaba del sistema.
