#include "echo_graphic/compressed_image_viewer.hpp"

#include <cstdio>
#include <iostream>
#include <stdexcept>

#include "echo_graphic/terminal_utils.hpp"

namespace echo_graphic
{

CompressedImageViewer::CompressedImageViewer(
  const std::string & topic_name,
  const std::string & topic_type,
  double fps)
: Node("echo_graphic_compressed_image_viewer"), limiter_(fps)
{
  if (!command_exists("chafa")) {
    throw std::runtime_error("'chafa' is not installed. Install it with 'sudo apt install chafa'.");
  }

  subscription_ = create_subscription<sensor_msgs::msg::CompressedImage>(
    topic_name, 10, std::bind(&CompressedImageViewer::callback, this, std::placeholders::_1));

  std::cout << "[" << topic_name << "] Starting compressed image stream (type: " << topic_type << ")\n";
}

void CompressedImageViewer::callback(const sensor_msgs::msg::CompressedImage::SharedPtr msg)
{
  if (!limiter_.ready() || msg->data.empty()) {
    return;
  }

  std::cout << "\033[H" << std::flush;
  FILE * pipe = popen("chafa -", "w");
  if (!pipe) {
    RCLCPP_ERROR(get_logger(), "Failed to start chafa.");
    return;
  }

  fwrite(msg->data.data(), 1, msg->data.size(), pipe);
  pclose(pipe);
}

}  // namespace echo_graphic
