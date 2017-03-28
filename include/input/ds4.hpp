#ifndef AI_RC_CAR_INPUT_DS4_HPP
#define AI_RC_CAR_INPUT_DS4_HPP

#include "joystick.hpp"

#include <cstdlib>
#include <thread>
#include <chrono>


struct ds4 {
    
    std::thread ds4drv_thread, update_thread
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
        
        this->ds4drv_thread = std::thread([](){ system("ds4drv") });
        
        std::cout << "update_thread()" << std::endl;
        update_thread = std::thread([&](){
            while (true) {
                std::cout << "update" << std::endl;
                joystick::event event = controller.get();

                switch (event.get_type()) {
                    case joystick::event::Type::Button:
                        switch (event.number) {
                            case 0:
                                circle.pressed = event.value;
                                if (event.value) std::cout << "circle pressed" << std::endl;
                            default: 
                                break;
                        }
                    case joystick::event::Type::Axis:
                    default:
                        break;
                }

                std::this_thread::sleep_for (std::chrono::milliseconds(100));
            }
        });
    }
};

#endif // AI_RC_CAR_INPUT_DS4_HPP