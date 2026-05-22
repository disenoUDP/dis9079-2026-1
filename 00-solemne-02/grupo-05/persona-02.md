# investigaciones individuales

Isidora Andrea Pérez Maulén /  [isipm08](<https://github.com/nicolasvaldesgreve/dis9079-2026-1/tree/main/21-isipm08>)

# Sensor
## Sensor de sonido tipo KY-038 / LM393

### **¿Qué es?**
+ El sensor de sonido KY-038 es un dispositivo electrónico diseñado para **detectar ondas sonoras** o **variaciones acústicas** del entorno y convertirlas en señales elécticas, en donde el sonido es capaz de "viajar por el aire" en forma de vibraciones, donde el sensor capta estas vibraciones mediante un micrófono de condensador.
+ Estas señales pueden ser interpretadas por un circuito, un microcontrolador o una computadora.
+ Utilizado en proyectos de robótica, domótica, instalaciones interactivas, instrumentos musicales electrónicos, sistemas de seguridad y arte multimedia.
+ Es compatible con varias placas, por ejemplo: Arduino UNO, Arduino Nano, Arduino Mega, ESP32, ESP8266 y Raspberry Pi, lo que facilita su integración en múltiples plataformas.

![titulo](./imagenes/sensorsonido.webp)

*Créditos Imagen:* https://www.teslaelectronicla.com/producto/sensor-de-sonido-ky-038/

### **Componentes**
- Micrófono
  + Captura vibraciones del aire.
  + Convierte sonido en pequeñas variaciones eléctricas.
    
- Amplificador
  + Aumenta señal del micrófono para poder procesarla.
    
- Comparador/Procesador
  + Determina si el sonido supera cierto umbral.
  + También se puede ajustar la sensibilidad con un potenciómetro (algunos sensores).
    
- Salida
  + Analógica: Entrega valores variables según intensidad del sonido detectado.
  + Digital: Se activa cuando el nivel de sonido supera cierto umbral que es previamente ajustado con un potenciómetro.

![titulo](./imagenes/partesensor.jpeg)

*Créditos Imagen:* https://destecmex.com/producto/modulo-sensor-de-sonido-ky-038/

### **Aplicaciones más comunes**
- Estos son algunos de los ejemplos en los cuales se puede aplicar un sensor de sonido
  + Detectar aplausos.
  + Activar luces o motores.
  + Medir contaminación acústica.
  + Crear visualizaciones musicales.
  + Controlar robots por voz.
  + Generar experiencias interactivas en el arte digital.


### **Visualización de datos**
- Un claro y fácil ejemplo para visualizar datos es a través de un LED.
  + A mayor sonido el LED se enciende.
  + Se realizan este tipo de conexiones (sirve tanto para el sensor de sonido KY-037 y KY-038)
  + Luego entraremos a Arduino, lo conectaremos y pondremos este código referencial;
  + En el Monitor Serial visualizaremos el comportamiento del módulo cuando se efectúe un sonido, donde el contador varía según intensidad del sonido. (considerar en el sensor de sonido KY-038 se aumenta sensibilidad). Observando así que con un menor sonido el LED de igual forma es encendido por su mayor sensibilidad.
  
> Tinkercad y código sacados de esta página: https://blog.uelectronics.com/tarjetas-desarrollo/uso-de-los-sensores-de-sonido-ky-038-ky-037-para-controlar-el-encendido-de-un-foco/ 

![titulo](./imagenes/tinkercadsensor.png)

```cpp
//Nota: Ajustar la sensibilidad del micrófono con el trimpot

int led = 13;    //Colocaremos un Led en el Pin 13 del Arduino para saber cuando sea activado el Sensor de Sonido
int KY037= 4;    //Pin 4 para la salida digital del KY
int flanco= 0;   //Variable de apoyo para saber la lectura del sensor

void setup()
{
  Serial.begin(9600);      //Inicialización del puerto serial a 9600 baudios
  pinMode( led, OUTPUT) ;  //pin 13/led como pin de salida
  pinMode( KY037, INPUT) ; //pin del KY como entrada de datos
}

void loop()
{
  if (digitalRead(KY037)==HIGH )          //Si se detecta un sonido el KY(dependiente a la sensibilidad determinada por el usuario)
  {
    flanco= flanco + 1;                  // Se realiza un contador +1 por cada vez que el sensor detecte un flanco ALTO
    Serial.print("Número de Flancos: "); // Escribe el número de flancos detectados dependiendo el sonido censado...
    Serial.println(flanco, DEC) ;        // escribiendo el valor en forma decimal

if (flanco == 4) {                      //Si el contador llega a 4, que es el valor anteriormente calibrado a nuestro sistema
      Serial.println(flanco);          //Escribe el valor del flanco=4 y...
      digitalWrite(led, HIGH);         //...enciende el led 

    } else if (flanco== 8) {          //El contador esperara un nuevo sonido para desactivar el led y eso es cuando se llega al valor de flanco=8
      Serial.println(flanco);         //Escribe el valor del flanco=8 y... 
      digitalWrite(led, LOW);         //...se apagará el led y ..
      flanco= 0;                      //Se reiniciara el valor del flanco para que no se quede ningún valor guardad en flanco                  
      }
   }
}
```

### **Referente**

## Actuador

## Fuentes Sensor
- https://uelectronics.com/producto/sensor-microfono-ky-038/
- https://blog.uelectronics.com/tarjetas-desarrollo/uso-de-los-sensores-de-sonido-ky-038-ky-037-para-controlar-el-encendido-de-un-foco/

## Bibliografía
