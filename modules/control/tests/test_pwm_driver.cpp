#include <control.hpp>  


int main() {
    
    control::pwm_driver pwm_driver;
    
    control::pwm_driver::servo servo;
    
    while (true) {
        
        pwm_driver.set_ratio(servo, 0);
        
        std::this_thread::sleep_for(std::chrono::seconds(1));
        
        pwm_driver.set_ratio(servo, 1);
        
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    
    return 0;
}