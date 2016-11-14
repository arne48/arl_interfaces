cmake_minimum_required(VERSION 2.8.3)
project(arl_interfaces)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  cmake_modules
  hardware_interface
  pluginlib
  roscpp
)

include_directories(include)

catkin_package(
        CATKIN_DEPENDS roscpp
        INCLUDE_DIRS include
)


install(DIRECTORY include/${PROJECT_NAME}/
        DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION})