

#ifndef MAX_SONAR_H
#define MAX_SONAR_H

#include "Timer.h"
#include "DigitalIn.h"
#include "DigitalOut.h"
#include "InterruptIn.h"

using namespace mbed;

typedef enum {
    MB_1210
} MaxSonarModel_t;


/** The MaxSonar Class is designed to be used with Maxbotix MaxSonars. Currently, only
 * support for pulse width input is supported. Eventually support for analog
 * reads (and thus allowing for chaining) will be added.
 * 
 * Example: (Prints the MaxSonar readings out 10 times per second)
 * @code
 * int main() {
 *     RawSerial pc(USBTX, USBRX);
 *     pc.baud(115200);
 * 
 *     MaxSonar MaxSonar_in(PC_9, NC, MB_1210, false);
 * 
 *     int temp_distance = 0;
 *     int i = 0;
 *     while(true) {
 *         temp_distance = (int)MaxSonar_in.get_distance();
 *         pc.printf("distance: %d\n\r", temp_distance);
 *         wait_ms(100);
 *     }
 * }
 * @endcode
 */
class MaxSonar {

public:

    /** Create a Maxbotix MaxSonar input using the specified pins, the specified model,
     * and whether the incoming signal is analog or digital. If the input pin is set
     * to analog, then the distance measurement will be proportionally converted to 
     * a voltage. If not set to analog, then the input signal is expected to be a 
     * proportionally converted to a pulse width signal. If the rx_pin is set, then
     * the start_readings() needs to be called. If rx_pin is not set, then readings
     * will begin automatically and continue as long as there is power to the MaxSonar.
     * 
     * @param data_pin This is the input line from the MaxSonar which contains the range reading
     * @param rx_pin The rx_pin is used to tell the MaxSonar when to perform range readings.
     * @param model The particular MaxBotix MaxSonar model.
     * @param analog Indicates whether data_pin is an analog in pin or not.
     */
    MaxSonar(PinName data_pin, PinName rx_pin, MaxSonarModel_t model, bool analog=false);

    /** Starts repeat readings on the MaxSonar.
     */
    void start_readings();

    /** Stops readings from the MaxSonar, but retains the previous readings.
     */
    void stop_readings();

    /** Performs a single read from the MaxSonar. It should be noted that normally
     * the get_distance() function returns an average of the previous 5 readings
     * to account for noise, however, when a single read is performed, get_distance()
     * will only return this single read. 
     * 
     * After calling single_read() there will be a delay before the reading is
     * available due to several factors. 
     *
     * single_read() will also find use when daisy-chaining MaxSonars together.
     */
    void single_read();

    /** Returns the distance to the detected object in cm. Returns -1.0 if no 
     * object was detected (either because the nearest object was too close, or
     * because the nearest object was too far away). The distance is calculated
     * as the average of the previous 5 readings. This is to ensure that outliers
     * are smoothed out.
     */
    float get_distance();


    void sonar_interrupt_callback();

protected:
    Timer _timer;
    InterruptIn _int;
    DigitalIn _data_in;
    DigitalOut _rx_out;
    int _start_time; // Temporary variable for the start time of the pulse
    int _end_time; // Temporary variable fro teh end time of the pulse
    float _distance; // Sum of 5 distances, should be divided by 5 when returning the value
    float _distance_history[5];
    int _cur_dist_idx;
    int _us_per_cm; // Pulse-wdith scaling factor
    int _v_per_cm; // Voltage scaling factor if using analog
    bool _perform_single;
    bool _using_rx_pin; // Flag indicating whether the user is using the rx_pin or not

};

#endif //MAX_SONAR_H