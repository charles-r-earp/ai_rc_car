#include <control.hpp>

#include <thread>
#include <chrono>   


int main() {
    
    control::pwm_driver pwm_driver;
    
    pwm_driver.set_duty(0, 0.5);
    
    return 0;
}