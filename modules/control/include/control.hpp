#ifndef AI_RC_CAR_CONTROL_HPP
#define AI_RC_CAR_CONTROL_HPP

#include <iostream>

#include <wiringPi.h>

#define WIRINGPI_CODES 

namespace control {
    
    struct led { 
        
        const int pin;
        
        led(const int pin = 0) {
            
            this->pin = pin;
        }
        
        void set(bool on) {
            
            digitalWrite(this->pin, on);
        }
        
    };
}

#endif // AI_RC_CAR_CONTROL_HPP