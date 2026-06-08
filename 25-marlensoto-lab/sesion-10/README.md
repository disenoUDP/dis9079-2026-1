# sesion-10

lunes 18 mayo 2026

solemne 2
# Desarrollo de la solemne

## Idea del proyecto

Durante la clase trabajamos en el desarrollo de nuestra solemne. La idea principal era crear un sistema IoT utilizando un sensor de distancia HC-SR04 conectado a una Raspberry Pi Pico 2W.

El sistema también incorporaba un botón que, al presionarlo, permitía recolectar y enviar la información de distancia detectada por el sensor. Al volver a presionar el botón, el sistema dejaba de enviar información.

Además, utilizamos una placa Arduino UNO R4 WiFi conectada a un servo motor. Esta placa se encargaba de recibir los datos enviados y mover el servo dependiendo de la distancia detectada.

---

## Proceso

### Replanteamiento de la idea

Al inicio tuvimos que replantear nuestra idea, ya que no estábamos completamente seguras de si sería posible realizar correctamente la comunicación entre ambas placas.

### Investigación del cableado

Luego comenzamos a investigar el cableado de todos los componentes. Esta etapa fue bastante caótica porque no teníamos mucho conocimiento sobre el funcionamiento del sensor ultrasónico, el servo motor ni la conexión correcta del botón y su ubicación en la protoboard.

<img width="899" height="1599" alt="Cableado_sensor distancia" src="https://github.com/user-attachments/assets/9ca381b2-a9fa-41ad-884b-01503b4b7ea2" />

### Desarrollo del código

Después de resolver gran parte del cableado, comenzamos a desarrollar el código. Esta parte también fue compleja, ya que el proyecto necesitaba manejar más líneas de código y librerías que los ejercicios realizados anteriormente.

Cuando el código estaba casi listo comenzaron a aparecer varios errores de compilación y conexión.

### Errores y librerías

Finalmente descubrimos que necesitábamos instalar librerías específicas para utilizar correctamente el sensor y la comunicación entre las placas.

Durante gran parte de la clase estuvimos revisando errores, investigando soluciones y realizando pruebas pero no se logro nada tuvimos que intergarnos a otro grupo por tema de tiempo sobre la entrega.
