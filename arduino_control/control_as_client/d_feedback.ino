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
    Serial.print("     (input) mm: ");
    Serial.print(posn_incr2meter(inputCounts)*1000);
    Serial.println("");
  }
}


void report_serial_temperature(const float current_temp_degrees) {
  
  if(millis() - time_now > period) {
    time_now = millis();
    
    Serial.print("Temperature: ");
    Serial.println(current_temp_degrees);
  }
}


float posn_incr2inch(const int inputCounts) {
  return (inputCounts - increment_top_posn) * calibration_inch_per_increment;  //arduino's are slow at division
}


float posn_incr2meter(const int inputCounts) {
  return (inputCounts - increment_top_posn) * calibration_meter_per_increment;  //arduino's are slow at division
}

bool get_fork_state() {
  return P1.readDiscrete(1, 5);
}

bool get_press_power_switch_state() {
  return P1.readDiscrete(1, 6);
}

float temperature_count2degree(const int inputCounts) {
  return (inputCounts * calibration_degree_per_count);
}

bool get_temperature1_alarm1_state() {
  return P1.readDiscrete(1, 3);
}

void set_remote_indicator(const bool setLight) {
  if (setLight) { digitalWrite(LED_BUILTIN, HIGH); }
  else          { digitalWrite(LED_BUILTIN, LOW);  }
}
