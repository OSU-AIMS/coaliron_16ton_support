// ----------
// Main Loop
// ----------


void loop()
{
  
  // Read Sensors
  int current_posn_incr = P1.readAnalog(2, 1);
  float current_posn_meter = posn_incr2meter(current_posn_incr);
  bool current_fork_state = get_fork_state();
  
  // Serial Interface
  report_serial_position();
  
  // ROS Interface
  if (nh.connected() && ros_enabled) {

    // Set ROS Indicator Light = ON
    set_remote_indicator(true);

    // Update Robot Status Topic
    

    // Update Sensor Topics
    update_ros_joint_states(current_posn_meter);
    update_ros_fork_state(current_fork_state);
  }
  else {
    // Set ROS Indicator Light = OFF
    set_remote_indicator(false);
  }
  nh.spinOnce();
  
  // Motion Control
  controller(current_posn_meter);
  
}

// EOF
