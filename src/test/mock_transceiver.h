#ifndef MOCK_TRANSCEIVER_H
#define MOCK_TRANSCEIVER_H

#include <stdint.h>

#include "../protocol/protocol.h"

#define MOCK_BUFFER_SIZE 255

char *  mock_transceiver_receivebuffer(void);
void    mock_transceiver_reset(void);
char *  mock_transceiver_transmitbuffer(void);
uint8_t mock_transceiver_transmitindex(void);
uint8_t mock_transceiver_receiveindex(void);
void    mock_transceiver_prepare_response(struct protocol_package *p);
#endif /* MOCK_TRANSCEIVER_H */
