# persona-3

ccarlabelenn

## ¿Qué es una API y cómo funciona? 

Una API (Application Programming Interface o Interfaz de Programación de Aplicaciones) es un conjunto de reglas y protocolos que permite que dos sistemas o aplicaciones se comuniquen entre sí. En términos más simples, una API actúa como intermediario, recibe una solicitud, la procesa y devuelve una respuesta, sin necesitar saber qué ocurre internamente en el sistema al que se está accediendo.

Una forma simple que me ayudó a enternderlo es con la metáfora del mesero en un restaurante: tú haces un pedido (vendrías siendo la aplicación), el mesero (este sería la API) lo lleva a la cocina (este el servidor) y vuelve con tu plato. Tú nunca entras a la cocina ni necesitas saber cómo se preparó, solo recibes el resultado.

Las APIs funcionan principalmente mediante solicitudes y respuestas estructuradas. Una aplicación envía una solicitud HTTP a una URL específica llamada endpoint, indicando qué quiere hacer (obtener datos, enviar información, actualizar o eliminar algo). El servidor procesa esa solicitud y devuelve una respuesta, generalmente en formato JSON o XML, que la aplicación puede interpretar y usar.

**Tipos de API y aplicaciones**

Existen distintos tipos de APIs según su uso y nivel de acceso. Las APIs públicas están disponibles para cualquier desarrollador y suelen utilizarse para integrar servicios externos, como mapas, clima o redes sociales. Las APIs privadas son utilizadas dentro de una organización para conectar sistemas internos. También existen APIs de socios, que permiten el acceso únicamente a usuarios autorizados.
La mayoría de las APIs modernas funcionan mediante el protocolo HTTP y utilizan métodos específicos para interactuar con los datos. Los más comunes son:

+ **GET**: solicita información al servidor.
+ **POST**: envía nueva información.
+ **PUT**: actualiza información existente.
+ **DELETE**: elimina información.

Las respuestas de una API suelen entregarse en formato JSON (JavaScript Object Notation), un formato ligero y fácil de interpretar tanto por personas como por aplicaciones. Gracias a esto, distintos dispositivos y programas pueden intercambiar información de manera eficiente.

**Ventajas de utilizar APIs**

Las APIs permiten reutilizar servicios ya existentes, reduciendo tiempos de desarrollo y facilitando la integración entre diferentes plataformas. Además, hacen posible que dispositivos ubicados en distintos lugares compartan información en tiempo real, como ocurrió en este proyecto mediante Adafruit IO. Su uso es fundamental en aplicaciones de Internet de las Cosas (IoT), donde múltiples dispositivos necesitan intercambiar datos de forma constante y segura.


