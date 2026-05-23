# investigaciones individuales

Martina Alegría Coloma/ AlegriaColoma

En lo personal durante el proceso me senti super frustrada al no comprender del todo lo que estaba haciendo, creo que aun no lo comprendo pero comprendo un poco lo que hicimos durante la solemne.

## Sensor
### ¿Qué es un sensor?

Un sensor es todo aquello que tiene una propiedad sensible a una magnitud del medio, y al variar esta magnitud también varía con cierta intensidad la propiedad, es decir, manifiesta la presencia de dicha magnitud, y también su medida.

Existen 12 tipos de sensores, que miden y detectan distintos tipos de variables

* Sensor de temperatura
* Sensores de luz
* Sensores de distancia
* Sensores de proximidad
* Sensores de posición
* Sensores de color
* Sensores de la humedad
* Sensores de velocidad
* Sensores de sonido
* Sensores de contacto
* Sensores ópticos
* Sensores magneticos

### Potenciómetro 

Un potenciómetro es un componente electrónico que funciona como resistor variable de tres terminales: dos fijos y uno móvil denominado "cursor" o wiper. Al girar o deslizar su perilla, el cursor se desplaza sobre una pista resistiva, modificando el valor de la resistencia entre los terminales y permitiendo así controlar y regular tanto la caída de voltaje como la intensidad de la corriente dentro de un circuito eléctrico, dependiendo del tipo de aplicación.

#### Aplicaciones del potenciómetro 

* Control de volumen en equipos de sonido: Al girar el potenciómetro, se ajusta la amplitud de la señal de audio, permitiendo incrementar o disminuir el volumen.
  
* Control de intensidad luminosa: En sistemas de iluminación, se usa para ajustar la luminosidad de una bombilla, modificando la corriente que llega al dispositivo.
  
* Ajuste de sensores: Muchos sensores, como los de temperatura o humedad, utilizan potenciómetros para calibrar las señales de entrada.

* Instrumentos musicales eléctricos: Los potenciómetros son muy comunes en guitarras eléctricas y amplificadores, donde permiten ajustar el tono y el volumen.

#### Conclusión del potenciómetro (revisar)

El potenciómetro es uno de los componentes más versátiles y utilizados en la electrónica. Gracias a su capacidad para variar la resistencia de un circuito, tiene aplicaciones que van desde el control de volumen en dispositivos de audio hasta la calibración de sensores en sistemas industriales. Existen diferentes tipos y tamaños de potenciómetros, y cada uno es adecuado para una variedad de aplicaciones. Conocer las medidas, tipos y cómo conectarlos correctamente es esencial para garantizar el rendimiento óptimo de los circuitos en los que se utilizan.

#### Posibles fallas

- Fallo de rotación: esto suele deberse al desgaste de la resistencia, lo que da como resultado un mal contacto entre el contacto móvil y la resistencia
- Fallo de pines y resistencias: cuando el potenciómetro se rompe dentro del pin, se producirá un fenómeno en el que el potenciómetro no funcionará, es decir, no habrá cambios en la corriente o el voltaje del circuito cuando se gire el eje giratorio.
- Problemas de funcionamiento: si la tuerca de fijación está demasiado apretada, puede provocar que el eje del potenciómetro no gire. Además, si la perilla tiene demasiada fuerza, también puede dañar el potenciómetro.
- Mal contacto: esto puede ser causado por polvo o suciedad y se puede solucionar con controles de limpieza.

#### Moog Music 

El Minimoog Model D fue el primer sintetizador portátil del mundo y convirtió a Moog en un nombre conocido en la industria musical, gracias a artistas como Herbie Hancock, Kraftwerk, Gary Numan y Rick Wakeman.

El Minimoog Model D utiliza potenciómetros giratorios de distintos valores según la función: 25K lineal para mezcla de modulación, volumen de oscilador y ruido; 50K audio inverso para el énfasis del filtro VCF; 50K audio para la rueda de modulación; y 5K lineal para afinación, frecuencia de osciladores, corte de filtro, sustain y volumen principal.

El Minimoog Model D es un sintetizador analógico monofónico equipado con 3 osciladores VCO analógicos y un filtro ladder paso bajo de 24 dB/octava. Su teclado Fatar incluye velocity y aftertouch, y cuenta con conectividad MIDI in/out/thru además de CV/Gate.

<img width="876" height="584" alt="image" src="https://github.com/user-attachments/assets/ee66402f-75b0-4193-87d3-0bb943897e45" />

## Actuador

### Micro servo motor SG90

El servo SG90 Tower Pro es un micro servo de alta calidad y tamaño compacto, ideal para proyectos de robótica, aeromodelismo y automatización. Su bajo consumo lo hace perfecto para aprendizaje y prototipado, permitiendo su uso directo con placas Arduino o similares alimentadas por USB.

- Definición de servomotor : Un servomotor se define como un motor eléctrico que proporciona un control preciso de la posición angular o lineal, la velocidad y el par mediante un sistema de bucle de retroalimentación.

- Sistemas de control : El servomotor utiliza sistemas de control avanzados como PID y lógica difusa para ajustar el movimiento según las señales de entrada y retroalimentación para un rendimiento óptimo.

- Tipos de motores : Existen diferentes tipos, como los servomotores de CA y CC, con subtipos como síncronos, asíncronos, con escobillas y sin escobillas, cada uno adaptado a aplicaciones específicas.

- Mecanismo de retroalimentación : El uso eficaz de sensores como potenciómetros y codificadores ayuda a monitorizar y ajustar con precisión la posición, la velocidad o el par del motor.

- Información sobre aplicaciones : Los servomotores son fundamentales en campos de alta precisión como la robótica, la maquinaria CNC y la fabricación automatizada, por su capacidad para manejar movimientos y tareas complejas.

#### Posibles fallas

La falla más frecuente en el SG90 es el jitter o vibración: el servo tiembla al intentar mantener una posición, causado generalmente por una fuente de alimentación inestable o una señal PWM con ruido. La solución es usar una fuente de 5V estable y verificar que las conexiones estén firmes.

Otra falla habitual es el estancamiento (stalling): el servo no se mueve o queda bloqueado, frecuentemente por sobrecarga mecánica o algún obstáculo físico. En estos casos se recomienda reducir la carga o considerar un servo de mayor torque como el MG90S.

El sobrecalentamiento también es un problema conocido: ocurre cuando el servo se mantiene bloqueado en una posición bajo carga por periodos prolongados. Para evitarlo, se recomiendan ciclos de "reposo" periódicos en el código.

Además, el desgaste de engranajes reduce la eficiencia del servo con el tiempo. Dado que el SG90 tiene engranajes de nylon, se puede aplicar grasa de silicona para prolongar su vida útil.

#### Doug Domke

La inspiración original de Doug Domke fue una versión mucho más grande con 450 servos que vio en un museo de arte moderno. A partir de esa experiencia, decidió construir su propia versión accesible y compartirla de forma abierta con la comunidad maker. El proyecto fue publicado el 4 de septiembre de 2019 en Hackster.io bajo licencia GPL3+, lo que significa que cualquier persona puede replicarlo, modificarlo y mejorarlo libremente.

El dispositivo cuenta con 36 servomotores dispuestos en una tabla de clavijas que producen distintos patrones visuales, y puede usarse en un modo interactivo donde sigue la mano de una persona gracias a sensores ultrasónicos. Todo está controlado por un Arduino Uno junto con tres módulos de control PWM de 16 canales, y palitos de helado muestran el movimiento de los servos a los espectadores.

La obra fue construida sobre una tabla de clavijas (pegboard) de 24 por 48 pulgadas, recortada a 32 pulgadas de ancho. Los servos están montados a 4 pulgadas de distancia entre sí y fijados a la parte trasera de la tabla con pegamento caliente. Los palitos de helado, cortados a 3 y un cuarto de pulgada, están montados en los ejes de los servos, también con pegamento caliente. Cada servo tiene su propio palito como elemento visual, convirtiendo el movimiento angular del SG90 en un efecto visual colectivo.

Domke describe que cuando se pone la mano sobre el sensor central, el Arduino entra en modo interactivo y todos los servos intentan seguir la mano mientras se mueve por encima de los sensores de distancia. Cuando se retira la mano por unos segundos, el programa regresa a su modo de exhibición. Para esto se usan cinco sensores ultrasónicos HC-SR04 montados en el borde superior trasero de la pantalla, aunque esta función es completamente opcional.

La lista de materiales es completamente accesible y económica: un Arduino Uno, tres controladores PWM de 16 canales de Adafruit, 36 servomotores SG90, una fuente de alimentación de 5V a 30W, extensiones de cable para servos, la tabla de clavijas, 36 palitos de helado cortados, y opcionalmente cinco sensores HC-SR04. Domke señaló que los SG90 son el único gasto importante del proyecto: se puede comprar un paquete de 8 por alrededor de 20 dólares, pero advierte que algunos no alcanzan los 180° completos y recomienda comprar en cantidad para seleccionar los que sí funcionen bien.

Pocos proyectos de Arduino usan servomotores de una manera tan interesante como esta pieza de arte electrónico, que incluso con solo 36 servos produce efectos visuales notables. El blog oficial de Arduino lo destacó como referencia en su categoría, validando su valor como obra que cruza la frontera entre la electrónica maker y el arte cinético interactivo. Además, Domke tiene otros proyectos similares, incluyendo un reloj de palabras controlado por 114 servomotores, lo que muestra una línea de trabajo artístico consistente centrada en el SG90 como herramienta expresiva.

<img width="900" height="675" alt="image" src="https://github.com/user-attachments/assets/22691394-8db0-4514-af59-d9b8cab687e6" />

## Bibliografía

Arduino Team. 2019. *Three dozen servos create animated artwork* https://blog.arduino.cc/2019/09/06/three-dozen-servos-create-animated-artwork/

Columna de Zhihu. 2024. *¿Cúales son los fallos más comunes del potenciómetro giratorio?* https://es.alltrans-sensor.com/news/what-are-the-common-faults-of-rotating-potenti-79615642.html

Doug Domke. 2019. *Servo Motor Artwork* https://www.hackster.io/doug-domke/servo-motor-artwork-79e2d3

Fumo,D. Noviembre, 2022. *Moog’s Minimoog Model D Reissue Revives a Classic Synth With Vintage Soul and Modern Updates* https://vintageking.com/blog/moog-minimoog-model-d-reissue/

KPower. Enero, 2026 *The Mighty Micro: How the 9g SG90 Servo Motor Powers Creativity and Precision* https://www.kpower.com/blog/3235.html

Osaka electronics. 2024. *¿Qué es un potenciómetro?* https://osakaelectronicsltda.com/blog/biblioteca/que-es-un-potenciometro

Ruiz, L. Abril, 2026. *Los 12 tipos de sensores: sus características y funciones*. https://psicologiaymente.com/miscelanea/tipos-de-sensores

Wikipedia. SF. *Potenciómetro* https://es.wikipedia.org/wiki/Potenci%C3%B3metro

Zaitronics. Enero, 2026 *SG90 Servo Arduino Tutorial: Wiring, Code & Troubleshooting Guide* https://zaitronics.com.au/blogs/guides/sg90-servo-arduino-guide

Consultada en Mayo de 2026. https://claude.ai/chat/2cac5ff0-ddce-4e17-8b73-aea8bf90c3be
