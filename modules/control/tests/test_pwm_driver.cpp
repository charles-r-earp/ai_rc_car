#include <control.hpp>

#include <thread>
#include <chrono>   


int main() {
    
    control::pwm_driver pwm_driver;
    
    int x;
    
    while (true) {
        
        if (x++ > 10) {
            
            x = 0;
        }
        
        pwm_driver.set_duty(0, x/10.0);
        
        std::chrono::seconds(1);
    }
    
    
    
    return 0;
}