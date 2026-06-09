#pragma once

#include <string>

#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/image.hpp"

#include "ros2_echo_graphic/rate_limiter.hpp"

namespace ros2_echo_graphic
{

class ImageViewer : public rclcpp::Node
{
public:
  ImageViewer(const std::string & topic_name, const std::string & topic_type, double fps);

private:
  void callback(const sensor_msgs::msg::Image::SharedPtr msg);
  std::vector<uint8_t> to_rgb(const sensor_msgs::msg::Image & msg) const;

  RateLimiter limiter_;
  rclcpp::Subscription<sensor_msgs::msg::Image>::SharedPtr subscription_;
};

}  // namespace ros2_echo_graphic
