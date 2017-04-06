#ifndef AI_RC_CAR_CONTROL_CONTROL_HPP
#define AI_RC_CAR_CONTROL_CONTROL_HPP

#include <i2c-linux/i2c_linux.hpp>
#include <cmath>
#include <iostream>

struct control {

    i2c_linux::pwm_driver::servo steering_servo;
    i2c_linux::pwm_driver::servo drive_motor;
    i2c_linux::pwm_driver pwm_driver;
    
    control() : steering_servo(0), drive_motor(4) {
        
        // endpoints and reverse direction
        this->steering_servo.start = 0.40;
        this->steering_servo.end = 0.60;
        this->steering_servo.reversed = true;
        
    }
    
    void steer(const double& steer_ratio) {
        // steer ratio is on the interval (-1, 1) with 1 being a left turn and -1 a right turn
        
        // convert to ratio on interval (0, 1)
        double ratio = (steer_ratio + 1)/2.0;
        
        std::cout << "control.steer() ratio: " << ratio << std::endl;
                                   
        pwm_driver.set_ratio(this->steering_servo, ratio);
    }
    
    void steering_trim(const int direction) {
        
        double trim = this->steering_servo.trim;
        trim += direction * 0.01;
        
        trim = std::min(trim, this->steering_servo.start);
        trim = std::max(trim, this->steering_servo.end);
        
        this->steering_servo.trim = trim;
        
        std::cout << "control.steering_trim() trim: " << trim << std::endl;
    }
    
    void drive(const double& speed_ratio) {
        // speed ratio is interval (-1, 1) with 1 being forward, -1 being reverse
        
        double ratio = (speed_ratio + 1)/2.0;
        std::cout << "control.drive() ratio: " << ratio << std::endl;
        
        pwm_driver.set_ratio(this->drive_motor, ratio);
        
    }
    
};

#endif // AI_RC_CAR_CONTROL_CONTROL_HPP