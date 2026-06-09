# Release Notes

## GitHub source release

1. Update `package.xml` version.
2. Commit the version change.
3. Create and push a matching tag:

```bash
git tag -a v0.1.0 -m "echo-graphic v0.1.0"
git push origin main v0.1.0
```

The `release` GitHub Action creates a GitHub Release and attaches a source archive.

## ROS build farm release

Official apt distribution through the ROS build farm requires bloom and a rosdistro pull request.

Prerequisites on Ubuntu/ROS 2 Jazzy:

```bash
sudo apt install python3-bloom python3-rosdep fakeroot debhelper dh-python
sudo rosdep init
rosdep update
```

Then run bloom against this upstream repository:

```bash
bloom-release \
  --rosdistro jazzy \
  --track jazzy \
  --new-track \
  ros2_echo_graphic
```

Use this upstream repository when bloom prompts for it:

```text
https://github.com/codevilot/echo-graphic.git
```

A typical release repository name is:

```text
https://github.com/codevilot/echo-graphic-release.git
```

Bloom will generate release branches and open a rosdistro pull request. The package becomes available through apt after the ROS build farm imports, builds, and syncs the release.
