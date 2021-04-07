#include <SPI.h>
#include <RH_NRF24.h>

RH_NRF24 nrf24(9,10);

void setup() 
{
  Serial.begin(115200);
  while (!Serial) 
  if (!nrf24.init())
    Serial.println("init failed");
  // Defaults after init are 2.402 GHz (channel 2), 2Mbps, 0dBm
  if (!nrf24.setRF(RH_NRF24::DataRate250kbps  , RH_NRF24::TransmitPower0dBm))
    Serial.println("setRF failed");    
}

void loop()
{
  if (nrf24.available())
  {
    // Should be a message for us now   
    uint8_t buf[RH_NRF24_MAX_MESSAGE_LEN];
    uint8_t len = sizeof(buf);
    if (nrf24.recv(buf, &len))
    {
      Serial.print("got request: ");
      Serial.println((char*)buf);      
    }
    else
    {
      Serial.println("recv failed");
    }
  }
}
