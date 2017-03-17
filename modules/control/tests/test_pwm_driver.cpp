#include <control.hpp>

#include <thread>
#include <chrono>   


int main() {
    
    control::pwm_driver pwm_driver;
    
    pwm_driver.set_duty(0, 1);
    
    return 0;
}