# persona-1

Martina Alegría Coloma

## Investigación sobre APIs

### ¿Qué es una API?

Las API (interfaces de programación de aplicaciones) son mecanismos que permiten que diferentes aplicaciones o componentes de software se comuniquen entre sí mediante solicitudes y respuestas. Funcionan como un puente entre un cliente, que realiza una petición, y un servidor, que entrega la información o servicio solicitado. Gracias a las API, los desarrolladores pueden integrar datos, servicios y funcionalidades de otras aplicaciones sin necesidad de crearlos desde cero, lo que simplifica y acelera el desarrollo de software.

Para que una API sea fácil de utilizar, es fundamental contar con una documentación clara que explique sus funciones, protocolos, métodos de autenticación y la forma correcta de estructurar las solicitudes y respuestas.

### Flujo de trabajo 

<img width="453" height="186" alt="image" src="https://github.com/user-attachments/assets/fd7a82ab-eba5-4804-89b3-a6d4d659ad01" />

*Fuente: Finerio Connect*


Una app hace una solicitud (request) a la API
La API procesa esa solicitud y la envía al sistema correspondiente
El sistema responde con los datos solicitados
La API te devuelve esa respuesta en un formato estándar

#### Tipos de API

* REST — La más popular hoy en día. Usa HTTP y es fácil de entender. Ejemplo: la mayoría de apps web y móviles.

* SOAP — Más antigua y rígida, usa XML. Común en sistemas bancarios o empresariales.

* GraphQL — Más moderna, permite pedir exactamente los datos que necesitas.

* WebSocket — Para comunicación en tiempo real, como chats o juegos.

### Ejemplos cotidianos de APIs

- Tú ingresas tu número de tarjeta en un formulario --> Ese número va directamente a la API de Stripe (nunca lo ve la tienda) --> Stripe valida con el banco y devuelve: "aprobado" o "rechazado" --> La tienda solo recibe ese resultado, jamás tus datos bancarios.

- Cuando Uber, Rappi o cualquier app muestra un mapa. La app envía a la API: "dame el mapa de esta zona con estas coordenadas" --> Google Maps devuelve los datos visuales del mapa --> La app los muestra como si fueran propios

- Cuando abres una app del clima: La app detecta tu ubicación (coordenadas GPS) --> Le pregunta a la API: "¿qué clima hay en latitud X, longitud Y?" --> La API responde con temperatura, humedad, pronóstico, etc. en formato JSON ---> La app toma esos números y los muestra de forma bonita}


## Bibliografía

- Amazon Web Services. s.f. ¿Qué es una interfaz de programación de aplicaciones (API)? AWS. https://aws.amazon.com/es/what-is/api/
- Bengochea, D. Marzo, 2022. API: qué es, para qué sirve, cómo funciona y ejemplos. Outvio. https://outvio.com/es/blog/que-es-una-api/
- Goodwin, M. Abril, 2024. What is an API (application programming interface)? IBM. https://www.ibm.com/think/topics/api
  
