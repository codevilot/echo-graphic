#pragma once

#include <chrono>
#include <deque>
#include <map>
#include <string>

#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/joint_state.hpp"

#include "echo_graphic/rate_limiter.hpp"

namespace echo_graphic
{

class JointStateViewer : public rclcpp::Node
{
public:
  JointStateViewer(const std::string & topic_name, const std::string & topic_type, double fps);

private:
  void callback(const sensor_msgs::msg::JointState::SharedPtr msg);
  void update_history(const sensor_msgs::msg::JointState & msg, size_t joint_count);
  std::string format_hz() const;

  std::string topic_name_;
  RateLimiter limiter_;
  rclcpp::Subscription<sensor_msgs::msg::JointState>::SharedPtr subscription_;
  std::map<std::string, std::deque<double>> position_history_;
  std::deque<std::chrono::steady_clock::time_point> message_times_;
};

}  // namespace echo_graphic
