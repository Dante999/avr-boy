#include "spimaster.hpp"

#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>

#define SPI_DDRX     DDRB
#define SPI_PORTX    PORTB
#define SPI_BIT_MOSI (1 << PB3)
#define SPI_BIT_MISO (1 << PB4)
#define SPI_BIT_SCK  (1 << PB5)
#define SPI_BIT_SS   (1 << PB2)

// valid values: 2, 4, 8, 16, 32, 64, 128
#define SPI_CLK_RATE 2

static void spi_delay(void)
{
	_delay_ms(100);
}

void SPI::enable_slave(void)
{
	SPI_PORTX &= ~SPI_BIT_SS;
}

void SPI::disable_slave(void)
{
	SPI_PORTX |= SPI_BIT_SS;
}

void SPI::init_hw(void)
{

	SPI_DDRX |= SPI_BIT_MOSI | SPI_BIT_SCK | SPI_BIT_SS;

	SPDR = 0x00; // preset data register

	SPCR |= (1 << SPE) | (1 << MSTR);

#if SPI_CLK_RATE == 4
	// default
#elif SPI_CLK_RATE == 16
	SPCR |= (1 << SPR0);
#elif SPI_CLK_RATE == 64
	SPCR |= (1 << SPR1);
#elif SPI_CLK_RATE == 128
	SPCR |= (1 << SPR1) | (1 << SPR0);
#elif SPI_CLK_RATE == 2
	SPCR |= (1 << SPI2X);
#elif SPI_CLK_RATE == 8
	SPCR |= (1 << SPI2X) | (1 << SPR0);
#elif SPI_CLK_RATE == 32
	SPCR |= (1 << SPI2X) | (1 << SPR1);
#elif SPI_CLK_RATE == 64
	SPCR |= (1 << SPI2X) | (1 << SPR1) | (1 << SPR1);

#endif

	SPI::disable_slave();
	spi_delay();
	SPI::enable_slave();
}

uint8_t SPI::transceive(uint8_t data)
{

	SPDR = data;

	while (!(SPSR & (1 << SPIF))) {
		// Wait for reception complete
	}

	return SPDR;
}
