// -------------------
// ROS Initialization
// -------------------


// ROS Node Setup (max one node allowed)
ros::NodeHandle nh;

std_msgs::Header joint_state_header;
std_msgs::Header robot_status_header;

sensor_msgs::JointState joint_state_msg;
std_msgs::Bool fork_state_msg;
std_msgs::Float64 joint_command;
//industrial_msgs::RobotStatus robot_status_msg;

ros::Publisher pub_joint_states("joint_states", &joint_state_msg);
ros::Publisher pub_fork_state("fork_state", &fork_state_msg);
//ros::Publisher pub_robot_status("robot_status", &robot_status_msg);

ros::Subscriber<std_msgs::Float64> sub_joint_command("joint_command", cb_joint_command);


// -------------------
// Setup
// -------------------


void setup() {

  // Initialize Serial Comm Sockets
  Serial.begin(115200);
  Serial.println("Setup Process Complete");

  // Setup Network for ROS (if requested)
  pinMode(SWITCH_BUILTIN, INPUT);
  bool enable_network = digitalRead(SWITCH_BUILTIN);

  if (enable_network) {
    Serial.println("Setup Configuration: Network enabled. Will now attempt to connect to network");
    Ethernet.begin(mac);
    setup_network();
    ros_enabled = true;
  }
  else {
    ros_enabled = false;
  }

  // Setup ROS handles
  setup_ros();
    
  while (!P1.init()) {
    delay(100); //Wait for Modules to Sign on  
  }

  // Initialize Sensors
  set_fork_power(true);

  // Exteneral Remote Control Indicator
  pinMode(LED_BUILTIN, OUTPUT);

  // Set Remote Control Indicator to OFF
  set_remote_indicator(false);

  // Report Setup Success
  Serial.println("Setup Process Complete");
}
