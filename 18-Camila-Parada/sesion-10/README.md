# ⋆⭒˚.⋆ └[∵┌] Clase 10: Preparación para la solemne 02 [┐∵]┘ ⋆.˚⭒⋆

Lunes 18 de mayo 2026

## Observaciones

Tras el evento del incendio, pues las cosas se complejizaron un poco con los tiempos. Pero pese a ello el profe y ayudante nos apoyaron trayendo ejercicios prácticos para poder entender y planificar que hacer para la solemne.

Cabe mencionar que para esta clase traje avances de lo que tenía pensado hacer: una imitación hecha a partir de un estudio de un instrumento armable de Maywa denki.

Al ver que muchos de sus proyectos incluían solenoides es que me animé a comprar un par en Hubbot y experimentar con ellos.

En un inicio no pude hacer mucho... dado que no tenía suficiente amperaje para poder trabajar con él. Preguntandole a "Claude" es que pude obtener "ayuda" directa, puesto que no pude encontrar proyectos o referentes que trabajaran directo con el tipo de mini solenoide que tenía (ZHO-0420). De la poca documentación que encontré se encuentra el "Datasheet" del fabricante.

## Observaciones

Pese a ello logré armar un circuito que funcionaba con un Relé que se nos entregó el año pasado en "Taller de máquinas electrónicas".
Tras conseguir una conexión/entrada y una fuente de poder, puse a prueba el solenoide conectado a arduino. El cuál con un código enviaba señales que activaban el motor cada x cantidad de tiempo.

```cpp
// ============================================================
// Arduino UNO R4 WiFi — TEST del solenoide
// Prueba SOLO el relé y el solenoide, sin WiFi ni MQTT
// Da un golpe cada 2 segundos, de forma continua
//
// NOTA: el ZHO-0420S es pull-type y golpea al DESACTIVARSE
// ============================================================

const int RELE_PIN = 7;     // pin de señal del relé
const int PULSO_MS = 80;    // duración energizado de cada golpe

void setup() {
  Serial.begin(115200);
  pinMode(RELE_PIN, OUTPUT);
  digitalWrite(RELE_PIN, LOW);   // relé apagado al inicio
  Serial.println("=== TEST del solenoide ===");
  Serial.println("Un golpe cada 2 segundos...");
}

void loop() {
  Serial.println(">>> GOLPE");
  digitalWrite(RELE_PIN, HIGH);  // energiza el solenoide
  delay(PULSO_MS);               // espera el pulso
  digitalWrite(RELE_PIN, LOW);   // suelta -> golpe (pull-type)

  delay(2000);                   // espera 2 segundos hasta el próximo golpe
}
```

Este código lo traje para mostrarle a Vania parte de mi idea, resolviendo la parte técnica del actuador.

Ya sólo esa clase nos quedó por resolver cuales serían los actuadores.
Para ello es que trabajamos usando 2 botones.

Para más detalles del proceso se encuentra [este archivo más detallado](https://github.com/Camila-Parada/dis9079-2026-1/blob/main/00-solemne-02/grupo-06/persona-01.md)

***

<!-- Las horas avanzan... y pues sólo quiero que mi cuerpo resista. Mañana será otro día y pues, espero que lo que hago sea un aporte. -->
