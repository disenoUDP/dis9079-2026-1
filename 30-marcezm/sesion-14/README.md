# sesion-14

lunes 15 junio 2026  
---

## Etapa 1 — Problema inicial y decisión de plataforma

Al comenzar la clase apareció un problema que afectó directamente el desarrollo del proyecto: el servicio que se estaba utilizando para el envío de datos, **dweet.io**, dejó de funcionar porque el sitio estaba caído.

Esto obligó a replantear la forma en que los datos del sensor de la planta iban a ser compartidos entre dos integrantes ubicados en lugares distintos. El objetivo del proyecto era que ambos pudieran visualizar la información en tiempo real desde sus respectivas casas.

Se evaluaron dos caminos:

- Mantener una red local con el Arduino, lo que era más simple pero solo funcionaba si ambos estaban conectados al mismo WiFi.
- Migrar a una solución en la nube, que implicaba más configuración pero permitía conexión remota real.

Finalmente se eligió la segunda alternativa, ya que el proyecto requería independencia de ubicación.

---

## Elección de plataforma: HiveMQ Cloud

Se decidió trabajar con **HiveMQ Cloud**, utilizando el protocolo **MQTT** como sistema de comunicación.

Esta plataforma se eligió porque es estable, gratuita en su versión básica y no requiere gestionar servidores propios. Se utilizó el modo **serverless**, lo que permitió evitar configuraciones de infraestructura más complejas.

---

## Etapa 2 — Configuración del clúster y credenciales

Durante la misma sesión se realizó la configuración completa del entorno en HiveMQ:

- Creación de una cuenta en `console.hivemq.cloud`
- Creación de un clúster gratuito en modo serverless
- Obtención de los datos de conexión (host y puertos seguros MQTT/WebSocket)

Luego se creó un usuario con permisos de **publicación y suscripción (PUBLISH_SUBSCRIBE)**, necesario para que el sistema funcionara en ambos sentidos: Arduino enviando datos y navegador recibiéndolos en tiempo real.

---

## Etapa 3 — Programación del Arduino y conexión WiFi

Se programó el **Arduino UNO R4 WiFi** para cumplir tres funciones principales:

1. Leer datos desde el módulo ADS1115 mediante I2C  
2. Conectarse a una red WiFi local  
3. Publicar los datos mediante MQTT hacia el topic `planta/humedad`

### Problema detectado en clase

Al ejecutar el primer código, el monitor serial mostraba el mensaje **“Not connected”**. En un inicio se interpretó como un error del programa.

Sin embargo, después de revisar en clase, se determinó que el problema no era del código, sino de configuración del entorno de trabajo.

### Solución aplicada

- Conexión del Arduino mediante cable USB  
- Selección correcta del puerto en el IDE  
- Instalación de librerías necesarias:
  - `ArduinoMqttClient`
  - `Adafruit ADS1X15`

---

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

  ## Etapa 4 — Verificación de la comunicación con la nube (HiveMQ)

Antes de avanzar hacia la visualización de los datos, se realizó una verificación para confirmar que el sistema de envío estaba funcionando correctamente.

Para esto se utilizó el **cliente web de HiveMQ**, disponible en la consola de la plataforma, que permite suscribirse a topics MQTT y observar los mensajes en tiempo real sin necesidad de construir una interfaz propia.

Se realizó la suscripción al topic `planta/humedad`, lo que permitió ver los mensajes enviados desde el Arduino en formato JSON mientras ocurrían.

Esta prueba sirvió para validar el flujo completo de comunicación:

Arduino → MQTT (HiveMQ Cloud) → Cliente Web

Con esto se confirmó que la conexión a la nube era estable y que el problema no estaba en la transmisión de datos, sino en las capas posteriores del sistema.

---

## Etapa 5 — Primera visualización web y detección de error conceptual

Una vez confirmada la llegada de los datos a la nube, se desarrolló una primera versión de la interfaz web, cuyo objetivo era transformar las lecturas en un porcentaje de humedad visible para el usuario.

### Problema detectado

La visualización mostraba valores casi constantes cercanos al 100%, sin cambios significativos entre mediciones.

Esto generó la impresión inicial de que existía un error en el cálculo o en la lectura de los datos.

### Causa del problema

Al analizar el sistema completo, se identificó que el error no estaba en el código de la interfaz, sino en la interpretación del hardware.

Se había asumido que el sistema funcionaba con un sensor de humedad de suelo tradicional, cuando en realidad se estaba trabajando con **cuatro electrodos conectados a distintas partes de la planta** (hojas, tallo y sustrato).

Por lo tanto, los valores obtenidos no representaban humedad directa, sino variaciones de conductividad eléctrica entre puntos biológicos.

---

## Etapa 6 — Rediseño de la visualización: “La Voz de las Plantas”

Debido a la naturaleza real de los datos, se decidió rediseñar completamente la visualización para que no dependiera de una interpretación de “humedad”, sino de comportamiento dinámico del sistema.

Se desarrolló una interfaz más orgánica, compuesta por:

- Ondas circulares en movimiento continuo  
- Partículas reactivas que responden a los cambios de datos  
- Un núcleo central pulsante como elemento principal de la visualización  

### Ajustes implementados

- Se modificó la respuesta visual utilizando una función no lineal, lo que permitió amplificar las diferencias entre valores bajos y altos.
- Se incorporó un panel de estado del sistema con información en tiempo real:
  - Estado de conexión con HiveMQ  
  - Hora del último mensaje recibido  
  - Contador de mensajes entrantes  

Esto permitió monitorear no solo los datos, sino también la estabilidad de la conexión durante pruebas y grabaciones.

---

## Etapa 7 — Corrección del modelo de interpretación del sensor

Al seguir observando los datos en el monitor serial, se confirmó que el sistema no estaba midiendo humedad de forma real, sino variaciones eléctricas entre los electrodos.

Se revisaron distintos enfoques hasta llegar a la interpretación correcta del comportamiento del sensor.

### Modelo inicial (incorrecto)

Se intentó inicialmente convertir los valores del ADC en un porcentaje de humedad utilizando un rango de referencia entre estado seco y mojado:

```cpp
const int VALOR_SECO   = 17000;   // Valor cuando el suelo está SECO
const int VALOR_MOJADO = 8000;    // Valor cuando el suelo está MOJADO

int16_t valorCrudo = ads.readADC_SingleEnded(0);
int humedad = map(valorCrudo, VALOR_SECO, VALOR_MOJADO, 0, 100);
humedad = constrain(humedad, 0, 100);
```

## Problema real identificado

Se confirmó que el sistema no correspondía a un sensor de humedad de suelo convencional, sino a un conjunto de **cuatro electrodos distribuidos en diferentes zonas de la planta** (hojas, tallo y sustrato).

A partir de esto, se entendió que los valores obtenidos no debían interpretarse como humedad directa, sino como variaciones de **conductividad eléctrica entre distintos puntos del organismo vegetal**, lo que cambia completamente el tipo de lectura y su significado.

---

## Conclusión

Esta sesión permitió consolidar un cambio relevante dentro del desarrollo del proyecto: se dejó atrás una solución dependiente de servicios externos inestables para avanzar hacia una arquitectura propia basada en **MQTT con HiveMQ Cloud**, logrando comunicación en tiempo real entre ubicaciones distintas.

Además, se reforzó un aprendizaje importante a nivel de diseño del sistema: muchos de los errores que inicialmente parecen fallas de programación en realidad provienen de una interpretación incorrecta del hardware. Entender con precisión qué está midiendo el sistema es un paso esencial antes de aplicar cálculos, modelos o visualizaciones sobre los datos obtenidos.
