#include "display/font.h"

uint8_t font_pgm_width(const struct font *f)
{
	return f->width;
}
uint8_t font_pgm_height(const struct font *f)
{
	return f->height;
}

uint8_t font_pgm_byte(const struct font *f, uint16_t index)
{
	return f->data[index];
}

uint8_t font_width_P(const uint8_t *data)
{
	return data[0];
}

uint8_t font_height_P(const uint8_t *data)
{
	return data[1];
}

uint8_t font_byte_P(const uint8_t *data, uint16_t index)
{
	return data[index + 2];
}
