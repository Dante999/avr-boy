#ifndef USERPORT_H
#define USERPORT_H

#include <stdio.h>

#define USERPORT_LOW    0
#define USERPORT_HIGH   1
#define USERPORT_TOGGLE 2

void userport_init(void);
void userport_11(uint8_t stat);
void userport_12(uint8_t stat);

#endif /* USERPORT_H */
