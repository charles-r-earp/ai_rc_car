#ifndef AI_RC_CAR_AI_RC_CAR_HPP
#define AI_RC_CAR_AI_RC_CAR_HPP


#include "control/control.hpp"
#include "input/input.hpp"

struct ai_rc_car {

    control controller;
    input input_manager;
    
    void run() {
        while(true) {
            this->update();
        }
    }
    
    void update() {
        
       input::control_input inputs = this->input.get();
        this->controller.drive(inputs.drive_ratio);
        this->controller.steer(inputs.steer_ratio);
    }
    
};


#endif // AI_RC_CAR_AI_RC_CAR_HPP