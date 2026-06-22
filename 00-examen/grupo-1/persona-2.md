# persona-2

Jesús Miranda / https://github.com/jesumirandaa 

# Investigación individual: APIs

---

## ¿Qué es una API?

API significa **Application Programming Interface** o **Interfaz de Programación de Aplicaciones**.

Una API es un conjunto de reglas y protocolos que permite que diferentes sistemas, aplicaciones o dispositivos puedan comunicarse entre sí e intercambiar información.

Su función principal es actuar como un puente entre tecnologías, permitiendo que un sistema pueda utilizar datos o funciones de otro sin necesidad de conocer cómo funciona internamente.

Esto facilita la creación de proyectos porque permite conectar diferentes herramientas y servicios sin tener que desarrollar cada parte desde cero.

- Un ejemplo cotidiano sería una aplicación del clima. Esta aplicación no necesariamente obtiene los datos meteorológicos por sí misma, sino que puede conectarse a un servicio externo mediante una API. De esta manera solicita la información necesaria y luego muestra los resultados de una forma más simple para el usuario.

---

## ¿Cómo funciona una API?

La comunicación mediante una API funciona principalmente mediante un sistema de **solicitud y respuesta**.

En este proceso participan diferentes elementos:

| Elemento | Función |
|---|---|
| Sistema solicitante | Dispositivo, aplicación o software que pide información o envía datos |
| API | Intermediario que organiza la comunicación entre sistemas |
| Sistema proveedor | Servicio o servidor que procesa la información y entrega una respuesta |

El proceso ocurre de la siguiente manera:

1. Un dispositivo o aplicación realiza una solicitud.
2. La API recibe y organiza esa solicitud.
3. El sistema proveedor procesa la información.
4. La API devuelve una respuesta.
5. El sistema solicitante utiliza esos datos para mostrar información o realizar una acción.

Ejemplo de comunicación:

| Elemento | Función dentro de la comunicación |
|---|---|
| Dispositivo / Aplicación | Sistema que inicia la comunicación, enviando una solicitud o datos |
| API | Puente o intermediario que recibe la solicitud y permite la comunicación entre sistemas |
| Servidor / Servicio | Sistema que procesa la información solicitada y genera una respuesta |
| Respuesta con datos | Información que vuelve al dispositivo o aplicación para ser utilizada |



La comunicación ocurre rápidamente y normalmente no es visible para el usuario final.

---

## Solicitudes HTTP dentro de una API

Muchas APIs utilizan el protocolo **HTTP** para comunicarse entre sistemas.

HTTP permite enviar solicitudes y recibir respuestas dependiendo de la acción que se quiere realizar.

| Método | Función |
|---|---|
| GET | Solicitar información |
| POST | Enviar información nueva |
| PUT | Actualizar información existente |
| DELETE | Eliminar información |

Ejemplo:

```http
GET /temperatura
```

Esta solicitud indica que un sistema quiere obtener el dato actual de temperatura desde otro servicio.

---

## Endpoint

Un **endpoint** es una dirección específica dentro de una API donde se realiza una solicitud.

Si una API fuera un sistema completo, el endpoint sería un punto específico que permite acceder a una función determinada.

Ejemplo:

API general:

```text
https://api.clima.com
```

Endpoint:

```text
/temperatura
```

Dirección completa:

```text
https://api.clima.com/temperatura
```

El endpoint indica exactamente qué información se quiere obtener o qué acción se quiere realizar.

---

## Formato JSON

Las APIs necesitan entregar la información de una manera ordenada para que otros sistemas puedan interpretarla.

Uno de los formatos más utilizados es **JSON**:

**JavaScript Object Notation**

JSON organiza datos utilizando una estructura simple de elementos y valores.

Ejemplo:

```json
{
  "ciudad": "Santiago",
  "temperatura": 18,
  "estado": "nublado"
}
```

Esta información puede ser recibida por distintos dispositivos o aplicaciones para mostrarla, almacenarla o utilizarla dentro de un proyecto.

---

## Tipos de APIs

Existen distintos tipos de APIs dependiendo de su forma de funcionamiento y del objetivo que cumplen.

---

## API REST

Las APIs REST son unas de las más utilizadas actualmente.

Funcionan mediante solicitudes HTTP y permiten que distintos sistemas puedan intercambiar información de una forma flexible.

Ejemplo:

```http
GET /productos
```

Una aplicación podría solicitar información y recibir datos como:

- Nombre
- Descripción
- Precio

---

## API SOAP

SOAP es un tipo de API que utiliza una estructura más rígida y definida.

La información debe enviarse siguiendo reglas específicas, por lo que suele utilizarse en sistemas donde se requiere mayor seguridad y control.

Ejemplos:

- Sistemas empresariales
- Plataformas financieras
- Servicios internos

---

## API WebSocket

Las APIs WebSocket permiten mantener una comunicación constante entre dos sistemas.

A diferencia de una API tradicional, donde un sistema solicita información y espera una respuesta, WebSocket permite que ambos lados puedan intercambiar información continuamente.

Se utiliza en:

- Chats
- Videojuegos online
- Transmisiones en tiempo real
- Notificaciones instantáneas

---

## API RPC

Las APIs RPC (**Remote Procedure Call**) permiten que un sistema solicite que otro sistema ejecute una acción específica.

Funciona como una comunicación donde un dispositivo puede pedir:

> "Realiza esta tarea y devuelve el resultado"

Ejemplos:

- Ejecutar una función
- Calcular información
- Enviar una acción a otro sistema

---

# APIs y dispositivos físicos

Las APIs también son importantes dentro de proyectos relacionados con electrónica e Internet de las Cosas (**IoT**).

Permiten que dispositivos físicos puedan comunicarse con plataformas digitales o con otros dispositivos.

Ejemplo:

| Etapa | Función dentro del sistema |
|---|---|
| Sensor | Captura información del entorno físico |
| Microcontrolador | Procesa los datos recibidos y prepara la información para enviarla |
| API | Permite conectar el dispositivo con otros sistemas o servicios |
| Servidor | Recibe, procesa o almacena los datos enviados |
| Otro dispositivo | Utiliza la información recibida para mostrar datos o ejecutar una acción |


## Bibliografía

- Amazon Web Services. (s.f.). *What is an API?*

- IBM. (2024). *What is an API?*

- Mozilla Developer Network. (s.f.). *HTTP Methods and APIs*
