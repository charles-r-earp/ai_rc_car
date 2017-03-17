add_library(control INTERFACE)
target_sources(control INTERFACE control.hpp)
target_include_directories(control INTERFACE include)

find_library(wiringPi wiringPi4 /usr/local/include /usr/local/lib)

target_link_libraries(control INTERFACE wiringPi)

#add_subdirectory(tests)