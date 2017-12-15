cmake_minimum_required (VERSION 2.6)
project(ai_rc_car)

if (CMAKE_VERSION VERSION_LESS "3.1")
    if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
      set (CMAKE_CXX_FLAGS "--std=gnu++11 ${CMAKE_CXX_FLAGS}")
    endif ()
  else ()
    set (CMAKE_CXX_STANDARD 11)
endif ()

add_library(ai_rc_car INTERFACE)
target_sources(ai_rc_car INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include/ai_rc_car.hpp)
target_include_directories(ai_rc_car INTERFACE submodules/i2c-linux/include submodules/i2c-linux/submodules/i2c-tools/include)

#find_package(i2c-linux CONFIG REQUIRED)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(ai_rc_car INTERFACE pthread)

add_executable(run src/run.cpp)
target_link_libraries(run ai_rc_car)

add_subdirectory(tests)
