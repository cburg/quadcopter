

#include "quad_serial.h"


int int_to_char[10] = {1000000000,
				  	   100000000,
			  		   10000000,
					   1000000,
					   100000,
					   10000,
					   1000,
					   100,
					   10,
					   1};

uint8_t char_to_hex[16] = {"0123456789ABCDEF"};

void quad_serial_init() {

	// Nothing to initialize for Serial data.  It should already be 
	// done when we initialize the UART0 module.
}


void serial_put_int(int val) {
	if (val < 0) {
		UARTCharPut(UART0_BASE, '-');
		val = -val;
	}

	if (val == 0) {
		UARTCharPut(UART0_BASE, '0');
		return;
	}

	bool leading_zeros_done = false;
	int i;
	for (i = 0; i < 10; i++) {
		uint8_t temp = (uint8_t)(val / int_to_char[i]) + 0x30;
		if (temp > '0' || leading_zeros_done == true) {
			leading_zeros_done = true;
			UARTCharPut(UART0_BASE, temp);
			val = val % int_to_char[i];
		}
	}
}


void serial_put_short(short val) {
	if (val < 0) {
		UARTCharPut(UART0_BASE, '-');
		val = -val;
	}

	if (val == 0) {
		UARTCharPut(UART0_BASE, '0');
		return;
	}

	bool leading_zeros_done = false;
	int i;
	for (i = 5; i < 10; i++) {
		uint8_t temp = (uint8_t)(val / int_to_char[i]) + 0x30;
		if (temp > '0' || leading_zeros_done == true) {
			leading_zeros_done = true;
			UARTCharPut(UART0_BASE, temp);
			val = val % int_to_char[i];
		}
	}
}

void serial_put_int_hex(int val) {
	uint8_t temp;

	temp = (val & 0xF0000000) >> 28;
	UARTCharPut(UART0_BASE, char_to_hex[temp]);

	temp = (val & 0x0F000000) >> 24;
	UARTCharPut(UART0_BASE, char_to_hex[temp]);

	temp = (val & 0x00F00000) >> 20;
	UARTCharPut(UART0_BASE, char_to_hex[temp]);

	temp = (val & 0x000F0000) >> 16;
	UARTCharPut(UART0_BASE, char_to_hex[temp]);

	temp = (val & 0x0000F000) >> 12;
	UARTCharPut(UART0_BASE, char_to_hex[temp]);

	temp = (val & 0x00000F00) >> 8;
	UARTCharPut(UART0_BASE, char_to_hex[temp]);

	temp = (val & 0x000000F0) >> 4;
	UARTCharPut(UART0_BASE, char_to_hex[temp]);

	temp = (val & 0x0000000F) >> 0;
	UARTCharPut(UART0_BASE, char_to_hex[temp]);

}


void serial_put_float(float val) {
	if (val < 0) {
		serial_put_string("-");
		val = -val;
	}

	int head = ((int)val);
	serial_put_int(head);
	serial_put_string(".");	
	

	int i;
	for (i = 0; i < 8; i++) {
		val -= head;
		val *= 10;
		head = ((int)val);
		serial_put_int(head);
	}
}

void serial_put_char_hex(uint8_t val) {
	uint8_t temp;

	temp = (val & 0xF0) >> 4;
	UARTCharPut(UART0_BASE, char_to_hex[temp]);

	temp = (val & 0x0F) >> 0;
	UARTCharPut(UART0_BASE, char_to_hex[temp]);

}


// Assumes that 'string' is null terminated
void serial_put_string(const char *string) {
	int i = 0;
	uint8_t temp = string[i];
	while (temp != '\0') {
		UARTCharPut(UART0_BASE, temp);
		i++;
		temp = string[i];
	}
}