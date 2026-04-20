# sesion-04

lunes 30 marzo 2026

## Apuntes en clases

La comunicación entre dispositivos se realiza a través de redes WiFi que permiten transmitir datos sin conexión física

+ 2.4 GHz: mayor alcance, menor velocidad
+ 5 GHz: mayor velocidad, menor alcance

Para proyectos con varios dispositivos es más estable utilizar un router dedicado

Cada dispositivo tiene una dirección IP que lo identifica dentro de la red. En este sistema la Raspberry Pi actúa como nodo central con una IP fija

## MQTT y estructura de comunicación

Se utiliza MQTT como protocolo de intercambio de datos. Funciona mediante un sistema de publicación y suscripción donde los mensajes pasan por un broker generalmente implementado con Mosquitto

Elementos principales

+ Broker
+ Puerto 1883
+ Topic compartido
+ Credenciales de acceso

+ Todos los dispositivos deben conectarse al mismo topic para comunicarse

La comunicación se puede entender a partir del modelo OSI y del uso de protocolos como UDP, que prioriza la velocidad por sobre la verificación de datos

Estos sistemas se basan en los principios de Claude Shannon fundamentales para la transmisión de información en redes

## Para interactuar con la Raspberry Pi

+ SSH (acceso por terminal)
+ TigerVNC (interfaz gráfica remota)

## Configuración y código

En Arduino, la conexión se organiza en:

+ `setup()`: conexión a WiFi
+ `loop()`: envío o recepción de mensajes

Parámetros necesarios:

* SSID y contraseña
* IP del broker
* puerto 1883
* topic común
