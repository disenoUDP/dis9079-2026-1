# sesion-13

lunes 08 junio 2026

## Trabajo en clases (avance examen)

Examen: 22 de junio

Edificio A: Salvador Sanfuentes (Medición de datos).

Edificio B: FADD, Republica 180 (Reacción de los datos).

# Contexto proyecto

Puente digital

Nuestro proyecto parte desde la pregunta `¿Cuántos habitan los lugares de trabajo?`, nos interesa capturar el conteo de personas que entran al lugar de trabajo en la Universidad; y visualizarlo en el otro edificio. En este caso, ver cuanta gente entra al LID en Salvador Sanfuentes y visualizarlo en Rep180. Dos edificios, dos espacios de trabajo que coexisten sin saber cuánta gente entra en cada una. En la puerta del LID se instala un *Sensor Infrarrojo Evasor de Obstáculos* conectado a una Raspberry PI Pico 2W, que mide el flujo de gente que entra a este espacio; esto lo denominaremos `entrada`. Esta información se envía de manera inalámbrica a través de wifi a una base de datos (API o Adafruit) que lleva el conteo de la gente. Finalmente, en Rep180, el sistema responde encendiendo y completando cada píxel de un *Anillo LED RGB WS2812 de 16 leds* conectada al Arduino UNO R4 wifi; de esta manera, las personas que están en Rep180 pueden ver mediante una señal visual qué tan rápido se va llenando el LID, esto lo denominaremos `salida`. El mensaje que queremos transmitir es hacer visible el ritmo con que los espacios se llenan, los momentos en que el LID se desborda; es una fluctuación constante que todos vivimos pero nadie registra.


# Pseudocódigo

cómo encontrar el maximo de un numero, estructuras logicos o planificaciones del codigo para saber cómo funciona.

Diagrama de flujo -> mermaid


PROYECTO: Puente Digital
EDIFICIO A → LID (Salvador Sanfuentes)
EDIFICIO B → Rep180

════════════════════════════════════════
MÓDULO A — Arduino UNO R4 WiFi (LID)
════════════════════════════════════════

VARIABLES:
  conteo        ← 0
  umbral        ← 16        // máximo del anillo LED
  estadoSensor  ← LIBRE

INICIALIZAR:
  conectar WiFi (SSID, PASSWORD)
  conectar Adafruit IO (usuario, clave, feed: "lid-conteo")
  configurar pin sensor infrarrojo como ENTRADA

BUCLE PRINCIPAL:
  LEER estadoSensor ← sensor infrarrojo

  SI estadoSensor == OBSTRUIDO:
    esperar hasta estadoSensor == LIBRE   // persona cruzó completamente
    conteo ← conteo + 1
    
    SI conteo > umbral:
      conteo ← umbral                    // tope máximo

    PUBLICAR conteo → Adafruit IO (feed: "lid-conteo")
    esperar 500ms                        // evitar lecturas duplicadas

════════════════════════════════════════
MÓDULO B — Arduino UNO R4 WiFi (Rep180)
════════════════════════════════════════

VARIABLES:
  conteo        ← 0
  totalLeds     ← 16
  ledsActivos   ← 0

INICIALIZAR:
  conectar WiFi (SSID, PASSWORD)
  conectar Adafruit IO (usuario, clave, feed: "lid-conteo")
  configurar anillo LED WS2812 (16 leds)
  apagar todos los LEDs

BUCLE PRINCIPAL:
  SUSCRIBIR a Adafruit IO (feed: "lid-conteo")

  SI llega nuevo valor:
    conteo ← valor recibido
    ledsActivos ← MAPEAR(conteo, 0, 16, 0, totalLeds)

    PARA i DESDE 0 HASTA totalLeds - 1:
      SI i < ledsActivos:
        SI ledsActivos <= 5:
          encender LED[i] → color VERDE   // poco ocupado
        SI ledsActivos <= 10:
          encender LED[i] → color AMARILLO // ocupación media
        SI ledsActivos <= 16:
          encender LED[i] → color ROJO    // casi lleno o lleno
      SINO:
        apagar LED[i]



# Lista de materiales

Que cosas vamos a necesitar / dibujos de planificación

- Sensor Infrarrojo Evasor de Obstáculos: Es ideal si quieres esconder la tecnología. Al ser tan pequeño, se puede poner en la entrada del LID y dejar asomados solo los dos pequeños LED, Para luego registrar el tránsito del LID.

Cómo funciona sensor:

https://www.luisllamas.es/detectar-obstaculos-con-sensor-infrarrojo-y-arduino/

https://agelectronica.lat/pdfs/textos/O/OKY3127.PDF

  
- Anillo LED RGB WS2812 de 16 leds (más economico) -> Matriz LED RGB 8×8 con WS2812B – 64 píxeles direccionables (menos economico).

Se ocupara para visualizar que tan rapido se va llenando el LID (Registra y visualiza los datos).

Codigo para el anillo led -> https://github.com/adafruit/Adafruit_NeoPixel/blob/master/Adafruit_NeoPixel.cpp

- Arduino R4 wifi

- Base de impresión 3d -> tipo totem


# Codigo de prueba con consola simulado

poner datos al azar y cuando funcione cambiarlo los datos reales y rangos buscados.

