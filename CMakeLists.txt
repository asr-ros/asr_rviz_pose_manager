cmake_minimum_required(VERSION 2.8.3)
project(asr_rviz_pose_manager)

add_definitions(-std=gnu++0x)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  move_base_msgs
)

catkin_package(

)

include_directories(
  ${catkin_INCLUDE_DIRS}
)


add_executable(asr_rviz_pose_manager_node src/main.cpp)


target_link_libraries(asr_rviz_pose_manager_node
  ${catkin_LIBRARIES}
)

