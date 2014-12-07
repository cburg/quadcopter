
#include "PWMLed.h"

#include "wait_api.h"

// We want the period to be fast enough to avoid flicker when someone moves their
// head.
#define LED_PWM_PERIOD_ms  5 // 10 Hz period
#define LED_PWM_PERIOD_us  5000 // 10 Hz period

#define COLOR_SWEEP_MAX_DELAY_ms    20
#define COLOR_SWEEP_MIN_DELAY_ms    0

PWMLed::PWMLed(PinName led, LED_type_t type) : 
    _pwm_red(led),
    _pwm_green(NC),
    _pwm_blue(NC),
    _type(type) {

    _pwm_red.period_ms(LED_PWM_PERIOD_ms);
}



PWMLed::PWMLed(PinName red_led, PinName green_led, PinName blue_led, LED_type_t type) :
    _pwm_red(red_led),
    _pwm_green(green_led),
    _pwm_blue(blue_led),
    _type(type) {

    _pwm_red.period_ms(LED_PWM_PERIOD_ms);
    _pwm_green.period_ms(LED_PWM_PERIOD_ms);
    _pwm_blue.period_ms(LED_PWM_PERIOD_ms);

}



void PWMLed::set_brightness(float brt) {

    // Cap the brightness values.
    if (brt < 0.0) {
        brt = 0.0;
    } else if (brt > 1.0) {
        brt = 1.0;
    }

    // Lookup whether the LED is an anode or cathode type so we can invert the 
    // PWM signal appropriately.
    if (_type == ANODE) {
        _pwm_red.pulsewidth_us((int32_t)((1.0 - brt) * (float)LED_PWM_PERIOD_us));
    } else {
        _pwm_red.pulsewidth_us((int32_t)(brt * (float)LED_PWM_PERIOD_us));
    }
}



void PWMLed::set_brightness(float red_brt, float green_brt, float blue_brt) {
    // Cap the brightness values.
    if (red_brt < 0.0) {
        red_brt = 0.0;
    } else if (red_brt > 1.0) {
        red_brt = 1.0;
    }

    if (green_brt < 0.0) {
        green_brt = 0.0;
    } else if (green_brt > 1.0) {
        green_brt = 1.0;
    }

    if (blue_brt < 0.0) {
        blue_brt = 0.0;
    } else if (blue_brt > 1.0) {
        blue_brt = 1.0;
    }

    // Lookup whether the LED is an anode or cathode type so we can invert the 
    // PWM signal appropriately.
    if (_type == ANODE) {
        _pwm_red.pulsewidth_us((int32_t)((1.0 - red_brt) * (float)LED_PWM_PERIOD_us));
        _pwm_green.pulsewidth_us((int32_t)((1.0 - green_brt) * (float)LED_PWM_PERIOD_us));
        _pwm_blue.pulsewidth_us((int32_t)((1.0 - blue_brt) * (float)LED_PWM_PERIOD_us));
    } else {
        _pwm_red.pulsewidth_us((int32_t)(red_brt * (float)LED_PWM_PERIOD_us));
        _pwm_green.pulsewidth_us((int32_t)(green_brt * (float)LED_PWM_PERIOD_us));
        _pwm_blue.pulsewidth_us((int32_t)(blue_brt * (float)LED_PWM_PERIOD_us));
    }
}



void PWMLed::set_color(Color_t color, float brt) {

    if (brt < 0.0) {
        brt = 0.0;
    } else if (brt > 1.0) {
        brt = 1.0;
    }

    
    float red = 0.0;
    float green = 0.0;
    float blue = 0.0;

    switch (color) {
        case RED:
            red = 1.0;
            green = 0.0;
            blue = 0.0;
            break;
        case GREEN:
            red = 0.0;
            green = 1.0;
            blue = 0.0;
            break;
        case BLUE:
            red = 0.0;
            green = 0.0;
            blue = 1.0;
            break;
        case YELLOW:
            red = 1.0;
            green = 1.0;
            blue = 0.0;
            break;
        case CYAN:
            red = 0.0;
            green = 1.0;
            blue = 1.0;
            break;
        case MAGENTA:
            red = 1.0;
            green = 0.0;
            blue = 1.0;
            break;
        case WHITE:
            red = 1.0;
            green = 1.0;
            blue = 1.0;
            break;
        case OFF:
            break;
    }

    red *= brt;
    green *= brt;
    blue *= brt;

    set_brightness(red, green, blue);
}

// Float based mod function.  Returns x % y.
float fmod(float x, float y) {
    return x - float(int(x / y)) * y;
}

// Float based absoalute value function.  Returns |x|.
float fabs(float x) {
    return x < 0.0 ? -x : x;
}

void PWMLed::rgb_color_sweep(float speed, float brt) {

    if (speed < 0.0) {
        speed = 0.0;
    } else if (speed > 1.0) {
        speed = 1.0;
    }

    if (brt < 0.0) {
        brt = 0.0;
    } else if (brt > 1.0) {
        brt = 1.0;
    }

    uint32_t sweep_delay_ms = (float)COLOR_SWEEP_MAX_DELAY_ms * speed;

    float h = 0.0;    // hue
    float s = 1.0;    // saturation
    float v = 1.0;    // value
    float c = v * s;  // chroma

    float h_prime = 0.0; // the nth 60 degree category that hue is in.

    float x = 0.0;

    float red_val = 0.0;
    float green_val = 0.0;
    float blue_val = 0.0;

    for (h = 0.0; h < 360.0; h += 0.2) {
        h_prime = (h / 60.0);

        x = c * (1.0 - fabs(fmod(h_prime, 2.0) - 1.0));


        if (h_prime < 1.0) {
            red_val = c;
            green_val = x;
            blue_val = 0.0;
        } else if (h_prime < 2.0) {
            red_val = x;
            green_val = c;
            blue_val = 0.0;
        } else if (h_prime < 3.0) {
            red_val = 0.0;
            green_val = c;
            blue_val = x;
        } else if (h_prime < 4.0) {
            red_val = 0.0;
            green_val = x;
            blue_val = c;
        } else if (h_prime < 5.0) {
            red_val = x;
            green_val = 0.0;
            blue_val = c;
        } else {
            red_val = c;
            green_val = 0.0;
            blue_val = x;
        }


        float m = v - c;

        red_val += m;
        green_val += m;
        blue_val += m;

        // Adjust for the user specified brightness.
        red_val *= brt;
        green_val *= brt;
        blue_val *= brt;

        set_brightness(red_val, green_val, blue_val);

        wait_ms(2);
    }

}


