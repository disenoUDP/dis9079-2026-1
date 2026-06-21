# persona-1

brauliofigueroa2001

## investigación textual sobre API

### ¿qué es una API?

la definición exacta de API según IBM (International Business Machines) es:

una API (o interfaz de programación de aplicaciones) es un conjunto de reglas o protocolos que permite que las aplicaciones de software se comuniquen entre sí para intercambiar datos, características y funcionalidades.

las API simplifican y aceleran el desarrollo de aplicaciones y software al permitir que los desarrolladores integren datos, servicios y capacidades de otras aplicaciones, en lugar de desarrollarlos desde cero.
Ofrecen a los propietarios de aplicaciones una forma sencilla y segura de poner a disposición los datos y las funciones de sus aplicaciones tanto para consumidores internos como externos de la API.

son interfaces predefinidas que comparten únicamente los datos y las funciones necesarias para consultas específicas. Los servidores no tienen que exponer todos sus datos; las API permiten compartir pequeños paquetes de información relevantes para una solicitud determinada.

además, mantienen ocultos otros detalles internos del sistema, lo que ayuda a preservar la integridad y la seguridad del sistema.

info extraída de: [IBM](https://www.ibm.com/think/topics/api) y traducida con chatgpt

### ¿cómo funciona una API?

es útil pensar en la comunicación mediante una API en términos de una solicitud (request) y una respuesta (response) entre un cliente y un servidor. La aplicación que envía la solicitud es el cliente, y el servidor proporciona la respuesta. La API actúa como el puente que establece la conexión entre ambos.

**ejemplo de cómo funciona**

una forma sencilla de entender cómo funcionan las API es observar un ejemplo común: el procesamiento de pagos por parte de terceros.

cuando un usuario compra un producto en un sitio de comercio electrónico, el sitio puede ofrecer la opción de “Pagar con PayPal” u otro sistema externo de pago. Esta funcionalidad depende de las API para establecer la conexión entre ambas plataformas.

**paso a paso del ejemplo**

- cuando el comprador hace clic en el botón de pago, se envía una llamada a la API para recuperar información. Esta es la solicitud (request). La solicitud se procesa desde una aplicación hacia el servidor web a través del Identificador Uniforme de Recursos (URI) de la API e incluye un verbo de solicitud, encabezados (headers) y, en ocasiones, un cuerpo de solicitud (request body).

- después de recibir una solicitud válida desde la página del producto, la API realiza una llamada al programa externo o servidor web; en este caso, al sistema de pago de terceros.

- el servidor envía una respuesta a la API con la información solicitada.

- luego, la API transfiere los datos a la aplicación que realizó la solicitud inicial, en este caso, el sitio web del producto.

- aunque la transferencia de datos varía según el servicio web utilizado, todas las solicitudes y respuestas se realizan a través de una API. No existe visibilidad de este proceso en la interfaz de usuario; es decir, las API intercambian datos dentro del computador o de las aplicaciones y, para el usuario, todo aparece como una conexión fluida y transparente.

info extraída de: [IBM](https://www.ibm.com/think/topics/api) y traducida con chatgpt

### tipos de APIS

las API pueden clasificarse según su caso de uso, incluyendo API de datos, API de sistemas operativos, API remotas y API web.

**API web**

las API web permiten la transferencia de datos y funcionalidades a través de internet mediante el protocolo HTTP.

hoy en día, la mayoría de las API son API web. Estas constituyen un tipo de API remota (lo que significa que utilizan protocolos para manipular recursos externos) que exponen los datos y las funcionalidades de una aplicación a través de internet.

**Los cuatro tipos principales de API web son:**

**API abiertas (Open APIs)**

las API abiertas son interfaces de programación de aplicaciones de código abierto a las que se puede acceder mediante el protocolo HTTP. También conocidas como API públicas, cuentan con puntos de acceso (endpoints) definidos y formatos establecidos para las solicitudes y respuestas.

**API de socios (Partner APIs)**

las API de socios conectan a socios comerciales estratégicos. Por lo general, los desarrolladores acceden a estas API de forma autoservicio a través de un portal público para desarrolladores. Sin embargo, deben completar un proceso de incorporación y obtener credenciales de acceso para utilizar las API de socios.

**API internas (Internal APIs)**

las API internas, o privadas, permanecen ocultas para los usuarios externos. Estas API no están disponibles fuera de la empresa. En cambio, las organizaciones las utilizan para mejorar la productividad y la comunicación entre distintos equipos internos de desarrollo.

**API compuestas (Composite APIs)**

las API compuestas combinan múltiples API de datos o servicios. Permiten a los programadores acceder a varios endpoints mediante una sola llamada.Son especialmente útiles en arquitecturas de microservicios, donde la ejecución de una única tarea puede requerir información proveniente de varias fuentes.

### otros tipos de APIS menos comunes

- API de datos (o de bases de datos): se utilizan para conectar aplicaciones con sistemas de gestión de bases de datos.
  
- API de sistemas operativos (o locales): se utilizan para definir cómo las aplicaciones utilizan los servicios y recursos del sistema operativo.
  
- API remotas: se utilizan para definir cómo interactúan las aplicaciones que se ejecutan en distintos dispositivos.

### ejemplos de APIS

Debido a que las API permiten a las organizaciones abrir el acceso a sus recursos manteniendo la seguridad y el control, se han convertido en un componente valioso de las aplicaciones modernas, tanto empresariales como personales.

**A continuación, se presentan algunos ejemplos de API que los usuarios encuentran con frecuencia:**

### inicios de sesión universales 

- un ejemplo popular de API es la función que permite a las personas iniciar sesión en sitios web utilizando los datos de acceso de sus perfiles de Facebook, X o Google. Esta práctica funcionalidad permite que cualquier sitio web utilice la API de uno de estos servicios populares para realizar una autenticación rápida.

- esta capacidad ahorra a los usuarios el tiempo y las molestias de crear un nuevo perfil para cada aplicación web o nueva membresía.

**ejemplos concretos**

- iniciar sesión en Spotify utilizando una cuenta de Google.

- acceder a Canva usando las credenciales de Facebook sin crear una cuenta nueva.

### internet de las Cosas (IoT)

- estos dispositivos “inteligentes” ofrecen funcionalidades adicionales, como pantallas táctiles con acceso a internet y recopilación de datos, gracias al uso de API.

- por ejemplo, un refrigerador inteligente puede conectarse a aplicaciones de recetas o crear y enviar notas a teléfonos móviles mediante mensajes de texto. Sus cámaras internas pueden conectarse a distintas aplicaciones para que los usuarios puedan ver el contenido del refrigerador desde cualquier lugar.

**ejemplos concretos**

- un termostato inteligente que consulta la información meteorológica mediante una API para ajustar automáticamente la temperatura del hogar.

- una pulsera deportiva que envía datos de actividad física a una aplicación móvil para generar estadísticas y recomendaciones.

### comparación de reservas de viaje

- los sitios web de reservas de viajes reúnen información de miles de vuelos y muestran las opciones más económicas para cada fecha y destino. Las API hacen posible este servicio al proporcionar a los usuarios acceso a información actualizada sobre la disponibilidad de hoteles y aerolíneas.

- este acceso puede realizarse tanto desde un navegador web como desde la propia aplicación de la empresa de reservas. Gracias al intercambio automatizado de datos y solicitudes, las API reducen significativamente el tiempo y el esfuerzo necesarios para buscar vuelos o alojamientos disponibles.

**ejemplos concretos**

- Skyscanner consulta las API de múltiples aerolíneas para mostrar los vuelos más económicos disponibles.

- Kayak utiliza API de hoteles para comparar precios y disponibilidad en distintas plataformas de reserva.

### aplicaciones de navegación

- las aplicaciones de navegación utilizan API fundamentales que muestran mapas estáticos o interactivos. Además, emplean otras API y funcionalidades para ofrecer indicaciones de ruta, límites de velocidad, puntos de interés, alertas de tráfico y mucho más.

- los usuarios interactúan indirectamente con una API cuando planifican rutas de viaje o realizan el seguimiento de elementos en movimiento, como un vehículo de reparto.

**ejemplos concretos**

- Google Maps utiliza API para mostrar mapas, calcular rutas y ofrecer información del tráfico en tiempo real.

- Waze emplea API para recibir y compartir reportes de accidentes, congestiones y obras en la vía.

### redes sociales

 - las empresas de redes sociales utilizan API para permitir que otras organizaciones compartan e integren contenido publicado en sus plataformas dentro de sus propios sitios web.

 - por ejemplo, la API de Instagram permite a las empresas insertar su cuadrícula de publicaciones de Instagram en su sitio web y actualizarla automáticamente cada vez que se publica nuevo contenido.

 **ejemplos concretos**

 - una tienda en línea que muestra automáticamente sus últimas publicaciones de Facebook en su página principal.

### aplicaciones SaaS

- las API son una parte fundamental del crecimiento de los productos de Software como Servicio (SaaS).

- plataformas como los CRM (herramientas de gestión de relaciones con clientes) suelen incluir varias API integradas que permiten a las empresas conectarse con aplicaciones que ya utilizan, como herramientas de mensajería, redes sociales y correo electrónico.

- esta integración reduce drásticamente el tiempo que los usuarios dedican a cambiar entre aplicaciones para realizar tareas de ventas y marketing. Además, ayuda a reducir o evitar los llamados silos de datos, que pueden surgir cuando distintos departamentos utilizan aplicaciones diferentes y la información queda aislada entre ellos.

**ejemplos concretos**

- un CRM como Salesforce conectado a Gmail para registrar automáticamente los correos electrónicos intercambiados con clientes.

- un sistema como HubSpot integrado con Slack para enviar notificaciones automáticas cuando se genera un nuevo prospecto de venta.

info sacada de [IBM](https://www.ibm.com/think/topics/api) ,traducción con chatgpt y ejemplos concretos de los tipos de API sacados de IA
