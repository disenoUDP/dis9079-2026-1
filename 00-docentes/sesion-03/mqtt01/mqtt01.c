// mqtt01
// marzo 2026
// raspberry pi pico 2 w
// por montoyamoraga para disenoUDP

// agregar bibliotecas
#include <stdio.h>
#include <string.h>
#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"
#include "lwip/apps/mqtt.h"
#include "lwip/ip_addr.h"

// configuracion wifi
#define WIFI_SSID "pixel9"
#define WIFI_PASSWORD "mateo123"

// configuracion mqtt
#define MQTT_BROKER "10.174.124.28"
#define MQTT_PORT 1883
#define MQTT_TOPIC "dis9079/20260323/led"

// declarar instancia de cliente mqtt
mqtt_client_t *cliente;

// funcion para controlar led
void set_led(bool estado)
{
    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, estado);
    printf("LED: %s\n", estado ? "prendido" : "apagado");
}

// funciones de callback para mqtt
static void mqtt_incoming_data_cb(void *arg, const u8_t *data, u16_t len, u8_t flags)
{
    char mensaje[50];
    memcpy(mensaje, data, len);
    mensaje[len] = '\0';

    printf("Mensaje recibido: %s\n", mensaje);

    if (strcmp(mensaje, "on") == 0)
    {
        set_led(true);
    }
    else if (strcmp(mensaje, "off") == 0)
    {
        set_led(false);
    }
}

// called when topic is received
static void mqtt_incoming_publish_cb(void *arg, const char *topic, u32_t tot_len)
{
    printf("Topic: %s\n", topic);
}

// connection result
static void mqtt_connection_cb(mqtt_client_t *client, void *arg, mqtt_connection_status_t status)
{
    if (status == MQTT_CONNECT_ACCEPTED)
    {
        printf("MQTT conectado ✅\n");

        // subscribe to topic
        mqtt_set_inpub_callback(client, mqtt_incoming_publish_cb, mqtt_incoming_data_cb, NULL);
        mqtt_subscribe(client, MQTT_TOPIC, 0, NULL, NULL);

        printf("Suscrito a: %s\n", MQTT_TOPIC);
    }
    else
    {
        printf("Error MQTT ❌: %d\n", status);
    }
}

// conexion wifi

void conectar_wifi()
{
    if (cyw43_arch_init())
    {
        printf("WiFi init failed\n");
        return;
    }

    cyw43_arch_enable_sta_mode();

    printf("Conectando a WiFi...\n");

    if (cyw43_arch_wifi_connect_timeout_ms(
            WIFI_SSID,
            WIFI_PASSWORD,
            CYW43_AUTH_WPA2_AES_PSK,
            10000))
    {
        printf("Error WiFi ❌\n");
        return;
    }

    printf("WiFi conectado ✅\n");
}

void conectar_mqtt()
{
    client = mqtt_client_new();

    ip_addr_t broker_ip;
    ipaddr_aton(MQTT_BROKER, &broker_ip);

    struct mqtt_connect_client_info_t ci = {
        .client_id = "pico_w_led"};

    printf("Conectando a MQTT...\n");

    mqtt_client_connect(client, &broker_ip, MQTT_PORT,
                        mqtt_connection_cb, NULL, &ci);
}

// funcion principal main()
int main()
{
    // inicializar stdio para la comunicacion serial
    stdio_init_all();

    // pausa para asegurar que serial monitor este lista
    sleep_ms(2000);

    conectar_wifi();
    conectar_mqtt();


    // Ejemplo para encender el LED del Pico W
    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1);

while (true)
    {
        // nothing here: everything happens via callbacks
        sleep_ms(1000);
    }
}
