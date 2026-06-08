# solemne-02

## Integrantes

- Antonella Lavalle / antolavalle
- Martina Alegria / AlegriaColoma
- Catalina Salinas / catasal

## Descripción textual del proyecto

* Para lograr la comunicación entre ambas placas, se utilizó la plataforma Adafruit IO como intermediario en la nube, empleando el protocolo de mensajería MQTT. Este protocolo permite enviar y recibir mensajes pequeños a través de internet de forma eficiente.

### Lado de la Raspberry Pi Pico W

La Raspberry Pi Pico W se conecta a una red WiFi y luego establece conexión con Adafruit IO mediante MQTT. Un botón físico está conectado al pin GP0 de la placa. Cuando se presiona el botón, el programa detecta el cambio de estado y publica un mensaje en el feed correspondiente. Para evitar lecturas falsas por rebote mecánico del botón, se agregó una pequeña pausa de 250 milisegundos tras cada pulsación.

### Lado del Arduino Uno R4 WiFi

El Arduino se conecta a la misma red WiFi y al mismo feed de Adafruit IO. Cada vez que llega un mensaje al feed, se ejecuta automáticamente una función que lee el contenido del mensaje. Si el mensaje dice "ON", enciende un LED; si dice "OFF", lo apaga.
  
## Materiales usados
* Raspberry Pi pico 2
* Arduino R4
* Botón pulsador (push button 4 patas)
* LED (cualquier color)
* Resistencia 220Ω1Protege el LED de sobrecorriente
* Protoboard (placa de pruebas)
* Cables puente macho-macho
* Cable micro-USB1
* Cable USB-C

## Prueba de códigos

### Problemas encontrados durante el desarrollo

Durante las pruebas se presentaron algunos inconvenientes. El código del Arduino funcionaba correctamente en un computador, pero al intentar usarlo desde otro equipo, el programa cargaba pero no lograba recibir los mensajes del feed. Para resolver esto, se optó por mantener el Arduino conectado al computador donde el código había sido verificado, y la Raspberry Pi Pico W se operó desde el otro equipo. Con esta configuración el sistema comenzó a funcionar correctamente.

Respecto al LED, se observó que el LED externo no encendía, pero sí lo hacía el LED de transmisión (TX) de la placa al momento de recibir cada mensaje, lo que confirmó que la comunicación entre ambos dispositivos estaba operando con éxito.

### Prueba a distancia

Finalmente, el sistema fue probado con ambas placas separadas aproximadamente 6 metros entre sí, logrando una comunicación exitosa, lo que demostró que el envío de información funciona de forma inalámbrica sin necesidad de proximidad física entre los dispositivos.

<img width="1600" height="1200" alt="Placas y cables 22-05" src="https://github.com/user-attachments/assets/7f1432c7-e8b8-49f1-b60d-52b68aa59e93" />

## Sensor usado

Botón 

 Un botón pulsador normal tiene 4 patas pero solo 2 circuitos internos: las patas A-B están siempre conectadas entre sí, y las patas C-D están siempre conectadas entre sí. Cuando apretás el botón, A-B se conecta con C-D. Por eso solo usás una pata de cada lado.
No necesitás resistencia externa porque el código usa Pin.PULL_UP, que activa una resistencia interna del Pico que mantiene GP15 en nivel alto (HIGH) cuando el botón no está presionado. Al presionar, GP15 cae a nivel bajo (LOW) y el Pico detecta ese cambio.

<img width="487" height="460" alt="boton" src="https://github.com/user-attachments/assets/27a12dc5-1013-4e0c-a581-41366887edde" />

<img width="504" height="579" alt="pico2w" src="https://github.com/user-attachments/assets/7bf40e4d-8da1-4b7d-9845-838e607ed848" />

<img width="880" height="463" alt="inalambrico" src="https://github.com/user-attachments/assets/881f277e-f0f4-46e5-ac69-5ec51a5124f7" />

durante la clase se probo con enviar datos al adafruit
<img width="1882" height="861" alt="io adafruit" src="https://github.com/user-attachments/assets/a86efa48-aaeb-46b4-947a-0579609b8873" />

### Proceso durante clase corrección solemne 2 

Corregimos el código, era necesario que en el Código para la Raspi colocar que el mensaje era "ON" para encender el LED interno de la placa Arduino UNO R4, pero aún no podemos apagarlo luego de encenderlo ni prender ni apagar el LED externo.

Posteriormente logramos arreglar el código incluyendo un apartado para que al soltar el botón el LED interno se apague, el LED se enciende al mantener presionado el botón, botón que manteniendo presionado envia un mensaje de "ON" y al soltarlo envia un "OFF" y se apaga el LED.

Lo que estamos intentando ahora es conectar bien el LED externo para que pueda ser el que encienda

<img width="1200" height="1600" alt="WhatsApp Image 2026-05-25 at 15 31 44" src="https://github.com/user-attachments/assets/607c14ae-8d8f-4a99-8ab7-68b6f9890448" />

Finalmente realizamos bien la conexión con los cables, resistencia y el LED, permitiendo que enciendan ambos LED (interno y externo) 

<img width="1600" height="1476" alt="image" src="https://github.com/user-attachments/assets/42d365d1-3a67-4329-973e-a7891c66445c" />

<img width="1600" height="1498" alt="image" src="https://github.com/user-attachments/assets/7920e1b3-c975-4a4b-8f06-15422dbcdc9a" />

## Resultado bueno funcional 

https://github.com/user-attachments/assets/c9e92d02-9f83-4edf-9f51-975c2e9b597a


https://github.com/user-attachments/assets/f96f3a10-2545-4a07-9acf-d99c48e91bf3



## Actuador usado

- LEDS
  
## Código usado para enviar

Respecto al código utilizado para enviar, tuvimos que realizarle cambios para añadirle que al soltar el botón se enviara un mensaje de "OFF" y que respecto a ese mensaje pudieramos apagar el LED, tanto interno como externo. 

## Código usado para recibir

El código utilizado estaba correcto, aunque durante un momento intentamos que los mensajes fueran "1" y "0"

## Imágenes del proyecto
<img width="900" height="1600" alt="WhatsApp Image 2026-05-21 at 19 02 01" src="https://github.com/user-attachments/assets/fc3011c3-77e6-49eb-8ea7-3f1cd5e51e51" />

<img width="807" height="642" alt="luz led" src="https://github.com/user-attachments/assets/79fb90f6-19b8-4cad-97b7-6ded2a79117a" />

## Animaciones del proyecto

al principo probamos sin colocar un cable puente en la entrada 13
https://github.com/user-attachments/assets/a0d115bc-8573-45b9-bbcb-b2d1fac5d7e9 

https://github.com/user-attachments/assets/ff885a3a-38ae-4f76-9ec6-ffaf2f524898

## Registro del proyecto 

https://youtube.com/shorts/Kj6q2cJO3Xo?si=JP_w2Klc17pr-onz

## Bibliografía
chat gpt

claude 

Mateo 

compañeros
