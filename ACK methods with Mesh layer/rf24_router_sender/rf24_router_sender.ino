
#include <RHRouter.h>
#include <RH_NRF24.h>
#include <SPI.h>

#define CLIENT_ADDRESS 1
#define SERVER1_ADDRESS 2
#define SERVER2_ADDRESS 3

RH_NRF24 driver(8,10);

RHRouter manager(driver, CLIENT_ADDRESS);

void setup() 
{
  Serial.begin(9600);
  if (!manager.init())
    Serial.println("init failed");
  
  manager.addRouteTo(SERVER1_ADDRESS, SERVER1_ADDRESS);  
  manager.addRouteTo(SERVER2_ADDRESS, SERVER1_ADDRESS);
}

uint8_t data[] = "Hello World!";
uint8_t buf[RH_ROUTER_MAX_MESSAGE_LEN];

void loop()
{
  Serial.println("Sending to rf24_router_receiver");
    
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
      Serial.println("No reply, is rf22_router_server1, rf22_router_server2 and rf22_router_server3 running?");
    }
  }
  else
    Serial.println("sendtoWait failed. Are the intermediate router servers running?");
}
