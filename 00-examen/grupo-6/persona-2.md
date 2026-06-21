# persona-2

Monserrat-Paredes / https://github.com/Monserrat-Paredes


### criterios individuales

- Investigación textual sobre API.
- Bitácoras junio: evaluación de 4 sesiones (25 mayo, 01 junio, 08 de junio, 15 junio).
- Bitácoras junio (la misma nota que punto anterior).

## Investigación sobre API (Interfaz de Programación de Aplicaciones)

¿Qué es una API?

Una API (por sus siglas en inglés Application Programming Interface , en español Interfaz de Programación de Aplicaciones ) es un conjunto de definiciones, reglas y protocolos que permite la comunicación entre diferentes aplicaciones o softwares. A diferencia de una interfaz de usuario que conecta una persona con un ordenador, una API conecta dos softwares o partes de un software.

En términos simples, una API es como un mensajero que actúa entre un cliente y un servidor: traduce el mensaje y entrega la respuesta.

Analogía del restaurante: Para entenderlo mejor.

El cliente = el usuario/app que hace la solicitud.

El camarero = la API (transmite la orden).

El cocinero = el servidor que procesa y responde con la información.


## Origen

Aunque hoy asociamos las API a las páginas web, el concepto nació en 1968. Los científicos de computación Ira Cotton y Frank Greatorex crearon un sistema para que diferentes programas de software pudieran interactuar dentro de una misma computadora principal. Internet ni siquiera existía tal como lo conocemos.

Aunque hoy asociamos las APIs casi exclusivamente a internet (Web APIs), el concepto es mucho más antiguo:

Años 1960 : Las primeras APIs se usaron como bibliotecas en los sistemas operativos, permitiendo que los programas interactuaran con el sistema.

1988 : RPC (Llamada a procedimiento remoto) desarrollado por SUN Microsystems, primer protocolo que ganó popularidad.

Años 2000 (Revolución Web) : Roy Fielding describe en su tesis (2000) el estilo arquitectónico REST. Las API basadas en la red que utilizan HTTP se convirtieron en el estándar actual




## ¿Qué es una API?

Según la documentación de IBM, una API es un conjunto de reglas, protocolos y especificaciones que permite que diferentes aplicaciones informáticas se comuniquen entre sí para intercambiar datos, características y funcionalidades.

En lugar de crear cada herramienta u origen de datos desde cero, las API permiten a los desarrolladores conectar e integrar sistemas existentes de forma rápida y segura. Actúan como un puente o intermediario invisible para el usuario final, ofreciendo una conexión fluida dentro del software.


## El concepto de "Caja Negra" y Seguridad

Las API permiten compartir únicamente la información necesaria para una solicitud específica, manteniendo ocultos los detalles internos del código, el servidor o la base de datos. Esto añade una capa crítica de seguridad, ya que los dispositivos externos no tienen acceso total al sistema, sino solo a pequeños paquetes de datos autorizados.


## ¿Cómo funciona una API?

El funcionamiento básico de una API sigue el modelo de Cliente y Servidor a través de la infraestructura de Internet, normalmente mediante el protocolo HTTP (sistema de reglas mediante el cual un cliente (como una app o web) y un servidor se comunican). 


IBM lo ejemplifica de manera sencilla a través de los siguientes pasos:

Cliente / App  --- (1) Envía Petición (URI/HTTP) --->  API ---> (2) Llama al programa externo

Cliente / App <--- (4) Entrega Datos en Pantalla <-- Bridge  <--- (3) Responde con la información <--- Servidor Externo


1. La Petición (Request): Una aplicación (el cliente) envía una solicitud de datos a través de una dirección específica (URI). Esta petición incluye un verbo de solicitud (como GET para leer datos o POST para enviar datos) y una cabecera.

2. El Procesamiento: La API toma la solicitud y llama al servidor web o programa externo que contiene la información.

3. La Respuesta (Response): El servidor procesa la orden y envía los datos de vuelta a la API (generalmente organizados en formatos estandarizados y ligeros como JSON o XML).

4. La Entrega: La API transfiere estos datos a la aplicación inicial, que los interpreta y los muestra al usuario en su interfaz.


Un ejemplo cotidiano es cuando compras en una tienda online y seleccionas "Pagar con PayPal". La tienda no conoce tus claves bancarias; utiliza una API para comunicarse con PayPal, procesar el pago de forma segura y recibir de vuelta la confirmación de que el pago fue exitoso.


## Tipos de API

IBM clasifica las API principalmente bajo dos criterios: su accesibilidad (casos de uso en la web) y su arquitectura técnica.

- API Abiertas (o Públicas): Son de código abierto y cualquier desarrollador puede acceder a ellas a través del protocolo HTTP. Tienen puntos de conexión (endpoints) y formatos de respuesta definidos públicamente.

- API de Socios (Partner APIs): Diseñadas para conectar con socios estratégicos de negocio. Se accede a ellas mediante portales específicos de desarrolladores, pero requieren un proceso de validación y credenciales de inicio de sesión específicas.

- API Internas (o Privadas): Permanecen ocultas para el público general. Las empresas las utilizan internamente para comunicar diferentes componentes o departamentos de desarrollo y mejorar la productividad.

- API Compuestas: Combinan múltiples API de datos o servicios diferentes. Permiten que un programador haga una única llamada y obtenga información de varias fuentes a la vez (muy útil en arquitecturas de microservicios).


## Protocolos y estilos arquitectónicos:

- REST (Representational State Transfer): Es el estilo más común en las API web modernas. Utiliza el protocolo HTTP, es ligero y es compatible con múltiples lenguajes de programación y formatos como JSON.

- SOAP (Simple Object Access Protocol): Un protocolo de mensajería rígido y altamente estructurado basado estrictamente en XML, muy utilizado en entornos empresariales que requieren alta seguridad y contratos de datos estrictos.

- RPC (Remote Procedure Call): Protocolos orientados a ejecutar procedimientos o tareas en sistemas remotos como si fuesen locales (pueden basarse en XML o JSON).


## ¿Cómo se empieza a usar una API?

La plataforma de OpenWeather muestra los tres pasos estándar de la industria para trabajar con este recurso:

- Registro y API Key: El desarrollador crea una cuenta y la plataforma le otorga una API Key (una clave o token alfanumérico). Esta clave funciona como una firma digital o contraseña para rastrear quién hace la petición y controlar los límites de consumo.

- Consulta de la documentación: Se revisa el manual técnico para saber exactamente cómo escribir la dirección URI de la consulta.

- Integración: Se programa la llamada dentro del código de la aplicación para automatizar la solicitud de datos.

En resumen, las API son el tejido conectivo de internet. Permiten que un diseñador o programador cree una aplicación que muestre mapas interactivos, procese pagos o dé el pronóstico del tiempo en tiempo real, delegando la complejidad de los datos a servicios expertos externos.


## Bibliografia
