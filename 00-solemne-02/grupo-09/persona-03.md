# investigaciones individuales

Cristobal Vergara Silva / cristobalvergarasilva

## Sensor
Avances 

Estoy investigando del Sensor de pulso cardiaco (fotopletismografía), que es un sensor de codigo abierto, muy versatil en tanto a las placas a las que se puede conectar. El sensor más básico consta de dos componentes principales: un emisor de luz y un fotodiodo (receptor de luz).

Funciona emitiendo luz LED sobre la piel y midiendo cuánta luz rebota hacia un fotodetector. Esto funciona porque cada vez que el corazón late, llega más sangre a los vasos sanguineos y eso cambia la cantidad de luz reflejada, generando una variación eléctrica. Contando esas variaciones se obtienen las pulsaciones por minuto (BPM), como es el caso del sensor de Pulse.sensor.com. El sensor mas utilizado es el MAX30102 que mide también oxígeno en sangre, fabricado por Maxim Integrated. Este ademas de tener dos leds y un fotodetector, tiene un sensor de temperatura interno y como consume poca corriente es facil hacer proyectos portatiles con el.

**PulseSensor.png**

<img src="./imagenes/PulseSensor.png" alt="install" width="500">

**Max30102.png**

<img src="./imagenes/Max30102.png" alt="install" width="500">


Algunos de los puntos debiles que tiene este sensor suceden por ejemplo si el usuario que se le esta midiendo el pulso se mueve o si se aprieta demasiado el sensor, tambien si se esta midiendo en el dedo puede tener problemas si tiene un esmalte de uñas muy grueso o si la temperatura corporal esta muy alterada, tambien la luz ambiental tiene que estar preferiblemente controlada para que funcione mejor y sean mas precisos los datos

Al ser tan versatil a veces se integra a los dispositivos inteligentes, como relojes y monitores de actividad deportiva, posibilitando el monitoreo de la frecuencia cardíaca durante los entrenamientos.

Como ejemplo me llamo la atencion Pulse Room de el artista digital Mexicano, Rafael Lozano-Hemmer, la obra es una intevenion artistica que esta compuesta por dos partes, por un lado tenemos una consola que detecta la frecuencia cardiaca, y por el otro lado tenemos una serie de ampolletas led, que en algunas ocasiones llegaron a ser 300, y estas dos partes dialogan de la siguiente manera: cuando se toca la consola, el sensor incorporado registra el ritmo cardiaco y las luces comienzan a prenderse y apagarse imitando las pulsasiones, desplazandose de tal forma que el ritmo del último usuario se imprime en la primera ampolleta y va empujando los ritmos de los visitantes anteriores a las hileras mas lejanas de ampolletas.

**Plataforma, Fábrica La Constancia, Puebla, México, 2006**

<img src="./imagenes/as3r43.gif" alt="install" width="500">

**Enter Action-Digital Art Now, ARoS Aarhus Kunstmuseum, Aarhus, Denmark, 2009**

<img src="./imagenes/pulseroom2.gif" alt="install" width="500">


## Actuador

## Bibliografía

### Sensor:

https://www.polar.com/ar-es/explore/heart/optical-heart-rate?srsltid=AfmBOoq19K7bCSy03JDiLGLT7yffrw3xrYJCj9eRqPj11K5p0Py5gdDl
https://afel.cl/products/sensor-pulso-cardiaco-corazon?srsltid=AfmBOoo6FuucuOXlNX7iixlNmI2xyjE65Wf7BrylaO0yiD9LFT9xGvdn
https://www.lozano-hemmer.com/pulse_room.php
https://pulsesensor.com/pages/pulsesensor-manual
https://afel.cl/products/sensor-pulsioximetria-max30102?srsltid=AfmBOooQsCS0TE0x-UjsNl8IM3HjaWYF2Kxkyd0HIkJtS6jv7nIKT0D3
https://afel.cl/products/sensor-pulso-cardiaco-corazon?srsltid=AfmBOoo6FuucuOXlNX7iixlNmI2xyjE65Wf7BrylaO0yiD9LFT9xGvdn

