#include "board.h"
#include "leds.h"
#include "buttons.h"
#include "buzzer.h"

void board_init(void)
{
    led_init();
    button_init();
    buzzer_init();
}