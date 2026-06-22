# persona-1

agustinaaceituno

# APIS   
_Application Programming Interface o Interfaz de Programación de Aplicaciones_
## ¿Qué es?
Una herramienta que permite que distintos programas, plataformas o dispositivos intercambien información y trabajen en conjunto. Se pueden incorporar funciones o servicios ya existentes dentro de sus proyectos, evitando tener que programar todo desde el principio. Las API ayudan a proteger los sistemas, ya que solo entregan los datos necesarios para cada petición, sin revelar el funcionamiento completo de la plataforma o servidor.

## ¿Qué pueden hacer?
* Conectan aplicaciones entre sí.
* Permiten compartir datos de forma segura.
* Automatizan tareas.
* Facilitan la integración de servicios externos.
* Ahorran tiempo y recursos de desarrollo.

### Principales funciones de las APIs
#### Compartir información
Permiten acceder a bases de datos o servicios externos para obtener información actualizada. Gracias a ellas, una aplicación puede consultar datos sin almacenarlos localmente.
* Obtener información.
* Consultar resultados.
* Mostrar mapas y ubicaciones.
* Acceder a catálogos de productos.
#### Integrar servicios externos
Permiten incorporar funciones desarrolladas por otras empresas o plataformas sin necesidad de crearlas desde cero.
* Integrar pagos electrónicos.
* Iniciar sesión con cuentas.
* Utilizar sistemas de geolocalización.
* Incorporar herramientas de inteligencia artificial.
#### Automatizar procesos
Muchas tareas repetitivas pueden ejecutarse automáticamente mediante APIs.
* Enviar correos automáticos.
* Actualizar inventarios entre sistemas.
* Sincronizar datos entre aplicaciones.
* Generar reportes en tiempo real.
## ¿Cómo funcionan las APIs?
El funcionamiento de una API se basa en el modelo de solicitud y respuesta.
* Una aplicación realiza una solicitud a la API.
* La API recibe la solicitud y la interpreta.
* La API se comunica con el sistema o servicio correspondiente.
* El sistema procesa la petición.
* La API devuelve una respuesta a la aplicación.

Este proceso ocurre mediante internet utilizando protocolos como HTTP o HTTPS y formatos de intercambio de datos como JSON o XML.

## Tipos de APIS
#### API Web
Permiten la comunicación entre aplicaciones a través de internet. Son las más comunes en la actualidad y hacen posible el funcionamiento de servicios como mapas, redes sociales, comercio electrónico y aplicaciones de inteligencia artificial.
* Google Maps
* YouTube
* Spotify
* OpenAI
#### API Privadas
Son desarrolladas para uso exclusivo dentro de una organización. Su objetivo es facilitar la comunicación entre sistemas internos, mejorar la eficiencia operativa y proteger información sensible. No están disponibles para desarrolladores externos.
* Una API utilizada por una empresa para conectar su sistema de ventas con su sistema de inventario.
#### API Públicas - Open API
Son aquellas que están disponibles para cualquier desarrollador o empresa que desee utilizarlas. Generalmente requieren un registro previo para obtener una clave de acceso, pero su documentación y funcionalidades son accesibles para el público. Estas APIs permiten integrar servicios externos de forma rápida y sencilla en aplicaciones web y móviles.
* API de Google Maps
* API de OpenWeather 
* API de OpenAI
#### API SOAP
SOAP (Simple Object Access Protocol) es un protocolo de comunicación que utiliza XML para intercambiar datos entre sistemas. Se caracteriza por seguir estándares estrictos de seguridad y confiabilidad, por lo que es ampliamente utilizado en sectores como la banca, la salud y los servicios gubernamentales.
* Sistemas bancarios que requieren altos niveles de seguridad para procesar transacciones.
### API REST
REST (Representational State Transfer) es la arquitectura de API más utilizada actualmente. Se basa en el protocolo HTTP y normalmente utiliza el formato JSON para intercambiar información. Destaca por su simplicidad, flexibilidad y facilidad de integración con aplicaciones web y móviles.
* API de Spotify
* API de GitHub 
* API de OpenAI
## Beneficios
#### Facilitan la integración entre sistemas

Las APIs permiten que diferentes aplicaciones y plataformas se comuniquen entre sí de manera eficiente. Gracias a ellas, sistemas desarrollados con tecnologías distintas pueden intercambiar información y trabajar conjuntamente sin necesidad de modificar su funcionamiento interno.

#### Ahorran tiempo de desarrollo

Los desarrolladores pueden utilizar servicios ya existentes en lugar de crear todas las funcionalidades desde cero. Esto reduce significativamente el tiempo necesario para desarrollar aplicaciones y permite concentrarse en aspectos más específicos del proyecto.

#### Favorecen la reutilización de código

Las APIs permiten aprovechar funciones y servicios previamente desarrollados, evitando duplicar esfuerzos. Esto mejora la productividad y facilita el mantenimiento de los sistemas.

#### Permiten la automatización de procesos

Muchas tareas que antes requerían intervención manual pueden ejecutarse automáticamente mediante APIs. Esto mejora la eficiencia, reduce errores y agiliza los flujos de trabajo.

#### Mejoran la escalabilidad

Las aplicaciones pueden crecer e incorporar nuevas funcionalidades mediante la integración de APIs adicionales sin necesidad de reconstruir todo el sistema. Esto facilita la adaptación a nuevas necesidades y al aumento de usuarios.

#### Facilitan el acceso a servicios externos

Las APIs permiten integrar servicios especializados como mapas, pagos en línea, redes sociales, inteligencia artificial o servicios meteorológicos sin necesidad de desarrollarlos internamente.

#### Mejoran la experiencia del usuario

Al integrar múltiples servicios y automatizar procesos, las aplicaciones pueden ofrecer funciones más avanzadas, rápidas y personalizadas, mejorando la experiencia de quienes las utilizan.

#### Incrementan la seguridad

Muchas APIs incluyen mecanismos de autenticación, autorización y cifrado que permiten controlar el acceso a la información y proteger los datos intercambiados entre sistemas.

#### Favorecen la innovación

Las APIs permiten combinar tecnologías y servicios de diferentes proveedores para crear nuevas soluciones, productos y experiencias digitales que serían difíciles de desarrollar de manera independiente.

#### Facilitan la actualización y el mantenimiento

Al estar separadas de las aplicaciones que las utilizan, las APIs pueden actualizarse o mejorarse sin afectar significativamente a los sistemas conectados, simplificando el mantenimiento y la evolución del software.

## Ejemplos
### API de Spotify
La Spotify Web API es una interfaz que permite a desarrolladores acceder a datos y funcionalidades de Spotify desde aplicaciones web, móviles o de escritorio. A través de esta API es posible obtener información sobre canciones, álbumes, artistas, listas de reproducción y usuarios.
### ¿Qué permite hacer?
##### Buscar contenido musical
* Permite buscar canciones, artistas, álbumes y playlists dentro del catálogo de Spotify.
#### Obtener información de artistas
* Nombre del artista
* Géneros musicales
* Álbumes publicados
#### Acceder a canciones y álbumes
* Nombre de la canción
* Duración
* Fecha de lanzamiento
* Portada del álbum
## Bibliografía

* Amazon Web Services. (s. f.). _¿Qué es una API?_ https://aws.amazon.com/es/what-is/api/
* MDN Web Docs. (s. f.). _Introducción a las APIs del lado del cliente._ https://developer.mozilla.org/es/docs/Learn_web_development/Extensions/Client-side_APIs/Introduction
* Red Hat. (s. f.). _¿Qué son las interfaces de programación de aplicaciones (API)?_ https://www.redhat.com/es/topics/api/what-are-application-programming-interfaces
* IBM. (s. f.). _API (Application Programming Interface)._ https://www.ibm.com/es-es/think/topics/api
Spotify Developer. (s. f.). _Spotify for Developers._ https://developer.spotify.com/
Fielding, R. T. (2012). _Architectural Styles and the Design of Network-based Software Architectures._ https://arxiv.org/abs/1205.6363




