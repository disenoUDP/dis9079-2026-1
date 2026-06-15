# Grupo-4 - Examen Interacciones Inalámbricas

## Integrantes

- Renata Arévalo Urra / [arevalourra](<https://github.com/isipm08/dis9079-2026-1/tree/main/06-arevalourra>)
- Isidora Pérez Maulén / [isipm08](<https://github.com/isipm08/dis9079-2026-1/tree/main/21-isipm08>)

## Materiales usados

| Componente | Valor Unidad | Cantidad | Link |
| --- | --- | --- | --- |
| Arduino UNO R4 WiFi | $38.990 | 2 | <https://arduino.cl/producto/arduino-uno-r4-wifi/?srsltid=AfmBOopyyargcSiTQeFlT3cTN5ide380bxZlQXRZVP4u_op0O-qJcENB> |
| Protoboard 400 puntos | $2.100 | 1 | <https://afel.cl/products/mini-protoboard-400-puntos?pr_prod_strat=e5_desc&pr_rec_id=b8ead05f1&pr_rec_pid=8382004101272&pr_ref_pid=8381979852952&pr_seq=uniform> |
| Cables Dupont (Pack 20 unidades) | $1.000 | 1 | <https://afel.cl/products/pack-20-cables-de-conexion-macho-macho> |
| Sensor de Frecuencia Cardíaca ECG AD8232 Electrocardiograma | $9.990 | 1 | <https://afel.cl/products/sensor-de-frecuencia-cardiaca-ecg-ad8232-electrocardiograma> |
| Cable USB C | $ | 2 | <> |


## Proceso de Proyecto
---

### Lunes 01 Junio 

#### 3 Semanas para el examen

Inicio de ideación de examen, estuvimos leyendo e investigando sobre varios sensores, para ver si nos gustaba alguno para realizar nuestro proyectop de examen, nos decidimos por un sensor de pulso, específicamente el Sensor de Frecuencia Cardíaca ECG AD8232 Electrocardiograma, con la idea de obtener registros en vivo de los latidos por minuto del usuario, usaremos la API -> Adafruit IO, que ya conocemos y sabemos su funcionamiento, por el lado de recepción de datos, pensamos en una pantalla LCD que muestre los latidos por minuto, usaremos 2 arduinos, uno paras enviar y otro para recibir la información.

![Modulo Sensor](./imagenes/modulo-sensor.webp)

*Modulo Sensor AD8232 - Imagen extraída de página web de AFEL*

https://afel.cl/cdn/shop/files/modulo-sensor-ad8232.jpg?v=1720904051&width=713


### Interacción entre grupos vía Discord

Descripción inicial de nuestro proyecto:

Grupo 04: Queremos lograr una exploración sobre la capacidad de las tecnologías inalámbricas para transportar señales humanas más allá del cuerpo que las origina. El proyecto captura el ritmo cardíaco de una persona y lo transforma en una presencia remota, permitiendo que sus pulsaciones sean observadas en otro lugar en tiempo real. A través de esta conexión invisible, los latidos dejan de ser una experiencia íntima para convertirse en un lenguaje compartido entre dispositivos, espacios y personas. La propuesta reflexiona sobre cómo la información biológica puede viajar, ser representada y generar nuevas formas de percepción y vínculo mediante redes inalámbricas.

- Aarón nos sugiere computación inalámbrica en vez de tecnologías inalámbricas

- Aarón nos pregunta lo siguiente: van a procesar esos datos de pulso? van a enviar el pulso directamente? o un resumen en latidos por minuto?

    -  Resp: Resumen en latidos por minuto

- Jesús Miranda nos pregunta: ¿qué pasa en este caso en el dispositivo receptor? ya que en el párrafo dice que los latidos "son observados" pero no queda claro si es una pantalla LED, sonido, ¿cómo se ve esa presencia remota?

    - Resp: Estamos considerando el uso de la pantalla led del arduino o anexar una pantalla LCD para la visualización de los datos, que en este caso son las pulsaciones por minuto

-----

### Lunes 08 Junio

#### 2 Semanas para el examen

Proyecto de examen definido


###### Nombre Formal

Sistema IoT de monitoreo cardíaco en tiempo real

###### Objetivo

Diseñar un sistema capaz de capturar la actividad cardíaca de una persona mediante un sensor ECG AD8232, transmitir los datos a través de Internet utilizando Adafruit IO y visualizarlos remotamente en una pantalla LCD conectada a un segundo microcontrolador.

###### Funcionamiento

##### AD8232 → Arduino UNO R4 WiFi → Adafruit IO

##### Adafruit IO → Arduino UNO R4 WiFi → LCD 16x2

- El sensor AD8232 detecta la actividad eléctrica del corazón.

- El Arduino transmisor procesa la señal.

- Se calcula la frecuencia cardíaca en BPM.

- El dato se envía a Adafruit IO.

- Un segundo Arduino consulta la información.

- La pantalla LCD muestra los latidos por minuto en tiempo real.


### Pseudocódigo 

    INICIO

     Conectar Arduino transmisor a WiFi

     Conectar Arduino receptor a WiFi

     Mientras sistema esté activo

      - Leer señal ECG desde AD8232

      - Calcular BPM

      - Enviar BPM a Adafruit IO

    Fin Mientras

#### Arduino Receptor

    INICIO

     Conectar a WiFi

     Conectar a Adafruit IO

     Mientras sistema esté activo

      - Obtener BPM desde Adafruit IO

      - Mostrar BPM en LCD

    Fin Mientras

### Lista de materiales
    
2 Arduino UNO R4 WiFi

1 Sensor ECG AD8232

1 Pantalla LCD 16x2 con módulo I2C

Protoboard

Cables Dupont

2 Cable USB-C para Arduino

Red WiFi

Cuenta Adafruit IO

---- 

Mateo viene a nuestros puestos a consultar como va el avancwe de nuestro proyecto, le comentamos nuestra idea definida y le gusta, nos da la idea de hacer una carcasa para la opantalla donde se muestran los datos (BPM), y nos presta una Pantalla TFT LCD Redonda de 1,28", lo cual nos quedaría super con una carcasa, en forma de corazón, ya estamos trabajando en un modelo de impresión 3D e imprimir entre esta semana y la siguiente en el LID; Gracias Mateo!!

-----

### Nueva Lista de materiales
    
2 Arduino UNO R4 WiFi

1 Sensor ECG AD8232

Pantalla TFT LCD redonda de 1.28"

Protoboard

Cables Dupont

2 Cables USB-C para Arduino

Red WiFi

Cuenta Adafruit IO

![Compra Afel](./imagenes/compra-afel.gif)






