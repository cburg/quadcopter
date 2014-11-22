


#include "quad_uart.h"




void quad_uart_init() {
	
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART1);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART2);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART3);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART4);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART6);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);

    GPIOPinConfigure(GPIO_PA0_U0RX); // USB Serial Receive Line
    GPIOPinConfigure(GPIO_PA1_U0TX); // USB Serial Transmit Line



    GPIOPinConfigure(GPIO_PB0_U1RX); // Universal Sonar Receive Linx
    GPIOPinConfigure(GPIO_PB1_U1TX); // Transmit Line Sonar 1
    GPIOPinConfigure(GPIO_PD7_U2TX); // Transmit Line Sonar 2
    GPIOPinConfigure(GPIO_PC7_U3TX); // Transmit Line Sonar 3
    GPIOPinConfigure(GPIO_PC5_U4TX); // Transmit Line Sonar 4
    GPIOPinConfigure(GPIO_PD5_U6TX); // Transmit Line Sonar 5



    // Set the pin types
    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);
    GPIOPinTypeUART(GPIO_PORTB_BASE, GPIO_PIN_0 | GPIO_PIN_1);
    GPIOPinTypeUART(GPIO_PORTC_BASE, GPIO_PIN_5 | GPIO_PIN_7);
    GPIOPinTypeUART(GPIO_PORTD_BASE, GPIO_PIN_5 | GPIO_PIN_7);

    UARTEnable(UART0_BASE);
    UARTEnable(UART1_BASE);

    // Set the UART clock to have a baud rate of 115200
    UARTConfigSetExpClk(UART0_BASE, SysCtlClockGet(), 115200,
        (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));

    // The sonars use a 9600 baud rate for serial data, but we are using 
    // gpio with interrupts instead.
    UARTConfigSetExpClk(UART1_BASE, SysCtlClockGet(), 9600,
        (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));


    UARTConfigSetExpClk(UART2_BASE, SysCtlClockGet(), 115200,
        (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));


    UARTConfigSetExpClk(UART3_BASE, SysCtlClockGet(), 115200,
        (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));


    UARTConfigSetExpClk(UART4_BASE, SysCtlClockGet(), 115200,
        (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));


    UARTConfigSetExpClk(UART6_BASE, SysCtlClockGet(), 115200,
        (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));


}


// Sends the given string over the USB serial line.  Terminates whenever a
// null character is received, or when len is reached.  
// TODO: update to convert the string into an ASCII representation.
void quad_uart_send_string(uint8_t *char_str, int len) {
	int i;
	for (i = 0; i < len; i++) {
		// For now, we are assuming that we are only sending messages over the
		// UART line, not receiving.
		UARTCharPut(UART0_BASE, char_str[i]);
	}
}