#ifndef BUZZER_H
#define BUZZER_H

#include <stdint.h>

typedef struct
{
    uint16_t frequency_hz;
    uint16_t duration_ms;

} BuzzerNote;

typedef enum
{
    BUZZER_MELODY_BUTTON_BLUE = 0,
    BUZZER_MELODY_BUTTON_GREEN,
    BUZZER_MELODY_BUTTON_YELLOW,
    BUZZER_MELODY_BUTTON_RED,
    BUZZER_MELODY_BEEP,
    BUZZER_MELODY_SUCCESSFUL_SEQUENCE,
    BUZZER_MELODY_VICTORY,
    BUZZER_MELODY_GAME_OVER
} BuzzerMelody;

void buzzer_init(void);
void buzzer_stop(void);
void buzzer_play_note(uint16_t frequency_hz,
                      uint16_t duration_ms);
void buzzer_play_melody(BuzzerMelody melody);

#endif