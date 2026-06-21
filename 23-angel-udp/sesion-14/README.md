# sesion-14

lunes 15 junio 2026

Llegamos a clases y avanzamos observando los resultados que obteníamos al tomar fotos desde la Raspberry Pi, verificando si realizaba correctamente la función de colocar las fotos en Google Drive desde la ESP32-CAM. Algo de este estilo era lo que nos debía arrojar:

![ejemplo del filtro](./imagenes/prueba_con_filtro_7.jpg)

y si lo logró correctamente. El tema es que solo teníamos la API de Google Drive, que sería nuestra galería de fotos con la que podíamos visualizar estos resultados desde el computador, pero aún no teníamos vinculado nada al Arduino y menos la pantalla que nos mostraba parámetros o resultados. A pesar de todo, es un avance grande del proyecto porque la idea principal ya estaba funcionando, solo nos hacía falta ajustar detalles. Durante la misma clase, el grupo investigó formas de hacerlo funcionar (el Arduino) sin tener ningún resultado esperado, por lo que nos llevamos el proyecto a casa y fue donde decidimos hacer el cambio que comenté en persona persona-3 del grupo-5 en la carpeta 00-examen de este curso en GitHub, pero en resumen se podría describir de esta manera:

Desarrollamos un archivo retro, un sistema capaz de capturar, procesar y visualizar imágenes con estética retro utilizando múltiples microcontroladores conectados por WiFi.

Durante el proyecto optimizamos la comunicación, el almacenamiento y la interfaz gráfica, corrigiendo diversos errores técnicos hasta obtener una solución estable y funcional.

Para llegar a esto, optamos porque el Arduino sea el que saque las fotos y las mande a la “galería de imágenes”, donde ya quedan con el filtro, y desde la Raspberry Pi se pueda hacer la elección de ver la siguiente o retroceder por medio de botones, actualizándose cada vez que se toma una nueva foto.

Se pueden ver mejores descripciones, fotos, videos y detalles en la carpeta de nuestro grupo :)
