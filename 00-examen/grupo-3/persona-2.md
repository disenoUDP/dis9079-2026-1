# persona-2 DebSkar

## Investigación APIs

### ¿Qué es una API?

Una API (Application Programming Interface o Interfaz de Programación de Aplicaciones) es un conjunto de reglas y protocolos que permite a distintas aplicaciones informáticas comunicarse entre sí para intercambiar datos, características y funcionalidades.
La interfaz funciona como un contrato de servicio entre dos aplicaciones: define cómo deben comunicarse mediante solicitudes y respuestas, sin necesidad de que cada parte conozca los detalles internos de la otra. Esto contribuye a la seguridad del sistema, ya que solo se comparte la información necesaria.

### ¿Cómo funcionan las APIs?

La arquitectura de las APIs se explica en términos de cliente y servidor. La aplicación que envía la solicitud se denomina cliente, y la que provee la respuesta es el servidor. La API actúa como el puente que establece y gestiona la conexión entre ambos.

El proceso de comunicación sigue estos pasos:

* El cliente realiza una llamada a la API enviando una solicitud (con un verbo, una cabecera y, en ocasiones, un cuerpo de datos) a través de un URI.
* La API recibe la solicitud válida y la transmite al servidor o programa externo correspondiente.
* El servidor procesa la solicitud y genera una respuesta.
* La API devuelve los datos de respuesta al cliente solicitante.
Todo este intercambio ocurre de forma invisible para el usuario final.

> Por ejemplo, al hacer clic en "Pagar con PayPal" en una tienda en línea, se desencadena una llamada a la API que conecta el sitio web con el sistema de pago externo, todo sin que el usuario abandone la página.

### Tipos de APIs

Las APIs se clasifican de dos maneras: por su arquitectura (protocolo de comunicación) y por su ámbito de uso (quién puede acceder a ellas).

#### Por arquitectura

* SOAP (Simple Object Access Protocol): 
Protocolo basado en mensajes XML. Es menos flexible y fue más popular en el pasado. Ofrece verificación de tipos estricta, siendo preferido en entornos con altos requisitos de integridad de datos.

* RPC *(Remote Procedure Call): El cliente ejecuta un procedimiento en el servidor y recibe el resultado. Existen variantes como XML-RPC (usa XML, más simple y ligero) y JSON-RPC (usa JSON, compatible con cualquier lenguaje de programación).

* WebSocket *: Permite comunicación bidireccional y continua entre cliente y servidor. No requiere establecer una nueva conexión en cada intercambio, siendo ideal para aplicaciones en tiempo real.

* REST * (Representational State Transfer): El tipo más popular y flexible actualmente. Utiliza HTTP con métodos como GET, PUT, DELETE. Es sin estado (el servidor no guarda datos del cliente entre solicitudes) y soporta múltiples formatos (JSON, XML, texto, HTML, YAML), lo que lo hace ideal para APIs públicas.

* GraphQL *: Lenguaje de consulta desarrollado por Facebook (2012, código abierto desde 2015). Permite obtener exactamente los datos necesarios en una sola solicitud, resolviendo problemas de recuperación excesiva o insuficiente propios de REST.

#### Por ámbito de uso

* APIs privadas (internas) *: Solo se utilizan dentro de una empresa para conectar sistemas y equipos internos. No están disponibles para usuarios externos.

* APIs públicas (abiertas) *: Disponibles para cualquier desarrollador. Pueden ser gratuitas o de pago, con o sin proceso de autorización.

* APIs de socios *: Accesibles únicamente por desarrolladores externos autorizados, generalmente para facilitar alianzas estratégicas entre empresas.
APIs compuestas: Combinan dos o más APIs para responder a requisitos complejos del sistema. Son especialmente útiles en arquitecturas de microservicios.

### ¿Cómo se crea una API?

El diseño de una API de calidad requiere seguir un proceso ordenado de cinco etapas:

1 Planificación: Se definen los casos de uso y se elige una especificación estándar (como OpenAPI). Es clave anticipar los escenarios de uso y garantizar que la API cumpla con los estándares actuales de desarrollo.

2 Creación del prototipo: Los diseñadores construyen un prototipo utilizando código reutilizable. Una vez probado, los desarrolladores lo personalizan según las necesidades internas.

3 Pruebas: Al igual que cualquier software, la API debe ser probada para detectar errores, defectos y vulnerabilidades. Se utilizan herramientas específicas para reforzar la resistencia frente a ciberataques.

4 Documentación: La documentación actúa como un manual técnico que guía a otros desarrolladores sobre cómo utilizar la API. Una documentación clara y completa es determinante para el éxito y adopción de la API.

5 Comercialización (opcional): Existen mercados de APIs donde es posible publicar, compartir o monetizar una API. Esto permite a los desarrolladores ampliar el alcance y el impacto de su trabajo.

### Beneficios de las APIs

Las APIs ofrecen ventajas significativas 
tanto para desarrolladores como para organizaciones:

Integración: Permiten conectar nuevas aplicaciones con sistemas existentes, eliminando la necesidad de desarrollar funcionalidades desde cero y acelerando los tiempos de desarrollo.

Innovación: Facilitan la implementación rápida de nuevos servicios y funcionalidades sin reescribir el código completo, permitiendo a las empresas adaptarse ágilmente a cambios del mercado.

Ampliación multiplataforma: Hacen posible que una misma funcionalidad (como la integración de mapas) esté disponible en web, Android, iOS y otras plataformas simultáneamente.

Facilidad de mantenimiento: Al actuar como puerta de enlace entre sistemas, los cambios internos de un sistema no afectan al otro. Esto reduce el impacto de modificaciones futuras en el código.

Colaboración mejorada: Permiten integrar cientos de aplicaciones que de otro modo estarían desconectadas, automatizando flujos de trabajo y eliminando silos de información.

Monetización de datos: Las empresas pueden ofrecer acceso a sus datos o funcionalidades mediante APIs de pago, creando nuevas fuentes de ingresos.

Seguridad: Al no exponer completamente los datos del sistema, solo comparten los paquetes de información necesarios para cada solicitud específica.

### A Considerar

Si bien las APIs presentan ventajas, también existen aspectos a considerar al trabajar con ellas:

Dependencia de terceros: Al integrar APIs externas, el funcionamiento de una aplicación queda a la disponibilidad y estabilidad del proveedor de la API.

Seguridad y privacidad: Las APIs mal configuradas pueden convertirse en puntos vulnerables. Es importante implementar autenticación y pruebas de seguridad adecuadas.

Complejidad en el mantenimiento: Cuando una API externa cambia su versión o deja de funcionar, las aplicaciones que dependen de ella requieren actualizaciones. 

Costos: Muchas APIs de uso intensivo son de pago. El consumo elevado puede generar costos significativos, especialmente en aplicaciones a escala.

Limitaciones de rendimiento: Las APIs REST pueden presentar problemas de recuperación excesiva o insuficiente de datos.

Las APIs son un componente fundamental de la arquitectura del software moderno. Su capacidad para conectar sistemas, acelerar el desarrollo y  la innovación las convierte en una herramienta indispensable en aplicaciones personales y también empresariales.  

#### Fuentes
