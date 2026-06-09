#pragma once

#include <string>

#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/laser_scan.hpp"

#include "ros2_echo_graphic/rate_limiter.hpp"

namespace ros2_echo_graphic
{

class LidarViewer : public rclcpp::Node
{
public:
  LidarViewer(const std::string & topic_name, const std::string & topic_type, double fps);

private:
  void callback(const sensor_msgs::msg::LaserScan::SharedPtr msg);

  RateLimiter limiter_;
  rclcpp::Subscription<sensor_msgs::msg::LaserScan>::SharedPtr subscription_;
};

}  // namespace ros2_echo_graphic
