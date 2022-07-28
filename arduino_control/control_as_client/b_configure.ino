// ------------------
// ROS Configuration
// ------------------


// Hardware Settings
const char P1_08ADL_1_CONFIG[] = { 0x40, 0x07 }; 	 // enable all ports (default)
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED }; // NIC mac address

// ROS Master Information 
// Server host's port to talk with Arduino Client. NOT ROS port 11311.
IPAddress rosmaster(10,10,10,52);
const uint16_t serverPort = 11411;

// Manual Override
const unsigned long override_timeout = 5000; // milliseconds
unsigned long last_override = 0;



// ----------------------
// Control Definitions
// ----------------------


// Calibration Data - Position Sensor
const int increment_top_posn = 2034;
const float calibration_inch_per_increment = 0.00240449027863;  
const float calibration_meter_per_increment = 0.0000610740530772;

// Calibration Data - Temperature Sensor
const float analog_input_counts = 8191;  //13-bit P1-08ADL-1 0-20mA input module
const int temp_sense_min = 150;  // deg. C
const int temp_sense_max = 1000; // deg. C
const float calibration_degree_per_count = (temp_sense_max - temp_sense_min) / analog_input_counts;

//Stroke range meters
const float maxStrokeSoft = 0.1651;
const float minStrokeSoft = 0.0;
const float maxStrokeHard = 0.20294907837554;   // not currently used by control
const float minStrokeHard = 0.0;                // not currently used by control

//Remote Interface
bool ros_enabled = false;
float last_ros_joint_command = 0;        // Initialize goal to zero for safety

//Position control
const float motionBuffer = 0.012;

//Target Position
bool remoteMotionEnabled = false;
bool directionOfMotion;                  // false = down, true = up
float target_posn = 0;                   // Initialize goal to zero for safety
bool remoteTargetAchieved = false;

//Timer for position update over serial
const int period = 500;                  //Time between serial monitor updates [ms]
unsigned long time_now = 0;
