#ifndef BUTTON_H
#define BUTTON_H

#include "core-buttons.h"
#include <avr/io.h>

void button_read(struct Button *button);
void button_init(void);
#endif // BUTTON_H
