#ifndef SIMON_SAYS_TYPES_H
#define SIMON_SAYS_TYPES_H

#include <stdint.h>
#include "common/colour.h"

#define SIMON_SAYS_MAX_SEQUENCE_LENGTH 100

typedef struct
{
    Colour sequence[SIMON_SAYS_MAX_SEQUENCE_LENGTH];
    uint8_t sequence_length;
    uint8_t player_position;
    uint8_t score;
} SimonGame;

#endif