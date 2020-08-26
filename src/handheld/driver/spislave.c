#include <avr/io.h>

#define SPI_DDRX     DDRB
#define SPI_PORTX    PORTB
#define SPI_PINX     PINB
#define SPI_BIT_SS   (1 << PB4)
#define SPI_BIT_MOSI (1 << PB5)
#define SPI_BIT_MISO (1 << PB6)
#define SPI_BIT_SCK  (1 << PB7)

void spi_init(void)
{
	// set as output(s)
	SPI_DDRX |= SPI_BIT_MISO;

	// set as input(s)
	SPI_DDRX &= ~(SPI_BIT_SS | SPI_BIT_MOSI | SPI_BIT_SCK);

	// enable SPI
	SPCR |= (1 << SPE);
}

uint8_t spi_transceive(uint8_t data)
{
	SPDR = data;

	while (!(SPSR & (1 << SPIF))) {
		// Wait for reception complete
	}

	return SPDR;
}
