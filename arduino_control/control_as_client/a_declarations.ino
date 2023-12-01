// ----------------------
// Function Declarations
// ----------------------


// Setup Declarations
void setup_network();
void setup_ros();

// Conversions
float posn_incr2inch();
float posn_incr2meter();
float temperature_count2degree();

// Feedback
void report_serial();
bool get_fork_state();
bool get_press_power_switch_state();
bool get_temperature1_alarm1_state();

// External Indicators
void set_remote_indicator();

// ROS & Network Interfaces
void cb_joint_command(const std_msgs::Float64);
void cb_induction_coil_command(const std_msgs::Bool);
void update_ros_robot_status();
void update_ros_joint_states();
void update_ros_fork_state();
void update_ros_temperature1();
void update_ros_temperature1_alarm1_state();
void update_ros_press_power_switch_state();
void clearSerialBuffer();

// Motion
bool been_halted = true;
void moveDown();
void moveUp();
void halt();
void set_flow_control_valve(bool state);
bool tempFlowValveState = false;

// Controller
void controller();
void set_fork_power(bool state);
void set_induction_power(bool state);
