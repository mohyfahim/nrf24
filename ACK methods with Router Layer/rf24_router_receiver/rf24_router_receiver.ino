#include <RHRouter.h>
#include <RH_NRF24.h>
#include <SPI.h>

#define CLIENT_ADDRESS 1
#define SERVER1_ADDRESS 2
#define SERVER2_ADDRESS 3

RH_NRF24 driver(9,10);

RHRouter manager(driver, SERVER2_ADDRESS);

void setup() 
{
  Serial.begin(9600);
  if (!manager.init())
    Serial.println("init failed");
  
  manager.addRouteTo(CLIENT_ADDRESS, SERVER1_ADDRESS);  
  manager.addRouteTo(SERVER1_ADDRESS, SERVER1_ADDRESS);
}

uint8_t data[] = "And hello back to you from server2";
uint8_t buf[RH_ROUTER_MAX_MESSAGE_LEN];

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

    if (manager.sendtoWait(data, sizeof(data), from) != RH_ROUTER_ERROR_NONE)
      Serial.println("sendtoWait failed");
  }
}
