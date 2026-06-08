# sesion-10

lunes 18 mayo 2026

Preparación de la solemne 2

Durante la clase activamos la Raspi y probamos que funcionara el potenciometro y el código, también consultamos con compañeros la incorporación del boton en la protoboard 

<img width="1881" height="857" alt="image" src="https://github.com/user-attachments/assets/aee2cba7-6ad7-4c41-ae1f-868115fc0277" />

<img width="1200" height="1600" alt="image" src="https://github.com/user-attachments/assets/ee651c25-f787-41a5-926a-03d9914e7e00" />

-Probamos el botón con dos raspi distintas, wifi distintos y el problema es que no se conectan al wifi, por lo que creemos que intentando con wifi más estable y feeds propios si podría funcionar. 

<img width="1513" height="932" alt="image" src="https://github.com/user-attachments/assets/030b5563-7483-45d9-bf4f-3b8515cb8568" />

-finalmente solo queda esperar a ver si funciona con el wifi mas estable :(

## Pruebas de la solemne 2 


Decidimos realizar las prueba en un feed personal ya que en los feeds de Aarón no nos funcionó.

Durante las pruebas se presentaron algunos inconvenientes. El código del Arduino funcionaba correctamente en un computador, pero al intentar usarlo desde otro equipo, el programa cargaba pero no lograba recibir los mensajes del feed. Para resolver esto, se optó por mantener el Arduino conectado al computador donde el código había sido verificado, y la Raspberry Pi Pico W se operó desde el otro equipo. Con esta configuración el sistema comenzó a funcionar correctamente.

Respecto al LED, se observó que el LED externo no encendía, pero sí lo hacía el LED de transmisión (TX) de la placa al momento de recibir cada mensaje, lo que confirmó que la comunicación entre ambos dispositivos estaba operando con éxito.

Finalmente, el sistema fue probado con ambas placas separadas aproximadamente 6 metros entre sí, logrando una comunicación exitosa, lo que demostró que el envío de información funciona de forma inalámbrica sin necesidad de proximidad física entre los dispositivos.

Sensor usado para la solemne --> Botón, pulsador normal, 4 patas y dos nodos.

Actuador usado para la solemne --> un LED externo del la placa Arduino.



<img width="1600" height="1200" alt="image" src="https://github.com/user-attachments/assets/3a16bfe9-00be-4084-80d9-cf79f6aa3bf3" />

