#ifndef AI_RC_CAR_AI_RC_CAR_HPP
#define AI_RC_CAR_AI_RC_CAR_HPP


#include "control/control.hpp"
#include "input/input.hpp"


#include <thread>
#include <chrono>
#include <ctime>
#include <cstdio>

// Get current date/time, format is YYYY-MM-DD.HH:mm:ss
std::string currentDateTime() {
    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);
    // Visit http://en.cppreference.com/w/cpp/chrono/c/strftime
    // for more information about date/time format
    strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);

    return buf;
}

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
        std::cout << "Update " << currentDateTime() << std::endl;
        input::control_input inputs = this->input_manager.get();
        this->controller.drive(inputs.drive_ratio);
        this->controller.steer(inputs.steer_ratio);
        this->controller.steering_trim(inputs.steering_trim_direction);
    }
    
};


#endif // AI_RC_CAR_AI_RC_CAR_HPP