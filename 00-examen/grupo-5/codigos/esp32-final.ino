// =================================================================
// FIRMWARE ESP32-CAM - ARCHIVO RETRO
// Recibe disparos vía WiFi (HTTP), captura foto, aplica dithering
// estilo GameBoy y la sube a Google Drive. Sin dependencia de SD.
// =================================================================

#pragma GCC optimize ("Os")   // Compila priorizando tamaño de código sobre velocidad (más espacio libre en flash)

// ──────────────────────────────────────────────
// LIBRERÍAS
// ──────────────────────────────────────────────
#include "esp_camera.h"          // Driver de bajo nivel de la cámara OV2640 del AI-Thinker
#include <WiFi.h>                 // Conexión WiFi del ESP32
#include <WiFiUdp.h>               // Envío de paquetes UDP (usado para el beacon de descubrimiento)
#include <WiFiClientSecure.h>      // Cliente TCP con TLS (necesario para hablar HTTPS con Google)
#include <HTTPClient.h>            // Cliente HTTP de alto nivel, construido sobre WiFiClientSecure
#include <WebServer.h>             // Servidor HTTP local: aquí escuchamos /foto y /ping
#include "base64.h"                // Codificación Base64 de la imagen antes de mandarla a Drive
#include "img_converters.h"        // Conversión JPEG <-> RGB888 (fmt2rgb888 / fmt2jpg_cb)

// ──────────────────────────────────────────────
// PINES DE LA CÁMARA (mapeo fijo de la placa AI-Thinker ESP32-CAM)
// ──────────────────────────────────────────────
#define PWDN_GPIO_NUM     32   // Power-down de la cámara (no se usa en este diseño, queda en -1 lógicamente activo)
#define RESET_GPIO_NUM    -1   // Reset por hardware: no conectado, se deja en -1
#define XCLK_GPIO_NUM      0   // Reloj externo que alimenta el sensor de imagen
#define SIOD_GPIO_NUM     26   // I2C (SCCB) data: configuración del sensor
#define SIOC_GPIO_NUM     27   // I2C (SCCB) clock
#define Y9_GPIO_NUM       35   // Bus de datos paralelo de la cámara (8 bits): bit más significativo
#define Y8_GPIO_NUM       34
#define Y7_GPIO_NUM       39
#define Y6_GPIO_NUM       36
#define Y5_GPIO_NUM       21
#define Y4_GPIO_NUM       19
#define Y3_GPIO_NUM       18
#define Y2_GPIO_NUM        5   // Bit menos significativo del bus de datos
#define VSYNC_GPIO_NUM    25   // Sincronización vertical (fin de frame)
#define HREF_GPIO_NUM     23   // Sincronización horizontal (fin de línea)
#define PCLK_GPIO_NUM     22   // Reloj de píxel: marca cuándo el dato en el bus es válido

#define FLASH_LED_GPIO     4   // LED flash integrado de la placa, usado como aviso visual antes de disparar

// ──────────────────────────────────────────────
// CONFIGURACIÓN DE RED Y DESTINO DE SUBIDA
// ──────────────────────────────────────────────
const char* ssid     = "wenakiara";     // Nombre de la red WiFi a la que se conecta la cámara
const char* password = "tomas123";       // Contraseña de esa red
// URL del Google Apps Script que recibe la foto en base64 y la guarda en Drive
const String googleURL = "https://script.google.com/macros/s/AKfycbyvQm-MzpV4M_O-vw3rFW_cZa7HXK9S0TFa6U3f8l3oABs8XjHHbX2hDSWR2d_CrZQH/exec";

int numeroFoto = 1;   // Contador correlativo que se incluye en el nombre del archivo subido

// ──────────────────────────────────────────────
// ESTADO DEL DISPARO PENDIENTE
// El handler HTTP solo guarda estos valores y responde al instante;
// el procesamiento pesado (captura + dither + subida) ocurre en loop(),
// para no bloquear el socket TCP mientras se hace todo el trabajo.
// ──────────────────────────────────────────────
bool hayDisparosPendiente = false;   // Bandera: ¿hay un disparo esperando ser procesado?
String pendingVibe   = "";           // Paleta solicitada en el último POST /foto
String pendingDither = "";           // Algoritmo de dither solicitado
int    pendingBlock  = 8;            // Tamaño de bloque (solo relevante si el dither es "block")

WebServer server(80);   // Servidor HTTP escuchando en el puerto 80

WiFiUDP udpBeacon;                 // Socket UDP usado para anunciarse en la red
unsigned long ultimoBeacon = 0;    // Marca de tiempo del último beacon enviado
const int UDP_PORT = 4210;         // Puerto UDP compartido con el Arduino controlador

// ──────────────────────────────────────────────
// PALETAS DE COLOR ESTILO GAMEBOY
// Cada paleta tiene exactamente 4 colores (como las 4 tonalidades
// de gris/verde de una GameBoy real). El dither siempre termina
// mapeando cada píxel a uno de estos 4 colores.
// ──────────────────────────────────────────────
struct RGB { uint8_t r, g, b; };
#define PAL_COLORS 4

const RGB PAL_WISH_GB[PAL_COLORS]   = {{0x62,0x2E,0x4C},{0x75,0x50,0xE8},{0x60,0x8F,0xCF},{0x8B,0xE5,0xFF}};
const RGB PAL_KIROKAZE[PAL_COLORS]  = {{0x33,0x2C,0x50},{0x46,0x87,0x8F},{0x94,0xE3,0x44},{0x12,0xF3,0xE4}};
const RGB PAL_AYY4[PAL_COLORS]      = {{0x00,0x30,0x3B},{0xFF,0x77,0x77},{0xFF,0xCE,0x96},{0xF1,0xF2,0xDA}};
const RGB PAL_ICE_CREAM[PAL_COLORS] = {{0x7C,0x3F,0x58},{0xEB,0x6B,0x6F},{0xF9,0xA8,0x75},{0xFF,0xF6,0xD3}};
const RGB PAL_HOLLOW[PAL_COLORS]    = {{0x0F,0x0F,0x1B},{0x56,0x5A,0x75},{0xC6,0xB7,0xBE},{0xFA,0xFB,0xF6}};
const RGB PAL_CRIMSON[PAL_COLORS]   = {{0x1B,0x03,0x26},{0x7A,0x1C,0x4B},{0xBA,0x50,0x44},{0xEF,0xF9,0xD6}};

// ──────────────────────────────────────────────
// MATRICES DE UMBRAL PARA DITHER ORDENADO
// Cada número es un umbral relativo de brillo dentro del patrón.
// ──────────────────────────────────────────────
const uint8_t MAT_ORDERED2[4]   = { 0, 2, 3, 1 };                                              // Matriz 2x2 (Bayer de orden 1)
const uint8_t MAT_BAYER4[16]    = { 0, 8, 2, 10, 12, 4, 14, 6, 3, 11, 1, 9, 15, 7, 13, 5 };     // Matriz de Bayer 4x4 clásica
const uint8_t MAT_HALFTONE4[16] = { 12, 5, 6, 13, 4, 0, 1, 7, 11, 3, 2, 8, 15, 10, 9, 14 };     // Patrón circular tipo trama de imprenta

// Tipos de dither soportados (debe mantenerse sincronizado con dithersNombres[] del Arduino controlador)
enum DitherType {
  DITH_NEAREST, DITH_BLOCK, DITH_BAYER, DITH_ORDERED2,
  DITH_HALFTONE, DITH_FLOYD, DITH_ATKINSON, DITH_SIERRA_LITE, DITH_RANDOM
};

// Convierte el string recibido por HTTP (ej. "floyd-steinberg") al enum interno
DitherType ditherFromName(String name) {
  name.toLowerCase(); name.trim();                                        // Normaliza mayúsculas y espacios
  if (name == "nearest")                            return DITH_NEAREST;
  if (name == "block")                              return DITH_BLOCK;
  if (name == "bayer")                              return DITH_BAYER;
  if (name == "ordered2" || name == "ordered2x2")  return DITH_ORDERED2;
  if (name == "halftone")                           return DITH_HALFTONE;
  if (name == "floyd" || name == "floyd-steinberg") return DITH_FLOYD;
  if (name == "atkinson")                           return DITH_ATKINSON;
  if (name == "sierra" || name == "sierra-lite" || name == "sierralite") return DITH_SIERRA_LITE;
  if (name == "random")                             return DITH_RANDOM;
  return DITH_BAYER;   // Valor por defecto si no coincide con nada
}

// Convierte el enum a un nombre legible, usado en el nombre del archivo subido a Drive
String ditherToName(DitherType d) {
  switch (d) {
    case DITH_NEAREST:     return "Nearest";
    case DITH_BLOCK:       return "Block";
    case DITH_BAYER:       return "Bayer";
    case DITH_ORDERED2:    return "Ordered2x2";
    case DITH_HALFTONE:    return "Halftone";
    case DITH_FLOYD:       return "Floyd";
    case DITH_ATKINSON:    return "Atkinson";
    case DITH_SIERRA_LITE: return "SierraLite";
    case DITH_RANDOM:      return "Random";
  }
  return "Bayer";
}

// ──────────────────────────────────────────────
// MOTOR DE DITHERING
// Todas las funciones reciben el buffer RGB888 "en sitio" (lo modifican
// directamente) y devuelven cada píxel mapeado a uno de los 4 colores
// de la paleta activa.
// ──────────────────────────────────────────────

// Busca, dentro de la paleta de 4 colores, cuál está más cerca (distancia euclidiana al cuadrado) del color RGB dado
RGB nearestPaletteColor(int r, int g, int b, const RGB* pal) {
  int bestIdx = 0; long bestDist = LONG_MAX;
  for (int i = 0; i < PAL_COLORS; i++) {
    long dr=r-pal[i].r, dg=g-pal[i].g, db=b-pal[i].b;
    long dist = dr*dr + dg*dg + db*db;          // No hace falta raíz cuadrada: solo se compara, no se usa el valor
    if (dist < bestDist) { bestDist = dist; bestIdx = i; }
  }
  return pal[bestIdx];
}

// Dither "nearest": cada píxel se reemplaza directamente por el color de paleta más cercano, sin difuminar el error
void applyNearestDither(uint8_t* p, int w, int h, const RGB* pal) {
  for (int y = 0; y < h; y++) { yield();   // yield() cede tiempo al watchdog del ESP32 para que no se reinicie por timeout
    for (int x = 0; x < w; x++) {
      int i = (y*w+x)*3;                   // Índice del píxel dentro del buffer plano (3 bytes: R, G, B)
      RGB m = nearestPaletteColor(p[i], p[i+1], p[i+2], pal);
      p[i]=m.r; p[i+1]=m.g; p[i+2]=m.b;
    }
  }
}

// Dither "block": promedia bloques de bs×bs píxeles y pinta todo el bloque del color resultante (efecto pixel-art grueso)
void applyBlockDither(uint8_t* p, int w, int h, const RGB* pal, int bs) {
  if (bs < 1) bs = 1;                       // Protección: un bloque de tamaño 0 dividiría por cero
  for (int by = 0; by < h; by += bs) { yield();
    for (int bx = 0; bx < w; bx += bs) {
      long sR=0,sG=0,sB=0; int cnt=0;
      int mY=min(by+bs,h), mX=min(bx+bs,w);   // Evita salirse del borde en bloques incompletos al final de la imagen
      for (int y=by;y<mY;y++) for (int x=bx;x<mX;x++) {
        int i=(y*w+x)*3; sR+=p[i]; sG+=p[i+1]; sB+=p[i+2]; cnt++;
      }
      RGB m = nearestPaletteColor(sR/cnt, sG/cnt, sB/cnt, pal);   // Color promedio del bloque, mapeado a la paleta
      for (int y=by;y<mY;y++) for (int x=bx;x<mX;x++) {
        int i=(y*w+x)*3; p[i]=m.r; p[i+1]=m.g; p[i+2]=m.b;        // Se pinta todo el bloque con ese único color
      }
    }
  }
}

// Dither ordenado: aplica un umbral distinto por posición (x,y) según la matriz, antes de mapear a la paleta.
// Sirve tanto para "bayer" como "ordered2x2" y "halftone", solo cambia la matriz que se le pasa.
void applyOrderedDither(uint8_t* p, int w, int h, const RGB* pal, const uint8_t* mat, int ms, int mm) {
  for (int y = 0; y < h; y++) { yield();
    for (int x = 0; x < w; x++) {
      int i=(y*w+x)*3;
      int off = (mat[(y%ms)*ms+(x%ms)] * 255 / (mm+1)) - 127;     // Desplazamiento de brillo según la posición en la matriz
      RGB m = nearestPaletteColor(
        constrain(p[i]+off,0,255),
        constrain(p[i+1]+off,0,255),
        constrain(p[i+2]+off,0,255), pal);
      p[i]=m.r; p[i+1]=m.g; p[i+2]=m.b;
    }
  }
}

// Pesos de propagación de error para los dithers de difusión (Floyd-Steinberg, Atkinson, Sierra Lite)
struct ErrWeight { int dx, dy, num, den; };   // dx,dy: posición relativa del vecino. num/den: fracción del error que recibe.

// Dither por difusión de error: el error de cuantización de cada píxel se reparte entre los vecinos siguientes,
// logrando una transición más suave que el dither ordenado.
void applyErrorDiffusion(uint8_t* p, int w, int h, const RGB* pal, DitherType type) {
  // Buffer de error en PSRAM (no en RAM interna: una imagen QVGA×3 canales no entraría en la RAM normal del ESP32)
  int16_t* err = (int16_t*)ps_calloc((size_t)w*h*3, sizeof(int16_t));
  if (!err) { applyNearestDither(p, w, h, pal); return; }   // Si no hay memoria, degrada a nearest en vez de crashear

  ErrWeight wt[6]; int nw = 0;
  if (type == DITH_FLOYD) {
    // Floyd-Steinberg: reparte el error a 4 vecinos (derecha, y tres en la fila de abajo)
    wt[0]={1,0,7,16}; wt[1]={-1,1,3,16}; wt[2]={0,1,5,16}; wt[3]={1,1,1,16}; nw=4;
  } else if (type == DITH_ATKINSON) {
    // Atkinson: reparte solo 6/8 del error (más contraste, menos "manchado")
    wt[0]={1,0,1,8}; wt[1]={2,0,1,8}; wt[2]={-1,1,1,8};
    wt[3]={0,1,1,8}; wt[4]={1,1,1,8}; wt[5]={0,2,1,8}; nw=6;
  } else {
    // Sierra Lite: versión simplificada de 3 vecinos
    wt[0]={1,0,2,4}; wt[1]={-1,1,1,4}; wt[2]={0,1,1,4}; nw=3;
  }

  for (int y=0;y<h;y++) { yield();
    for (int x=0;x<w;x++) {
      int i=(y*w+x)*3;
      // Color original + error acumulado que le llegó de píxeles ya procesados
      int oR=constrain(p[i]+err[i],0,255);
      int oG=constrain(p[i+1]+err[i+1],0,255);
      int oB=constrain(p[i+2]+err[i+2],0,255);
      RGB m = nearestPaletteColor(oR,oG,oB,pal);
      p[i]=m.r; p[i+1]=m.g; p[i+2]=m.b;
      // Error que se "pierde" al cuantizar: se reparte hacia adelante según los pesos
      int eR=oR-m.r, eG=oG-m.g, eB=oB-m.b;
      for (int k=0;k<nw;k++) {
        int nx=x+wt[k].dx, ny=y+wt[k].dy;
        if (nx<0||nx>=w||ny<0||ny>=h) continue;   // Ignora vecinos fuera del borde de la imagen
        int ni=(ny*w+nx)*3;
        err[ni]  +=(int16_t)((long)eR*wt[k].num/wt[k].den);
        err[ni+1]+=(int16_t)((long)eG*wt[k].num/wt[k].den);
        err[ni+2]+=(int16_t)((long)eB*wt[k].num/wt[k].den);
      }
    }
  }
  free(err);   // Libera el buffer de error en PSRAM
}

// Dither "random": agrega ruido aleatorio antes de cuantizar, dando un efecto granulado tipo film
void applyRandomDither(uint8_t* p, int w, int h, const RGB* pal) {
  for (int y=0;y<h;y++) { yield();
    for (int x=0;x<w;x++) {
      int i=(y*w+x)*3, off=random(-64,65);    // Ruido aleatorio entre -64 y +64
      RGB m = nearestPaletteColor(
        constrain(p[i]+off,0,255),
        constrain(p[i+1]+off,0,255),
        constrain(p[i+2]+off,0,255), pal);
      p[i]=m.r; p[i+1]=m.g; p[i+2]=m.b;
    }
  }
}

// Despachador central: según el tipo de dither, llama a la función correspondiente
void applyDither(uint8_t* p, int w, int h, const RGB* pal, DitherType type, int bs) {
  switch (type) {
    case DITH_NEAREST:     applyNearestDither(p,w,h,pal); break;
    case DITH_BLOCK:       applyBlockDither(p,w,h,pal,bs); break;
    case DITH_BAYER:       applyOrderedDither(p,w,h,pal,MAT_BAYER4,4,15); break;
    case DITH_ORDERED2:    applyOrderedDither(p,w,h,pal,MAT_ORDERED2,2,3); break;
    case DITH_HALFTONE:    applyOrderedDither(p,w,h,pal,MAT_HALFTONE4,4,15); break;
    case DITH_FLOYD:
    case DITH_ATKINSON:
    case DITH_SIERRA_LITE: applyErrorDiffusion(p,w,h,pal,type); break;
    case DITH_RANDOM:      applyRandomDither(p,w,h,pal); break;
  }
}

// Convierte el nombre de "vibe" recibido por HTTP al puntero de la paleta correspondiente.
// IMPORTANTE: estos strings deben coincidir EXACTAMENTE con paletasNombres[] del Arduino controlador.
const RGB* selectPalette(const String& v) {
  if (v=="wish-gb")          return PAL_WISH_GB;
  if (v=="kirokaze-gb")      return PAL_KIROKAZE;   // Corregido: antes era "kirokaze-gameboy", ahora coincide con el controlador
  if (v=="ayy4")             return PAL_AYY4;
  if (v=="ice-cream-gb")     return PAL_ICE_CREAM;
  if (v=="hollow")           return PAL_HOLLOW;
  if (v=="crimson")          return PAL_CRIMSON;
  return PAL_WISH_GB;   // Paleta por defecto si no hay coincidencia
}

// ──────────────────────────────────────────────
// UTILIDADES DE CODIFICACIÓN Y FORMATO
// ──────────────────────────────────────────────

// Acumulador donde fmt2jpg_cb va escribiendo el JPEG recodificado, bloque por bloque
struct JpegAccum { uint8_t* buf; size_t len; };
static size_t jpegWriteCb(void* arg, size_t, const void* data, size_t len) {
  JpegAccum* a = (JpegAccum*)arg;
  uint8_t* nb = (uint8_t*)realloc(a->buf, a->len+len);   // Crece el buffer dinámicamente con cada bloque
  if (!nb) return 0;                                      // Si falla la realocación, aborta la codificación
  a->buf=nb; memcpy(a->buf+a->len,data,len); a->len+=len; return len;
}

// Formatea el contador de foto a 4 dígitos con ceros a la izquierda (0001, 0002, ...)
String fourDigit(int v) {
  if (v<10)   return "000"+String(v);
  if (v<100)  return "00"+String(v);
  if (v<1000) return "0"+String(v);
  return String(v);
}

// URL-encode mínimo: solo escapa los caracteres que romperían el payload application/x-www-form-urlencoded
String urlEncodeValue(const String& input) {
  String out=""; out.reserve(input.length()*3);   // Reserva de más para evitar realocaciones mientras crece el string
  for (int i=0;i<(int)input.length();i++) {
    char c=input.charAt(i);
    if      (c=='+') out+="%2B";
    else if (c=='/') out+="%2F";
    else if (c=='=') out+="%3D";
    else if (c=='&') out+="%26";
    else if (c=='#') out+="%23";
    else if (c=='?') out+="%3F";
    else if (c==' ') out+="%20";
    else             out+=c;   // El resto de caracteres se deja sin tocar
  }
  return out;
}

// Parpadea el flash 3 veces antes de capturar, como aviso visual de "foto en camino"
void avisoFlash() {
  for (int i=0;i<3;i++) {
    digitalWrite(FLASH_LED_GPIO,HIGH); delay(120);
    digitalWrite(FLASH_LED_GPIO,LOW);  delay(120); yield();
  }
}

// ──────────────────────────────────────────────
// PIPELINE PRINCIPAL: captura → dither → subida a Drive
// Se ejecuta desde loop(), nunca desde el handler HTTP directamente.
// ──────────────────────────────────────────────
String procesarYsubirFoto(String vibe, String ditherName, int blockSize) {
  Serial.println("\n=== [DISPARO RECIBIDO via WiFi] ===");
  Serial.println("[1] Parseando dither: " + ditherName);
  DitherType ditherType = ditherFromName(ditherName);

  Serial.println("[2] Ejecutando flash...");
  avisoFlash();

  Serial.println("[3] Capturando frame de cámara...");
  camera_fb_t* fb = esp_camera_fb_get();          // Toma un frame JPEG directo del sensor
  if (!fb) {
    Serial.println("[ERROR] Fallo al capturar imagen.");
    return "ERROR|CAM";
  }
  Serial.printf("[4] Frame capturado: %dx%d, %d bytes\n", fb->width, fb->height, fb->len);
  int imgW=fb->width, imgH=fb->height;

  Serial.println("[5] Allocando buffer RGB en PSRAM...");
  // Se necesita el frame en RGB888 (3 bytes/píxel) para poder ditherizarlo píxel a píxel
  uint8_t* rgbBuf = (uint8_t*)ps_malloc((size_t)imgW*imgH*3);
  if (!rgbBuf) {
    Serial.println("[ERROR] Sin memoria PSRAM para RGB.");
    esp_camera_fb_return(fb); return "ERROR|MEM";   // Libera el frame original aunque falle la asignación
  }
  Serial.printf("[6] Buffer RGB OK (%d bytes). Decodificando JPEG...\n", imgW*imgH*3);
  bool decoded = fmt2rgb888(fb->buf, fb->len, PIXFORMAT_JPEG, rgbBuf);   // Decodifica el JPEG capturado a RGB888
  esp_camera_fb_return(fb);                                              // El frame JPEG original ya no se necesita
  if (!decoded) {
    Serial.println("[ERROR] Fallo al decodificar JPEG a RGB.");
    free(rgbBuf); return "ERROR|DECODE";
  }

  Serial.println("[7] JPEG decodificado OK. Aplicando dither...");
  applyDither(rgbBuf, imgW, imgH, selectPalette(vibe), ditherType, blockSize);

  Serial.println("[8] Dither aplicado. Recodificando a JPEG...");
  yield();
  JpegAccum jpegOut = {NULL, 0};
  // Recodifica el resultado ditherizado a JPEG (calidad 90) para que ocupe menos al subirlo
  bool encoded = fmt2jpg_cb(rgbBuf, (size_t)imgW*imgH*3, imgW, imgH, PIXFORMAT_RGB888, 90, jpegWriteCb, &jpegOut);
  free(rgbBuf);   // El buffer RGB crudo ya no se necesita una vez generado el JPEG
  if (!encoded || !jpegOut.buf) {
    Serial.println("[ERROR] Fallo al recodificar a JPEG.");
    return "ERROR|ENCODE";
  }
  Serial.printf("[9] JPEG recodificado OK (%d bytes). Generando base64...\n", jpegOut.len);

  // Nombre final del archivo: "0001 - Pics - wish-gb - Floyd.jpg"
  String nombreOficial = fourDigit(numeroFoto) + " - Pics - " + vibe + " - " + ditherToName(ditherType) + ".jpg";
  String base64Safe  = urlEncodeValue(base64::encode(jpegOut.buf, jpegOut.len));   // Imagen codificada lista para enviar por POST
  free(jpegOut.buf);   // El JPEG crudo ya está copiado en el string base64, se libera

  Serial.printf("[10] Base64 generado (%d chars). Construyendo payload...\n", base64Safe.length());
  String nombreSafe  = urlEncodeValue(nombreOficial);
  String formPayload = "token=Pangataloca&filename=" + nombreSafe + "&base64=" + base64Safe;

  Serial.printf("[11] Payload listo (%d bytes). Conectando a Google...\n", formPayload.length());
  WiFiClientSecure clientSecure;
  clientSecure.setInsecure();   // No valida el certificado del servidor (simplifica, a costa de seguridad TLS estricta)
  HTTPClient http;
  http.begin(clientSecure, googleURL);
  http.setTimeout(30000);
  http.addHeader("Content-Type","application/x-www-form-urlencoded");
  http.setFollowRedirects(HTTPC_DISABLE_FOLLOW_REDIRECTS);   // Los redirects se manejan a mano más abajo

  Serial.println("[12] Enviando POST a Google Script...");
  int httpCode = http.POST(formPayload);
  Serial.printf("[13] Respuesta HTTP inicial: %d\n", httpCode);

  // Google Apps Script normalmente responde con una redirección 302 hacia la URL real de resultado;
  // hay que seguirla manualmente con un GET para confirmar que la subida terminó bien.
  if (httpCode == 301 || httpCode == 302 || httpCode == 307 || httpCode == 308) {
    String redir = http.getLocation();
    http.end();
    Serial.println("[14] Redireccion detectada, siguiendo con GET a: " + redir);
    if (redir.length() > 10) {
      http.begin(clientSecure, redir);
      http.setTimeout(15000);
      httpCode = http.GET();
      Serial.printf("[15] Respuesta tras redireccion (GET): %d\n", httpCode);
    }
  }
  http.end();

  if (httpCode == 200 || httpCode == 201) {
    Serial.println("[OK] ¡Subida exitosa!");
    numeroFoto++;   // Solo avanza el contador si la subida fue exitosa
    return "DONE";
  }
  Serial.println("[ERROR] Subida fallida. Codigo HTTP: " + String(httpCode));
  return "ERROR|HTTP:" + String(httpCode);
}

// ──────────────────────────────────────────────
// HANDLERS HTTP
// El handler de /foto retorna en microsegundos: solo guarda los
// parámetros recibidos y deja la bandera lista para que loop()
// haga el trabajo pesado fuera del contexto del socket TCP.
// ──────────────────────────────────────────────
void handleFoto() {
  // Lee los parámetros del POST, con valores por defecto si el Arduino no los manda
  pendingVibe   = server.hasArg("vibe")   ? server.arg("vibe")        : "wish-gb";
  pendingDither = server.hasArg("dither") ? server.arg("dither")      : "bayer";
  pendingBlock  = server.hasArg("block")  ? server.arg("block").toInt(): 8;

  hayDisparosPendiente = true;   // Marca el disparo para que loop() lo procese en la próxima vuelta

  // Responde de inmediato para liberar el socket; el Arduino interpreta "PROCESSING" como ACK de éxito
  server.send(200, "text/plain", "PROCESSING");
  Serial.println("[HTTP] Disparo encolado, conexion liberada.");
}

// Endpoint simple usado por el Arduino para verificar que la cámara está viva antes de disparar
void handlePing() {
  server.send(200, "text/plain", "ARCHIVO-RETRO-CAM-OK");
}

// ──────────────────────────────────────────────
// SETUP
// ──────────────────────────────────────────────
void setup() {
  Serial.begin(115200);
  delay(1000);                 // Da tiempo a que el monitor serie se conecte antes de imprimir nada
  randomSeed(esp_random());    // Semilla aleatoria real (hardware RNG) para el dither "random"

  pinMode(FLASH_LED_GPIO, OUTPUT);
  digitalWrite(FLASH_LED_GPIO, LOW);

  // ---- Configuración de pines y parámetros de la cámara ----
  camera_config_t config;
  config.ledc_channel = LEDC_CHANNEL_0; config.ledc_timer = LEDC_TIMER_0;   // Canal PWM usado para generar el reloj XCLK
  config.pin_d0=Y2_GPIO_NUM; config.pin_d1=Y3_GPIO_NUM;
  config.pin_d2=Y4_GPIO_NUM; config.pin_d3=Y5_GPIO_NUM;
  config.pin_d4=Y6_GPIO_NUM; config.pin_d5=Y7_GPIO_NUM;
  config.pin_d6=Y8_GPIO_NUM; config.pin_d7=Y9_GPIO_NUM;
  config.pin_xclk=XCLK_GPIO_NUM; config.pin_pclk=PCLK_GPIO_NUM;
  config.pin_vsync=VSYNC_GPIO_NUM; config.pin_href=HREF_GPIO_NUM;
  config.pin_sscb_sda=SIOD_GPIO_NUM; config.pin_sscb_scl=SIOC_GPIO_NUM;
  config.pin_pwdn=PWDN_GPIO_NUM; config.pin_reset=RESET_GPIO_NUM;
  config.xclk_freq_hz=10000000;            // 10 MHz: frecuencia segura para evitar artefactos con este sensor
  config.pixel_format=PIXFORMAT_JPEG;      // El sensor entrega JPEG directamente (se decodifica después para ditherizar)
  config.frame_size=FRAMESIZE_QVGA;        // 320x240 — buen balance entre detalle y tiempo de procesamiento
  config.jpeg_quality=10;                  // Escala 0-63 en este driver: 10 es alta calidad de captura inicial
  config.fb_count=1;                       // Un solo framebuffer (suficiente porque se procesa de a una foto)
  config.fb_location=CAMERA_FB_IN_PSRAM;   // El framebuffer vive en PSRAM, no en la RAM interna limitada

  esp_err_t err = esp_camera_init(&config);
  if (err != ESP_OK) {
    // Falla crítica: sin cámara no hay nada que hacer. Queda parpadeando el flash como indicador de error.
    Serial.printf("[ERROR CRITICO] Camara no inicializada: 0x%x\n", err);
    while(true) {
      digitalWrite(FLASH_LED_GPIO, HIGH); delay(200);
      digitalWrite(FLASH_LED_GPIO, LOW);  delay(200);
    }
  }
  Serial.println("[CAM] Camara inicializada correctamente.");

  if (!psramFound()) {
    // Sin PSRAM no hay espacio para los buffers RGB de la imagen completa: parpadeo rápido distinto como diagnóstico
    Serial.println("[ERROR] PSRAM no detectada.");
    while(true) {
      digitalWrite(FLASH_LED_GPIO, HIGH); delay(50);
      digitalWrite(FLASH_LED_GPIO, LOW);  delay(50);
    }
  }
  Serial.printf("[MEM] PSRAM total: %d bytes\n", ESP.getPsramSize());

  WiFi.begin(ssid, password);
  Serial.print("[WIFI] Conectando");
  while (WiFi.status() != WL_CONNECTED) { delay(500); Serial.print("."); }
  Serial.println("\n[WIFI] ¡Conectado!");

  udpBeacon.begin(UDP_PORT);

  server.on("/foto", HTTP_POST, handleFoto);   // Recibe el disparo desde el Arduino
  server.on("/ping", HTTP_GET,  handlePing);   // Chequeo de salud antes de cada disparo
  server.begin();
  Serial.println("[HTTP] Servidor listo en puerto 80 sin dependencia de SD.");
}

// ──────────────────────────────────────────────
// LOOP PRINCIPAL
// Funciona como una pequeña máquina de estados: atiende HTTP,
// procesa el disparo encolado, vigila la conexión WiFi y emite
// el beacon UDP periódico para que el Arduino descubra la IP.
// ──────────────────────────────────────────────
void loop() {
  // 1) Atiende peticiones HTTP entrantes (debe llamarse seguido para no perder conexiones)
  server.handleClient();
  yield();

  // 2) Si hay un disparo pendiente, se procesa aquí —fuera del handler HTTP— para no bloquear el socket
  if (hayDisparosPendiente) {
    hayDisparosPendiente = false;
    Serial.println("[LOOP] Procesando disparo encolado...");

    String resultado = procesarYsubirFoto(pendingVibe, pendingDither, pendingBlock);
    Serial.println("[LOOP] Resultado Final: " + resultado);
  }

  // 3) Watchdog de reconexión: si se cae el WiFi, reintenta hasta 10s y reinicia el servidor HTTP
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("[WIFI] Reconectando...");
    WiFi.disconnect();
    WiFi.begin(ssid, password);
    unsigned long t0 = millis();
    while (WiFi.status() != WL_CONNECTED && millis() - t0 < 10000) {
      delay(500); Serial.print(".");
    }
    if (WiFi.status() == WL_CONNECTED) {
      Serial.println("\n[WIFI] Reconectado con exito.");
      server.begin();   // El servidor debe reiniciarse tras perder y recuperar la conexión
    }
  }

  // 4) Beacon UDP cada 5 segundos: anuncia la IP actual por broadcast para que el Arduino la descubra sin configurarla a mano
  if (millis() - ultimoBeacon > 5000) {
    ultimoBeacon = millis();
    Serial.printf("[MEM] Heap libre: %d | PSRAM libre: %d\n", ESP.getFreeHeap(), ESP.getFreePsram());

    String msg = "ARCHIVO-RETRO-CAM:" + WiFi.localIP().toString();
    udpBeacon.beginPacket(IPAddress(255,255,255,255), UDP_PORT);   // Broadcast a toda la subred
    udpBeacon.print(msg);
    udpBeacon.endPacket();
    Serial.println("[UDP] Beacon enviado: " + msg);
  }
}
