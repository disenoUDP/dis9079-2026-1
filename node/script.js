let mqtt = require('mqtt');

let client = mqtt.connect('mqtt://localhost:1883', {
    protocolVersion: 5,
    clientId: 'mqttjs_' + Math.random().toString(16).substr(2, 8),
    clean: true,
    connectTimeout: 4000,
    username: 'montoyamoraga',
    password: 'dis9079',
    reconnectPeriod: 1000
});

// mqtt.Client#publish(topic, message, [options], [callback]);

