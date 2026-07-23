void simon_says()
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
}

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