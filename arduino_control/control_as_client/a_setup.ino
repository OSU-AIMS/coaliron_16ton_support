// ---------
// Setup: 
// ---------

#include <Arduino.h>

// P1AM-100 Special Functions
#include <P1AM.h>

// Communication Interfaces
#include <SPI.h>
#include <Ethernet.h>

// Use the TCP version of rosserial_arduino
#define ROSSERIAL_ARDUINO_TCP

// Kinematic Calculations (pos/vel/accel)
#include <RunningAverage.h>/

// ROS
#include <ros.h>
#include <std_msgs/Header.h>
#include <sensor_msgs/JointState.h>
//#include <industrial_msgs/RobotStatus.h>



// ----------------------
// Function Declarations
// ----------------------

// Motion
void moveDown();
void moveUp();
void halt();

// Position Feedback
void report_serial_position();
float posn_incr2inch();
float posn_incr2meter();

// ROS & Network Interfaces
void setup_network();
void setup_ros();
void update_ros_robot_status();
void update_ros_joint_states();
void clearSerialBuffer();

// Controller
void controller();



// ----------------------
// Configuration
// ----------------------

// Hardware Settings
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };

// ROS Master Information 
// Server host's port to talk with Arduino Client. NOT ROS port 11311.
IPAddress rosmaster(10,10,10,52);
const uint16_t serverPort = 11411;

// Manual Override
const unsigned long override_timeout = 5000; // milliseconds
unsigned long last_override = 0;



// ----------------------
// ROS Definitions
// ----------------------

// ROS Node Setup (max one node allowed)
ros::NodeHandle nh;

std_msgs::Header joint_state_header;
std_msgs::Header robot_status_header;

sensor_msgs::JointState joint_state_msg;
//industrial_msgs::RobotStatus robot_status_msg;

ros::Publisher pub_joint_states("joint_states", &joint_state_msg);
//ros::Publisher pub_robot_status("robot_status", &robot_status_msg);



// ---------------------
// Feedback Definitions 
// ---------------------





// ----------------------
// Control Definitions
// ----------------------

// Calibration Data
const int increment_top_posn = 2034;
const float calibration_inch_per_increment = 0.00240449027863;  
const float calibration_meter_per_increment = 0.0000610740530772;  

//Stroke range meters
const float maxStrokeSoft = 0.1651;
const float minStrokeSoft = 0.0;
const float maxStrokeHard = 0.20294907837554;   // not currently used by control
const float minStrokeHard = 0.0;                // not currently used by control

//Target Position
bool remoteMotionEnabled = false;
bool directionOfMotion;                  // false = down, true = up
float target_posn = 0;                   // Initialize goal to zero for safety
bool remoteTargetAchieved = false;

//Timer for position update over serial
const int period = 500;                  //Time between serial monitor updates [ms]
unsigned long time_now = 0;



// ----------------------
// Setup Function
// ----------------------

void setup() {

  // Initialize Comm Sockets
  Serial.begin(115200);
  Ethernet.begin(mac);

  // Setup Functions
  setup_network();
  setup_ros();
  
  while (!P1.init()) {
    delay(100); //Wait for Modules to Sign on  
  }

  pinMode(LED_BUILTIN, OUTPUT);
}
