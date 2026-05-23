# sesion-10

lunes 18 mayo 2026

En esta sesión llegamos con la idea de que teníamos solucionada la parte del código y conexiones de la solemne. Teniamos de idea hacer una maqueta de guillotina conectada al motor servo impulsado por el arduino y que fuera controlado con el potenciometro conectado a la raspi. Aarón nos sugirió no hscer esta idea y mejor controlar mas el movimiento del motor servo y que tuviera una intención más "poética" y quizá fuera mas sutil, lo teníamos moviéndose de 0 - 180 y lo cambiamos a 45 - 135 cambiando el código con ayuda de Claude AI

Despues nos enfrentamos a la sobrecarga de datos de Adafruit Io por lo que se nos sugirió controlarlo de alguna manera, hablamos con el grupo número 05 quienes estaban intentando controlarlo con un push button y Nicolás Valdés nos explico como funcionaba y nos ayudó (hay mas info de esta interacción en la carpeta grupal.)

Luego buscamos informacion sobre el botón y como integrarlo y pillamos:

<https://docs.sunfounder.com/projects/pico-2w-kit/en/latest/cproject/ar_button.html>

Intentamos conexiones con y sin resistor.

Mezclamos nuestro código los fragmentos del sitio y de cierto modo si funciono, solo que en vez de servir el botón para enviar y dejar de enviar datos a la nube, ahora solo se enviaban datos cuando movíamos el potenciómetr.

solemne 2
