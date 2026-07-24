#include "simon_says.h"
#include "simon_says_state.h"
#include "simon_says_types.h"
#include "board/buttons.h"
#include "board/buzzer.h"
#include "board/leds.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

static SimonGame game;
static SimonState state;

static void simon_says_new_game(void)
{
    game.sequence_length = 0;
    game.player_position = 0;
    game.score = 0;
    state = SIMON_STATE_ADD_COLOUR;
}

void simon_says_run(void)
{
    simon_says_new_game();
    while (true)
    {
        switch (state)
        {
            case SIMON_STATE_NEW_GAME:
                simon_says_new_game();
                break;
            case SIMON_STATE_ADD_COLOUR:
                break;
            case SIMON_STATE_SHOW_SEQUENCE:
                break;
            case SIMON_STATE_WAIT_PLAYER:
                break;
            case SIMON_STATE_NEXT_ROUND:
                break;
            case SIMON_STATE_GAME_OVER:
                break;
        }
        vTaskDelay(pdMS_TO_TICKS(10));
    }
}


/*void simon_says()
{
    printf("Simon Says!");
    int player_score = 0;
    while(true)
    {
        increase_sequence();
        present_sequence();
        play_ready_up_sound();
        if (player_sequence_matches())
        {
            player_score += 1;
        }
        else
        {
            game_over();
            break;
        }
    }
}*/

/*    int current = 0;
    gpio_set_level(leds[current], 1);

    while (1)
    {
        if (gpio_get_level(buttons[current]) == 0)
        {
            int previous = current;
            beep();
            gpio_set_level(leds[current], 0);
            current = (current + 1) % num_leds;
            gpio_set_level(leds[current], 1);
            while (gpio_get_level(buttons[previous]) == 0)
            {
                vTaskDelay(pdMS_TO_TICKS(10));
            }
        }
        vTaskDelay(pdMS_TO_TICKS(10));
    }
*/