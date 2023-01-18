// ---------------------------------
// Function Implementations: Motion
// ---------------------------------


void moveDown() {
  // Clear Halt Flag
  been_halted = false;

  // Set valves to move DOWN
  P1.writeDiscrete(LOW,1,5);   //Turn slot 1 channel 4 on
  P1.writeDiscrete(HIGH,1,6);  //Turn slot 1 channel 5 off
}


void moveUp() {
  // Clear Halt Flag
  been_halted = false;

  // Set valves to move UP
  P1.writeDiscrete(LOW,1,6);   //Turn slot 1 channel 5 off
  P1.writeDiscrete(HIGH,1,5);  //Turn slot 1 channel 4 on
}


void set_flow_control_valve(bool state)
{
  //Input 'state' sets the speed of the press
  //by opening/closing the flow control valve.
  //High for fast, LOW for slow
  P1.writeDiscrete(state,1,7); //Set the flow control valve to state
}


void halt() {

  if (!been_halted)
  {
    Serial.println("Recieved HALT command. Setting MoveUp for # ms.");
    moveUp();
  
    delay(50); // Pause n ms
    Serial.println("Commanding HALT (both valves closed.");
  }
  
  P1.writeDiscrete(LOW,1,5);   //Turn slot 1 channel 4 off
  P1.writeDiscrete(LOW,1,6);   //Turn slot 1 channel 5 off

  // Set Flag that halt has been called
  been_halted = true;
}


void set_fork_power(bool state)
{
  P1.writeDiscrete(state, 1, 4);
}
