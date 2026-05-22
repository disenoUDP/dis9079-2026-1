# investigaciones individuales — Sensor y Actuador
Luisa Toro Github: Luisaatoro9

### El Sensor: Pulsador (Botón)

### 1. ¿Qué aprendí sobre este sensor?

Parece el componente más simple del mundo, un botón pero cuando empecé a investigarlo me di cuenta de que tiene más ciencia de lo que parece.

En electrónica digital, un pulsador es un **sensor de contacto**: detecta si alguien lo presionó o no, y manda esa info como un `1` o un `0`. El problema real no es el botón en sí, sino lo que pasa con el pin cuando el botón *no está presionado*. Si lo conectas sin una resistencia de referencia, el pin queda en un **estado flotante**, básicamente el microcontrolador no sabe si está recibiendo un 0 o un 1 porque el ruido eléctrico del ambiente lo interfiere y genera activaciones falsas al azar.

<img width="499" height="350" alt="image" src="https://github.com/user-attachments/assets/d8f0b37c-8489-442f-a4b6-833e03b3bc25" /> 
<img width="499" height="350" alt="image" src="https://github.com/user-attachments/assets/85869c97-6bf5-476a-bffb-8213455ea5f2" />

La solución es usar resistencias **Pull-up o Pull-down** (que pueden ser internas del mismo Arduino o Raspberry, o externas en el circuito). Lo que hacen es "forzar" un estado lógico estable cuando el botón no se está usando, le dicen al pin "si no hay nada, eres un 0" (o un 1, dependiendo de la configuración). Eso elimina el ruido y el sistema se comporta como debería.

<img width="499" height="350" alt="image" src="https://github.com/user-attachments/assets/46823a8b-e0cb-4f4a-8843-ce8c0452bd15" />
<img width="499" height="350" alt="image" src="https://github.com/user-attachments/assets/f1fd9b50-6ba3-42b0-a2e2-f985ebde1b99" />

En nuestro proyecto usamos el botón como sensor porque necesitábamos que el *usuario* decidiera cuándo mandar la señal, no un temporizador automático.


---

### 2. Filtrado de información y visualización de datos

El gran problema de los sensores mecánicos como los botones es el **rebote** (o *debouncing* en inglés). Cuando presionas el botón, las chapitas metálicas internas chocan, vibran y generan varios pulsos de "encendido" en milisegundos antes de estabilizarse. Para el microcontrolador eso se parece a que presionaste el botón 10 veces seguidas cuando en realidad solo lo apretaste una vez.

<img width="1000" height="450" alt="image" src="https://github.com/user-attachments/assets/95d11ca8-9189-47f0-aef1-ca8a89139bb6" />

### ¿Por qué el botón genera varios pulsos si solo lo apreté una vez?

<img width="330" height="350" alt="image" src="https://github.com/user-attachments/assets/f9d3c70d-b676-4218-9fce-84c0a7432750" />
<img width="330" height="350" alt="image" src="https://github.com/user-attachments/assets/461b97da-f4aa-475b-8d9e-9405b5c2b080" />
<img width="330" height="350" alt="image" src="https://github.com/user-attachments/assets/f7b777d4-fb45-4885-8b8d-e74332f711ec" />


Cuando aprietas un botón, adentro hay dos pequeñas chapitas de metal que se juntan para cerrar el circuito. En tu cabeza eso pasa suave y limpio, se tocan y listo. Pero en la realidad física, esas chapitas rebotan igual que cuando dejas caer una pelota al piso: no se quedan quietas de inmediato, sino que chocan, se separan, vuelven a chocar, se separan, y recién después de unos milisegundos se estabilizan y quedan juntas de verdad.

Para nosotros eso es invisible porque pasa en menos de 20 milisegundos. Pero el microcontrolador lee el estado del pin miles de veces por segundo, entonces alcanza a ver cada uno de esos rebotes como si fueran presiones distintas. Aunque aprete una vez, él vio cinco.

Es exactamente lo que muestra el diagrama arriba: esa línea roja llena de subidas y bajadas rápidas no es que el botón estuviera loco, es que estaba rebotando físicamente y el Arduino registró cada rebote como un 1.

El delay en el código existe justo para eso: cuando detecta el primer 1, espera unos milisegundos con los ojos cerrados hasta que las chapitas terminen de rebotar y se estabilicen. Después de esa espera, recién ahí registra la presión como válida, y ya no le importa lo que pasó durante el rebote.

**Cómo se filtra:** La solución más directa es por código, después de detectar la primera señal, se pone un pequeño `delay` para ignorar todo lo que pase en los siguientes milisegundos. Así el sistema solo registra una presión real y descarta el ruido mecánico.

**Cómo se visualiza:** En Adafruit IO los datos del botón aparecen como valores binarios: `0` (no presionado) o `1` (presionado). Sin el filtrado, el gráfico en la plataforma se llena de picos aleatorios que parecen muchas presiones cuando era solo una. Con el debouncing bien hecho, cada presión es un pico limpio y claro.

<img width="1000" height="450" alt="image" src="https://github.com/user-attachments/assets/1870820b-b2b9-443c-973a-e2d1a8eb08b1" />

---

### 3. Problemas comunes

**Saturación del servidor:** Si el código manda el estado del botón en *cada ciclo del loop* (aunque no haya cambiado), Adafruit IO se llena de datos repetidos y puede bloquear la cuenta. Lo correcto es mandar información **solo cuando el estado cambia** de 0 a 1 o de 1 a 0. Enviar por evento, no por tiempo.

**Conexiones cruzadas en la protoboard:** Es muy fácil conectar el botón en diagonal en la protoboard y crear un cortocircuito sin darse cuenta. Los pulsadores tienen 4 patas pero internamente están conectadas en pares, si no se entiende eso, el botón queda siempre cerrado o siempre abierto. Revisar la continuidad con multímetro *antes* de alimentar la placa es clave.

**Estado flotante sin resistencia:** Ya lo expliqué arriba, pero vale repetirlo porque es el error más frecuente, conectar el botón sin Pull-up o Pull-down y después no entender por qué el sistema hace cosas solo.

<img width="1000" height="450" alt="image" src="https://github.com/user-attachments/assets/54d2b361-1a42-4a99-8a84-c2ade269f79e" />

---

### 4. Referente: Amazon Dash Buttons

Aunque ya no se usan, para mí los Amazon Dash Buttons son el ejemplo más real de lo que estamos haciendo en este ramo. Eran botones físicos que pegabas en la lavadora o en la cocina y, cuando se te estaba acabando el detergente o el café, simplemente los apretabas. En ese momento, el botón mandaba una señal por Wi-Fi directo a Amazon para pedir el producto automáticamente.

Me parece bacán porque la lógica es exactamente la misma que usamos en el proyecto:

* *El sensor:* Un pulsador de contacto simple que detecta cuando lo aprietas.
* *El evento:* Ese toque genera un paquete de datos que viaja por la red (en nuestro caso a Adafruit IO, en el de ellos a los servidores de Amazon).
* *La respuesta:* La nube recibe el dato y hace algo. Para nosotros es prender un LED, para ellos era despachar un pedido a tu casa.

Lo que más me llamó la atención al investigar esto es que, aunque la escala es gigante comparada con nuestro circuito, ellos tuvieron que pelear con los mismos problemas que yo:

* *Saturación de datos:* Amazon no podía tener millones de botones mandando info cada segundo porque colapsarían. Por eso, al igual que nosotros con la Raspberry, el botón solo "despierta" y envía info cuando hay un evento real (la presión).
* *El Debouncing:* Imagínate si un niño se pone a jugar con el botón y lo aprieta 20 veces. Amazon tuvo que programar un filtro (un delay lógico) para no enviarte 10 bidones de detergente o 10 bolsas de kilo a la casa por error. Es el mismo concepto del "ojo cerrado" que usamos en nuestro código para que el Arduino no se maree con los rebotes de las chapitas metálicas.

<img width="330" height="350" alt="image" src="https://github.com/user-attachments/assets/9aaa784f-2b53-43c4-8ca0-9762efd376d5" />
<img width="330" height="350" alt="image" src="https://github.com/user-attachments/assets/11568db3-2787-4b4d-8a7c-73c83b3b6fad" />
<img width="330" height="350" alt="image" src="https://github.com/user-attachments/assets/e28aa9ba-868e-4903-9b9d-7722a21b1aca" />

Al final, es el mismo principio de "botón activa evento en la nube", y me sirve mucho para ver que lo que estamos aprendiendo se usa (o se usó) en productos que simplifican la vida de la gente.

### Referente Extra: Flic, El botón que puede salvar vidas

Flic es una empresa sueca que fabrica botones IoT inalámbricos usados en hospitales y clínicas. Los pacientes los tienen al lado de su cama y con un solo clic llaman a la enfermera de turno. El personal médico los usa como botones de pánico en situaciones de emergencia. No hay pantalla, no hay app que abrir, solo un botón físico que al presionarse manda una alerta instantánea al celular del equipo médico.

La lógica es exactamente la misma que usamos en clase: sensor de contacto detecta una presión → genera un evento → ese evento viaja por WiFi o Bluetooth a la nube → la nube genera una respuesta. En el Dash Button la respuesta era un pedido de detergente. Acá la respuesta puede ser una enfermera corriendo a una habitación.

Lo que hace interesante este referente es el contexto, demuestra que el mismo principio básico de un pulsador como sensor no tiene límite de aplicación. Desde encender un LED en clase hasta sistemas críticos de salud, la arquitectura es la misma: un humano presiona → una señal viaja → algo responde del otro lado.

<img width="330" height="350" alt="image" src="https://github.com/user-attachments/assets/0d17e394-7814-41bb-a447-56157b229782" />
<img width="330" height="350" alt="image" src="https://github.com/user-attachments/assets/c0e7b304-9a14-4b96-8b39-d6db6fbc23ce" />
<img width="330" height="350" alt="image" src="https://github.com/user-attachments/assets/5bc0cc85-75a7-443e-8a4e-956c22b4832c" />

# El Actuador: LED

### 1. ¿Qué aprendí sobre este actuador?

Un actuador es cualquier componente que convierte una señal eléctrica en algo físico. En el caso del **LED** (*Light Emitting Diode*, Diodo Emisor de Luz), esa salida física es luz.

<img width="330" height="350" alt="image" src="https://github.com/user-attachments/assets/be73b25d-6e9f-4f66-b5ba-e05542302c11" />
<img width="330" height="350" alt="image" src="https://github.com/user-attachments/assets/9db5fab5-6674-41cf-9c30-c9dfe99019d6" />
<img width="330" height="350" alt="image" src="https://github.com/user-attachments/assets/9aedcc7d-f33c-4069-9b16-a9f932943df4" />

Lo que más me costó entender al principio es que el LED no funciona como una ampolleta común. Es un **semiconductor**, y eso significa que la corriente no puede ser cualquier valor, si no se limita, el LED se destruye instantáneamente porque no tiene resistencia interna que lo proteja. Por eso siempre va con una resistencia en serie (en nuestro caso de **220Ω**) que controla cuánta corriente le llega.

**Dato: Límites operativos**

Investigando sobre componentes, me llamó la atención que existen LEDs con resistencia interna (se nota por un pequeño chip negro dentro del encapsulado). Buscando información técnica sobre ellos, encontré un reporte interesante que explica sus límites:

* *Funcionamiento ideal:* Trabajan de forma estable a 5V5V (aprox. 18mA18mA).
* *Zona de riesgo:* Al elevar el voltaje a 9V9V, el consumo sube a 30mA30mA, lo cual es bastante forzado y reduce la vida útil del componente.
* *Punto crítico:* Las pruebas de estrés indican que a 16V16V el componente falla catastróficamente (literalmente explota).

Mi conclusión: Esta información refuerza por qué es tan importante calcular bien la resistencia para nuestro proyecto. Aunque existen soluciones "todo en uno", entender la relación entre voltaje y corriente (Ley de Ohm) nos permite elegir el componente correcto y, sobre todo, saber cuándo estamos acercándonos a un límite peligroso para nuestra placa o el LED.

<img width="330" height="350" alt="image" src="https://github.com/user-attachments/assets/65aba760-3867-4d86-a908-473850764dd6" />
<img width="330" height="350" alt="image" src="https://github.com/user-attachments/assets/e57be755-e25a-4367-ae04-c7e969f0d7df" />
<img width="330" height="350" alt="image" src="https://github.com/user-attachments/assets/f709a3c2-8928-44e6-8005-65aabbbfde57" />


El pin del Arduino se configura como `OUTPUT` para que actúe como fuente de voltaje hacia el LED. Cuando el código manda un `HIGH`, el pin entrega 5V y el LED enciende. Cuando manda `LOW`, corta la corriente y se apaga.

---

### 2. Filtrado y visualización de datos

En el caso del LED el "filtrado" no ocurre en el sensor sino en la **recepción del mensaje**. El Arduino tiene que saber exactamente qué mensaje activar el LED y qué ignorar, no puede reaccionar a cualquier dato que llegue.

**Protocolo MQTT:** El sistema funciona por suscripción. El Arduino se "suscribe" a un canal específico en Adafruit IO y solo reacciona cuando llega el mensaje exacto que se programó. Si llega cualquier otra cosa, simplemente lo ignora. Eso es el filtrado del actuador, no reaccionar al ruido, solo a la instrucción correcta.

<img width="1000" height="450" alt="image" src="https://github.com/user-attachments/assets/6f48f77c-76b0-4aed-9a59-d1589517acfb" />

**Visualización:** El LED en sí mismo es la visualización más directa posible. Si el LED enciende, el dato viajó con éxito desde la Raspberry, pasó por Adafruit IO, llegó al Arduino y fue interpretado correctamente. Si no enciende, algo falló en algún punto de esa cadena, y eso lo convierte en una herramienta de diagnóstico muy útil además de ser el actuador del proyecto.

---

### 3. Problemas comunes

**Polaridad inversa:** El LED tiene una pata larga (**ánodo**, positivo) y una pata corta (**cátodo**, negativo). Si se conecta al revés, no pasa corriente y el LED no enciende pero tampoco se daña. El error es silencioso y puede hacer pensar que el problema está en el código cuando en realidad es solo el LED al revés. Se identifica al tacto: pata larga es el positivo.

<img width="330" height="350" alt="image" src="https://github.com/user-attachments/assets/d0b9a4b1-2fb8-41c8-a208-cbaa8a456851" />
<img width="330" height="350" alt="image" src="https://github.com/user-attachments/assets/99062674-495e-49fa-a3a6-3bf0564d098b" />
<img width="330" height="350" alt="image" src="https://github.com/user-attachments/assets/1ae34049-e305-4c49-955a-69f29d38fa64" />

**Baud rate incorrecto:** Si el puerto serie del Arduino no está sincronizado con el monitor (ambos deben estar en `115200`), el Arduino recibe caracteres nada que ver en vez de los mensajes reales de Adafruit IO. El LED nunca enciende aunque el código esté perfectamente escrito. Fue uno de los primeros detalles que se verificó en el proyecto exactamente para evitar ese problema.

<img width="500" height="528" alt="image" src="https://github.com/user-attachments/assets/e4568330-f2fe-4dae-8bef-2bc08603fa62" />
<img width="500" height="528" alt="image" src="https://github.com/user-attachments/assets/83238616-1ba9-489f-9906-6e9343fca1f9" />


**Resistencia muy baja:** Usar una resistencia demasiado baja (o no usar ninguna) no solo quema el LED, puede calentar el pin del microcontrolador y dañarlo con el tiempo. Con **220Ω** la corriente queda en un rango seguro tanto para el LED como para la placa.

<img width="500" height="350" alt="image" src="https://github.com/user-attachments/assets/f14151e3-27ea-41d1-9a1a-8693c708ccb9" />
<img width="500" height="350" alt="image" src="https://github.com/user-attachments/assets/56ae88e9-b9f3-4a6c-93f2-0afb9c1daf18" />

---

### 4. Referente: Leo Villareal — The Bay Lights

<img width="330" height="350" alt="image" src="https://github.com/user-attachments/assets/48321eea-c55b-4469-8cb6-00d473a2223e" />
<img width="330" height="350" alt="image" src="https://github.com/user-attachments/assets/a2cd9eac-e623-4dd7-a03f-72dad2a178c6" />
<img width="330" height="350" alt="image" src="https://github.com/user-attachments/assets/cc7a45a8-01a7-4247-87a2-fb9c89f4c850" />

Leo Villareal es un artista estadounidense conocido por instalaciones de luz a gran escala. Su obra más famosa, The Bay Lights, cubrió el puente Bay Bridge de San Francisco con 25,000 LEDs blancos distribuidos a lo largo de 2.9 km de cables verticales. El resultado es una instalación lumínica dinámica que cambia constantemente sin repetir nunca el mismo patrón.
Lo técnicamente interesante es que Villareal desarrolló software propio para generar los patrones, los algoritmos se inspiraban en cosas reales como las olas de la bahía, el viento y el flujo del tráfico en el puente. Es arte generativo: el código produce resultados únicos cada vez, así que la instalación nunca muestra lo mismo dos veces.
Estuvo encendida desde el 5 de marzo de 2013 hasta el 5 de marzo de 2023, exactamente 10 años. En 2024 comenzó su reinstalación con el doble de LEDs (50,000), financiada con 11 millones de dólares en donaciones privadas.

<img width="330" height="350" alt="image" src="https://github.com/user-attachments/assets/088d2ad5-905e-4a53-86ae-f615999fde3b" />
<img width="330" height="350" alt="image" src="https://github.com/user-attachments/assets/2cd96a80-e882-4e65-a8ac-da8c18afd0bb" />
<img width="330" height="350" alt="image" src="https://github.com/user-attachments/assets/f60b1dbd-11ff-40cc-b961-2007c13a3ff7" />
<img width="500" height="350" alt="image" src="https://github.com/user-attachments/assets/24512e60-8c80-4344-b189-ba7c98f18a02" />
<img width="500" height="350" alt="image" src="https://github.com/user-attachments/assets/b962d7dc-2172-4371-bca1-e4946120fbec" />

Lo que me parece interesante de este referente es que cada LED en esa instalación es exactamente lo mismo que el nuestro: un actuador que responde a una señal eléctrica. La diferencia es que Villareal tiene miles de ellos coordinados por un sistema central que les manda instrucciones en tiempo real, igual que Adafruit IO le manda instrucciones al nuestro. La lógica es dato en red → respuesta lumínica, a cualquier escala. Lo que hicimos en clase con un LED y un botón es, en esencia, la misma arquitectura que esa instalación de varios millones de dólares.

---

### Referencias

- [Cómo funciona el debouncing en botones](https://docs.arduino.cc/built-in-examples/digital/Debounce/)
- [Qué es el switch bounce y cómo hacer debounce](https://www.picotech.com/library/articles/blog/what-is-switch-bounce-how-to-implement-debounce)
- [Resistencias Pull-up y Pull-down — SparkFun](https://learn.sparkfun.com/tutorials/pull-up-resistors/all)
- [Resistencias Pull-up y Pull-down — Wilderness Labs](https://developer.wildernesslabs.co/Hardware/Tutorials/Electronics/Part4/PullUp_PullDown_Resistors/)
- [Amazon Dash Buttons — Wikipedia](https://en.wikipedia.org/wiki/Amazon_Dash)
- [Amazon Dash Buttons — qué eran y cómo funcionaban](https://www.oleoshop.com/blog/amazon-dash-buttons)
- [Cómo conectar un LED con Arduino](https://docs.arduino.cc/built-in-examples/basics/Blink/)
- [LEDs — guía completa SparkFun](https://learn.sparkfun.com/tutorials/light-emitting-diodes-leds/all)
- [Calcular resistencia para LED](https://learn.adafruit.com/adafruit-arduino-lesson-2-leds/leds)
- [The Bay Lights — reinstalación y financiamiento](https://www.thebaylights.org/)
- [Leo Villareal — The Bay Lights](http://villareal.net/the-bay-lights-2013-the-bay-bridge-sf-ca)
- [Protocolo MQTT explicado](https://io.adafruit.com/api/docs/mqtt.html)
- [Flic Smart Button — Emergency Medical Alarm](https://flic.io/es/healthcare/emergency-medical-alarm)
- [Flic Smart Button — Official Website](https://flic.io/)
