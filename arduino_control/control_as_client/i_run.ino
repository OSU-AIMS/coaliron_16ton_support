// ----------
// Main Loop
// ----------


void loop()
{
  
  // Read State
  int current_posn_incr = P1.readAnalog(2, 1);
  float current_posn_meter = posn_incr2meter(current_posn_incr);
  
  // Serial Interface
  report_serial_position();
  
  // ROS Interface
  if (nh.connected()) {

    // Set ROS Indicator Light = ON
    set_remote_indicator(true);

    // Update Robot Status Topic
    

    // Update Joint States Topic
    update_ros_joint_states(current_posn_meter);
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
