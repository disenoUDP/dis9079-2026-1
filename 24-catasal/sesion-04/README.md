# sesion-04

lunes 30 marzo 2026
descargar mqtt
enviar y resibir mensajes con el arduino
proxima clase avanzar en la solemne

## mqtt

El protocolo MQTT (Message Queuing Telemetry Transport) es un sistema de comunicación muy ligero utilizado para enviar y recibir mensajes entre dispositivos conectados a internet. En proyectos con Arduino, MQTT permite que placas como Arduino envíen señal a tiempo real.

Al enviar una señal a Adafruit significa que el Arduino envía información a la plataforma en línea Adafruit IO utilizando internet.

Esto se realiza normalmente mediante el protocolo MQTT, donde el dispositivo publica datos en un feed específico. Por ejemplo, al presionar un botón conectado al Arduino, este puede enviar el valor “1” a Adafruit IO para indicar que una acción fue activada.

 Al intercambiar información en tiempo real 
MQTT es muy útil en automatización y proyectos interactivos porque permite conectar múltiples dispositivos entre sí de manera sencilla. Por ejemplo, un Arduino puede enviar datos a una aplicación móvil, mientras otro Arduino recibe instrucciones desde internet para controlar luces o sensores. Gracias a su rapidez y bajo consumo de datos, MQTT se ha convertido en una de las tecnologías más utilizadas en sistemas inteligentes, domótica y monitoreo remoto.