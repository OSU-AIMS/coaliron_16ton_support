// ------------------------------
// Function Implementations: ROS
// ------------------------------


void setup_ros() {
  
  // Set the connection to rosserial socket server
  nh.getHardware() -> setConnection(rosmaster, serverPort);
  nh.initNode();

  // Advertise new topic
  nh.advertise(pub_joint_states);
}
