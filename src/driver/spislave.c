#include <avr/interrupt.h>
#include <avr/io.h>

#define SPI_DDRX     DDRB
#define SPI_BIT_MISO (1 << PB6)

void spi_init(void)
{

	SPI_DDRX |= SPI_BIT_MISO; // MISO as output
	SPCR |= (1 << SPE);       // enable SPI
}

uint8_t spi_transceive(uint8_t data)
{

	SPDR = data;

	while (!(SPSR & (1 << SPIF))) {
		// Wait for reception complete
	}

	return SPDR;
}

//// SPI Transmission/reception complete ISR
// ISR(SPI_STC_vect)
//{
//	// Code to execute
//	// whenever transmission/reception
//	// is complete.
//}
