#ifndef INC_SERIAL_H_
#define INC_SERIAL_H_

#include "common-defines.h"

#define SERIAL_BUFFER_SIZE          256U

void serial_setup(void);
bool serial_data_available(void);

uint32_t serial_read(uint8_t *data, const uint32_t Len);
uint8_t serial_read_byte(uint8_t *data, const uint32_t Len);
void serial_send(uint8_t *data, const uint32_t Len);

#endif /* INC_SERIAL_H_ */