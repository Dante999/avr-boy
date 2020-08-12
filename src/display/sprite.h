#include <stdbool.h>
#include <stdio.h>

#include "../protocol/core.h"

#define SPRITE_MAX_INDEX CORE_SPRITE_MAX_INDEX
#define SPRITE_MAX_DATA  CORE_SPRITE_MAX_SIZE

typedef struct {
	bool    show;
	uint8_t x;
	uint8_t y;
	uint8_t data[SPRITE_MAX_DATA];
} sprite_t;

void sprite_set_coord(uint8_t index, uint8_t x, uint8_t y);
void sprite_set_data(uint8_t index, uint8_t *data);
void sprite_set_show(uint8_t index, bool show);

const sprite_t *sprite_get(uint8_t index);