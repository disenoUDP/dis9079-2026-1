# persona-4

AntFuentealba

## Investigación sobre APIs (Application Programming Interface)
### ¿Qué es una API?

Una API (Application Programming Interface o Interfaz de Programación de Aplicaciones) es un conjunto de reglas, protocolos y definiciones que permite la comunicación entre distintos sistemas, aplicaciones o servicios de software.

En términos simples, una API funciona como un intermediario o puente entre dos sistemas: recibe una solicitud, la envía al sistema correspondiente, y devuelve una respuesta sin que el usuario o la aplicación necesiten conocer cómo funciona internamente el sistema al que se conectan.

Una forma fácil de entenderlo es mediante la metáfora del restaurante:

- El usuario es el cliente
- La API es el mesero
- El servidor es la cocina
- El resultado es el plato que llega a la mesa

El cliente hace un pedido, el mesero lo transmite, la cocina lo prepara y luego devuelve el resultado.

### ¿Cómo funciona una API?
El funcionamiento de una API se basa en el modelo de solicitud y respuesta:

1. Una aplicación (cliente) envía una solicitud.
2. Esa solicitud viaja a un servidor a través de la API.
3.El servidor procesa la información.
4. Devuelve una respuesta estructurada.
5. La aplicación utiliza esos datos para mostrarlos o procesarlos.

En APIs web, esta comunicación ocurre mediante protocolos como HTTP o HTTPS, y los datos suelen enviarse en formato JSON o XML.

Ejemplo de respuesta JSON:
```cpp
{
  "ciudad": "Santiago",
  "temperatura": 18,
  "estado": "nublado"
}
```
### Conceptos clave
Endpoint

Un endpoint es una dirección específica dentro de una API donde se solicita una función o dato.

Ejemplo:

- API general: `https://api.clima.com`
- Endpoint: `/clima`

Cada endpoint entrega información distinta, como temperatura, pronóstico o ubicación.

API = sistema completo
Endpoint = punto específico dentro del sistema

### Funcionamiento desde el código

El flujo general de uso de una API es:

- Se define la URL del endpoint
- Se envía una solicitud con parámetros (ej: ciudad=Santiago)
- La API responde con datos
- El código interpreta la respuesta (JSON)
- Los datos se usan en la aplicación

En lenguajes como C++, el JSON llega como texto y debe ser interpretado antes de usarse como variables reales.

### Tipos de APIs
1. API REST

Es la más utilizada actualmente. Funciona mediante solicitudes HTTP simples.

- Flexible y ligera
- Muy común en aplicaciones web y móviles
- Usa JSON como formato principal

Ejemplo: aplicaciones del clima o redes sociales

2. API SOAP

Es más rígida y estructurada.

- Usa reglas estrictas
- Más segura, pero menos flexible
- Basada en XML

Ejemplo: sistemas bancarios o servicios institucionales como correos corporativos

3. API RPC

Permite ejecutar funciones específicas en otro sistema.

- Se comporta como llamadas a funciones remotas
- Muy directa

Ejemplo: Discord mostrando actividad de juegos

4. API WebSocket

Permite comunicación en tiempo real.

- Conexión continua entre cliente y servidor
- Intercambio constante de datos

Ejemplo: chats en vivo o videojuegos online

### Clasificación general de APIs
- APIs de datos: gestionan bases de datos
- APIs de sistemas operativos: acceden a hardware o sistema
- APIs web: funcionan por internet
- APIs públicas: abiertas a desarrolladores externos
- APIs privadas: uso interno de organizaciones

### Ventajas de las APIs

Las APIs son fundamentales en el desarrollo moderno porque:

- Facilitan la integración entre sistemas
- Reducen tiempo de desarrollo
- Permiten reutilizar funcionalidades
- Mejoran la escalabilidad
- Impulsan la innovación digital
- Permiten crear servicios conectados

### APIs y transformación digital

Las APIs son clave en la transformación digital porque permiten conectar plataformas, automatizar procesos y compartir datos en tiempo real.

Se utilizan ampliamente en:

- Banca
- Salud
- Educación
- Comercio electrónico
- Servicios gubernamentales

Esto ha permitido la creación de sistemas más eficientes, conectados y personalizados.

### Ejemplo real: Spotify Web API

La Spotify Web API permite acceder a información de:

- Canciones
- Artistas
- Álbumes
- Playlists

#### Características principales:

- Usa HTTP/HTTPS
- Devuelve datos en JSON
- Sigue arquitectura REST
- Requiere autenticación (OAuth 2.0)

Permite crear aplicaciones que muestran datos musicales, estadísticas y recomendaciones en tiempo real.

### APIs en diseño y experiencia de usuario

Desde el diseño de productos digitales, las APIs permiten:

- Interfaces dinámicas
- Contenido en tiempo real
- Personalización de experiencias
- Integración de servicios externos

Esto mejora la interacción del usuario y permite experiencias más fluidas y adaptadas.

### Conclusión

Las APIs son una pieza fundamental del desarrollo de software moderno. Funcionan como un puente entre sistemas, permitiendo la comunicación eficiente entre aplicaciones sin necesidad de conocer su funcionamiento interno.

Gracias a ellas, es posible construir aplicaciones más rápidas, conectadas, escalables y centradas en el usuario. Su uso sigue creciendo en todos los ámbitos digitales, siendo esenciales en la tecnología actual.

### Bibliografía

- AWS – What is an API
https://aws.amazon.com/what-is/api/

- IBM – What is an API (2024)
https://www.ibm.com/think/topics/api

- Spotify Developer Documentation (Web API)
https://developer.spotify.com/documentation/web-api

- Prototypr Blog – Spotify Web API
https://blog.prototypr.io/have-you-heard-about-the-spotify-web-api-8e8d1dac9eaf

- Delta Protect – Introducción a APIs
https://www.deltaprotect.com/blog/que-es-una-api

- Outvio – ¿Qué es una API?
https://outvio.com/es/blog/que-es-una-api/

- Appleute – REST API explanation
https://www.appleute.de/es/biblioteca-para-desarrolladores-de-aplicaciones/what-is-rest-api/



