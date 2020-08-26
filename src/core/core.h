#ifndef CORE_H
#define CORE_H

#include <stdbool.h>
#include <stdint.h>

#define CORE_PIXEL_OFF    0
#define CORE_PIXEL_ON     1
#define CORE_PIXEL_TOGGLE 2

#define CORE_TEXT_MAX_SIZE    20
#define CORE_SPRITE_MAX_SIZE  8
#define CORE_SPRITE_MAX_INDEX 5

typedef enum {
	BUTTON_UP,
	BUTTON_DOWN,
	BUTTON_LEFT,
	BUTTON_RIGHT,
	BUTTON_A,
	BUTTON_B,
	BUTTON_START,
	BUTTON_SELECT,
	BUTTON_CONFIG
} c_buttonid_t;

typedef struct {
	uint8_t reg0;
	uint8_t reg1;
} c_buttonstat_t;

typedef struct {
	uint8_t x;
	uint8_t y;
} c_coord_t;

typedef struct {
	c_coord_t coord;
	uint8_t   color;
} c_pixel_t;

typedef struct {
	c_coord_t coord;
	char      text[20];
} c_text_t;

typedef struct {
	uint8_t   index;
	bool      show;
	c_coord_t coord;
	uint8_t   data[CORE_SPRITE_MAX_SIZE];
} c_sprite_t;

bool core_button_get(c_buttonstat_t *stat, c_buttonid_t id);
void core_button_set(c_buttonstat_t *stat, c_buttonid_t id);
void core_button_clear(c_buttonstat_t *stat);

#endif /* PERIPHERALS_H */
