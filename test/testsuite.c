
#include "unity.h"

#include "test_cartridge.h"
#include "test_graphx.h"
#include "test_protocol.h"

void tearDown(void) {}
void setUp(void) {}

int main(void)
{
	UNITY_BEGIN();

	test_graphx_run();
	test_protocol_run();
	test_cartridge_run();

	return UNITY_END();
}
