# esp-ap-and-ap-sta
Repositorie created to aid during my ESP32 WiFi learning.

# AP Code

New defines were created.

```c
#define AP_SSID "ESP32_AP"
#define AP_PASSWORD "0123" 
#define AP_MAX_CONN 5
#define AP_CHANNEL 0
```
The WiFi initialization code:

```c
static esp_err_t init_wifi(void){
    wifi_init_config_t wifi_init_config = WIFI_INIT_CONFIG_DEFAULT(); // macro default

    esp_netif_init();
    esp_event_loop_create_default();
    nvs_flash_init();
    esp_wifi_init(&wifi_init_config);
    esp_wifi_set_mode(WIFI_MODE_AP); // Changed to AP mode
    esp_wifi_set_storage(WIFI_STORAGE_FLASH);

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

    printf("WiFi initialization completed.");
    return ESP_OK;
}
```
## Results

After flashing and monitoring:

![WhatsApp Image 2024-01-02 at 22 06 28_5d62491c](https://github.com/Rafaelatff/esp-ap-and-ap-sta/assets/58916022/049cc28c-3614-4bc9-9f4a-9b4a39171e8a)

Searching for network:

![WhatsApp Image 2024-01-02 at 22 02 47_cef66725](https://github.com/Rafaelatff/esp-ap-and-ap-sta/assets/58916022/72c391c9-3595-49c7-bd2c-82af144ab95e)

Connecting to the network:

![WhatsApp Image 2024-01-02 at 22 10 12_86225851](https://github.com/Rafaelatff/esp-ap-and-ap-sta/assets/58916022/70284f95-9992-4e60-89eb-43dd2d6ddcb2)

When connecting:

![WhatsApp Image 2024-01-02 at 22 08 35_add51573](https://github.com/Rafaelatff/esp-ap-and-ap-sta/assets/58916022/976fcad7-181d-412f-8185-d958deadb846)

# AP STA Code

New defines were created:

```c
#define STA_SSID "ESP32_STA"
#define STA_PASSWORD "0123"
```

```c
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
```

## Results

After flashing and monitoring:

![WhatsApp Image 2024-01-02 at 23 00 14_f902070a](https://github.com/Rafaelatff/esp-ap-and-ap-sta/assets/58916022/0d96876b-9327-4190-902d-5997b4ef12f8)

Then, when I connecte to the ESP32_AP network:

![WhatsApp Image 2024-01-02 at 23 02 35_d42dfb1b](https://github.com/Rafaelatff/esp-ap-and-ap-sta/assets/58916022/21363612-4005-45ba-b28c-5e01d94ec2c6)


