#ifndef BUZZER_H
#define BUZZER_H

#include <stdint.h>

void buzzer_init(void);

/*
 * Emite um tom.
 *
 * frequency_hz = frequência em Hertz
 * duration_ms  = duração em milissegundos
 */
void buzzer_beep(uint16_t frequency_hz, uint32_t duration_ms);
void buzzer_stop(void);

#endif