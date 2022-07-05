// -----------------------------------
// Function Implementations: Feedback
// -----------------------------------


void report_serial_position() {
  
  if(millis() - time_now > period) {
    time_now = millis();

    int inputCounts = P1.readAnalog(2, 1); //Read analog data from slot 1 channel 2 of the analog input module
    
    Serial.print("Position from TOP: ");
    Serial.print("     incr: ");
    Serial.print(P1.readAnalog(2, 1));
    Serial.print("     inch: ");
    Serial.print(posn_incr2inch(inputCounts));
    Serial.print("     mm: ");
    Serial.print(posn_incr2meter(inputCounts)*1000);
    Serial.println("");
  }
}


float posn_incr2inch(const int inputCounts) {
  return (inputCounts - increment_top_posn) * calibration_inch_per_increment;  //arduino's are slow at division
}


float posn_incr2meter(const int inputCounts) {
  return (inputCounts - increment_top_posn) * calibration_meter_per_increment;  //arduino's are slow at division
}


bool get_fork_state()
{
  return P1.readDiscrete(1, 5);
}


void set_remote_indicator(const bool setLight) {
  if (setLight) { digitalWrite(LED_BUILTIN, HIGH); }
  else          { digitalWrite(LED_BUILTIN, LOW);  }
}
