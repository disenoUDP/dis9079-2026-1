
// -----------------------------
// TOTEM 02
// Recibe datos desde Adafruit IO
// y los muestra en pantalla OLED SH1106
// -----------------------------

#include <WiFiS3.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"
#include <Wire.h>
#include <U8g2lib.h>

// -----------------------------
// DATOS WIFI
// -----------------------------

#define WIFI_SSID "TU_WIFI"
#define WIFI_PASS "TU_CLAVE_WIFI"

// -----------------------------
// ADAFRUIT IO
// -----------------------------

#define IO_USERNAME "TU_USUARIO_ADAFRUIT"
#define IO_KEY "TU_IO_KEY_ADAFRUIT"

#define AIO_SERVER "io.adafruit.com"
#define AIO_SERVERPORT 1883 

// Usa el mismo feed que el Totem 01
// Si tu feed se llama TOTEM01, deja "TOTEM01"
// Si tu feed se llama totem01, cambia a "totem01"
#define AIO_FEED "TOTEM01"

// -----------------------------
// CLIENTE WIFI + MQTT
// -----------------------------

WiFiClient client;

Adafruit_MQTT_Client mqtt(
  &client,
  AIO_SERVER,
  AIO_SERVERPORT,
  IO_USERNAME,
  IO_KEY
);

Adafruit_MQTT_Subscribe estadoFeed = Adafruit_MQTT_Subscribe(
  &mqtt,
  IO_USERNAME "/feeds/" AIO_FEED
);

// -----------------------------
// PANTALLA OLED SH1106
// -----------------------------

U8G2_SH1106_128X64_NONAME_F_HW_I2C pantalla(
  U8G2_R0,
  U8X8_PIN_NONE
);

// -----------------------------
// CODIGOS DEL SISTEMA
// -----------------------------

const int COD_SIN_PRESENCIA = 0;
const int COD_DISTANCIA_01 = 1;
const int COD_DISTANCIA_02 = 2;
const int COD_DISTANCIA_03 = 3;
const int COD_AUSENCIA = 4;

// -----------------------------
// VARIABLES
// -----------------------------

int codigoActual = -1;
int codigoAnterior = -2;

unsigned long ultimoPing = 0;
const unsigned long intervaloPing = 30000;

// -----------------------------
// SETUP
// -----------------------------

void setup() {
  Serial.begin(9600);
  delay(1000);

  Wire.begin();
  Wire.setClock(50000);

  pantalla.begin();
  pantalla.setContrast(120);

  mostrarInicio("Totem 02", "Iniciando...");

  conectarWiFi();

  mqtt.subscribe(&estadoFeed);

  conectarMQTT();

  mostrarInicio("Totem 02", "Esperando datos");
}

// -----------------------------
// LOOP
// -----------------------------

void loop() {
  mantenerConexionMQTT();

  Adafruit_MQTT_Subscribe *subscription;

  while ((subscription = mqtt.readSubscription(1000))) {
    if (subscription == &estadoFeed) {
      recibirEstado();
    }
  }

  if (millis() - ultimoPing >= intervaloPing) {
    ultimoPing = millis();

    if (!mqtt.ping()) {
      mqtt.disconnect();
      Serial.println("MQTT desconectado");
    }
  }
}

// -----------------------------
// CONECTAR WIFI
// -----------------------------

void conectarWiFi() {
  Serial.println("-------------------------");
  Serial.print("Conectando a WiFi");

  mostrarInicio("Conectando", "WiFi...");

  WiFi.begin(WIFI_SSID, WIFI_PASS);

  unsigned long inicioWiFi = millis();
  const unsigned long tiempoMaximoWiFi = 20000;

  while (
    WiFi.status() != WL_CONNECTED &&
    millis() - inicioWiFi < tiempoMaximoWiFi
  ) {
    Serial.print(".");
    delay(500);
  }

  Serial.println();

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("WiFi conectado");
    Serial.print("IP: ");
    Serial.println(WiFi.localIP());

    mostrarInicio("WiFi conectado", "Conectando IO...");
  } else {
    Serial.println("No conecto a WiFi");
    mostrarInicio("Error WiFi", "Revisar datos");
  }

  Serial.println("-------------------------");
}

// -----------------------------
// CONECTAR MQTT / ADAFRUIT
// -----------------------------

void conectarMQTT() {
  if (mqtt.connected()) {
    return;
  }

  Serial.println("Conectando a Adafruit IO...");
  mostrarInicio("Conectando", "Adafruit IO...");

  int8_t resultado;

  while ((resultado = mqtt.connect()) != 0) {
    Serial.print("Error MQTT: ");
    Serial.println(mqtt.connectErrorString(resultado));

    mqtt.disconnect();

    mostrarInicio("Error MQTT", "Reintentando...");

    delay(3000);
  }

  Serial.println("Conectado a Adafruit IO");
  Serial.println("-------------------------");

  mostrarInicio("Adafruit IO", "Conectado");
  delay(1000);
}

// -----------------------------
// MANTENER CONEXION
// -----------------------------

void mantenerConexionMQTT() {
  if (WiFi.status() != WL_CONNECTED) {
    conectarWiFi();
  }

  if (!mqtt.connected()) {
    conectarMQTT();
  }
}

// -----------------------------
// RECIBIR ESTADO
// -----------------------------

void recibirEstado() {
  char *datoRecibido = (char *)estadoFeed.lastread;

  int codigoRecibido = atoi(datoRecibido);

  Serial.print("Dato recibido desde Adafruit IO: ");
  Serial.println(datoRecibido);

  Serial.print("Codigo interpretado: ");
  Serial.println(codigoRecibido);

  if (codigoRecibido == codigoAnterior) {
    Serial.println("Mismo codigo, no se actualiza pantalla");
    Serial.println("-------------------------");
    return;
  }

  codigoActual = codigoRecibido;
  codigoAnterior = codigoActual;

  interpretarCodigo(codigoActual);
}

// -----------------------------
// INTERPRETAR CODIGO
// -----------------------------

void interpretarCodigo(int codigo) {
  String mensaje = "";

  if (codigo == COD_SIN_PRESENCIA) {
    mensaje = "Sin presencia";
  }

  else if (codigo == COD_DISTANCIA_01) {
    mensaje = "Distancia 01";
  }

  else if (codigo == COD_DISTANCIA_02) {
    mensaje = "Distancia 02";
  }

  else if (codigo == COD_DISTANCIA_03) {
    mensaje = "Distancia 03";
  }

  else if (codigo == COD_AUSENCIA) {
    mensaje = "Ausencia prolongada";
  }

  else {
    mensaje = "Codigo no valido";
  }

  Serial.print("Mensaje pantalla: ");
  Serial.println(mensaje);
  Serial.println("-------------------------");

  mostrarEnPantalla(mensaje, codigo);
}

// -----------------------------
// MOSTRAR TEXTO DE INICIO
// -----------------------------

void mostrarInicio(String linea1, String linea2) {
  pantalla.clearBuffer();

  pantalla.setFont(u8g2_font_6x10_tf);

  pantalla.drawStr(0, 16, linea1.c_str());
  pantalla.drawStr(0, 36, linea2.c_str());

  pantalla.sendBuffer();
}

// -----------------------------
// MOSTRAR MENSAJE EN PANTALLA
// -----------------------------

void mostrarEnPantalla(String mensaje, int codigo) {
  pantalla.clearBuffer();

  pantalla.setFont(u8g2_font_6x10_tf);

  pantalla.drawStr(0, 12, "Totem 02");
  pantalla.drawStr(0, 26, "Estado recibido:");

  if (mensaje == "Ausencia prolongada") {
    pantalla.drawStr(0, 44, "Ausencia");
    pantalla.drawStr(0, 56, "prolongada");
  } else {
    pantalla.drawStr(0, 46, mensaje.c_str());
  }

  pantalla.setCursor(88, 64);
  pantalla.print("Cod:");
  pantalla.print(codigo);

  pantalla.sendBuffer();
}
