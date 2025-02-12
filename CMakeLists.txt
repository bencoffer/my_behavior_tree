cmake_minimum_required(VERSION 3.8)
project(my_behavior_tree)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(behaviortree_cpp REQUIRED)

add_executable(bt_node src/bt_node.cpp)
ament_target_dependencies(bt_node rclcpp behaviortree_cpp)

install(TARGETS
  bt_node
  DESTINATION lib/${PROJECT_NAME})

ament_package()
