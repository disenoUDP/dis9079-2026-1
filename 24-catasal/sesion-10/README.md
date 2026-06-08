# sesion-10

lunes 18 mayo 2026

solemne 2

# enviar información a adafruit
<img width="1882" height="861" alt="io adafruit" src="https://github.com/user-attachments/assets/1de7832a-c0d0-4533-b3dd-0c3307738fac" />


# como se puede encender una luz led externa 

Para controlar un **LED externo**, que funciona como una pequeña luz que se enciende y apaga mediante programación. El Arduino envía señales eléctricas desde uno de sus pines digitales. Cuando el pin se activa en estado “HIGH”, permite el paso de corriente eléctrica, lo que enciende el LED; cuando cambia a “LOW”, corta la corriente y el LED se apaga. Para que el LED no reciba demasiada energía y se queme, se coloca una **resistencia de 220Ω o 330Ω** en serie, que tiene la función de limitar la corriente. La conexión correcta es: pin 10 → resistencia → pata larga del LED (ánodo +), y la pata corta del LED (cátodo -) → GND del Arduino.

El funcionamiento se controla mediante un programa en Arduino IDE. En el código, primero se define el pin del LED como salida usando `pinMode`, lo que permite que el Arduino envíe electricidad por ese pin. Luego, dentro del `loop`, se alterna entre encender y apagar el LED usando `digitalWrite(HIGH)` y `digitalWrite(LOW)`, con pausas de tiempo definidas por `delay(1000)`, que equivalen a un segundo. Esto hace que el LED parpadee continuamente en ciclos. Este ejercicio es fundamental porque enseña cómo un microcontrolador puede controlar dispositivos físicos mediante programación, siendo la base para proyectos más avanzados como sensores, automatización o sistemas controlados por WiFi.

// LED externo conectado al pin 13

// La función setup se ejecuta una vez
void setup() {

  // Configura el pin 13 como salida
  pinMode(13, OUTPUT);

}

// La función loop se repite infinitamente
void loop() {

  // Enciende el LED
  digitalWrite(13, HIGH);

  // Espera 1 segundo
  delay(1000);

  // Apaga el LED
  digitalWrite(13, LOW);

  // Espera 1 segundo
  delay(1000);

}


<img width="807" height="642" alt="luz led" src="https://github.com/user-attachments/assets/a802100f-499b-43e8-9c0d-9e1918205516" />

