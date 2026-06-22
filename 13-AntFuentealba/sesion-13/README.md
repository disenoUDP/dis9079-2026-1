# sesion-13

lunes 08 junio 2026

## Preparación examen
En esta clase, Aarón nos pidió avanzar en distintos entregables del proyecto:

### Texto mejorado
El Oráculo es una experiencia interactiva que invita a los participantes a formular una pregunta en voz alta. Al iniciar, una pantalla OLED mostrará un mensaje de bienvenida con las instrucciones de uso: "Di tu pregunta y aplaude, el Oráculo te responderá".
Luego, mediante un aplauso, los participantes activan una consulta a través de una red inalámbrica. La intensidad del aplauso es capturada por un sensor de sonido y utilizada como punto de partida para generar una respuesta.
La propuesta funciona como una interpretación paródica de los oráculos tradicionales. En lugar de buscar respuestas verdaderas o revelaciones, el sistema entrega mensajes ambiguos, irónicos o contradictorios, invitando a cada participante a construir su propio significado.
La consulta es enviada a una entidad remota, entendida como un dispositivo conectado a la red que recibe los datos del aplauso, los interpreta y selecciona una respuesta a partir de la información recibida. Durante este proceso, un LED se encenderá cuando la consulta sea recibida por la entidad remota y otro LED se encenderá cuando la respuesta sea enviada de vuelta al Oráculo, permitiendo visualizar la comunicación entre ambos dispositivos. De esta manera, la "sabiduría" del Oráculo no proviene de una fuente mística, sino de un proceso tecnológico que transforma una señal sonora en un mensaje aparentemente significativo.
Las respuestas serán representadas mediante texto mostrado en una pantalla OLED y mediante audio reproducido por un parlante. La combinación de ambos busca mejorar la experiencia, permitiendo que los mensajes sean recibidos tanto de forma visual como auditiva.
Una vez entregada la respuesta, se reproducirá un segundo audio que dirá: "Alakasim, Alakasom, otra pregunta por favor", indicando que el Oráculo está listo para recibir una nueva consulta. Si transcurren 10 segundos sin que se detecte un nuevo aplauso, la pantalla volverá automáticamente al mensaje inicial de bienvenida.

### Pseudocódigo
```cpp
INICIO

Escribir "Di tu pregunta y aplaude, el Oráculo te responderá"

Mientras VERDADERO Hacer

Si AplausoDetectado = VERDADERO Entonces

Leer IntensidadSonido

Valor ← Convertir(IntensidadSonido)

Enviar(Valor)

Encender(LED1)

Respuesta ← ProcesarConsulta(Valor)

Encender(LED2)

Enviar(Respuesta)

EscribirOLED(Respuesta)

ReproducirAudio(Respuesta)

ReproducirAudio(
"Alakasim, Alakasom, otra pregunta por favor")

Tiempo ← 0

Mientras Tiempo < 10 Segundos Hacer

Si AplausoDetectado = VERDADERO Entonces
Salir del ciclo
FinSi

FinMientras

EscribirOLED(
"Di tu pregunta y aplaude, el Oráculo te responderá")

FinSi

FinMientras

FIN 

```
### Lista de materiales
| Componente                | Cantidad | Valor unitario | Link |
|--------------------------|----------|----------------|------|
| Arduino UNO R4 WiFi      | 1        | 38.990         |      |
| Raspberry Pi Pico 2W     | 1        | 14.990         |      |
| Sensor de sonido         | 1        |                |      |
| PAM8403                  | 1        |                |      |
| Parlante 8 ohms          | 1        |                |      |
| Pantalla OLED            | 1        |                |      |
| Paquete de LEDs          | 1        |                |      |
| Protoboard grande        | 1        |                |      |
| Protoboard chica         | 1        |                |      |
| Micro SD                 | 1        |                |      |
| DFPlayer Mini            | 1        |                |      |
| Cables Dupont (40 unid.) | 1        |                |      |

### Dibujo

![diagrama](./imagenes/diagrama.png)

En nuestro caso, trabajamos en todos estos puntos a partir de la definición del proyecto “El Oráculo”, desarrollando su lógica, materiales y flujo de funcionamiento. Logramos redactar el concepto general del sistema, donde el usuario realiza una pregunta en voz alta, activa el sistema mediante un aplauso y recibe una respuesta generada por una entidad remota, la cual es presentada tanto en pantalla OLED como en audio.

También elaboramos el pseudocódigo y el diagrama de flujo del sistema, describiendo paso a paso cómo se captura la señal del sensor de sonido, cómo se procesa la información y cómo se entrega la respuesta mediante los distintos outputs del sistema (LEDs, pantalla y parlante).

Además, intentamos avanzar en el código de prueba con simulación en consola; sin embargo, al no contar con todos los componentes físicos disponibles en ese momento, se nos hizo difícil probar y validar correctamente el comportamiento del sistema. Esto limitó el desarrollo del código, por lo que el avance se centró principalmente en la estructura lógica y la planificación del proyecto.
