cmake_minimum_required(VERSION 3.5)
project(chatting)

# Default to C++14
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(rosidl_default_generators REQUIRED)
set(msg_files
  "msg/Nachricht.msg"
)
rosidl_generate_interfaces(${PROJECT_NAME}
  ${msg_files}
)
ament_export_dependencies(rosidl_default_runtime)

# Create targets for publisher
add_executable(talker src/publisher_lambda_function.cpp)
ament_target_dependencies(talker rclcpp std_msgs)
rosidl_target_interfaces(talker ${PROJECT_NAME} "rosidl_typesupport_cpp")

install(TARGETS
  talker
  DESTINATION lib/${PROJECT_NAME})

# Create targets for subscriber
add_executable(listener src/subscriber_lambda_function.cpp)
ament_target_dependencies(listener rclcpp std_msgs)
rosidl_target_interfaces(listener ${PROJECT_NAME} "rosidl_typesupport_cpp")

install(TARGETS
  listener
  DESTINATION lib/${PROJECT_NAME})

ament_package()