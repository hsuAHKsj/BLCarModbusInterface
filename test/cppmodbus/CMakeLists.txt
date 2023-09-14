cmake_minimum_required(VERSION 3.0.2)
project(cppModbus)

add_compile_options(-fPIC)
if(CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS}")
    set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -Wall -O3")
    message(STATUS "optional:-std=c++11")
endif(CMAKE_COMPILER_IS_GNUCXX)

include_directories("./include")
link_directories("./lib")


set(LIBRARY_OUTPUT_PATH ../lib) 

ADD_LIBRARY(motor SHARED
  src/modbus_wrapper.cpp
  src/joint_driver.cpp
)


add_executable(
  test_info
  test/test.cpp
) 

add_executable(
  test_read_all_holding_reg
  test/test_wrapper.cpp
) 

target_link_libraries(test_read_all_holding_reg
libmotor.so)

add_executable(
  test_motor
  test/test_motor.cpp
) 

target_link_libraries(test_motor
libmotor.so)