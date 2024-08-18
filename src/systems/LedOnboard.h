/***************************************************************************
  This is a simple test for the RocketFlight Motion Pack LED

  Designed specifically to work with the Heltec Wireless Tracker V1.1
  ----> https://heltec.org/project/wireless-tracker/

  Written by David Skinner, July 2024

  BSD license, all text above must be included in any redistribution
 ***************************************************************************/

#ifndef ONBOARD_LED_h
#define ONBOARD_LED_h

#include "HardwareTest.h"

class LedOnboard : public HardwareTest
{
public:
  LedOnboard();
  bool Init(Stream *port);
  void Read();
  void Run();
  void Flash(int flashes, unsigned long intervalMillis);

private:
  unsigned long _next;
  uint8_t _state;
};

#endif
