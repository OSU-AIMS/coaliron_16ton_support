/*
 * Network Test using ROSSerial Publisher
 * 
 * Tests ROS Interface:
 *   From ~ Arduino Ethernet Shield
 *   To   ~ rosserial socket server
 *   
 * You can launch the rosserial socket server with
 * roslaunch rosserial_server socket.launch
 * The default port is 11411
 */
 
#include <SPI.h>
#include <Ethernet.h>

// To use the TCP version of rosserial_arduino
#define ROSSERIAL_ARDUINO_TCP

#include <ros.h>
#include <std_msgs/String.h>

// Set the shield settings
// Let DHCP server set IP Address
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };

// ROS Master Information. 
// serverPort specific to ArduinoServer. NOT ROS port 11311.
IPAddress rosmaster(10,10,10,51);
const uint16_t serverPort = 11411;

ros::NodeHandle nh;
// Make a chatter publisher
std_msgs::String str_msg;
ros::Publisher chatter("coaliron_chatter", &str_msg);

// Be polite and say hello
char hello[26] = "CoalIron Press Connected!";
uint16_t period = 1000;
uint32_t last_time = 0;


void setup()
{
  // Initialize Outputs.
  Serial.begin(115200);
  Ethernet.begin(mac);

  setup_network();
  setup_ros();

}


void setup_network()
{
  // Wait for Ethernet Shield to finish initializing
  while (Ethernet.linkStatus() != LinkON) {
    Serial.println("Ethernet Disconnected. Retrying..");
    delay(1000);
  }

  // Report Info
  Serial.println("");
  Serial.println("Ethernet Connected");
  Serial.print("DNS:              ");
  Serial.println(Ethernet.dnsServerIP());
  Serial.print("IPv4 addrss:      ");
  Serial.println(Ethernet.localIP());
  Serial.print("ROSSerial Server: ");
  Serial.print(rosmaster);
  Serial.print(":");
  Serial.println(serverPort);
  Serial.println("");
}


void setup_ros()
{
  // Set the connection to rosserial socket server
  nh.getHardware()->setConnection(rosmaster, serverPort);
  nh.initNode();

  // Advertise new topic
  nh.advertise(chatter);
}


void loop()
{
  if(millis() - last_time >= period)
  {
    last_time = millis();
    if (nh.connected())
    {
      Serial.println("ROSSerial Server Connected");
      // Say hello
      str_msg.data = hello;
      chatter.publish( &str_msg );
    } else {
      Serial.println("ROSSerial Server Not Connected");
    }
  }
  nh.spinOnce();
  delay(500);
}
