
#include "mbed.h"
#include "quadcopter/libraries/servo/PWMServo.h"


int main() {
    RawSerial pc(USBTX, USBRX);
    pc.baud(115200);

    InterruptIn sonar_in();

    PWMServo ms(PC_9);
    ms.set_min_max_pwm(575, 2425);
    ms.set_min_max_angle(0, 180);

    while(true) {
        int i;
        for (i = 0; i <= 60; i += 5) {
            ms.move_to_angle(i);
            pc.printf("%d\n\r", i);
            wait_ms(100);
        }

            ms.move_to_angle(60);
            ms.move_to_anle(120);

        for (i = 120; i >= 0; i -= 5) {
            ms.move_to_angle(i);
            pc.printf("%d\n\r", i);
            wait_ms(100);
        }
    }
}
