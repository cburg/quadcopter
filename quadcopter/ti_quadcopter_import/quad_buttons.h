

// TODO: Implement anti-bouncing code.
// TODO: Implement button holding code.

#ifndef QUAD_BUTTONS_H
#define QUAD_BUTTONS_H

#include "quad_common.h"
#include "quad_rgb_led.h"
#include "quad_motor.h"

#define BOUNCE_THRESHOLD_ms	20
#define HOLD_THRESHOLD_ms	500
#define REPEATE_RATE_ms		100 // 100 milliseconds = 10 events / second

// We want the buttons to be "OR"-able so we can detect multiple button presses
// simultaneously.
enum Buttons {
	LEFT_BUTTON = 1,
	RIGHT_BUTTON = 2,
	E_STOP_BUTTON = 4
};

typedef struct Button_ {
	bool pressed;
	bool released;
	bool holding;
	uint32_t last_change_ms; // time since pressed or released last changed
} Button;


Button left_button;
Button right_button;
Button left_and_right_button;
Button e_stop_button;


// Initializes the Buttons
void quad_buttons_init();

// Handles all button events.  A button event is defined as when a button is 
// pressed and released.  While it is not currently implemented, holding a
// button down could be used to generate button events in quick succession. 
void quad_buttons_handle_button_events(int button_events);

// Checks each of the buttons to see whether they have been pressed / released
// and generates a button event for each one accordingly.  
int quad_buttons_get_button_events();

#endif //QUAD_BUTTONS_H
