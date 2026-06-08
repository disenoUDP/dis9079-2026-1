# sesion-13

lunes 08 junio 2026

## Seudocódigo del Proyecto

### Emisor (Arduino UNO R4 WiFi)

```text
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

### Receptor (Computador o Raspberry Pi Pico 2 W)

```text
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

### Flujo General

```text
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

```text
Capturar señales eléctricas de la planta

Convertir señales en datos digitales

Transmitir datos de forma inalámbrica

Recibir y procesar la información

Transformar los datos en imágenes, luces o sonidos

Mostrar en tiempo real la actividad detectada por la planta
```
