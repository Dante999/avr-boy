#include "font.h"

#include <avr/pgmspace.h>

uint8_t font_pgm_width(const struct font *f)
{
	return pgm_read_byte(&f->width);
}

uint8_t font_pgm_height(const struct font *f)
{
	return pgm_read_byte(&f->height);
}

uint8_t font_pgm_byte(const struct font *f, uint16_t index)
{
	return pgm_read_byte(&(f->data[index]));
}

uint8_t font_width_P(const uint8_t *data)
{
	return pgm_read_byte(&data[0]);
}

uint8_t font_height_P(const uint8_t *data)
{
	return pgm_read_byte(&data[1]);
}

uint8_t font_byte_P(const uint8_t *data, uint16_t index)
{
	return pgm_read_byte(&data[index + 2]);
}
