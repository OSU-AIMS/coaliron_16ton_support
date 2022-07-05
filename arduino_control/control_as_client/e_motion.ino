// ---------------------------------
// Function Implementations: Motion
// ---------------------------------


void moveDown() {
  P1.writeDiscrete(LOW,1,2);   //Turn slot 1 channel 1 on
  P1.writeDiscrete(HIGH,1,3);  //Turn slot 1 channel 2 off
}


void moveUp() {
  P1.writeDiscrete(HIGH,1,2);  //Turn slot 1 channel 1 on
  P1.writeDiscrete(LOW,1,3);   //Turn slot 1 channel 2 off
}


void halt() {
  P1.writeDiscrete(LOW,1,2);   //Turn slot 1 channel 1 off
  P1.writeDiscrete(LOW,1,3);   //Turn slot 1 channel 2 off
}


void set_fork_power(bool state)
{
  P1.writeDiscrete(state, 1, 4);
}