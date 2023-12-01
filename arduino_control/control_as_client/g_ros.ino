// ------------------------------
// Function Implementations: ROS
// ------------------------------


void setup_ros() {
  
  // Set the connection to rosserial socket server
  nh.getHardware() -> setConnection(rosmaster, serverPort);
  nh.initNode();

  nh.advertise(pub_joint_states);
  nh.advertise(pub_fork_state);
  nh.advertise(pub_press_power_switch_state);
  nh.advertise(pub_temperature1_alarm1_state);
  nh.advertise(pub_temperature1);
//  nh.advertise(pub_robot_status);

  nh.subscribe(sub_induction_coil_command);
  nh.subscribe(sub_joint_command);
}


void cb_induction_coil_command(const std_msgs::Bool &msg) {

  // Set Coil Power State
  set_induction_power(msg.data);
}


void cb_joint_command(const std_msgs::Float64& msg) {

  // Check if motor powered on
  if( get_press_power_switch_state() ) {
    
    // Extract data from message
    last_ros_joint_command = msg.data;
  
    // Lookup Current Position
    float current_posn = posn_incr2meter(P1.readAnalog(2, 1));
  
    // Soft Stop Limits
    if      (last_ros_joint_command > maxStrokeSoft) last_ros_joint_command = maxStrokeSoft;
    else if (last_ros_joint_command < minStrokeSoft) last_ros_joint_command = minStrokeSoft;
  
    // Set the direction of motion
    if (current_posn < last_ros_joint_command) directionOfMotion = false;  // down
    else                                       directionOfMotion = true;   // up
  
    // Serial Feedback
    Serial.print("Set New Target Position: ");
    Serial.println(last_ros_joint_command, 3);
  
    // Enable Motion
    remoteMotionEnabled = true;
    remoteTargetAchieved = false;
  }
  else {
    Serial.println("ROS joint command requested, but discarded.");
    nh.loginfo("ROS joint command requested, but discarded.");    
  }
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


void update_ros_fork_state(bool &state) {

  // Update message
  fork_state_msg.data = state;

  // Publish message
  pub_fork_state.publish( &fork_state_msg );
  
}


void update_ros_temperature1(float &current_temp_degrees) {

  // Message Header
  temperature_header.stamp = nh.now();
  
  // Assemble & Update Message
  temperature1_msg.header      = temperature_header;
  temperature1_msg.temperature = current_temp_degrees;
  temperature1_msg.variance    = 0;

  pub_temperature1.publish( &temperature1_msg );
}


void update_ros_temperature1_alarm1_state(bool &state) {

  // Update message
  temperature1_alarm1_state_msg.data = state;

  // Publish message
  pub_temperature1_alarm1_state.publish( &temperature1_alarm1_state_msg );
  
}


void update_ros_press_power_switch_state(bool &state) {

  // Update message
  press_power_switch_state_msg.data = state;

  // Publish message
  pub_press_power_switch_state.publish( &press_power_switch_state_msg );
  
}
