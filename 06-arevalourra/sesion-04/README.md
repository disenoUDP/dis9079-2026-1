# sesion-04

lunes 30 marzo 2026

tiger VNC -> Permite renderizar el escritorio

192.168.0.100  -> ID Computador Raspberry Pi


## Escritorio Raspi


sudo -> super user / admin do

comando [sudo rm rf] -> destruye computador

mqtt -> topic

clave -> dis9079


Se está trabajando con un sistema que se conecta a WiFi y luego a un broker (MQTT) para enviar mensajes.

El foco está en:

-manejo de errores de conexión

-reintentos automáticos

-envío de mensajes entre dispositivos


Aparecen errores como:

“falló la conexión” / códigos tipo: 2, 22, etc.


A veces el sistema:

no se conecta al primer intento pero sí lo hace en el segundo o tercer intento

La conexión puede ser inestable o lenta, pero termina funcionando.
Es normal que los dispositivos sean lentos para conectarse.

En vez de mostrar error definitivo se implementa un mensaje tipo “en 2 segundos más vuelvo a intentar” (delay 2000)

Se crea una lógica de reintento automático de conexión


## Flujo de conexión del sistema

- Se intenta conectar al WiFi
  
- Luego busca la Raspberry Pi

- Finalmente se conecta al broker (Mosquitto/MQTT)}
  
Puede fallar al inicio, pero vuelve a intentar y cuando logra conectarse -> celebra


**Envío de mensajes**

El sistema envía mensajes a un tópico (MQTT), por ejemplo:

"hola 0"
"hola 1"
"hola 2"

Los mensajes pueden ser recibidos por cualquier dispositivo conectado al mismo broker


**Se puede enviar:**

-texto (mensajes)

-números

-links

-datos en general

Limitaciones:

No es ideal para streaming de audio en tiempo real
Sí se pueden enviar pequeños paquetes de datos


**El código se guarda dentro del dispositivo, no necesita estar conectado al computador para funcionar**

Se puede subir el código una vez, desconectar, usarlo en otro computador y el dispositivo sigue funcionando igual


**“bug” = error o falla en el sistema**

Un bug es cuando “algo no debería ser así, pero está pasando”.


## Confusión entre conceptos:

ID y Username (usuario)

Se estaban usando como si fueran lo mismo -> Pero NO son lo mismo


UDP -> User Datagram Protocol











