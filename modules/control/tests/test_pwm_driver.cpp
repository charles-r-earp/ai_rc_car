#include <control.hpp>

#include <thread>
#include <chrono>   


int main() {
    
    control::pwm_driver pwm_driver;
    
    while(true) {
        
        pwm_driver.setPWM(0, 100, 1000);
        
        std::chrono::seconds(1);
    }
    
    return 0;
}