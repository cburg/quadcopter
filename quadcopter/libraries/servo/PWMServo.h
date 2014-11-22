

#ifndef PWM_SERVO_H
#define PWM_SERVO_H


#include "PwmOut.h"

using namespace mbed;


/** Allows control of a PWM based servo motor (as opposed to more advanced
 * servos which might use I2C for their communication interface).  Allows the
 * user to specify the actual range of motion and the control signal rather than
 * assuming that the servo adheres to a standard.
 * 
 * Example:
 * @code
 * int main() {
 * 
 *     PWMServo ms(PC_9);
 *     ms.set_min_max_pwm(575, 2425); // 575 us to 2425 us
 *     ms.set_min_max_angle(0, 180);
 * 
 *     while(true) {
 *      
 *         int i;
 *         for (i = 0; i <= 180; i += 5) {
 *             ms.move_to_angle(i);
 *             wait_ms(100);
 *         }
 * 
 *         for (i = 180; i >= 0; i -= 5) {
 *             ms.move_to_angle(i);
 *             wait_ms(100);
 *         }
 * 
 *     }
 * }
 * @endcode
 */
class PWMServo {

public:

    /** Create a servo output on the specified pin.
     * 
     * @param pin The pin which the pwm from the servo is connected to.
     * @note
     * The default values are:
     *      Period - 50 Hz (20 ms)
     *      Min PWM - 1.0 ms
     *      Max PWM - 2.0 ms
     *      Min Angle - 0 degrees
     *      Max Angle - 180 degrees
     */
    PWMServo(PinName pin);

    /** Set the minimum and maximum PWM duty cycles. The default is 1000 us and
     * 2000 us respectively.
     * 
     * @param min_pwm_us The minimum PWM duty cycle in microseconds for the servo.
     * @param max_pwm_us The maximum PWM duty cycle in microseconds for the servo.
     */
    void set_min_max_pwm(uint32_t min_pwm_us, uint32_t max_pwm_us);


    /** Set the minimum and maximum angles for the servo. The default is 0 degrees
     * and 180 degrees respectively.
     * 
     * @param min_angle_deg The minimum PWM duty cycle in microseconds for the servo.
     * @param max_angle_deg The maximum PWM duty cycle in microseconds for the servo.
     * 
     * @note
     * The minimum angle will likely be set to 0, however, if you desire to work
     * off the neutral value of the servo (usually, 1.5 ms), then explicitly
     * setting the minimum angle might be useful.
     */
    void set_min_max_angle(uint32_t min_angle_deg, uint32_t max_angle_deg);


    /** Set the period of the PWM cycle for the servo in hertz.
     * 
     * @param period_hz The frequency in Hz of the PWM period.
     */
    void set_period_hz(float period_hz);


    /** Set the period of the PWM cycle for the servo in seconds.
     * 
     * @param period_sec The PWM period in seconds.
     */
    void set_period_sec(float period_sec);


    /** Set the period of the PWM cycle for the servo in milliseconds.
     * 
     * @param period_ms The PWM period in milliseconds.
     */
    void set_period_ms(uint32_t period_ms);


    /** Set the period of the PWM cycle for the servo in microseconds.
     * 
     * @param period_us The PWM period in microseconds.
     */    
     void set_period_us(uint32_t period_us);


    /** Set the desired angle to move the servo to.
     * 
     * @param angle_deg The angle in degrees to move the servo to.
     *
     * @note
     * The PWM signal will be calculated based on the min, max angles, and min,
     * max PWM values set previously. If these have not been set, then the default
     * values will be used.
     */
    void move_to_angle(float angle_deg);


    /** Explicitly set the PWM duty cycle for the servo.  This will probably be 
     * used in one of two instances: when you're testing the range of the servo,
     * and if setting angles doesn't prove to be accurate enough.
     *
     * @param pwm_duty_us The PWM duty cycle to send to the servo.
     * 
     */
    void set_pwm_value(uint32_t pwm_duty_us);


protected:
    uint32_t _min_pwm_us;
    uint32_t _max_pwm_us;
    uint32_t _min_angle_deg;
    uint32_t _max_angle_deg;

    PwmOut _pwm_out;
};

#endif //PWM_SERVO_H