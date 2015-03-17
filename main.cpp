
#include "mbed.h"
#include "quadcopter/libraries/servo/PWMServo.h"
#include "quadcopter/libraries/imu/MPU6050Imu.h"


RawSerial pc(USBTX, USBRX);
Mpu6050Imu imu(I2C_SDA, I2C_SCL);
PWMServo motor(PWM_OUT);
uint32_t current_pwm_us;

#define PWM_MIN     900
#define PWM_MAX     1900
#define PWM_IDLE    

// Motor Initialization:
//  1.) Set stick to idle
//  2.) Connect Battery
//  3.) Hold in Idle for 1.0 seconds
//  4.) Wait for beeps
//  5.) Increase motor speed to desired level.

void serial_interrupt() {
    char c = pc.getc();
    switch(c) {
        case(' '): // Kill Switch!
            motor.set_pwm_value(0);
            printf("Killing Motor!!!\n\r");
            break;
        case('m'):    // Min
            current_pwm_us = PWM_MIN;
            motor.set_pwm_value(current_pwm_us);
            printf("Setting motor speed to: %d\n\r", (int)current_pwm_us);
            break;
        case('/'):    // Max
            current_pwm_us = PWM_MAX;
            motor.set_pwm_value(current_pwm_us);
            printf("Setting motor speed to: %d\n\r", (int)current_pwm_us);
            break;
        case('.'):    // Step Up
            current_pwm_us += 5;
            if (current_pwm_us > PWM_MAX) {
                current_pwm_us = PWM_MAX;
            }
            motor.set_pwm_value(current_pwm_us);
            printf("Setting motor speed to: %d\n\r", (int)current_pwm_us);
            break;
        case(','):    // Step Down
            current_pwm_us -= 5;
            if (current_pwm_us < PWM_MIN) {
                current_pwm_us = PWM_MIN;
            }
            motor.set_pwm_value(current_pwm_us);
            printf("Setting motor speed to: %d\n\r", (int)current_pwm_us);
            break;
        default:
            break;
    }
}

int main() {
    pc.attach(serial_interrupt);
    pc.baud(115200);

    imu.set_sensitivity(Sensitivity_1, Sensitivity_1);

    motor.set_min_max_pwm(1100, 1900);
    motor.set_period_ms(20);

    current_pwm_us = 0;

    int16_t accel_x = 0;
    int16_t accel_y = 0;
    int16_t accel_z = 0;
    int16_t gyro_x = 0;
    int16_t gyro_y = 0;
    int16_t gyro_z = 0;

    while(true) {
        imu.read_raw(&accel_x, &accel_y, &accel_z, &gyro_x, &gyro_y, &gyro_z);
        pc.printf("Ax: %d\tAy: %d\tAz: %d\tGx: %d\tGy: %d\tGz: %d\t\n\r",
            accel_x, accel_y, accel_z, gyro_x, gyro_y, gyro_z);
        wait_ms(20);
    }
}
