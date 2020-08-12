#include "../protocol/cartridge.h"
#include "../protocol/protocol.h"
#include "mock_transceiver.h"
#include "unity.h"

void test_cartridge_draw_text(void)
{
	mock_transceiver_reset();

	struct protocol_package t_package;

	t_package.cmd    = PRTCL_CMD_ACK;
	t_package.length = 0;

	mock_transceiver_prepare_response(&t_package);

	cartridge_draw_text(7, 11, "ABCDE");

	char *tb = mock_transceiver_transmitbuffer();

	TEST_ASSERT_EQUAL(PRTCL_START_BYTE, tb[0]);
	TEST_ASSERT_EQUAL(PRTCL_CMD_DRAW_TEXT, tb[1]);
	TEST_ASSERT_EQUAL(sizeof(c_text_t), tb[2]);
	TEST_ASSERT_EQUAL(7, tb[3]);
	TEST_ASSERT_EQUAL(11, tb[4]);
	TEST_ASSERT_EQUAL('A', tb[5]);
	TEST_ASSERT_EQUAL('B', tb[6]);
	TEST_ASSERT_EQUAL('C', tb[7]);
	TEST_ASSERT_EQUAL('D', tb[8]);
	TEST_ASSERT_EQUAL('E', tb[9]);
	TEST_ASSERT_EQUAL('\0', tb[10]);
}

void test_cartridge_run(void)
{
	RUN_TEST(test_cartridge_draw_text);
}