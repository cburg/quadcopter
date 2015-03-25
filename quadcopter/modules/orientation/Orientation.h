
#ifndef QUADCOPTER_ORIENTATION_H
#define QUADCOPTER_ORIENTATION_H

#include <cmath>
#include "MPU6050Imu.h"
#include "SystemClock.h"

// TODO:
//      1.) Add comments
//      2.) Update function call to use a general IMU class, not one specific to
//          the MPU-6050.
//      3.) Add quaternions to the function.

typedef struct euler_orientation {
    float x; 
    float y; 
    float z;
    uint64_t timestamp;
} euler_orientation_t;

typedef struct quaternions {
    uint64_t timestamp;
} quaternions_t;


class Orientation {
public:
    Orientation(SystemClock &sys_clock);

    bool get_euler_angles(Mpu6050Imu *imu, euler_orientation_t *euler);

protected:
    // Pointer to timer
    // Pointer to first raw imu data
    // Pointer to second raw imu data
    // Array of raw imu data structs

    SystemClock &_sys_clock;
    euler_orientation_t _euler_prev;
};




#endif // QUADCOPTER_ORIENTATION_H