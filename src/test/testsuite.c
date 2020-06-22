
#include "unity.h"

#include "test_graphx.h"
#include "test_protocol.h"

void tearDown(void) {}
void setUp(void) {}

void test_simple_basics(void)
{
	TEST_ASSERT_EQUAL_UINT8(5, 5);
}

int main(void)
{
	UNITY_BEGIN();

	test_graphx_run();
	test_protocol_run();

	return UNITY_END();
}
