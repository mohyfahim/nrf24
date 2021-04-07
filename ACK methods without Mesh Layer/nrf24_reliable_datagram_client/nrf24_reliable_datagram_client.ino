// nrf24_reliable_datagram_client.pde
// -*- mode: C++ -*-
// Example sketch showing how to create a simple addressed, reliable messaging client
// with the RHReliableDatagram class, using the RH_NRF24 driver to control a NRF24 radio.
// It is designed to work with the other example nrf24_reliable_datagram_server
// Tested on Uno with Sparkfun WRL-00691 NRF24L01 module
// Tested on Teensy with Sparkfun WRL-00691 NRF24L01 module
// Tested on Anarduino Mini (http://www.anarduino.com/mini/) with RFM73 module
// Tested on Arduino Mega with Sparkfun WRL-00691 NRF25L01 module

#include <RHReliableDatagram.h>
#include <RH_NRF24.h>
#include <SPI.h>

#define CLIENT_ADDRESS 1
#define SERVER_ADDRESS 2

// Singleton instance of the radio driver
RH_NRF24 driver(9,10);
// RH_NRF24 driver(8, 7);   // For RFM73 on Anarduino Mini

// Class to manage message delivery and receipt, using the driver declared above
RHReliableDatagram manager(driver, CLIENT_ADDRESS);

void setup() 
{
  Serial.begin(115200);
  if (!manager.init())
    Serial.println("init failed");
  // Defaults after init are 2.402 GHz (channel 2), 2Mbps, 0dBm
}

String data = "Hello World!";
int counter = 0;
// Dont put this on the stack:
uint8_t buf[RH_NRF24_MAX_MESSAGE_LEN];

void loop()
{
  Serial.println("Sending to nrf24_reliable_datagram_server");
    
  // Send a message to manager_server
  if (manager.sendtoWait((data+String(counter)).c_str(), data.length()+String(counter).length(), SERVER_ADDRESS))
  {  Serial.print("got reply from : 0x");
//      Serial.print(from, HEX);
//      Serial.print(": ");
//      Serial.println((char*)buf);
//    }
//    else
//    {
//      Serial.println("
    // Now wait for a reply from the server
//    uint8_t len = sizeof(buf);
//    uint8_t from;   
//    if (manager.recvfromAckTimeout(buf, &len, 2000, &from))
//    {
//    No reply, is nrf24_reliable_datagram_server running?");
//    }
  }
  else
    Serial.println("sendtoWait failed");

   counter++;
  delay(500);
}
