# sesion-05

## Trabajando en la solemne

Llegamos a la clase con algunas dudas y confusiones ya que intentamos el código de ejemplo entregado por Aarón pensando que teníamos todo en orden pero habían dos cosas, teníamos que actualizar el Arduino R4 WIFI (agradecemos a Aaron por ayudarnos) y además no nos habíamos dado cuenta que estabamos usando las credenciales incorrectas, estábamos usando la contraseña personal del sitio en lugar de la AIO Key (la cual te proporciona Adafruit IO para la conexión)

Luego de solucionar esos errores, nos funcionó el ejercicio y pudimos empezar a buscar otros ejercicios, uno de nuestros compañeros por discord envió el link de un ejemplo (<https://learn.adafruit.com/adafruit-io-basics-color>)

En este ejemplo se controla desde un dashboard de Adafruit el color de un LED rgb conectado al Arduino. Este ejemplo nos interesó bastante y fuimos a conseguir los componentes que nos faltaban al LID (el led rgb, 4 cables dupont y 3 resistencias de 560 ohm) (ya teníamos la protoboard y el Arduino R4 WIFI)

Conseguimos todo menos el led rbg ya que solo habían led monocolor de 2 patitas. Mateo nos dio la idea de usar uno de esos LED y en vez de cambiar los colores tratar de prender y apagarlo igualmente desde un dashboard de Adafruit.

Para esto creamos un feed y un dashboard con un `toggle` para que cuando se generarán las conexiones poder controlar la luz del LED. Sin mucho conocimiento sobre programación le pedimos a ChatGPT que nos modificará el ejemplo que nos dio Aarón con lo que necesitábamos pero ningún código de los que nos dio funcionó.

lunes 06 abril 2026

solemne 1
