#include "buzzer.h"
#include "notes.h"
#include "driver/ledc.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define BUZZER_GPIO         GPIO_NUM_33

#define BUZZER_TIMER        LEDC_TIMER_0
#define BUZZER_MODE         LEDC_LOW_SPEED_MODE
#define BUZZER_CHANNEL      LEDC_CHANNEL_0
#define BUZZER_RESOLUTION   LEDC_TIMER_10_BIT
#define BUZZER_DUTY         512

static const BuzzerNote BUTTON_BLUE_MELODY[] =
{
    { NOTE_C4, 150 }
};

static const BuzzerNote BUTTON_GREEN_MELODY[] =
{
    { NOTE_D4, 150 }
};

static const BuzzerNote BUTTON_YELLOW_MELODY[] =
{
    { NOTE_E4, 150 }
};

static const BuzzerNote BUTTON_RED_MELODY[] =
{
    { NOTE_F4, 150 }
};

static const BuzzerNote BEEP_MELODY[] =
{
    { NOTE_A4, 100 }
};

static const BuzzerNote SUCCESSFUL_SEQUENCE_MELODY[] =
{
    { NOTE_C4, 120 },
    { NOTE_E4, 120 },
    { NOTE_G4, 120 },
    { NOTE_C5, 250 }
};

static const BuzzerNote VICTORY_MELODY[] =
{
    { NOTE_C4, 120 },
    { NOTE_E4, 120 },
    { NOTE_G4, 120 },
    { NOTE_C5, 250 },
    { NOTE_C4, 120 },
    { NOTE_E4, 120 },
    { NOTE_G4, 120 },
    { NOTE_C5, 250 },
    { NOTE_C4, 120 },
    { NOTE_E4, 120 },
    { NOTE_G4, 120 },
    { NOTE_C5, 250 }
};

static const BuzzerNote GAME_OVER_MELODY[] =
{
    { NOTE_G4, 180 },
    { NOTE_E4, 180 },
    { NOTE_C4, 350 }
};

static void play_sequence(const BuzzerNote *notes,
                          uint32_t count)
{
    for(uint32_t iii = 0; iii < count; iii++)
    {
        buzzer_play_note(notes[iii].frequency_hz,
                         notes[iii].duration_ms);
        vTaskDelay(pdMS_TO_TICKS(30));
    }
    return;
}

void buzzer_init(void)
{
    ledc_timer_config_t timer =
    {
        .speed_mode = BUZZER_MODE,
        .duty_resolution = BUZZER_RESOLUTION,
        .timer_num = BUZZER_TIMER,
        .freq_hz = NOTE_A4,
        .clk_cfg = LEDC_AUTO_CLK
    };
    ledc_timer_config(&timer);

    ledc_channel_config_t channel =
    {
        .gpio_num = BUZZER_GPIO,
        .speed_mode = BUZZER_MODE,
        .channel = BUZZER_CHANNEL,
        .timer_sel = BUZZER_TIMER,
        .duty = 0,
        .hpoint = 0
    };
    ledc_channel_config(&channel);
    return;
}

void buzzer_play_note(uint16_t frequency_hz,
                      uint16_t duration_ms)
{
    ledc_set_freq(BUZZER_MODE,
                  BUZZER_TIMER,
                  frequency_hz);
    ledc_set_duty(BUZZER_MODE,
                  BUZZER_CHANNEL,
                  BUZZER_DUTY);
    ledc_update_duty(BUZZER_MODE,
                     BUZZER_CHANNEL);
    vTaskDelay(pdMS_TO_TICKS(duration_ms));
    buzzer_stop();
    return;
}

void buzzer_stop(void)
{
    ledc_set_duty(BUZZER_MODE,
                  BUZZER_CHANNEL,
                  0);
    ledc_update_duty(BUZZER_MODE,
                     BUZZER_CHANNEL);
    return;
}

void buzzer_play_melody(BuzzerMelody melody)
{
    switch(melody)
    {
        case BUZZER_MELODY_BUTTON_BLUE:
        {
            play_sequence(BUTTON_BLUE_MELODY,
                          sizeof(BUTTON_BLUE_MELODY)/sizeof(BuzzerNote));
            break;
        }

        case BUZZER_MELODY_BUTTON_GREEN:
        {
            play_sequence(BUTTON_GREEN_MELODY,
                          sizeof(BUTTON_GREEN_MELODY)/sizeof(BuzzerNote));
            break;
        }

        case BUZZER_MELODY_BUTTON_YELLOW:
        {
            play_sequence(BUTTON_YELLOW_MELODY,
                          sizeof(BUTTON_YELLOW_MELODY)/sizeof(BuzzerNote));
            break;
        }

        case BUZZER_MELODY_BUTTON_RED:
        {
            play_sequence(BUTTON_RED_MELODY,
                          sizeof(BUTTON_RED_MELODY)/sizeof(BuzzerNote));
            break;
        }

        case BUZZER_MELODY_BEEP:
        {
            play_sequence(BEEP_MELODY,
                          sizeof(BEEP_MELODY)/sizeof(BuzzerNote));
            break;
        }

        case BUZZER_MELODY_SUCCESSFUL_SEQUENCE:
        {
            play_sequence(SUCCESSFUL_SEQUENCE_MELODY,
                          sizeof(SUCCESSFUL_SEQUENCE_MELODY)/sizeof(BuzzerNote));
            break;
        }

        case BUZZER_MELODY_VICTORY:
        {
            play_sequence(VICTORY_MELODY,
                          sizeof(VICTORY_MELODY)/sizeof(BuzzerNote));
            break;
        }

        case BUZZER_MELODY_GAME_OVER:
        {
            play_sequence(GAME_OVER_MELODY,
                          sizeof(GAME_OVER_MELODY)/sizeof(BuzzerNote));
            break;
        }
    }
    return;
}