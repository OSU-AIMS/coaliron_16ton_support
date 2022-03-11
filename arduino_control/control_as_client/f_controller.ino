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
    if ( mswitch_up == true && mswitch_dwn == false ) {
      last_override = millis();
      moveUp();
    }
    else if ( mswitch_up == false && mswitch_dwn == true ) {
      last_override = millis();
      moveDown();
    }
    else {
      remoteMotionEnabled = false;
      target_posn = current_posn; // Ensure fail's safe
      halt();
    }
    
  }



  // -----------------------------
  // Remote Input ~ Serial or ROS
  // -----------------------------

  if (Serial.available() && override_lockout == false) {
    
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
  else if (Serial.available() && override_lockout == true) {
    Serial.println("--- !! Remote Control Lockout. Please wait 5-seconds !! ---");
    clearSerialBuffer();
  }

  //else if (_ADD_ROS_CHECK_) {
  //  //ADD ROS CODE HERE
  //}



  // ---------------------------
  // Actuation of Remote Motion
  // ---------------------------

  if (remoteTargetAchieved == false && remoteMotionEnabled && override_lockout == false) {
    
    // Check if target position achieved
    if      (directionOfMotion == false && current_posn >= target_posn) remoteTargetAchieved = true;  // overshoot moving down              
    else if (directionOfMotion == true  && current_posn <= target_posn) remoteTargetAchieved = true;  // overshoot moving up
    
    // Actuate if target not met
    if (remoteTargetAchieved == true) {
      halt();
      target_posn = current_posn;   // fail safe
    }
    else if (directionOfMotion == false)   moveDown();
    else if (directionOfMotion == true)    moveUp();
    
  }
}
