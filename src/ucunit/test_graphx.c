#include "system.h"
#include "testsuite.h"
#include "uCUnit-v1.0.h"

#include "../graphx.h"

#include <stdio.h>

char *print_coordinates(uint8_t x, uint8_t y)
{
	static char buffer[20] = {0x00};
	sprintf(buffer, "x=%3d y=%3d", x, y);

	return buffer;
}

static void test_draw_pixel(void)
{
	UCUNIT_TestcaseBegin("graphx.c : draw pixel");

	graphx_init();

	for (uint8_t x = 0; x < GRAPHX_WIDTH; x++) {

		for (uint8_t y = 0; y < GRAPHX_HEIGHT; y++) {

			graphx_draw_pixel(x, y, PIXEL_ON);

			UCUNIT_Check(graphx_get_pixel(x, y) == 1,
				     "graphx_get_pixel(...) == 1",
				     print_coordinates(x, y));
		}
	}

	for (uint8_t x = 0; x < GRAPHX_WIDTH; x++) {

		for (uint8_t y = 0; y < GRAPHX_HEIGHT; y++) {

			graphx_draw_pixel(x, y, PIXEL_OFF);

			UCUNIT_Check(graphx_get_pixel(x, y) == 0,
				     "graphx_get_pixel(...) == 0",
				     print_coordinates(x, y));
		}
	}

	UCUNIT_TestcaseEnd();
}

static void test_draw_hline(void)
{

	UCUNIT_TestcaseBegin("graphx.c : draw hline");

	graphx_init();

	uint8_t x_start = 0;
	uint8_t x_end   = 10;
	uint8_t y       = 20;

	graphx_draw_hline(x_start, x_end, y, PIXEL_ON);

	for (uint8_t i = x_start; i <= x_end; i++) {
		UCUNIT_CheckIsEqual(graphx_get_pixel(i, y), 1);
	}

	UCUNIT_TestcaseEnd();
}

static void test_draw_vline(void)
{
	UCUNIT_TestcaseBegin("graphx.c : draw vline");

	graphx_init();

	uint8_t y_start = 0;
	uint8_t y_end   = 10;
	uint8_t x       = 20;

	graphx_draw_vline(x, y_start, y_end, PIXEL_ON);

	for (uint8_t i = y_start; i <= y_end; i++) {
		UCUNIT_CheckIsEqual(graphx_get_pixel(x, i), 1);
	}

	UCUNIT_TestcaseEnd();
}

static void test_draw_tile_4x16(void)
{
	UCUNIT_TestcaseBegin("graphx.c : draw tile 4x16");

	graphx_init();

	const uint8_t width  = 4;
	const uint8_t height = 16;
	const uint8_t tile[] = {0xFF, 0x01, 0x01, 0xFF, 0xFF, 0x80, 0x80, 0xFF};

	graphx_draw_tile(0, 0, tile, width, height);

	for (uint8_t i = 0; i < width; i++) {
		UCUNIT_CheckIsEqual(graphx_get_pixel(i, 0), 1);
		UCUNIT_CheckIsEqual(graphx_get_pixel(i, height - 1), 1);
	}

	for (uint8_t i = 0; i < height; i++) {
		UCUNIT_CheckIsEqual(graphx_get_pixel(0, i), 1);
		UCUNIT_CheckIsEqual(graphx_get_pixel(width - 1, i), 1);
	}

	UCUNIT_TestcaseEnd();
}

static void test_draw_tile_1x64(void)
{
	UCUNIT_TestcaseBegin("graphx.c : draw tile 1x64");

	graphx_init();

	const uint8_t width  = 1;
	const uint8_t height = 64;
	const uint8_t tile[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

	graphx_draw_tile(0, 0, tile, width, height);

	for (uint8_t i = 0; i < height; i++) {
		UCUNIT_CheckIsEqual(graphx_get_pixel(0, i), 1);
	}

	UCUNIT_TestcaseEnd();
}

static void test_draw_tile_128x8(void)
{
	UCUNIT_TestcaseBegin("graphx.c : draw tile 8x128");

	graphx_init();

	const uint8_t width  = 128;
	const uint8_t height = 8;
	const uint8_t tile[] = {
	    0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
	    0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
	    0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
	    0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
	    0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
	    0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
	    0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
	    0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
	    0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
	    0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
	    0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
	    0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01};

	graphx_draw_tile(0, 0, tile, width, height);

	for (uint8_t i = 0; i < width; i++) {
		UCUNIT_CheckIsEqual(graphx_get_pixel(i, 0), 1);
	}

	UCUNIT_TestcaseEnd();
}

static void test_draw_tile_128x64(void)
{

	UCUNIT_TestcaseBegin("graphx.c : draw tile 128x64");

	graphx_init();

	const uint8_t width  = 128;
	const uint8_t height = 64;

	const uint8_t tile[] = {
	    0xff, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
	    0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
	    0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
	    0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
	    0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
	    0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
	    0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
	    0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
	    0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
	    0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
	    0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
	    0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0xff, 0xff, 0x00, 0x00, 0x00,
	    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	    0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x60, 0x1c, 0x07, 0x07, 0x7c,
	    0xc0, 0x00, 0x00, 0x03, 0x3e, 0xe0, 0x00, 0x00, 0xe0, 0x3e, 0x01,
	    0x00, 0x00, 0xff, 0x41, 0x41, 0x41, 0xc1, 0x22, 0x1c, 0x00, 0x00,
	    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff,
	    0x21, 0x21, 0x21, 0x21, 0x52, 0x8c, 0x00, 0x00, 0xf8, 0x06, 0x01,
	    0x01, 0x01, 0x01, 0x06, 0xf8, 0x00, 0x00, 0x03, 0x0c, 0x30, 0xc0,
	    0x30, 0x0c, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	    0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20,
	    0x2c, 0x2f, 0x21, 0x21, 0x21, 0x21, 0x21, 0x2f, 0x2c, 0x20, 0x20,
	    0x20, 0x23, 0x2c, 0x2c, 0x23, 0x20, 0x20, 0x20, 0x20, 0x2f, 0x20,
	    0x20, 0x20, 0x21, 0x22, 0x2c, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
	    0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x2f, 0x28, 0x28, 0x28, 0x28,
	    0x24, 0x23, 0x20, 0x20, 0x21, 0x26, 0x28, 0x28, 0x28, 0x28, 0x26,
	    0x21, 0x20, 0x20, 0x20, 0x20, 0x20, 0x2f, 0x20, 0x20, 0x20, 0x20,
	    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff,
	    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfe, 0xff, 0x03, 0x03, 0x03,
	    0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x83, 0x83, 0x83, 0x03, 0x03,
	    0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03,
	    0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03,
	    0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03,
	    0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03,
	    0x03, 0x03, 0x03, 0x03, 0x03, 0xff, 0xfe, 0x00, 0x00, 0x00, 0x00,
	    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	    0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00,
	    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	    0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x38, 0x38,
	    0x38, 0x38, 0xff, 0xff, 0xff, 0x38, 0x38, 0x38, 0x38, 0x00, 0x00,
	    0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0xc0, 0xc0, 0xc0, 0x00, 0x00,
	    0x00, 0x00, 0x00, 0xc0, 0xc0, 0xc0, 0xc0, 0x00, 0x00, 0x00, 0x00,
	    0x00, 0x00, 0x30, 0x78, 0xfc, 0xfc, 0x78, 0x30, 0x00, 0x00, 0x00,
	    0x00, 0x00, 0x30, 0x78, 0xfc, 0xfc, 0x78, 0x30, 0x00, 0x00, 0x00,
	    0x00, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	    0x00, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff,
	    0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x83, 0x83,
	    0x83, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
	    0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
	    0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
	    0x80, 0x80, 0xbe, 0xaa, 0xb6, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
	    0xbc, 0x96, 0xbc, 0x80, 0x80, 0x80, 0x80, 0x80, 0xff, 0xff, 0x00,
	    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00,
	    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01,
	    0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
	    0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
	    0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
	    0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
	    0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
	    0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	    0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x80, 0x80, 0x80, 0x80, 0x80,
	    0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
	    0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
	    0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
	    0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
	    0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
	    0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
	    0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
	    0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
	    0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
	    0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
	    0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
	    0xff,
	};

	graphx_draw_tile(0, 0, tile, width, height);

	for (uint8_t i = 0; i < width; i++) {

		uint8_t x1 = i;
		uint8_t x2 = i;
		uint8_t y1 = 0;
		uint8_t y2 = height - 1;

		UCUNIT_Check(graphx_get_pixel(x1, y1) == 1,
			     "graphx_get_pixel(...) == 1",
			     print_coordinates(x1, y1));

		UCUNIT_Check(graphx_get_pixel(x2, y2) == 1,
			     "graphx_get_pixel(...) == 1",
			     print_coordinates(x2, y2));
	}

	for (uint8_t i = 0; i < height; i++) {

		uint8_t x1 = 0;
		uint8_t x2 = width - 1;
		uint8_t y1 = i;
		uint8_t y2 = i;

		UCUNIT_Check(graphx_get_pixel(x1, y1) == 1,
			     "graphx_get_pixel(...) == 1",
			     print_coordinates(x1, y1));

		UCUNIT_Check(graphx_get_pixel(x2, y2) == 1,
			     "graphx_get_pixel(...) == 1",
			     print_coordinates(x2, y2));
	}

	UCUNIT_TestcaseEnd();
}

void test_graphx_run(void)
{
	test_draw_pixel();
	test_draw_hline();
	test_draw_vline();
	test_draw_tile_4x16();
	test_draw_tile_1x64();
	test_draw_tile_128x8();
	test_draw_tile_128x64();

	UCUNIT_WriteSummary();
}
