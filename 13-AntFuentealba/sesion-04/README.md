# sesion-04

lunes 30 marzo 2026

## Apuntes

- El WiFi funciona como una “carretera” por donde circulan los datos. Puede tener o no acceso a internet, pero permite la comunicación entre dispositivos dentro de una red.
- La red puede compartir una misma IP, lo que facilita la conexión entre dispositivos sin configuraciones individuales complejas.
- La tecnología 5G ofrece alta velocidad de transmisión, pero tiene un alcance limitado.



## Comandos 

- `sudo`  
  Permite ejecutar comandos como superusuario (administrador).  
  Es potente y peligroso, ya que puede modificar o eliminar archivos del sistema.

- `rm -rf`  
  Comando que elimina archivos o directorios de forma permanente.  
  Mal utilizado puede borrar todo el sistema.



## Acceso remoto 

### TigerVNC
Sistema que permite visualizar y controlar gráficamente una Raspberry Pi desde otro computador.

Instalación:
```bash
brew install tigervnc
```



### Rosetta
Emulador de Apple que permite ejecutar aplicaciones diseñadas para procesadores Intel en equipos con Apple Silicon (M1, M2, M3). Funciona traduciendo el código automáticamente.



## Redes 

### Modelo OSI
Modelo conceptual que divide la comunicación en distintas capas, permitiendo entender cómo viajan los datos a través de una red.


### Puertos
- Puerto **1883**: estándar utilizado por MQTT para la comunicación.



## Protocolos 

### MQTT (Message Queuing Telemetry Transport)
- Protocolo ligero de mensajería  
- Funciona sobre TCP  
- Modelo **publish/subscribe**  
- Usa un **broker** (intermediario)  

Características:
- Alta fiabilidad  
- Orden en los mensajes  
- Ideal para IoT  

En este contexto:
- El broker se ejecuta en la Raspberry Pi (ej: Mosquitto)
- Dispositivos (Arduino, computador, etc.) se conectan al broker


### UDP (User Datagram Protocol)
- Protocolo de transporte rápido y sin conexión  
- No verifica si los datos llegan correctamente  
- Prioriza velocidad y baja latencia  

Usos:
- Streaming  
- Juegos online  
- Comunicación en tiempo real  


### Diferencia MQTT vs UDP

| MQTT | UDP |
|------|-----|
| Basado en conexión (TCP) | Sin conexión |
| Alta fiabilidad | No garantiza entrega |
| Orden de mensajes | No asegura orden |
| Más lento | Muy rápido |
| Ideal para IoT | Ideal para tiempo real |


## Plataformas

### HiveMQ
Plataforma de mensajería basada en MQTT orientada a IoT a gran escala.

Permite:
- Comunicación entre múltiples dispositivos  
- Gestión de datos en tiempo real  
- Alta seguridad y escalabilidad  



## Arduino 

### Requisitos para conectar dispositivos

Para conectar un Arduino a otro sistema (como una Raspberry Pi):

1. Conexión a WiFi  
2. Acceso a la IP de la red  
3. Uso de un broker MQTT (ej: Mosquitto)  
4. Configuración de envío/recepción de mensajes  

Ejemplo:
- Arduino → WiFi → Router → Broker → Otros dispositivos  



### Ejemplos trabajados en clase

- **WiFi Chat Server**  
  Permite enviar mensajes desde el monitor serial y activar un LED.

- **Simple Webserver**  
  Permite controlar el Arduino desde el navegador (encender/apagar LED).

- **UDP Send/Receive**  
  Comunicación directa entre dispositivos usando UDP.



## Funcionamiento

- `loop()` en Arduino:  
  Se ejecuta continuamente y puede usarse para enviar datos o escuchar mensajes.

- Los dispositivos pueden:
  - Publicar información  
  - Suscribirse a canales  
  - Reaccionar a eventos en tiempo real  



## IoT 

- Los dispositivos (Arduino, Raspberry Pi, computador) forman parte de un sistema conectado.
- Se pueden enviar datos desde sensores hacia otros dispositivos que reaccionan (ej: prender luces, mostrar datos, etc.).





## Ideas clave

- La comunicación entre dispositivos depende de protocolos  
- MQTT es confiable; UDP es rápido  
- El broker es el centro del sistema MQTT  
- Arduino puede enviar y recibir datos en red  
- El WiFi permite comunicación local, incluso sin internet  
- El uso de comandos de sistema requiere precaución  

## Ejemplo de código (OLED SSD1306)

```cpp
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setup() {
  Wire.begin();

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    while (true);
  }

  display.clearDisplay();

  // Dibuja un punto en la parte inferior
  display.fillCircle(64, 55, 4, SSD1306_WHITE);

  display.display();
}

void loop() {
}
```


