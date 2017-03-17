#include <control.hpp>  


int main() {
    
    control::pwm_driver pwm_driver;
    
    pwm_driver.set_pwm_freq(60);
    
    control::pwm_driver::servo servo;
    
    pwm_driver.set_duty(15, 1);
    
    while (true) {
        
        pwm_driver.set_ratio(servo, 0);
        
        std::this_thread::sleep_for(std::chrono::seconds(1));
        
        pwm_driver.set_ratio(servo, 1);
        
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    
    return 0;
}