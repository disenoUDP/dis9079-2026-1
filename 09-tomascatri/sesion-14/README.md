# sesion-14

lunes 15 junio 2026

Hola, tanto tiempo. Sinceramente, estuve tan metido con el código y con que funcionara todo que se me olvidó por completo llenar las bitácoras, por lo que pondré todo el proceso que hice los días anteriores, pero algo resumido para que se tenga contexto sobre el proceso.

## Proceso

### Clase de 1 de junio


Ya que falté ese día, mi grupo puso sobre la mesa usar la API de los sismos en Chile. Investigando, me di cuenta de que existe una API que toma de referencia los datos de sismología de la Universidad de Chile y que se podría utilizar para el proyecto. Tenía pensado que podríamos usar unos motores que tenía Kiara de un examen que tuvo para simular la magnitud en miniatura.

* [Documentación API Earthquake](https://docs.boostr.cl/reference/earthquake)
* [Endpoint API Earthquake](https://api.boostr.cl/earthquake.json)

---

### Clase 8 de junio

En clase estuvimos pensando qué podríamos hacer, ya que lo de los sismos era solo una idea. Propusimos que nos basáramos en un proyecto llamado:

* [Pixela](https://rai-lander.itch.io/pixela)

Una plataforma que transforma fotografías en imágenes con estética retro mediante el procesamiento de píxeles y la aplicación de paletas de colores limitadas. A través de la aplicación web alojada directamente en la cámara Pixela, se puede configurar una variedad de funciones, incluidos métodos de procesamiento de imágenes, paletas de colores, diferentes modos de captura, configuraciones de conexión Wi-Fi y otras pequeñas personalizaciones, como paletas de colores favoritas.

![Referente](./imagenes/referente.jpg)

Después de aprobar esto, vimos cómo podríamos adaptar este proyecto a nuestro presupuesto, materiales y a la rúbrica.

A partir de esta idea, compramos lo siguiente para el proyecto:

* ESP32-CAM y su base que venía junto a la cámara llamada ESP32-CAM-MB.
* Pantalla TFT LCD 2" de 240x320 (elegimos esa resolución, ya que en el proyecto original es la que da mejores resultados).

Los componentes que ya tenemos y usamos:

* Potenciómetro 100k
* 3 push button
* Pantalla LCD 128 × 64
* Módulo SD
* micro-SD junto a adaptador SD
* Muchos cables jumper

---

### Clase 15 de junio

Ya teníamos una idea de lo que queríamos hacer, lo cual sería de esta forma: Raspberry se encarga de controlar todo lo que tiene que ver con el disparo y selección de filtro y la ESP32-CAM procesa y saca las fotos. Esta foto sería subida a Google Drive automáticamente desde el ESP32. Posteriormente, con el Arduino R4 WiFi haríamos la visualización de las imágenes subidas al Google Drive con la pantalla de 240x320 para que cuando uno se sacara la foto viera el resultado.

La API sería Google Drive. Para eso usamos un script de Google para lograr esto. Este script se basa en el que se usa en Pixela para subir las fotos a Google Drive y funciona así:

```text
Cámara
   │
   │ POST (imagen en Base64)
   ▼
Google Apps Script
   │
   ├── Guarda imagen en Google Drive
   └── Registra metadatos en Google Sheets (opcional)
   │
Arduino UNO R4
   │ GET (solicita imagen)
   ▼
Apps Script
   │
   ├── Busca imágenes en Drive
   ├── Redimensiona → 240×320
   ├── Convierte → RGB565
   └── Devuelve Base64
```

Suena fácil porque fue la solución que encontramos, ya que entre medio hubo muchos flujos de trabajo y descubrimos que lo mejor por ahora era repartir así las funciones de cada microchip para no saturarlos.

En la semana anterior a ese día realicé todo el código de la ESP32-CAM junto a la Raspberry Pi Pico 2 W; más que nada era una maqueta funcional. Ya en otro día mejoré los filtros y añadí un flash a la cámara que permitía saber cuándo iba a sacar la foto.

#### Evolución de pruebas

![Intento 1](./imagenes/intento1.jpg)

*No detectaba filtros y también aparece mi gata.*

![Intento 2](./imagenes/intento2.jpg)

*El tratamiento de imagen era igual en todos, solo cambiaban los colores mostrados.*

![Intento 3](./imagenes/intento3.jpg)

*Ahora ya los píxeles se repartieron de manera más interesante.*

![Intento 4](./imagenes/intento4.jpg)

*Se hizo una selección de cómo uno quiere que los píxeles se distribuyan tal como el referente, lo que da más juego al proyecto.*

Dejaré el Drive que usé; hay una carpeta de pruebas en donde se puede ver la evolución de los filtros y de mi locura:

* [Carpeta de pruebas en Google Drive](https://drive.google.com/drive/u/0/folders/1SUIurSYrSJvULb5bxX92DnnLRRc22yIt)

Ya en clases, intentamos probar el Arduino Uno R4 WiFi, pero lamentablemente no estaba funcionando, tampoco la pantalla, por lo que la clase se basó en intentar hacerlo funcionar como fuera.

Según la IA, se necesita una SD para poder poner imágenes de manera consistente en el Arduino dado su baja memoria, por lo que sacamos un módulo SD para usarlo en el Arduino, pero ese día justo no llevé el adaptador, por lo que nos quedamos con las ganas de probar, además de que la pantalla seguía sin funcionar.


