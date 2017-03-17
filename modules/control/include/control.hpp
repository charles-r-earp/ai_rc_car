#ifndef AI_RC_CAR_CONTROL_HPP
#define AI_RC_CAR_CONTROL_HPP

#include <wiringPi.h>

#define WIRINGPI_CODES 

namespace control {

    struct servo_control {
        
        servo_control() {
            
            this->setup();
        }
    
        int setup() {
            
            int error_code = wiringPiSetup (); 
            
            std::cout << "servo_control setup()... error_code = " << error_code << std::endl; 
            
            return error_code;
        }
    };
}

#endif // AI_RC_CAR_CONTROL_HPP