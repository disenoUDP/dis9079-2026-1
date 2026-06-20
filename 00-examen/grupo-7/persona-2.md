## Investigación textual sobre la API: MQTT y HiveMQ Cloud

### ¿Qué es una API en este contexto?

Una API (Interfaz de Programación de Aplicaciones) es el conjunto de reglas que permite que dos sistemas distintos —en este caso, el Arduino y la nube— se comuniquen entre sí sin que cada uno necesite conocer los detalles internos del otro. En el proyecto trabajé específicamente con el protocolo **MQTT** y el servicio en la nube **HiveMQ Cloud**, que implementa ese protocolo como servicio gestionado.

### MQTT 

Según JustProtocols (2026), MQTT es un protocolo de mensajería liviano basado en el patrón **publicador/suscriptor (pub/sub)**, diseñado originalmente en 1999 por Andy Stanford-Clark (IBM) y Arlen Nipper para monitorear oleoductos vía satélite, donde el ancho de banda era costoso y las conexiones poco confiables. El mismo autor señala que desde entonces el protocolo se convirtió en el estándar dominante para el Internet de las Cosas (IoT), siendo ahora un estándar abierto de OASIS, con MQTT 5.0 como su versión más reciente, publicada en 2019. De acuerdo con esta fuente, MQTT corre sobre TCP, usando el puerto 1883 sin cifrar y el puerto 8883 cuando se asegura con TLS — este último es el que usé en mi proyecto.

**Diferencia clave frente a HTTP:** JustProtocols (2026) explica que mientras HTTP sigue un modelo de solicitud-respuesta donde el cliente inicia cada intercambio, MQTT mantiene una conexión persistente con mensajería pub/sub, lo que lo hace mucho más eficiente para escenarios IoT con mensajes pequeños y frecuentes. Esto era justamente lo que necesitaba mi proyecto: que el Arduino enviara lecturas del sensor de forma constante sin tener que abrir una nueva conexión cada vez.

**Cómo funciona el modelo pub/sub:** según AWS (s.f.), los clientes MQTT envían un mensaje SUBSCRIBE al bróker para recibir mensajes de los topics de su interés. Por su parte, MQTTfy (2026) detalla que, a diferencia del modelo cliente-servidor tradicional donde los clientes se comunican directamente con un servidor, el modelo pub-sub desacopla al emisor del mensaje (el publicador) del receptor (el suscriptor), logrando esto a través de un componente central llamado bróker.

Este desacople fue lo que me permitió que mi Arduino (publicador) y mi página HTML de visualización (suscriptor) nunca necesitaran conocerse directamente entre sí — ambos solo necesitan conocer al bróker (HiveMQ) y el nombre del topic (`planta/voz`).

### HiveMQ Cloud

HiveMQ Cloud es un servicio de bróker MQTT completamente gestionado en la nube. Para mi proyecto utilicé específicamente el plan **Serverless**, que según la propia documentación de HiveMQ (s.f.-b) se puede usar de forma completamente gratuita, sin necesidad de tarjeta de crédito, siendo la forma ideal de aprender y experimentar con MQTT y HiveMQ Cloud.

De acuerdo con HiveMQ (s.f.-a), el plan gratuito incluye hasta 100 conexiones simultáneas sin costo y un límite de tránsito de datos de 10GB al mes, sobre una infraestructura de bróker compartida entre distintos usuarios del servicio. Para un proyecto académico con un par de dispositivos conectados (el Arduino y el navegador), estos límites resultaron más que suficientes.

---

### Por qué esta combinación fue adecuada para el proyecto 

La elección de MQTT sobre HiveMQ Cloud resolvió el problema central que detectamos al inicio del proyecto: la necesidad de comunicar dos ubicaciones físicas distintas sin depender de que ambas estuvieran en la misma red local. Al ser un protocolo orientado a IoT, de bajo consumo de datos y con conexión persistente, MQTT fue una elección natural frente a alternativas como HTTP, que habría requerido que el navegador consultara constantemente al servidor (polling) en lugar de recibir los datos de forma instantánea apenas el Arduino los publicaba.

---

### Proceso de implementación: fallos y errores encontrados

Durante la implementación de MQTT y HiveMQ Cloud en mi proyecto, pude darme cuenta de que se pueden cometer distintos tipos de errores al trabajar con una API. A continuación detallo los que me pasaron a mí durante el proceso.

**1. Caída del servicio original (dweet.io)**

El primer error no fue propiamente de MQTT, sino lo que me obligó a buscarlo: el servicio que estaba usando hasta ese momento, `dweet.io`, dejó de funcionar porque el sitio estaba caído. Esto me hizo darme cuenta de que depender de un servicio externo sin respaldo es un riesgo, y me llevó a buscar una alternativa más estable: HiveMQ Cloud como bróker MQTT.

**2. "Not connected" en el Arduino IDE**

Al cargar por primera vez el código que integraba la librería `ArduinoMqttClient`, el monitor serial me mostró el mensaje **"Not connected"**. En un primer momento pensé que era un error de la API o de mi código de conexión MQTT.

- **Lo que realmente pasaba:** no era un error de programación ni de la librería, sino que me faltaba conectar el cable USB y seleccionar el puerto correcto en el IDE.
- **Cómo lo solucioné:** conecté el Arduino por USB, seleccioné el puerto en `Herramientas → Puerto`, e instalé las librerías `ArduinoMqttClient` y `Adafruit ADS1X15`.

Esto me enseñó que no todo mensaje de error que aparece al trabajar con una API es culpa de la API en sí — a veces el problema está un paso antes, en la conexión física del hardware.

**3. Necesidad de confirmar que los datos sí llegaban al bróker**

Antes de confiar en que mi implementación de MQTT estaba funcionando, necesitaba verificar que los mensajes que publicaba realmente llegaban a HiveMQ. Usé el **Cliente Web de HiveMQ** para suscribirme al topic `planta/humedad` y observar los mensajes JSON en tiempo real, sin depender de tener la página HTML abierta al mismo tiempo. Esto me permitió aislar el problema: pude confirmar que la capa de comunicación (MQTT/HiveMQ) funcionaba correctamente, antes de revisar la lógica de mi propio código en el Arduino o en el HTML.

**4. Error conceptual en los datos que estaba publicando**

Una vez confirmado que el canal MQTT transmitía datos sin problemas, me encontré con un nuevo error: el valor de "humedad" que publicaba en el topic siempre marcaba 100%, sin importar la condición real de la planta.

- **Lo que realmente pasaba:** el problema no estaba en MQTT ni en HiveMQ, sino en la fórmula que yo aplicaba antes de publicar el dato. Estaba tratando el sensor como si fuera un sensor de humedad capacitivo de una sola entrada, cuando en realidad tenía 4 electrodos de conductividad eléctrica en distintos puntos de la planta.
- **Cómo lo solucioné:** modifiqué el payload que publicaba por MQTT para enviar los 4 valores crudos por separado (`hojaGrande`, `hojaChica`, `tallo`, `tierra`) más un promedio de actividad, en vez de un porcentaje de humedad que no tenía sentido.

Este fue el error que más me costó detectar, porque la API estaba funcionando perfectamente bien — el problema era que yo le estaba pidiendo que transportara un dato mal calculado.

**5. Cambio de nombre del topic**

Como consecuencia del punto anterior, me di cuenta de que el topic `planta/humedad` ya no representaba correctamente lo que estaba transmitiendo. Lo renombré a `planta/voz`, ya que el payload que publicaba dejó de ser información de humedad y pasó a ser la señal eléctrica de la planta interpretada como actividad.

### Que logre aprender del uso de la API

Al revisar todo mi proceso, me di cuenta de que ninguno de los errores que tuve fue, en rigor, un fallo del protocolo MQTT ni del servicio HiveMQ Cloud — ambos funcionaron de forma estable durante todo el desarrollo. Mis errores fueron, en cambio, de **configuración del entorno** (no tener seleccionado el puerto USB) y de **diseño del payload** (interpretar mal qué tipo de dato estaba publicando). Esto me dejó una idea clara: una API puede estar funcionando perfectamente bien a nivel de transporte de datos, mientras el contenido que viaja a través de ella sigue siendo conceptualmente incorrecto. Verificar la conexión y verificar el significado de los datos son dos pasos de depuración distintos, y ambos fueron necesarios para que mi proyecto llegara a funcionar.

---

### Conclusión

Investigar y trabajar con MQTT y HiveMQ Cloud me permitió entender, más allá de la implementación práctica, por qué este tipo de protocolo es el estándar en proyectos de IoT: su arquitectura publicador-suscriptor desacopla completamente el hardware emisor de la interfaz que consume los datos, lo que simplifica el diseño y permite escalar el sistema sin reescribir su lógica central. A diferencia de un protocolo como HTTP, MQTT está pensado desde su origen para dispositivos con recursos limitados y conexiones poco confiables, exactamente el escenario de un microcontrolador transmitiendo datos de un sensor en tiempo real.

Usar el plan gratuito Serverless de HiveMQ Cloud me demostró además que es posible construir una arquitectura de comunicación remota funcional, segura (mediante TLS) y persistente sin necesidad de administrar infraestructura propia ni incurrir en costos. Pero más importante que la herramienta en sí, este proceso me dejó una lección que va a servirme en cualquier proyecto futuro: cuando algo falla al trabajar con una API, no hay que asumir automáticamente que el problema está en la API. A veces está en la conexión física, y otras veces está en cómo uno mismo está interpretando los datos que esa API transporta.

---

## Referencias bibliográficas

AWS. (s.f.). *What is MQTT? MQTT protocol explained*. Amazon Web Services. https://aws.amazon.com/what-is/mqtt/

HiveMQ. (s.f.). *MQTT publish/subscribe architecture (pub/sub) – MQTT essentials: Part 2*. https://www.hivemq.com/blog/mqtt-essentials-part2-publish-subscribe/

HiveMQ. (s.f.). *HiveMQ Cloud – Fully-managed MQTT platform on the cloud*. https://www.hivemq.com/products/mqtt-cloud-broker/

HiveMQ. (s.f.). *Getting started with HiveMQ Cloud*. HiveMQ Documentation. https://docs.hivemq.com/hivemq-cloud/quick-start-guide.html

HiveMQ. (s.f.). *HiveMQ Console*. HiveMQ Documentation. https://docs.hivemq.com/hivemq-cloud/console.html

JustProtocols. (2026, 25 de marzo). *MQTT protocol explained: Publish-subscribe, QoS levels, topics & retained messages*. https://justprotocols.com/protocols/mqtt

MQTTfy. (2026, 15 de marzo). *Understanding the MQTT publish-subscribe model*. https://mqttfy.com/resources/understanding-mqtt-client-publish-subscribe

RisingWave. (s.f.). *Ingest data from HiveMQ broker*. https://docs.risingwave.com/integrations/sources/hivemq
