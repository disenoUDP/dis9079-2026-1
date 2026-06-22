# sesion-14

lunes 15 junio 2026

# Contador con dos botones y Adafruit IO
Resumen de cableado, código y configuración — Arduino Uno R4 WiFi

1. Objetivo
Dos botones pulsadores conectados a un Arduino Uno R4 WiFi. Uno suma y otro resta un contador. El valor se envía por WiFi a un feed de Adafruit IO usando el protocolo MQTT.

3. Materiales
•	Arduino Uno R4 WiFi
•	Protoboard
•	2 botones pulsadores (push button)
•	3 cables macho-macho (jumpers)

5. Conexiones (cableado)
No se necesitan resistencias: el código activa la resistencia interna de pull-up del Arduino (modo INPUT_PULLUP).

# Librerías necesarias (Arduino IDE)

1.	Adafruit MQTT Library
2.	WiFiS3 (incluida con el paquete de placas Arduino R4)

# Lógica del programa
El Arduino se conecta al WiFi y luego al broker MQTT de Adafruit IO.
Se leen los pines D2 y D3 en modo INPUT_PULLUP.
Al detectar que el botón SUMA pasa a LOW, el contador aumenta en 1.
Al detectar que el botón RESTA pasa a LOW, el contador disminuye en 1.
Cada cambio se publica en el feed “contador” de Adafruit IO.

# Configuración en Adafruit IO
Entrar a io.adafruit.com
Crear un feed llamado “contador”
Crear un dashboard y agregar un bloque tipo Gauge o Stream apuntando a ese feed
Copiar el AIO Key desde el perfil de usuario para usarlo en el código

