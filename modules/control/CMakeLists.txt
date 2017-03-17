add_library(control INTERFACE)

find_library(wiringPi_LIBRARIES wiringPi /usr/local/lib)
message("wiringPi_LIBRARIES path: ${wiringPi_LIBRARIES}\n")

find_path(wiringPi_INCLUDE_DIRS wiringPi/wiringPi.h /usr/local/include)
message("wiringPi_LIBRARIES path: ${wiringPi_LIBRARIES}\n")

target_include_directories(control INTERFACE include wiringPi_INCLUDE_DIRS)

target_sources(control INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include/control.hpp)



#target_link_libraries(control INTERFACE wiringPi_LIBRARIES)

add_executable(servo_control tests/servo_control.cpp)
target_link_libraries(servo_control control)