# sesion-12

lunes 01 junio 2026

## EXAMEN:  Estudios inalámbricos sobre  poéticos

1 parrafo de al menos 4 lineas, que hace su proyecto, no como que (buscar referentes, palabras clave)
Grupo de 3 a 4 personas


INDIVIDUAL

- Investigación sobre apis

- Bitacoras y procesos 


GRUPAL

Demo entre rep180 y ss2221 en video funcionamiento en vivio entre extremos de la sala docs y código ordenadito


REQUISITOS

- Incluir arrays + for / iteración
  
- Usar al menos un microcontrolador
  
- Usar al menos un sensor y/o un actuador, en múltiplos, para usar arrays
  
- Comentar el código
  
- Declarar toda ia usada con lujo de detalles, incluyendo prompts y todo lo que hayan hecho


## NOMBRE PROYECTO

- Espacios entrelazados

- Dualidad de esapcios

- lectura (por datos)

- connection BLID (Combinación directa de Biblioteca + LID)

- Puente Digital


## PRIMER PÁRRAFO DE CONTEXTO

Grupo 6

Dos edificios que actúan al unísono, sin saberlo. Un sensor en el LID, otro  en la biblioteca, cada uno contando y midiendo presencia, traduciendo lo humano a pulsos digitales. Entre ellos, no está vacío: viaja un protocolo, una API recibe el conteo, lo procesa, lo devuelve transformado; y un actuador responde: una pantalla que se ilumina, un LED que cambia de color, una señal que dice aquí hay vida. El sistema nervioso oculto de los lugares donde pensamos, construido sobre microcontroladores, WiFi y la pregunta técnicamente precisa pero profundamente humana: ¿cuántos habitan tus pasillos ahora mismo?


## PREGUNTAS / RESPUESTAS

- ¿cómo se comunica visualmente el conteo al usuario final? ¿qué significan los distintos colores del led?

R: Se comunica mediante luces led. Rojo Biblioteca, Verde LID.

- ¿qué sensor van a ocupar para detectar a un ser vivo?

R: Sensor PIR HC-SR501 Detector de Movimiento o Sensor ultrasónico


## OPCIONES SENSORES (todos usan luz infrarroja)

La diferencia de los siguientws sensores es la forma en que interactúan con el cuerpo humano y el espacio físico es completamente distinta.

- Sensor Infrarrojo Evasor de Obstáculos

<img width="540" height="500" alt="infrarrojoEvasor" src="https://github.com/user-attachments/assets/80ddaf9e-7b0c-4e7c-a720-cd896846ca23" />

Imagen sacada de: https://afel.cl/products/sensor-infrarrojo-evasor-de-obstaculos?_pos=1&_sid=5dc4ed558&_ss=r 

Cómo funciona: Es un sensor de reflexión activa. Tiene dos "ojos" pequeños: un LED emisor que lanza un haz de luz infrarroja invisible y un fotodiodo receptor que espera a que esa luz rebote en un objeto (el cuerpo de una persona).

Área de visión: Un haz lineal muy estrecho y directo. 

Su rango es corto y ajustable mediante un pequeño tornillo (típicamente de 2 a 30 cm.


Para el proyecto: Es ideal si se busca que el sensor este oculto. Al ser tan pequeño (como un pulgar), se puede poner en el acceso del LID tipo totem y dejar asomados solo los dos pequeños LEDs. Este sensor funciona muy bien en pasillos estrechos o torniquetes dinámicos. Su punto débil es que si el pasillo es muy ancho más de 40 cm, la luz no alcanzará a rebotar en la persona y no registrará el tránsito.

Problema que se puede tener: La puerta es bidireccional, registra el dato de una persona más de una vez, si entro y salgo me registre dos veces, cómo si fueran 2 personas. El sensor es "ciego" a la dirección.

Alcance del sensor corto -> generalmente entre 2 y 30 cm

  
- Sensor de Proximidad Infrarrojo E18-D80NK

<img width="633" height="446" alt="proximidadInfrarrojo" src="https://github.com/user-attachments/assets/69f93a31-2813-4352-80b3-635882e440c9" />

Imagen sacada de: https://afel.cl/products/sensor-de-proximida-infrarrojo-e18-d80nk?_pos=1&_sid=f70d01128&_ss=r

Cómo funciona: Utiliza el mismo principio de reflexión activa que el evasor de obstáculos (emite y recibe su propia luz infrarroja), pero con componentes de grado industrial. Viene encapsulado en un tubo plástico roscado y blindado contra interferencias de luz ambiental.

Área de visión: Un haz directo, milimétrico y de largo alcance. Su potenciómetro trasero permite calibrar el disparo con precisión quirúrgica desde los 3 cm hasta 80 cm.

Para el proyecto: Es la mejor opción técnica para un conteo real. Al tener un alcance de hasta 80 cm, cubre perfectamente el ancho estándar del paso de una persona en una puerta. 

Su precisión es digital: en cuanto el cuerpo corta el haz, el sensor manda un pulso instantáneo al Arduino R4 WiFi. Al ser robusto, puedes fijarlo firmemente a los muros o estructuras de los accesos sin temor a que se descalibre si alguien lo pasa a llevar.

  
- Sensor de Movimiento HC-SR501:

<img width="498" height="439" alt="sensorPir" src="https://github.com/user-attachments/assets/24d67823-2f06-4da0-b48d-7d81aba65b82" />

Imagen sacada de: https://afel.cl/products/sensor-de-movimiento-hc-sr501?_pos=1&_sid=50d2fe854&_ss=r 


El sensor PIR cuenta "siluetas". Técnicamente, un sensor PIR detecta cambio de calor en movimiento (es un interruptor ciego: hay o no hay movimiento), no formas.

Cómo funciona: No emite luz; es un receptor pasivo. Detecta la radiación infrarroja (el calor) que emiten los cuerpos humanos en movimiento.

Funciona como un interruptor: si detecta un cambio térmico en su área de cobertura, se activa.

Área de visión: Muy amplia un cono de unos 110° y hasta 7 metros de distancia).

Para el proyecto: No sirve para contar. Al tener un ángulo tan abierto, si tres personas cruzan juntas el pasillo, el sensor se activará una sola vez de forma continua. Además, si alguien entra a la biblioteca y se queda completamente quieto leyendo, el sensor dejará de "verlo" porque ya no hay movimiento térmico, asumiendo falsamente que el espacio está vacío.

## PARRAFO ARREGLADO

Este proyecto consiste en un sistema que conecta el LID y la biblioteca para medir cuántas personas entran y salen de cada lugar en tiempo real. En la puerta de cada edificio se instalan dos sensores infrarrojos industriales conectados a una placa Arduino con WiFi. Al colocar dos sensores en fila, el sistema detecta de forma automática la dirección de la persona: si pasa primero por el de afuera y luego por el de adentro, cuenta como una entrada; si lo hace al revés, cuenta como una salida. Esta información se envía de manera inalámbrica a través de internet a una base de datos (API) que lleva el conteo exacto. Finalmente, el sistema responde encendiendo una pantalla o luces LED en el otro edificio; de esta forma, las personas que están en la biblioteca pueden ver mediante una señal visual qué tan lleno está el LID, y viceversa, automatizando el registro de ocupación de los espacios del campus.


## Referentes de apis -> visto en clases

https://eroft.decontextualize.com/

https://metmuseum.github.io/

https://github.com/public-apis/public-apis

https://developer.nytimes.com/apis

https://api.nasa.gov/

https://www.reddit.com/r/webdev/comments/194rfia/api_hidden_gems/

https://openweathermap.org/api

https://en.wikipedia.org/wiki/API

https://everest-pipkin.com/projects/corsicana

https://yeseul.com/Slow-Dimming-Study-Rice-Dimmer

https://yeseul.com/Invisible-Sculpture-On-Wheels-GimHae
