#ifndef SPISLAVE_H
#define SPISLAVE_H

#include <stdint.h>

void    spi_init(void);
uint8_t spi_transceive(uint8_t data);

#endif // SPISLAVE_H
