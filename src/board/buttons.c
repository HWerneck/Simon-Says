#include "buttons.h"
#include <assert.h>
#include "driver/gpio.h"
#include "esp_err.h"

static const gpio_num_t BUTTON_PINS[COLOUR_COUNT] =
{
    GPIO_NUM_27, // BLUE
    GPIO_NUM_26, // GREEN
    GPIO_NUM_25, // YELLOW
    GPIO_NUM_32  // RED
};

void buttons_init(void)
{
    uint64_t pin_mask = 0;
    for (Colour colour_iterator = COLOUR_BLUE; colour_iterator < COLOUR_COUNT; colour_iterator++)
    {
        pin_mask |= (1ULL << BUTTON_PINS[colour_iterator]);
    }

    gpio_config_t config =
    {
        .mode = GPIO_MODE_INPUT,
        .pin_bit_mask = pin_mask,
        .pull_up_en = GPIO_PULLUP_ENABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE
    };
    ESP_ERROR_CHECK(gpio_config(&config));
    return;
}

bool get_button_down(Colour *colour)
{
    if (colour == NULL)
    {
        return false;
    }

    for (Colour colour_iterator = COLOUR_BLUE; colour_iterator < COLOUR_COUNT; colour_iterator++)
    {
        if (gpio_get_level(BUTTON_PINS[colour_iterator]) == 0)
        {
            *colour = colour_iterator;
            return true;
        }
    }
    return false;
}