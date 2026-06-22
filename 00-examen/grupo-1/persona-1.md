# persona-1

magdalenabalart

## Investigación textual API
 
Una API, *Application Programming Interface*, es un conjunto de reglas o protocolos que permite que distintas aplicaciones de software se comuniquen entre sí. Funciona como un puente entre programas, ya que permite intercambiar datos, características y funcionalidades sin que una aplicación tenga que conocer cómo está construida la otra por dentro.

> Las API simplifican y aceleran el desarrollo de aplicaciones y software, ya que permiten a los desarrolladores integrar datos, servicios y funcionalidades de otras aplicaciones, en lugar de desarrollarlos desde cero. Las API ofrecen a los propietarios de aplicaciones una forma sencilla y segura de poner los datos y las funciones de la aplicación a disposición de los consumidores internos y externos.

Un ejemplo es la aplicación del clima, la app no necesariamente crea todos los datos meteorológicos por sí sola. Lo que hace es conectarse a otro sistema que tiene esa información y a través de una API, recibe los datos para mostrarlos de una forma más simple. 

El funcionamiento de una API se basa en una solicitud y una respuesta. Una aplicación, que sería el cliente, le pide algo a otro sistema, que sería el servidor. Luego, ese servidor procesa la solicitud y responde con la información necesaria. Para el usuario esto ocurre de manera invisible porque solo ve el resultado final en la pantalla, pero por detrás hay varios sistemas conectándose entre sí. 

Existen diversos tipos de APIs y no todas funcionan de la misma manera. Aunque todas tienen como objetivo permitir la comunicación entre sistemas, cada una utiliza distintos métodos, formatos o reglas para intercambiar información. 

**API SOAP**: funciona de una manera más ordenada y rígida. Se podría comparar con llenar un formulario muy específico: la información debe ir en cierto formato y siguiendo reglas claras. Por eso puede ser más segura y controlada, pero también menos flexible porque no permite tantas variaciones en la forma de enviar los datos.   

| Ejemplo cotidiano | Tipo de API | Explicación |
|---|---|---|
| Outlook / correo institucional | SOAP | Un ejemplo de uso de API SOAP puede verse en servicios como Outlook o correos institucionales. Aunque como usuarios solo vemos la bandeja de entrada, el calendario o los contactos, por detrás pueden existir sistemas que se comunican mediante mensajes estructurados para intercambiar esa información de forma ordenada y segura. |


**APIs RPC**: funcionan como cuando una aplicación le pide a otra que haga una tarea concreta. Por ejemplo, sería como decirle a otro sistema: “calcula esto”, “guarda esta información” o “devuélveme este resultado”. El servidor realiza esa acción y luego entrega una respuesta. 

| Ejemplo cotidiano | Tipo de API | Explicación |
|---|---|---|
| Discord / actividad de juego | RPC | Un ejemplo de API RPC puede verse cuando Discord muestra la actividad de un juego en el perfil del usuario. En este caso, el juego o aplicación envía información a Discord, como el nombre del juego, el estado de la partida o el tiempo de uso. Discord recibe esos datos y los muestra como estado del usuario. Esto ocurre por detrás, por lo que la persona solo ve el resultado final en su perfil. 

**APIs WebSocket**: sirven para mantener una comunicación constante entre dos sistemas. A diferencia de otras APIs, donde una aplicación pregunta y espera una respuesta, WebSocket permite que ambas partes se envíen información en tiempo real. Esto es útil, por ejemplo, en chats, videojuegos en línea, notificaciones o aplicaciones donde los datos deben actualizarse al instante.  

| Ejemplo cotidiano | Tipo de API | Explicación |
|---|---|---|
| Chat en vivo / mensajería online | WebSocket | Un ejemplo de API WebSocket puede verse en chats en vivo o aplicaciones de mensajería. Cuando una persona envía un mensaje, la información viaja desde su dispositivo hacia el servidor del chat, y luego el servidor la envía al dispositivo de la otra persona. Esto permite que los mensajes aparezcan casi al instante, sin tener que actualizar la página constantemente. Por eso WebSocket se usa en sistemas que necesitan comunicación en tiempo real. |

**APIs REST**: son de las más utilizadas actualmente en páginas web y aplicaciones. Funcionan de una manera más simple y flexible: una aplicación solicita información o pide realizar una acción, y el servidor responde. Por ejemplo, una app puede pedir mostrar productos, actualizar un perfil o cargar publicaciones. Por su facilidad de uso, REST es muy común en servicios digitales actuales. 

| Ejemplo cotidiano | Tipo de API | Explicación |
|---|---|---|
| App del clima | REST | Un ejemplo de API REST puede verse en una aplicación del clima. Cuando la persona busca una ciudad, la app envía una solicitud al servidor indicando qué información necesita, por ejemplo el clima de Santiago. Luego, el servidor responde con datos como la temperatura, la humedad o el estado del tiempo. La aplicación recibe esa información y la muestra de forma más simple en la pantalla. |

Desde el código, una API se utiliza realizando una solicitud a una dirección específica, llamada *endpoint*. Esta solicitud puede incluir datos o parámetros, como una ciudad, una fecha o un usuario. Luego, la API procesa esa solicitud y devuelve una respuesta, normalmente en un formato ordenado como JSON (JavaScript Object Notation, es un formato para ordenar datos). En las APIs, JSON es muy usado porque permite que el servidor devuelva información de forma ordenada y que el código pueda leerla fácilmente. Después, la aplicación puede tomar esos datos y mostrarlos de una forma más visual para el usuario. 

1. Escribir la dirección de la API.
2. se escribe la información solicitada, por ejemplo: ciudad=Santiago.
3. El código manda esa solicitud.
4. La API responde con datos.
5. Tu código lee esos datos.
6. Después se decide qué hacer con ellos: mostrarlos, guardarlos, usarlos en una pantalla, etc.

En C++, JSON se entiende como un texto ordenado con datos, pero C++ no lo lee automáticamente como si fuera una variable normal. Primero llega como texto y después el código debe interpretarlo. 

una API puede responder esto:
```
{
  "ciudad": "Santiago",
  "temperatura": 18,
  "estado": "nublado"
} 
```
Pero para C++ eso llega como un string (texto) 
```cpp
string respuesta = "{ \"ciudad\": \"Santiago\", \"temperatura\": 18, \"estado\": \"nublado\" }"; 
```
El problema es que C++ no entiende solo que "temperatura" vale 18. Para poder usar ese dato, hay que convertir o leer el JSON. 
```cpp
int temperatura = 18;

if (temperatura > 25) {
  cout << "Hace calor";
} else {
  cout << "No hace tanto calor";
}
```
JSON es el formato en que la API entrega los datos, y C++ debe leer ese formato para transformar esos datos en variables que pueda usar.

### Endpoint 

Un endpoint es una dirección específica dentro de una API a la que una aplicación envía una solicitud. Si la API es el sistema completo, el endpoint sería el punto exacto al que el código se conecta para pedir una información o realizar una acción determinada. 

Por ejemplo, una API del clima puede tener distintas “puertas” 
```
/clima
/ciudad
/pronostico
/temperatura
```
Cada endpoint sirve para pedir una cosa distinta. 
 
```
https://api.clima.com
```
es la dirección general de la API.
 
```
/clima
```
es el endpoint, porque indica qué información específica se está pidiendo. 

**API** = el sistema completo  
**Endpoint** = la dirección específica dentro de esa API donde hago una solicitud

### Bibliografía
Amazon Web Services. (s.f.). What is an API? AWS.  
Amazon Web Services. (s.f.). SOAP vs REST: Difference Between API Technologies. AWS.  
IBM. (2024). What is an API? IBM Think.  
OpenAI. (2026). ChatGPT [Modelo de lenguaje de gran escala]. https://chat.openai.com/  





