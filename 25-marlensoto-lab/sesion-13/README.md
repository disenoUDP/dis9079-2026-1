# sesion-13

lunes 08 junio 2026

### Clase actual — Pseudocódigo y pruebas

#### ¿Qué es el pseudocódigo?
El pseudocódigo es una descripción estructurada del algoritmo escrita en lenguaje natural,
sin depender de la sintaxis de un lenguaje de programación específico.
Su objetivo es planificar la lógica antes de escribir código real.

#### Pseudocódigo del sistema
// CAPTURA
lectura_raw ← ADS1115.leer_canal(0)      // micro-voltaje de la planta
lectura_mv  ← convertir_a_milivoltios(lectura_raw)

// PROCESAMIENTO
variacion ← ABS(lectura_mv - valor_anterior)
SI variacion > umbral_actividad:
  nivel_actividad ← "ALTO"
SI NO:
  nivel_actividad ← "BAJO"

// EMPAQUETADO
paquete ← { "timestamp": hora_actual(), "valor": lectura_mv, "actividad": nivel_actividad }

// TRANSMISIÓN UDP/HTTP
ENVIAR paquete a ip_raspberry:puerto por WiFi

valor_anterior ← lectura_mv
ESPERAR intervalo_muestreo

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

PLANTA
   │
   ▼
ADS1115
   │
   ▼
Arduino UNO R4 WiFi
   │
   │ WiFi
   ▼
Raspberry Pi Pico 2 W / PC
   │
   ├──► Música generativa
   │
   └──► Visualización gráfica
### Siguiente clase — Programación definitiva

Con el pseudocódigo validado y las pruebas aprobadas, se procederá a:

- [ ] Escribir el código final en el Arduino UNO R4 WiFi
- [ ] Configurar el receptor en la Raspberry Pi Pico 2 W
- [ ] Conectar la visualización (música generativa + gráfico en pantalla)
- [ ] Prueba de integración completa con la planta conectada
