
void loop()
{
  
  // Read State
  int current_posn_incr = P1.readAnalog(2, 1);
  float current_posn_meter = posn_incr2meter(current_posn_incr);
  
  // Serial Interface
  report_serial_position();
  
  // ROS Interface
  if (nh.connected()) {
    update_ros_joint_states(current_posn_meter);
  }
  nh.spinOnce();
  
  // Motion Control
  controller(current_posn_meter);
  
}

// EOF
