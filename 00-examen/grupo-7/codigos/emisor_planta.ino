#include <Wire.h>
#include <Adafruit_ADS1X15.h>
#include <WiFiS3.h>

const char* NOMBRE_RED = "planta-sensor";
const char* CLAVE_RED  = "plantaviva";

Adafruit_ADS1115 ads;
WiFiServer servidor(80);

int lecturas[4]  = {0, 0, 0, 0};
int base[4]      = {0, 0, 0, 0};
int cambio[4]    = {0, 0, 0, 0};

String nombres[4] = {"hoja_grande", "hoja_pequena", "tallo", "sustrato"};

void setup() {
  Serial.begin(9600);
  Serial.println("=== La Voz de las Plantas - Grupo 07 ===");

  if (!ads.begin()) {
    Serial.println("ERROR: ADS1115 no encontrado.");
    while (1);
  }
  ads.setGain(GAIN_SIXTEEN);
  Serial.println("ADS1115 listo.");

  Serial.println("Calibrando... no toques la planta");
  delay(2000);
  for (int i = 0; i < 4; i++) {
    long suma = 0;
    for (int j = 0; j < 10; j++) {
      suma += ads.readADC_SingleEnded(i);
      delay(100);
    }
    base[i] = suma / 10;
    Serial.print("Base canal ");
    Serial.print(i);
    Serial.print(": ");
    Serial.println(base[i]);
  }
  Serial.println("Calibrado!");

  Serial.print("Creando red: ");
  Serial.println(NOMBRE_RED);
  WiFi.beginAP(NOMBRE_RED, CLAVE_RED);
  while (WiFi.status() != WL_AP_LISTENING) {
    delay(500);
    Serial.print(".");
  }
  servidor.begin();
  Serial.println("\nRed lista!");
  Serial.println("Conectarse a 'planta-sensor' y abrir:");
  Serial.println("http://192.168.4.1/datos");
}

void loop() {
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

  WiFiClient cliente = servidor.available();
  if (cliente) {
    String peticion = "";
    while (cliente.connected()) {
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
      cliente.println(json);

    } else if (peticion.indexOf("GET / ") >= 0) {
      cliente.println("HTTP/1.1 200 OK");
      cliente.println("Content-Type: text/html");
      cliente.println("Connection: close");
      cliente.println();
      cliente.println("<html><body style='background:#000;color:#0f0;font-family:monospace;padding:2rem'>");
      cliente.println("<h2>La Voz de las Plantas</h2>");
      cliente.println("<p>Abre <a href='/datos' style='color:#0f0'>/datos</a> para ver los valores</p>");
      cliente.println("</body></html>");
    }

    delay(10);
    cliente.stop();
  }

  delay(50);
}