# sesion-07

lunes 20 abril 2026

Placa de prueba (Protoboard)

La Protoboard es una placa que permite armar circuitos electrónicos sin necesidad de soldar componentes. Se utiliza principalmente para pruebas y prototipos.
Para alimentar la protoboard se usa el módulo Arduino Power Breadboard, que entrega voltaje a las líneas laterales.

El cable rojo se conecta al riel de positivo (+)
El cable verde (o negro, comúnmente) se conecta al riel de negativo (−)
Esto permite distribuir energía a todo el circuito de manera ordenada.
Servo motor

El Servo motor es un dispositivo que permite controlar la posición angular con precisión.
Generalmente tiene 3 cables:

Rojo → alimentación (+)
Negro o café → tierra (−)
Amarillo o naranja → señal (control desde Arduino)
Se utiliza mucho en proyectos donde se requiere movimiento controlado, como brazos robóticos o mecanismos interactivos.

<img width="1295" height="645" alt="tinkercad" src="https://github.com/user-attachments/assets/59b48e4b-886c-44b5-a101-dd22a009f9bf" />


Uso de Tinkercad

En la plataforma Tinkercad se pueden crear circuitos de forma virtual mediante simulaciones interactivas.
Permite armar circuitos con Arduino sin necesidad de componentes físicos
Se pueden probar conexiones y códigos antes de implementarlos en la vida real
Facilita el aprendizaje mediante visualización interactiva
Potenciómetro
El Potenciómetro es un componente que permite variar la resistencia y controlar valores como voltaje o señal.

Conexión:

Una patita lateral → positivo (+)
Otra patita lateral → negativo (−)
Patita del medio → salida variable (señal)

Funcionamiento:

La patita central entrega un valor variable dependiendo de la posición del eje del potenciómetro.
En Arduino:

Se conecta a un pin analógico, por ejemplo A0
En tu caso:

Señal → A0
Lectura analógica → permite controlar valores (como el movimiento de un servo)
Relación con Arduino
El Arduino recibe la señal del potenciómetro (por ejemplo en A0) y la interpreta para controlar otros componentes, como el servo motor.

Ejemplo de flujo:

Giras el potenciómetro
Arduino lee el valor analógico
Ese valor se transforma en un ángulo
El servo motor se mueve según ese ángulo



https://github.com/user-attachments/assets/24d9d3b6-e760-4cb6-9d02-7268d68859c2

