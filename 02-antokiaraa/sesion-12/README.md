# sesion-12

lunes 01 junio 2026

## clase y planificación examen

API: Application Programming Interface

es un "puente" que permite que dos sistemas se comuniquen e intercambien datos inalámbricamente (a través de internet) es básicamente otra interfaz que cumple la misma función que ya usamos con Adafruit IO: cuando conectamos nuestra placa a la nube para subir datos!

está la opción de no necesariamente usar sensores físicos y solo conectarse a la nube.

ejemplo de un proyecto que se conecta a una nube “Api” y indica los vuelos cercanos según la ubicación.

- Weather APIs:
tiene datos actuales y previstos para el futuro, calidad del aire, etc.

en wikipedia en basic information sale la info de la web, con una llave de la api de la wikipedia se puede usar toda la información para un proyecto.

### primer acercamiento a idea de examen

Nuestra idea de proyecto consiste en utilizar una API con datos de la actividad sismológica global en tiempo real para transformarla en una experiencia visual, logrando mostrar físicamente los últimos temblores del mundo brevemente después de ocurrir.

Queremos que al presionar un botón para activar el envío de datos el dispositivo reaccione vibrando con una fuerza proporcional al sismo real, mientras una pantalla muestra el lugar exacto y los grados del evento.

### preguntas que nos realizaron

1. Saben qué motor vibrador ocuparán?
2. Los datos de los sismos, son en tiempo real, o sea es cuando esta pasando un sismo en ese momento?
3. Si no esta ocurriendo un sismo no se mueve? o guarda los datos de los sismos

### respuestas

1. No tenemos pensado uno en específico, pero hemos usado en otro proyecto motores de joystick y podrían funcionar.
2. Pusimos que se mostrarían brevemente después de ocurrir o el último registrado al momento de presionar el botón para enviar el dato.
3. Si no se registran sismos, se mostraría en la pantalla que no ocurrió ninguno en el último tiempo (rango por definir).

### comentarios

igual tuvimos poco tiempo para pensar qué queriamos realmente, esa fue solo una idea del momento pero no estamos seguro si será definitivo, queremos investigar y ver otras opciones más interesantes!



