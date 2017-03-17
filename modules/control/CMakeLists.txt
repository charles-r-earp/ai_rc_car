add_library(control INTERFACE)

target_include_directories(control INTERFACE include)

target_sources(control INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include/control.hpp)

#target_link_libraries(control INTERFACE)

add_executable(test_pwm_driver tests/test_pwm_driver.cpp)
target_link_libraries(test_pwm_driver control)


