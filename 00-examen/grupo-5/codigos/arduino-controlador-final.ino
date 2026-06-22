// =================================================================
// ARCHIVO RETRO - FIRMWARE ARDUINO UNO R4 WIFI (VERSIÓN ASÍNCRONA)
// Es el "cerebro" del sistema: lee el potenciómetro (vibe) y el
// botón (disparo / cambio de dither), dibuja el estado en el OLED
// y le manda el comando al ESP32-CAM por WiFi.
// =================================================================

// ──────────────────────────────────────────────
// LIBRERÍAS
// ──────────────────────────────────────────────
#include <WiFi.h>                 // Conexión WiFi del Uno R4
#include <WiFiUdp.h>               // Escucha el beacon UDP que emite el ESP32-CAM para descubrir su IP
#include <Wire.h>                  // Bus I2C, usado por el OLED
#include <Adafruit_GFX.h>          // Librería gráfica base (texto, formas) sobre la que corre el driver del OLED
#include <Adafruit_SSD1306.h>      // Driver específico del controlador SSD1306 del display

// ──────────────────────────────────────────────
// CREDENCIALES WIFI
// ──────────────────────────────────────────────
const char* ssid     = "wenakiara";
const char* password = "tomas123";

// ──────────────────────────────────────────────
// DESCUBRIMIENTO DE LA CÁMARA POR UDP
// El ESP32-CAM no tiene IP fija: cada 5s grita su IP por broadcast
// UDP y este Arduino la escucha para saber a dónde mandar el HTTP.
// ──────────────────────────────────────────────
WiFiUDP udpListen;
const int UDP_PORT = 4210;        // Debe coincidir con el puerto que usa el ESP32-CAM
String esp32camIP = "";           // IP de la cámara, una vez descubierta
bool camDescubierta = false;      // ¿Ya se encontró la cámara en la red?

// ──────────────────────────────────────────────
// ENTRADAS FÍSICAS
// ──────────────────────────────────────────────
#define LONG_PRESS_MS 600UL        // Umbral en ms para distinguir pulsación corta (disparo) de larga (cambiar dither)
const int PIN_BOTON = 2;           // Botón único: corto = disparar, largo = siguiente dither
const int PIN_POT   = A0;          // Potenciómetro: selecciona la paleta/"vibe" en tiempo real

// ──────────────────────────────────────────────
// PANTALLA OLED
// ──────────────────────────────────────────────
#define SCREEN_W 128
#define SCREEN_H 64
Adafruit_SSD1306 oled(SCREEN_W, SCREEN_H, &Wire, -1);   // -1: no hay pin de reset dedicado, comparte el reset del Arduino

#define STATUS_H 16   // Alto de la franja amarilla física del panel (0-15px). El resto (16-63px) es la franja azul.

// ──────────────────────────────────────────────
// PALETAS DISPONIBLES
// Estos nombres viajan tal cual en el POST al ESP32-CAM, así que
// deben coincidir EXACTAMENTE con los strings de selectPalette()
// en el firmware de la cámara.
// ──────────────────────────────────────────────
const char* paletasNombres[] = {"wish-gb", "kirokaze-gb", "ayy4", "ice-cream-gb", "hollow", "crimson"};
const int totalPaletas = 6;
int ultimaPaletaSeleccionada = -1;   // -1 fuerza un primer redibujo en el primer loop()

// ──────────────────────────────────────────────
// ALGORITMOS DE DITHER DISPONIBLES
// Mismo criterio: deben coincidir con ditherFromName() del ESP32-CAM.
// ──────────────────────────────────────────────
const char* dithersNombres[] = {"bayer", "floyd", "atkinson", "sierra", "ordered2", "halftone", "block", "random", "nearest"};
const int totalDithers = 9;
int ditherActualIdx = 0;     // Índice del dither activo dentro de dithersNombres[]
int blockSize = 8;           // Tamaño de bloque usado solo cuando el dither activo es "block"

// Tiempo estimado (en segundos) que demora cada dither en procesarse en la cámara,
// usado únicamente para animar la barra de progreso en el OLED mientras se espera la respuesta.
struct TiempoDither { const char* nombre; float segundos; };
TiempoDither TIEMPOS_ESTIMADOS[] = {
  {"bayer", 4.0}, {"ordered2", 4.0}, {"halftone", 4.0}, {"block", 3.0},
  {"nearest", 3.0}, {"random", 4.0}, {"floyd", 7.0}, {"atkinson", 8.0}, {"sierra", 6.5}
};

// Busca el tiempo estimado de un dither por nombre; si no lo encuentra, usa 5.0s como valor genérico
float tiempoEstimadoPara(const char* dither) {
  for (uint8_t i = 0; i < sizeof(TIEMPOS_ESTIMADOS) / sizeof(TiempoDither); i++) {
    if (strcmp(TIEMPOS_ESTIMADOS[i].nombre, dither) == 0) return TIEMPOS_ESTIMADOS[i].segundos;
  }
  return 5.0;
}

String vibe;   // Nombre de la paleta actualmente seleccionada por el potenciómetro

// Trunca un texto para que nunca desborde el ancho de pantalla (evita que el wrap automático
// invada la línea de abajo cuando un nombre de paleta es muy largo)
String truncarTexto(const String& s, int maxChars) {
  if ((int)s.length() <= maxChars) return s;
  return s.substring(0, maxChars - 1) + ".";   // Corta y agrega un punto como indicador de truncado
}

// ──────────────────────────────────────────────
// RENDER: FRANJA AMARILLA (0-15px) — status bar fija
// Se redibuja sola, sin tocar el contenido de la franja azul.
// Diseño "negativo": toda la franja se enciende en blanco y el
// texto "ARCHIVO RETRO" se dibuja en negro, apagando esos píxeles.
// ──────────────────────────────────────────────
void dibujarStatusBar() {
  oled.fillRect(0, 0, SCREEN_W, STATUS_H, SSD1306_WHITE);   // Enciende todo el bloque amarillo
  oled.setTextSize(1);
  oled.setTextColor(SSD1306_BLACK);                          // Texto en negro = píxeles apagados sobre el fondo encendido
  oled.setCursor(2, 4);
  oled.print("ARCHIVO RETRO");
  oled.display();
}

// Limpia únicamente la franja azul (16-63px), dejando la franja amarilla intacta arriba
void limpiarContenido() {
  oled.fillRect(0, STATUS_H, SCREEN_W, SCREEN_H - STATUS_H, SSD1306_BLACK);
}

// ──────────────────────────────────────────────
// RENDER: FRANJA AZUL (16-63px) — contenido dinámico
// ──────────────────────────────────────────────

// Pantalla principal: muestra la vibe y el dither activos, y la ayuda de controles
void dibujarPantalla(const String& vibeAct, const char* dither) {
  limpiarContenido();
  oled.setTextSize(1);
  oled.setTextColor(SSD1306_WHITE);
  oled.setTextWrap(false);   // Evita que Adafruit_GFX salte de línea solo si el texto no entra

  oled.setCursor(2, 20); oled.print("Vibe: " + truncarTexto(vibeAct, 15));   // 15 chars caben junto al prefijo "Vibe: " en 128px
  oled.setCursor(2, 32); oled.print("Dith: " + String(dither));

  if (strcmp(dither, "block") == 0) {
    oled.setCursor(2, 44); oled.print("Block: " + String(blockSize));        // Solo "block" usa este parámetro extra
  } else {
    oled.setCursor(2, 44); oled.print("> Disparo  >> Dither");               // Recordatorio de controles para el resto de dithers
  }
  oled.display();
}

// Barra de progreso, usada mientras se espera la respuesta del ESP32-CAM
void dibujarBarra(int pct, const String& mensaje) {
  pct = constrain(pct, 0, 100);
  limpiarContenido();
  oled.setTextSize(1);
  oled.setTextColor(SSD1306_WHITE);
  oled.setCursor(2, 18); oled.print(mensaje);

  const int barX = 4, barY = 34, barW = 120, barH = 20;
  oled.drawRect(barX, barY, barW, barH, SSD1306_WHITE);          // Marco de la barra
  int fillW = (barW - 4) * pct / 100;
  if (fillW > 0) oled.fillRect(barX + 2, barY + 2, fillW, barH - 4, SSD1306_WHITE);   // Relleno proporcional al progreso

  oled.setCursor(barX + barW / 2 - 10, barY + 6);
  oled.print(String(pct) + "%");
  oled.display();
}

// Mensaje genérico de una o dos líneas (errores, estados transitorios) en la franja azul
void dibujarMensaje(const String& l1, const String& l2 = "") {
  limpiarContenido();
  oled.setTextSize(1);
  oled.setTextColor(SSD1306_WHITE);
  oled.setCursor(2, 24); oled.print(l1);
  if (l2.length() > 0) {
    oled.setCursor(2, 40); oled.print(l2);
  }
  oled.display();
}

// ──────────────────────────────────────────────
// DESCUBRIMIENTO DE LA CÁMARA
// Escucha el beacon UDP del ESP32-CAM hasta 15s, validando que el
// mensaje tenga el prefijo esperado y limpiando la IP de basura.
// ──────────────────────────────────────────────
// Prefijo exacto que manda el ESP32-CAM en cada beacon. Se usa su largo real para cortar
// el mensaje en el lugar correcto, en vez de un número fijo "a mano" que se puede desincronizar.
const char* BEACON_PREFIX = "ARCHIVO-RETRO-CAM:";

void descubrirCamara() {
  Serial.print("[UDP] Buscando ARCHIVO-RETRO-CAM...");
  dibujarStatusBar();
  dibujarMensaje("Buscando IP Cam...");

  unsigned long t0 = millis();
  while (millis() - t0 < 15000) {
    int n = udpListen.parsePacket();
    if (n > 0) {
      char buf[64] = {0};
      udpListen.read(buf, sizeof(buf)-1);
      String msg = String(buf);

      if (msg.startsWith(BEACON_PREFIX)) {
        // Corta justo después del prefijo, sea cual sea su largo (antes era un número fijo: substring(11))
        String ipSucia = msg.substring(strlen(BEACON_PREFIX));
        ipSucia.trim();

        // Filtra carácter por carácter, quedándose solo con dígitos y puntos (limpia restos del prefijo o saltos de línea)
        esp32camIP = "";
        for (unsigned int i = 0; i < ipSucia.length(); i++) {
          char c = ipSucia.charAt(i);
          if ((c >= '0' && c <= '9') || c == '.') {
            esp32camIP += c;
          }
        }

        camDescubierta = true;
        Serial.print("\n[UDP] Camara limpia detectada en: ");
        Serial.println(esp32camIP);
        dibujarStatusBar();   // No cambia visualmente (ya no hay indicador OK/X), pero mantiene el flujo de refresco consistente
        return;
      }
    }
    delay(200);   // Evita saturar la CPU mientras espera paquetes
  }
}

// ──────────────────────────────────────────────
// SETUP
// ──────────────────────────────────────────────
void setup() {
  Serial.begin(115200);
  pinMode(PIN_BOTON, INPUT_PULLUP);   // Botón a GND: LOW = presionado
  analogReadResolution(14);            // El Uno R4 soporta hasta 14 bits de resolución en el ADC (0-16383)

  Wire.begin();
  if (!oled.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { while (true) {} }   // Si el OLED no responde, queda colgado (falla visible al no encender nada)

  dibujarStatusBar();
  dibujarMensaje("Conectando WiFi...");

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) { delay(500); }

  udpListen.begin(UDP_PORT);
  descubrirCamara();

  vibe = paletasNombres[0];   // Arranca con la primera paleta por defecto, hasta que el potenciómetro se mueva
  dibujarPantalla(vibe, dithersNombres[ditherActualIdx]);
}

// ──────────────────────────────────────────────
// LOOP PRINCIPAL
// ──────────────────────────────────────────────
void loop() {
  // 1) Si se perdió la referencia a la cámara, intenta redescubrirla antes de seguir
  if (!camDescubierta) {
    descubrirCamara();
    if(!camDescubierta) {
      dibujarStatusBar();
      dibujarMensaje("Cam Desconectada");
      delay(2000);
      return;   // Sale del loop y reintenta desde el principio en la próxima vuelta
    }
    dibujarPantalla(vibe, dithersNombres[ditherActualIdx]);
  }

  // 2) Lee el potenciómetro y lo mapea a un índice de paleta (0 a totalPaletas-1)
  int valorPot = analogRead(PIN_POT);
  int paletaActual = (long)valorPot * totalPaletas / 16384;   // 16384 = 2^14, rango máximo del ADC configurado arriba
  if (paletaActual >= totalPaletas) paletaActual = totalPaletas - 1;   // Clamp por si el ADC entrega el valor máximo exacto
  if (paletaActual < 0) paletaActual = 0;

  if (paletaActual != ultimaPaletaSeleccionada) {
    ultimaPaletaSeleccionada = paletaActual;
    vibe = paletasNombres[paletaActual];
    dibujarPantalla(vibe, dithersNombres[ditherActualIdx]);   // Solo redibuja si la paleta realmente cambió (evita parpadeo)
  }

  // 3) Manejo del botón: distingue pulsación corta (disparar) de larga (cambiar dither)
  if (digitalRead(PIN_BOTON) == LOW) {
    unsigned long tInicio = millis();
    bool esPulsacionLarga = false;

    while (digitalRead(PIN_BOTON) == LOW) {
      if ((millis() - tInicio) >= LONG_PRESS_MS && !esPulsacionLarga) {
        esPulsacionLarga = true;
        ditherActualIdx = (ditherActualIdx + 1) % totalDithers;   // Avanza al siguiente dither, con wraparound
        dibujarPantalla(vibe, dithersNombres[ditherActualIdx]);
      }
      delay(20);
    }

    if (esPulsacionLarga) { delay(200); return; }   // Ya se cambió el dither, no dispara la foto en esta pulsación

    // ---- Pulsación corta confirmada: ejecuta el disparo ----
    const char* dither = dithersNombres[ditherActualIdx];
    float tiempoEstimado = tiempoEstimadoPara(dither);

    dibujarBarra(0, "Enviando...");

    // Paso A: ping preventivo a la cámara, para no intentar el POST grande si está caída
    WiFiClient testClient;
    testClient.setTimeout(3000);
    if (!testClient.connect(esp32camIP.c_str(), 80)) {
        Serial.println("[DEBUG] Ping fallido - IP correcta pero puerto cerrado");
        camDescubierta = false;   // Fuerza un redescubrimiento en el próximo loop
        dibujarStatusBar();
        dibujarMensaje("Ping Cam Fallo");
        delay(1500);
        return;
    }
    testClient.println("GET /ping HTTP/1.1");
    testClient.print("Host: "); testClient.println(esp32camIP);
    testClient.println("Connection: close");
    testClient.println();

    unsigned long tTimeoutPing = millis();
    while(!testClient.available() && (millis() - tTimeoutPing < 1000)) { delay(10); }

    String pong = "";
    while(testClient.available()) pong += (char)testClient.read();
    testClient.stop();
    Serial.println("[DEBUG] Respuesta del Pong: " + pong);

    delay(500);   // Pequeño respiro antes de abrir la conexión principal

    // Paso B: POST /foto con los parámetros del disparo
    WiFiClient client;
    client.setTimeout(5000);

    if (!client.connect(esp32camIP.c_str(), 80)) {
      Serial.println("[HTTP] Error de conexion al puerto 80 en ejecucion POST");
      camDescubierta = false;
      dibujarStatusBar();
      dibujarMensaje("Error POST HTTP");
      delay(1500);
      return;
    }

    String postData = "vibe=" + vibe + "&dither=" + String(dither) + "&block=" + String(blockSize);

    client.println("POST /foto HTTP/1.1");
    client.print("Host: "); client.println(esp32camIP);
    client.println("Content-Type: application/x-www-form-urlencoded");
    client.print("Content-Length: "); client.println(postData.length());
    client.println("Connection: close");
    client.println();
    client.print(postData);

    // Animación de barra mientras la cámara mantiene la conexión abierta (esperando el ACK "PROCESSING")
    unsigned long tEspera = millis();
    unsigned long esperaMs = (unsigned long)(tiempoEstimado * 1000.0);
    while (client.connected()) {
      unsigned long transcurrido = millis() - tEspera;
      int pct = (int)min((transcurrido * 100UL) / esperaMs, 99UL);   // Nunca llega a 100% hasta tener la respuesta real
      dibujarBarra(pct, "Procesando...");
      if (client.available()) break;   // En cuanto llega algo de respuesta, corta la animación y pasa a leerla
      delay(100);
    }

    // Lectura de la respuesta: "PROCESSING" se trata como éxito porque es el ACK inmediato del ESP32-CAM
    // (la subida real a Drive sigue corriendo en la cámara después de este punto)
    String respuesta = "";
    unsigned long tRead = millis();
    while (client.connected() || client.available()) {
      if (millis() - tRead > 35000) break;   // Timeout de seguridad para no quedar colgado indefinidamente
      if (!client.available()) { delay(50); continue; }

      String line = client.readStringUntil('\n');
      Serial.println("[R4 RAW] " + line);

      if (line.indexOf("DONE") != -1)       respuesta = "DONE";
      if (line.indexOf("PROCESSING") != -1) respuesta = "DONE";   // ACK inmediato mapeado como éxito
      if (line.indexOf("ERROR") != -1)      respuesta = "ERROR";
    }
    client.stop();

    dibujarBarra(100, "Listo!");
    delay(300);

    if (respuesta == "DONE") {
      dibujarMensaje("CAPTURADA! " + vibe, "Dith: " + String(dither) + " - Subiendo...");
    } else {
      dibujarMensaje("Fallo en subida", "Check ESP32 CAM");
    }
    delay(2000);

    ultimaPaletaSeleccionada = -1;   // Fuerza que el próximo movimiento del potenciómetro redibuje, aunque vuelva a la misma paleta
    dibujarPantalla(vibe, dither);
  }

  delay(50);   // Pequeña pausa entre vueltas del loop, suficiente para no perder eventos del botón
}
