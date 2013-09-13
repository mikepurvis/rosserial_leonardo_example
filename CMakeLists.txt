cmake_minimum_required(VERSION 2.8.3)

project(rosserial_leonardo_example)

find_package(catkin REQUIRED COMPONENTS std_msgs rosserial_msgs)
catkin_package()

file(MAKE_DIRECTORY ${PROJECT_BINARY_DIR}/firmware)

# Generate the rosserial messages and ros_lib code
add_custom_command(
  OUTPUT ${PROJECT_BINARY_DIR}/firmware/ros_lib
  COMMAND rosrun rosserial_arduino make_libraries.py ${PROJECT_BINARY_DIR}/firmware
  COMMAND cp ${PROJECT_SOURCE_DIR}/firmware/ros_lib/* ${PROJECT_BINARY_DIR}/firmware/ros_lib/
)
add_custom_target(${PROJECT_NAME}_ros_lib DEPENDS ${PROJECT_BINARY_DIR}/firmware/ros_lib)
add_dependencies(${PROJECT_NAME}_ros_lib rosserial_msgs_genpy std_msgs_genpy)

# Generate a call to CMake inside the firmware subdirectory (firmware itself is generated outside of catkin).
add_custom_command(
  OUTPUT ${PROJECT_BINARY_DIR}/firmware/example
  WORKING_DIRECTORY ${PROJECT_BINARY_DIR}/firmware
  COMMAND ${CMAKE_COMMAND} ${PROJECT_SOURCE_DIR}/firmware -DCMAKE_TOOLCHAIN_FILE=${PROJECT_SOURCE_DIR}/arduino-cmake/cmake/ArduinoToolchain.cmake
  COMMAND make
)
add_custom_target(${PROJECT_NAME}_firmware ALL DEPENDS ${PROJECT_BINARY_DIR}/firmware/example)
add_dependencies(${PROJECT_NAME}_firmware ${PROJECT_NAME}_ros_lib)

# Generate a target for the upload command, so that is accessible from catkin_make.
add_custom_target(
  ${PROJECT_NAME}_firmware_upload
  WORKING_DIRECTORY ${PROJECT_BINARY_DIR}/firmware
  COMMAND rosrun ${PROJECT_NAME} enter_bootloader /dev/arduino
  COMMAND make upload
)
add_dependencies(${PROJECT_NAME}_firmware_upload ${PROJECT_NAME}_firmware)
