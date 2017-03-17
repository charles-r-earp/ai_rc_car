#include <control.hpp>

#include <thread>
#include <chrono>   


int main() {
    
    control::pwm_driver pwm_driver;
    
    //pwm_driver.set_duty(0, 1);
    
    int x = 0;
    
    while(x < 100) {
        std::cout << x << " = " << pwm_driver.read(x) << std::endl;
        ++x;
    }
    
    return 0;
}