#ifndef AVRBOY_HANDHELD_H
#define AVRBOY_HANDHELD_H

#include "protocol.h"

void handheld_wait_for_actions(void);
void handheld_init(protocol_callback_transmit cb_transmit,
                   protocol_callback_receive  cb_receive);
#endif /* AVRBOY_HANDHELD_H */
