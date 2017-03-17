#include <control.hpp>

#include <thread>
#include <chrono>   


int main() {
    
    control::pwm_driver pwm_driver;
    
    pwm_driver.set_width(0, 0);
    
    return 0;
}