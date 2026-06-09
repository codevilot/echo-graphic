cmake_minimum_required(VERSION 3.8)
project(ros2_echo_graphic)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(sensor_msgs REQUIRED)

add_executable(echo-graphic
  src/main.cpp
  src/compressed_image_viewer.cpp
  src/dds_transport.cpp
  src/image_viewer.cpp
  src/joint_state_viewer.cpp
  src/lidar_viewer.cpp
  src/png_encoder.cpp
  src/rate_limiter.cpp
  src/terminal_utils.cpp
  src/topic_discovery.cpp
)
target_compile_features(echo-graphic PUBLIC cxx_std_17)
target_include_directories(echo-graphic PRIVATE include)
ament_target_dependencies(echo-graphic rclcpp sensor_msgs)

add_executable(echo-graphic-mockup
  src/mockup_main.cpp
  src/dds_transport.cpp
  src/mock_image_publisher.cpp
  src/mock_joint_state_publisher.cpp
  src/mock_publishers.cpp
  src/mock_scan_publisher.cpp
  src/png_encoder.cpp
)
target_compile_features(echo-graphic-mockup PUBLIC cxx_std_17)
target_include_directories(echo-graphic-mockup PRIVATE include)
ament_target_dependencies(echo-graphic-mockup rclcpp sensor_msgs)

install(TARGETS echo-graphic echo-graphic-mockup
  DESTINATION lib/${PROJECT_NAME}
)

ament_package()
