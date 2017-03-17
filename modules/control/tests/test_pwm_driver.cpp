#include <control.hpp>

#include <thread>
#include <chrono>   


int main() {
    
    control::pwm_driver pwm_driver;
    
    pwm_driver.write(6, 1000);
    pwm_driver.write(7, 1000);
    pwm_driver.write(8, 0);
    pwm_driver.write(9, 0);
    
    int x;
    
    while(x++ < 40) {
        
        //pwm_driver.setPWM(0, 100, 1000);
        
        //pwm_driver.setDuty(0, 4095);
        
         std::cout << x << " = " << pwm_driver.read(x) << std::endl;
        
    }
    
    while (true) {
        
        std::chrono::seconds(1);
    }
    
    
    
    return 0;
}