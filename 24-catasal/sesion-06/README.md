# sesion-06

lunes 13 abril 2026

Capacitancia

arduino_capacitive_touch, instalar en arduino

La librería arduino_capacitive_touch permite que una placa Arduino detecte el tacto utilizando sensores capacitivos. Este tipo de sensor funciona identificando pequeños cambios eléctricos cuando una persona toca una superficie conductora, como papel aluminio, cobre o cables. Gracias a esto, es posible crear botones táctiles sin necesidad de botones físicos tradicionales, lo que se utiliza mucho en proyectos interactivos, arte digital y domótica.

Para instalar la librería en el programa Arduino IDE, primero se debe abrir el IDE y dirigirse a la sección Programa → Incluir Librería → Administrar Bibliotecas. Luego, en el buscador, se escribe “CapacitiveSensor” o “capacitive touch” y se instala la librería correspondiente. Una vez instalada, ya se puede incluir en el código mediante la línea #include <CapacitiveSensor.h>. Esto permite acceder a funciones que leen la sensibilidad táctil de los sensores conectados.

El funcionamiento básico consiste en conectar dos pines del Arduino: uno actúa como emisor y el otro como receptor. Entre ambos se coloca una resistencia, normalmente de 1MΩ a 10MΩ, y el receptor se conecta al objeto que será tocado. Cuando una persona toca la superficie, el tiempo de carga eléctrica cambia y el Arduino interpreta esa variación como una interacción táctil. Este método es económico y fácil de implementar en proyectos educativos.

Los sensores capacitivos tienen muchas aplicaciones en diseño interactivo y tecnología creativa. Se utilizan en lámparas táctiles, instrumentos musicales electrónicos, interfaces artísticas y objetos inteligentes. También son populares en instalaciones donde se busca una interacción más natural entre las personas y los dispositivos. Al no requerir presión física, ofrecen una experiencia más moderna y sensible que un botón convencional.
