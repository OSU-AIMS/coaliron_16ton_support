// ----------------------
// Function Declarations
// ----------------------


// Setup Declarations
void setup_network();
void setup_ros();

// Feedback Position
void report_serial_position();
void report_serial_temperature();
float posn_incr2inch();
float posn_incr2meter();

// Feedback Sensors
bool get_fork_state();
bool get_press_power_switch_state();
float temperature_count2degree();
bool get_temperature1_alarm1_state();

// External Indicators
void set_remote_indicator();

// ROS & Network Interfaces
void update_ros_robot_status();
void update_ros_joint_states();
void update_ros_fork_state();
void update_ros_temperature1();
void update_ros_temperature1_alarm1_state();
void update_ros_press_power_switch_state();
void clearSerialBuffer();

// Motion
void moveDown();
void moveUp();
void halt();

// Controller
void controller();
void set_fork_power(bool state);
