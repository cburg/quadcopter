

#include "quad_i2c.h"

void quad_i2c_init() {
	// We will be using I2C pins:
	//		PE4 -- I2C SCL
	//		PE5 -- I2C SDA
	SysCtlPeripheralEnable(SYSCTL_PERIPH_I2C2); // We will be jumping the pins
												// for I2C2 to PB7 and PB6 for
												// the Sensor Hub BoosterPack.
			
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);// Enable the port (if it 
    											// hasn't already been done).
	GPIOPinConfigure(GPIO_PE4_I2C2SCL);
	GPIOPinConfigure(GPIO_PE5_I2C2SDA);
	
	GPIOPinTypeI2CSCL(GPIO_PORTE_BASE, GPIO_PIN_4);
	GPIOPinTypeI2C(GPIO_PORTE_BASE, GPIO_PIN_5);
	
	I2CMasterInitExpClk(I2C2_BASE, SysCtlClockGet(), false); // set to true to
															 // enable 400kbps
															 // transmissions
	
	I2CMasterEnable(I2C2_BASE);
}
