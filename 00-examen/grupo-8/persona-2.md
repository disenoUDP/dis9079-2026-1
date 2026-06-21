# persona-2

antolavalle

# APIs Web

## ¿Qué es una API?

**API** = Application Programming Interface

Es un intermediario que te permite usar funcionalidades complejas sin tener que entender cómo funcionan por dentro.

La analogía clásica: enchufas un electrodoméstico y funciona. No necesitas saber nada de electricidad. La API es el enchufe.

```
tú  →  API  →  sistema complejo (GPS, servidor, hardware...)
```

---

## Tipos de APIs en el navegador

**De navegador** → ya vienen incluidas, no hay que instalar nada
- Geolocation API, DOM, Canvas, Web Audio...

**De terceros** → hay que traerlas de afuera
- Twitter API, Google Maps, Twilio...

---

## ¿Para qué sirven? (por categoría)

| qué quieres hacer | API que usas |
|---|---|
| manipular HTML/CSS | DOM API |
| pedir datos a un servidor | Fetch API / XMLHttpRequest |
| dibujar en pantalla | Canvas / WebGL |
| reproducir audio/video | Web Audio API / WebRTC |
| saber dónde está el usuario | Geolocation API |
| guardar datos en el browser | IndexedDB / Web Storage |
| mandar notificaciones | Notifications API |

---

## Cómo funcionan

### Están basadas en objetos

```js
// accedes a la API a través de un objeto
navigator.geolocation.getCurrentPosition(function(pos) {
  console.log(pos.coords.latitude)
})
```

### Son asíncronas

No puedes esperar que los datos lleguen al instante. Por eso usan **callbacks** o **Promises**:

```js
//  esto no funciona
var pos = navigator.geolocation.getCurrentPosition()
console.log(pos.latitude) // undefined, todavía no llegó

//  así sí
navigator.geolocation.getCurrentPosition(function(pos) {
  console.log(pos.coords.latitude) // aquí sí tienes los datos
})
```

### Algunas piden permiso

Geolocation, Notifications, la cámara... el navegador le pregunta al usuario antes de darte acceso. Es por seguridad.

### Algunas solo funcionan con HTTPS

Service Workers, Push API... si estás en `http://` no van a funcionar.

---

## API vs Servicio web

| | API | Servicio web |
|---|---|---|
| necesita red | no siempre | siempre |
| protocolos | cualquiera | casi siempre SOAP |
| acceso | suelen ser abiertas | más restringido |

> todo servicio web es una API, pero no toda API es un servicio web

---

## Microservicios

Un microservicio es una app pequeña que hace **una sola cosa** y se comunica con el resto a través de APIs.

```
app grande
├── servicio de login   → expone una API
├── servicio de pagos   → expone una API
└── servicio de emails  → expone una API
```

La diferencia con un servicio web: el microservicio es la **app en sí**, el servicio web es la **estrategia de comunicación**.

---

## APIs que existen

```
red        → Fetch, WebSockets, XMLHttpRequest
storage    → IndexedDB, localStorage, Cache API
media      → Canvas, WebGL, Web Audio, WebRTC
device     → Geolocation, Vibration, Battery
workers    → Web Workers, Service Workers
seguridad  → Web Crypto, Credential Management
otros      → Bluetooth, USB, NFC, Payments...
```

---

*fuentes: [MDN](https://developer.mozilla.org/es/docs/Web/API) · [MDN intro](https://developer.mozilla.org/es/docs/Learn_web_development/Extensions/Client-side_APIs/Introduction) · [Parasoft](https://es.parasoft.com/blog/web-api-vs-web-services-microservices-basics-differences/)*
