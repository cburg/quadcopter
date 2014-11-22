

#ifndef QUAD_9_AXIS_H
#define QUAD_9_AXIS_H

#include "quad_common.h"
#include "quad_rgb_led.h"
#include "inc/hw_i2c.h"
#include "driverlib/i2c.h"
#include "driverlib/uart.h"
#include "quad_serial.h"

#define MAGNETO_MIN_VAL	-1200	// (micro Teslas)
#define MAGNETO_MAX_VAL	 1200	
#define ACCEL_MIN_VAL	-4		// (g == 9.81 m/s^2)
#define ACCEL_MAX_VAL	 4		
#define GYRO_MIN_VAL	-500	// (degrees / sec)
#define GYRO_MAX_VAL	 500	
#define GYRO_RESOLUTION	 250.0	// (degrees / sec)

// Slave Address
#define SLAVE_ADDR_9_AXIS	0x68

#define MAX_SHORT	65536
#define GRAVITY_1	16383.0
#define GYRO_SCALE	(250.0 / 32767.0)

// Slave Registers:
// General:
#define WHO_AM_I		0x75
#define POWER_SETTING	0x6B

// Gyroscope:
#define GYRO_CONFIG		0x1B
#define GYRO_XOUT_H		0x43
#define GYRO_XOUT_L		0x44
#define GYRO_YOUT_H		0x45
#define GYRO_YOUT_L		0x46
#define GYRO_ZOUT_H		0x47
#define GYRO_ZOUT_L		0x48

// Accelerometer:
#define ACCEL_CONFIG	0x1C
#define ACCEL_XOUT_H	0x3B
#define ACCEL_XOUT_L	0x3C
#define ACCEL_YOUT_H	0x3D
#define ACCEL_YOUT_L	0x3E
#define ACCEL_ZOUT_H	0x3F
#define ACCEL_ZOUT_L	0x40

// Magnetometer:
#define MAGENTO_XOUT_H	0x03
#define MAGENTO_XOUT_L	0x04
#define MAGENTO_YOUT_H	0x05
#define MAGENTO_YOUT_L	0x06
#define MAGENTO_ZOUT_H	0x07
#define MAGENTO_ZOUT_L	0x08


#define FS_SEL 1				// For setting the range of the Gyroscope
#define AFS_SEL 1				// For setting the range of the Accelerometer


// Some structure to hold the calibration floats....

typedef struct NineAxisRawReadings {
	uint16_t gyro_x;
	uint16_t gyro_y;
	uint16_t gyro_z;
	uint16_t accel_x;
	uint16_t accel_y;
	uint16_t accel_z;
	uint16_t magneto_x;
	uint16_t magneto_y;
	uint16_t magneto_z;
} NineAxisRaw;

typedef struct NineAxisFloatReadings {
	float gyro_x;
	float gyro_y;
	float gyro_z;
	float accel_x;
	float accel_y;
	float accel_z;
	float magneto_x;
	float magneto_y;
	float magneto_z;
	float yaw;
	float roll;
	float pitch;
	uint32_t sec;
	uint32_t micros;
} NineAxisFloat;


NineAxisFloat naf_cur;
NineAxisFloat naf_prev;
NineAxisRaw nar_cur;


void quad_9_axis_init();
uint16_t quad_9_axis_read_register(uint8_t reg);
void quad_9_axis_read_raw_data();
void quad_9_axis_get_float_data();
void quad_9_axis_get_euler_angles(float *yaw, float *pitch, float *roll);

void quad_9_axis_kalman_filter();
void quad_9_axis_calc_compensation();

#endif //QUAD_9_AXIS_H
