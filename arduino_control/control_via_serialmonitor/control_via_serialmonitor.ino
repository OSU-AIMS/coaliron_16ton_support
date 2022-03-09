/*
 * CoalIron Press Control via SerialMonitor
 * 
 * Arduino-code for USB-connected SerialMonitor control the 16-ton Coal Iron Press.
 *
 * Copyright (c) 2022, The Ohio State University
 * The Artificially Intelligent Manufacturing Systems Lab (AIMS)
 * Authors: Brian Thurston, Adam Buynak
 */

#include <P1AM.h>

//int inputCounts = 0;

//Stroke range inches
float maximumHeight = 6.5f;
float minimumHeight = 0.0f;

//Target Position
float targetPos = 0;
float currentPos; //The current position of the ram
float directionOfMotion = true; //False for down, true for up
bool moveToTargetPosition = false;

//Timer for position update over serial
int period = 50; //Time between serial monitor updates [ms]
unsigned long time_now = 0;

void setup(){ // the setup routine runs once:

  Serial.begin(115200);  //initialize serial communication at 115200 bits per second
  
  while (!P1.init())
  {
    ; //Wait for Modules to Sign on  
  }

  pinMode(LED_BUILTIN,OUTPUT);
}

void loop()
{
  regularPrintPosition();

  //Read in the target position
  if(Serial.available())
  {
    
    targetPos = Serial.parseFloat();
    clearSerialBuffer();

    //Clamp the target Position
    if(targetPos > maximumHeight) targetPos = maximumHeight;
    if(targetPos < minimumHeight) targetPos = minimumHeight;
    Serial.print("Set Point: ");
    Serial.println(targetPos);
    currentPos = positionINCH();
    //Initiate motion
    moveToTargetPosition = true;

    //Set the direction of motion
    if(currentPos > targetPos)
    {
      directionOfMotion = false;
    }
    else
    {
      directionOfMotion = true;
    }
  }

  //Check to see if motion is enabled and if the target position has been reached
  if(moveToTargetPosition == true)
  {
    //Collect the current position
    currentPos = positionINCH();

    //Check if target has been reached
    if(directionOfMotion == false && currentPos < targetPos)
    {
      moveToTargetPosition = false;
    }
    if(directionOfMotion == true && currentPos > targetPos)
    {
      moveToTargetPosition = false;
    }
    
    if(moveToTargetPosition == false)
    {
      Serial.println("Halting");
      halt();
    }
    else
    {
      if(directionOfMotion == false) moveDown();
      else moveUp();
    }
  }
  else
  {
    //Manual control
      if(P1.readDiscrete(1,1))
      {
        P1.writeDiscrete(HIGH,1,2);  //Turn slot 1 channel 1 on
      }
      else if(P1.readDiscrete(1,2))
      {
        P1.writeDiscrete(HIGH,1,3);  //Turn slot 1 channel 2 on
      }
      else
      {
        P1.writeDiscrete(LOW,1,2);   //Turn slot 1 channel 1 off
        P1.writeDiscrete(LOW,1,3);   //Turn slot 1 channel 2 off
      }
  }

}

void clearSerialBuffer()
{
  while(Serial.available())
  {
    char q = Serial.read();
  }
}

void moveDown()
{
  P1.writeDiscrete(LOW,1,2);  //Turn slot 1 channel 1 on
  P1.writeDiscrete(HIGH,1,3);   //Turn slot 1 channel 2 off
}

void moveUp()
{
  P1.writeDiscrete(HIGH,1,2);  //Turn slot 1 channel 1 on
  P1.writeDiscrete(LOW,1,3);   //Turn slot 1 channel 2 off
}

void halt()
{
  P1.writeDiscrete(LOW,1,2);   //Turn slot 1 channel 1 off
  P1.writeDiscrete(LOW,1,3);   //Turn slot 1 channel 2 off
}

//Positioning
//Raw counts:
//Top height 2024 counts
//Lowest possible position 5343 counts
//Span 3319

//Top 6.75", 2024 counts
//Bottom 0", 4846 counts

void regularPrintPosition()
{
  if(millis() - time_now > period)
  {
    time_now = millis();
    Serial.print("     incr: ");
    Serial.print(P1.readAnalog(2, 1));
    Serial.print("     inch (from bottom): ");
    Serial.print(positionINCH());
    Serial.print("     mm (from top): ");
    Serial.print(positionMETER()*1000);
    Serial.println("");
  }
}


float positionINCH()
{
  //This function returns the position of the ram in decimal inches

  int inputCounts = P1.readAnalog(2, 1);              //Read analog data from slot 1 channel 2 of the analog input module
  float mill = map(inputCounts, 4846, 2024, 0, 6750); //Calibration by Brian Thurston: 418.0741 increments per inch

  return mill/1000;
}

float positionMETER()
{
  //This function returns the position of the ram in decimal meters

  int inputCounts = P1.readAnalog(2, 1);

  const int increment_posn_0meter = 2034;
  const float calibration_meter_per_increment = 0.0000610740530772;  //Calibration by Adam Buynak

  // Calculate
  float posn_meter = (inputCounts - increment_posn_0meter) * calibration_meter_per_increment;
  
  return posn_meter;
}
