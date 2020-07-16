#ifndef CORE_H
#define CORE_H

#include <stdbool.h>
#include <stdint.h>

enum button_id {
	BUTTON_UP,
	BUTTON_DOWN,
	BUTTON_LEFT,
	BUTTON_RIGHT,
	BUTTON_A,
	BUTTON_B,
	BUTTON_START,
	BUTTON_SELECT,
	BUTTON_CONFIG
};

struct button_stat {
	uint8_t reg0;
	uint8_t reg1;
};

struct draw_text {
	uint8_t x;
	uint8_t y;

	char *text;
};

bool core_button_get(struct button_stat *stat, enum button_id id);
void core_button_set(struct button_stat *stat, enum button_id id);
void core_button_clear(struct button_stat *stat);

#endif /* PERIPHERALS_H */
