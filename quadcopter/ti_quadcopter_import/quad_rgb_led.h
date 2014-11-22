

#ifndef QUAD_RGB_LED_H
#define QUAD_RGB_LED_H

#include "quad_common.h"
#include "quad_pwm.h"

#define PWM_RGB_PERIOD_us	20000
#define RGB_TIME_RES_Hz		1000000

#define MIN_RGB_VALUE		0
#define MAX_RGB_VALUE		255

uint32_t rgb_period_num_ticks;

enum Colors {
	RED,
	GREEN,
	BLUE,
	YELLOW,		// red + green
	CYAN,		// green + blue
	MAGENTA,	// red + blue
	WHITE,
	OFF
};


void quad_rgb_led_init();
void quad_rgb_led_set_color(int color);
void quad_rgb_led_set_color_values(uint8_t red, uint8_t green, uint8_t blue);
uint32_t quad_rgb_calculate_num_ticks(uint32_t value);

#endif //QUAD_RGB_LED_H
