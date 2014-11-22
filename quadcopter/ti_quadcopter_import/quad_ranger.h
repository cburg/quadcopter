#ifndef QUAD_RANGER_H
#define QUAD_RANGER_H

#include "quad_common.h"
#include "driverlib/timer.h"
#include "driverlib/sysctl.h"
#include "driverlib/interrupt.h"
#include "quad_serial.h"
#include "quad_system_time.h"
#include "quad_rgb_led.h"

uint32_t micros_start;
uint32_t seconds_start;
uint32_t micros_end;
uint32_t seconds_end;

uint32_t distance;

void quad_ranger_init();
uint32_t quad_ranger_get_last_distance();

#endif //QUAD_RANGER_H
