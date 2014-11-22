

#ifndef QUAD_PWM_H
#define QUAD_PWM_H

#include "quad_common.h"
#include "inc/hw_pwm.h"
#include "driverlib/pwm.h"

//******************************************************************************
//
// Defines, Macros, Global Variables
//
//******************************************************************************
#define PWM0_PERIOD_us		20000	// 20000 microseconds = 50 Hz period
#define PWM1_PERIOD_us		20000	// 20000 microseconds = 50 Hz period
#define PWM0_TIME_RES_Hz	1000000	// 1 billionth of a second resolution
#define PWM1_TIME_RES_Hz	1000000 // 1 billionth of a second resolution

#define PWM1_PERIOD_Hz		50	// 50 Hz = 20 ms (standard servo / ESC period)
#define PWM0_PERIOD_Hz		50	// 50 Hz = 20 ms (standard servo / ESC period)

// These can be computed whenever and so are here purely for convenience.  Also,
// I doubt that they will really be needed or used, but here they are just in 
// case.
volatile uint32_t pwm0_period_num_ticks;
volatile uint32_t pwm0_period_len_us;
volatile uint32_t pwm0_clock_freq_hz;

volatile uint32_t pwm1_period_num_ticks;
volatile uint32_t pwm1_period_len_us;
volatile uint32_t pwm1_tick_len_ns;
volatile uint32_t pwm1_clock_freq_hz;
volatile uint32_t pwm1_period_hz;



//******************************************************************************
//
// Structs, Enums, etc.
//
//******************************************************************************



//******************************************************************************
//
// Functions
//
//******************************************************************************


void quad_pwm_init();


#endif //QUAD_PWM_H
