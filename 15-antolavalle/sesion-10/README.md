# sesion-10

lunes 18 mayo 2026

Solemne 2

En esta clase comenzamos a trabajar en la solemne 2, que consiste en desarrollar una comunicación inalámbrica entre microcontroladores usando Adafruit IO, integrando sensores y actuadores. La idea es que haya dos placas, una dentro de la sala y otra afuera en el patio, separadas por un vidrio, y que se comuniquen entre sí. Cada grupo puede decidir cuál envía y cuál recibe la información.

Un punto importante del encargo es no saturar el canal, por lo que el envío de datos tiene que ser lento y controlado mediante un botón, es decir, solo enviar información mientras el botón esté presionado. Lo mismo aplica para la recepción, que también debe activarse solo cuando se presione un botón.

En un inicio, nuestra idea era usar un botón junto con un potenciómetro para enviar datos, de manera que el botón habilitara el envío y el potenciómetro controlara el valor, permitiendo regular el brillo de un LED en la placa receptora. Durante la clase comenzamos probando el potenciómetro con la Raspberry Pi y el código, además de hacer pruebas con el botón en distintas placas. Sin embargo, tuvimos problemas con la conexión WiFi, ya que no logramos que las placas se conectaran correctamente, lo que nos impidió avanzar con Adafruit IO. Pensamos que podía ser por la inestabilidad de la red o por algún error en la configuración.

Después, cuando nos juntamos en la semana, decidimos simplificar la idea inicial y dejar de lado el uso del potenciómetro, manteniendo solo el botón como entrada. De esta forma, el sistema pasó a funcionar como un encendido y apagado del LED, en lugar de controlar su brillo. También decidimos trabajar con un feed personal, ya que con los feeds de Aarón no estaba funcionando correctamente.

Con este cambio logramos avanzar, aunque aparecieron otros problemas: el código del Arduino funcionaba bien en un computador, pero al usarlo en otro, aunque cargaba, no recibía los datos del feed. Para solucionarlo, dejamos el Arduino conectado al computador donde el código sí funcionaba, y usamos la Raspberry Pi Pico W desde otro equipo. Con esa configuración logramos que el sistema funcionara y que las placas se comunicaran.

<img width="1200" height="1600" alt="rasberri" src="https://github.com/user-attachments/assets/3db8ddcc-0a4b-4901-bb72-81facc86f5cf" />

<img width="1200" height="1600" alt="arduino" src="https://github.com/user-attachments/assets/5d27c35f-9220-4167-b9db-cf2f9d317a2f" />


En cuanto a los resultados, vimos que el LED externo no encendía como esperábamos, pero sí se activaba el LED TX de la placa cada vez que llegaba un mensaje, lo que confirmó que la comunicación sí estaba funcionando. Esto indica que el problema probablemente está en la conexión o configuración del LED externo más que en la comunicación.

Finalmente, probamos el sistema separando las placas aproximadamente 6 metros, y la comunicación siguió funcionando correctamente.
