# sesion-04 - lunes 30 marzo 2026

En esta clase instalamos y configuramos el entorno para comunicación inalámbrica. El foco estuvo en lograr que el Arduino mandara y recibiera señales a través de un Broker MQTT (Mosquitto) instalado en la Raspberry Pi. También vimos la base teórica de todo esto con Claude Shannon y cómo la información se transforma en bits para viajar por el "ruido" del aire.

1. **TigerVNC:** Lo instalamos (brew install tiger-vnc) para ver el escritorio de la Raspberry Pi por IP de forma remota.
2. **Comandos sudo:** sudo es "Super User Do". Es peligroso si no sabes qué haces; por ejemplo, sudo rm -rf borra el disco completo. No tocar.
3. Puerto: 1883 es el estándar MQTT.
4. UDP (User Datagram Protocol): Lo vimos como alternativa rápida para streaming o juegos, porque manda paquetes sin verificar conexión (ideal para baja latencia).
5. MQTT: Más estructurado, permite enviar texto, números y links. Una vez subido el código, el dispositivo es autónomo y no necesita el PC.

### Bugs y errores de conexión

* Detección de Bugs: Un bug es cuando algo falla o no debería pasar. En clase nos tiró errores de conexión constantes.
* Solución: Metimos un delay(2000) en el setup para que, si falla, espere 2 segundos y reintente solo hasta conectar.
* Dato técnico: Ojo con confundir ID y Username, no son lo mismo y eso nos trancó un rato.

### Teoría de la Información (Claude Shannon)

Shannon es el padre de la era digital. Él inventó el concepto de BIT (Binary Digit) y definió el modelo de comunicación que estamos usando:

    Fuente: Arduino.
    Transmisor: Chip WiFi.
    Canal: Aire (ondas de radio).
    Ruido: Interferencias (lo que ensucia la señal y hace que salgan signos de interrogación).
    Receptor: Broker/Adafruit.

**Claude Shannon invented the future** 

* **https://people.math.harvard.edu/~ctm/home/text/others/shannon/entropy/entropy.pdf**
<img width="800" height="588" alt="Captura de pantalla 2026-03-30 162936" src="https://github.com/user-attachments/assets/448bc899-d79b-4fbe-8bc5-6c49af8c950a" />
<img width="800" height="565" alt="image" src="https://github.com/user-attachments/assets/fd8d85e5-f090-4a0e-a099-e24f6ce67f9e" />

# **Codigo RecibirArduino**
https://github.com/user-attachments/assets/e2b217d5-daf4-4f3e-91c7-cc4d67c35b1f

# **UNO R4 WiFi Network Examples**
https://docs.arduino.cc/tutorials/uno-r4-wifi/wifi-examples/#wi-fi-udp-send-receive-string
1. Conectarte a internet: Cómo hacer que tu placa use el Wi-Fi de tu casa o de la UDP.
2. Web Server: Cómo crear una página web interna que puedas ver desde tu celular para prender luces, por ejemplo.
3. Network Scan: Cómo hacer que el Arduino busque redes Wi-Fi cerca.

### Bibliografía y referentes 

* Apple. (s.f.). *Acerca de Rosetta*. https://support.apple.com/es-cl/102527

* BBC News Mundo. (s.f.). *Claude Shannon: el padre de la teoría de la información*. https://www.bbc.com/mundo/articles/cn0yxddw9dwo

* Cloudflare. (s.f.). *¿Qué es UDP (User Datagram Protocol)?*. https://www.cloudflare.com/es-es/learning/ddos/glossary/user-datagram-protocol-udp/

* HiveMQ. (s.f.). *HiveMQ*. https://www.hivemq.com/

* MQTT.org. (s.f.). *MQTT: The Standard for IoT Messaging*. https://mqtt.org/

* Mosquitto. (s.f.). *Mosquitto*. https://mosquitto.org/

* TigerVNC. (s.f.). *TigerVNC*. https://tigervnc.org/

Explicando la solemne 1
