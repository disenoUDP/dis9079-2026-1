# Código hecho usando de base el código de Mateo y del profesor, con ayuda de Gemini para implementar componentes y uso de pantalla OLED.

import time
import os
import board
import digitalio
import analogio
import bitbangio
import math
import wifi
import socketpool
import ssl
import adafruit_ssd1306
import adafruit_minimqtt.adafruit_minimqtt as MQTT
from adafruit_io.adafruit_io import IO_MQTT

FEED_KEY = "solemne02-grupo01"

# Configuración de la Pantalla OLED
i2c = bitbangio.I2C(board.GP27, board.GP26)
oled = adafruit_ssd1306.SSD1306_I2C(128, 64, i2c)

# Configuración de Componentes Físicos
button = digitalio.DigitalInOut(board.GP15)
button.direction = digitalio.Direction.INPUT
button.pull = digitalio.Pull.UP

pot = analogio.AnalogIn(board.GP28)

# Indicador LED de la placa para mostrar actividad de envío MQTT.
led = digitalio.DigitalInOut(board.LED)
led.direction = digitalio.Direction.OUTPUT

# Escribe en la consola para confirmar que el programa ha arrancado y que esté conectándose al WiFi.
print("Conectando a WiFi...")

# Si se conecta a la red WiFi, imprime "WiFi conectado" en la consola. Si no, muestra un error y termina el programa.
wifi.radio.connect(os.getenv("CIRCUITPY_WIFI_SSID"), os.getenv("CIRCUITPY_WIFI_PASSWORD"))
print("WiFi conectado")

# Configuración de MQTT para Adafruit IO
pool = socketpool.SocketPool(wifi.radio)
mqtt_client = MQTT.MQTT(
    broker="io.adafruit.com",
    username=os.getenv("ADAFRUIT_AIO_USERNAME"),
    password=os.getenv("ADAFRUIT_AIO_KEY"),
    socket_pool=pool,
    ssl_context=ssl.create_default_context(),
)
io = IO_MQTT(mqtt_client)
print("Conectando a Adafruit IO...")
io.connect()
print("Conectado a Adafruit IO")

# Foto del gato convertida en bytearray
WIDTH_GATO = 33
HEIGHT_GATO = 41
ROW_BYTES = 5  

GATO_BYTES = bytearray([
    0x00, 0x00, 0x07, 0xe0, 0x00, 0x00, 0x00, 0x1c, 0x3c, 0x00, 0x00, 0x00,
    0x30, 0x06, 0x00, 0x00, 0x00, 0xe0, 0x03, 0x00, 0x00, 0x00, 0x80, 0x01,
    0x00, 0x00, 0x00, 0x90, 0x81, 0x80, 0x00, 0x01, 0x98, 0xc0, 0x80, 0x00,
    0x01, 0x1c, 0xe0, 0x80, 0x00, 0x01, 0x1f, 0xf0, 0x80, 0x00, 0x01, 0x3f,
    0xf0, 0x80, 0x00, 0x01, 0x3b, 0xb8, 0x80, 0x00, 0x01, 0xbb, 0xb8, 0x80,
    0x00, 0x00, 0xbe, 0xf9, 0x80, 0x00, 0x00, 0xbd, 0x79, 0x00, 0x00, 0x01,
    0xbf, 0xf3, 0x00, 0x00, 0x03, 0xdf, 0xe6, 0x00, 0x00, 0x03, 0xe7, 0x1c,
    0x00, 0x00, 0x07, 0xf0, 0xf0, 0x00, 0x00, 0x0f, 0xdf, 0x80, 0x00, 0x00,
    0x0f, 0xef, 0xe0, 0x00, 0x00, 0x1e, 0xf7, 0xf0, 0x00, 0x00, 0x1e, 0x76,
    0x70, 0x00, 0x00, 0x1f, 0xb6, 0x70, 0x00, 0x00, 0x1f, 0xb7, 0x60, 0x00,
    0x00, 0x1f, 0xcf, 0x00, 0x00, 0x00, 0x1f, 0xff, 0x00, 0x00, 0x7c, 0x1f,
    0xff, 0x80, 0x00, 0x7e, 0x1f, 0xff, 0xc0, 0x00, 0xfe, 0x0f, 0xff, 0xc0,
    0x00, 0xf6, 0x0f, 0xff, 0xc0, 0x00, 0xe0, 0x0f, 0xff, 0xc0, 0x00, 0xe0,
    0x1f, 0xfb, 0xc0, 0x00, 0xf0, 0x1f, 0xfb, 0xf0, 0x00, 0x78, 0x3f, 0xf9,
    0xf0, 0x00, 0x7f, 0xf9, 0xf8, 0x00, 0x00, 0x3f, 0xf1, 0xf8, 0x00, 0x00,
    0x0f, 0xe0, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x78, 0x00, 0x00, 0x00, 0x00,
    0x38, 0x00, 0x00, 0x00, 0x00, 0x1c, 0x00, 0x00, 0x00, 0x00, 0x0c, 0x00,
    0x00
])

# Función que rota la imagen del gato y la dibuja en la pantalla OLED
def rotar_y_dibujar_gato(angulo_servo, x_destino, y_destino):
    t = 90 - angulo_servo
    angulo_rad = math.radians(t)
    cos_a = math.cos(angulo_rad)
    sin_a = math.sin(angulo_rad)
    
    cx_orig = WIDTH_GATO / 2
    cy_orig = HEIGHT_GATO / 2

    # Reducción del tamaño a 54x54
    DEST_SIZE = 54
    cx_dest = DEST_SIZE / 2
    cy_dest = DEST_SIZE / 2
    
    # Caché local de la función (Evita búsquedas repetitivas en RAM)
    pintar_pixel = oled.pixel
    
    for yd in range(DEST_SIZE):
        ty = yd - cy_dest
        # Precalculamos la parte de la ecuación que depende solo de Y para liberar el bucle interno
        ys_part = ty * cos_a + cy_orig
        xs_part = ty * sin_a + cx_orig
        
        for xd in range(DEST_SIZE):
            tx = xd - cx_dest
            
            xs = int(tx * cos_a + xs_part)
            ys = int(-tx * sin_a + ys_part)
            
            if 0 <= xs < WIDTH_GATO and 0 <= ys < HEIGHT_GATO:
                byte_idx = ys * ROW_BYTES + (xs // 8)
                bit_idx = 7 - (xs % 8)
                
                if (GATO_BYTES[byte_idx] >> bit_idx) & 1:
                    pintar_pixel(xd + x_destino, yd + y_destino, 1)

def actualizar_pantalla(val_pot, angulo, transmitiendo=False):
    oled.fill(0)
    
    # Desplazamos levemente el lienzo de 54x54 para que no tape los textos
    rotar_y_dibujar_gato(angulo, 4, 5)
    
    oled.text(f"POT: {val_pot}", 68, 4, 1)
    oled.text(f"ANG: {angulo}", 68, 16, 1)
    
    if transmitiendo:
        oled.text("ENVIADO!", 68, 32, 1)
        
    oled.show()

last_button_state = True
ultimo_angulo = -1  # Para comparar cambios

while True:
    try:
        io.loop()
    except (OSError, Exception):
        try:
            io.connect()
        except Exception:
            pass

    val_pot = pot.value * 1023 // 65535
    angulo_servo = val_pot * 180 // 1023

    current_state = button.value

    # Control del botón e indicador físico
    if last_button_state == True and current_state == False:
        print(f"MQTT Activo: {val_pot}")
        actualizar_pantalla(val_pot, angulo_servo, transmitiendo=True)

        try:
            io.publish(FEED_KEY, str(val_pot))
        except Exception:
            pass

        led.value = True
        time.sleep(0.2)
        led.value = False
        time.sleep(0.3)
    else:
        # OPTIMIZACIÓN 3: Renderizar solo si el potenciómetro realmente se movió
        if angulo_servo != ultimo_angulo:
            actualizar_pantalla(val_pot, angulo_servo, transmitiendo=False)
            ultimo_angulo = angulo_servo

    last_button_state = current_state
    time.sleep(0.005)  # Tiempo de espera reducido para una respuesta táctil más veloz