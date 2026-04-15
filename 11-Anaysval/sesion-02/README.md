# sesion-02

lunes 16 marzo 2026

Grupo: Benjamín Álvarez, Anays Cornejo

### Apuntes

### Arduino

Arduino es una placa electrónica que ejecuta programas para controlar componentes como sensores, luces o motores.

El código se escribe en el computador, se compila y luego se envía a la placa, donde se ejecuta como instrucciones que el microcontrolador puede interpretar.

```cpp
void setup() {
  // se ejecuta una vez al iniciar
}

void loop() {
  // se repite constantemente
}
```

### Instalación

Para trabajar con Arduino se usa el Arduino IDE.

Se necesita:

- Instalar la placa Arduino UNO R4 desde Boards Manager
- Agregar bibliotecas desde Library Manager (por ejemplo MQTT o herramientas gráficas)
- Usar herramientas de terminal como Homebrew mediante comandos Bash
  
### Arduino UNO R4 WiFi

Es una versión de Arduino con conexión WiFi integrada.

Permite:

- Enviar datos a través de red
- Usar la pantalla LED incorporada
- Comunicarse con otros dispositivos conectados a la misma red
  
### MQTT

MQTT es un protocolo liviano que permite que dispositivos intercambien mensajes.

Características:

- Funciona con modelo publish/subscribe
- Usa un broker como intermediario
- Trabaja sobre redes TCP/IP
- Organiza la comunicación en topics (canales de mensajes)
  
### Broker (Mosquitto)

El broker es el servidor que recibe los mensajes y los distribuye a los dispositivos correctos.

- Puerto común: 1883
- Conecta quienes envían datos con quienes los reciben
- Un ejemplo de broker es Mosquitto
  
### Conexión WiFi

Las credenciales se guardan en un archivo llamado:

```cpp
#define SECRET_SSID "nombre_wifi"
#define SECRET_PASS "clave_wifi"
```

Después el Arduino:

- Se conecta a la red WiFi
- Se conecta al broker MQTT
- Envía y recibe mensajes usando topics

### Ejemplo en clase

Se usaron bibliotecas como:

- ArduinoGraphics
- Arduino_LED_Matrix

Esto permitió mostrar texto en movimiento en la pantalla LED del Arduino UNO R4 WiFi.

### Open Source

Es un modelo donde el código o el hardware puede ser usado, modificado y compartido libremente.

OSHWA certifica proyectos de hardware abierto.

### SemVer (versionamiento)

Sistema para organizar versiones de software:

- Mayor → cambios grandes que rompen compatibilidad
- Menor → nuevas funciones compatibles
- Parche → correcciones pequeñas
  
### Herramientas

- Homebrew → instala programas desde la terminal
- Bash → lenguaje de comandos del sistema
- OSC → protocolo usado para comunicación en tiempo real en sistemas interactivos

### Enlaces

<https://mosquitto.org/documentation/authentication-methods/>
