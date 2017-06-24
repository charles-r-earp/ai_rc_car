#include <ai_rc_car.hpp>


int main() {
    
    //ai_rc_car car;
    //car.run();
    
    exec("ds4drv");
    
    std::this_thread::sleep_for (std::chrono::seconds(30));
    
    return 0;
}