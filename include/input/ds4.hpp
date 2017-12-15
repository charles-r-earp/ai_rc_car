#ifndef AI_RC_CAR_INPUT_DS4_HPP
#define AI_RC_CAR_INPUT_DS4_HPP

#include "joystick.hpp"

#include <cstdlib>
#include <thread>
#include <chrono>

#include <cassert>

#include <set>


struct ds4 {
    
    std::thread ds4drv_thread, update_thread;
    joystick controller;
    
    struct button {
        bool pressed;
    };
    
    struct axis {
        double value; // -1, 1
        
        void set(int raw_axis_value) {
            int _min = joystick::event::min_axis_value;
            int _max = joystick::event::max_axis_value;
            this->value = 2*(raw_axis_value - _min)/double(_max - _min) - 1;
        }
    };
    
    struct trigger {
        double value; // 0, 1 -> 1 fully pressed
        
        void set(int raw_axis_value) {
            int _min = joystick::event::min_axis_value;
            int _max = joystick::event::max_axis_value;
            this->value = (raw_axis_value - _min)/double(_max - _min);
        }
    };
    
    struct thumbstick {
        axis x, y;
    };
    
    button circle, triangle, square, cross;
    button share, options, PS;
    button L1, R1, L3, R3;

    thumbstick left, right;
    thumbstick digital;
    
    trigger L2, R2;
    
    void update() {
      for (auto& event : this->controller.get_events()) {
        switch (event.type) {
          case joystick::event::Type::Button:
            switch (event.number) {
            case 0:
              this->square.pressed = event.value;
              break;
            case 1:
              this->cross.pressed = event.value;
              break;
            case 2:
              this->circle.pressed = event.value;
              break;
            case 3:
              this->triangle.pressed = event.value;
              break;
            case 4:
              this->L1.pressed = event.value;
              break;
            case 5:
              this->R1.pressed = event.value;
              break;
            case 6:
              // L2
              break;
            case 7:
              // R2
              break;
            case 8:
              this->share.pressed = event.value;
              break;
            case 9:
              this->options.pressed = event.value;
              break;
            case 10:
              this->L3.pressed = event.value;
              break;
            case 11:
              this->R3.pressed = event.value;
              break;
            case 12:
              this->PS.pressed = event.value;
              break;
            default:
              break;
            }
            break;
        case joystick::event::Type::Axis:
          switch (event.number) {
          case 0:
            this->left.x.set(event.value);
            break;
          case 1:
            this->left.y.set(-event.value);
            break;
          case 2:
            this->right.x.set(event.value);
            break;
          case 3:
            this->L2.set(event.value);
            break;
          case 4:
            this->R2.set(event.value);
            break;
          case 5:
            this->right.y.set(-event.value);
            break;
          case 6:
            this->digital.x.set(event.value);
            break;
          case 7:
          case 8:
          case 9:
          case 10:
          case 11:
            break;
          case 12:
            break;
          default:
            break;
        }
           default:
             break;
        }
      }
      std::this_thread::sleep_for (std::chrono::milliseconds(1));
    }
};

#endif // AI_RC_CAR_INPUT_DS4_HPP
