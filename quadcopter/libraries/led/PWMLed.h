



#ifndef PWM_LED_H
#define PWM_LED_H


#include "PwmOut.h"

using namespace mbed;

typedef enum {
    RED,
    GREEN,
    BLUE,
    YELLOW,
    CYAN,
    MAGENTA,
    WHITE,
    OFF
} Color_t;

typedef enum {
    CATHODE,
    ANODE
} LED_type_t;


/** 
 */
class PWMLed {

public:

    /** 
     */
    PWMLed(PinName led, LED_type_t type);


    /** 
     */
    PWMLed(PinName red_led, PinName green_led, PinName blue_led, LED_type_t type);


    /** 
     */
    void set_brightness(float brt);


    /** 
     */
    void set_brightness(float red_brt, float green_brt, float blue_brt);


    /**
     */
    void set_color(Color_t color, float brt);


    /** 
     */
    void rgb_color_sweep(float speed, float brt);

protected:
    PwmOut _pwm_red;
    PwmOut _pwm_green;
    PwmOut _pwm_blue;
    LED_type_t _type;
};

#endif //PWM_LED_H