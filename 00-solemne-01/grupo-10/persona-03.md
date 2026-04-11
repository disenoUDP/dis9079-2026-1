# persona-01

investigaciones individuales (AntFuentealba)

## sobre adafruit i/o

### ¿Qué es Adafruit IO?

Adafruit IO es una plataforma en la nube orientada al Internet de las Cosas (IoT), que permite conectar dispositivos físicos como Arduino, ESP32 o Raspberry Pi a internet para enviar, recibir y visualizar datos en tiempo real.

Su principal función es facilitar la comunicación entre hardware y la nube, simplificando procesos complejos de programación mediante herramientas accesibles y visuales.

### Funcionamiento general

El sistema opera de la siguiente manera:

1. El dispositivo (Arduino) se conecta a una red WiFi  
2. Se autentica en Adafruit IO mediante credenciales  
3. Envía o recibe datos a través de feeds  
4. Los datos se visualizan en dashboards en tiempo real  

Este proceso permite la interacción remota con dispositivos físicos, lo que es clave en sistemas IoT.

### Autenticación y conexión

Para establecer la conexión es necesario definir credenciales únicas en el código:

```cpp
#define IO_USERNAME "usuario"
#define IO_KEY "clave"
```

Además, se deben incluir las credenciales de la red WiFi:

```cpp
#define WIFI_SSID "nombre_wifi"
#define WIFI_PASS "contraseña_wifi"
```

### Librería 

La librería de Adafruit IO permite:

- Conectar el dispositivo a internet  
- Enviar datos a la nube (publish)  
- Recibir datos desde la nube (subscribe)  
- Mantener comunicación en tiempo real  

Internamente, esta comunicación se basa en protocolos como MQTT, pero la librería simplifica su uso.



### Funciones 

- `io.connect()` → inicia la conexión con Adafruit IO  
- `io.run()` → mantiene la conexión activa y procesa datos  
- `io.feed()` → define el canal de comunicación  
- `feed->save(valor)` → envía datos a la nube  

### Feeds 

Los feeds son el componente central de Adafruit IO. Funcionan como contenedores donde se almacenan los datos enviados por los dispositivos.

#### Tipos de datos

- Valores de sensores (temperatura, humedad, presión)  
- Estados de actuadores (encendido/apagado)  
- Variables de control  

#### Metadatos

Cada feed puede incluir configuraciones adicionales como:

- Privacidad (público o privado)  
- Licencia de uso  
- Descripción del contenido  

#### Regla de implementación

Se debe crear un feed por cada fuente de datos distinta.

Ejemplo:  
Un sensor de temperatura y dos sensores de humedad → 3 feeds.



### Modos de uso

#### Uso con código (API MQTT / REST)

- Control manual de feeds  
- Mayor flexibilidad  
- Requiere programación  

#### Uso sin código (WipperSnapper)

- Creación automática de feeds  
- Configuración desde interfaz gráfica  
- Orientado a usuarios sin experiencia en programación  



### Dashboards

Los dashboards son paneles visuales que permiten:

- Visualizar datos en gráficos  
- Controlar dispositivos  
- Monitorear variables en tiempo real  

#### Proceso de creación

1. Acceder a la sección “Dashboards”  
2. Crear un nuevo panel  
3. Asignar nombre y descripción  
4. Agregar bloques vinculados a feeds  

Los dashboards comienzan vacíos y se configuran manualmente según los feeds creados.


### Envío de datos (Publish)

El envío de datos se realiza mediante un feed, utilizando código en Arduino.

El sistema:

- Se conecta a WiFi  
- Se conecta a Adafruit IO  
- Envía datos periódicamente  
- Permite visualizar los datos en la nube  



### Consideraciones técnicas

- La velocidad del monitor serial debe coincidir con el código (ej: 115200 baud)  
- Adafruit IO tiene límites de envío de datos  
- Las credenciales deben almacenarse en archivos como `config.h`  
- No se deben compartir claves en repositorios públicos  


### Firmware

El firmware es el software interno que permite el funcionamiento del hardware. Actúa como intermediario entre el sistema físico y el software, permitiendo la comunicación con módulos como WiFi o Bluetooth.


### Resumen

Adafruit IO es una herramienta clave para el desarrollo de proyectos IoT, ya que permite integrar dispositivos físicos con sistemas en la nube de manera simple y eficiente.

Su estructura basada en feeds y dashboards facilita tanto la transmisión como la visualización de datos, mientras que su compatibilidad con Arduino y otros dispositivos la convierte en una plataforma accesible para el desarrollo de sistemas interactivos en tiempo real.


## sobre artista, diseñadora o producto que usa electrónica o computación inalámbricas


Laurie Anderson es una artista, música y performer estadounidense nacida en 1947, reconocida como una de las figuras más influyentes del arte contemporáneo y la experimentación tecnológica.

Su trabajo combina múltiples disciplinas:
- Música electrónica  
- Performance  
- Arte visual  
- Literatura  
- Tecnología  

Desde los años 70, ha desarrollado una práctica centrada en la relación entre **lenguaje, tecnología y experiencia humana**.


### Contexto

Se formó en:
- Historia del arte (Barnard College)  
- Escultura (Columbia University)  

Su formación explica su enfoque interdisciplinario, combinando arte conceptual con tecnología y medios digitales.


### Obra

Uno de sus trabajos más conocidos es:

- **O Superman (1981)**  

Esta obra utiliza loops de voz procesada y electrónica, logrando un impacto tanto en el arte experimental como en la cultura popular.

#### 1. Uso del lenguaje
El lenguaje es un elemento central en su trabajo:
- Narración fragmentada  
- Uso de la voz como instrumento  
- Reflexión política y cultural  

#### 2. Tecnología como medio artístico

Anderson ha sido pionera en integrar tecnología en el arte:

- Sintetizadores  
- Procesamiento de voz  
- Interfaces electrónicas  
- Instrumentos diseñados por ella misma  

Ejemplo:
- Violines electrónicos  
- Dispositivos con sensores  

#### 3. Interdisciplinariedad

Su trabajo combina:
- Música  
- Video  
- Performance en vivo  
- Instalaciones multimedia  

Esto la posiciona como una referente del arte digital contemporáneo.

#### 4. Relación con lo digital

Explora temas como:
- Inteligencia artificial  
- Comunicación digital  
- Interfaces humanas  
- Cultura de datos  

Su obra anticipa muchas de las discusiones actuales sobre tecnología.


### Otros trabajos

#### United States I–IV (1983)
Obra multimedia que mezcla narrativa, música y tecnología para reflexionar sobre la cultura estadounidense.


#### The End of the Moon
Proyecto desarrollado tras su residencia en la NASA, donde combina ciencia, narrativa y performance.


#### Homeland / Happiness
Obras que integran storytelling con crítica social y política.


#### Landfall (2019)
Proyecto musical inspirado en el huracán Sandy, centrado en la memoria y el cambio climático.



### Relación con tecnología y ciencia

Fue la primera artista en residencia de la NASA, lo que evidencia su conexión con el mundo científico.

Su trabajo demuestra que:
- El arte y la ciencia comparten procesos experimentales  
- La tecnología puede ser un medio expresivo  

### Enfoque conceptual

Su obra aborda temas como:

- Identidad  
- Memoria  
- Lenguaje  
- Política  
- Tecnología  

Explora cómo las tecnologías influyen en:
- La percepción  
- La comunicación  
- La experiencia humana  


### Relación con la interacción digital

Laurie Anderson es relevante en el contexto de la interacción digital porque:

- Integra tecnología en experiencias artísticas  
- Utiliza interfaces como parte de la obra  
- Trabaja con datos y tiempo real  
- Genera nuevas formas de interacción  


### Impacto en el arte contemporáneo

Su influencia incluye:

- Desarrollo del arte multimedia  
- Uso experimental del sonido y la voz  
- Integración de tecnología en el arte  

Ha inspirado a artistas en:
- Arte digital  
- Música experimental  
- Performance  

### Conclusión

Laurie Anderson es una figura clave en la relación entre arte y tecnología. Su trabajo demuestra que la tecnología no solo cumple una función técnica, sino que también puede ser un medio expresivo para explorar nuevas formas de comunicación y experiencia.

Su enfoque interdisciplinario la convierte en una referente fundamental para comprender el arte digital y la interacción contemporánea.


### Bibliografía

- Anderson, Laurie. *Official Website*. https://laurieanderson.com  
- Wikipedia. “Laurie Anderson”. https://en.wikipedia.org/wiki/Laurie_Anderson  
- Smithsonian Magazine. “The Multiple Arts of Laurie Anderson”. https://www.smithsonianmag.com  
- Harvard Gazette. “The introspective Laurie Anderson”. https://news.harvard.edu  
- Museum of Modern Art (MoMA). “Laurie Anderson”. https://www.moma.org  
- MIT Media Lab (referencias generales sobre arte y tecnología). https://www.media.mit.edu  

