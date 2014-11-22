

#include "PWMServo.h"

PWMServo::PWMServo(PinName pin) :
        _min_pwm_us(1000),
        _max_pwm_us(2000),
        _min_angle_deg(0),
        _max_angle_deg(180),
        _pwm_out(pin) {

    _pwm_out.period_ms(20); // 50 Hz period.
}


void PWMServo::set_min_max_pwm(uint32_t min_pwm_us, uint32_t max_pwm_us) {
    _min_pwm_us = min_pwm_us;
    _max_pwm_us = max_pwm_us;
}


void PWMServo::set_min_max_angle(uint32_t min_angle_deg, uint32_t max_angle_deg) {
    _min_angle_deg = min_angle_deg;
    _max_angle_deg = max_angle_deg;
}


void PWMServo::set_period_hz(float period_hz) {
    _pwm_out.period((1 / period_hz));
}


void PWMServo::set_period_sec(float period_sec) {
    _pwm_out.period(period_sec);
}


void PWMServo::set_period_ms(uint32_t period_ms) {
    _pwm_out.period_ms(period_ms);
}

void PWMServo::set_period_us(uint32_t period_us) {
    _pwm_out.period_us(period_us);
}

void PWMServo::move_to_angle(float angle_deg) {
    // Only set the angle if it's within the valid range.
    if (angle_deg > _max_angle_deg || angle_deg < _min_angle_deg || angle_deg < 0) {
        return;
    }

    // TODO: clean up? make more efficient?
    float angle_offset = angle_deg - _min_angle_deg;
    float angle_range = _max_angle_deg - _min_angle_deg;
    float angle_offset_frac = angle_offset / angle_range;

    uint32_t pwm_period_range = _max_pwm_us - _min_pwm_us;
    uint32_t pwm_offset = (uint32_t)(pwm_period_range * angle_offset_frac);
    uint32_t pwm_value = _min_pwm_us + pwm_offset;

    _pwm_out.pulsewidth_us(pwm_value);

}


void PWMServo::set_pwm_value(uint32_t pwm_duty_us) {
    _pwm_out.pulsewidth_us(pwm_duty_us);
}
