// ----------
// Main Loop
// ----------


void loop()
{
  
  // Read Sensors
  int current_posn_incr = P1.readAnalog(2, 1);
  int current_temp_counts = P1.readAnalog(2, 3);
  float current_p1 = posn_incr2meter(current_posn_incr);
  float current_t1 = temperature_count2degree(current_temp_counts);
  bool current_fork_state = get_fork_state();
  bool current_t1_a1_state = get_temperature1_alarm1_state();
  bool current_press_power_switch_state = get_press_power_switch_state();
  
  // Serial Interface
  report_serial_position();
  report_serial_temperature(current_t1);
  
  // ROS Interface
  if (nh.connected()) {

    // Set ROS Indicator Light = ON
    set_remote_indicator(true);

    // Update Robot Status Topic
    

    // Update Sensor Topics
    update_ros_joint_states(current_p1);
    update_ros_fork_state(current_fork_state);
    update_ros_press_power_switch_state(current_press_power_switch_state);
    update_ros_temperature1_alarm1_state(current_t1_a1_state);
    update_ros_temperature1(current_t1);
  }
  else {
    // Set ROS Indicator Light = OFF
    set_remote_indicator(false);
  }
  nh.spinOnce();
  
  // Motion Control
  controller(current_p1);
  
}

// EOF
