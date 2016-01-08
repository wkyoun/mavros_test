cmake_minimum_required(VERSION 2.8.3)
project(mavros_test)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  std_msgs
  mavros
  geometry_msgs
  
)

catkin_package(
#  INCLUDE_DIRS include
  LIBRARIES mavros_test
  CATKIN_DEPENDS roscpp std_msgs mavros geometry_msgs
  DEPENDS system_lib
)

include_directories(
  ${catkin_INCLUDE_DIRS}
)

add_executable(mavros_test src/mavros_test_throttle.cpp)
target_link_libraries(mavros_test
   ${catkin_LIBRARIES}
 )



