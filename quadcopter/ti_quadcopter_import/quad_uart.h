


#ifndef QUAD_UART_H
#define QUAD_UART_H

#include "quad_common.h"
#include "driverlib/uart.h"
#include "inc/hw_uart.h"
#include "quad_rgb_led.h"

void quad_uart_init();

void quad_uart_send_string(uint8_t *char_str, int len);

#endif //QUAD_UART_H