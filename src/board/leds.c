#include "leds.h"
#include "driver/gpio.h"
#include "esp_err.h"

static const gpio_num_t LED_PINS[COLOUR_COUNT] =
{
    GPIO_NUM_16, // BLUE
    GPIO_NUM_17, // GREEN
    GPIO_NUM_18, // YELLOW
    GPIO_NUM_19  // RED
};

void leds_init(void)
{
    uint64_t pin_mask = 0;
    for (Colour colour_iterator = COLOUR_BLUE; colour_iterator < COLOUR_COUNT; colour_iterator++)
    {
        pin_mask |= (1ULL << LED_PINS[colour_iterator]);
    }

    gpio_config_t config =
    {
        .mode = GPIO_MODE_OUTPUT,
        .pin_bit_mask = pin_mask,
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE
    };
    ESP_ERROR_CHECK(gpio_config(&config));

    leds_all_off();
    return;
}

void led_on(Colour colour)
{
    assert(colour < COLOUR_COUNT);
    if (colour >= COLOUR_COUNT)
    {
        return;
    }
    gpio_set_level(LED_PINS[colour], 1);
    return;
}

void led_off(Colour colour)
{
    if (colour >= COLOUR_COUNT)
    {
        return;
    }
    gpio_set_level(LED_PINS[colour], 0);
    return;
}

void led_toggle(Colour colour)
{
    if (colour >= COLOUR_COUNT)
    {
        return;
    }
    int state = gpio_get_level(LED_PINS[colour]);
    gpio_set_level(LED_PINS[colour], !state);
    return 0;
}

void led_set(Colour colour, bool state)
{
    if (colour >= COLOUR_COUNT)
    {
        return;
    }
    gpio_set_level(LED_PINS[colour], state);
    return;
}

void leds_all_on(void)
{
    for (Colour colour_iterator = COLOUR_BLUE; colour_iterator < COLOUR_COUNT; colour_iterator++)
    {
        led_on(colour_iterator);
    }
    return;
}

void leds_all_off(void)
{
    for (Colour colour_iterator = COLOUR_BLUE; colour_iterator < COLOUR_COUNT; colour_iterator++)
    {
        led_off(colour_iterator);
    }
    return;
}