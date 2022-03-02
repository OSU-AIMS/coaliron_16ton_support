# Arduino Control

The `arduino_control` directory is a Arduino Sketchbook. 


## Provided Code

| Arduino Sketch | Description |
| -------------- | ----------- |
| P1AM_network_test | Sample demonstration and basic connection test for establishing an TCP/IP connection to the network and connecting to a ROS master running at a defined endpoint IP address. | 



## Arduino Sketchbook libraries

The arduino control code relies upon two libraries.
<br>`ros_lib` provides support for the ROS interface.
<br>`P1AM` provides hardware interface support.


#### ros_lib Library

Build the ros libraries needed by the Arduino controller into this sketchbook. You must build these from your local environment due to ROS verion requirements.
Must have already installed the `ros-<distro>-rosserial` and `ros-<distro>-rosserial-arduino` packages prior to this step.


```bash
cd <package_path>/arduino_control/libraries
rm -rf ros_lib
rosrun rosserial_arduino make_libraries.py .
```


#### P1AM Library:

This package was designed to use AutomationDirect's Productivity Open automation platform, `P1AM-100`. Learn more at the [P1AM website](https://facts-engineering.github.io/).

<br>The P1AM libary is included as a submodule in this Sketchbook. Some git-clients will automatically load submodules, but you may need to perform this manually as shown below.

```bash
git submodule init
git submodule update
```



## Hardware

Hardware specific to this system is included below with links to the vendors documentation.

| [P1AM-100](https://cdn.automationdirect.com/static/specs/p1amspecs.pdf) | [P1AM-ETH](https://cdn.automationdirect.com/static/specs/p1ameth.pdf) |
| -------- | -------- |
| <img src="https://facts-engineering.github.io/modules/P1AM-100/P1AM-100_STRAIGHTON.png" width="100"> | <img src="https://facts-engineering.github.io/modules/P1AM-ETH/P1AM-ETH_STRAIGHTON.png" width="100"> |