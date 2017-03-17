



#include <iostream>

#include <wiringPi.h>

#define WIRINGPI_CODES 



namespace control {
    
    struct led { 
        
        const int pin;
        
        led(const int pin = 0) : pin(pin) {
            
            int code = wiringPiSetup();
            
            if (code != 0) std::cout << "LED wiringPiSetup() returned: " << code << std::endl;
            
            pinMode (pin, OUTPUT);
        }
        
        void set(bool on) {
            
            digitalWrite(this->pin, on ? HIGH : LOW);
        }
        
    };
}