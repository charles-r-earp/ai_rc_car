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
        double steer_ratio, drive_ratio;  
    };
    
    input(State state = State::Manual) {
        this->state = state;
        
        this->controller.init();
    }
    
    
    
    control_input get() {
        
        // check for controller input
        // or ai error input 
        // to switch state 
        
        control_input inputs;
        
        switch(this->state) {
            case State::Manual:
                break;
            case State::Autonomous:
                break;
        }
    }
};

#endif // AI_RC_CAR_INPUT_INPUT_HPP