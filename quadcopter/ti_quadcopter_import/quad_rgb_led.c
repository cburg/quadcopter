

#include "quad_common.h"
#include "quad_rgb_led.h"


void quad_rgb_led_init() {
	rgb_period_num_ticks = pwm1_period_num_ticks;
	quad_rgb_led_set_color(MAGENTA);
}


void quad_rgb_led_set_color(int color) {
	//									  r   g   b
	switch(color) {
		case RED:
			quad_rgb_led_set_color_values(255, 0, 0);
			break;
		case GREEN:
			quad_rgb_led_set_color_values(0, 255, 0);
			break;
		case BLUE:
			quad_rgb_led_set_color_values(0, 0, 255);
			break;
		case YELLOW:
			quad_rgb_led_set_color_values(255, 255, 0);
			break;
		case CYAN:
			break;
		case MAGENTA:
			quad_rgb_led_set_color_values(255, 0, 255);
			break;
		case WHITE:
			quad_rgb_led_set_color_values(255, 255, 255);
			break;
		case OFF:
			quad_rgb_led_set_color_values(0, 0, 0);
			break;
		default:
			quad_rgb_led_set_color_values(0, 0, 0);
			break;
	}
}


void quad_rgb_led_set_color_values(uint8_t red, uint8_t green, uint8_t blue) {
	uint32_t red_ticks = quad_rgb_calculate_num_ticks(red);
	uint32_t blue_ticks = quad_rgb_calculate_num_ticks(blue);
	uint32_t green_ticks = quad_rgb_calculate_num_ticks(green);
	
	PWMPulseWidthSet(PWM1_BASE, PWM_OUT_5, red_ticks);
	PWMPulseWidthSet(PWM1_BASE, PWM_OUT_6, blue_ticks);
	PWMPulseWidthSet(PWM1_BASE, PWM_OUT_7, green_ticks);
}


// 
uint32_t quad_rgb_calculate_num_ticks(uint32_t value) {
	
	uint32_t return_ticks;
	uint32_t div_remaining;
	
	return_ticks = (rgb_period_num_ticks * value) / MAX_RGB_VALUE;
	div_remaining = (rgb_period_num_ticks * value) % MAX_RGB_VALUE;
	
	if (div_remaining > MAX_RGB_VALUE / 2) {
		return_ticks++;
	}
	
	if (return_ticks == 0) {
		return_ticks++; // a PWM value of 0 will be constantly on...
	} else if (return_ticks == rgb_period_num_ticks) {
		return_ticks--;
	}
	
	return return_ticks;
}
