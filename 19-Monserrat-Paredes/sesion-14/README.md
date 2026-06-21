# sesion-14

lunes 15 junio 2026

Problema que se puede tener: La puerta es bidireccional, registra el dato de una persona más de una vez, si entro y salgo me registre dos veces, cómo si fueran 2 personas. El sensor es "ciego" a la dirección.

Alcance corto -> generalmente entre 2 y 30 cm.

La gente entra y sale por la misma puerta.


# Solución: investigación funcionamiento

se puede solucionar ya que un sendor detecta entrada o salida, si quisieramos registrar ambos datos necesitariamos 2 sensores.

## Opción 1: Aprovecgar el sentido de la puerta 

Colocación en ángulo: En lugar de poner el sensor apuntando recto (90° respecto a la pared), colócalo en un ángulo diagonal de 45° mirando hacia afuera (hacia el pasillo). Alguien que entra activará el sensor de frente, pero alguien que sale pasará por detrás del cono de detección del infrarrojo, reduciendo drásticamente las marcas de salida.

Tip que podría ayudar: Dirección del sensor, usa el potenciómetro pequeño (el tornillo que trae el propio sensor IR) para regular la distancia de detección. No dejes que mida todo el ancho de la puerta; ajústalo para que solo detecte objetos que pasen a un máximo de 15 o 20 cm del sensor. Así, el cambio de dirección física a 45° será sumamente eficiente separando las entradas de las salidas.


## Opción 2: Configurar la Raspberry Pi Pico 2W (mejor solución segun gemini)

Para que cada pasada cuente como un único "movimiento", se puede hacer que la base de datos o el Arduino UNO R4 divida el total de detecciones por 2.

Si el sensor detecta 20 movimientos en total (entre entradas y salidas) durante la hora de almuerzo, tu código asume que el flujo real de ocupación aumentó en 10 personas. Para un proyecto que busca mostrar el ritmo y las fluctuaciones, este margen de aproximación funciona bastante bien.

Para asegurar que una sola persona no marque dos veces seguidas al cruzar, necesitas implementar el delay inteligente en el código de tu Pico (usualmente programada en MicroPython). Este script usa un bloqueo de 2 segundos:

Para que cualquiera de las dos opciones de dirección funcione, necesitas este código en tu Pico. Incluye un tiempo de bloqueo personalizable (lo ideal para este flujo es configurarlo entre 2.0 y 3.0 segundos) para asegurar que, tras la detección inicial en la dirección correcta, el sensor ignore el resto del paso de la persona.


El código para tu Raspberry Pi Pico 2W:

```cpp
import machine
import time

# Configuración del pin del sensor (ajusta el número de pin GP según tu circuito)
PIN_SENSOR = 2  
sensor = machine.Pin(PIN_SENSOR, machine.Pin.IN, machine.Pin.PULL_UP)

contador_entradas = 0
ultimo_registro = 0

# TIEMPO DE BLOQUEO (En segundos):
# Ajusta este tiempo según lo que tarda una persona en terminar de pasar la puerta.
TIEMPO_BLOQUEO = 2.5  

print("--- Puente Digital: Conteo de Entradas LID ---")

while True:
    # Los sensores evasores de obstáculos FC-51 entregan 0 (LOW) al detectar presencia
    if sensor.value() == 0:
        tiempo_actual = time.time()
        
        # Filtro de delay inteligente: Solo cuenta si pasó el tiempo de bloqueo
        if (tiempo_actual - ultimo_registro) >= TIEMPO_BLOQUEO:
            contador_entradas += 1
            print(f"[NUEVA ENTRADA] Total personas en LID: {contador_entradas}")
            
            # --- AQUÍ CONECTAS TU ENVÍO A LA API / ADAFRUIT IO ---
            # Ejemplo: enviar_dato_wifi(contador_entradas)
            # -----------------------------------------------------
            
            # Registra el momento exacto de la entrada para activar la "ceguera"
            ultimo_registro = tiempo_actual
            
    # Pequeño delay de estabilidad para evitar que el bucle sature el procesador
    time.sleep(0.05)
```

## Opción 3: Cambiar de conteo numérico -> Métrica de intensidad o pulso

Torniquete -> termómetro que mide la vitalidad del LID (en tiempo real, flujo constante)

Cada vez que el sensor del LID detecta un paso (sea entrada o salida), manda un pulso. Si hay muchos pulsos seguidos, el anillo LED se enciende rápido y cambia a colores cálidos/alerta (el espacio está "hirviendo" de movimiento). Si nadie pasa, el anillo se va apagando lentamente. Esto calza perfecto con la idea de mostrar el "ritmo" y el desborde del lugar.

Ejemplo del funcionamiento del anillo led:

- 0% de Energía: Sala en calma. El anillo está apagado o en un azul/verde muy tenue.

- 50% de Energía: Flujo constante. El anillo se llena hasta la mitad con colores amarillos y naranjas.

- 100% de Energía: ¡LID desbordado! Las 16 luces del anillo brillan intensamente en color rojo vivo o parpadean.


Código para el Arduino UNO R4 WiFi:

```cpp
#include <Adafruit_NeoPixel.h>

#define PIN_NEOPIXEL  6   // Pin de datos conectado al anillo LED
#define NUM_LEDS      16  // Tu anillo de 16 LEDs

Adafruit_NeoPixel anillo(NUM_LEDS, PIN_NEOPIXEL, NEO_GRB + KHZ800);

int pulsosAnteriores = 0;
int pulsosActuales = 0; // Este valor lo debes actualizar con lo que recibas por Wi-Fi

float energia = 0.0;           // Nivel de energía actual de la sala (0 a 100)
float tasaDesgaste = 0.15;     // Qué tan rápido se enfría la sala (ajustable)
unsigned long ultimoTiempo = 0;

void setup() {
  anillo.begin();
  anillo.show(); // Inicializa todos los LEDs apagados
  Serial.begin(9600);
}

void loop() {
  // --- SIMULACIÓN DE RECEPCIÓN WI-FI ---
  // Aquí debes integrar tu código que lee desde Adafruit/API y actualiza 'pulsosActuales'
  // -------------------------------------

  // 1. Monitorear si llegaron nuevos pulsos desde el LID
  if (pulsosActuales > pulsosAnteriores) {
    int nuevosPulsos = pulsosActuales - pulsosAnteriores;
    
    // Cada pulso nuevo inyecta 25 unidades de energía
    energia = energia + (nuevosPulsos * 25.0); 
    if (energia > 100.0) energia = 100.0; // Límite máximo
    
    pulsosAnteriores = pulsosActuales;
  }

  // 2. Lógica de Desgaste (Enfriamiento constante del espacio)
  if (millis() - ultimoTiempo >= 50) { // Se ejecuta cada 50 milisegundos
    ultimoTiempo = millis();
    
    if (energia > 0.0) {
      energia = energia - tasaDesgaste;
    } else {
      energia = 0.0;
    }
    
    // 3. Actualizar la visualización del anillo LED según la energía
    actualizarAnillo(energia);
  }
}

void actualizarAnillo(float nivelEnergia) {
  // Calculamos cuántos LEDs se deben encender (de 0 a 16)
  int ledsPrendidos = map(nivelEnergia, 0, 100, 0, NUM_LEDS);
  
  // Definir color según la temperatura de la energía
  uint32_t colorActual;
  
  if (nivelEnergia < 35.0) {
    colorActual = anillo.Color(0, 255, 100);   // Verde/Cian: Sala calmada, ritmo lento
  } else if (nivelEnergia < 75.0) {
    colorActual = anillo.Color(255, 130, 0);   // Naranja: Ritmo constante, ocupación media
  } else {
    colorActual = anillo.Color(255, 0, 0);     // Rojo: ¡Desborde, movimiento intenso!
  }

  // Encender los LEDs que correspondan
  for (int i = 0; i < NUM_LEDS; i++) {
    if (i < ledsPrendidos) {
      anillo.setPixelColor(i, colorActual);
    } else {
      anillo.setPixelColor(i, anillo.Color(0, 0, 0)); // Apagar el resto
    }
  }
  anillo.show();
}
```

Resultado visual: Si el LID está vacío, el anillo estará completamente apagado. Si entra un grupo de 3 personas seguidas, el anillo se encenderá de golpe hasta la mitad en color naranja. Si el flujo se detiene, se vera cómo los LEDs se van apagando uno a uno, como un eco que se desvanece, reflejando que el ritmo bajó. Si la sala se llena por completo de eventos, los 16 LEDs brillarán en un rojo intenso estático.

Si el aforo es 0, el anillo en la FADD está apagado. Si el aforo sube a 15, el anillo se enciende hasta la mitad. Si hay un evento en el LID y entra mucha gente, el anillo se completará y brillará por completo en República 180, alertando del "desborde".


## Puntos importantes

Adafruit IO: genera un feed llamado lid-conteo, y obtén mi AIO Username y AIO Key desde la sección "My Key" del tablero. Reemplazar esos valores en ambos códigos junto con el SSID/contraseña de WiFi.
Lógica del sensor: el código actual incrementa el contador cada vez que detecta un objeto (cada persona = +1) y reinicia a 0 al llegar a 16. Si quieren un conteo neto real (entradas - salidas), necesitarían dos sensores (uno detectando dirección de entrada, otro de salida) ya que un solo sensor IR no puede distinguir la dirección del movimiento.
Colores del anillo: verde (1-5 personas), amarillo (6-10), rojo (11-16). Pueden cambiar los rangos o usar un solo color según su mensaje visual.


## Investigación sobre Apis

Información sacada de: 

https://openweathermap.org/api

https://www.ibm.com/es-es/think/topics/api

Una API (por sus siglas en inglés, Application Programming Interface o Interfaz de Programación de Aplicaciones) es un componente fundamental en el desarrollo de software moderno.


## Origen

Aunque hoy asociamos las API a las páginas web, el concepto nació en 1968. Los científicos de computación Ira Cotton y Frank Greatorex crearon un sistema para que diferentes programas de software pudieran interactuar dentro de una misma computadora principal. Internet ni siquiera existía tal como lo conocemos.


## ¿Qué es una API?

Según la documentación de IBM, una API es un conjunto de reglas, protocolos y especificaciones que permite que diferentes aplicaciones informáticas se comuniquen entre sí para intercambiar datos, características y funcionalidades.

En lugar de crear cada herramienta u origen de datos desde cero, las API permiten a los desarrolladores conectar e integrar sistemas existentes de forma rápida y segura. Actúan como un puente o intermediario invisible para el usuario final, ofreciendo una conexión fluida dentro del software.


## El concepto de "Caja Negra" y Seguridad

Las API permiten compartir únicamente la información necesaria para una solicitud específica, manteniendo ocultos los detalles internos del código, el servidor o la base de datos. Esto añade una capa crítica de seguridad, ya que los dispositivos externos no tienen acceso total al sistema, sino solo a pequeños paquetes de datos autorizados.


## ¿Cómo funciona una API?

El funcionamiento básico de una API sigue el modelo de Cliente y Servidor a través de la infraestructura de Internet, normalmente mediante el protocolo HTTP (sistema de reglas mediante el cual un cliente (como una app o web) y un servidor se comunican). 


IBM lo ejemplifica de manera sencilla a través de los siguientes pasos:

Cliente / App  --- (1) Envía Petición (URI/HTTP) --->  API ---> (2) Llama al programa externo

Cliente / App <--- (4) Entrega Datos en Pantalla <-- Bridge  <--- (3) Responde con la información <--- Servidor Externo


1. La Petición (Request): Una aplicación (el cliente) envía una solicitud de datos a través de una dirección específica (URI). Esta petición incluye un verbo de solicitud (como GET para leer datos o POST para enviar datos) y una cabecera.

2. El Procesamiento: La API toma la solicitud y llama al servidor web o programa externo que contiene la información.

3. La Respuesta (Response): El servidor procesa la orden y envía los datos de vuelta a la API (generalmente organizados en formatos estandarizados y ligeros como JSON o XML).

4. La Entrega: La API transfiere estos datos a la aplicación inicial, que los interpreta y los muestra al usuario en su interfaz.


Un ejemplo cotidiano es cuando compras en una tienda online y seleccionas "Pagar con PayPal". La tienda no conoce tus claves bancarias; utiliza una API para comunicarse con PayPal, procesar el pago de forma segura y recibir de vuelta la confirmación de que el pago fue exitoso.


## Tipos de API

IBM clasifica las API principalmente bajo dos criterios: su accesibilidad (casos de uso en la web) y su arquitectura técnica.

- API Abiertas (o Públicas): Son de código abierto y cualquier desarrollador puede acceder a ellas a través del protocolo HTTP. Tienen puntos de conexión (endpoints) y formatos de respuesta definidos públicamente.

- API de Socios (Partner APIs): Diseñadas para conectar con socios estratégicos de negocio. Se accede a ellas mediante portales específicos de desarrolladores, pero requieren un proceso de validación y credenciales de inicio de sesión específicas.

- API Internas (o Privadas): Permanecen ocultas para el público general. Las empresas las utilizan internamente para comunicar diferentes componentes o departamentos de desarrollo y mejorar la productividad.

- API Compuestas: Combinan múltiples API de datos o servicios diferentes. Permiten que un programador haga una única llamada y obtenga información de varias fuentes a la vez (muy útil en arquitecturas de microservicios).


## Protocolos y estilos arquitectónicos:

- REST (Representational State Transfer): Es el estilo más común en las API web modernas. Utiliza el protocolo HTTP, es ligero y es compatible con múltiples lenguajes de programación y formatos como JSON.

- SOAP (Simple Object Access Protocol): Un protocolo de mensajería rígido y altamente estructurado basado estrictamente en XML, muy utilizado en entornos empresariales que requieren alta seguridad y contratos de datos estrictos.

- RPC (Remote Procedure Call): Protocolos orientados a ejecutar procedimientos o tareas en sistemas remotos como si fuesen locales (pueden basarse en XML o JSON).


## ¿Cómo se empieza a usar una API?

La plataforma de OpenWeather muestra los tres pasos estándar de la industria para trabajar con este recurso:

- Registro y API Key: El desarrollador crea una cuenta y la plataforma le otorga una API Key (una clave o token alfanumérico). Esta clave funciona como una firma digital o contraseña para rastrear quién hace la petición y controlar los límites de consumo.

- Consulta de la documentación: Se revisa el manual técnico para saber exactamente cómo escribir la dirección URI de la consulta.

- Integración: Se programa la llamada dentro del código de la aplicación para automatizar la solicitud de datos.

En resumen, las API son el tejido conectivo de internet. Permiten que un diseñador o programador cree una aplicación que muestre mapas interactivos, procese pagos o dé el pronóstico del tiempo en tiempo real, delegando la complejidad de los datos a servicios expertos externos.
