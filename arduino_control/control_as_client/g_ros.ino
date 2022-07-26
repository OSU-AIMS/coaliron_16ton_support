// ------------------------------
// Function Implementations: ROS
// ------------------------------


void setup_ros() {
  
  // Set the connection to rosserial socket server
  nh.getHardware() -> setConnection(rosmaster, serverPort);
  nh.initNode();

  nh.advertise(pub_joint_states);
  nh.advertise(pub_fork_state);
  nh.advertise(pub_temp_alarm1_state);
  nh.advertise(pub_press_power_switch_state);
  nh.advertise(pub_current_temp_degrees);
//  nh.advertise(pub_robot_status);/

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


void update_ros_current_temp_degrees(float current_temp_degrees) {

  // Message Header
  current_temp_degrees_header.stamp = nh.now();
  
  // Assemble & Update Message
  current_temp_degrees_msg.header   = current_temp_degrees_header;
  current_temp_degrees_msg.temperature = current_temp_degrees;
  current_temp_degrees_msg.variance = 0;

  pub_current_temp_degrees.publish( &current_temp_degrees_msg );
}


void update_ros_fork_state(bool &state) {

  // Update message
  fork_state_msg.data = state;

  // Publish message
  pub_fork_state.publish( &fork_state_msg );
  
}


void update_ros_temp_alarm1_state(bool &state) {

  // Update message
  temp_alarm1_state_msg.data = state;

  // Publish message
  pub_temp_alarm1_state.publish( &temp_alarm1_state_msg );
  
}


void update_ros_press_power_switch_state(bool &state) {

  // Update message
  press_power_switch_state_msg.data = state;

  // Publish message
  pub_press_power_switch_state.publish( &press_power_switch_state_msg );
  
}
