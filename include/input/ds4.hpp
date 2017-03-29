#ifndef AI_RC_CAR_INPUT_DS4_HPP
#define AI_RC_CAR_INPUT_DS4_HPP

#include "joystick.hpp"

#include <cstdlib>
#include <thread>
#include <chrono>

#include <cassert>


struct ds4 {
    
    std::thread ds4drv_thread, update_thread;
    joystick controller;
    
    struct button {
        bool pressed;
    };
    
    struct axis {
        int value;
    };
    
    struct thumbstick {
        axis x, y;
    };
    
    button circle, triangle, square, cross;
    button L1, R1;

    thumbstick left, right;
    axis L2, R2;
    
    ds4() {
        //std::cout << "ds4()" << std::endl;
        
        // creates /dev/input/joy1
        this->ds4drv_thread = std::thread([](){ system("ds4drv"); });
        

        //std::cout << "update_thread()" << std::endl;
        /*
        this->update_thread = std::thread([&](){
            
            
            
            std::this_thread::sleep_for (std::chrono::milliseconds(1));
        });*/
    }
};

#endif // AI_RC_CAR_INPUT_DS4_HPP