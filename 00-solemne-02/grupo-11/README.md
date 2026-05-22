# solemne-02

## Integrantes

- Martina Alegria / AlegriaColoma
- Antonella Lavalle / antolavalle
- Catalina Salinas / catasal

## Descripción textual del proyecto

* El proyecto consiste en desarrollar un sistema de comunicación entre una Raspberry Pi y un Arduino utilizando la plataforma Adafruit IO como intermediaria para el envío y recepción de datos en tiempo real. Para esto, se utilizará un potenciómetro conectado a la Raspberry Pi, el cual permitirá obtener valores analógicos según la posición del control giratorio.

* La Raspberry Pi leerá continuamente los datos entregados por el potenciómetro y los enviará a Adafruit IO mediante conexión a internet y el protocolo MQTT o HTTP. Estos datos quedarán almacenados y disponibles en la nube, permitiendo la comunicación entre distintos dispositivos conectados.

* Posteriormente, el Arduino se conectará a Adafruit IO para recibir los valores enviados desde la Raspberry Pi. Dependiendo del valor entregado por el potenciómetro, el Arduino podrá ejecutar distintas acciones, como controlar la intensidad de un LED, mover un servomotor o activar otros componentes electrónicos.

Un botón pulsador normal tiene 4 patas pero solo 2 circuitos internos: las patas A-B están siempre conectadas entre sí, y las patas C-D están siempre conectadas entre sí. Cuando apretás el botón, A-B se conecta con C-D. Por eso solo usás una pata de cada lado.
No necesitás resistencia externa porque el código usa Pin.PULL_UP, que activa una resistencia interna del Pico que mantiene GP15 en nivel alto (HIGH) cuando el botón no está presionado. Al presionar, GP15 cae a nivel bajo (LOW) y el Pico detecta ese cambio.

<img width="487" height="460" alt="boton" src="https://github.com/user-attachments/assets/27a12dc5-1013-4e0c-a581-41366887edde" />

<img width="504" height="579" alt="pico2w" src="https://github.com/user-attachments/assets/7bf40e4d-8da1-4b7d-9845-838e607ed848" />

<img width="880" height="463" alt="inalambrico" src="https://github.com/user-attachments/assets/881f277e-f0f4-46e5-ac69-5ec51a5124f7" />

durante la clase se probo con enviar datos al adafruit
<img width="1882" height="861" alt="io adafruit" src="https://github.com/user-attachments/assets/a86efa48-aaeb-46b4-947a-0579609b8873" />


## Materiales usados
* Raspberry Pi pico 2
* Arduino R4
* el LEDBotón pulsador (push button 4 patas)
* LED (cualquier color)
* Resistencia 220Ω1Protege el LED de sobrecorriente
* Protoboard (placa de pruebas)
* Cables puente macho-macho
* Cable micro-USB1
* Cable USB-C

## Sensor usado

- Potenciometro
 
## Actuador usado

- LEDS
  
## Código usado para enviar

## Código usado para recibir

## Imágenes del proyecto
<img width="900" height="1600" alt="WhatsApp Image 2026-05-21 at 19 02 01" src="https://github.com/user-attachments/assets/fc3011c3-77e6-49eb-8ea7-3f1cd5e51e51" />

<img width="807" height="642" alt="luz led" src="https://github.com/user-attachments/assets/79fb90f6-19b8-4cad-97b7-6ded2a79117a" />

## Animaciones del proyecto

https://github.com/user-attachments/assets/a0d115bc-8573-45b9-bbcb-b2d1fac5d7e9 

https://github.com/user-attachments/assets/ff885a3a-38ae-4f76-9ec6-ffaf2f524898

## Bibliografía
chat gpt
claude
profesor aron 
mateo 
compañeros 
