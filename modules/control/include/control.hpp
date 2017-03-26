#ifndef AI_RC_CAR_CONTROL_HPP
#define AI_RC_CAR_CONTROL_HPP

//#include <i2c-linux/pwm_driver.hpp>

struct control {

    //const i2c-linux::pwm_driver::servo steering_servo(0);
    //const i2c-linux::pwm_driver::bidirectional_motor drive_motor(4, 5);
    //const i2c-linux::pwm_driver pwm_driver;
    
    steer(const double& steer_ratio) {
        // steer ratio is on the interval (-1, 1) with 1 being a left turn and -1 a right turn
        
        // convert to ratio on interval (0, 1)
        double ratio = (steer_ratio + 1)/2.0;
        
      //  pwm_driver.set_ratio(this->steering_servo, ratio);
    }
    
    drive(const double& speed_ratio) {
        // speed ratio is interval (-1, 1) with 1 being forward, -1 being reverse
        
        double duty = std::abs(speed_ratio);
        int direction = std::sign(speed_ratio);
        
        //pwm_driver.set_duty(this->drive_motor, duty, direction);
        
    }
    
};

#endif // AI_RC_CAR_CONTROL_HPP