

#include "MPU6050Imu.h"



Mpu6050Imu::Mpu6050Imu(PinName sda, PinName scl) :
    _i2c(sda, scl) {

    // Write to Power Register
    char power_on[2] = {POWER_SETTING, 0x00};
    _i2c.write((MPU_6050_SLAVE_ADDR<<1), power_on, 2);

}


void Mpu6050Imu::set_sensitivity(MpuSensitivity_t gyro, MpuSensitivity_t accel) {
    
    uint8_t gyro_sens[2] = {GYRO_CONFIG, SET_FS_SEL(gyro)};
    uint8_t accel_sens[2] = {ACCEL_CONFIG, SET_AFS_SEL(accel)};

    _i2c.write((MPU_6050_SLAVE_ADDR<<1), (const char*)gyro_sens, 2);
    _i2c.write((MPU_6050_SLAVE_ADDR<<1), (const char*)accel_sens, 2);
}

void Mpu6050Imu::read_raw(int16_t *accel_x, int16_t *accel_y, int16_t *accel_z,
             int16_t *gyro_x,  int16_t *gyro_y,  int16_t *gyro_z) {

    // accelx, accely, accelz, temp, gyrox, gyroy, gyroz
    uint16_t rawdata[7];

    // Perform a burst read of all the registers. A burst read of registers will
    // grab the data from the specified register initially. The register address
    // will be incremented for each subsequent byte.  Thus all data can be 
    // acquired in 2 I2C transactions as opposed to 24!
    const char start_register = ACCEL_XOUT_H;
    _i2c.write((MPU_6050_SLAVE_ADDR<<1), (const char*)&start_register, 1);
    _i2c.read((MPU_6050_SLAVE_ADDR<<1), (char*)rawdata, 14);


    // Copy the values in. Sadly, the register values are essentially given to 
    // us in big-endian format whereas the Cortex M4 is little-endian.
    *accel_x = ((rawdata[0] & 0x00FF) << 8) | ((rawdata[0] & 0xFF00) >> 8);
    *accel_y = ((rawdata[1] & 0x00FF) << 8) | ((rawdata[1] & 0xFF00) >> 8);
    *accel_z = ((rawdata[2] & 0x00FF) << 8) | ((rawdata[2] & 0xFF00) >> 8);
    *gyro_x = ((rawdata[4] & 0x00FF) << 8) | ((rawdata[4] & 0xFF00) >> 8);
    *gyro_y = ((rawdata[5] & 0x00FF) << 8) | ((rawdata[5] & 0xFF00) >> 8);
    *gyro_z = ((rawdata[6] & 0x00FF) << 8) | ((rawdata[6] & 0xFF00) >> 8);
}