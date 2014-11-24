

#include "MaxSonar.h"

// Callback to be used as the Interrupt Service Routine
void MaxSonar::sonar_interrupt_callback() {
    if (_data_in.read() == 1) {
        _start_time = 0;
        _timer.start();
    }

    if (_data_in.read() == 0) {
        _timer.stop();
        _end_time = _timer.read_us();
        _timer.reset();
        
        // Caclulate the distance
        _distance_history[_cur_dist_idx] = (((float)_end_time) - ((float)_start_time)) / (float)_us_per_cm;
        
        _cur_dist_idx++;
        if (_cur_dist_idx == 5){
            _cur_dist_idx = 0;
        }

        if (_perform_single) {
            stop_readings();
        }
    }
}

MaxSonar::MaxSonar(PinName data_pin, PinName rx_pin, MaxSonarModel_t model, bool analog) :
    _int(data_pin),
    _data_in(data_pin),
    _rx_out(rx_pin),
    _start_time(0.0),
    _end_time(0.0),
    _distance_history({0.0, 0.0, 0.0, 0.0, 0.0}),
    _cur_dist_idx(0),
    _us_per_cm(0.0),
    _perform_single(false) {

    // Set the scaling factors
    switch(model) {
        case (MB_1210):
            _us_per_cm = 58;
            break;
        default:
            _us_per_cm = 58;
            break;
    }

    // Set the Interrupts
    _int.fall<MaxSonar>(this, &MaxSonar::sonar_interrupt_callback);
    _int.rise<MaxSonar>(this, &MaxSonar::sonar_interrupt_callback);

    if (rx_pin == NC) {
        _using_rx_pin = false;
    } else {
        _using_rx_pin = true;
        stop_readings();
    }
}


void MaxSonar::start_readings() {
    if (_using_rx_pin) {
        _rx_out.write(1);
    }
}


void MaxSonar::stop_readings() {
    if (_using_rx_pin) {
        _rx_out.write(0);
    }
}


void MaxSonar::single_read() {
    if (_using_rx_pin) {
        _cur_dist_idx = 0;

        // Clear the previous distance entries
        for (int i = 0; i < 5; i++) {
            _distance_history[i] = 0.0;
        }

        _perform_single = true;
        _rx_out.write(1);
    }
}




float MaxSonar::get_distance() {
    // Check whether a single read was performed
    if (_perform_single) {
        return _distance_history[0];
    } else {
        float average_distance = 0.0;
        for (int i = 0; i < 5; i++) {
            average_distance += _distance_history[i];
        }
        return (average_distance / 5.0);
    }
}

