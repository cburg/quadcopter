

#ifndef QUAD_SYSTEM_TIME_H
#define QUAD_SYSTEM_TIME_H

#include "quad_common.h"
#include "driverlib/timer.h"
#include "driverlib/sysctl.h"
#include "driverlib/interrupt.h"

uint32_t time_seconds;
uint32_t time_micros;

void quad_system_time_init();

void quad_system_time_interrupt();

void get_time_elapsed(uint32_t sec_prev, uint32_t micros_prev, uint32_t sec_cur, uint32_t micros_cur, uint32_t *sec_elapsed, uint32_t *micros_elapsed);

uint32_t get_system_time_millis();
uint32_t get_system_time_micros();
uint32_t get_system_time_seconds();



#endif //QUAD_SYSTEM_TIME_H