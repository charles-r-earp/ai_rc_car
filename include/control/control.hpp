#ifndef AI_RC_CAR_CONTROL_CONTROL_HPP
#define AI_RC_CAR_CONTROL_CONTROL_HPP

#include <i2c-linux/pwm_driver.hpp>
#include <cmath>
#include <iostream>

struct control {

    i2c_linux::pwm_driver::servo steering_servo;
    i2c_linux::pwm_driver::servo drive_motor;
    i2c_linux::pwm_driver pwm_driver;
    float steer_min = 0.34, steer_max = 0.56;
    bool steer_reversed = true;
    float drive_min = -1, drive_max = 1;
    bool drive_reversed = false;
    
    control() : steering_servo(0), drive_motor(4) {
    }
    
    void steer(const double& steer_ratio) {
        // steer ratio is on the interval (-1, 1) with 1 being a left turn and -1 a right turn
        
        // convert to ratio on interval (0, 1)
        double ratio = (steer_ratio + 1)/2.0;
        ratio = ratio * (steer_max - steer_min) + steer_min;
        
        std::cout << "control.steer() ratio: " << ratio << std::endl;
                                   
        pwm_driver.set_ratio(this->steering_servo, ratio);
    }
    
    /*void steering_trim(const int direction) {
        
        double trim = this->steering_servo.trim;
        trim += direction * 0.01;
        
        //trim = std::max(trim, this->steering_servo.start);
        //trim = std::min(trim, this->steering_servo.end);
        
        this->steering_servo.trim = trim;
        
        std::cout << "control.steering_trim() trim: " << trim << std::endl;
    }*/
    
    void drive(const double& speed_ratio) {
        // speed ratio is interval (-1, 1) with 1 being forward, -1 being reverse
        speed_ratio = -1;
        double ratio = (speed_ratio + 1)/2.0;
        ratio = ratio * (drive_max - drive_min) + drive_min;
        std::cout << "control.drive() ratio: " << ratio << std::endl;
        
        pwm_driver.set_ratio(this->drive_motor, ratio);
        
    }
    
};

#endif // AI_RC_CAR_CONTROL_CONTROL_HPP
