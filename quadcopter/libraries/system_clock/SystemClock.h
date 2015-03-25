
#ifndef SYSTEM_CLOCK_H
#define SYSTEM_CLOCK_H

#include "Ticker.h"
#include "DigitalOut.h"

using namespace mbed;


// TODO: Check to make sure we don't have time drift! If we do, ways to minimize:
//      1.) Use external clock
//      2.) Use separate timer and configure it correctly (this will eat our PWM)
//      3.) Use multiple tickers (one for seconds, one for ms, one for microseconds)
// 
// With a Saleae logic analyzer running at 24 MHz, a pin was read as toggling at
// 9.833 us and 9.917 us. With a 24 MHz sample rate, the error will be 41.667 ns.


/** A simple class to maintain the number of microseconds the system has been 
 * running. Intended to calculate the time between multiple events.
 */
class SystemClock {

public:

    /**
     */
    SystemClock();

    void start();
    uint32_t get_uptime_ms();

    uint64_t get_uptime();

protected:
    void ticker_callback();

    uint64_t _uptime_us;
    Ticker _ticker;
};


#endif //SYSTEM_CLOCK_H