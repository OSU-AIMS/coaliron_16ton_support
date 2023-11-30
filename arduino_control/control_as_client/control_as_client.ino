/*
 * CoalIron Press Control via Client
 * 
 * Arduino-code for hosting a rosserial client to control the 16-ton Coal Iron Press.
 * Requires connection initiated by a rosserial server node running elsewhere.
 * 
 * You can launch the rosserial socket server with
 * roslaunch rosserial_server socket.launch
 * The default port is 11411
 * 
 * Copyright (c) 2022-2023, The Ohio State University
 * The Artificially Intelligent Manufacturing Systems Lab (AIMS)
 * Author: Adam Buynak
 */
 
 /* Software Version: v0.2.3 */


/* ------------------------------------------
 * | Card | Port | Use
 * |-----------------------------------------
 * |  1   |  1R  | Empty
 * |  1   |  2R  | Empty
 * |  1   |  3R  | Temperature alarm 1
 * |  1   |  4R  | Empty
 * |  1   |  5R  | Fork State
 * |  1   |  6R  | Press Power Switch State
 * |  1   |  7R  | Empty
 * |  1   |  8R  | Empty
 * |-----------------------------------------
 * |  1   |  1W  | Empty
 * |  1   |  2W  | Empty
 * |  1   |  3W  | Induction Heater
 * |  1   |  4W  | Fork Sensor power
 * |  1   |  5W  | Hydraulic Valve 1
 * |  1   |  6W  | Hydraulic Valve 2
 * |  1   |  7W  | Flow control valve
 * -----------------------------------------
 */



#include <Arduino.h>

// P1AM-100 Special Functions
#include <P1AM.h>

// Communication Interfaces
#include <SPI.h>
#include <Ethernet.h>

// Use the TCP version of rosserial_arduino
#define ROSSERIAL_ARDUINO_TCP

// ROS
#include <ros.h>
#include <std_msgs/Header.h>
#include <sensor_msgs/JointState.h>
#include <std_msgs/Bool.h>
#include <std_msgs/Float64.h>
#include <sensor_msgs/Temperature.h>
//#include <industrial_msgs/RobotStatus.h>

#include <std_srvs/SetBool.h>



// Placeholder Required for Arduino's PreProcessor/Compiler
void placeholder() {}
