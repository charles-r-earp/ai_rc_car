#ifndef AI_RC_CAR_CONTROL_HPP
#define AI_RC_CAR_CONTROL_HPP

#include <iostream>

#include <wiringPi.h>

#define WIRINGPI_CODES 

namespace control {
    
    struct led {
        
        int pin;
        
        led(const int& pin) {
            
            this->pin = pin;
        }
        
        bool set(const bool& on) {
            
            digitalWrite (0, on); 
        }
    };
}

#endif // AI_RC_CAR_CONTROL_HPP