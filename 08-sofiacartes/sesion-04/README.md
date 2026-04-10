# sesion-04

lunes 30 marzo 2026

## Apuntes

- 5g muy rapida pero bajo alcance

instalar tiger vnc

sudo es una palabra peligrosa super user admin 

rm rf remove  -> remueve todo el disco duro del computador

port (puerto) 1883 es el estandar que ocurre mqtt

- TigerVNC: sistema de escritorio gráfico para visualizar la raspberry pi
- brew install tiger VNC
- 5g es rápida pero de bajo alcance
- Sudo es una palabra peligrosa, usar admin
- el broker siempre vive en el raspberry pi -> MQTT
- arduino 01 -> clave encriptada -> dis0979
- 52 -> arduino01
- Model OSI -> capas de comunicación
- sobre wifi se usa la estrategia mqtt
- UDP `User Datagram Protocol`: Mensajes entre canales. Es un protocolo de transporte rápido y sin conexión, ideal para streaming, juegos en línea y VoIP. Envía paquetes (datagramas) directamente sin establecer sesión ni verificar recepción, priorizando la velocidad y baja latencia sobre la fiabilidad. Se usa cuando la rapidez es crítica. [UDP](https://en.wikipedia.org/wiki/User_Datagram_Protocol)
- sudo: Super usuario hacer (no usar) peligroso.

### Claude Shannon

Fue un matemático, ingeniero eléctrico y criptógrafo estadounidense, conocido como el padre de la teoría de la información. *teoría está relacionada con las leyes matemáticas que rigen la transmisión y el procesamiento de la información y se ocupa de la medición de la información y de la representación de la misma, así como también de la capacidad de los sistemas de comunicación para transmitir y procesar información.*

#### ¿Qué se necesita para conectarse a otro arduino?

- arduino se conecta al wifi -> arduino conectado al router
-  IP de wifi
- tener el broker en mosquitto
- UDP `User Datagram Protocol`
- `Simple webserver`: En arduino docs. [SIMPLE WEBSERVER WIFI](https://docs.arduino.cc/retired/library-examples/wifi-library/SimpleWebServerWiFi/)
- `Rosetta:` Es un emulador de software desarrollado por Apple que permite a las computadoras Mac con procesadores Apple Silicon (chips M1, M2, M3) ejecutar aplicaciones diseñadas originalmente para procesadores Intel. Funciona automáticamente en segundo plano, traduciendo el código durante la primera ejecución para garantizar la compatibilidad.
- `HiveMQ:` Es una plataforma de mensajería MQTT diseñada para el Internet de las Cosas (IoT) empresarial, permitiendo la comunicación rápida, confiable y segura entre dispositivos y aplicaciones. Funciona como un `broker` de mensajes que gestiona, filtra y distribuye datos en tiempo real a gran escala, ideal para proyectos industriales y de misión crítica.

*Wifi es como una carretera, le puedes poner internet, tambien puedes no ponerle*
