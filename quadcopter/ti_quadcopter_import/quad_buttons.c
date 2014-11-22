

#include "quad_buttons.h"


void quad_buttons_init() {
	// Configure the Right and Left Buttons
	HWREG(GPIO_PORTF_BASE + GPIO_O_LOCK) = GPIO_LOCK_KEY;
	HWREG(GPIO_PORTF_BASE + GPIO_O_CR) |= 0x01;
	HWREG(GPIO_PORTF_BASE + GPIO_O_LOCK) = 0;
	GPIODirModeSet(GPIO_PORTF_BASE, GPIO_PIN_4|GPIO_PIN_0, GPIO_DIR_MODE_IN);
	GPIOPadConfigSet(GPIO_PORTF_BASE, GPIO_PIN_4|GPIO_PIN_0, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);

	// Configure the E Stop Button (at least I believe it is the E-Stop :P )
	//HWREG(GPIO_PORTE_BASE + GPIO_O_LOCK) = GPIO_LOCK_KEY;
	//HWREG(GPIO_PORTE_BASE + GPIO_O_CR) |= 0x01;
	//HWREG(GPIO_PORTE_BASE + GPIO_O_LOCK) = 0;
	//GPIODirModeSet(GPIO_PORTE_BASE, GPIO_PIN_3, GPIO_DIR_MODE_IN);
	//GPIOPadConfigSet(GPIO_PORTE_BASE, GPIO_PIN_3, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);
	
}


// Currently button presses don't use a "state", though will eventually be 
// configured to.  This state will essentially change what a particular button
// press, or combination of button presses does.  For example, if we are in the
// calibration state, we want the buttons to set max and min values to the speed
// controllers. 
// 
// A button_event happens whenever a button is pressed and released.  Note that
// holding down a button will not trigger multiple events (at this time anyway,
// support for this may be added later).
void quad_buttons_handle_button_events(int button_events) {
	// We should handle the E-stop case separately, and immediately.
	if ((button_events & E_STOP_BUTTON) == E_STOP_BUTTON) {
		quad_motors_set_value(MOTOR_1, 0);
		quad_motors_set_value(MOTOR_2, 0);
		quad_motors_set_value(MOTOR_3, 0);
		quad_motors_set_value(MOTOR_4, 0);
		return;
	}
	
	// For the previous values, the quad_motors_set_value() function will
	// automatically cap the values at 
	int motor_1_prev = quad_motors_get_last_val(MOTOR_1);
	int motor_2_prev = quad_motors_get_last_val(MOTOR_2);
	int motor_3_prev = quad_motors_get_last_val(MOTOR_3);
	int motor_4_prev = quad_motors_get_last_val(MOTOR_4);
	
	switch (button_events) {
		case RIGHT_BUTTON:
		
			quad_rgb_led_set_color(RED);
			
			// set max value / Increase Amount
			quad_motors_set_value(MOTOR_1, motor_1_prev + 1);
			quad_motors_set_value(MOTOR_2, motor_2_prev + 1);
			quad_motors_set_value(MOTOR_3, motor_3_prev + 1);
			quad_motors_set_value(MOTOR_4, motor_4_prev + 1);
			break;
		case LEFT_BUTTON:
		
			quad_rgb_led_set_color(BLUE);
			
			// set min value / Decrease Amount
			quad_motors_set_value(MOTOR_1, motor_1_prev - 1);
			quad_motors_set_value(MOTOR_2, motor_2_prev - 1);
			quad_motors_set_value(MOTOR_3, motor_3_prev - 1);
			quad_motors_set_value(MOTOR_4, motor_4_prev - 1);
			break;
		case (RIGHT_BUTTON | LEFT_BUTTON):
			// Toggle between max and min values:
			
			// We are not at MAX_VALUE for all motors
			if (motor_1_prev != MAX_MOTOR_VALUE || motor_2_prev != MAX_MOTOR_VALUE ||
				motor_3_prev != MAX_MOTOR_VALUE || motor_4_prev != MAX_MOTOR_VALUE) {	
				
				quad_rgb_led_set_color(WHITE);
				
				quad_motors_set_value(MOTOR_1, MAX_MOTOR_VALUE);
				quad_motors_set_value(MOTOR_2, MAX_MOTOR_VALUE);
				quad_motors_set_value(MOTOR_3, MAX_MOTOR_VALUE);
				quad_motors_set_value(MOTOR_4, MAX_MOTOR_VALUE);
				
			// We are at MAX_VALUE for all motors
			} else {				
			
				quad_rgb_led_set_color(OFF);		
				
				quad_motors_set_value(MOTOR_1, 0);
				quad_motors_set_value(MOTOR_2, 0);
				quad_motors_set_value(MOTOR_3, 0);
				quad_motors_set_value(MOTOR_4, 0);
			}

			break;
		default:
			break;		
	}
}

int quad_buttons_get_button_events() {

	int button_events = 0;
	
	// Right button pressed or released
	if (GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_0) == 0x00) {
		right_button.pressed = true;
		right_button.released = false;
	} else {
		right_button.released = true;;
	}
	
	
	
	// Left button pressed or released
	if (GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_4) == 0x00) {
		left_button.pressed = true;
		left_button.released = false;
	} else {
		left_button.released = true;
	}
	
	
	
	// Check if both buttons are pressed, and neither is released.  Checking 
	// that neither is released is necessary because we only mark a button press
	// as false when both buttons have been released.  Okay...I spent way too
	// long figuring out why this wasn't working the way I wanted :P
	if ((left_button.pressed && right_button.pressed) && 
		(!right_button.released && !left_button.released)) {
		
		left_and_right_button.pressed = true;
	}
	
	
	// Set the events based on press and release combinations.
	if (left_and_right_button.pressed && (left_button.released || right_button.released)) {
		button_events |= LEFT_BUTTON | RIGHT_BUTTON;
		left_and_right_button.pressed = false;
	}
	
	if (right_button.pressed && right_button.released && !left_button.pressed) {
		button_events |= RIGHT_BUTTON;
		right_button.pressed = false;
	}
	
	if (left_button.pressed && left_button.released && !right_button.pressed) {
		button_events |= LEFT_BUTTON;
		left_button.pressed = false;
	}
	
	
	
	// Once both buttons have been released, then we can mark the button_pressed
	// variable as false.  
	if (left_button.released && right_button.released) {
		left_button.pressed = false;
		right_button.pressed = false;
	}
	
	return button_events;
}



