// Mesh has much greater memory requirements, and you may need to limit the
// max message length to prevent wierd crashes
#define RH_MESH_MAX_MESSAGE_LEN 50

#include <RHMesh.h>
#include <RH_NRF24.h>
#include <SPI.h>

// In this small artifical network of 3 nodes,
#define CLIENT_ADDRESS 1
#define SERVER1_ADDRESS 2
#define SERVER2_ADDRESS 3

// Singleton instance of the radio driver
RH_NRF24 driver(9,10);

// Class to manage message delivery and receipt, using the driver declared above
RHMesh manager(driver, CLIENT_ADDRESS);

void setup() 
{
  Serial.begin(115200);
  if (!manager.init())
    Serial.println("init failed");
}

uint8_t data[] = "Hello World!";
uint8_t buf[RH_MESH_MAX_MESSAGE_LEN];

void loop()
{
  Serial.println("Sending to manager_mesh_server2");
    
  if (manager.sendtoWait(data, sizeof(data), SERVER2_ADDRESS) == RH_ROUTER_ERROR_NONE)
  {
    uint8_t len = sizeof(buf);
    uint8_t from;    
    if (manager.recvfromAckTimeout(buf, &len, 3000, &from))
    {
      Serial.print("got reply from : 0x");
      Serial.print(from, HEX);
      Serial.print(": ");
      Serial.println((char*)buf);
    }
    else
    {
      Serial.println("No reply, is rf22_mesh_server1, rf22_mesh_server2 and rf22_mesh_server3 running?");
    }
  }
  else
     Serial.println("sendtoWait failed. Are the intermediate mesh servers running?");
}
