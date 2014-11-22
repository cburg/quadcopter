

#ifndef QUAD_MOTOR_H
#define QUAD_MOTOR_H

#include "quad_common.h"
#include "quad_pwm.h"
#include "quad_rgb_led.h"
#include "driverlib/pwm.h"

// us == microseconds
// ms == milliseconds
// Hz == Hertz (Cycles per second)
#define MIN_PULSE_WIDTH_us	1000	// 0.7 ms ()
#define MAX_PULSE_WIDTH_us	2000	// 2.0 ms (2000)
#define PULSE_TIME_RES_Hz	1000000	// 1000000 Hz = 1 us / cycle

#define MIN_MOTOR_VALUE		0
#define MAX_MOTOR_VALUE		1000

volatile uint32_t motor_min_pulse_ticks;
volatile uint32_t motor_max_pulse_ticks;



// Enums and Structs
enum Motors {
	MOTOR_1,	// 
	MOTOR_2,	// 
	MOTOR_3,	// 
	MOTOR_4		// 
};

typedef struct Motor_s {
	int prev_val;
} Motor;


Motor motor_1;
Motor motor_2;
Motor motor_3;
Motor motor_4;



// Initializes the motors
void quad_motors_init();

// Calibration function for use with the ESC's on startup.  Used to avoid human
// control in an effort to make it more autonomous.
// Note: This function is not currently used as our ESC's calibration routine
// would not fit well with this.
void quad_motors_calibrate();

// 'value' in quad_motors_set_value() should be a value between 0 and 1000.  
// If a value greater than 1000 is passed, it will be truncated to 1000.
// 'motor' should be one of: MOTOR_1, MOTOR_2, MOTOR_3, or MOTOR_4.
void quad_motors_set_value(int motor, int value);

// Returns the last value set for the given motor.  'motor' should be one of:
// MOTOR_1, MOTOR_2, MOTOR_3, or MOTOR_4.
int quad_motors_get_last_val(int motor);

// helper function.  Calculates the number of ticks based on the min_pulse_ticks,
// max_pulse_ticks, and the value passed in to quad_motors_set_value().  The 
// number returned will be a rounded value, and not the result of integer
// division.  Note, the rounding is pretty rudimentary.
uint32_t quad_motors_calculate_num_ticks(uint32_t value);


#endif // QUAD_MOTOR_H
