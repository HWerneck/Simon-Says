/*#include <stdio.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "driver/gpio.h"
#include "driver/ledc.h"
#include "esp_log.h"

#define LED_GPIO GPIO_NUM_2
#define BUZZER_GPIO GPIO_NUM_4

#define LEDC_TIMER      LEDC_TIMER_0
#define LEDC_MODE       LEDC_LOW_SPEED_MODE
#define LEDC_CHANNEL    LEDC_CHANNEL_0
#define LEDC_DUTY       512       // 50% para resolução de 10 bits
#define LEDC_RESOLUTION LEDC_TIMER_10_BIT

void buzzer_play(uint32_t frequency)
{
    ledc_set_freq(LEDC_MODE, LEDC_TIMER, frequency);
    ledc_set_duty(LEDC_MODE, LEDC_CHANNEL, LEDC_DUTY);
    ledc_update_duty(LEDC_MODE, LEDC_CHANNEL);
}

void buzzer_stop(void)
{
    ledc_set_duty(LEDC_MODE, LEDC_CHANNEL, 0);
    ledc_update_duty(LEDC_MODE, LEDC_CHANNEL);
}

void app_main(void)
{
    esp_log_level_set("gpio", ESP_LOG_NONE);
    esp_log_level_set("wifi", ESP_LOG_NONE);
    esp_log_level_set("*", ESP_LOG_NONE);
    printf("Hello World!\n");
    gpio_reset_pin(LED_GPIO);
    gpio_set_direction(LED_GPIO, GPIO_MODE_OUTPUT);

    ledc_timer_config_t timer = {
        .speed_mode = LEDC_MODE,
        .duty_resolution = LEDC_RESOLUTION,
        .timer_num = LEDC_TIMER,
        .freq_hz = 440,
        .clk_cfg = LEDC_AUTO_CLK
    };

    ledc_timer_config(&timer);

    ledc_channel_config_t channel = {
        .gpio_num = BUZZER_GPIO,
        .speed_mode = LEDC_MODE,
        .channel = LEDC_CHANNEL,
        .timer_sel = LEDC_TIMER,
        .duty = 0,
        .hpoint = 0
    };

    ledc_channel_config(&channel);

    const uint32_t notes[] = {
        262, // C4
        294, // D4
        330, // E4
        349  // F4
    };

    while (1)
    {
        gpio_set_level(LED_GPIO, 1);
        for (int i = 0; i < 4; i++)
        {
            buzzer_play(notes[i]);
            vTaskDelay(pdMS_TO_TICKS(1000));
        }
        buzzer_stop();

        gpio_set_level(LED_GPIO, 0);
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}*/

#include <stdio.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "driver/gpio.h"
#include "driver/ledc.h"

#define LED_BLUE       GPIO_NUM_16
#define LED_GREEN      GPIO_NUM_17
#define LED_YELLOW     GPIO_NUM_18
#define LED_RED        GPIO_NUM_19

#define BTN_BLUE       GPIO_NUM_27
#define BTN_GREEN      GPIO_NUM_26
#define BTN_YELLOW     GPIO_NUM_25
#define BTN_RED        GPIO_NUM_32

#define BUZZER         GPIO_NUM_33

static void gpio_init_all(void)
{
    gpio_config_t out = {
        .mode = GPIO_MODE_OUTPUT,
        .pin_bit_mask =
            (1ULL << LED_BLUE) |
            (1ULL << LED_GREEN) |
            (1ULL << LED_YELLOW) |
            (1ULL << LED_RED)
    };

    gpio_config(&out);

    gpio_config_t in = {
        .mode = GPIO_MODE_INPUT,
        .pull_up_en = GPIO_PULLUP_ENABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .pin_bit_mask =
            (1ULL << BTN_BLUE) |
            (1ULL << BTN_GREEN) |
            (1ULL << BTN_YELLOW) |
            (1ULL << BTN_RED)
    };

    gpio_config(&in);
}

static void buzzer_init(void)
{
    ledc_timer_config_t timer = {
        .speed_mode = LEDC_LOW_SPEED_MODE,
        .timer_num = LEDC_TIMER_0,
        .duty_resolution = LEDC_TIMER_10_BIT,
        .freq_hz = 2000,
        .clk_cfg = LEDC_AUTO_CLK
    };

    ledc_timer_config(&timer);

    ledc_channel_config_t channel = {
        .gpio_num = BUZZER,
        .speed_mode = LEDC_LOW_SPEED_MODE,
        .channel = LEDC_CHANNEL_0,
        .timer_sel = LEDC_TIMER_0,
        .duty = 0,
        .hpoint = 0
    };

    ledc_channel_config(&channel);
}

static void beep(void)
{
    ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0, 512);
    ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0);

    vTaskDelay(pdMS_TO_TICKS(100));

    ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0, 0);
    ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0);
}

/*void app_main(void)
{
    gpio_init_all();
    buzzer_init();

    gpio_set_level(LED_BLUE, 1);

    bool led_apagado = false;

    while (1)
    {
        if (!led_apagado && gpio_get_level(BTN_BLUE) == 0)
        {
            gpio_set_level(LED_BLUE, 0);
            beep();
            led_apagado = true;

            while (gpio_get_level(BTN_BLUE) == 0)
            {
                vTaskDelay(pdMS_TO_TICKS(10));
            }
        }

        vTaskDelay(pdMS_TO_TICKS(10));
    }
}*/

void app_main(void)
{
    gpio_init_all();
    buzzer_init();
    
    const gpio_num_t leds[] = {
        LED_BLUE,
        LED_GREEN,
        LED_YELLOW,
        LED_RED
    };

    const gpio_num_t buttons[] = {
        BTN_BLUE,
        BTN_GREEN,
        BTN_YELLOW,
        BTN_RED
    };

    const int num_leds = sizeof(leds) / sizeof(leds[0]);

    int current = 0;

    gpio_set_level(leds[current], 1);

    while (1)
    {
        if (gpio_get_level(buttons[current]) == 0)
        {
            beep();

            gpio_set_level(leds[current], 0);

            current = (current + 1) % num_leds;

            gpio_set_level(leds[current], 1);

            while (gpio_get_level(buttons[current == 0 ? num_leds - 1 : current - 1]) == 0)
            {
                vTaskDelay(pdMS_TO_TICKS(10));
            }
        }

        vTaskDelay(pdMS_TO_TICKS(10));
    }
}