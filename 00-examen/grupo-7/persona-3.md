# persona-3

Luisaatoro9

# Investigación sobre APIs

### Introducción

Cuando empecé a pensar en cómo hacer que las plantas "hablen", me di cuenta de que necesitaba una forma de conectar datos del mundo real con algo que la gente pudiera ver, escuchar o sentir. Ahí fue cuando las APIs aparecieron como una herramienta central del proyecto. Al principio el término sonaba técnico y lejano, pero investigando fui entendiendo que en realidad ya las usamos todo el tiempo sin saberlo, ya que, cuando una app del clima te muestra la temperatura, cuando Spotify te recomienda una canción, o cuando un mapa calcula tu ruta en tiempo real, todo eso ocurre gracias a una API, cosa que no tenia idea. 

Esta investigación busca entender qué son las APIs, cómo funcionan, y sobre todo, cómo pueden ser relevantes para un proyecto como *La Voz de las Plantas*, donde los datos de las plantas, humedad del suelo, temperatura, luz, necesitan conectarse con una experiencia que tenga sentido para las personas.

---

### ¿Qué es una API?

API son las siglas de *Application Programming Interface*, que en español sería algo como "Interfaz de Programación de Aplicaciones". En términos simples, una API es un conjunto de reglas que permite que dos programas o sistemas se comuniquen entre sí. Funciona como un intermediario, ejemplo, tú haces una solicitud (un *request*) y el sistema te devuelve una respuesta (un *response*) con los datos que pediste.

Una metáfora que me ayudó a entenderlo fue, imagina que estás en un restaurante. Tú eres la aplicación, la cocina es el sistema que tiene los datos, y el mesero es la API. Tú no entras directamente a la cocina a buscar tu comida, sino que le dices al mesero lo que necesitas, él lo transmite a la cocina y te trae de vuelta lo que pediste. La API hace exactamente eso, traduce y transmite solicitudes entre sistemas que de otra forma no podrían hablar entre sí.

Existen diferentes tipos de APIs, pero las más comunes hoy en día son las **APIs REST**, que funcionan a través de internet usando el protocolo HTTP. Estas APIs reciben solicitudes en forma de URLs con parámetros específicos y responden, normalmente, con datos en formato JSON, que es una estructura de texto que tanto las personas como las máquinas pueden leer con relativa facilidad.

---

### ¿Cómo funcionan?

El flujo básico de una API REST es el siguiente:

1. **El cliente hace una solicitud (request):** esto puede ser una aplicación, un script o incluso un navegador web. La solicitud se hace a una URL específica llamada *endpoint*, que es como la "puerta de entrada" de la API.
2. **La API procesa la solicitud:** verifica que sea válida, que el cliente tenga los permisos necesarios (muchas APIs requieren una *API key*, que es básicamente una contraseña de acceso) y busca los datos pedidos.
3. **La API devuelve una respuesta (response):** generalmente en formato JSON, con los datos solicitados o con un mensaje de error si algo salió mal.

Por ejemplo, si quisiéramos consultar la temperatura actual de Santiago usando la API de OpenWeather, haríamos una solicitud a una URL que se vería más o menos así:

```
https://api.openweathermap.org/data/2.5/weather?q=Santiago&appid=TU_API_KEY
```

Y la API respondería con un bloque de datos JSON que incluiría la temperatura, la humedad, la descripción del clima, entre otras cosas.

Un aspecto importante es que muchas APIs son **públicas y gratuitas** (al menos en sus niveles básicos), lo que las hace muy accesibles para proyectos creativos, educativos o experimentales como este.

---

### Referentes investigados

### The Cat API

**Sitio:** [https://www.thecatapi.com](https://www.thecatapi.com)

The Cat API fue uno de los primeros referentes que exploré, no tanto por su contenido (imágenes y datos de gatos) sino porque es un ejemplo casi perfecto para entender cómo funciona una API en la práctica. Su estructura es muy clara y directa, que quiere decir esto, hacés una solicitud a su endpoint y te devuelve una imagen aleatoria de un gato en formato JSON, con su URL, dimensiones y otros datos.

Lo valioso de este referente es que demuestra que una API no necesita ser compleja para ser funcional. También muestra cómo los datos pueden ser dinámicos, es decir, que cada vez que hacés la misma solicitud, podés obtener un resultado diferente. Eso es relevante para mi proyecto porque quiero que la "voz" de cada planta sea única y cambiante según sus condiciones en tiempo real.

---

### NASA Open APIs

**Sitio:** [https://api.nasa.gov](https://api.nasa.gov)

La NASA ofrece una colección de APIs públicas que permiten acceder a imágenes, datos astronómicos, información sobre el clima espacial y mucho más. Una de las más conocidas es la APOD (*Astronomy Picture of the Day*), que entrega una imagen del espacio diferente cada día junto con una descripción escrita por astrónomos.

Lo que me interesó de este referente es cómo la NASA usa sus APIs no solo para compartir datos científicos, sino también para crear experiencias visuales y narrativas. Las imágenes del cosmos que genera esta API son tan impresionantes que artistas y diseñadores las usan para crear piezas audiovisuales, instalaciones y publicaciones.

---

### OpenWeather API

**Sitio:** [https://openweathermap.org/api](https://openweathermap.org/api)

OpenWeather es una de las APIs más usadas en proyectos creativos y funcionales que necesitan datos climáticos en tiempo real. Permite consultar temperatura, humedad, presión atmosférica, velocidad del viento y pronósticos extendidos para prácticamente cualquier lugar del mundo.

Este referente es directamente relevante para *La Voz de las Plantas* porque las plantas no viven aisladas porque responden al clima exterior. La temperatura del ambiente, la humedad del aire, la cantidad de lluvia… todos esos factores influyen en el estado de una planta. Podría cruzar los datos internos del sensor (humedad del suelo, temperatura de la maceta) con los datos climáticos externos de OpenWeather para construir una narrativa más completa de lo que está viviendo la planta en ese momento.

---

### The Metropolitan Museum of Art Open Access API (The Met API)

**Sitio:** [https://metmuseum.github.io](https://metmuseum.github.io)  
            [https://www.metmuseum.org/hubs/open-access](https://www.metmuseum.org/hubs/open-access)

El Museo Metropolitano de Arte de Nueva York tiene una API completamente abierta y gratuita que da acceso a más de 400.000 obras de su colección, incluyendo imágenes en alta resolución, datos sobre artistas, fechas, materiales y procedencia de cada pieza.

Este es uno de los referentes que más me impactó porque demuestra cómo una institución cultural puede democratizar el acceso a su patrimonio a través de la tecnología. Cualquier persona, con un poco de código, puede acceder a una pintura del Renacimiento o a una escultura griega y usarla en un proyecto creativo, educativo o artístico sin pagar nada. Para mi proyecto, esto abre la posibilidad de conectar el estado de una planta con imágenes de flores u obras botánicas del museo, si la planta está bien hidratada y floreciendo, podría "mostrar" una obra llena de color o si está seca, algo más austero.

---

### Corsicana — Everest Pipkin

**Sitio del proyecto:** [https://everest-pipkin.com/projects/corsicana](https://everest-pipkin.com/projects/corsicana)  
**Web del artista:** [https://everest-pipkin.com](https://everest-pipkin.com)

Everest Pipkin es una artista y desarrolladora que trabaja en la intersección entre sistemas digitales, naturaleza y poesía computacional. Su proyecto *Corsicana* es un generador de texto que crea pequeñas historias sobre objetos cotidianos, paisajes y seres vivos usando datos y algoritmos.

Pipkin no solo usa datos para informar, sino para crear narrativas, para hacer que el espectador sienta algo. 

---

### Ye Seul Kim — *Slow Dimming Study* y *Invisible Sculpture on Wheels*

**Slow Dimming Study:** [https://yeseul.com/Slow-Dimming-Study-Rice-Dimmer](https://yeseul.com/Slow-Dimming-Study-Rice-Dimmer)  
**Invisible Sculpture on Wheels:** [https://yeseul.com/Invisible-Sculpture-On-Wheels-GimHae](https://yeseul.com/Invisible-Sculpture-On-Wheels-GimHae)

Ye Seul Kim es una artista coreana que trabaja con la relación entre sistemas vivos, tiempo y percepción. En *Slow Dimming Study*, interviene el ciclo de vida de los granos de arroz conectándolo a un sistema de iluminación que responde a su proceso de fermentación. En *Invisible Sculpture on Wheels*, trabaja con objetos y movimientos imperceptibles para el ojo humano pero que existen y ocurren constantemente.

Estos trabajos fueron fundamentales para mí porque plantean una pregunta que también está en el centro de mi proyecto, ¿cómo hacemos visible lo que normalmente no vemos? Las plantas hacen cosas todo el tiempo, transpirar, absorber agua, crecer milímetro a milímetro pero no lo percibimos o con tan solo hablarles ya tienen una reacción que como decia antes no nos es fácil verlo. La obra de Ye Seul Kim me inspiró a pensar en la experiencia del tiempo lento y en cómo los datos pueden volver perceptible lo imperceptible.

---

## Reflexión

Antes de esta investigación, la palabra API sonaba a algo exclusivamente técnico, casi ajeno al diseño. Pero investigando me di cuenta de que las APIs son, en el fondo, sistemas de traducción, toman algo que existe en un formato y lo convierten en algo que puede ser usado en otro contexto. Y eso, traducir, interpretar, mediar entre sistemas, es exactamente lo que hacemos en diseño.

Lo más interesante de los referentes que encontré, especialmente los de Everest Pipkin y Ye Seul Kim, es que no usan los datos para simplemente "mostrar información", sino para crear experiencias que hacen sentir algo. Eso es lo que busco con *La Voz de las Plantas*, que cuando alguien interactúe con la pieza, no esté leyendo datos de una planta, sino escuchándola, sintiéndola, entendiéndola de una manera distinta.

---

## Bibliografía

- Wikipedia. *API (Application Programming Interface)*.  
  [https://en.wikipedia.org/wiki/API](https://en.wikipedia.org/wiki/API)

- MDN Web Docs. *Introduction to web APIs*.  
  [https://developer.mozilla.org/en-US/docs/Learn/JavaScript/Client-side_web_APIs/Introduction](https://developer.mozilla.org/en-US/docs/Learn/JavaScript/Client-side_web_APIs/Introduction)

- The Cat API.  
  [https://www.thecatapi.com](https://www.thecatapi.com)

- NASA Open APIs.  
  [https://api.nasa.gov](https://api.nasa.gov)

- OpenWeather API.  
  [https://openweathermap.org/api](https://openweathermap.org/api)

- The Metropolitan Museum of Art — Open Access.  
  [https://www.metmuseum.org/hubs/open-access](https://www.metmuseum.org/hubs/open-access)

- The Met Collection API — Documentación técnica.  
  [https://metmuseum.github.io](https://metmuseum.github.io)

- Everest Pipkin — *Corsicana*.  
  [https://everest-pipkin.com/projects/corsicana](https://everest-pipkin.com/projects/corsicana)

- Everest Pipkin — Sitio web.  
  [https://everest-pipkin.com](https://everest-pipkin.com)

- Ye Seul Kim — *Slow Dimming Study / Rice Dimmer*.  
  [https://yeseul.com/Slow-Dimming-Study-Rice-Dimmer](https://yeseul.com/Slow-Dimming-Study-Rice-Dimmer)

- Ye Seul Kim — *Invisible Sculpture on Wheels, GimHae*.  
  [https://yeseul.com/Invisible-Sculpture-On-Wheels-GimHae](https://yeseul.com/Invisible-Sculpture-On-Wheels-GimHae)
