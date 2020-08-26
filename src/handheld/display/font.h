#ifndef FONT_H
#define FONT_H

#include <stdint.h>

struct font {
	const uint8_t  width;
	const uint8_t  height;
	const uint8_t *data;
};

uint8_t font_pgm_width(const struct font *f);
uint8_t font_pgm_height(const struct font *f);
uint8_t font_pgm_byte(const struct font *f, uint16_t index);

uint8_t font_width_P(const uint8_t *data);
uint8_t font_height_P(const uint8_t *data);
uint8_t font_byte_P(const uint8_t *data, uint16_t index);

#endif // FONT_H
