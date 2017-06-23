#include <ai_rc_car.hpp>

#include <thread>
#include <chrono>

int main() {

    ai_rc_car rc_car;
    
    float speed = 0;
    int direction;
    
    while (true) {
    
        if (speed > 1) {
            direction = -1;
        }
        else if (speed < -1) {
            direction = 1;
        }
        else {
            rc_car.controller.drive(speed);
        }
        
        speed = 0.1 * direction;
        std::this_thread::sleep_for (std::chrono::seconds(1));
    }
    
    return 0;
}