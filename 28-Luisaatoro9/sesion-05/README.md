# sesion-05 - lunes 06 abril 2026

### solemne 1

Resumen de la sesión

Hoy fue el **"bautismo de fuego" en el Internet de las Cosas (IoT)** para la Solemne 01.  
Decidimos cambiar el hardware y usar **dos placas Arduino Uno R4 WiFi** para asegurar la comunicación.  


### Inicio Solemne 01: Creando el Ecosistema IoT

Para que el proyecto funcione, aprendí que hay que armar un **"cerebro" en la nube**.  
Mi investigación se centró en configurar **Adafruit IO** como centro de mando:

- **🔐 Identidad y Seguridad:**  
  Creé mi cuenta y obtuve la **AIO Key**. Entendí que funciona como un token dinámico secreto, si se sube a GitHub, el proyecto queda vulnerable.

- **📬 Buzón de datos (Feeds):**  
  Configuré mis primeros feeds (un feed por cada origen de datos).  
  Lo mejor de Adafruit es que permite conexiones vía **MQTT sobre WebSockets (puerto 443)**.  
  Como este puerto es el mismo que usa el tráfico HTTPS normal, logramos saltarnos el firewall de la U que bloqueaba el puerto MQTT estándar (1883).

- **🧩 Software y Bibliotecas:**  
  Actualicé el IDE a la versión 2.3.8 e instalé la biblioteca **Adafruit IO Arduino**.  
  Aquí comprendí las dependencias: la biblioteca necesita "ayudantes" como `HttpClient` y `Adafruit_MQTT` para gestionar la comunicación inalámbrica.

---

## Ejercicios Prácticos en Clase - Ejercicio 1: Conexión y Monitor Serial

- **Configuración de red:**  
  Al principio la placa no detectaba mi celular.  
  Aprendí que en redes la precisión es absoluta: una mayúscula mal puesta en el SSID impide la conexión.  
  Además, tuve que configurar mi Hotspot en **2.4 GHz**, ya que el Arduino no "ve" la frecuencia de 5 GHz.

- **Sincronización:**  
  Inicialmente veía símbolos extraños (rombos).  
  Era un error de **baudios**: el código definía `115200` pero el monitor estaba en `9600`.  
  Al sincronizarlos, pude ver el estado de **"conectado"**.

---

###  Ejercicio 2: El drama del LED y el voltaje

- **Fail del día:**  
  ¡Se nos quemó un LED!  
  Entre tanto cable, usamos una resistencia que no correspondía y el componente no aguantó.

- **Aprendizaje técnico:**  
  Usamos el multímetro para revisar el voltaje.  
  Entendí que no es llegar y conectar; hay que saber cuánta energía aguanta cada pieza.  

  Además, visualicé la lógica **bidireccional**:  
  `botón web → nube → Arduino`

---

###  Hallazgos 

- **Estructura:**  
  `#include` siempre va arriba; es como presentar a los invitados antes de la fiesta.

- **Limitaciones:**  
  El plan gratuito tiene un **Rate Limiting de 30 datos por minuto**.  
  Hay que cuidar el tráfico para que no nos bloqueen la cuenta.

### Referencias

* Adafruit. (s.f.). *Adafruit IO basics: Digital output (Arduino setup)*. https://learn.adafruit.com/adafruit-io-basics-digital-output/arduino-setup

* Adafruit. (s.f.). *Adafruit IO basics: Feeds*. https://learn.adafruit.com/adafruit-io-basics-feeds

* Adafruit. (s.f.). *Welcome to Adafruit IO*. https://learn.adafruit.com/welcome-to-adafruit-io

* Adafruit IO. (s.f.). *API documentation: Limits*. https://io.adafruit.com/api/docs/#limits

* Arduino. (s.f.). *WiFi examples (UNO R4 WiFi)*. https://docs.arduino.cc/tutorials/uno-r4-wifi/wifi-examples/

