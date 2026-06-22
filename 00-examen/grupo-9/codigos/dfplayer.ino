#include <DFRobotDFPlayerMini.h>
#include "AdafruitIO_WiFi.h"


// ================== ADAFRUIT IO ==================
#define IO_USERNAME "xxx"
#define IO_KEY      "xxx"


#define WIFI_SSID   "xxx"
#define WIFI_PASS   "xxx"


AdafruitIO_WiFi io(IO_USERNAME, IO_KEY, WIFI_SSID, WIFI_PASS);


// Feed cerebro
AdafruitIO_Feed *cerebro = io.feed("cerebro");


// ================== DFPLAYER ==================
DFRobotDFPlayerMini player;


// ================== CALLBACK ==================
void handleMessage(AdafruitIO_Data *data) {


 int numero = data->toInt();


 Serial.print("Dato recibido: ");
 Serial.println(numero);


 // 0 -> audio 010
 // 1 -> audio 001
 // ...
 // 9 -> audio 009
 int audio = (numero == 0) ? 10 : numero;


 Serial.print("Reproduciendo audio ");
 Serial.println(audio);


 player.playFolder(1, audio);


 // Esperar 5 segundos
 delay(5000);


 // Reproducir audio 011
 player.playFolder(1, 11);
}


void setup() {


 Serial.begin(115200);
 Serial1.begin(9600);


 Serial.println("Iniciando DFPlayer...");


 if (!player.begin(Serial1)) {
   Serial.println("ERROR DFPlayer");
   while (true);
 }


 player.volume(10);


 Serial.println("DFPlayer listo");


 // Escuchar feed cerebro
 cerebro->onMessage(handleMessage);


 Serial.println("Conectando a Adafruit IO...");


 io.connect();


 while (io.status() < AIO_CONNECTED) {
   Serial.print(".");
   delay(500);
 }


 Serial.println();
 Serial.println("Conectado a Adafruit IO");


 // Esperar 3 segundos después de conectar
 delay(3000);


 // Reproducir audio 012 una sola vez
 player.playFolder(1, 12);
}


void loop() {


 io.run();


}

