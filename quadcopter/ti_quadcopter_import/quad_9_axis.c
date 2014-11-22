

#include "quad_9_axis.h"
#include <math.h>


void quad_9_axis_init() {

	// Configure the Gyroscope sensitivity
	I2CMasterSlaveAddrSet(I2C2_BASE, SLAVE_ADDR_9_AXIS, false);
	I2CMasterDataPut(I2C2_BASE, WHO_AM_I);
	I2CMasterControl(I2C2_BASE, I2C_MASTER_CMD_SINGLE_SEND);
	while(I2CMasterBusy(I2C2_BASE)) {
		;
	}
	
	I2CMasterSlaveAddrSet(I2C2_BASE, SLAVE_ADDR_9_AXIS, true);
	I2CMasterControl(I2C2_BASE, I2C_MASTER_CMD_SINGLE_RECEIVE);
	while(I2CMasterBusy(I2C2_BASE)) {
		;
	}

	int j = 0;
	int i = 0;
	while (i < 100000) {
		i++;
		j++;
	}


	I2CMasterSlaveAddrSet(I2C2_BASE, SLAVE_ADDR_9_AXIS, false);
	I2CMasterDataPut(I2C2_BASE, POWER_SETTING);
	I2CMasterControl(I2C2_BASE, I2C_MASTER_CMD_BURST_SEND_START);
	while(I2CMasterBusy(I2C2_BASE)) {
		;
	}
	I2CMasterDataPut(I2C2_BASE, 0x00);
	I2CMasterControl(I2C2_BASE, I2C_MASTER_CMD_BURST_SEND_FINISH);
	while(I2CMasterBusy(I2C2_BASE)) {
		;
	}


	i = 0;
	while (i < 100000) {
		i++;
		j++;
	}


	/*
	// The code here configures the Gyroscope and  Accelerometer's 
	// sensitivity.
	// Configure the Gyroscope sensitivity
	I2CMasterSlaveAddrSet(I2C2_BASE, SLAVE_ADDR_9_AXIS, false);

	//I2CMasterDataPut(I2C2_BASE, 0x00);
	I2CMasterControl(I2C2_BASE, I2C_MASTER_CMD_BURST_SEND_START);
	while(I2CMasterBusy(I2C2_BASE)) {
		;
	}

	I2CMasterDataPut(I2C2_BASE, GYRO_CONFIG);
	I2CMasterControl(I2C2_BASE, I2C_MASTER_CMD_BURST_SEND_CONT);
	while(I2CMasterBusy(I2C2_BASE)) {
		;
	}

	I2CMasterDataPut(I2C2_BASE, FS_SEL << 3);
	I2CMasterControl(I2C2_BASE, I2C_MASTER_CMD_BURST_SEND_FINISH);
	while(I2CMasterBusy(I2C2_BASE)) {
		;
	}
	


	// Configure the Accelerometer sensitivity
	I2CMasterSlaveAddrSet(I2C2_BASE, SLAVE_ADDR_9_AXIS, false);

	//I2CMasterDataPut(I2C2_BASE, 0x00);
	I2CMasterControl(I2C2_BASE, I2C_MASTER_CMD_BURST_SEND_START);
	while(I2CMasterBusy(I2C2_BASE)) {
		;
	}

	I2CMasterDataPut(I2C2_BASE, ACCEL_CONFIG);
	I2CMasterControl(I2C2_BASE, I2C_MASTER_CMD_BURST_SEND_CONT);
	while(I2CMasterBusy(I2C2_BASE)) {
		;
	}

	I2CMasterDataPut(I2C2_BASE, FS_SEL << 3);
	I2CMasterControl(I2C2_BASE, I2C_MASTER_CMD_BURST_SEND_FINISH);
	while(I2CMasterBusy(I2C2_BASE)) {
		;
	}*/
	naf_prev.gyro_x = 0.0;
	naf_prev.gyro_y = 0.0;
	naf_prev.gyro_z = 0.0;
	naf_prev.accel_x = 0.0;
	naf_prev.accel_y = 0.0;
	naf_prev.accel_z = 0.0;
	naf_prev.magneto_x = 0.0;
	naf_prev.magneto_y = 0.0;
	naf_prev.magneto_z = 0.0;
	naf_prev.yaw = 0.0;
	naf_prev.pitch = 0.0;
	naf_prev.roll = 0.0;
	naf_prev.sec = 0;
	naf_prev.micros = 0;


	naf_cur.gyro_x = 0.0;
	naf_cur.gyro_y = 0.0;
	naf_cur.gyro_z = 0.0;
	naf_cur.accel_x = 0.0;
	naf_cur.accel_y = 0.0;
	naf_cur.accel_z = 0.0;
	naf_cur.magneto_x = 0.0;
	naf_cur.magneto_y = 0.0;
	naf_cur.magneto_z = 0.0;
	naf_cur.yaw = 0.0;
	naf_cur.pitch = 0.0;
	naf_cur.roll = 0.0;
	naf_cur.sec = 0;
	naf_cur.micros = 0;
}


uint16_t quad_9_axis_read_register(uint8_t reg) {
	I2CMasterSlaveAddrSet(I2C2_BASE, SLAVE_ADDR_9_AXIS, false);
	I2CMasterDataPut(I2C2_BASE, reg);
	I2CMasterControl(I2C2_BASE, I2C_MASTER_CMD_SINGLE_SEND);
	while(I2CMasterBusy(I2C2_BASE)) {
		;
	}
	
	I2CMasterSlaveAddrSet(I2C2_BASE, SLAVE_ADDR_9_AXIS, true);
	I2CMasterControl(I2C2_BASE, I2C_MASTER_CMD_SINGLE_RECEIVE);
	while(I2CMasterBusy(I2C2_BASE)) {
		;
	}
	uint16_t temp = (uint16_t)((I2CMasterDataGet(I2C2_BASE)) & 0x000000FF);
	return temp;
}

void quad_9_axis_read_raw_data() {
	// Read the raw data from the 9-axis
	nar_cur.gyro_x = quad_9_axis_read_register(GYRO_XOUT_H) << 8;
	nar_cur.gyro_x |= quad_9_axis_read_register(GYRO_XOUT_L);
	
	nar_cur.gyro_y = quad_9_axis_read_register(GYRO_YOUT_H) << 8;
	nar_cur.gyro_y |= quad_9_axis_read_register(GYRO_YOUT_L);
	
	nar_cur.gyro_z = quad_9_axis_read_register(GYRO_ZOUT_H) << 8;
	nar_cur.gyro_z |= quad_9_axis_read_register(GYRO_ZOUT_L);

	nar_cur.accel_x = quad_9_axis_read_register(ACCEL_XOUT_H) << 8;
	nar_cur.accel_x |= quad_9_axis_read_register(ACCEL_XOUT_L);
	
	nar_cur.accel_y = quad_9_axis_read_register(ACCEL_YOUT_H) << 8;
	nar_cur.accel_y |= quad_9_axis_read_register(ACCEL_YOUT_L);
	
	nar_cur.accel_z = quad_9_axis_read_register(ACCEL_ZOUT_H) << 8;
	nar_cur.accel_z |= quad_9_axis_read_register(ACCEL_ZOUT_L);

	// Copy "naf_cur" into "naf_prev"
	naf_prev.gyro_x = naf_cur.gyro_x;
	naf_prev.gyro_y = naf_cur.gyro_y;
	naf_prev.gyro_z = naf_cur.gyro_z;
	naf_prev.accel_x = naf_cur.accel_x;
	naf_prev.accel_y = naf_cur.accel_y;
	naf_prev.accel_z = naf_cur.accel_z;
	naf_prev.magneto_x = naf_cur.magneto_x;
	naf_prev.magneto_y = naf_cur.magneto_y;
	naf_prev.magneto_z = naf_cur.magneto_z;
	naf_prev.yaw = naf_cur.yaw;
	naf_prev.pitch = naf_cur.pitch;
	naf_prev.roll = naf_cur.roll;
	naf_prev.sec = naf_cur.sec;
	naf_prev.micros = naf_cur.micros;

	// Copy raw data into naf_cur while converting to float
	naf_cur.gyro_x = (short)nar_cur.gyro_x;
	naf_cur.gyro_y = (short)nar_cur.gyro_y;
	naf_cur.gyro_z = (short)nar_cur.gyro_z;
	naf_cur.accel_x = (short)nar_cur.accel_x / ((float)GRAVITY_1);
	naf_cur.accel_y = (short)nar_cur.accel_y / ((float)GRAVITY_1);
	naf_cur.accel_z = (short)nar_cur.accel_z / ((float)GRAVITY_1);
}


void quad_9_axis_get_euler_angles(float *yaw, float *pitch, float *roll) {

	uint32_t micros_elapsed = 0;
	uint32_t sec_elapsed = 0;
	get_time_elapsed(naf_prev.sec, naf_prev.micros, naf_cur.sec, naf_cur.micros, &sec_elapsed, &micros_elapsed);

	float roll_ratio_denom = sqrtf(naf_cur.accel_y*naf_cur.accel_y + naf_cur.accel_z*naf_cur.accel_z);
	float pitch_ratio_denom = sqrtf(naf_cur.accel_x*naf_cur.accel_x + naf_cur.accel_z*naf_cur.accel_z);



	//float temp_yaw = atanf();
	float accel_roll = atanf(naf_cur.accel_x / roll_ratio_denom) * ((float)180.0) / ((float)3.14159);
	float accel_pitch = atanf(naf_cur.accel_y / pitch_ratio_denom) * ((float)180.0) / ((float)3.14159);


	float gyro_time = ((float)micros_elapsed) / 1000000.0;
	float gyro_scale = 250.0 / 32767.0;

	float gyro_pitch = naf_prev.pitch + (naf_cur.gyro_x - naf_prev.gyro_x) * gyro_scale * gyro_time;
	float gyro_roll = naf_prev.roll + (naf_cur.gyro_y - naf_prev.gyro_y) * gyro_scale * gyro_time;

	// NOTE: The casts here are necessary!!!! Without them, assigning
	//       filtered_pitch / filtered_roll to an external variable will cause
	//       the system to freeze.  I am not sure why this happens...
	float filtered_pitch = gyro_pitch * ((float)0.95) + accel_pitch * ((float)0.05);
	float filtered_roll = gyro_roll * ((float)0.95) + accel_roll * ((float)0.05);

	*pitch = filtered_pitch;
	*roll = filtered_roll;

	naf_cur.pitch = filtered_pitch;
	naf_cur.roll = filtered_roll;
	
}