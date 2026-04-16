# sesion-03 - lunes 23 marzo 2026

### Raspberry Pi vs  Arduino: Del microcontrolador al mini PC

Esta semana subimos de nivel. Dejamos un poco de lado el Arduino (que es más simple, para tareas específicas) para conocer la familia Raspberry Pi (más completa, color verde).

Lo más loco es la historia: desde la Harvard Mark I con suerte sumaba, hasta lo que tenemos hoy. Aprendí que Raspberry Pi no solo hace microcomputadores (como la Pi 5 o la Pi Zero), sino que ahora tienen su propio chip microcontrolador: el RP2050 (y su sucesor el RP2350 que viene en la Pico 2 W).

💡 Dato curioso El nombre del lenguaje Python no es por la serpiente, sino por una referencia cultural a Monty Python. 

**Tarea: ver el capítulo 1! 📺**

### Configurando el nuevo cerebro (Pico 2 W)

La Raspberry Pi Pico 2 W es una placa de alto rendimiento.

1. **ditor:** Dejamos el IDE de Arduino y nos pasamos a Visual Studio Code, que es más pro.
2. **Extensiones:** Instalamos la de "Raspberry Pi Pico" (la verificada) para poder programar.
3. **Lenguajes:** Usaremos C++ (para tener más control del hardware) o MicroPython (que es más sencillo).
4. **Protocolos:** Aprendimos que SPI se usa para cosas rápidas como pantallas (usa más cables) y I2C es más simple porque usa menos conexiones.

### El desafío: Solemne 01 (06 de abril)

El profe nos puso una meta difícil: comunicación inalámbrica entre dispositivos.

1. El reto: El Arduino Uno R4 WiFi debe enviar un mensaje a la Raspberry Pi Pico 2 W.
2. La reacción: Al recibirlo, la Raspberry debe prender o parpadear su LED integrado.
3. Nuestra propuesta: No nos quedaremos con lo mínimo, vamos a intentar que reaccione con algo extra, como un motor o un botón, para que sea una interacción de verdad. Se valora el orden y el intento!

### Otras plataformas y exploración

También vimos que existen placas súper específicas, sobre todo para audio y "audio extraño":

* **Bela.io:** Para audio de alta fidelidad.
* **Meet Daisy:** Un microcontrolador gigante para procesar sonido.
* **BeagleBoard:** Que hizo una alianza con una gente de arte en Inglaterra.

Audio y experimentación (Lo que profundicé)

Además de lo básico, estuve mirando e informandome con lo siqguiente:

1. **Korg:** Caché que marcas grandes como Korg ya meten placas Raspberry Pi dentro de sus sintetizadores digitales. O sea, la placa verde que tenemos es estándar en la industria de la música electrónica.
2. **Monome:** Son controladores minimalistas súper caros y de culto. Usan hardware parecido al que estamos viendo para crear interfaces de cuadrículas LED que los músicos usan para loopear sonidos.

### Bibliografía y Referencias

* Korg. (s.f.). *Electronic music icon Korg makes music with Raspberry Pi*. https://www.raspberrypi.com/news/electronic-music-icon-korg-makes-music-with-raspberry-pi/

* Mermaid.js. (s.f.). *Flowcharts*. https://mermaid.js.org/syntax/flowchart.html

* Monome. (s.f.). *Monome*. https://monome.org/

* New Interfaces for Musical Expression. (s.f.). *NIME*. https://nime.org/

* Raspberry Pi. (s.f.). *Raspberry Pi Pico 2 series: Product brief*. https://pip-assets.raspberrypi.com/categories/1005-raspberry-pi-pico-2/documents/RP-008302-DS-2-pico-2-product-brief.pdf

* Visual Studio Code. (s.f.). *Visual Studio Code*. https://code.visualstudio.com/

* Wikipedia contributors. (s.f.). *Harvard Mark I*. https://en.wikipedia.org/wiki/Harvard_Mark_I

