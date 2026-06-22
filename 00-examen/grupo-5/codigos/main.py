# ============================================================
# main.py — ARCHIVO RETRO
# Visor de fotos para Raspberry Pi Pico W con MicroPython Pimoroni.
# Descarga imagenes JPEG desde una carpeta de Google Drive,
# las guarda en una tarjeta SD y las muestra en una pantalla TFT.
# Los botones permiten navegar entre fotos manualmente.
# ============================================================


# ─────────────────────────────────────────────────────────────
# IMPORTS
# ─────────────────────────────────────────────────────────────

import os        # operaciones de sistema de archivos (listdir, mkdir, stat, mount)
import time      # funciones de tiempo: sleep, time(), sleep_ms()
import network   # control de la interfaz WiFi del Pico W
import socket    # conexiones TCP de bajo nivel para HTTP
import ssl       # envuelve sockets TCP en TLS para HTTPS
import ujson as json  # version liviana de JSON para MicroPython

from machine import Pin, SPI          # control de pines GPIO y bus SPI
from pimoroni_bus import SPIBus       # bus SPI de alto nivel de Pimoroni para la pantalla
from picographics import PicoGraphics, DISPLAY_PICO_DISPLAY_2, PEN_RGB565
                                      # libreria grafica de Pimoroni: display, tipo de pantalla y formato de color
import jpegdec    # decodificador JPEG de Pimoroni/BitBank, escribe directo al framebuffer
from sdcard import SDCard             # driver MicroPython para tarjetas SD via SPI


# ─────────────────────────────────────────────────────────────
# CONFIGURACION DE RED Y GOOGLE DRIVE
# ─────────────────────────────────────────────────────────────

WIFI_SSID        = "wenakiara"                      # nombre de la red WiFi a conectar
WIFI_PASS        = "tomas123"                       # contrasena de la red WiFi
GDRIVE_FOLDER_ID = "1SUIurSYrSJvULb5bxX92DnnLRRc22yIt"  # ID de la carpeta de Google Drive con las fotos
GOOGLE_API_KEY   = "AIzaSyB1jQ1CmLxIgNyUrw2aSETBW3ScH-AWnD8"  # clave de API de Google para Drive v3

CHECK_EVERY_SEC  = 10                # segundos entre cada revision de fotos nuevas en Drive
JPEG_SCALE       = jpegdec.JPEG_SCALE_FULL  # escala de decodificacion JPEG: FULL = resolucion original


# ─────────────────────────────────────────────────────────────
# PINES GPIO
# ─────────────────────────────────────────────────────────────

# Pantalla TFT ST7789V via SPI0
TFT_CS   = 10   # Chip Select: activa la pantalla en el bus SPI
TFT_DC   = 11   # Data/Command: indica si el byte enviado es dato o comando
TFT_RST  = 12   # Reset: reinicia el controlador ST7789V al arrancar
TFT_BL   = 14   # Backlight: controla el brillo de la retroiluminacion por PWM
TFT_MOSI = 19   # Master Out Slave In: linea de datos del Pico hacia la pantalla
TFT_SCK  = 18   # Clock: reloj del bus SPI0

# Tarjeta SD via SPI1
SD_SCK  = 26    # Clock del bus SPI1 para la SD
SD_MOSI = 27    # Datos del Pico hacia la SD
SD_MISO = 28    # Datos de la SD hacia el Pico
SD_CS   = 22    # Chip Select de la SD

# Botones de navegacion
BTN_NEXT_PIN = 5   # boton para avanzar a la siguiente foto
BTN_PREV_PIN = 6   # boton para retroceder a la foto anterior


# ─────────────────────────────────────────────────────────────
# CONSTANTES DE FUNCIONAMIENTO
# ─────────────────────────────────────────────────────────────

IMG_DIR      = "/sd/IMGS"   # ruta donde se guardan las fotos en la SD
MAX_IMAGES   = 500          # maximo de fotos que se cargan en la galeria
DEBOUNCE_MS  = 50           # milisegundos de espera para filtrar rebotes del boton
HTTP_TIMEOUT = 15           # segundos antes de abandonar una conexion HTTPS sin respuesta


# ─────────────────────────────────────────────────────────────
# RESET MANUAL DE LA PANTALLA
# Se hace antes de inicializar el bus SPI para garantizar que
# el controlador ST7789V arranca desde un estado limpio.
# ─────────────────────────────────────────────────────────────

_rst_pin = Pin(TFT_RST, Pin.OUT)  # configura el pin RST como salida digital
_rst_pin.value(0)                  # pone RST en bajo: inicia el reset del controlador
time.sleep_ms(100)                 # mantiene el reset 100ms para que sea efectivo
_rst_pin.value(1)                  # libera el reset: el controlador comienza a inicializarse
time.sleep_ms(100)                 # espera 100ms a que el controlador termine de arrancar


# ─────────────────────────────────────────────────────────────
# INICIALIZACION DE LA PANTALLA
# ─────────────────────────────────────────────────────────────

display_bus = SPIBus(cs=TFT_CS, dc=TFT_DC, sck=TFT_SCK, mosi=TFT_MOSI, bl=TFT_BL)
# SPIBus crea el canal SPI0 de Pimoroni con los pines de la pantalla

display = PicoGraphics(display=DISPLAY_PICO_DISPLAY_2, bus=display_bus, pen_type=PEN_RGB565, rotate=0)
# PicoGraphics es la libreria grafica: DISPLAY_PICO_DISPLAY_2 define resolucion 320x240,
# PEN_RGB565 usa 16 bits por pixel (65536 colores), rotate=0 es orientacion landscape

display.set_backlight(0.8)
# enciende la retroiluminacion al 80% de brillo (valor entre 0.0 y 1.0)


# ─────────────────────────────────────────────────────────────
# COLORES (pens)
# En PicoGraphics un "pen" es un color registrado internamente
# que se activa con set_pen() antes de dibujar.
# ─────────────────────────────────────────────────────────────

PEN_WHITE  = display.create_pen(255, 255, 255)  # blanco puro
PEN_BLACK  = display.create_pen(0,   0,   0  )  # negro puro
PEN_RED    = display.create_pen(255, 0,   0  )  # rojo para mensajes de error
PEN_CYAN   = display.create_pen(0,   255, 255)  # cian para textos destacados
PEN_YELLOW = display.create_pen(255, 255, 0  )  # amarillo (reservado para uso futuro)
PEN_GRAY   = display.create_pen(40,  40,  40 )  # gris muy oscuro para fondos de iconos
PEN_LGRAY  = display.create_pen(160, 160, 160)  # gris claro para textos secundarios


# ─────────────────────────────────────────────────────────────
# DECODIFICADOR JPEG Y ESTADO DE LA GALERIA
# ─────────────────────────────────────────────────────────────

jpeg = jpegdec.JPEG(display)
# crea el decodificador JPEG vinculado al framebuffer del display

gallery_names   = []     # lista de nombres de archivo de las fotos cargadas desde la SD
gallery_current = 0      # indice de la foto que se esta mostrando actualmente
sd_ok           = False  # flag: True si la SD se monto correctamente


# ─────────────────────────────────────────────────────────────
# FUENTE PIXEL ART PARA EL SPLASH
# Cada letra se define como una matriz de 5 columnas x 7 filas.
# '1' = pixel encendido, '0' = pixel apagado.
# _BLK define cuantos pixeles reales ocupa cada celda de la matriz.
# ─────────────────────────────────────────────────────────────

_FONT = {
    'A': ["01110","10001","10001","11111","10001","10001","10001"],
    'R': ["11110","10001","10001","11110","10100","10010","10001"],
    'C': ["01111","10000","10000","10000","10000","10000","01111"],
    'H': ["10001","10001","10001","11111","10001","10001","10001"],
    'I': ["11111","00100","00100","00100","00100","00100","11111"],
    'V': ["10001","10001","10001","10001","10001","01010","00100"],
    'O': ["01110","10001","10001","10001","10001","10001","01110"],
    'E': ["11111","10000","10000","11110","10000","10000","11111"],
    'T': ["11111","00100","00100","00100","00100","00100","00100"],
}

_BLK = 4   # cada celda de la matriz ocupa 4x4 pixeles reales en pantalla
_GAP = 1   # separacion entre letras expresada en celdas (1 celda = 4px)


def _draw_word(word, x0, y0, pen):
    # dibuja una palabra usando la fuente pixel art en la posicion (x0, y0)
    display.set_pen(pen)   # activa el color con el que se dibujaran los bloques
    cx = x0                # posicion horizontal actual, avanza letra a letra
    for ch in word:
        rows = _FONT.get(ch)           # obtiene la matriz de la letra actual
        if not rows:                   # si la letra no esta en el diccionario, deja espacio
            cx += (_BLK * 5) + _GAP * _BLK
            continue
        for row, bits in enumerate(rows):    # recorre cada fila de la matriz (7 filas)
            for col, b in enumerate(bits):   # recorre cada columna de la fila (5 columnas)
                if b == '1':                 # solo dibuja si la celda esta encendida
                    display.rectangle(
                        cx + col * _BLK,     # posicion x del bloque
                        y0 + row * _BLK,     # posicion y del bloque
                        _BLK, _BLK           # ancho y alto del bloque en pixeles
                    )
        cx += (_BLK * 5) + _GAP * _BLK      # avanza al inicio de la siguiente letra


def show_splash():
    # muestra la pantalla de bienvenida con el titulo ARCHIVO RETRO en pixel art
    display.set_pen(PEN_BLACK)
    display.clear()                           # limpia la pantalla con negro
    _draw_word("ARCHIVO", 38, 60, PEN_CYAN)  # dibuja "ARCHIVO" centrado, fila superior
    _draw_word("RETRO",   62, 100, PEN_CYAN) # dibuja "RETRO" centrado, fila inferior
    display.set_pen(PEN_LGRAY)
    display.rectangle(20, 148, 200, 1)        # linea horizontal decorativa debajo del titulo
    display.text("iniciando...", 10, 160, 240, 2)  # texto de estado debajo de la linea
    display.update()                          # envia el framebuffer a la pantalla
    time.sleep(2)                             # mantiene el splash visible 2 segundos


def show_msg(msg, pen=PEN_WHITE):
    # muestra un mensaje de texto centrado en pantalla negra
    # se usa para errores, estados de conexion y avisos generales
    display.set_pen(PEN_BLACK)
    display.clear()
    display.set_pen(pen)
    display.text(msg, 10, 100, 300, 2)  # x=10, y=100, wordwrap=300px, escala=2
    display.update()


# ─────────────────────────────────────────────────────────────
# ANIMACION DE DESCARGA
# show_downloading se llama varias veces durante la descarga
# para animar los puntos suspensivos en pantalla.
# _dl_frame lleva la cuenta del fotograma actual.
# ─────────────────────────────────────────────────────────────

_dl_frame = 0   # contador global de fotogramas de la animacion de descarga

def show_downloading(n):
    # muestra el estado de descarga con animacion de puntos suspensivos
    # n es el numero de foto que se esta descargando
    global _dl_frame
    frames = ["Descargando.  ", "Descargando.. ", "Descargando..."]
    display.set_pen(PEN_BLACK)
    display.clear()
    display.set_pen(PEN_CYAN)
    display.text(frames[_dl_frame % 3], 10, 95, 300, 2)  # cicla entre los 3 fotogramas
    display.set_pen(PEN_LGRAY)
    display.text("foto %d" % n, 10, 130, 300, 2)         # muestra el numero de foto
    display.update()
    _dl_frame += 1   # avanza al siguiente fotograma


# ─────────────────────────────────────────────────────────────
# ICONO DE CAMARA
# Se dibuja con rectangulos y circulos basicos.
# Aparece en la esquina inferior izquierda cuando llega una foto nueva.
# ─────────────────────────────────────────────────────────────

def draw_camera_icon(x, y):
    # cuerpo principal de la camara: rectangulo gris oscuro
    display.set_pen(PEN_GRAY)
    display.rectangle(x, y + 4, 24, 16)   # cuerpo horizontal
    display.rectangle(x + 8, y, 8, 5)     # protuberancia superior (visor)
    # lente: circulo negro exterior con circulo gris interior
    display.set_pen(PEN_BLACK)
    display.circle(x + 12, y + 12, 5)     # borde exterior del lente
    display.set_pen(PEN_LGRAY)
    display.circle(x + 12, y + 12, 3)     # interior del lente


# ─────────────────────────────────────────────────────────────
# TARJETA SD
# ─────────────────────────────────────────────────────────────

def init_sd():
    # intenta montar la tarjeta SD en /sd usando SPI1
    # prueba primero a 4 MHz y luego a 1 MHz porque algunos modulos
    # SD economicos no toleran velocidades altas durante la inicializacion
    global sd_ok
    for baud in (4_000_000, 1_000_000):
        try:
            spi = SPI(1, baudrate=baud, polarity=0, phase=0,
                      sck=Pin(SD_SCK), mosi=Pin(SD_MOSI), miso=Pin(SD_MISO))
            # SPI(1) usa el bus SPI1 del Pico W con los pines definidos arriba
            sd  = SDCard(spi, Pin(SD_CS))  # inicializa el protocolo de la SD
            vfs = os.VfsFat(sd)            # crea un sistema de archivos FAT sobre la SD
            os.mount(vfs, "/sd")           # monta el sistema de archivos en la ruta /sd
            sd_ok = True
            print("SD OK @ %d Hz" % baud)
            try:
                os.listdir(IMG_DIR)        # verifica si la carpeta de imagenes existe
            except OSError:
                os.mkdir(IMG_DIR)          # si no existe, la crea
            return
        except Exception as e:
            print("SD intento %d Hz: %s" % (baud, e))
    print("Error SD: no se pudo montar")
    sd_ok = False


# ─────────────────────────────────────────────────────────────
# WIFI
# ─────────────────────────────────────────────────────────────

def connect_wifi():
    # activa la interfaz WiFi en modo estacion (cliente) y se conecta a la red
    # espera hasta 15 segundos antes de abandonar
    wlan = network.WLAN(network.STA_IF)   # obtiene la interfaz WiFi en modo cliente
    wlan.active(True)                      # activa el hardware WiFi
    if not wlan.isconnected():
        wlan.connect(WIFI_SSID, WIFI_PASS) # inicia la conexion con las credenciales
        t0 = time.time()
        while not wlan.isconnected() and time.time() - t0 < 15:
            time.sleep(0.5)                # espera en bucle hasta conectar o agotar tiempo
    ok = wlan.isconnected()
    if ok:
        print("WiFi OK:", wlan.ifconfig()[0])  # imprime la IP asignada por DHCP
    return ok                              # devuelve True si la conexion fue exitosa


# ─────────────────────────────────────────────────────────────
# CLIENTE HTTPS
# Implementacion manual de HTTP/1.1 sobre TLS porque MicroPython
# no incluye un cliente HTTP completo. Soporta redireccionamiento,
# Content-Length y Transfer-Encoding chunked.
# ─────────────────────────────────────────────────────────────

def _readline(sock):
    # lee una linea del socket y la devuelve como string sin \r\n
    line = sock.readline()
    return "" if not line else line.decode().rstrip("\r\n")

def https_get(host, path, extra_headers=None, timeout=HTTP_TIMEOUT):
    # abre una conexion HTTPS al host dado y envia un GET al path dado
    # devuelve (codigo_estado, diccionario_headers, socket_abierto)
    # el socket queda abierto para que el llamador lea el cuerpo
    addr = socket.getaddrinfo(host, 443)[0][-1]  # resuelve el hostname a IP:puerto
    raw  = socket.socket()                         # crea un socket TCP
    raw.settimeout(timeout)                        # configura timeout de inactividad
    raw.connect(addr)                              # establece la conexion TCP
    s = ssl.wrap_socket(raw)                       # negocia TLS sobre el socket TCP

    # construye la peticion HTTP
    req = "GET %s HTTP/1.1\r\nHost: %s\r\nUser-Agent: Pico2W\r\nConnection: close\r\n" % (path, host)
    if extra_headers:
        for k, v in extra_headers.items():
            req += "%s: %s\r\n" % (k, v)   # agrega cabeceras adicionales si las hay
    req += "\r\n"
    s.write(req.encode())   # envia la peticion al servidor

    status_line = _readline(s)                          # lee la primera linea: "HTTP/1.1 200 OK"
    parts  = status_line.split(" ", 2)
    status = int(parts[1]) if len(parts) > 1 else 0    # extrae el codigo de estado numerico

    headers = {}
    while True:
        line = _readline(s)
        if line == "":
            break                              # linea vacia indica fin de los headers
        k, _, v = line.partition(":")
        headers[k.strip().lower()] = v.strip()  # guarda cada header en minusculas

    return status, headers, s

def _read_exact(sock, sink, n, bufsize=512):
    # lee exactamente n bytes del socket y los escribe en sink
    # sink puede ser un archivo abierto o un objeto _BytesSink
    total = 0
    buf   = bytearray(bufsize)   # buffer reutilizable de 512 bytes para no fragmentar RAM
    while total < n:
        want = min(bufsize, n - total)       # no pide mas bytes de los que faltan
        got  = sock.readinto(buf, want)      # lee directamente en el buffer sin copiar
        if not got:
            break                            # conexion cerrada antes de tiempo
        sink.write(buf[:got])                # escribe solo los bytes recibidos
        total += got
    return total

def _read_chunked(sock, sink, bufsize=512):
    # lee un cuerpo HTTP en formato chunked (Transfer-Encoding: chunked)
    # cada chunk comienza con su tamano en hexadecimal seguido de \r\n
    total = 0
    while True:
        size_line = _readline(sock)
        if size_line == "":
            continue                                  # ignora lineas vacias entre chunks
        size = int(size_line.split(";")[0], 16)      # convierte el tamano de hex a entero
        if size == 0:
            _readline(sock)                           # chunk final de tamano 0: fin del cuerpo
            break
        total += _read_exact(sock, sink, size, bufsize)  # lee el chunk completo
        _readline(sock)                               # consume el \r\n al final del chunk
    return total

def read_body(sock, headers, sink, bufsize=512):
    # lee el cuerpo completo de la respuesta HTTP segun el tipo de transferencia
    # delega en _read_exact o _read_chunked segun los headers recibidos
    if "content-length" in headers:
        return _read_exact(sock, sink, int(headers["content-length"]), bufsize)
    if headers.get("transfer-encoding", "").lower() == "chunked":
        return _read_chunked(sock, sink, bufsize)
    # si no hay Content-Length ni chunked, lee hasta que el servidor cierre la conexion
    total = 0
    buf   = bytearray(bufsize)
    while True:
        got = sock.readinto(buf)
        if not got:
            break
        sink.write(buf[:got])
        total += got
    return total

class _BytesSink:
    # objeto que actua como archivo en memoria: acumula bytes en una lista
    # se usa para leer respuestas JSON sin crear un archivo en disco
    def __init__(self):
        self.chunks = []
    def write(self, b):
        self.chunks.append(bytes(b))        # guarda cada fragmento recibido
    def getvalue(self):
        return b"".join(self.chunks)        # une todos los fragmentos en un solo bytes

def _split_url(url):
    # separa una URL HTTPS en (host, path) para seguir redirecciones
    if url.startswith("https://"):
        url = url[8:]                        # elimina el prefijo https://
    slash = url.find("/")
    return (url, "/") if slash == -1 else (url[:slash], url[slash:])


# ─────────────────────────────────────────────────────────────
# GOOGLE DRIVE
# ─────────────────────────────────────────────────────────────

def list_drive_files():
    # consulta la API de Google Drive v3 y devuelve la lista de archivos JPEG
    # de la carpeta configurada, ordenados por fecha de creacion ascendente
    path = (
        "/drive/v3/files"
        "?q=%27" + GDRIVE_FOLDER_ID + "%27+in+parents"   # filtra por carpeta padre
        "+and+mimeType+contains+%27image%2Fjpeg%27"       # solo archivos JPEG
        "+and+trashed%3Dfalse"                             # excluye archivos en la papelera
        "&fields=files(id%2Cname)"                         # pide solo id y nombre
        "&orderBy=createdTime+asc"                         # mas antiguas primero
        "&pageSize=" + str(MAX_IMAGES) +                   # limite de resultados
        "&key=" + GOOGLE_API_KEY
    )
    status, headers, sock = https_get("www.googleapis.com", path)
    if status != 200:
        sock.close()
        return []                           # si la API falla, devuelve lista vacia
    sink = _BytesSink()
    read_body(sock, headers, sink)          # lee el JSON de respuesta completo
    sock.close()
    try:
        return json.loads(sink.getvalue()).get("files", [])  # parsea y devuelve la lista
    except:
        return []                           # si el JSON es invalido, devuelve lista vacia

def make_filename(file_id):
    # convierte el ID de Google Drive (que puede contener guiones y otros caracteres)
    # en un nombre de archivo seguro para FAT32: solo letras y numeros, maximo 8 caracteres
    base = ""
    for c in file_id:
        if ('a' <= c <= 'z') or ('A' <= c <= 'Z') or ('0' <= c <= '9'):
            base += c
    return base[:8] + ".jpg"   # limita a 8 caracteres y agrega extension

def animate_download(host, path, dest_path, n, max_redirects=3):
    # descarga un archivo JPEG desde host+path y lo guarda en dest_path
    # anima la pantalla con show_downloading() durante la descarga
    # soporta hasta max_redirects redirecciones HTTP
    for _ in range(max_redirects):
        show_downloading(n)
        addr = socket.getaddrinfo(host, 443)[0][-1]  # resuelve el host
        raw  = socket.socket()
        raw.settimeout(HTTP_TIMEOUT)
        raw.connect(addr)
        s = ssl.wrap_socket(raw)                      # abre conexion HTTPS

        show_downloading(n)
        req = "GET %s HTTP/1.1\r\nHost: %s\r\nUser-Agent: Pico2W\r\nConnection: close\r\n\r\n" % (path, host)
        s.write(req.encode())   # envia la peticion GET

        show_downloading(n)
        status_line = _readline(s)
        parts  = status_line.split(" ", 2)
        status = int(parts[1]) if len(parts) > 1 else 0

        headers = {}
        while True:
            line = _readline(s)
            if line == "":
                break
            k, _, v = line.partition(":")
            headers[k.strip().lower()] = v.strip()

        if status in (301, 302, 303, 307, 308):
            # el servidor redirige: actualiza host y path y reintenta
            loc = headers.get("location")
            s.close()
            if not loc:
                return False
            host, path = _split_url(loc)
            continue

        if status != 200:
            s.close()
            return False   # error HTTP: abandona la descarga

        # descarga el cuerpo y lo escribe directamente en el archivo destino
        f     = open(dest_path, "wb")
        total = 0
        try:
            buf = bytearray(512)
            if "content-length" in headers:
                remaining = int(headers["content-length"])
                while remaining > 0:
                    want = min(512, remaining)
                    got  = s.readinto(buf, want)
                    if not got:
                        break
                    f.write(buf[:got])
                    total     += got
                    remaining -= got
                    if total % 4096 < 512:
                        show_downloading(n)   # actualiza la animacion cada ~4KB
            else:
                while True:
                    got = s.readinto(buf)
                    if not got:
                        break
                    f.write(buf[:got])
                    total += got
                    if total % 4096 < 512:
                        show_downloading(n)
        finally:
            f.close()   # siempre cierra el archivo aunque haya error
            s.close()   # siempre cierra el socket aunque haya error

        return total > 100   # considera la descarga valida si recibio mas de 100 bytes
    return False

def check_drive():
    # compara los archivos del Drive con los que ya hay en la SD
    # descarga solo los que faltan y devuelve True si se descargo alguno
    if not sd_ok:
        print("check_drive: SD no disponible, omitiendo")
        return False

    files = list_drive_files()
    if not files:
        return False

    any_downloaded = False
    count          = 1

    for f in files:
        fid = f.get("id", "")
        if not fid:
            continue
        fpath = IMG_DIR + "/" + make_filename(fid)
        try:
            os.stat(fpath)   # si el archivo ya existe en la SD, lo salta
            continue
        except OSError:
            pass             # OSError significa que el archivo no existe: hay que descargarlo

        print("Descargando (%d):" % count, f.get("name", fid))
        dl_path = "/drive/v3/files/" + fid + "?alt=media&key=" + GOOGLE_API_KEY
        ok      = animate_download("www.googleapis.com", dl_path, fpath, count)

        if ok:
            print("  Descarga OK")
            any_downloaded = True
            count += 1
        else:
            print("  [ERROR] Fallo la descarga. Saltando...")
            try:
                os.remove(fpath)   # elimina el archivo parcial para no corromper la galeria
            except:
                pass

    return any_downloaded


# ─────────────────────────────────────────────────────────────
# GALERIA LOCAL
# ─────────────────────────────────────────────────────────────

def scan_local_images():
    # lee la carpeta IMG_DIR en la SD y llena gallery_names
    # valida cada archivo leyendo los primeros 2 bytes (cabecera JPEG: FF D8)
    # elimina los archivos que no son JPEG validos
    global gallery_names
    gallery_names = []
    if not sd_ok:
        return
    try:
        names = os.listdir(IMG_DIR)
    except OSError:
        return

    for name in names:
        low = name.lower()
        if not (low.endswith(".jpg") or low.endswith(".jpeg")):
            continue   # ignora archivos que no sean JPEG por extension
        fullpath = IMG_DIR + "/" + name
        try:
            with open(fullpath, "rb") as fh:
                hdr = fh.read(2)   # lee solo los primeros 2 bytes para validar
        except OSError:
            continue
        if hdr != b"\xff\xd8":
            # los dos primeros bytes de todo JPEG valido son 0xFF 0xD8
            # si no coinciden, el archivo esta corrupto: se elimina
            try:
                os.remove(fullpath)
            except OSError:
                pass
            continue
        gallery_names.append(name)
        if len(gallery_names) >= MAX_IMAGES:
            break   # respeta el limite maximo de imagenes en memoria


# ─────────────────────────────────────────────────────────────
# MOSTRAR IMAGEN
# El JPEG ocupa los 320x240px completos de la pantalla.
# El overlay (contador e icono) se dibuja encima del JPEG
# en la esquina inferior antes del display.update() final.
# ─────────────────────────────────────────────────────────────

def show_current_image(new_photo=False):
    # muestra la foto actual de la galeria con el contador superpuesto
    # new_photo=True agrega el icono de camara indicando que es una foto recien descargada
    if not gallery_names:
        return   # no hay nada que mostrar
    path = IMG_DIR + "/" + gallery_names[gallery_current]
    print("Renderizando:", path)

    display.set_pen(PEN_BLACK)
    display.clear()   # limpia el framebuffer antes de decodificar

    try:
        jpeg.open_file(path)                          # abre el archivo JPEG desde la SD
        jpeg.decode(0, 0, JPEG_SCALE, dither=False)   # decodifica el JPEG al framebuffer desde (0,0)
    except Exception as e:
        print("Error JPEG:", e)
        show_msg("Error al decodificar\nla imagen", PEN_RED)
        return

    # calcula la posicion del contador en la esquina inferior derecha
    num_str = "%d" % (gallery_current + 1)   # numero de foto actual (base 1)
    tot_str = "/%d" % len(gallery_names)     # total de fotos
    num_w   = len(num_str) * 14              # ancho estimado del numero (14px por caracter a escala 2)
    tot_w   = len(tot_str) * 10             # ancho estimado del total (10px por caracter a escala 2)
    total_w = num_w + tot_w
    bx = 320 - total_w - 16   # posicion x: pegado al borde derecho con margen de 16px
    by = 240 - 28             # posicion y: 28px desde el borde inferior

    display.set_pen(display.create_pen(20, 20, 20))       # fondo gris muy oscuro semi-opaco
    display.rectangle(bx - 4, by - 2, total_w + 20, 26)  # rectangulo de fondo del contador
    display.set_pen(PEN_WHITE)
    display.text(num_str, bx, by + 2, 150, 2)             # numero actual en blanco
    display.set_pen(PEN_LGRAY)
    display.text(tot_str, bx + num_w, by + 2, 150, 2)     # total en gris claro

    if new_photo:
        # muestra el icono de camara y la palabra "nueva" en la esquina inferior izquierda
        display.set_pen(display.create_pen(20, 20, 20))
        display.rectangle(4, 240 - 28, 60, 26)    # fondo del icono
        draw_camera_icon(8, 240 - 26)              # dibuja el icono de camara
        display.set_pen(PEN_CYAN)
        display.text("nueva", 36, 240 - 22, 80, 1) # etiqueta "nueva" junto al icono

    display.update()   # envia el framebuffer completo a la pantalla


# ─────────────────────────────────────────────────────────────
# BOTONES DE NAVEGACION
# Se usa deteccion de flanco descendente (1->0) con debounce
# para evitar que un solo toque cuente multiples veces.
# PULL_UP: el pin lee 1 en reposo y 0 cuando el boton se presiona.
# ─────────────────────────────────────────────────────────────

btn_next  = Pin(BTN_NEXT_PIN, Pin.IN, Pin.PULL_UP)  # boton siguiente con resistencia pull-up interna
btn_prev  = Pin(BTN_PREV_PIN, Pin.IN, Pin.PULL_UP)  # boton anterior con resistencia pull-up interna
_next_was = 1   # estado anterior del boton siguiente (1 = no presionado)
_prev_was = 1   # estado anterior del boton anterior  (1 = no presionado)

def handle_buttons():
    # detecta pulsaciones y avanza o retrocede en la galeria
    global gallery_current, _next_was, _prev_was

    next_now = btn_next.value()
    if next_now == 0 and _next_was == 1:          # flanco descendente: boton recien presionado
        time.sleep_ms(DEBOUNCE_MS)                 # espera para filtrar rebotes mecanicos
        if btn_next.value() == 0 and gallery_names:
            gallery_current = (gallery_current + 1) % len(gallery_names)
            # % len() hace que al llegar al final vuelva a la primera foto
            show_current_image()
    _next_was = next_now   # guarda el estado para comparar en la siguiente iteracion

    prev_now = btn_prev.value()
    if prev_now == 0 and _prev_was == 1:
        time.sleep_ms(DEBOUNCE_MS)
        if btn_prev.value() == 0 and gallery_names:
            gallery_current = (gallery_current - 1) % len(gallery_names)
            # -1 % len() en Python/MicroPython da el ultimo indice si estamos en 0
            show_current_image()
    _prev_was = prev_now


# ─────────────────────────────────────────────────────────────
# BUCLE PRINCIPAL
# ─────────────────────────────────────────────────────────────

def main():
    global gallery_current
    show_splash()    # pantalla de bienvenida mientras el hardware termina de arrancar

    init_sd()        # intenta montar la SD
    if sd_ok:
        scan_local_images()   # carga las fotos que ya habia en la SD
        print("Imagenes en SD al inicio:", len(gallery_names))
    else:
        show_msg("SD no detectada.\nVerifica conexion.", PEN_RED)
        time.sleep(3)

    show_msg("Conectando WiFi...")
    wifi_ok = connect_wifi()   # intenta conectar a la red WiFi

    if wifi_ok and sd_ok:
        try:
            check_drive()       # descarga fotos nuevas del Drive si las hay
        except Exception as e:
            print("Error check_drive inicial:", e)
        scan_local_images()     # re-escanea la SD para incluir las fotos recien descargadas

    if gallery_names:
        show_current_image()    # muestra la primera foto disponible
    else:
        if not sd_ok:
            show_msg("Sin SD.\nInserta tarjeta\ny reinicia.", PEN_RED)
        else:
            show_msg("Sin imagenes.\nSube fotos al Drive.")

    last_check = time.time()   # marca el tiempo de la ultima revision del Drive

    while True:
        handle_buttons()       # revisa botones en cada iteracion del bucle

        now = time.time()
        if wifi_ok and sd_ok and now - last_check >= CHECK_EVERY_SEC:
            # cada CHECK_EVERY_SEC segundos revisa si hay fotos nuevas en Drive
            last_check = now
            try:
                prev_total = len(gallery_names)
                if check_drive():
                    scan_local_images()
                    if len(gallery_names) > prev_total:
                        gallery_current = len(gallery_names) - 1  # salta a la foto nueva
                        show_current_image(new_photo=True)         # muestra icono de camara
                    else:
                        show_current_image()
            except Exception as e:
                print("Error en ciclo:", e)

        time.sleep_ms(10)   # cede el control 10ms para no saturar el procesador en el bucle


main()   # punto de entrada: MicroPython ejecuta este archivo al arrancar