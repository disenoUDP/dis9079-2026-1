# sesion-13

lunes 08 junio 2026

### Clase — Pseudocódigo y pruebas

#### ¿Qué es el pseudocódigo?
El pseudocódigo es una descripción estructurada del algoritmo escrita en lenguaje natural,
sin depender de la sintaxis de un lenguaje de programación específico.
Su objetivo es planificar la lógica antes de escribir código real.

#### Seudocódigo del Proyecto
Emisor (Arduino UNO R4 WiFi)
INICIO

    INICIO 
    
    Inicializar ADS1115

    Conectar a la red WiFi

    MIENTRAS el sistema esté activo

    Leer señal eléctrica de la planta

    Convertir lectura analógica a valor digital

    Enviar dato mediante WiFi

    Esperar un breve intervalo
  

Receptor (Computador o Raspberry Pi Pico 2 W)
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

Flujo General

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

Lógica del Proyecto

    Capturar señales eléctricas de la planta

    Convertir señales en datos digitales

    Transmitir datos de forma inalámbrica

    Recibir y procesar la información

    Transformar los datos en imágenes, luces o sonidos

    Mostrar en tiempo real la actividad detectada por la planta
    
---

### Códigos de prueba (verificación por etapas)

Antes de integrar todo el sistema, se verificará cada subsistema por separado:

| Prueba | Qué verifica | Herramienta |
|--------|-------------|-------------|
| `test_ads1115.ino` | Lectura del sensor y valores por Serial Monitor | Arduino IDE |
| `test_wifi.ino` | Conexión a red WiFi de la facultad | Arduino IDE |
| `test_envio_udp.ino` | Transmisión de paquete y recepción en Raspberry | Python socket |
| `test_recepcion_pico.py` | Recepción y parseo en Pico 2 W | Thonny / MicroPython |

---
   
### Siguiente clase — Programación definitiva

Con el pseudocódigo validado y las pruebas aprobadas, se procederá a:

- [ ] Escribir el código final en el Arduino UNO R4 WiFi
- [ ] Configurar el receptor en la Raspberry Pi Pico 2 W
- [ ] Conectar la visualización (música generativa + gráfico en pantalla)
- [ ] Prueba de integración completa con la planta conectada
