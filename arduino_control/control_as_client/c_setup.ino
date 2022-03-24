// -------------------
// ROS Initialization
// -------------------


// ROS Node Setup (max one node allowed)
ros::NodeHandle nh;

std_msgs::Header joint_state_header;
std_msgs::Header robot_status_header;

sensor_msgs::JointState joint_state_msg;
//industrial_msgs::RobotStatus robot_status_msg;

ros::Publisher pub_joint_states("joint_states", &joint_state_msg);
//ros::Publisher pub_robot_status("robot_status", &robot_status_msg);



// -------------------
// Setup
// -------------------


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

  // Exteneral Remote Control Indicator
  pinMode(LED_BUILTIN, OUTPUT);

  // Set Remote Control Indicator to OFF
  set_remote_indicator(false);
}
