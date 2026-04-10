# persona-01 Cristobal Vergara Silva

investigaciones individuales

## sobre adafruit i/o
De primeras segui las indicaciones de como crearme una cuenta en adafruit y todo salio bien, luego me fui a arduino ide a ver como funcionaba, instale la biblioteca de adafruit para intentar con el ejemplo que subieron a github, lo copie y ahi me salio el primer error, "Compilation error: 'AdafruitIO_WiFi' does not name a type" y "Compilation error: exit status 1" que despues de buscar informacion, el error era que habia elminiado el void setup y void loop e igual me puso contento que por fin me resulto algo, cuando los agregue funciono. pero ahi vino una segunda complicacion, con el arduino conectado no me aparecia nada en port, para descartar primero revise si tenia instalada la ultima version del driver y luego cerre arduino ide para probar si no lo reconocia porque lo conecte con el programa ya abierto (no tenia nada que ver) despues intrusie todos los botones del programa, y revise de nuevo las cosas que tenia instaladas, despues de perder su buen tiempo intrusiando le decidi preguntar a chat gpt algo desconfiado porque no pense que me ayudaria, pero me dijo que podia deberse a que el cable que estaba usando era solo de carga y no para traspasar archivos, y es verdad que estaba ocupando el cable que uso para cargar mi celular entonces no descarto esa posibilidad, por ahora no tengo acceso a otro cable asi que esperare a mañana para conseguirme uno y asi puedo descartar esa opcion que me hace sentido que sea ese el problema (tengo tambien que investigar como poner fotos aca para adjuntar el problema de puerto). eso por ahora

Resulta que si era el cable, logramos correr el codigo y prender luces en el arduino pero tengo dificultades con la conexion con adafruit, estoy revisando bien las credenciales y vere un tutorial

Otro aprendizaje, revisamos bien el contenido y en arduino los valores que habia que cambiar por las credenciales nuestras, lo hicimos mal, y estbamos usando la contraseña personal mas no la que te da el sitio, la aio key.
Por otro lado intrusiando logramos conectar la raspberry pi a Adafruit

LOGRAMOS CONECTARLO!!!!!
encontramos un sitio de tutoriales en la pagina de adafruit, seguimos las indicaciones y aun no resultaba y aaron nos actualizo el arduino, que era el gran problema, luego de eso se conecto sin problema, probamos con el block "stream" en dashboard como decia en el ejemplo
https://learn.adafruit.com/assets/34840

## sobre artista, diseñadora o producto que usa electrónica o computación inalámbricas

## Minoru Fujimoto
Minoru Fujimoto es un artista, doctor en filosofia ,coreografo y doctor en computación vestible de la Universidad de Kobe. 
Tras trabajar en el departamento de informatica del diseño en la Universidad de Arte de Musashino, fundo MPLUSPLUS (make ++), firma que integra Led en los textiles a traves de un sistema de control inalambrico, segun ellos mismos trabajan con la "sincronización inalámbrica de dispositivos a gran escala y la integración audiovisual precisa hasta la robótica avanzada".

Los ubique por la reciente colaboracion en la que trabajaron con el diseñador japones Kunihiko Morinaga, fundador de la marca ANREALAGE, para crear la coleccion "2026-27 A/W “GHOST”" en la que de fondo tenia una gran pantalla reproduciendo escenas de the Ghost In The Shell, y al mismo tiempo iban pasando prendas programadas para estar coordinadas con la esenografia, para de este modo camuflarse en momentos especificos.
La programación de las prenda tenian ¨hilos blandos y textiles incrustados 10.000 LED_LCD" con la capacidad de ser plegados y cosidos, en las que el equipo tras meses desarrollando el sistema de programacion, logro que estos LEDs fueran controlables individualmente mediante control remoto, con la capacidad de presentar "imagenes animadas", lo cual llamaron: camuflaje optico termico inspirado en el efecto ficticio de mismo nombre que aparece en el anime Ghost In The Shell.

No es primera vez que Fujimoto (MPLUSPLUS) colabora con Morinaga y con la empresa LED Tokyo, que alquila pantallas LED de gran escala, tambien realizaron coleccion 2025-26 A/W “ SCREEN ” y una colaboracion con Beyonce, donde ocupo uno de sus vestidos en su gira Cowboy Carter Tour, en donde Fujimoto tambien desarrollo textiles LED capaces de mostrar imagenes controladas a distancia.
Si bien la tecnología LED portátil ya había sido abordada por algunas marcas de  moda experimental, MPLUSPLUS incorporó sus pantallas en diversos escenarios muy distintos, desde desfiles hasta festivales y conciertos (2022 Stray Kids, MAMA awards) generando toda una fantasia entre el dialogo del arte y la tecnologia.

![runway](./imagenes/Morinaga.jpg)

![runway](./imagenes/Fujimoto.png)

![runway](Beyonce.webp)

![runway](gifpasarela)
