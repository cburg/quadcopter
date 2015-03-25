

#include "system_clock.h"

#define TICKER_TIMEOUT_US   10 // 10 microsecond ticks, change this based on the precision we can get.

SystemClock::SystemClock() :
    _uptime_us(0),
    _ticker() {
}

void SystemClock::start() {
    _ticker.attach_us(this, &SystemClock::ticker_callback, TICKER_TIMEOUT_US);
}

uint64_t SystemClock::get_uptime() {
    return _uptime_us;
}

void SystemClock::ticker_callback() {
    _uptime_us+=10;
}