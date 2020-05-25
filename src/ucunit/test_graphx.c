#include "system.h"
#include "testsuite.h"
#include "uCUnit-v1.0.h"

#include "../graphx.h"

#define GRAPHX_WIDTH  128
#define GRAPHX_HEIGHT 64

void test_draw_pixel(void)
{

	UCUNIT_TestcaseBegin("graphx.c : draw pixel");

	struct graphxdata *gd = graphx_new(GRAPHX_WIDTH, GRAPHX_HEIGHT);

	graphx_draw_pixel(gd, 0, 0, PIXEL_ON);
	UCUNIT_CheckIsEqual(graphx_get_pixel(gd, 0, 0), 1);

	graphx_draw_pixel(gd, 0, 0, PIXEL_OFF);
	UCUNIT_CheckIsEqual(graphx_get_pixel(gd, 0, 0), 0);

	graphx_draw_pixel(gd, 0, GRAPHX_HEIGHT, PIXEL_ON);
	UCUNIT_CheckIsEqual(graphx_get_pixel(gd, 0, GRAPHX_HEIGHT), 1);

	graphx_draw_pixel(gd, 0, GRAPHX_HEIGHT, PIXEL_OFF);
	UCUNIT_CheckIsEqual(graphx_get_pixel(gd, 0, GRAPHX_HEIGHT), 0);

	graphx_destroy(gd);

	UCUNIT_TestcaseEnd();
}

void test_draw_hline(void)
{
	uint8_t x_start = 0;
	uint8_t x_end   = 10;
	uint8_t y       = 20;

	UCUNIT_TestcaseBegin("graphx.c : draw hline");

	struct graphxdata *gd = graphx_new(GRAPHX_WIDTH, GRAPHX_HEIGHT);

	graphx_draw_hline(gd, x_start, x_end, y, PIXEL_ON);

	for (uint8_t i = x_start; i <= x_end; i++) {
		UCUNIT_CheckIsEqual(graphx_get_pixel(gd, i, y), 1);
	}
}

void test_draw_vline(void)
{
	uint8_t y_start = 0;
	uint8_t y_end   = 10;
	uint8_t x       = 20;

	UCUNIT_TestcaseBegin("graphx.c : draw hline");

	struct graphxdata *gd = graphx_new(GRAPHX_WIDTH, GRAPHX_HEIGHT);

	graphx_draw_vline(gd, x, y_start, y_end, PIXEL_ON);

	for (uint8_t i = y_start; i <= y_end; i++) {
		UCUNIT_CheckIsEqual(graphx_get_pixel(gd, x, i), 1);
	}
}

void test_graphx_run(void)
{
	test_draw_pixel();
	test_draw_hline();
	test_draw_vline();

	UCUNIT_WriteSummary();
}
