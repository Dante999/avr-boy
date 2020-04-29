#ifndef PCF8574_H
#define PCF8574_H

#include <avr/io.h>

void    pcf8574_init(void);
void    pcf8574_set(uint8_t byte);
uint8_t pcf8574_get(void);
#endif // PCF8574_H
