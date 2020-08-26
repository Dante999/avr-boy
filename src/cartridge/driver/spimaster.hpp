#ifndef SPIMASTER_HPP
#define SPIMASTER_HPP

#include <stdint.h>

class SPI {

      public:
	SPI(void) = delete;
	static void    init_hw(void);
	static void    enable_slave(void);
	static void    disable_slave(void);
	static uint8_t transceive(uint8_t data);
};

#endif // SPIMASTER_HPP
