# sesion-12

lunes 01 junio 2026

EXAMEN:  Estudios inalámbricos sobre  poéticos

1 parrafo de al menos 4 lineas, que hace su proyecto, no como que (buscar referentes, palabras clave)
Grupo de 3 a 4 personas


INDIVIDUAL

Investigación sobre apis 
Bitacoras y procesos 

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


## PÁRRAFO DE CONTEXTO

Grupo 6: Dos edificios que actúan al unísono, sin saberlo. Un sensor en el LID, otro  en la biblioteca, cada uno contando y midiendo presencia, traduciendo lo humano a pulsos digitales. Entre ellos, no está vacío: viaja un protocolo, una API recibe el conteo, lo procesa, lo devuelve transformado; y un actuador responde: una pantalla que se ilumina, un LED que cambia de color, una señal que dice aquí hay vida. El sistema nervioso oculto de los lugares donde pensamos, construido sobre microcontroladores, WiFi y la pregunta técnicamente precisa pero profundamente humana: ¿cuántos habitan tus pasillos ahora mismo?


## PREGUNTAS / RESPUESTAS

- ¿cómo se comunica visualmente el conteo al usuario final? ¿qué significan los distintos colores del led?

R: Se comunica mediante luces led. Rojo Biblioteca, Verde LID.

- ¿qué sensor van a ocupar para detectar a un ser vivo?

R: Sensor PIR HC-SR501 Detector de Movimiento o Sensor ultrasónico

## OPCIONES SENSORES (todos usan luz infrarroja)

La diferencia de los siguientws sensores es la forma en que interactúan con el cuerpo humano y el espacio físico es completamente distinta.

- Sensor Infrarrojo Evasor de Obstáculos

Cómo funciona: Es un sensor de reflexión activa. Tiene dos "ojos" pequeños: un LED emisor que lanza un haz de luz infrarroja invisible y un fotodiodo receptor que espera a que esa luz rebote en un objeto (el cuerpo de una persona).

Área de visión: Un haz lineal muy estrecho y directo. Su rango es corto y ajustable mediante un pequeño tornillo (típicamente de 2 a 30 cm.

Para tu proyecto: Es ideal si quieres esconder la tecnología. Al ser tan pequeño (como un pulgar), puedes perforar el marco de una puerta o un tótem de madera en el acceso del LID y dejar asomados solo los dos pequeños LEDs. Funciona muy bien en pasillos estrechos o torniquetes dinámicos. Su punto débil es que si el pasillo es muy ancho más de 40 cm, la luz no alcanzará a rebotar en la persona y no registrará el tránsito.
  
- Sensor de Proximidad Infrarrojo E18-D80NK

Cómo funciona: Utiliza el mismo principio de reflexión activa que el evasor de obstáculos (emite y recibe su propia luz infrarroja), pero con componentes de grado industrial. Viene encapsulado en un tubo plástico roscado y blindado contra interferencias de luz ambiental.

Área de visión: Un haz directo, milimétrico y de largo alcance. Su potenciómetro trasero permite calibrar el disparo con precisión quirúrgica desde los 3 cm hasta 80 cm.

Para tu proyecto: Es la mejor opción técnica para un conteo real. Al tener un alcance de hasta 80 cm, cubre perfectamente el ancho estándar del paso de una persona en una puerta. Su precisión es digital: en cuanto el cuerpo corta el haz, el sensor manda un pulso instantáneo al Arduino R4 WiFi. Al ser robusto, puedes fijarlo firmemente a los muros o estructuras de los accesos sin temor a que se descalibre si alguien lo pasa a llevar.
  
- Sensor de Movimiento HC-SR501: El sensor PIR cuenta "siluetas". Técnicamente, un sensor PIR detecta cambio de calor en movimiento (es un interruptor ciego: hay o no hay movimiento), no formas.

Cómo funciona: No emite luz; es un receptor pasivo. Detecta la radiación infrarroja (el calor) que emiten los cuerpos humanos en movimiento.

Funciona como un interruptor: si detecta un cambio térmico en su área de cobertura, se activa.

Área de visión: Muy amplia un cono de unos 110° y hasta 7 metros de distancia).

Para tu proyecto: No sirve para contar. Al tener un ángulo tan abierto, si tres personas cruzan juntas el pasillo, el sensor se activará una sola vez de forma continua. Además, si alguien entra a la biblioteca y se queda completamente quieto leyendo, el sensor dejará de "verlo" porque ya no hay movimiento térmico, asumiendo falsamente que el espacio está vacío.
