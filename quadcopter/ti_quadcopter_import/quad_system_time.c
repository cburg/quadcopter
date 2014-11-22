

#include "quad_system_time.h"


void quad_system_time_init() {
	SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);
	TimerConfigure(TIMER0_BASE, TIMER_CFG_PERIODIC);

	// TODO: make this "safe".  This will only work out nicely if 
	// SysCtlClockGet() returns a value that is a multiple of 1000000.
	uint32_t timer_period = (SysCtlClockGet() / 1000000);

	TimerLoadSet(TIMER0_BASE, TIMER_A, timer_period);

	IntEnable(INT_TIMER0A);
	TimerIntEnable(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
	TimerEnable(TIMER0_BASE, TIMER_A);
	IntMasterEnable();
}


void quad_system_time_interrupt(void) {
	TimerIntClear(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
	time_micros += 1;
	if (time_micros >= 1000000) {
		time_seconds++;
		time_micros = 0;
	}
}

void get_time_elapsed(uint32_t sec_prev, uint32_t micros_prev, uint32_t sec_cur, uint32_t micros_cur, uint32_t *sec_elapsed, uint32_t *micros_elapsed) {

		(*sec_elapsed) = sec_cur - sec_prev;

		if ((*sec_elapsed) > 0) {
			(*micros_elapsed) = 1000000 - (micros_prev - micros_cur);
		} else {
			(*micros_elapsed) = micros_cur - micros_prev;
		}
}


uint32_t get_system_time_millis() {
	return time_micros * 1000;

}


uint32_t get_system_time_micros() {
	return time_micros;
}



uint32_t get_system_time_seconds() {
	return time_seconds;
}
