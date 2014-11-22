
#include "quad_ranger.h"

void quad_ranger_init() {

	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
	GPIOPinTypeGPIOInput(GPIO_PORTB_BASE, GPIO_PIN_1);

	GPIOIntTypeSet(GPIO_PORTB_BASE, GPIO_PIN_1, GPIO_BOTH_EDGES); // set interupt to both edges

	IntEnable(INT_GPIOB);
	GPIOIntEnable(GPIO_PORTB_BASE, GPIO_PIN_1);
	quad_rgb_led_set_color(GREEN);
	
	IntMasterEnable();

	distance = 0;

}

void pinIntHandler(void)
{

	GPIOIntClear(GPIO_PORTB_BASE, GPIO_INT_PIN_1);

	// Get time of leading / rising edge
	if (GPIOPinRead(GPIO_PORTB_BASE,GPIO_PIN_1) == 0x02 /*&& timerValue == 0*/) {
		//TimerEnable(TIMER0_BASE, TIMER_A); // start counting
		micros_start = get_system_time_micros();
		seconds_start = get_system_time_seconds();
	}

	// Get time of trailing / falling edge, and calculate distance.
	if (GPIOPinRead(GPIO_PORTB_BASE,GPIO_PIN_1) == 0x00/* && timerValue != 0 */) {
		micros_end = get_system_time_micros();
		seconds_end = get_system_time_seconds();

		uint32_t micros_dif = 0;
		uint32_t seconds_dif = 0;

		get_time_elapsed(seconds_start, micros_start, seconds_end, micros_end, &seconds_dif, &micros_dif);

		// Calculate the distance.  The '+ 20' is to handle the case where we
		// receive an interrupt slightly before an even multiple of 58 us.
		// This would not affect our calculation in the event that we are 
		// slightly over the threshold, and it eliminates a costly mod
		// operation.
		distance = (micros_dif + 20) / 58;

		/*
		if (timerValue != 1)
		{	
			// Code to eliminate "noise" from the Sonar's signal.  The sonar 
			// has a tendency to make very sudden changes in distance measured.
			// This could be due to a number of factors, however, it is
			// undesirable.  I would argue though, that if it is only a brief
			// change then the response time of the motors would essentially 
			// make the impact negligible.  Additionally, we may want an 
			// abrupt change in height above the ground.  This could happen
			// if we move over and off of a table.... 
			if ( distance-timerValue < 5 && distance-timerValue > -5) {
				distance = timerValue;
			} else {
				if (timerValue > distance)
				distance += 5;
				else
				distance -= 5;
			}
		}
		*/
	}

}


uint32_t quad_ranger_get_last_distance() {
	return distance;
}
