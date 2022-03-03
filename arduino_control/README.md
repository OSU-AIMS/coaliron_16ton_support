# Arduino Control

The `arduino_control` directory is a Arduino Sketchbook. 


## Provided Code

| Arduino Sketch | Description |
| -------------- | ----------- |
| P1AM_network_test | Sample demonstration and basic connection test for establishing an TCP/IP connection to the network and connecting to a ROS master running at a defined endpoint IP address. | 



## ReProgramming the P1AM-100

To reprogram the P1AM-100 you must perform the below setup steps..

1. Setup the Arduino Sketchbook (following section)
2. Install programming support for the P1AM-100 platform
   - Start the Arduino IDE and select File > Preferences
   - Enter `https://raw.githubusercontent.com/facts-engineering/facts-engineering.github.io/master/package_productivity-P1AM-boardmanagermodule_index.json` into the Additional Board Manager URLs field. You can add multiple URLs, separating them with commas.
   - Open the Boards Manager from Tools > Board > Boards Manager
   - Type `P1AM` into the search box and install the P1AM-100 platform
   - Select Tools > Board > P1AM-100
   - Go to Tools > Port and select the COM Port for your P1AM-100
3. Compile
   - Compile via Arduino IDE (suggested)
   - Compile via `catkin_tools`
4. Upload
   - via Arduino IDE (suggested)
   - via Arduino IDE CLI



### Arduino Sketchbook libraries

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

The P1AM libary is included as a submodule in this Sketchbook. Some git-clients will automatically load submodules, but you may need to perform this manually as shown below.

```bash
git submodule init
git submodule update
```



## Hardware

Hardware specific to this system is included below with links to the vendors documentation.

| [P1AM-100](https://cdn.automationdirect.com/static/specs/p1amspecs.pdf) | [P1AM-ETH](https://cdn.automationdirect.com/static/specs/p1ameth.pdf) |
| -------- | -------- |
| <img src="https://facts-engineering.github.io/modules/P1AM-100/P1AM-100_STRAIGHTON.png" width="100"> | <img src="https://facts-engineering.github.io/modules/P1AM-ETH/P1AM-ETH_STRAIGHTON.png" width="100"> |