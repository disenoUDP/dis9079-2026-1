// -------------------------
// Importar bibliotecas
// -------------------------

#include <WiFiS3.h>               // Librería nativa para el módulo WiFi del Arduino UNO R4
#include "Adafruit_MQTT.h"        // Librería base de Adafruit para el protocolo MQTT
#include "Adafruit_MQTT_Client.h" // Cliente que gestiona la conexión de datos con el servidor
#include <Servo.h>                // Librería para el control del servo motor SG90


// -------------------------
// Datos de configuración (WiFi y Adafruit IO)
// -------------------------

// Nombre de tu red WiFi local
#define WLAN_SSID       "wenakiara"

// Contraseña de tu red WiFi
#define WLAN_PASS       "tomas123"

// Servidor MQTT de la plataforma Adafruit IO
#define AIO_SERVER      "io.adafruit.com"

// Puerto estándar para conexiones MQTT inseguras
#define AIO_SERVERPORT  1883

// Tu nombre de usuario de Adafruit IO
#define AIO_USERNAME    "tomascatri"

// Tu clave secreta AIO KEY de Adafruit IO
#define AIO_KEY         "blep"


// -------------------------
// Creación de objetos y suscripciones
// -------------------------

// Instancia del cliente WiFi nativo
WiFiClient client;

// Configuración del cliente MQTT amarrado al cliente WiFi y los datos del servidor
Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);

// Configuración de la suscripción al feed específico (Ruta: usuario/feeds/nombre-del-feed)
// Este feed debe llamarse EXACTAMENTE igual al definido en la Raspberry Pi Pico
Adafruit_MQTT_Subscribe grupo_feed = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/solemne02-grupo01");

// Instancia para controlar el servo motor físico
Servo myservo;

// Pin digital con soporte PWM donde se conecta el cable naranja de señal del servo
const int servoPin = 9;


// -------------------------
// Declaración de funciones
// -------------------------

// Avisamos al compilador que abajo existe la función encargada de conectar/reconectar MQTT
void MQTT_connect();


// -------------------------
// Setup: Configuración inicial (se ejecuta una sola vez)
// -------------------------

void setup() {
  // Iniciar la comunicación con el monitor serial a 115200 baudios
  Serial.begin(115200);
  
  // Asociar el objeto del servo al pin físico número 9
  myservo.attach(servoPin);

  // --- Proceso de conexión a la red WiFi ---
  Serial.print("Conectando a WiFi...");
  WiFi.begin(WLAN_SSID, WLAN_PASS);
  
  // Bucle de espera: se mantiene aquí hasta que el estado del WiFi sea "conectado"
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print("."); // Imprime puntos suspensivos mientras conecta
  }
  Serial.println(" ¡Conectado!");

  // Activar la escucha de datos registrando la suscripción en el cliente MQTT
  mqtt.subscribe(&grupo_feed);
}


// -------------------------
// Loop principal: Ejecución continua
// -------------------------

void loop() {
  // Verificar que la conexión a MQTT siga viva; si se cayó, se reconecta automáticamente
  MQTT_connect();

  // Crear un puntero para almacenar de forma temporal la suscripción entrante
  Adafruit_MQTT_Subscribe *subscription; 
  
  // Leer si llegó algún mensaje en un rango de 5 segundos (5000ms)
  while ((subscription = mqtt.readSubscription(5000))) {
    
    // Si el mensaje que llegó pertenece específicamente a nuestro feed del grupo
    if (subscription == &grupo_feed) {
      
      // Imprimir el mensaje crudo en texto que mandó la Pico W
      Serial.print(F("Dato recibido de la Pico: "));
      Serial.println((char *)grupo_feed.lastread);
      
      // OPTIMIZACIÓN Y CONVERSIÓN:
      // Convertir el arreglo de caracteres de texto a un número entero funcional (rango 0 - 1023)
      int potValue = atoi((char *)grupo_feed.lastread);
      
      // MAPEO MATEMÁTICO:
      // Transforma proporcionalmente el valor del potenciómetro (0-1023) al arco del servo (0-180 grados)
      int angulo = map(potValue, 0, 1023, 0, 180);
      
      // Mover físicamente los engranajes del servo motor al ángulo calculado
      myservo.write(angulo);
      
      // Confirmar la acción en el monitor serial para depuración
      Serial.print("Servo movido a: ");
      Serial.println(angulo);
    }
  }
}


// -------------------------
// Función de conexión y resiliencia MQTT
// -------------------------

void MQTT_connect() {
  int8_t ret;

  // Si el cliente ya se encuentra conectado con éxito, salir de la función de inmediato
  if (mqtt.connected()) return;

  Serial.print("Conectando a MQTT... ");
  
  // Bucle de reintento en caso de fallas de red
  while ((ret = mqtt.connect()) != 0) {
       // Mostrar el error específico en la consola de Arduino
       Serial.println(mqtt.connectErrorString(ret));
       Serial.println("Reintentando conexión en 5 segundos...");
       
       mqtt.disconnect(); // Desconectar de forma limpia antes de volver a intentar
       delay(5000);       // Pausa de seguridad para evitar saturar el servidor
  }
  
  Serial.println("¡MQTT Conectado!");
}