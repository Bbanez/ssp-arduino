#include "Arduino.h"
#include "SSP.h"

void onPacketReceive(SSPPacket *packet)
{
  // Do something with the packet
}

void setup() {}
void loop()
{
  SSP ssp = SSP(&Serial, SSPAddress(31, 23), 115200, onPacketReceive, false);
  unsigned long cTime        = millis() + 10;
  unsigned long sendPacketAt = millis() + 1000;
  while (1) {
    // Serial can freeze if serial.available() is called to often.
    // This this will call it every 10ms.
    if (cTime < millis()) {
      cTime = millis() + 10;
      // Check for incoming packets
      ssp.run(millis());
    }
    if (sendPacketAt < millis()) {
      sendPacketAt = millis() + 1000;
      ssp.send(SSPPacket(SSPAddress(1, 1), 1, String(millis())));
    }
  }
}