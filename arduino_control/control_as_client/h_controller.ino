// ------------------
// Controller
// ------------------


void controller(float current_posn) {


  // ------------------------
  // Manual Control Override
  // ------------------------
  
  bool mswitch_up  = P1.readDiscrete(1,1);
  bool mswitch_dwn = P1.readDiscrete(1,2);
  bool override_lockout = (last_override + override_timeout) > millis();

  if (mswitch_up || mswitch_dwn || override_lockout) {
    set_flow_control_valve(LOW);
    set_remote_indicator(false);
    remoteMotionEnabled = false;
    if ( mswitch_up == true && mswitch_dwn == false ) {
      last_override = millis();
      moveUp();
    }
    else if ( mswitch_up == false && mswitch_dwn == true ) {
      last_override = millis();
      moveDown();
    }
    else {
      halt();
      target_posn = current_posn; // Ensure fail's safe
    } 
  }



  // -----------------------------
  // Remote Input ~ Serial or ROS
  // -----------------------------

  if (Serial.available() && override_lockout == true) {
    Serial.println("--- !! Remote Control Lockout. Please wait 5-seconds !! ---");
    clearSerialBuffer();
  }
  
  else if (Serial.available() && ros_enabled == false && override_lockout == false) {
    
    // Serial Client Input Position of unit: [mm]
    target_posn = Serial.parseFloat() * 0.001;
    clearSerialBuffer();

    // Soft Stop Limits
    if      (target_posn > maxStrokeSoft) target_posn = maxStrokeSoft;
    else if (target_posn < minStrokeSoft) target_posn = minStrokeSoft;

    // Set the direction of motion
    if (current_posn < target_posn) directionOfMotion = false;  // down
    else                            directionOfMotion = true;   // up
     
    // Serial Feedback
    Serial.print("Set New Target Position: ");
    Serial.println(target_posn);
    
    // Enable Motion
    remoteMotionEnabled = true;
    remoteTargetAchieved = false;
  }

  else if (ros_enabled == true && override_lockout == false) {
    // Serial Client Input Position of unit: [meter]
    target_posn = last_ros_joint_command;
  }

  if (Serial.available() && ros_enabled == true) {
    Serial.println("--- !! Serial Control Lockout. Only accepting ROS Control. !! ---");
    clearSerialBuffer();
  }



  // ---------------------------
  // Actuation of Remote Motion
  // ---------------------------

  if (remoteTargetAchieved == false && remoteMotionEnabled && override_lockout == false) {
    
    // Check if target position achieved
    if      (directionOfMotion == false && current_posn >= target_posn) remoteTargetAchieved = true;  // overshoot moving down              
    else if (directionOfMotion == true  && current_posn <= target_posn) remoteTargetAchieved = true;  // overshoot moving up
    
    // Actuate Control given Target Achieved
    if (remoteTargetAchieved == true) {
      halt();
      set_flow_control_valve(LOW);  // default back to slow speed
      target_posn = current_posn;   // fail safe
    }
    else if (directionOfMotion == false)   moveDown();
    else if (directionOfMotion == true)    moveUp();
    
    // Set speed of press motion
    if(directionOfMotion == false && current_posn > target_posn - motionBuffer) // moving down
    {
      set_flow_control_valve(LOW);
    }
    else 
    {
      set_flow_control_valve(HIGH);
    }

    if(directionOfMotion == true && remoteTargetAchieved == false) // moving up
    {
      set_flow_control_valve(HIGH);
    }
    else if (directionOfMotion == true) set_flow_control_valve(LOW);
  }
}
