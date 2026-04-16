# sesion-04

lunes 30 marzo 2026

En esta clase se vio cómo conectar dispositivos (Arduino, Raspberry Pi, computador) usando WiFi y protocolos.

Los dispositivos se comunican a través de una red y un intermediario:

Arduino → WiFi → Router → Broker → otros dispositivos

### Claude Shannon

La comunicación entre dispositivos se basa en ideas de Claude Shannon, quien desarrolló la teoría de la información.

Él explicó cómo los datos se pueden transmitir, codificar y recibir entre distintos sistemas sin perder información.

Esto es clave hoy en tecnología, porque permite que dispositivos como Arduino y Raspberry se comuniquen a través de redes (como WiFi) y protocolos como MQTT.

 ![foto](./imagenes/teoria.png)

 ---

### WiFi

- Medio por donde viajan los datos en la red
- Puede existir sin internet
- Mejor usar router que compartir internet desde el celular

Tipos:

- 2.4 GHz → mayor alcance, menor velocidad  
- 5 GHz → mayor velocidad, menor alcance  

### Raspberry Pi

- Punto central del sistema
- Tiene IP fija
- Puede actuar como broker
- Acceso remoto con SSH o TigerVNC

### MQTT

- Protocolo de mensajería
- Modelo publish/subscribe
- Usa broker (ej: Mosquitto)
- Puerto 1883

### UDP

- Muy rápido
- No asegura entrega ni orden

### Herramientas

### HiveMQ

- Plataforma basada en MQTT
- Permite conectar muchos dispositivos
- Pensado para sistemas grandes

### Rosetta

- Permite usar programas hechos para Intel en Mac con Apple Silicon
- Traduce el código automáticamente

### Acceso remoto

- SSH → control por terminal
- TigerVNC → acceso gráfico

### Comandos

- `sudo` → administrador 
- `rm -rf` → borra todo  

### Arduino en red

Puede:

- Conectarse a WiFi
- Enviar y recibir datos
- Reaccionar en tiempo real

Para funcionar correctamente:

- Misma red WiFi
- Mismo broker
- Mismo topic
- Mismas credenciales
