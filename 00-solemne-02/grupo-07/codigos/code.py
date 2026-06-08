import time
import board
import digitalio
import wifi
import socketpool
import adafruit_minimqtt.adafruit_minimqtt as MQTT


# ---------------- WIFI ----------------
SSID = "monkiboy"
PASSWORD = "benja1234"


# ---------------- ADAFRUIT IO ----------------
AIO_USER = "bla"
AIO_KEY = "bla"
FEED = "detector-movimiento"


# ---------------- PIR ----------------
pir = digitalio.DigitalInOut(board.GP2)
pir.direction = digitalio.Direction.INPUT


# ---------------- BOTÓN (HOLD) ----------------
button = digitalio.DigitalInOut(board.GP0)
button.direction = digitalio.Direction.INPUT
button.pull = digitalio.Pull.UP


# ---------------- WIFI ----------------
print("Conectando WiFi...")
wifi.radio.connect(SSID, PASSWORD)
print("WiFi OK")


pool = socketpool.SocketPool(wifi.radio)


mqtt = MQTT.MQTT(
   broker="io.adafruit.com",
   username=AIO_USER,
   password=AIO_KEY,
   socket_pool=pool
)


mqtt.connect()
print("MQTT OK")


# ---------------- CALIBRACIÓN ----------------
print("Calibrando PIR...")
time.sleep(30)
print("Listo")


# ---------------- VARIABLES ----------------
pir_state = False
motion_start_time = 0
last_motion_time = 0


MIN_TRIGGER_TIME = 0.8
COOLDOWN = 2


motion_count = 0


# ---------------- LOOP ----------------
while True:


   system_active = not button.value  # botón mantenido


   if system_active:


       current = pir.value


       if current and not pir_state:
           motion_start_time = time.monotonic()


       if current and pir_state:
           duration = time.monotonic() - motion_start_time


           if duration >= MIN_TRIGGER_TIME:
               if time.monotonic() - last_motion_time > COOLDOWN:


                   motion_count += 1


                   print("MOVIMIENTO DETECTADO #", motion_count)


                   try:
                       mqtt.publish(
                           f"{AIO_USER}/feeds/{FEED}",
                           f"motion:{motion_count}"
                       )
                   except Exception as e:
                       print("Error MQTT:", e)


                   last_motion_time = time.monotonic()


       pir_state = current


   else:
       pir_state = False


   time.sleep(0.01)