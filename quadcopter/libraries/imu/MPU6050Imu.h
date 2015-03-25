



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


// Used by filters to scale values to a common base unit (degrees/sec for gyro
// and acceleration due to earths gravity for the accelerometer)
#define MAX_SHORT_POS   ((float)32767)
#define MIN_SHORT_NEG   ((float)32768)

#define GYRO_RESOLUTION_SENS_0  ((float)250.0)
#define GYRO_RESOLUTION_SENS_1  ((float)500.0)
#define GYRO_RESOLUTION_SENS_2  ((float)1000.0)
#define GYRO_RESOLUTION_SENS_3  ((float)2000.0)

#define GYRO_SCALE_SENS_0_POS   (MAX_SHORT_POS / GYRO_RESOLUTION_SENS_0)
#define GYRO_SCALE_SENS_1_POS   (MAX_SHORT_POS / GYRO_RESOLUTION_SENS_1)
#define GYRO_SCALE_SENS_2_POS   (MAX_SHORT_POS / GYRO_RESOLUTION_SENS_2)
#define GYRO_SCALE_SENS_3_POS   (MAX_SHORT_POS / GYRO_RESOLUTION_SENS_3)

#define GYRO_SCALE_SENS_0_NEG   (MIN_SHORT_NEG / GYRO_RESOLUTION_SENS_0)
#define GYRO_SCALE_SENS_1_NEG   (MIN_SHORT_NEG / GYRO_RESOLUTION_SENS_1)
#define GYRO_SCALE_SENS_2_NEG   (MIN_SHORT_NEG / GYRO_RESOLUTION_SENS_2)
#define GYRO_SCALE_SENS_3_NEG   (MIN_SHORT_NEG / GYRO_RESOLUTION_SENS_3)


#define ACCEL_RESOLUTION_SENS_0  ((float)2.0)
#define ACCEL_RESOLUTION_SENS_1  ((float)4.0)
#define ACCEL_RESOLUTION_SENS_2  ((float)8.0)
#define ACCEL_RESOLUTION_SENS_3  ((float)16.0)

#define ACCEL_SCALE_SENS_0_POS   (MAX_SHORT_POS / ACCEL_RESOLUTION_SENS_0)
#define ACCEL_SCALE_SENS_1_POS   (MAX_SHORT_POS / ACCEL_RESOLUTION_SENS_1)
#define ACCEL_SCALE_SENS_2_POS   (MAX_SHORT_POS / ACCEL_RESOLUTION_SENS_2)
#define ACCEL_SCALE_SENS_3_POS   (MAX_SHORT_POS / ACCEL_RESOLUTION_SENS_3)

#define ACCEL_SCALE_SENS_0_NEG   (MIN_SHORT_NEG / ACCEL_RESOLUTION_SENS_0)
#define ACCEL_SCALE_SENS_1_NEG   (MIN_SHORT_NEG / ACCEL_RESOLUTION_SENS_1)
#define ACCEL_SCALE_SENS_2_NEG   (MIN_SHORT_NEG / ACCEL_RESOLUTION_SENS_2)
#define ACCEL_SCALE_SENS_3_NEG   (MIN_SHORT_NEG / ACCEL_RESOLUTION_SENS_3)



// Used to set the sensitivity of the gyro (FS_SEL) and accelerometer (AFS_SEL)
#define SET_FS_SEL(x)   (((uint8_t)0x03 & x) << (uint8_t)3)
#define SET_AFS_SEL(x)   (((uint8_t)0x03 & x) << (uint8_t)3)


typedef enum {
    Sensitivity_0 = 0, // Most Sensitive (smallest range)
    Sensitivity_1 = 1,
    Sensitivity_2 = 2,
    Sensitivity_3 = 3  // Least Sensitive (largest range)
} MpuSensitivity_t;

// Accelerometer: g -- units of earths gravity
// Gyrocscope: degrees / second
typedef struct imu_raw_data {
    float accel_x;
    float accel_y;
    float accel_z;
    float gyro_x;
    float gyro_y;
    float gyro_z;
} imu_data_t;

/** 
 */
class Mpu6050Imu {

public:

    /** 
     */
    Mpu6050Imu(PinName sda, PinName scl);

    /** 
     */
    void set_sensitivity(MpuSensitivity_t gyro, MpuSensitivity_t accel);


    /** 
     */
    void read_raw(imu_data_t *raw_data);

protected:

    I2C _i2c;
    float _accel_scale_pos; // scaling factor used to get raw values to g
    float _accel_scale_neg;
    float _gyro_scale_pos;  // scaling factor used to get raw values to deg/sec
    float _gyro_scale_neg;
};

#endif //MPU_6050_IMU_H