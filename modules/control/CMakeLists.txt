add_library(control INTERFACE)
target_sources(control INTERFACE include/control.hpp)
#target_include_directories(control INTERFACE include)

find_library(wiringPi wiringPi4 /usr/local/include /usr/local/lib)

target_link_libraries(control INTERFACE wiringPi)

add_executable(servo_control tests/servo_control.cpp)
target_link_libraries(servo_control control)