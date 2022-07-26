// -----------------------------------
// Function Implementations: Feedback
// -----------------------------------


void report_serial(const int incr_posn, const int incr_temp1) {
  
  if(millis() - time_now > period) {
    time_now = millis();

    Serial.print("POSITION from TOP: ");
    Serial.print("     incr: ");
    Serial.print(incr_posn);
    Serial.print("     inch: ");
    Serial.print(posn_incr2inch(incr_posn));
    Serial.print("     (input) mm: ");
    Serial.print(posn_incr2meter(incr_posn)*1000);

    Serial.print("     TEMPERATURE 1. incr: ");
    Serial.print(incr_temp1);
    Serial.print("     deg C: ");
    Serial.print(temperature_count2degree(incr_temp1), 2);
    Serial.println("");
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
  return ((inputCounts * calibration_degree_per_count) + 150.0);
}

bool get_temperature1_alarm1_state() {
  return P1.readDiscrete(1, 3);
}

void set_remote_indicator(const bool setLight) {
  if (setLight) { digitalWrite(LED_BUILTIN, HIGH); }
  else          { digitalWrite(LED_BUILTIN, LOW);  }
}
