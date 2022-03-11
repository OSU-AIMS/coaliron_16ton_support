// ------------------------------
// Function Implementations: ROS
// ------------------------------


void setup_ros() {
  
  // Set the connection to rosserial socket server
  nh.getHardware() -> setConnection(rosmaster, serverPort);
  nh.initNode();

  nh.advertise(pub_joint_states);

}


void update_ros_joint_states(float pos_1) {

  // Message Header
  joint_state_header.stamp = nh.now();
 
  // Build msg components
  char *name[] = {"joint_1"};
  float pos[]  = {pos_1};
  float vel[]  = {0};
  float eff[]  = {0};
  
  // Assemble & Update Message
  joint_state_msg.header   = joint_state_header;
  joint_state_msg.name     = name;
  joint_state_msg.position = pos;
  joint_state_msg.velocity = vel;
  joint_state_msg.effort   = eff;
  
  // Setting lengths
  joint_state_msg.name_length     = 1;
  joint_state_msg.position_length = 1;
  joint_state_msg.velocity_length = 1;
  joint_state_msg.effort_length   = 1;

  pub_joint_states.publish( &joint_state_msg );
}
