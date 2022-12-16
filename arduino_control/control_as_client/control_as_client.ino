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
 * Copyright (c) 2022, The Ohio State University
 * The Artificially Intelligent Manufacturing Systems Lab (AIMS)
 * Author: Adam Buynak
 */
 
 /* Software Version: v0.2.1 */


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
#include <coaliron_16ton_support/JointControlPoint.h>



// Placeholder Required for Arduino's PreProcessor/Compiler
void placeholder() {}
