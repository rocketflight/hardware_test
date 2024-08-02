/***************************************************************************
  This is a simple test for the OpenRocketFlight Motion Pack LED

  Designed specifically to work with the Heltec Wireless Tracker V1.1
  ----> https://heltec.org/project/wireless-tracker/

  Written by David Skinner, July 2024

  BSD license, all text above must be included in any redistribution
 ***************************************************************************/

#include "LedOnboard.h"

LedOnboard::LedOnboard() {}

bool LedOnboard::Init(Stream *port)
{

  HardwareTest::Init(port);

  pinMode(LED_PIN, OUTPUT);
  this->_next = millis();
  this->_state = LED_OFF;

  this->_initialised = true;
  this->Info(F("Onboard led: is initialised"));
  return true;
}

void LedOnboard::Run()
{
  if (!this->IsOk())
    return;

  if (millis() >= this->_next)
  {
    this->_next += LED_MILLIS;
    this->_state = this->_state == LED_OFF ? LED_ON : LED_OFF;
    digitalWrite(LED_PIN, this->_state);

    if (VERBOSE)
    {
      this->Info(String(F("Onboard led: is ")) + String(this->_state == LED_OFF ? "off" : "on"));
    }
  }
  return;
}

void LedOnboard::Read()
{
  if (!this->IsOk())
  {
    this->Error(F("LED: is offline"));
    return;
  }

  _port->printf("%d\tLED    state: %s\n",
                millis(),
                this->_state == LED_OFF ? "off" : "on");
  return;
}

void LedOnboard::Flash(int flashes, unsigned long intervalMillis)
{
  pinMode(LED_BUILTIN, OUTPUT);
  for (int i = 0; i < flashes * 2; i++)
  {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(intervalMillis);
    digitalWrite(LED_BUILTIN, LOW);
    delay(intervalMillis);
  }
}
