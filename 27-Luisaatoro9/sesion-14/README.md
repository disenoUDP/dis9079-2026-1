# sesion-14

lunes 15 junio 2026

# Migración a la nube y problemas con los sensores

La clase de hoy empezó súper estresante porque el servicio que estábamos usando para mandar los datos de la planta (dweet.io) dejó de funcionar. Quedamos medio parados porque dependíamos de eso para ver la información en tiempo real y tuvimos que buscar una solución rápido. Al final decidimos dejar de trabajar solamente en una red local y migrar todo a la nube usando HiveMQ Cloud para que los datos se pudieran visualizar desde cualquier lugar.

Primero trabajamos con un código de prueba utilizando el Arduino UNO R4, el ADS1115 y una red WiFi creada por el propio dispositivo. La idea era comprobar que los cuatro canales del ADS1115 estuvieran leyendo correctamente y que los datos se pudieran consultar desde una página local en formato JSON.

Después de verificar que las lecturas funcionaban, comenzamos la migración a HiveMQ Cloud. Esta parte tomó bastante tiempo porque tuvimos que crear la cuenta, configurar el clúster, obtener las credenciales y modificar el código para utilizar MQTT como protocolo de comunicación.

<img width="737" height="827" alt="image" src="https://github.com/user-attachments/assets/d60a6c5a-1c4f-4626-8596-c6c033526a72" />


Durante las pruebas tuvimos algunos problemas de conexión. En un momento el monitor serial indicaba que el dispositivo no estaba conectado y pensamos que existía un error en el código. Después de revisar varias cosas nos dimos cuenta de que el problema estaba relacionado con la configuración y la conexión física del Arduino, por lo que logramos solucionarlo conectándolo correctamente por USB.

Cuando finalmente conseguimos visualizar los datos desde la web apareció otro problema inesperado. Los valores parecían indicar niveles de humedad cercanos al 100% casi todo el tiempo. Lo primero que pensamos fue que el cálculo estaba mal hecho o que existía algún error en la programación.

<img width="728" height="387" alt="image" src="https://github.com/user-attachments/assets/ed078f7c-069a-4812-91f7-7eb231aed4ab" />

Después de analizar mejor el hardware entendimos que el problema no estaba en el software. Los sensores que utilizábamos no eran sensores de humedad convencionales para medir suelo. En realidad estábamos trabajando con cuatro electrodos ubicados en distintas zonas de la planta, por lo que las lecturas representaban variaciones eléctricas entre hojas, tallo y otros puntos de contacto.

<img width="1105" height="842" alt="image" src="https://github.com/user-attachments/assets/9abbba76-464e-4566-8a12-239769c0010c" />

A partir de ese descubrimiento decidimos replantear el enfoque del proyecto. En lugar de interpretar los datos únicamente como humedad, comenzamos a pensar en ellos como señales eléctricas producidas por la planta. Esto dio origen a la idea de construir una visualización más orgánica basada en ondas, partículas y movimientos que reaccionaran a esos cambios, transformando el proyecto en una especie de "voz de las plantas".

<img width="647" height="386" alt="image" src="https://github.com/user-attachments/assets/5d3ea31c-cd1a-4121-b5af-104f504a1d65" />
<img width="515" height="721" alt="image" src="https://github.com/user-attachments/assets/d05ac97b-9abe-45de-8e45-3a80889a806d" />

## Código de prueba utilizado

```cpp
#include <Wire.h>
#include <Adafruit_ADS1X15.h>
#include <WiFiS3.h>

const char* NOMBRE_RED = "planta-sensor";
const char* CLAVE_RED  = "plantaviva";

Adafruit_ADS1115 ads;
WiFiServer servidor(80);

 int lecturas[4] = {0, 0, 0, 0};
 int base[4]     = {0, 0, 0, 0};
 int cambio[4]   = {0, 0, 0, 0};

String nombres[4] = {"hoja_grande", "hoja_pequena", "tallo", "sustrato"};

unsigned long ultimaLectura = 0;
const int INTERVALO = 500;

void setup() {
Serial.begin(9600);
Serial.println("=== La Voz de las Plantas - Grupo 07 ===");

if (!ads.begin()) {
Serial.println("ERROR: ADS1115 no encontrado.");
while (1);
}
ads.setGain(GAIN_SIXTEEN);

Serial.println("Calibrando... no toques la planta");
delay(2000);
for (int i = 0; i < 4; i++) {
long suma = 0;
for (int j = 0; j < 10; j++) {
  suma += ads.readADC_SingleEnded(i);
  delay(100);
}
base[i] = suma / 10;
}
Serial.println("Calibrado!");

WiFi.beginAP(NOMBRE_RED, CLAVE_RED);
while (WiFi.status() != WL_AP_LISTENING) {
delay(500);
Serial.print(".");
}
servidor.begin();
Serial.println("\nRed lista!");
Serial.println("http://192.168.4.1/datos");
}

void loop() {
unsigned long ahora = millis();
if (ahora - ultimaLectura >= INTERVALO) {
ultimaLectura = ahora;
for (int i = 0; i < 4; i++) {
  lecturas[i] = ads.readADC_SingleEnded(i);
  cambio[i]   = lecturas[i] - base[i];
}
for (int i = 0; i < 4; i++) {
  Serial.print(nombres[i]);
  Serial.print(": ");
  Serial.print(lecturas[i]);
  Serial.print(" (");
  if (cambio[i] >= 0) Serial.print("+");
  Serial.print(cambio[i]);
  Serial.println(")");
}
Serial.println("---");
}

WiFiClient cliente = servidor.available();
if (cliente) {
String peticion = "";
unsigned long inicio = millis();
while (cliente.connected() && millis() - inicio < 1000) {
  if (cliente.available()) {
    char c = cliente.read();
    peticion += c;
    if (peticion.endsWith("\r\n\r\n")) break;
  }
}

if (peticion.indexOf("GET /datos") >= 0) {
  String json = "{";
  for (int i = 0; i < 4; i++) {
    json += "\"" + nombres[i] + "\":" + String(lecturas[i]);
    json += ",\"" + nombres[i] + "_cambio\":" + String(cambio[i]);
    if (i < 3) json += ",";
  }
  json += "}";

  cliente.println("HTTP/1.1 200 OK");
  cliente.println("Content-Type: application/json");
  cliente.println("Access-Control-Allow-Origin: *");
  cliente.println("Connection: close");
  cliente.println();
  cliente.print(json);
}
cliente.stop();
}
}
```

## Código final utilizado

```cpp
/*
 * LA VOZ DE LAS PLANTAS — Arduino UNO R4 WiFi + ADS1115
 * Publica los 4 canales del ADS1115 a HiveMQ Cloud via MQTT
 *
 * Librerías necesarias (Herramientas → Gestionar librerías):
 *   - ArduinoMqttClient  (de Arduino)
 *   - Adafruit ADS1X15   (de Adafruit)
 *   WiFiS3 ya viene incluida con Arduino UNO R4
 */

#include <WiFiS3.h>
#include <ArduinoMqttClient.h>
#include <Wire.h>
#include <Adafruit_ADS1X15.h>

// ─── CONFIGURACIÓN WiFi ───────────────────────────────────────────
const char* WIFI_SSID     = "xxxxxx";       // <-- tu red
const char* WIFI_PASSWORD = "xxxxxxxxxx";   // <-- tu contraseña

// ─── CONFIGURACIÓN HiveMQ Cloud ──────────────────────────────────
const char* MQTT_HOST     = "XXXXXXXX";
const int   MQTT_PORT     = XXXX;
const char* MQTT_USER     = "Planta";
const char* MQTT_PASSWORD = "Planta2024!";
const char* MQTT_TOPIC    = "planta/humedad";
const char* CLIENT_ID     = "arduino-planta-001";

// ─── CALIBRACIÓN DEL SENSOR DE HUMEDAD (canal A0) ────────────────
// Mide tu sensor en aire seco y en agua, ajusta estos valores:
const int VALOR_SECO   = 17000;   // lectura con suelo SECO
const int VALOR_MOJADO =  8000;   // lectura con suelo MOJADO

// ─── INTERVALO DE ENVÍO ──────────────────────────────────────────
const long INTERVALO_MS = 3000;   // enviar cada 3 segundos

// ─── OBJETOS ─────────────────────────────────────────────────────
Adafruit_ADS1115 ads;
WiFiSSLClient    wifiClient;
MqttClient       mqttClient(wifiClient);

unsigned long ultimoEnvio = 0;

// ─────────────────────────────────────────────────────────────────
void setup() {
  Serial.begin(9600);
  while (!Serial) delay(10);

  Serial.println("================================");
  Serial.println("  LA VOZ DE LAS PLANTAS");
  Serial.println("================================");

  // Iniciar ADS1115
  if (!ads.begin()) {
    Serial.println("[ERROR] ADS1115 no encontrado. Verifica SDA/SCL.");
    while (1) delay(1000);
  }
  ads.setGain(GAIN_ONE);
  Serial.println("[OK] ADS1115 listo");

  // Conectar WiFi
  conectarWiFi();

  // Configurar y conectar MQTT
  mqttClient.setId(CLIENT_ID);
  mqttClient.setUsernamePassword(MQTT_USER, MQTT_PASSWORD);
  conectarMQTT();
}

// ─────────────────────────────────────────────────────────────────
void loop() {
  mqttClient.poll();

  // Reconectar MQTT si se cae
  if (!mqttClient.connected()) {
    Serial.println("[MQTT] Desconectado, reconectando...");
    delay(1000);
    conectarMQTT();
  }

  // Enviar datos según intervalo
  unsigned long ahora = millis();
  if (ahora - ultimoEnvio >= INTERVALO_MS) {
    ultimoEnvio = ahora;
    leerYEnviar();
  }
}

// ─────────────────────────────────────────────────────────────────
void leerYEnviar() {

  // Leer los 4 canales del ADS1115
  int16_t a0 = ads.readADC_SingleEnded(0);  // sensor principal humedad suelo
  int16_t a1 = ads.readADC_SingleEnded(1);  // canal extra 1
  int16_t a2 = ads.readADC_SingleEnded(2);  // canal extra 2
  int16_t a3 = ads.readADC_SingleEnded(3);  // canal extra 3

  // Calcular humedad como porcentaje (basado en A0)
  int humedad = map(a0, VALOR_SECO, VALOR_MOJADO, 0, 100);
  humedad = constrain(humedad, 0, 100);

  // Determinar estado
  String estado;
  if      (humedad < 30) estado = "SECO";
  else if (humedad < 60) estado = "OPTIMO";
  else                   estado = "HUMEDO";

  // Construir JSON con todos los datos
  String json = "{";
  json += "\"humedad\":"    + String(humedad)  + ",";
  json += "\"valorCrudo\":" + String(a0)       + ",";
  json += "\"a1\":"         + String(a1)       + ",";
  json += "\"a2\":"         + String(a2)       + ",";
  json += "\"a3\":"         + String(a3)       + ",";
  json += "\"estado\":\""   + estado           + "\"";
  json += "}";

  // Publicar en HiveMQ
  mqttClient.beginMessage(MQTT_TOPIC);
  mqttClient.print(json);
  mqttClient.endMessage();

  // Log en Serial Monitor
  Serial.println("─────────────────────────");
  Serial.println("[MQTT] Enviado:");
  Serial.println("  humedad  : " + String(humedad) + "%");
  Serial.println("  A0 (raw) : " + String(a0));
  Serial.println("  A1       : " + String(a1));
  Serial.println("  A2       : " + String(a2));
  Serial.println("  A3       : " + String(a3));
  Serial.println("  estado   : " + estado);
}

// ─────────────────────────────────────────────────────────────────
void conectarWiFi() {
  Serial.print("[WiFi] Conectando a: ");
  Serial.println(WIFI_SSID);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  int intentos = 0;
  while (WiFi.status() != WL_CONNECTED && intentos < 30) {
    delay(500);
    Serial.print(".");
    intentos++;
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println();
    Serial.println("[WiFi] Conectado!");
    Serial.print("[WiFi] IP: ");
    Serial.println(WiFi.localIP());
  } else {
    Serial.println();
    Serial.println("[WiFi] ERROR: No se pudo conectar.");
    Serial.println("[WiFi] Verifica SSID y contraseña.");
  }
}

// ─────────────────────────────────────────────────────────────────
void conectarMQTT() {
  Serial.print("[MQTT] Conectando a HiveMQ...");

  int intentos = 0;
  while (!mqttClient.connect(MQTT_HOST, MQTT_PORT) && intentos < 5) {
    Serial.print(".");
    delay(2000);
    intentos++;
  }

  if (mqttClient.connected()) {
    Serial.println(" OK!");
  } else {
    Serial.println(" FALLO");
    Serial.print("[MQTT] Error codigo: ");
    Serial.println(mqttClient.connectError());
  }
}
```
### HTML para visualización de datos 
<img width="733" height="521" alt="image" src="https://github.com/user-attachments/assets/70197aad-5d83-4875-839c-6109f969e475" />
<img width="743" height="442" alt="image" src="https://github.com/user-attachments/assets/f16999a1-bbdc-4780-ab6c-c38b70d42d0b" />
<img width="401" height="457" alt="image" src="https://github.com/user-attachments/assets/da3c26b4-9620-437d-84ef-ce81a1e1e00b" />


