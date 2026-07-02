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