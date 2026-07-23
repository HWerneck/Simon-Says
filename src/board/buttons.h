#ifndef BUTTONS_H
#define BUTTONS_H

#include <stdbool.h>
#include "common/colour.h"

void buttons_init(void);
bool get_button_down(Colour *colour);

#endif