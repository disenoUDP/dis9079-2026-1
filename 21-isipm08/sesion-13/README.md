# sesion-13

lunes 08 junio 2026

Hoy trabajaremos en diferentes puntos de nuestro examen
- Además nuestra idea fija de examen será que desde un Arduino conectada con un sensor de fecuencia cardíaca, mande la información a otro Arduino conectado a una pantalla LED y lleguen los datos de la persona a la cual se le está tomando el pulso, a su vez la pantalla LED tendrá un tipo carcasa realizada en impresión 3D con un LED conectado que seguirá el pulso de la persona.  

## Texto anterior
- Queremos realizar una exploración sobre la capacidad de la computación inalámbrica para poder transportar señales humanas, especificamente las pulsaciones. El proyecto captura el ritmo cardíaco de una persona y lo transforma en una presencia remota, permitiendo que las pulsaciones sean observadas a través de una pantalla LCD. A través de esta conexión invisible, los latidos dejan de ser una experiencia íntima para convertirse en un lenguaje compartido entre dispositivos, espacios y personas. La propuesta reflexiona sobre cómo la información biológica puede viajar, ser representada y generar nuevas formas de percepción y vínculo mediante redes inalámbricas.

## Texto corregido
- Hay señales que permanecen ocultas bajo la piel, silenciosas y constantes, acompañándonos sin que las veamos. Nuestro proyecto nace de la inquietud de tomar una de ellas —el latido del corazón— y permitirle viajar más allá del cuerpo que la origina.
Cada pulsación es capturada y enviada a través de una red invisible, recorriendo la distancia como un mensaje vivo. Lo que antes habitaba únicamente en la intimidad del cuerpo se transforma en luz, movimiento y presencia. El corazón ya no solo late para sí mismo: se manifiesta en otro lugar, en otro objeto, en otra experiencia.
Al llegar a su destino, el pulso reaparece en una estructura con forma de corazón, donde una luz palpita siguiendo exactamente el ritmo de la persona que porta el sensor. Cada destello es una huella de vida transmitida en tiempo real, una traducción tecnológica de algo profundamente humano.
La propuesta invita a reflexionar sobre la relación entre cuerpo y tecnología, explorando cómo una señal biológica puede atravesar el espacio y generar una conexión sensible entre personas, dispositivos y entornos. En este encuentro, la tecnología deja de ser solo una herramienta de comunicación para convertirse en un puente capaz de transportar fragmentos de nuestra propia existencia.

## Texto explicativo
- Este proyecto tiene como objetivo explorar el uso de la computación inalámbrica para capturar, transmitir y visualizar señales biológicas humanas en tiempo real. Para ello, se utiliza un sensor de frecuencia cardíaca conectado a un primer Arduino, encargado de registrar las pulsaciones de una persona y enviar esos datos de forma inalámbrica.
La información es recibida por un segundo Arduino, que la procesa y la muestra tanto en la plataforma Adafruit IO como en una pantalla LED. De esta manera, el ritmo cardíaco puede ser monitoreado y observado a distancia.
Como complemento a la visualización digital, la pantalla LED se encuentra integrada en una carcasa impresa en 3D con forma de corazón. Además, un LED incorporado se ilumina siguiendo el ritmo de las pulsaciones registradas, generando una representación física y visual del latido en tiempo real.
La propuesta busca demostrar cómo una señal biológica puede ser capturada, transportada y representada mediante tecnologías inalámbricas, creando nuevas formas de visualizar datos humanos y de conectar personas y dispositivos a través de información en vivo.

## Pseudocódigo

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
    
## Listado de materiales 
- 1 Pantalla LCD azul $2.400
- 1 Sensor de Frecuencia Cardíaca ECG AD8232 Electrocardiograma $9.990
- 1 Protoboard 400 puntos $2.100
- 2 Arduino R4 WIFI $38.990
- Cables dupont (40 u) $2.590
- 2 Cables USB C 
