# sesion-14

lunes 15 junio 2026 
## Etapa 1 — Diagnóstico del problema y elección de plataforma

Durante la clase surgió un problema concreto al iniciar el trabajo: el servicio que se estaba usando hasta ese momento, `dweet.io`, había dejado de funcionar porque el sitio estaba caído.

Esto generó un primer dilema de diseño, ya que el proyecto necesitaba que dos integrantes, ubicados en casas distintas, pudieran ver los datos del sensor de la planta en tiempo real. En plena clase se evaluaron dos caminos posibles:

- **Volver a la red propia del Arduino**: solución más rápida de implementar, pero solo funciona si ambos integrantes están conectados a la misma red local.
- **Migrar a un servicio en la nube**: requiere más trabajo de configuración, pero permite la comunicación real a distancia entre ambas casas.

Se optó por la segunda opción, ya que el requisito real del proyecto era que cada integrante pudiera grabar y visualizar los datos desde su propia ubicación.

### Elección del servicio en la nube

Se evaluó **HiveMQ Cloud** como alternativa a dweet.io, utilizando el protocolo **MQTT**. La elección se basó en que es un servicio gratuito, estable y que no requiere gestionar servidores propios. Dentro de las opciones disponibles, se eligió específicamente el plan **"Serverless"** (sin servidores), por ser gratuito y no necesitar configuración de infraestructura adicional.

---

## Etapa 2 — Configuración del clúster y credenciales en HiveMQ

En la misma sesión se realizó la configuración completa de la cuenta en la nube:

- Registro en `console.hivemq.cloud`
- Creación de un clúster gratuito de tipo "Sin Servidores"
- Obtención de los datos de conexión del clúster (host, puerto MQTT con TLS y puerto WebSocket con TLS)

Posteriormente, en la sección **"Gestión de acceso → Credenciales"**, se creó un usuario con permiso de **Publicar y Suscribir** (`PUBLISH_SUBSCRIBE`). Este permiso era necesario para que el Arduino pudiera enviar datos al mismo tiempo que el navegador los leía, ambos usando la misma cuenta de acceso.

---

## Etapa 3 — Primera programación del Arduino y conexión MQTT

Se programó el Arduino UNO R4 WiFi para cumplir tres funciones:

1. Leer el sensor ADS1115 por protocolo I2C
2. Conectarse a la red WiFi de la casa
3. Publicar los datos leídos mediante MQTT con conexión segura (TLS) hacia un topic llamado `planta/humedad`

### Problema encontrado

Al cargar el código por primera vez, el monitor serial del Arduino IDE mostró el mensaje **"Not connected"**. La primera interpretación, en plena clase, fue que se trataba de un error en el código.

## Códigos de prueba
    #include <Wire.h>
    #include <Adafruit_ADS1X15.h>
    #include <WiFiS3.h>

    const char* NOMBRE_RED = "planta-sensor";
    const char* CLAVE_RED  = "plantaviva";

    Adafruit_ADS1115 ads;
    WiFiServer servidor(80);

     int lecturas[4] = {0, 0, 0, 0};
     int base[4]     = {0, 0, 0, 0};
     int cambio[4]   = {0, 0, 0, 0};

    String nombres[4] = {"hoja_grande", "hoja_pequena", "tallo", "sustrato"};

    unsigned long ultimaLectura = 0;
    const int INTERVALO = 500;

    void setup() {
    Serial.begin(9600);
    Serial.println("=== La Voz de las Plantas - Grupo 07 ===");

    if (!ads.begin()) {
    Serial.println("ERROR: ADS1115 no encontrado.");
    while (1);
    }
    ads.setGain(GAIN_SIXTEEN);

    Serial.println("Calibrando... no toques la planta");
    delay(2000);
    for (int i = 0; i < 4; i++) {
    long suma = 0;
    for (int j = 0; j < 10; j++) {
      suma += ads.readADC_SingleEnded(i);
      delay(100);
    }
    base[i] = suma / 10;
    }
    Serial.println("Calibrado!");

    WiFi.beginAP(NOMBRE_RED, CLAVE_RED);
    while (WiFi.status() != WL_AP_LISTENING) {
    delay(500);
    Serial.print(".");
    }
    servidor.begin();
    Serial.println("\nRed lista!");
    Serial.println("http://192.168.4.1/datos");
    }
 
    void loop() {
    unsigned long ahora = millis();
    if (ahora - ultimaLectura >= INTERVALO) {
    ultimaLectura = ahora;
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
    }
 
    WiFiClient cliente = servidor.available();
    if (cliente) {
    String peticion = "";
    unsigned long inicio = millis();
    while (cliente.connected() && millis() - inicio < 1000) {
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
      cliente.print(json);
    }
    cliente.stop();
    }
    }
### Causa real y solución

Tras revisar el problema en el momento, se determinó que el mensaje no correspondía a un error de programación, sino a que faltaba conectar el cable USB y seleccionar el puerto correcto en el IDE. El problema se resolvió ahí mismo:

- Conectando el Arduino por USB
- Seleccionando el puerto en `Herramientas → Puerto`
- Instalando las dos librerías necesarias: `ArduinoMqttClient` y `Adafruit ADS1X15`

---

## Verificación de la conexión Arduino → HiveMQ

Antes de avanzar hacia la visualización, se necesitaba confirmar que los datos del Arduino realmente estaban llegando a la nube. Para esto se utilizó el **Cliente Web de HiveMQ**, una herramienta incluida gratuitamente en la consola.

Se realizó una suscripción al topic `planta/humedad` directamente desde el Cliente Web, lo que permitió observar los mensajes en formato JSON llegando en tiempo real, sin necesidad de tener abierto el archivo HTML de visualización al mismo tiempo.

Esta verificación, hecha durante la misma clase, confirmó que la conexión Arduino → HiveMQ funcionaba correctamente antes de continuar con el desarrollo de la interfaz visual.

---

## Primera visualización web y detección de un error conceptual

Se desarrolló una primera versión del HTML que calculaba un porcentaje de humedad de suelo (0 a 100%) a partir de un único sensor, mostrando una tarjeta simple con barra de progreso.

### Problema encontrado

Este enfoque asumía que el ADS1115 estaba conectado a un sensor de humedad de suelo tradicional, con una lógica de calibración basada en un valor seco y un valor mojado de referencia.

### Causa real

La lógica de calibración no aplicaba al hardware real del proyecto. En la práctica, lo que estaba conectado eran **cuatro electrodos (pinzas)** ubicados en distintas partes de la planta: hoja grande, hoja chica, tallo y tierra — no un sensor de humedad capacitivo.

El error se hizo evidente en el momento, cuando el valor de humedad calculado marcaba 100% de forma constante, sin importar la condición real de la planta.

---

## Rediseño de la visualización: "La Voz de las Plantas"

Se reemplazó la tarjeta simple de humedad por una visualización orgánica tipo **"campo de energía"**, compuesta por ondas circulares deformables, partículas y un núcleo central pulsante, siguiendo una referencia visual definida previamente para el proyecto.

### Problema encontrado

La primera versión de esta visualización no mostraba diferencias notorias entre valores bajos y altos del sensor. El cambio entre un estado y otro era casi imperceptible a simple vista.

### Solución aplicada

- Se recalculó la amplitud de la distorsión de las ondas utilizando una **relación cuadrática** en lugar de una relación lineal, lo que exagera la diferencia visual entre un valor bajo y uno alto.
- Se agregó un panel de estado de conexión a HiveMQ visible en pantalla, que muestra el estado de la conexión, la hora del último dato recibido y un contador de mensajes — para poder verificar a simple vista que el sistema seguía conectado durante una grabación.

---

##Corrección final: de "sensor de humedad" a "electrodos de la planta"

Al revisar nuevamente el monitor serial del Arduino, se confirmó que la humedad calculada seguía marcando 100% de forma constante. Esto evidenció, todavía en la misma clase, que el código estaba interpretando incorrectamente el tipo de dato que se estaba leyendo. A continuación el detalle de las tres versiones de código que se probaron hasta llegar a la solución correcta.

### Versión 1 — Primer intento (sensor de humedad de suelo)

La primera idea fue tratar el ADS1115 como si estuviera conectado a un sensor capacitivo de humedad de suelo tradicional:

```cpp
const int VALOR_SECO   = 17000;   // Valor cuando el suelo está SECO
const int VALOR_MOJADO = 8000;    // Valor cuando el suelo está MOJADO

int16_t valorCrudo = ads.readADC_SingleEnded(0);
int humedad = map(valorCrudo, VALOR_SECO, VALOR_MOJADO, 0, 100);
humedad = constrain(humedad, 0, 100);
```

La idea de `map()` era simple: tomar el valor crudo del ADC (que puede ir de -32768 a 32767) y convertirlo a una escala de 0% a 100%, usando dos puntos de referencia: cómo se ve el valor cuando está seco y cómo se ve cuando está mojado.

**Por qué esto no funcionó:** este cálculo solo tiene sentido si el sensor conectado es un sensor de humedad capacitivo de una sola entrada. La conexión real era distinta — había 4 pinzas/electrodos conectados a los 4 canales del ADS1115 (A0, A1, A2, A3), cada uno tocando una parte diferente de la planta: hoja grande, hoja chica, tallo y tierra. Estos electrodos no miden "humedad", miden diferencias de conductividad eléctrica entre puntos de la planta.

**Cómo se detectó:** al revisar el Serial Monitor, se observó que sin importar qué tan húmeda o seca estuviera la tierra, el cálculo de humedad siempre marcaba 100%:

## Conclusión

Esta clase permitió pasar de una solución que dependía de una plataforma externa poco confiable (dweet.io) a una arquitectura propia basada en MQTT y HiveMQ Cloud, capaz de comunicar dos ubicaciones distintas en tiempo real.

El proceso dejó un aprendizaje clave más allá de lo técnico: errores que parecían de programación —como el "Not connected" o la humedad fija en 100%— eran en realidad errores de interpretación del hardware conectado. Esto reforzó la importancia de verificar qué mide un sensor antes de aplicar cualquier fórmula sobre sus datos.
