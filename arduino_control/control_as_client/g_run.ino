
void loop()
{

  // Time (dt in seconds)
//  unsigned int cycles = TCNT1;
//  TCNT1 = 0; // Reset Clock
//  float dt  = (float)cycles * 0.00000002083333333333; 

  float current_time = millis();
  float dt = current_time - last_time;
  float last_time = current_time;
  cache_dt.addValue(dt);


  // Position
  int   current_posn_incr   = P1.readAnalog(2, 1);
  float current_posn_meter  = posn_incr2meter(current_posn_incr);
  float dx                  = current_posn_meter - cache_dx.getValue(cache_dx.getCount());
  cache_dx.addValue(dx);


  // Velocity
  float dxdt = cache_dx.getFastAverage() / cache_dt.getFastAverage();
  cache_dxdt.addValue(dxdt);


  // Acceleration
  float dxddt = (dxdt - cache_dx.getValue(cache_dxdt.getCount())) / cache_dt.getFastAverage();
  cache_dxddt.addValue(dxddt);

  
  // Serial Interface
  report_serial_position();

  
  // ROS Interface
  if (nh.connected()) {
    update_ros_joint_states(current_posn_meter, dxdt, dxddt);
  }
  nh.spinOnce();

  
  // Motion Control
  controller(current_posn_meter);
}

// EOF
