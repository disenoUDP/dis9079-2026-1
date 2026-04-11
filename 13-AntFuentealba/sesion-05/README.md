# sesion-05

lunes 06 abril 2026

solemne 1

Aaron atraso la solemne porque todos estabamos muy perdidos

## Apuntes

## Adafruit IO

Adafruit IO es una plataforma en la nube orientada a proyectos de Internet de las Cosas (IoT). Permite conectar dispositivos como Arduino, ESP8266 o Raspberry Pi para:

- Enviar datos a internet  
- Recibir datos desde la nube  
- Visualizar información en tiempo real  
- Controlar dispositivos remotamente  



## Conexión

Para conectarse a Adafruit IO es necesario usar credenciales únicas:

```cpp
#define IO_USERNAME  "usuario"
#define IO_KEY       "clave"
```

Estas variables permiten autenticar el dispositivo en la plataforma.

Es fundamental incluirlas siempre para mantener la conexión activa.



## Librería 

La librería facilita la comunicación entre el dispositivo y la nube.

Permite:

- Enviar datos (publish)  
- Recibir datos (subscribe)  
- Mantener conexión en tiempo real  
- Trabajar con feeds  



## Funciones clave

- `io.run();`  
  Mantiene la conexión activa y procesa datos entrantes.

- `io.feed();`  
  Permite acceder a un feed específico para enviar o recibir datos.


## Feeds (canales de datos)

Los feeds son el elemento central de Adafruit IO. Funcionan como contenedores donde se almacenan los datos.

### Tipos de datos

- Valores de sensores (temperatura, humedad, etc.)  
- Estados de dispositivos (encendido/apagado)  
- Variables de control  

### Metadatos

Cada feed puede incluir:

- Privacidad (público o privado)  
- Licencia de uso  
- Descripción del contenido  


### Regla importante

- Se debe crear un feed por cada fuente de datos distinta.  

Ejemplo:  
Un sensor de temperatura y dos de humedad → 3 feeds.


## Dashboards

Los dashboards son paneles visuales donde se muestran los datos.

### Funciones

- Visualizar datos en gráficos  
- Controlar dispositivos  
- Monitorear variables en tiempo real  

### Creación básica

1. Ir a la sección “Dashboards”  
2. Crear uno nuevo  
3. Asignar nombre y descripción  
4. Agregar bloques vinculados a feeds  


## Funcionamiento 

1. El dispositivo se conecta a WiFi  
2. Se conecta a Adafruit IO mediante la librería  
3. Envía o recibe datos a través de feeds  
4. Los datos se visualizan en dashboards  



## Ejemplo: Envío de datos (Publish)

El siguiente código permite enviar datos a Adafruit IO mediante un feed.

Importante: las credenciales deben guardarse en `config.h` y no subirse a repositorios públicos.

```cpp
#include "config.h"

int contador = 0;

// definir feed
AdafruitIO_Feed *nombreFeed = io.feed("grupoXX");

void setup()
{
  Serial.begin(115200);

  while (!Serial);

  Serial.print("conectando a Adafruit IO");

  io.connect();

  while (io.status() < AIO_CONNECTED)
  {
    Serial.print(".");
    delay(500);
  }

  Serial.println();
  Serial.println(io.statusText());
}

void loop()
{
  io.run();

  Serial.println("enviando -> " + String(contador));

  nombreFeed->save(contador);

  contador = contador + 1;

  delay(3000);
}
```

---

## Explicación

- Se conecta a WiFi  
- Se autentica con Adafruit IO  
- Envía datos a un feed  
- Repite el envío periódicamente  
- Permite visualizar los datos en la nube  



## Consideraciones 

- La velocidad del monitor serial debe coincidir con el código (ej: 115200 baud)  
- Adafruit IO tiene límites de envío de datos → usar `delay()`  
- Es recomendable separar credenciales en `config.h`  
- No subir claves a GitHub  

---

## Conceptos complementarios

### Firmware
El firmware es el software interno que permite que el hardware funcione correctamente. Actúa como puente entre software y hardware.


## Ideas clave

- Adafruit IO permite conectar hardware con la nube  
- Los feeds organizan los datos  
- Los dashboards visualizan la información  
- `io.run()` mantiene la comunicación activa  
- MQTT es el protocolo base de la plataforma  
- La seguridad de las credenciales es fundamental

## Experiencia
Esta clase fue muy frustrante porque no nos estaba resultando la conexión y yo personalmente me empece a abrumar, despues nos ayudo Aaron y Mateo, y me calme porque funciono todo y me di cuenta que la solemne no era tan complicada como pensaba.
