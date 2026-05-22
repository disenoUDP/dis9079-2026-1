# investigaciones individuales

Renata De Los Ángeles Arévalo Urra / github

## Sensor

# Sensor MQ-135: Sensor de calidad del aire

El sensor MQ-135 es un dispositivo electrónico utilizado para detectar diferentes gases presentes en el ambiente y estimar la calidad del aire. Puede identificar sustancias como dióxido de carbono (CO₂), humo, amoníaco, alcohol y otros compuestos contaminantes. Actualmente este tipo de sensores tiene aplicaciones en hogares inteligentes, industrias, sistemas de monitoreo ambiental y proyectos IoT.

Al investigar este sensor llamó la atención que un componente tan pequeño sea capaz de detectar algo que normalmente las personas no pueden percibir directamente. Generalmente podemos notar humo o malos olores, pero la presencia de ciertos gases pasa desapercibida, y descubrir que eso puede convertirse en datos medibles resultó muy interesante.

El MQ-135 funciona mediante un material sensible —óxido de estaño dopado con indio (In₂O₃-SnO₂)— que modifica su resistencia eléctrica cuando entra en contacto con diferentes gases presentes en el aire. Estos cambios generan señales eléctricas que pueden ser interpretadas por una placa como Arduino o Raspberry Pi Pico para posteriormente ser procesadas (Zevallos Reyna, 2024).

El sensor puede entregar dos tipos de salida:

- **Salida analógica:** entrega valores variables proporcionales a la concentración de gas detectada.

- **Salida digital:** activa una señal cuando la concentración supera un límite definido mediante un potenciómetro integrado.

Mientras se investigaba su funcionamiento, se descubrió que el sensor realmente no "detecta" el aire de forma directa, sino que identifica cambios eléctricos producidos por los gases. Antes de investigarlo se imaginaba un funcionamiento parecido al de una cámara o detector visual, pero en realidad utiliza principios electrónicos basados en variaciones de conductividad.

### Información que puede entregar

El sensor puede proporcionar información relacionada con:

- Calidad del aire.

- Presencia de humo.

- Variaciones en ciertos gases.

- Cambios ambientales.

Por ejemplo:

- Aire limpio → valores bajos.

- Aire con humo → valores altos.

- Espacios con poca ventilación → valores intermedios o elevados.

Resulta interesante que algo tan cotidiano como el aire de una habitación pueda transformarse en números y datos analizables. Muchas veces las personas toman decisiones según lo que perciben, pero un sensor permite trabajar con información objetiva y cuantificable.

### Filtrado de información

Los sensores no siempre entregan datos completamente estables, ya que las mediciones pueden cambiar ligeramente incluso cuando las condiciones del ambiente siguen siendo prácticamente iguales. Esto ocurre debido a interferencias, cambios ambientales o pequeñas variaciones eléctricas conocidas como "ruido". Por esta razón, la información obtenida suele pasar por un proceso de filtrado para obtener resultados más confiables.

Por ejemplo, si el sensor MQ-135 se encuentra en una habitación donde el aire permanece estable, podría entregar mediciones como:

- 250

- 270

- 255

- 300

- 260

Aunque el aire no haya cambiado de forma importante, los valores presentan diferencias. Para evitar interpretar estas variaciones como cambios reales en la calidad del aire, se utilizan métodos de filtrado.

Uno de los métodos más utilizados es el **promedio simple**, que consiste en sumar varias mediciones y dividirlas por la cantidad de datos obtenidos.

**Ejemplo:**

(250 + 270 + 255 + 300 + 260) ÷ 5 = **267**

En lugar de trabajar con todos los valores por separado, el sistema utiliza un valor más estable y representativo.

Descubrir que los sensores no entregan información completamente perfecta desde el primer momento resultó revelador. Antes se pensaba que un sensor simplemente medía y mostraba resultados exactos, pero la información necesita procesarse antes de ser utilizada.

### Problemas comunes

Uno de los principales problemas del MQ-135 es que necesita un proceso de **calibración** antes de entregar resultados confiables. Además, factores externos como la temperatura y la humedad pueden alterar las mediciones obtenidas (Torres Guin et al., 2024).

Otros problemas frecuentes son:

- Tiempo de estabilización o precalentamiento inicial (entre 20 y 48 horas recomendadas para máxima precisión).

- Influencia de condiciones ambientales externas.

- Consumo energético relativamente elevado (~150 mA).

- Dificultad para identificar gases específicos de forma individual, ya que responde a múltiples sustancias simultáneamente.

Algo que sorprende bastante al estudiarlo es que el sensor necesita un período de calentamiento para funcionar correctamente. Se podría pensar que basta con conectarlo para comenzar a obtener resultados precisos inmediatamente, pero no es así.

### Visualización de datos

La información obtenida por el sensor puede representarse mediante:

- Gráficos en **Adafruit IO** o **ThingSpeak**.

- Dashboards en tiempo real.

- Aplicaciones móviles.

- Pantallas LCD conectadas a la placa.

- Sitios web con actualización automática.

Por ejemplo, con un sistema de colores:

- **Verde:** aire limpio.

- **Amarillo:** calidad intermedia.

- **Rojo:** aire contaminado.

Transformar números en gráficos facilita la interpretación de la información y permite identificar cambios de manera rápida, incluso para personas sin conocimientos técnicos.

### Aplicaciones reales

El MQ-135 puede utilizarse en distintas áreas:

- Hogares inteligentes.

- Escuelas y oficinas.

- Industrias con manejo de sustancias químicas.

- Monitoreo ambiental urbano.

- Sistemas de ciudades inteligentes.

- Vehículos y transporte.

Durante la investigación resultó llamativo que tecnologías similares sean utilizadas a gran escala para monitorear contaminación ambiental y apoyar decisiones relacionadas con la salud y el medioambiente.

## Actuador

## Bibliografía

Sensor

https://arduino.cl/producto/sensor-calidad-de-aire-mq-135/?srsltid=AfmBOopRZOVVRWbb5xdSsABVzjzi7T4vcWkNDE-aWxD_iEcP8E1m9sLp

https://naylampmechatronics.com/blog/42_tutorial-sensores-de-gas-mq2-mq3-mq7-y-mq135.html

https://hubot.cl/producto/modulo-sensor-de-humo-gases-peligrosos-mq-135-sku-538/?srsltid=AfmBOoox7uX-iEAoZn2PM3kuv4gWqYw8YWLxJcvKisVQukzlfv9cE15K

https://afel.cl/products/sensor-calidad-aire-mq135?srsltid=AfmBOorQa2KZVSSmgqhH3xC-9p5F6P5ZNW8AbV_R9iX_Vo5O-7fYYaur
