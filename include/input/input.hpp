

#include <joystick.hpp>
#include <ds4.hpp>

#include <thread>
#include <chono>

struct input {
    
    ds4 controller;
    
    enum State {
        Manual,
        Autonomous
    };
    
    struct control_input {
        double steer_ratio, drive_ratio;  
    };
    
    input(State state = State.Manual) {
        this->state = state;
    }
    
    control_input get() {
        
        // check for controller input
        // or ai error input 
        // to switch state 
        
        control_input inputs;
        
        switch(this->state) {
            case State.Manual:
                break;
            case State.Autonomous:
                break;
        }
    }
};