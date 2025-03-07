/***************************************************************************
  This is a simple test for the RocketFlight Motion Pack Button

  Designed specifically to work with the Heltec Wireless Tracker V1.1
  ----> https://heltec.org/project/wireless-tracker/

  Written by David Skinner, July 2024

  BSD license, all text above must be included in any redistribution
 ***************************************************************************/

#include "ButtonOnboard.h"

ButtonOnboard::ButtonOnboard() {}

Button2 buttonOB;

void IRAM_ATTR OnTimer()
{
  buttonOB.loop();
}

bool ButtonOnboard::Init(Stream *port, std::function<void(Button2 &btn)> callback)
{
  HardwareTest::Init(port);

  buttonOB.begin(BUTTON_PIN);
  buttonOB.setLongClickTime(BUTTON_LONG_CLICK_MSEC);
  buttonOB.setLongClickHandler(callback);
  buttonOB.setClickHandler([this](Button2 &b)
                           { this->Info(F("Onboard button: click")); });

  this->_timer = timerBegin(0, 80, true);
  timerAttachInterrupt(_timer, &OnTimer, true);
  timerAlarmWrite(_timer, 10000, true); // every 0.1 seconds
  timerAlarmEnable(_timer);

  this->_initialised = true;
  this->Info(F("Onboard button: is initialised"));
  return true;
}
