# sesion-06

lunes 13 abril 2026

## Sensar con capacitancia

Resistencia eléctrica

Tienen capacitancia

y el que lo contiene es el Condensador eléctrico (CAPACITOR)

La fórmula de capacitancia "C = E0 Er A/d" (manera informal de escribirlo)

Arduino UNO R4 tiene un sensor capacitivo de tacto

Necesitamos:

- Arduino UNO
- Algo que afecte el campo de tacto
- Arduino Capacitive_Touch

Qué patita nos ayuda a hacer qué, tener en cuenta si está bien conectado porque pueden haber fallos humanos y no es porque no funcione el circuito

En el arduino

D0 Patita del arduino: Es la cero de la sección digital
(Las análogas si dicen Ej: A1, A2, A3, A4, A5A)

La de más abajo a la izquierda

cuando usamos la biblioteca dicen que se use el código como está

Arriba en herramientas de "Arduino IDE" -> Sketch e incluir biblioteca -> Arduino_Capacitive_Touch

esto auto completa por mi

Monitor serial (9600) es la velocidad estándar en el serial

### Instrumento 

Stylophone 51: El Stylophone es un sintetizador analógico en miniatura que se toca con un lápiz óptico.

Theremin: Es el primer instrumento musical electrónico, inventado en 1920 por Leon Theremin, que se caracteriza por tocarse sin contacto físico. Utiliza dos antenas para controlar el tono (mano derecha) y el volumen (mano izquierda) mediante el movimiento de las manos en el aire dentro de un campo electromagnético.

### En el arduino

No sé cuál es el valor mínimo o máximo que existe en un umbral

y trato de incorporar un valor que siempre se acuerde cuáles son los mínimos y máximos, partiendo del peor caso posible, luego en el loop calibro, incluyendo el valor de lectura y actualizo el mínimo y máximo

si ese valor es menor que el mínimo de lectura es un mejor mínimo , mejor cambiar el mínimo a que sea lo que es ahora

También si es que el valor de lectura es mayor de lo que yo creo que es el máximo lo actualizo  lo que yo creo que es el máximo y cada vez que encuentre un valor mayor lo va a actualizar

también puedo hacer que me muestre el valor mínimo y va a imprimir mínimo y máximo Ej: (Serial.Print())
