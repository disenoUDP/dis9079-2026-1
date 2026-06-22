# sesion-14

lunes 15 junio 2026

# Apuntes clase 15/06

Hoy es la última clase antes del examen, lo cual me da un poco de pena ya que este es uno de los cursos que más he querido dentro de la carrera junto con el taller que estoy cursando actualmente, pero la vida sigue y hay que aprender el arte de soltar las cosas LOL.

Como esta clase es solo avance, nos dedicamos a tratar de resolver el problema que nos ha estado causando el humidificador USB ya que no lo estamos logrando manejar mediante el Arduino UNO R4 WiFi, así que decidimos preguntarle a Cami Parada (que el año pasado trabajó con este mismo componente) qué deberíamos hacer ya que no estábamos entendiendo mucho y hay poca documentación de cómo utilizar este componente de la manera en que queremos hacerlo. Cami nos explicó que ellos cuando utilizaron el humidificador, sacaron el botón que se encuentra en la placa e hicieron un puente en los dos puntos de soldadura traseros (de donde se encontraba el botón), para así lograr manejar el componente, pero no de manera directa, sino que manejaban el cuándo se le daba alimentación (lo cual lo activa de inmediato) y cuando se la cortaban (lo cual lo apaga). 

Ya con la información que nos dio Cami, fuimos al LID a soldar ambos puntos para probar controlarlo, pero nos dimos cuenta de que al conectarlo ya no prendía la luz LED que trae la placa para indicar que el componente está activo, lo cual nos preocupó ya que pensamos que se había rendido a la vida por nuestra culpa. Para probar si estaba vivo o no, probamos con un multímetro y al hacer contacto se prendía el LED de manera muy sutil y tiritona lo cual nos dejó aún más confundidos, pero por lo menos eso daba señales de que estaba vivo!! así que seguimos luchando hasta que era muy tarde y no logramos solucionar lo del humidificador. De hecho, en un punto probamos un código que era para ver si este seguía funcionando o no y al momento de correr el código la membrana empezaba a vibrar, pero no lograba generar la bruma cuando hacia contacto con el agua.

> Spoiler: Al final el problema era la membrana. Compramos más KITs de humidificar porque pensamos que el que teníamos ya no funcionaba, pero en realidad el problema era solo la membrana que probablemente murió cuando la mandamos a re-soldar en una tienda de electrónica que no recuerdo su nombre (eran muy simpáticos si!!).
