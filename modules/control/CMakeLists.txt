#include_directories(include)

add_library(control INTERFACE)

target_include_directories(control INTERFACE include)

target_sources(control INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include/control.hpp)

find_library(wiringPi wiringPi /usr/local/include /usr/local/lib)
message("wiringPi path: ${wiringPi}\n")

#target_link_libraries(control INTERFACE wiringPi)

add_executable(servo_control tests/servo_control.cpp)
target_link_libraries(servo_control control)