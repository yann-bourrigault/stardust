cmake_minimum_required(VERSION 2.8.3)
project(sd_hardware_interface)

find_package(catkin REQUIRED
	roscpp
	std_msgs
	control_msgs
	sensor_msgs
	urdf
  	joint_limits_interface
  	transmission_interface
  	control_toolbox
	controller_manager
	hardware_interface
	rosparam_shortcuts
  	dynamic_reconfigure
)

## Generate dynamic reconfigure parameters in the 'cfg' folder
generate_dynamic_reconfigure_options(
  cfg/PID.cfg
)

catkin_package(
  INCLUDE_DIRS
    include
  CATKIN_DEPENDS
    hardware_interface
    controller_manager
    roscpp
    control_msgs
    urdf
    joint_limits_interface
    transmission_interface
    control_toolbox
    std_msgs
    sensor_msgs
    rosparam_shortcuts
    dynamic_reconfigure
  LIBRARIES
    HWInterface
    ControlLoop
    Encoder
    VelocityController
)

include_directories(
  ${catkin_INCLUDE_DIRS}
  include
)

# HWInterface
add_library(HWInterface src/hardware_interface.cpp)
add_dependencies(HWInterface
  ${${PROJECT_NAME}_EXPORTED_TARGETS}
  ${catkin_EXPORTED_TARGETS}
)
target_link_libraries(HWInterface
  Encoder
  ControlLoop
  ${catkin_LIBRARIES}
)

# Control loop
add_library(ControlLoop src/control_loop.cpp)
add_dependencies(ControlLoop
  ${${PROJECT_NAME}_EXPORTED_TARGETS}
  ${catkin_EXPORTED_TARGETS}
)
target_link_libraries(ControlLoop
  ${catkin_LIBRARIES}
)

# Encoder
add_library(Encoder src/encoder.cpp)
add_dependencies(Encoder
  ${${PROJECT_NAME}_EXPORTED_TARGETS}
  ${catkin_EXPORTED_TARGETS}
)
target_link_libraries(Encoder
  ${catkin_LIBRARIES}
)

# Velocity controller
add_library(VelocityController src/velocity_controller.cpp)
add_dependencies(VelocityController
  ${${PROJECT_NAME}_EXPORTED_TARGETS}
  ${catkin_EXPORTED_TARGETS}
)
target_link_libraries(VelocityController
  ${catkin_LIBRARIES}
)

# HWInterface executable
add_executable(${PROJECT_NAME} src/hardware_node.cpp)
add_dependencies(${PROJECT_NAME}
  ${${PROJECT_NAME}_EXPORTED_TARGETS}
  ${catkin_EXPORTED_TARGETS}
)
target_link_libraries(${PROJECT_NAME}
  HWInterface
  Encoder
  ControlLoop
  VelocityController
  ${catkin_LIBRARIES}
)

# Install includes
install(DIRECTORY include/${PROJECT_NAME}/
        DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION})

# Install libraries
install(TARGETS
    ControlLoop
    Encoder
    HWInterface
    VelocityController
  LIBRARY DESTINATION
    ${CATKIN_PACKAGE_LIB_DESTINATION}
)

# Install executable
install(TARGETS ${PROJECT_NAME}
  ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION})

install(DIRECTORY
  config
  launch
  DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
)
