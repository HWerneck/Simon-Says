/*#include <stdio.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "driver/gpio.h"
#include "driver/ledc.h"
#include "esp_log.h"

#define LED_GPIO GPIO_NUM_2
//#define BUZZER_GPIO GPIO_NUM_4

#define NUM_COLORS 4
#define LED_BLUE       GPIO_NUM_16
#define LED_GREEN      GPIO_NUM_17
#define LED_YELLOW     GPIO_NUM_18
#define LED_RED        GPIO_NUM_19

#define BUTTON_BLUE       GPIO_NUM_27
#define BUTTON_GREEN      GPIO_NUM_26
#define BUTTON_YELLOW     GPIO_NUM_25
#define BUTTON_RED        GPIO_NUM_32

#define BUZZER         GPIO_NUM_33

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

#include "board/board.h"
#include "games/simon_says.h"

void app_main(void)
{
    board_init();
    simon_says_run();
}