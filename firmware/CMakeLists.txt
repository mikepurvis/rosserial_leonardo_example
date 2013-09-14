cmake_minimum_required(VERSION 2.8)
project(rosserial_leonardo_example_firmware)

set(ARDUINO_DEFAULT_BOARD leonardo)
set(ARDUINO_DEFAULT_PORT /dev/arduino)

include_directories(${PROJECT_BINARY_DIR}/ros_lib)

generate_arduino_firmware(example SRCS main.cpp)
