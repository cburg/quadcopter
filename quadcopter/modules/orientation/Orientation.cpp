
#include "Orientation.h"


Orientation::Orientation(SystemClock &sys_clock) :
    _sys_clock(sys_clock) {
    _euler_prev.x = 0.0;
    _euler_prev.y = 0.0;
    _euler_prev.z = 0.0;
    _euler_prev.timestamp = 0;
}


bool Orientation::get_euler_angles(Mpu6050Imu *imu, euler_orientation_t *euler) {
    if (imu == NULL || euler == NULL) {
        if (euler) {
            euler->x = 0.0;
            euler->y = 0.0;
            euler->z = 0.0;
            euler->timestamp = 0;

            _euler_prev.x = 0.0;
            _euler_prev.y = 0.0;
            _euler_prev.z = 0.0;
            _euler_prev.timestamp = 0;
        }
        return false;
    }

    // Euler orientation angles:
    // To get the rotation around the y axis we need the x and z vectors. The angle the resulting 
    // vector makes around the origin is then the angle of rotation about the y axis. However, this
    // assumes that we have a zero magnitude y vector (i.e. y-axis is level with earth / there is no
    // pitch). In the event that there is pitch, we need to use the magnitude of the vector in the 
    // yz-plane, not just the z vector. 
    // 
    // The same will apply when dealing with pitch calculations. But with the xz-plane instead.
    // 
    // These calculations assume that rotation about the z axis is yaw. 


    uint64_t timestamp = _sys_clock.get_uptime();

    imu_data_t raw_data;
    imu->read_raw(&raw_data);

    uint64_t time_diff_us = timestamp - _euler_prev.timestamp;


    // Calculate vector magnitudes in the yz and xz planes
    float yz_mag = sqrtf(raw_data.accel_y * raw_data.accel_y + raw_data.accel_z * raw_data.accel_z);
    float xz_mag = sqrtf(raw_data.accel_x * raw_data.accel_x + raw_data.accel_z * raw_data.accel_z);

    // Calculate angles from accelerometer
    float y_angle_accel = atanf(raw_data.accel_x / yz_mag) * ((float)180.0) / ((float)3.14159);
    float x_angle_accel = atanf(raw_data.accel_y / xz_mag) * ((float)180.0) / ((float)3.14159);

    // Calculate angles from gyroscope
    float y_angle_gyro = _euler_prev.y + (float)(raw_data.gyro_y / 1000000.0) * (float)time_diff_us;
    float x_angle_gyro = _euler_prev.x + (float)(raw_data.gyro_x / 1000000.0) * (float)time_diff_us;

    // Low pass filter to combine the two
    euler->y = y_angle_gyro * 0.95 + y_angle_accel * 0.05;
    euler->x = x_angle_gyro * 0.95 + x_angle_accel * 0.05;
    //euler->timestamp = timestamp;

    //euler->y = y_angle_accel;
    //euler->x = x_angle_accel;
    euler->timestamp = timestamp;

    // Store value.
    _euler_prev.y = euler->y;
    _euler_prev.x = euler->x;
    _euler_prev.timestamp = timestamp;

    return true;
}