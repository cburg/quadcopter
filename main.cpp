
#include "mbed.h"
#include "quadcopter/libraries/servo/PWMServo.h"
#include "quadcopter/libraries/imu/MPU6050Imu.h"
#include "quadcopter/libraries/system_clock/SystemClock.h"
#include "quadcopter/modules/orientation/Orientation.h"


// "Globals"
RawSerial pc(USBTX, USBRX);
Mpu6050Imu imu(I2C_SDA, I2C_SCL);
PWMServo motor(PWM_OUT);
SystemClock sys_clock;
Orientation orient(sys_clock);

uint32_t current_pwm_us;
bool pid_loop;

#define PWM_MIN     900
#define PWM_MAX     1900
#define PWM_IDLE    1200

// Motor Initialization:
//  1.) Set stick to idle
//  2.) Connect Battery
//  3.) Hold in Idle for 1.0 seconds
//  4.) Wait for beeps
//  5.) Increase motor speed to desired level.

int int_to_char[10] = {1000000000,
                       100000000,
                       10000000,
                       1000000,
                       100000,
                       10000,
                       1000,
                       100,
                       10,
                       1};

void serial_put_int(int val) {
    if (val < 0) {
        pc.putc('-');
        val = -val;
    }

    if (val == 0) {
        pc.putc('0');
        return;
    }

    bool leading_zeros_done = false;
    int i;
    for (i = 0; i < 10; i++) {
        uint8_t temp = (uint8_t)(val / int_to_char[i]) + 0x30;
        if (temp > '0' || leading_zeros_done == true) {
            leading_zeros_done = true;
            pc.putc(temp);
            val = val % int_to_char[i];
        }
    }
}

void serial_put_float(float val) {
    if (val < 0) {
        pc.putc('-');
        val = -val;
    }

    int head = ((int)val);
    serial_put_int(head);
    pc.putc('.'); 
    

    int i;
    for (i = 0; i < 8; i++) {
        val -= head;
        val *= 10;
        head = ((int)val);
        serial_put_int(head);
    }
}

void serial_interrupt() {
    char c = pc.getc();

    switch(c) {
        case('s'):
            pid_loop = !pid_loop;
            break;
        case(' '): // Kill Switch!
            motor.set_pwm_value(0);
            pc.printf("Killing Motor!!!\n\r");
            break;
        case('m'):    // Min
            current_pwm_us = PWM_MIN;
            motor.set_pwm_value(current_pwm_us);
            pc.printf("Setting motor speed to: %d\n\r", (int)current_pwm_us);
            break;
        case('/'):    // Max
            current_pwm_us = PWM_MAX;
            motor.set_pwm_value(current_pwm_us);
            pc.printf("Setting motor speed to: %d\n\r", (int)current_pwm_us);
            break;
        case('.'):    // Step Up
            current_pwm_us += 5;
            if (current_pwm_us > PWM_MAX) {
                current_pwm_us = PWM_MAX;
            }
            motor.set_pwm_value(current_pwm_us);
            pc.printf("Setting motor speed to: %d\n\r", (int)current_pwm_us);
            break;
        case(','):    // Step Down
            current_pwm_us -= 5;
            if (current_pwm_us < PWM_MIN) {
                current_pwm_us = PWM_MIN;
            }
            motor.set_pwm_value(current_pwm_us);
            pc.printf("Setting motor speed to: %d\n\r", (int)current_pwm_us);
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


    //imu_data_t raw_data;
    euler_orientation_t euler;
    sys_clock.start();

    pid_loop = false;

    float target_angle = -45.0;
    float Kp = 1.0;
    float angle_err = 0.0;

    while(true) {

        orient.get_euler_angles(&imu, &euler);

        angle_err = target_angle - euler.y;
        
        if (pid_loop) {
            current_pwm_us += (int)(Kp * angle_err);
            motor.set_pwm_value(current_pwm_us);
        }
        

        // Print out some information. 
        pc.putc('Y');
        pc.putc(':');
        pc.putc(' ');
        serial_put_float(euler.y);
        pc.putc('\t');
        pc.putc('M');
        pc.putc(':');
        pc.putc(' ');
        serial_put_int(current_pwm_us);
        pc.putc('\n');
        pc.putc('\r');
        //pc.printf("Y:%d\tMotor:%u\n\r", (int)(euler.y), current_pwm_us);
    }
}
