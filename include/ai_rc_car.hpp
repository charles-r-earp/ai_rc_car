#ifndef AI_RC_CAR_AI_RC_CAR_HPP
#define AI_RC_CAR_AI_RC_CAR_HPP


#include "control/control.hpp"
#include "input/input.hpp"


#include <thread>
#include <chrono>
#include <ctime> 

struct ai_rc_car {

    control controller;
    input input_manager;
    
    void run() {
        bool next_update = true;
        std::thread timer_thread;
        while(true) {
            
            timer_thread = std::thread([](){
                std::this_thread::sleep_for (std::chrono::milliseconds(100));
            });
            
            this->update();
            
            timer_thread.join(); // waits until next time;
        }
    }
    
    void update() {
        
        input::control_input inputs = this->input_manager.get();
        this->controller.drive(inputs.drive_ratio);
        this->controller.steer(inputs.steer_ratio);
        
    }
    
};


#endif // AI_RC_CAR_AI_RC_CAR_HPP