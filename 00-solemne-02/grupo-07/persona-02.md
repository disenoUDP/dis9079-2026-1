# investigaciones individuales

Anays Cornejo - [Anaysval](https://github.com/Anaysval)

## Sensor

### Sensor PIR 

### ¿Qué es un sensor PIR?

Un sensor PIR (Passive Infrared Sensor) es un dispositivo electrónico que detecta movimiento mediante cambios en la radiación infrarroja emitida por personas, animales u objetos calientes. 

Estos sensores se utilizan principalmente para identificar si una persona se ha movido dentro o fuera de su rango de detección. Son dispositivos pequeños, económicos, de bajo consumo energético, fáciles de usar y con una larga vida útil, ya que no tienen partes mecánicas que se desgasten.

Por estas características, son muy comunes en electrodomésticos, sistemas de iluminación automática y equipos de seguridad en hogares o negocios. También se conocen como sensores PIR, sensores infrarrojos pasivos, sensores piroeléctricos o sensores de movimiento infrarrojo.

### Uso del sensor PIR

El sensor PIR detecta movimiento cuando percibe cambios en la radiación infrarroja del ambiente. Esto ocurre cuando una persona u objeto caliente entra en su zona de detección.

Está compuesto principalmente por una lente Fresnel, un sensor infrarrojo y tres pines de conexión: VCC, OUT y GND.

Se utiliza principalmente en:

- Alarmas de seguridad
- Luces automáticas
- Sistemas de domótica
- Robots
- Puertas automáticas

### Filtrado de información
  
El sensor PIR puede generar errores o falsas detecciones debido a factores externos, por lo que se aplican técnicas de filtrado para mejorar la precisión.

Los principales problemas que afectan la lectura son la luz solar directa, cambios bruscos de temperatura, movimiento de mascotas e interferencias eléctricas.

Para reducir estos errores se utilizan:

- Uso de retardos de tiempo
- Verificación de varias lecturas consecutivas
- Ajuste de sensibilidad del sensor

### Visualización de datos

Los datos entregados por el sensor pueden visualizarse de distintas formas dependiendo del sistema utilizado.

Se puede mostrar información mediante:

- Monitor serial en Arduino (ej: “Movimiento detectado” o “Sin movimiento”)
- LEDs indicadores
- Pantallas LCD
- Pantallas OLED (más pequeñas, de bajo consumo y con mejor contraste)
- Plataformas IoT para monitoreo remoto

### Problemas comunes

El sensor PIR puede presentar distintos problemas que afectan su funcionamiento correcto.

Los más frecuentes son:

- Falsas detecciones provocadas por calor ambiental, ventiladores o luz solar
- Alcance limitado de detección (generalmente entre 3 y 7 metros)
- Tiempo de espera entre activaciones del sensor
- Errores por mala instalación o mala orientación
- Interferencias eléctricas o alimentación inestable

### Obra

### Made to Measure 

La instalación Made to Measure del estudio Process Studio es una obra de arte interactivo donde el espacio responde a la presencia del público mediante sensores de movimiento instalados en el techo. Según la documentación oficial del proyecto, la obra utiliza 15 sensores PIR para detectar la presencia y el desplazamiento de los visitantes dentro de la sala.

“Al acercarse a los objetos expuestos o al caminar por la sala, el visitante activaba 15 sensores de movimiento montados en el techo, activando bucles en 8 altavoces diferentes y el parpadeo o conmutación de 5 tubos de neón. Dependiendo de las acciones de los visitantes, surgieron diferentes paisajes sonoros y situaciones de iluminación.” (Process Studio, n.d.) 

El sensor PIR es un dispositivo que detecta movimiento a partir de cambios en la radiación infrarroja emitida por el cuerpo humano. Su función principal es identificar la presencia de personas en un espacio sin contacto directo, lo que lo hace ideal para sistemas de iluminación automática, seguridad y entornos interactivos. En este caso, los sensores permiten que la instalación reaccione al público en tiempo real, activando luz y sonido según su movimiento.

No encontré más información sobre la instalación Made to Measure del estudio Process Studio además de lo que aparece en su página oficial. La información es bastante limitada y solo describe la obra de forma general, Tampoco encontré videos oficiales ni documentación técnica más detallada sobre cómo funciona el proyecto. La quise utilizar igualmente porque se ve interesante y un poco misteriosa, donde no hay mucha más información y queda un poco a la imaginación. 

### Bibliografía

- Adafruit Learning System. (n.d.). PIR sensor guide. <https://learn.adafruit.com/pir-passive-infrared-proximity-motion-sensor/overview>
- Process Studio. (n.d.). Made to measure. <https://process.studio/works/made-to-measure/>
- Random Nerd Tutorials. (n.d.). Arduino with PIR motion sensor. <https://randomnerdtutorials.com/arduino-with-pir-motion-sensor/>
- SparkFun Electronics. (n.d.). PIR motion sensor hookup guide. <https://learn.sparkfun.com/tutorials/pir-motion-sensor-hookup-guide/all>

## Actuador

## Bibliografía
