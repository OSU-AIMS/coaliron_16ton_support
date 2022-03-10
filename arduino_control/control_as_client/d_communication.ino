// ---------------------------------------------------
// Function Implementations: Communication Interfaces
// ---------------------------------------------------


void setup_network() {
  
  // Wait for Ethernet Shield to finish initializing
  while (Ethernet.linkStatus() != LinkON) {
    Serial.println("Ethernet Disconnected. Retrying..");
    delay(500);
  }

  // Report Info
  Serial.println("");
  Serial.println("Ethernet Connected");
  Serial.print("DNS:              ");     Serial.println(Ethernet.dnsServerIP());
  Serial.print("IPv4 addrss:      ");     Serial.println(Ethernet.localIP());
  Serial.print("ROSSerial Server: ");     Serial.print(rosmaster);
                                          Serial.print(":");
                                          Serial.println(serverPort);
  Serial.println("");
}


void clearSerialBuffer() {
  while(Serial.available() > 0) {
    char q = Serial.read();
  }
}
