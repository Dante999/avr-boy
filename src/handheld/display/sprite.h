#ifndef SPRITE_H
#define SPRITE_H

#include <stdbool.h>
#include <stdio.h>

#include "core/core.h"

#define SPRITE_MAX_INDEX CORE_SPRITE_MAX_INDEX
#define SPRITE_MAX_DATA  CORE_SPRITE_MAX_SIZE

typedef struct {
	bool    show;
	uint8_t x;
	uint8_t y;
	uint8_t fgdata[SPRITE_MAX_DATA];
	uint8_t bgdata[SPRITE_MAX_DATA];
} sprite_t;

void sprite_init(void);
void sprite_set_coord(uint8_t index, uint8_t x, uint8_t y);
void sprite_set_fgdata(uint8_t index, const uint8_t *data);
void sprite_set_bgdata(uint8_t index, const uint8_t *data);
void sprite_set_show(uint8_t index, bool show);

const sprite_t *sprite_get(uint8_t index);

#endif /* SPRITE_H */
