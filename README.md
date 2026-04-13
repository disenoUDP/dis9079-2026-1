# dis9079-2026-1

dis9079 interacciones inalámbricas, primer semestre 2026

lunes, 2:30 a 5:20pm

02:30pm a 04:00pm - primera parte
04:00 a  04:20pm - descanso
04:20 a 05:20pm - segunda parte

## equipo docente

* aarón montoya <https://github.com/montoyamoraga>: profesore
* mateo arce <https://github.com/matbutom>: ayudante

## unidades

## calendario

| sesión                         | fecha       | temas                                                 |
| :----------------------------- | :---------- | :---------------------------------------------------- |
| [01](./00-docentes/sesion-01/) | 03-09 lun   | intro a interacciones inalámbricas, github, markdown  |
| [02](./00-docentes/sesion-02/) | 03-16 lun   | protocolos de comunicación MQTT en microcontroladores |
| [03](./00-docentes/sesion-03/) | 03-23 lun   | comunicación inalámbrica entre distintos dispositivos |
| [04](./00-docentes/sesion-04/) | 03-30 lun   | estrategias para mensajes inalámbricos                |
| [05](./00-docentes/sesion-05/) | 04-06 lun   | solemne 1                                             |
| [06](./00-docentes/sesion-06/) | 04-13 lun   | retroalimentación solemne 1, sensor capacitivo        |
| [07](./00-docentes/sesion-07/) | 04-20 lun   | sensores análogicos y digitales                       |
| [08](./00-docentes/sesion-08/) | 04-27 lun   | actuadores, motor servo, buzzer                       |
| receso                         | 05-01/09    | semana de receso                                      |
| [09](./00-docentes/sesion-09/) | 05-11 lun   | trabajo en solemne 2                                  |
| [10](./00-docentes/sesion-10/) | 05-18 lun   | solemne 2                                             |
| [11](./00-docentes/sesion-11/) | 05-25 lun   | escritura de manuales y diagramas                     |
| [12](./00-docentes/sesion-12/) | 06-01 lun   | comunicación bidireccional                            |
| [13](./00-docentes/sesion-13/) | 06-08 lun   | trabajo en examen                                     |
| [14](./00-docentes/sesion-14/) | 06-15 lun   | trabajo en examen                                     |
| [15](./00-docentes/sesion-15/) | 06-22 lun   | examen                                                |

## asistencia

Desde 2026, para aprobar un curso en Diseño UDP, es necesario asistir a un mínimo del 80% de las sesiones.

## evaluaciones

este curso de profundización tiene 2 solemnes en fechas establecidas por la escuela.

el promedio de ambas solemnes recibe el nombre de nota de presentación NP.

para poder rendir el examen final, es necesario obtener una nota de presentación NP >= 3.5 y cumplir con el requisito de asistencia mínima.

para la nota final del curso, se pondera 70% NP y 30% examen final.

## Servidor MQTT

Para correr el servidor Mosquitto local:

```bash
cd /dis9079-2026-1
mosquitto -c mosquitto.conf
```

Para ver la interfaz visual del broker, usamos [MQTT Explorer](https://mqtt-explorer.com/):

```bash
open "/Applications/MQTT Explorer.app"
```

Conectarse con:

* Host: `localhost`
* Port: `1883`
* Username: `matbutom`
* Password: `dis9079`

## Bibliografía obligatoria

* Tim Pulver, Hands-On Internet of Things with MQTT, Packt Publishing, 2019.
* Samuel Greengard, The Internet of Things, MIT Press, 2015.
* Dhairya Parikh, Raspberry Pi and MQTT Essentials, Packt Publishing, 2022.
* Claire Rowland et al, Designing Connected Products, O’Reilly Media, 2015.
* Stefan Poslad, Ubiquitous Computing, Wiley, 2009.

## Bibliografía complementaria

* Paul Dourish, Where the Action Is, MIT Press, 2001.
* Paul Dourish, The Stuff of Bits, MIT Press, 2022.
* Michael Connor et al, The Art Happens Here: Net Art Anthology, Rhizome, 2019.
* The Connectivity of Things: Network Cultures since 1832, MIT Press, 2024.
* Edward Shanken, Systems, MIT Press, 2015.
