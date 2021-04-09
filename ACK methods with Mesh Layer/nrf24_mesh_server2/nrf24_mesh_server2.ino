#define RH_MESH_MAX_MESSAGE_LEN 50

#include <RHMesh.h>
#include <RH_NRF24.h>
#include <SPI.h>

#define CLIENT_ADDRESS 1
#define SERVER1_ADDRESS 2
#define SERVER2_ADDRESS 3

RH_NRF24 driver;

RHMesh manager(driver, SERVER2_ADDRESS);

void setup() 
{
  Serial.begin(115200);
  if (!manager.init())
    Serial.println("init failed");
}

uint8_t data[] = "And hello back to you from server2";
uint8_t buf[RH_MESH_MAX_MESSAGE_LEN];
void loop()
{
  uint8_t len = sizeof(buf);
  uint8_t from;
  if (manager.recvfromAck(buf, &len, &from))
  {
    Serial.print("got request from : 0x");
    Serial.print(from, HEX);
    Serial.print(": ");
    Serial.println((char*)buf);

    // Send a reply back to the originator client
    if (manager.sendtoWait(data, sizeof(data), from) != RH_ROUTER_ERROR_NONE)
      Serial.println("sendtoWait failed");
  }
}
