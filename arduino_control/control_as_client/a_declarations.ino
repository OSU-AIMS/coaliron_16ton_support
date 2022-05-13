// ----------------------
// Function Declarations
// ----------------------


// Setup Declarations
void setup_network();
void setup_ros();

// Motion
void moveDown();
void moveUp();
void halt();

// Feedback
void report_serial_position();
float posn_incr2inch();
float posn_incr2meter();
void set_remote_indicator();

// ROS & Network Interfaces
void update_ros_robot_status();
void update_ros_joint_states();
void clearSerialBuffer();

// Controller
void controller();
