

#include "MPU6050Imu.h"



Mpu6050Imu::Mpu6050Imu(PinName sda, PinName scl) :
    _i2c(sda, scl) {

    //_i2c.frequency(400000);

    // Write to Power Register
    char power_on[2] = {POWER_SETTING, 0x00};
    _i2c.write((MPU_6050_SLAVE_ADDR<<1), power_on, 2);

}


uint16_t Mpu6050Imu::read_mpu_6050_register(uint8_t reg) {
    // Write the register address we are interested in
    _i2c.write((MPU_6050_SLAVE_ADDR<<1), (const char*)&reg, 1);

    // Read the reply
    uint16_t reg_val = 0x0000;
    _i2c.read((MPU_6050_SLAVE_ADDR<<1), (char*)&reg_val, 1);

    return (reg_val & 0x00FF); 
}



void Mpu6050Imu::read_raw(int16_t *accel_x, int16_t *accel_y, int16_t *accel_z,
             int16_t *gyro_x,  int16_t *gyro_y,  int16_t *gyro_z) {


    // Read the raw data from the 9-axis
    *gyro_x = read_mpu_6050_register(GYRO_XOUT_H) << 8;
    *gyro_x |= read_mpu_6050_register(GYRO_XOUT_L);
    *gyro_y = read_mpu_6050_register(GYRO_YOUT_H) << 8;
    *gyro_y |= read_mpu_6050_register(GYRO_YOUT_L);
    *gyro_z = read_mpu_6050_register(GYRO_ZOUT_H) << 8;
    *gyro_z |= read_mpu_6050_register(GYRO_ZOUT_L);
    *accel_x = read_mpu_6050_register(ACCEL_XOUT_H) << 8;
    *accel_x |= read_mpu_6050_register(ACCEL_XOUT_L);
    *accel_y = read_mpu_6050_register(ACCEL_YOUT_H) << 8;
    *accel_y |= read_mpu_6050_register(ACCEL_YOUT_L);
    *accel_z = read_mpu_6050_register(ACCEL_ZOUT_H) << 8;
    *accel_z |= read_mpu_6050_register(ACCEL_ZOUT_L);
    
}