#include <RHRouter.h>
#include <RH_NRF24.h>
#include <SPI.h>

#define CLIENT_ADDRESS 1
#define SERVER1_ADDRESS 2
#define SERVER2_ADDRESS 3

RH_NRF24 driver(9,10);

RHRouter manager(driver, SERVER1_ADDRESS);

void setup() 
{
  Serial.begin(9600);
  if (!manager.init())
    Serial.println("init failed");
  
  manager.addRouteTo(CLIENT_ADDRESS, CLIENT_ADDRESS);  
  manager.addRouteTo(SERVER2_ADDRESS, SERVER2_ADDRESS);
}


void loop()
{
}
