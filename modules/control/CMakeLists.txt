add_library(control INTERFACE)
target_sources(control control.hpp)
include_directories(include)

find_library(wiringPi wiringPi /usr/local/include /usr/local/lib)

target_link_libraries(control wiringPi)

add_subdirectory(tests)