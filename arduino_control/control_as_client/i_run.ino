// ----------
// Main Loop
// ----------


void loop()
{
  
  // Read Sensors
  int current_posn_incr = P1.readAnalog(2, 1);
  int current_temp_counts = P1.readAnalog(2, 3);
  float current_posn_meter = posn_incr2meter(current_posn_incr);
  float current_temp_degrees = temp_count2degree(current_temp_counts);
  bool current_fork_state = get_fork_state();
  bool current_temp_alarm1_state = get_temp_alarm1_state();
  bool current_press_power_switch_state = get_press_power_switch_state();
  
  // Serial Interface
  report_serial_position();
  report_serial_temperature(current_temp_degrees);
  
  // ROS Interface
  if (nh.connected()) {

    // Set ROS Indicator Light = ON
    set_remote_indicator(true);

    // Update Robot Status Topic
    

    // Update Sensor Topics
    update_ros_joint_states(current_posn_meter);
    update_ros_fork_state(current_fork_state);
    update_ros_temp_alarm1_state(current_temp_alarm1_state);
    update_ros_press_power_switch_state(current_press_power_switch_state);
    update_ros_current_temp_degrees(current_temp_degrees);
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
