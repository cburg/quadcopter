

#ifndef QUAD_PERIPHERALS_H
#define QUAD_PERIPHERALS_H

#include "quad_common.h"
#include "driverlibg/uart.h"
#include "inc/hw_uart.h"

#include "driverlibg/pwm.h"
#include "inc/hw_pwm.h"

#include "driverlibg/i2c.h"
#include "inc/hw_i2c.h"

void quad_periph_init_pwm();
void quad_periph_init_uart();
void quad_periph_init_i2c();


#endif //QUAD_PERIPHERALS_H