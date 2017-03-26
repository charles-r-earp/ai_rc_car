#include <ai_rc_car.hpp>

#include <thread>
#include <chrono>

int main() {

    car rc_car;
    
    while (true) {
    
        rc_car.controller.steer(1);
        
        std::this_thread::sleep_for (std::chrono::seconds(1));
        
        rc_car.controller.steer(-1);
        
        std::this_thread::sleep_for (std::chrono::seconds(1));
    
    }
    
    return 0;
}