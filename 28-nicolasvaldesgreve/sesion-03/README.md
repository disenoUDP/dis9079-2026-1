# sesion-03

# Apuntes 23/03

### ¿Cuál es la diferencia entre microcontrolador y computador?

microcontrolador: cosas cumas y lentas.
computadores: cosas finas y rápidas.

---

## Visual Studio Code

Se instaló Visual Studio Code, en donde se intstalaron la extensión Raspberry Pi Pico (la versión verificada por raspberry). Dentro de la extensión, se encuentra micropython, el cual está nombrado en honor a monty python y es un lenguaje agnóstico para computadores, pero en éste curso usaremos el leguaje C++.

Al meterse en donde dice new C/C++ Project, hay que escribir el nombre del archivo, seleccionar en Board type Pico 2 w, en la selección de la versión hay que tener en cuenta que en éste curso usaremos la última versión, la cual en éste momento es v2.2.0, pero esto puede cambiar mediante transcurra el tiempo durante el semestre. En la sección de Studio seleccionamos la opción de Console over USB, y en donde dice Pico wireless options seleccionamos Pico W onboard LED.

- Spi se utiliza para conectar un microcontrolador a una pantalla
- I2c utiliza menos cables (y es más caro)
- Stdio (standart input output)
- SDK es un kit de desarrollo de software

En el archivo .cpp es en donde tenemos que trabajar, apretando el botón de "run".

Raspberry pino tiene un setup(), sino que tiene un main(), y todo lo que está dentro de main() sucede en el orden que esté dictado.

Cuando dice return-1, significa que perdí, me rendí. Para que el código pare, no es delay como en arduino, sino que es sleep_ms

---

### Encargo: ver el primer capitulo de Monty Python

La verdad antes no tenía idea de que existía Monty Python's Flying Circus, pero ahora que vi el primer capítulo puedo decir que es muy entretenido, ya que en lo personal me gustan bastante los chistes sin sentido o que no se sabe qué es lo que viene o qué es lo que está sucediendo realmente (creo que me gustan las situaciones ridículas), y de todo el capítulo puedo decir que mis escenas favoritas eran en donde hacían los chistes de los cerditos ya que en ninguno supe predecir que eso iba a suceder hasta que mostraban la pizarra tachando un cerdito más.
