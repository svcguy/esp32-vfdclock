/* main.c
 *
 * Template app main.c
 * 
 * Andy Josephson 12/2018
 */

#include "nvs_flash.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define RD_LED_PIN  GPIO_NUM_0
#define GR_LED_PIN  GPIO_NUM_2
#define BL_LED_PIN  GPIO_NUM_4
#define LED_ON      1
#define LED_OFF     0

static const char* TAG = "app_main";

static void heartbeat_task(void* arg);
static void gpio_setup(void);

void app_main(void)
{
    ESP_LOGI(TAG, "Starting app_main");
    nvs_flash_init();
    gpio_setup();

    ESP_LOGI(TAG, "Creating tasks");
    xTaskCreate(heartbeat_task, "task_hrtbt", 1024, NULL, 0, NULL);

    while(1)
    {
    }
}

static void heartbeat_task(void* arg)
{
    bool level = 0;
    while(1)
    {
        gpio_set_level( BL_LED_PIN, level);
        vTaskDelay(500/portTICK_RATE_MS);
        level = !level;
    }
}

static void gpio_setup(void)
{
    ESP_ERROR_CHECK( gpio_set_direction(BL_LED_PIN, GPIO_MODE_OUTPUT) );
    ESP_ERROR_CHECK( gpio_set_direction(GR_LED_PIN, GPIO_MODE_OUTPUT) );
    ESP_ERROR_CHECK( gpio_set_direction(RD_LED_PIN, GPIO_MODE_OUTPUT) );
    
    ESP_ERROR_CHECK( gpio_set_level(GPIO_NUM_0, LED_OFF) );
    ESP_ERROR_CHECK( gpio_set_level(GPIO_NUM_2, LED_OFF) );
    ESP_ERROR_CHECK( gpio_set_level(GPIO_NUM_4, LED_OFF) );
}