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

// ROS
#include <ros.h>
#include <sensor_msgs/JointState.h>



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
void clearSerialBuffer();

// Controller
void masterloop();



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

// ROS Node Setup
ros::NodeHandle nh;

sensor_msgs::JointState joint_state_msg;
ros::Publisher pub_joint_states("joint_states", &joint_state_msg);



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
const float maxStrokeHard = 0.20294907837554;
const float minStrokeHard = 0.0;

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
