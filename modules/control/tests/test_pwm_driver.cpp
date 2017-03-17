#include <control.hpp>

#include <thread>
#include <chrono>   


int main() {
    
    control::pwm_driver pwm_driver;
    
    int x;
    
    while(x < 10) {
        
        //pwm_driver.setPWM(0, 100, 1000);
        
        //pwm_driver.setDuty(0, 4095);
        
         std::cout << x << " = " << pwm_driver.read(x) << std::endl;
        
        std::chrono::seconds(1);
    }
    
    return 0;
}