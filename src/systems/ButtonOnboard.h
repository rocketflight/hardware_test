/***************************************************************************
  This is a simple test for the RocketFlight Motion Pack Button

  Designed specifically to work with the Heltec Wireless Tracker V1.1
  ----> https://heltec.org/project/wireless-tracker/

  Written by David Skinner, July 2024

  BSD license, all text above must be included in any redistribution
 ***************************************************************************/

#ifndef ONBOARD_BUTTON_h
#define ONBOARD_BUTTON_h

#if !defined(ESP32)
#error ButtonOnboard needs an ESP32
#endif

#define BUTTON_PIN 0
#define BUTTON_LONG_CLICK_MSEC 5000

#include <Button2.h>
#include "HardwareTest.h"

class ButtonOnboard : public HardwareTest
{
public:
  ButtonOnboard();
  bool Init(Stream *port, std::function<void(Button2 &btn)> f);

protected:
  hw_timer_t *_timer = nullptr;
};

#endif
