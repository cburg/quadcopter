



#ifndef MPU_6050_IMU_H
#define MPU_6050_IMU_H


#include "I2C.h"

using namespace mbed;

#define MPU_6050_SLAVE_ADDR 0x68

// Slave Registers:
// General:
#define WHO_AM_I        0x75
#define POWER_SETTING   0x6B

// Gyroscope:
#define GYRO_CONFIG     0x1B
#define GYRO_XOUT_H     0x43
#define GYRO_XOUT_L     0x44
#define GYRO_YOUT_H     0x45
#define GYRO_YOUT_L     0x46
#define GYRO_ZOUT_H     0x47
#define GYRO_ZOUT_L     0x48

// Accelerometer:
#define ACCEL_CONFIG    0x1C
#define ACCEL_XOUT_H    0x3B
#define ACCEL_XOUT_L    0x3C
#define ACCEL_YOUT_H    0x3D
#define ACCEL_YOUT_L    0x3E
#define ACCEL_ZOUT_H    0x3F
#define ACCEL_ZOUT_L    0x40

// Magnetometer (MPU 9050 Only):
#define MAGENTO_XOUT_H  0x03
#define MAGENTO_XOUT_L  0x04
#define MAGENTO_YOUT_H  0x05
#define MAGENTO_YOUT_L  0x06
#define MAGENTO_ZOUT_H  0x07
#define MAGENTO_ZOUT_L  0x08



#define FS_SEL 1                // For setting the range of the Gyroscope
#define AFS_SEL 1               // For setting the range of the Accelerometer


/** 
 */
class Mpu6050Imu {

public:

    /** 
     * I2C Clock Pin
     * I2C Data Pin
     * 
     */
    Mpu6050Imu(PinName sda, PinName scl);

    void read_raw(int16_t *accel_x, int16_t *accel_y, int16_t *accel_z,
                  int16_t *gyro_x,  int16_t *gyro_y,  int16_t *gyro_z);

protected:

    uint16_t read_mpu_6050_register(uint8_t reg);
    I2C _i2c;

};

#endif //MPU_6050_IMU_H