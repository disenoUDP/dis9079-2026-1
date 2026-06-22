# sesion-13

lunes 08 junio 2026

### La planta como nodo biológico - Avance

Durante la clase seguimos conversando sobre el enfoque del proyecto y llegamos a la conclusión de que no queríamos hacer solamente una traducción de señales de la planta a sonidos. La idea empezó a tomar otra forma y pensamos en usar la planta como una especie de sensor ambiental que pudiera detectar actividad dentro de la facultad sin necesidad de utilizar cámaras.

Lo que nos llamó la atención es que las plantas reaccionan a distintos estímulos de su entorno y generan pequeñas variaciones eléctricas. Por eso comenzamos a pensar en la planta como una especie de intermediaria entre el espacio y las personas que lo habitan. Más que medir algo específico, nos interesa capturar esos cambios y transformarlos en una experiencia visual y sonora.

## Decisiones sobre el hardware

También discutimos qué plataforma utilizar. En un principio apareció la posibilidad de trabajar solamente con Raspberry, pero después de revisar las características de cada dispositivo decidimos usar una combinación de componentes.

| Componente                         | Función                                          |
| ---------------------------------- | ------------------------------------------------ |
| Planta + ADS1115                   | Capturar las variaciones eléctricas de la planta |
| Arduino UNO R4 WiFi                | Leer los datos y enviarlos por WiFi              |
| Raspberry Pi Pico 2 W o computador | Recibir los datos y generar la visualización     |

La razón principal para incorporar el ADS1115 fue que necesitábamos una lectura más precisa de las señales. Además, el Arduino UNO R4 ya tiene conectividad WiFi integrada, lo que simplifica bastante la transmisión de datos.

Otro acuerdo fue instalar electrodos tanto en las hojas como en el sustrato para probar distintas zonas de medición y comparar los resultados.

## Flujo general del sistema

La idea general del funcionamiento quedó definida de esta manera:

```text
Planta
 ↓
Electrodos
 ↓
ADS1115
 ↓
Arduino UNO R4 WiFi
 ↓
WiFi
 ↓
Computador / Raspberry Pi Pico 2 W
 ↓
Procesamiento
 ↓
Visualización y sonido
```

## Funcionamiento esperado

Pensamos el sistema en dos partes: un emisor y un receptor.

### Emisor

El Arduino será el encargado de leer constantemente las señales provenientes de la planta y enviarlas por WiFi.

```text
INICIO

Conectar sensores
Conectar WiFi

Mientras el sistema esté funcionando:

- Leer señal de la planta
- Convertir la lectura a datos digitales
- Enviar información
- Esperar un instante

FIN
```

### Receptor

El computador o la Raspberry recibirán esos datos y los transformarán en imágenes y sonido.

```text
INICIO

Conectarse a la red
Esperar datos

Mientras el sistema esté funcionando:

- Recibir información
- Analizar intensidad de la señal
- Actualizar visualización
- Actualizar sonido

FIN
```

## Ideas para la visualización

Todavía no definimos el diseño final, pero conversamos algunas posibilidades.

| Estado      | Comportamiento visual                        | Sonido                       |
| ----------- | -------------------------------------------- | ---------------------------- |
| Señal alta  | Más movimiento y mayor cantidad de elementos | Sonidos más intensos         |
| Señal media | Comportamiento estable                       | Sin grandes cambios          |
| Señal baja  | Movimiento más lento y menos elementos       | Sonidos suaves y ambientales |

La intención es evitar una visualización que parezca solamente un gráfico científico. Queremos que se vea más orgánica y que transmita la sensación de que la planta está reaccionando a lo que ocurre a su alrededor.

## Organización del grupo

Como esta semana era difícil juntarnos presencialmente, repartimos las tareas para poder avanzar en paralelo.

| Persona   | Tarea                                                       |
| --------- | ----------------------------------------------------------- |
| Luisa     | Comprar el ADS1115 para comenzar las pruebas                |
| Compañera | Conseguir una planta de hojas grandes para los experimentos |

Además, dividimos el trabajo en dos áreas.

### Grupo de hardware y transmisión

* Revisar la librería ADS1115.
* Probar lecturas desde Arduino UNO R4.
* Verificar la conexión WiFi.

### Grupo de visualización

* Investigar herramientas para mostrar los datos en tiempo real.
* Explorar opciones como p5.js, D3.js y Canvas.
* Pensar formas de representar visualmente la actividad de la planta.

### Flujo General del Sistema

```
Planta
  ↓
Electrodos
  ↓
ADS1115
  ↓
Arduino UNO R4 WiFi
  ↓
Transmisión WiFi
  ↓
Computador / Raspberry Pi Pico 2 W
  ↓
Procesamiento de datos
  ↓
Visualización y sonido
```

### Lógica del Proyecto

```
1. Capturar señales eléctricas de la planta
2. Convertir señales en datos digitales
3. Transmitir datos de forma inalámbrica
4. Recibir y procesar la información
5. Transformar los datos en imágenes, luces o sonidos
6. Mostrar en tiempo real la actividad detectada por la planta
```

---

### A. Emisor *(Arduino UNO R4 WiFi)*

```
INICIO

  Inicializar ADS1115
  Conectar a la red WiFi

  MIENTRAS el sistema esté activo

    Leer señal eléctrica de la planta
    Convertir lectura analógica a valor digital
    Enviar dato mediante WiFi
    Esperar un breve intervalo

  FIN MIENTRAS

FIN
```

### B. Receptor *(Computador o Raspberry Pi Pico 2 W)*

```
INICIO

  Conectarse a la red WiFi
  Inicializar sistema de visualización

  MIENTRAS el sistema esté activo

    Recibir dato enviado por Arduino
    Analizar intensidad del valor recibido

    SI valor alto ENTONCES
      Aumentar movimiento visual
      Aumentar cantidad de elementos gráficos
      Aumentar intensidad sonora

    SI valor medio ENTONCES
      Mantener comportamiento normal

    SI valor bajo ENTONCES
      Disminuir movimiento visual
      Disminuir cantidad de elementos gráficos
      Disminuir intensidad sonora

    Actualizar visualización

  FIN MIENTRAS

FIN
```

## Reflexión

Lo que más discutimos hoy fue cómo representar los datos. Técnicamente podríamos mostrar números o gráficos, pero sentimos que eso no comunica realmente la idea del proyecto.

Por ahora la pregunta que nos está guiando es cómo hacer que esos datos se perciban como algo vivo y no solamente como información técnica. Creo que ese será uno de los desafíos más importantes de las próximas semanas.

## Tareas pendientes

* [ ] Comprar ADS1115.
* [ ] Conseguir una planta de hojas grandes.
* [ ] Revisar librerías para Arduino UNO R4.
* [ ] Realizar pruebas básicas de conexión WiFi.
* [ ] Investigar herramientas de visualización en tiempo real.
* [ ] Definir cómo se comunicarán emisor y receptor.


