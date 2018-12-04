#include "nvs_flash.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

static const char* TAG = "app_main";

void app_main(void)
{
    ESP_LOGI(TAG, "Starting app_main");
    nvs_flash_init();
    
    ESP_ERROR_CHECK( gpio_set_direction(GPIO_NUM_0, GPIO_MODE_OUTPUT) );
    ESP_ERROR_CHECK( gpio_set_direction(GPIO_NUM_2, GPIO_MODE_OUTPUT) );
    ESP_ERROR_CHECK( gpio_set_direction(GPIO_NUM_4, GPIO_MODE_OUTPUT) );
    
    ESP_ERROR_CHECK( gpio_set_level(GPIO_NUM_0, 0) );
    ESP_ERROR_CHECK( gpio_set_level(GPIO_NUM_2, 0) );
    ESP_ERROR_CHECK( gpio_set_level(GPIO_NUM_4, 0) );

    ESP_LOGI(TAG, "Starting app_main superloop");
    bool level=0;
    while(1)
    {
        ESP_ERROR_CHECK( gpio_set_level(GPIO_NUM_4, level));
        level = !level;
        vTaskDelay(500/portTICK_PERIOD_MS);
    }
}

