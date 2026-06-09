#pragma once

#include <string>

#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/compressed_image.hpp"

#include "ros2_echo_graphic/rate_limiter.hpp"

namespace ros2_echo_graphic
{

class CompressedImageViewer : public rclcpp::Node
{
public:
  CompressedImageViewer(const std::string & topic_name, const std::string & topic_type, double fps);

private:
  void callback(const sensor_msgs::msg::CompressedImage::SharedPtr msg);

  RateLimiter limiter_;
  rclcpp::Subscription<sensor_msgs::msg::CompressedImage>::SharedPtr subscription_;
};

}  // namespace ros2_echo_graphic
