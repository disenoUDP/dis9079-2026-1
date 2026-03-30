# sesion-04 30.03

**Rosetta:** Según gemini, es un emulador de software desarrollado por Apple que permite a las computadoras Mac con procesadores Apple Silicon (chips M1, M2, M3) ejecutar aplicaciones diseñadas originalmente para procesadores Intel. Funciona automáticamente en segundo plano, traduciendo el código durante la primera ejecución para garantizar la compatibilidad.

**HiveMQ**: Según Gemini, es una plataforma de mensajería MQTT diseñada para el Internet de las Cosas (IoT) empresarial, permitiendo la comunicación rápida, confiable y segura entre dispositivos y aplicaciones. Funciona como un "broker" de mensajes que gestiona, filtra y distribuye datos en tiempo real a gran escala, ideal para proyectos industriales y de misión crítica. 

Wifi es como una carretera, le puedes poner internet, tambien puedes no ponerle ;).

Ya no tenemos que tener una IP distinta cada uno, sino que será siempre la misma IP.

**sudo:** Super usuario hacer _**(no usar)**_

## Arduino

Modificar desde linea #51 con nuestrso grupos.

Loop: Enviar mensaje y que dirá

### Claude Shannon

El matemático e informático estadounidense que concibió y sentó las bases de la teoría de la información. Sus teorías sentaron las bases de las redes de comunicaciones electrónicas que hoy conectan el mundo. Claude Elwood Shannon nació el 30 de abril de 1916 en Petoskey, Michigan.
<https://people.math.harvard.edu/~ctm/home/text/others/shannon/entropy/entropy.pdf>

![shannon](./imagenes/shannon.webp)
![osilayers](./imagenes/osi.webp)

### En clases

<https://docs.arduino.cc/tutorials/uno-r4-wifi/wifi-examples/#wi-fi-udp-send-receive-string>
En este link probamos distintos archivos: 

1. **Wi-Fi® Chat Server**: Cada vez que se tecleaba en el serial monitor, el LED se prendía.
2. **Simple Webserver**: Con este ejemplo se podía prender y apagar el led del arduino clickeando los botones en la web.

**UDP (User Datagram Protocol)**: Sobre Wi-Fi es un protocolo de transporte rápido y sin conexión, ideal para streaming, juegos en línea y VoIP. Envía paquetes (datagramas) directamente sin establecer sesión ni verificar recepción, priorizando la velocidad y baja latencia sobre la fiabilidad. Se usa cuando la rapidez es crítica.

#### Diferencias de protocolos

MQTT es un protocolo de mensajería ligero (publicación/suscripción) ideal para IoT que funciona sobre TCP, garantizando la entrega de datos, alta fiabilidad y orden de mensajes. En cambio, UDP es un protocolo de transporte sin conexión que prioriza la velocidad máxima, sin garantizar la entrega ni el orden, ideal para streaming en tiempo real.

Te odiamos MQTT

![teodiamos](./imagenes/teodiamos.jpeg)
