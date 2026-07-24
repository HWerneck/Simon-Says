#ifndef LEDS_H
#define LEDS_H

#include <stdbool.h>
#include "common/colour.h"

void led_init(void);
void led_on(Colour colour);
void led_off(Colour colour);
void led_toggle(Colour colour);
void led_set(Colour colour, bool state);
void leds_all_on(void);
void leds_all_off(void);

#endif