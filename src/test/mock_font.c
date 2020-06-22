#include "../display/font.h"

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
