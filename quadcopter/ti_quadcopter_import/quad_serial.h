

#ifndef QUAD_SERIAL_H
#define QUAD_SERIAL_H

#include "quad_common.h"
#include "inc/hw_uart.h"
#include "driverlib/uart.h"


void quad_serial_init();
void serial_put_int(int val);
void serial_put_short(short val);
void serial_put_int_hex(int val);
void serial_put_float(float val);
void serial_put_char_hex(uint8_t val);
void serial_put_string(const char *string);


#endif //QUAD_SERIAL_H