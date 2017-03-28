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
        std::cout << "ds4()" << std::endl;
        
        // creates /dev/input/joy1
        this->ds4drv_thread = std::thread([](){ system("ds4drv"); });
        
        std::thread wait_thread([&](){
            bool success = false;
            success = controller.init(1);
            if (success) break;
            std::cout << "waiting for /dev/input/joy1" << std::endl;
            std::this_thread::sleep_for (std::chrono::seconds(1));
        });
        
        // wait
        wait_thread.join();
        
        std::cout << "update_thread()" << std::endl;
        this->update_thread = std::thread([&](){
            while (true) {
                //std::cout << "update" << std::endl;
                joystick::event event = controller.get();
                
                joystick::event::Type type = event.get_type();
                //std::cout << "type: " << type << std::endl;

                switch (type) {
                    case joystick::event::Type::Button:
                        std::cout << "Button!" << std::endl;
                        switch (event.number) {
                            case 0:
                                circle.pressed = event.value;
                                if (event.value) std::cout << "circle pressed" << std::endl;
                            default: 
                                break;
                        }
                    case joystick::event::Type::Axis:
                        std::cout << "Axis!" << std::endl;
                    default:
                        break;
                }

                std::this_thread::sleep_for (std::chrono::milliseconds(100));
            }
        });
    }
};

#endif // AI_RC_CAR_INPUT_DS4_HPP