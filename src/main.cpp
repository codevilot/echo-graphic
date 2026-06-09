#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

#include "rclcpp/rclcpp.hpp"

#include "echo_graphic/compressed_image_viewer.hpp"
#include "echo_graphic/dds_transport.hpp"
#include "echo_graphic/image_viewer.hpp"
#include "echo_graphic/joint_state_viewer.hpp"
#include "echo_graphic/lidar_viewer.hpp"
#include "echo_graphic/topic_discovery.hpp"

namespace
{

struct CliOptions
{
  std::string topic_name;
  double fps{10.0};
};

void print_usage()
{
  std::cerr << "Usage: ros2 run echo_graphic echo-graphic <topic_name> [--fps <fps>]\n";
}

CliOptions parse_args(int argc, char ** argv)
{
  CliOptions options;
  std::vector<std::string> args;
  for (int i = 1; i < argc; ++i) {
    args.emplace_back(argv[i]);
  }

  for (size_t i = 0; i < args.size(); ++i) {
    if (args[i] == "--fps") {
      if (i + 1 >= args.size()) {
        throw std::invalid_argument("--fps requires a value");
      }
      options.fps = std::stod(args[++i]);
    } else if (options.topic_name.empty()) {
      options.topic_name = args[i];
    } else {
      throw std::invalid_argument("unexpected argument: " + args[i]);
    }
  }

  if (options.topic_name.empty()) {
    throw std::invalid_argument("topic_name is required");
  }
  return options;
}

bool is_image(const std::string & topic_type)
{
  return topic_type == "sensor_msgs/msg/Image" || topic_type == "sensor_msgs/Image";
}

bool is_compressed_image(const std::string & topic_type)
{
  return topic_type == "sensor_msgs/msg/CompressedImage" || topic_type == "sensor_msgs/CompressedImage";
}

bool is_laser_scan(const std::string & topic_type)
{
  return topic_type == "sensor_msgs/msg/LaserScan" || topic_type == "sensor_msgs/LaserScan";
}

bool is_joint_state(const std::string & topic_type)
{
  return topic_type == "sensor_msgs/msg/JointState" || topic_type == "sensor_msgs/JointState";
}

std::shared_ptr<rclcpp::Node> create_viewer(
  const std::string & topic_name,
  const std::string & topic_type,
  double fps)
{
  using echo_graphic::CompressedImageViewer;
  using echo_graphic::ImageViewer;
  using echo_graphic::JointStateViewer;
  using echo_graphic::LidarViewer;

  if (is_image(topic_type)) {
    return std::make_shared<ImageViewer>(topic_name, topic_type, fps);
  }
  if (is_compressed_image(topic_type)) {
    return std::make_shared<CompressedImageViewer>(topic_name, topic_type, fps);
  }
  if (is_laser_scan(topic_type)) {
    return std::make_shared<LidarViewer>(topic_name, topic_type, fps);
  }
  if (is_joint_state(topic_type)) {
    return std::make_shared<JointStateViewer>(topic_name, topic_type, fps);
  }

  throw std::runtime_error(
    "Unsupported type '" + topic_type +
    "'. Supported: sensor_msgs/msg/Image, CompressedImage, LaserScan, JointState.");
}

}  // namespace

int main(int argc, char ** argv)
{
  echo_graphic::configure_default_dds_transport();
  rclcpp::init(argc, argv);

  try {
    const CliOptions options = parse_args(argc, argv);
    auto checker = std::make_shared<rclcpp::Node>("echo_graphic_type_checker");
    const auto topic_type = echo_graphic::find_topic_type(checker, options.topic_name);
    if (!topic_type.has_value()) {
      std::cerr << "[Error] Topic '" << options.topic_name << "' was not found or is not active.\n";
      rclcpp::shutdown();
      return 1;
    }

    rclcpp::spin(create_viewer(options.topic_name, *topic_type, options.fps));
  } catch (const std::invalid_argument & error) {
    std::cerr << "[Error] " << error.what() << "\n";
    print_usage();
    rclcpp::shutdown();
    return 2;
  } catch (const std::exception & error) {
    std::cerr << "[Error] " << error.what() << "\n";
    rclcpp::shutdown();
    return 1;
  }

  rclcpp::shutdown();
  return 0;
}
