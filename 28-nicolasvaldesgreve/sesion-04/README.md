# sesion-04

lunes 30 marzo 2026

# Apuntes 30/03

Para la clase Aarón trajo un router de tp-link el cual estará conectado a un computador raspberry que estará siempre activo!! el computador siempre tendrá la misma IP (192.168.0.100). Mateo escribió "ssh raspi@192.168.0.100" y eso es tocar la puerta del computador, en donde te preguntará si te quieres conectar, y luego te pide una contraseña. Con ayuda de tigerVNC puedes entrar al computador y ver un renderizado de lo que hay dentro

sudo: su (super user, admin) do (hacer) + rm  (remove) rf (recursivamente, force) = sudo rm rf = eliminar todo de manera recursiva a la fuerza, es decir, matar el computador.

+ Cualquier persona que envia, debe hacerlo con un topic en específico, al igual que cualquier persona que recibe tiene que tener un topic en específico sino no se va a conectar
+ El puerto 1883 es el que más se usa en mqtt, pero se puede usar otro.
+ username e ID no son lo mismo 
+ -c correr en mosquitto
+ -v moquitto piensa en voz alta

---

Se intentó hacer el ejercicio de enviar y recibir mensajes mediante el arduino con mqtt, pero hubieron problemas y se pudo lograr enviar mensajes pero no se recibían, por lo que se intentó arreglar pensando que era porque el Username y el ID eran lo mismo, pero al editarlo siguió sin funcionar, razón por la cual se utilizó inteligencia artifical para buscar soluciones pero luego de muchos intentos, tampoco funcionó.

Mosquitto nos falló, por lo que se está tratando de hacer el ejercicio con otro protocolo, que en éste caso es UDP (no se llama así por Diego Portales)

- Protocolo UDP (user datagram protocol): Éste protocolo también sirve para enviar mensajes, pero no le importa si éstos llegan o no, por lo que no es bueno para enviar audio ya que se necesita algo constante y preciso.

---

# Encargo de artista

Mientras estaba buscando artistas o diseñadores que usen electrónica o computación inalámbrica, recordé que vi un video de Laurie Anderson (que en ese momento solo la conocía por su canción ["O Superman"](https://www.youtube.com/watch?v=Vkfpi2H8tOE&list=RDVkfpi2H8tOE&start_radio=1)) en donde estaba bailando con un traje que cada vez que tocaba ciertas partes de su cuerpo o movía los brazos sonaba una batería, pero no estaba seguro de si era ella la que creó el traje hasta que hoy busqué y me di cuenta que en efecto, el traje es su creación, y no solo creó el traje sino que también hizo un violín de arco de cinta que en vez de tener cuerdas, éste tiene un bacezal magnético.

Anderson creció en Chicago pero en mediados de los 60' se mudó a Nueva York, en donde estudió historia del arte y escultura y conoció a Lou Reed, su pareja. Muchas personas logran identificar a Laurie porque la asocian a Lou Reed, no solo por ser pareja sino porque durante años hicieron giras juntos e hicieron proyectos en conjunto y por lo que he leido éste es bien reconocido en el género del rock, lo cual se me hace extraño pero ésto puede ser porque las personas de mi generación reconocemos primero a Laurie por sus obras y por asociación de ella reconocemos a Lou. Uno de sus actos de performance logró captar bastante atención en el año 1972, el cual fue "Duets on Ice" en donde patinaba por Manhattan sobre cubos de hielo al mismo tiempo que iba tocando violín.

Volviendo al traje, Anderson hizo un concierto en donde performó con ésta prenda la cual tiene sensores de movimiento que generan sonidos de batería, y se demostró que cada parte del cuerpo generaba un sonido distinto, logrando así poder mostrar todos los sonidos que hace la batería al mover los brazos, golpear a los costados de su pecho y golpeando sus rodillas. Dejo aquí el link a un clip del concierto: <https://www.youtube.com/watch?v=gRcVqL-2PMA>.

Fuentes:

<https://mujeresbacanas.com/la-eterna-pionera-laurie-anderson-1947-es-una/>

<https://angelsferrerb.wordpress.com/2022/09/21/laurie-anderson-una-artista-pionera-en-el-arte-multimedia-y-la-realidad-virtual-sin-limites/>
