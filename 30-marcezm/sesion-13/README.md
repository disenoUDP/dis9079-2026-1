# sesion-13

Lunes 08 de junio de 2026

## Desarrollo de la lógica del sistema

Durante esta sesión se definió la estructura lógica que tendrá el proyecto antes de comenzar la programación definitiva. Para ello se utilizó pseudocódigo, una herramienta que permite representar el funcionamiento general del sistema sin depender de un lenguaje de programación específico.

El objetivo fue identificar claramente cómo se moverán los datos desde la planta hasta la visualización final, estableciendo las tareas del emisor y del receptor dentro del sistema.

## Pseudocódigo

### Emisor (Arduino UNO R4 WiFi)

INICIO

```
Inicializar ADS1115

Conectar a la red WiFi

MIENTRAS el sistema esté activo

    Leer señal eléctrica de la planta

    Convertir lectura analógica a valor digital

    Enviar dato mediante WiFi

    Esperar un breve intervalo
```

FIN

### Receptor (Computador o Raspberry Pi Pico 2 W)

INICIO

```
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
```

FIN

## Comprensión del flujo de datos

El sistema funciona a partir de señales bioeléctricas captadas desde la planta mediante electrodos. Estas señales son amplificadas y leídas por el ADS1115, para posteriormente ser enviadas por el Arduino a través de la red WiFi.

Una vez recibidos los datos, el receptor interpreta los valores obtenidos y los transforma en cambios visuales y sonoros. De esta manera, la actividad eléctrica de la planta puede percibirse mediante elementos gráficos en movimiento y variaciones de sonido.

### Recorrido de la información

Planta → Electrodos → ADS1115 → Arduino UNO R4 WiFi → WiFi → Receptor → Procesamiento → Visualización

---

## Estrategia de pruebas

Antes de unir todos los componentes, se acordó probar cada parte del sistema de manera independiente. Esto permitirá detectar errores específicos y simplificar el proceso de depuración.

| Archivo de prueba        | Función                                                |
| ------------------------ | ------------------------------------------------------ |
| `test_ads1115.ino`       | Comprobar la lectura correcta de datos desde el sensor |
| `test_wifi.ino`          | Verificar la conexión inalámbrica                      |
| `test_envio_udp.ino`     | Revisar el envío de paquetes de datos                  |
| `test_recepcion_pico.py` | Confirmar la recepción y procesamiento de información  |

---

## Próximos pasos

Para la siguiente sesión se espera comenzar la implementación definitiva del sistema, conectando las distintas etapas desarrolladas hasta ahora. También se iniciarán las pruebas entre la lectura de la planta y la respuesta visual generada en tiempo real.

* [ ] Programación final del Arduino.
* [ ] Configuración del receptor.
* [ ] Integración de visualización y sonido.
* [ ] Prueba completa del sistema conectado.
* [ ] Registro de resultados y ajustes.
