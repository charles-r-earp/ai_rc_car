#include <control.hpp>

#include <iostream>



int main () {
    
    control::led led(0);
    
    bool on = false;
    
    for (;;) {
        
        led.set(on);
        on = !on;
        
        delay(500);
    }
    
    return 0;
}