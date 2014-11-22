

#include "quad_motor.h"

// Initializes the PWM's for the motors, sets the upper and lower bounds, and 
// starts a default PWM signal.
void quad_motors_init() {

	motor_min_pulse_ticks = (1000 * MIN_PULSE_WIDTH_us) / 
							(pwm1_tick_len_ns) + 1;
				 	  
	motor_max_pulse_ticks = (1000 * MAX_PULSE_WIDTH_us) / 
							(pwm1_tick_len_ns) - 1;
	
	
	// Set the initial pulse widths to be the minimum pulse width.
	PWMPulseWidthSet(PWM1_BASE, PWM_OUT_0, motor_min_pulse_ticks); // motor 1
	PWMPulseWidthSet(PWM1_BASE, PWM_OUT_1, motor_min_pulse_ticks); // motor 2
	PWMPulseWidthSet(PWM1_BASE, PWM_OUT_2, motor_min_pulse_ticks); // motor 3
	PWMPulseWidthSet(PWM1_BASE, PWM_OUT_3, motor_min_pulse_ticks); // motor 4
	
}



// This should run through the calibration routine as soon as the quad is 
// powered on.  There should be a slight delay so that the "operator" can 
// get their hands away :P.

// Unfortunately, the ESC's were designed to be calibrated with direct human
// contact, and not by a machine.  Thus, we must use timers to make sure we
// are in the proper step of the calibration process.  
// 
// We could probably do this with 
void quad_motors_calibrate() {
	
}




void quad_motors_set_value(int motor, int value) {
	// Cap our values.
	if (value < 0) {
		value = 0;
	} else if (value >= MAX_MOTOR_VALUE) {
		value = MAX_MOTOR_VALUE;
	}

	uint32_t set_ticks = quad_motors_calculate_num_ticks(value);

	switch(motor) {
		case MOTOR_1:
			PWMPulseWidthSet(PWM1_BASE, PWM_OUT_0, set_ticks); // motor 1
			motor_1.prev_val = value;
			break;
		case MOTOR_2:
			PWMPulseWidthSet(PWM1_BASE, PWM_OUT_1, set_ticks); // motor 2
			motor_2.prev_val = value;
			break;
		case MOTOR_3:
			PWMPulseWidthSet(PWM1_BASE, PWM_OUT_2, set_ticks); // motor 3
			motor_3.prev_val = value;
			break;
		case MOTOR_4:
			PWMPulseWidthSet(PWM1_BASE, PWM_OUT_3, set_ticks); // motor 4
			motor_4.prev_val = value;
			break;
	}
}



int quad_motors_get_last_val(int motor) {
	switch(motor) {
		case MOTOR_1:
			return motor_1.prev_val;
			break;
		case MOTOR_2:
			return motor_2.prev_val;
			break;
		case MOTOR_3:
			return motor_3.prev_val;
			break;
		case MOTOR_4:
			return motor_4.prev_val;
			break;
	}
	return -1;
}


// quad_motors_calculate_num_ticks() calculates the desired pulse width in ticks based on
// the value provided, the MAX_MOTOR_VALUE, and the motor_min_pulse_ticks and
// motor_max_pulse_ticks values.
// 
// The routine does use a rudimentary form of rounding. Note that this rounding
// is still not perfect as it will be off if MAX_MOTOR_VALUE is an odd number.  This
// is easily mitigated by setting MAX_MOTOR_VALUE to be an even number.
uint32_t quad_motors_calculate_num_ticks(uint32_t value) {
	// We are assuming that value has already been truncated to be in the range
	// [0, MAX_MOTOR_VALUE].  Bad things could happen otherwise!
	
	uint32_t return_ticks;
	uint32_t div_remaining;
	uint32_t pulse_range_ticks = motor_max_pulse_ticks - motor_min_pulse_ticks;
	
	return_ticks = (pulse_range_ticks * value) / MAX_MOTOR_VALUE;
	div_remaining = (pulse_range_ticks * value) % MAX_MOTOR_VALUE;
	
	if (div_remaining >= MAX_MOTOR_VALUE / 2) {
		return_ticks++;
	}
	
	return_ticks += motor_min_pulse_ticks;
	return return_ticks;
}


