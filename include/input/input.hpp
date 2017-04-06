#ifndef AI_RC_CAR_INPUT_INPUT_HPP
#define AI_RC_CAR_INPUT_INPUT_HPP

#include "ds4.hpp"

struct input {
    
    ds4 controller;
    
    enum State {
        Manual,
        Autonomous
    };
    
    State state;
    
    struct control_input {
        double steer_ratio, drive_ratio, steering_trim_direction;  
    };
    
    input(State state = State::Manual) {
        this->state = state;
        
    }
    
    
    
    control_input get() {
        
        // check for controller input
        // or ai error input 
        // to switch state 
        
        control_input inputs;
        
        switch(this->state) {
            case State::Manual:
                inputs.steer_ratio = this->controller.right.x.value;
                if (this->controller.L2.value > 0.1) {
                    inputs.drive_ratio = -this->controller.L2.value; // brake
                }
                else {
                    inputs.drive_ratio = this->controller.R2.value; // go 
                }
                if (int(this->controller.digital.x.value)) {
                    inputs.steering_trim_direction = this->controller.digital.x.value > 0 ? 1 : -1;
                }
                break;
            case State::Autonomous:
                break;
        }
        
        return inputs;
    }
};

#endif // AI_RC_CAR_INPUT_INPUT_HPP