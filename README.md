# echo-graphic

`echo-graphic` is a ROS 2 terminal viewer for common sensor topics. It renders images directly in the terminal and provides compact text visualizations for scans and joint states.

## Supported Topics

- `sensor_msgs/msg/Image`
- `sensor_msgs/msg/CompressedImage`
- `sensor_msgs/msg/LaserScan`
- `sensor_msgs/msg/JointState`

## Requirements

- ROS 2 Jazzy or newer
- `colcon`
- `chafa` for image rendering

```bash
sudo apt update
sudo apt install python3-colcon-common-extensions chafa
```

## Install

### APT

APT packages are not available yet. Until this package is released through the ROS build farm, install it from source.

### From Source

From a ROS 2 workspace:

```bash
source /opt/ros/$ROS_DISTRO/setup.bash
colcon build --packages-select ros2_echo_graphic
source install/setup.bash
```

If this package is not in a workspace yet:

```bash
mkdir -p ~/ros2_ws/src
cd ~/ros2_ws/src
git clone https://github.com/codevilot/echo-graphic.git
cd ~/ros2_ws
source /opt/ros/$ROS_DISTRO/setup.bash
colcon build --packages-select ros2_echo_graphic
source install/setup.bash
```

## Usage

View a raw image topic:

```bash
ros2 run ros2_echo_graphic echo-graphic /camera/image_raw --fps 10
```

View a compressed image topic:

```bash
ros2 run ros2_echo_graphic echo-graphic /camera/image_raw/compressed --fps 10
```

View a laser scan:

```bash
ros2 run ros2_echo_graphic echo-graphic /scan --fps 10
```

View joint states:

```bash
ros2 run ros2_echo_graphic echo-graphic /joint_states --fps 10
```

If the topic is not active yet, `echo-graphic` waits instead of exiting. A waiting message is printed every 10 seconds.

## Mock Publishers

Use the built-in mock publishers for local testing.

Raw image:

```bash
ros2 run ros2_echo_graphic echo-graphic-mockup image
ros2 run ros2_echo_graphic echo-graphic /camera/image_raw
```

Compressed image:

```bash
ros2 run ros2_echo_graphic echo-graphic-mockup compressed_image
ros2 run ros2_echo_graphic echo-graphic /camera/image_raw/compressed
```

Laser scan:

```bash
ros2 run ros2_echo_graphic echo-graphic-mockup scan
ros2 run ros2_echo_graphic echo-graphic /scan
```

Joint state:

```bash
ros2 run ros2_echo_graphic echo-graphic-mockup joint_states
ros2 run ros2_echo_graphic echo-graphic /joint_states
```

Mock publishers accept `--topic` and `--hz`:

```bash
ros2 run ros2_echo_graphic echo-graphic-mockup scan --topic /debug_scan --hz 5
```

## Notes

Fast DDS shared-memory transport can emit noisy `RTPS_TRANSPORT_SHM` messages on some machines. The executables default `FASTDDS_BUILTIN_TRANSPORTS` to `UDPv4` unless the variable is already set by the user.

## Release

This repository is ready for source builds with `colcon`. A ROS build farm release requires a bloom release repository and rosdistro PR, which should be done after the GitHub repository is published and versioned.
