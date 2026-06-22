# persona-2

Monserrat-Paredes / https://github.com/Monserrat-Paredes


# Investigación sobre API (Interfaz de Programación de Aplicaciones)


## Origen

En la década de los 70, las API experimentaron su primer gran salto en progreso gracias a los sistemas distribuidos. Surgieron métodos que permitieron el acceso remoto a la API de procedimientos al tiempo que evitaban la sobrecarga típica del programador mediante el empaquetado y desempaquetado de datos requerido para la interoperación entre diferentes tipos de computadoras.

- 1947 : Herman Goldstine y John Von Neumann escriben sobre la idea general de reutilizar partes de código programático, llamándolos "subrutinas"

- 1968 : El TÉRMINO "API" se acuña formalmente en un artículo sobre gráficos computacionales por Ira W. Cotton y Frank S. Greatorex, crearon un sistema para que diferentes programas de software pudieran interactuar dentro de una misma computadora principal. Internet ni siquiera existía tal como lo conocemos.

- Años 60-70 : Las primeras APIs se usaban como bibliotecas en sistemas operativos , permitiendo comunicación entre programas en la misma máquina (sin Internet)

- 1989 : Tim Berners-Lee propone la web mundial, creando el estándar HTTP.

- 2000 : Roy Fielding define REST, transformando APIs en interfaces globales basadas en web.



## ¿Qué es una API?

Una API (por sus siglas en inglés Application Programming Interface , en español Interfaz de Programación de Aplicaciones ) es un conjunto de definiciones, reglas y protocolos que permite la comunicación entre diferentes aplicaciones o softwares. A diferencia de una interfaz de usuario que conecta una persona con un ordenador, una API conecta dos softwares o partes de un software.

En términos simples, una API es como un mensajero que actúa entre un cliente y un servidor: traduce el mensaje y entrega la respuesta.

Analogía del restaurante (Para entenderlo mejor):

- El cliente = el usuario/app que hace la solicitud.

- El camarero = la API (transmite la orden).

- El cocinero = el servidor que procesa y responde con la información.


<img width="654" height="605" alt="api3" src="https://github.com/user-attachments/assets/e738b63f-c125-4ba0-a14a-ca3196c8c5e6" />

Imagen sacada de: https://itsqmet.edu.ec/api/



## El concepto de "Caja Negra" y Seguridad

Las API permiten compartir únicamente la información necesaria para una solicitud específica, manteniendo ocultos los detalles internos del código, el servidor o la base de datos. Esto añade una capa crítica de seguridad, ya que los dispositivos externos no tienen acceso total al sistema, sino solo a pequeños paquetes de datos autorizados.



## ¿Cómo funciona una API?

El funcionamiento básico de una API sigue el modelo de Cliente y Servidor a través de la infraestructura de Internet, normalmente mediante el protocolo HTTP (sistema de reglas mediante el cual un cliente (como una app o web) y un servidor se comunican). 


IBM lo ejemplifica de manera sencilla a través de los siguientes pasos:

Cliente / App  --- (1) Envía Petición (URI/HTTP) --->  API ---> (2) Llama al programa externo

Cliente / App <--- (4) Entrega Datos en Pantalla <-- Bridge  <--- (3) Responde con la información <--- Servidor Externo



El funcionamiento de una puede entenderse en cuatro pasos básicos:


1. Solicitud: Una aplicación envía una solicitud, especificando qué información o acción necesita.

2. Procesamiento: La API recibe la solicitud y la procesa, validando que los permisos sean correctos.
   
3. Respuesta: La API recupera los datos o ejecuta la acción requerida.
   
4. Devolución: Los datos o resultados son enviados de vuelta a la aplicación solicitante en un formato entendible (como JSON o XML).

Un ejemplo cotidiano es cuando compras en una tienda online y seleccionas "Pagar con PayPal". La tienda no conoce tus claves bancarias; utiliza una API para comunicarse con PayPal, procesar el pago de forma segura y recibir de vuelta la confirmación de que el pago fue exitoso.


<img width="645" height="285" alt="api1" src="https://github.com/user-attachments/assets/63890e96-2b1a-448a-9591-995a404ca794" />

Imagen sacada de: https://outvio.com/es/blog/que-es-una-api/



## Tipos de API -> Quién las usa

Según su Alcance y Accesibilidad. IBM (International Business Machines) clasifica las API principalmente bajo dos criterios: su accesibilidad (casos de uso en la web) y su arquitectura técnica.


| Tipo de API | Descripción Técnica | Caso de Uso Principal |
| :--- | :--- | :--- |
| **API Abiertas (Públicas)** | Son de **acceso público** y cualquier desarrollador puede utilizarlas a través del protocolo HTTP. Tienen puntos de conexión (*endpoints*) y formatos de respuesta definidos abiertamente. | Integrar servicios globales como mapas, datos climáticos o inicios de sesión sociales (Google/Facebook). |
| **API de Socios (Partner APIs)** | Diseñadas para conectar con socios estratégicos de negocio. Se accede a ellas mediante portales específicos, pero requieren un proceso de validación y credenciales de autenticación obligatorias. | Integrar sistemas de pasarelas de pago (Stripe) o empresas de logística con tiendas de comercio electrónico. |
| **API Internas (Privadas)** | Permanecen completamente ocultas para el público general. Las empresas las desarrollan y utilizan internamente para comunicar sus propios sistemas o bases de datos. | Conectar el departamento de inventario con el sistema de ventas de una misma empresa para mejorar la productividad. |
| **API Compuestas** | Combinan múltiples APIs de datos o servicios diferentes. Permiten que un programador haga una única llamada y obtenga información agrupada de varias fuentes a la vez. | Optimizar el rendimiento en arquitecturas de microservicios, reduciendo el tráfico de red en aplicaciones móviles. |


Existen muchos tipos de API: segun du entorno Tecnológico (Dónde operan)

- API web se utilizan para crear aplicaciones web y móviles, y se accede a ellas a través de la web mediante protocolos estándar como HTTP.
  
- API de biblioteca permiten a los programadores acceder a bibliotecas de código que pueden proporcionar una funcionalidad específica a medida que crean nuevas aplicaciones.

 - API del sistema operativo permiten que el software interactúe con un sistema operativo subyacente.
  
- API abiertas (o API públicas) las crean desarrolladores externos y permiten que cualquier persona acceda a un sitio web o una aplicación, y pueda usarlos.
  
- API de partners permiten la comunicación entre los sistemas de las empresas y los partners empresariales que tienen una relación distinta.
  
- API privadas o internas permiten a los usuarios de una empresa transferir datos entre equipos o conectar varias aplicaciones y sistemas internos.
  
- API compuestas combinan varias API de varios servidores u orígenes para crear una conexión unificada a un único sistema.
  
- API de servicios web son interfaces entre los navegadores web y los servidores web.
  
- API de nube permiten que las aplicaciones de nube se comuniquen entre sí.

- API remotas permiten que las aplicaciones que se ejecutan en diferentes equipos interactúen mediante la comunicación remota.



## Protocolos y estilos arquitectónicos:

 `REST` Arquitectura web altamente escalable que transmite datos mediante el protocolo HTTP. Se caracteriza por **no tener estado** (*stateless*), lo que significa que el servidor no almacena datos del cliente entre solicitudes, facilitando conexiones rápidas y ligeras.

 `SOAP` Protocolo estricto que permite compartir datos entre aplicaciones escritas en diferentes lenguajes y entornos. Define reglas exactas sobre cómo empaquetar, enviar y transmitir los mensajes a través de la red.

`RPC` Modelo diseñado para ejecutar código directamente en redes o servidores remotos, simulando una ejecución local.

`GraphQL` Lenguaje de consulta optimizado para conexiones lentas o inestables. Permite al cliente pedir exactamente los datos que necesita usando **un único endpoint**, evitando hacer múltiples solicitudes al servidor.

`Webhooks` Herramientas orientadas a eventos que envían información de forma automática e inmediata en el momento exacto en que ocurre una acción activadora.



## ¿Qué ventajas ofrecen las API?

Para muchas empresas, las API son activos esenciales para el negocio que ayudan a digitalizar los procesos, permitir la automatización, acelerar los flujos de trabajo, conectar personas y aplicaciones, e innovar en nuevos productos y servicios. Las API pueden ayudar a ofrecer experiencias de cliente excepcionales y mejorar la agilidad operativa.



## ¿A qué amenazas se enfrentan las API?

Las APIs son blancos atractivos para los hackers porque actúan como puertas de acceso a datos valiosos. Si carecen de la seguridad adecuada o están obsoletas (heredadas), los atacantes las explotan para robar información confidencial, tumbar servicios (interrupción) o secuestrar sistemas.



## ¿Cómo se empieza a usar una API?

La plataforma de OpenWeather muestra los tres pasos estándar de la industria para trabajar con este recurso:

- Registro y API Key: El desarrollador crea una cuenta y la plataforma le otorga una API Key (una clave o token alfanumérico). Esta clave funciona como una firma digital o contraseña para rastrear quién hace la petición y controlar los límites de consumo.

- Consulta de la documentación: Se revisa el manual técnico para saber exactamente cómo escribir la dirección URI de la consulta.

- Integración: Se programa la llamada dentro del código de la aplicación para automatizar la solicitud de datos.



## Conclusión
Las API son un pilar del desarrollo de software moderno que promueven la conectividad y la innovación. Desde aplicaciones móviles hasta sistemas empresariales, su capacidad para integrar funcionalidades y servicios las hace imprescindibles. Comprender y aprovechar las API no solo mejora la eficiencia del desarrollo, sino que también abre puertas a nuevas oportunidades en el mundo digital. 



## Bibliografia

Instituto Superior Tecnológico Quito Metropolitano [ITSQMET]. (s.f.). ¿Qué es una API y para qué sirve? https://itsqmet.edu.ec/api/

Outvio. (s.f.). ¿Qué es una API y cómo funciona en desarrollo y logística? https://outvio.com/es/blog/que-es-una-api/

OpenWeatherMap. (s.f.). Weather API: Current weather data and forecast. https://openweathermap.org/api

Wikipedia. (2026, 21 de junio). API. https://en.wikipedia.org/wiki/API

Recluit. (s.f.). Historia y evolución de las API. https://recluit.com/historia-y-evolucion-de-las-api/

Akamai. (s.f.). ¿Cómo funcionan las API? Conceptos básicos y seguridad. Recuperado el 21 de junio de 2026, de https://www.akamai.com/es/glossary/how-do-apis-work
