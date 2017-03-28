cmake_minimum_required (VERSION 2.6)
project(ai_rc_car)

if (CMAKE_VERSION VERSION_LESS "3.1")
    if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
      set (CMAKE_CXX_FLAGS "--std=gnu++11 ${CMAKE_CXX_FLAGS}")
    endif ()
  else ()
    set (CMAKE_CXX_STANDARD 11)
endif ()

find_library(i2c-linux NAMES i2c-linux)
add_library(ai_rc_car INTERFACE)


target_sources(ai_rc_car INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include/ai_rc_car.hpp)

#find_package(lambda REQUIRED)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include 
#${lambda_INCLUDE_DIRS}
)

target_link_libraries(ai_rc_car INTERFACE i2c-linux)

add_executable(run run/run.cpp)
target_link_libraries(run ai_rc_car)