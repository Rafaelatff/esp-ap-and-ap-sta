#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_event.h"
#include "esp_system.h"
#include "esp_wifi.h"
#include "nvs_flash.h"
#include "esp_netif.h" // replaces the #include "tcpip_adapter.h"
#include <string.h> // to use 'memset'

#define MAXIMUM_AP 20

#define AP_SSID "ESP32_AP"
#define AP_PASSWORD "0123" 
#define AP_MAX_CONN 5
#define AP_CHANNEL 0

#define STA_SSID "ESP32_STA"
#define STA_PASSWORD "0123" 

static esp_err_t init_wifi(void){
    wifi_init_config_t wifi_init_config = WIFI_INIT_CONFIG_DEFAULT(); // macro default

    esp_netif_init();
    esp_event_loop_create_default();
    nvs_flash_init();
    esp_wifi_init(&wifi_init_config);
    esp_wifi_set_mode(WIFI_MODE_APSTA); // Changed to AP STA mode
    esp_wifi_set_storage(WIFI_STORAGE_FLASH);
    wifi_config_t sta_config = {
        .sta = {
            .ssid = STA_SSID,
            .password = AP_PASSWORD,
        },
    };
    esp_wifi_set_config(ESP_IF_WIFI_STA, &sta_config);
    

    wifi_config_t ap_config = {
        .ap = {
            .ssid = AP_SSID,
            .password = AP_PASSWORD,
            .max_connection = AP_MAX_CONN,
            .channel = AP_CHANNEL,
            .ssid_hidden = 0, // not show_hidden
        },
    };
    esp_wifi_set_config(ESP_IF_WIFI_AP, &ap_config);

    esp_wifi_start();
    esp_wifi_connect();

    printf("WiFi initialization completed.");
    return ESP_OK;
}

void app_main(void)
{
    ESP_ERROR_CHECK(init_wifi());

    while(1){
        vTaskDelay(3000/ portTICK_PERIOD_MS);
    }
}
