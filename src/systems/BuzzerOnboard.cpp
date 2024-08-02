/***************************************************************************
  This is a simple test for the OpenRocketFlight Motion Pack Buzzer

  Designed specifically to work with the Heltec Wireless Tracker V1.1
  ----> https://heltec.org/project/wireless-tracker/

  Depends on the following libraries:
  ----> https://github.com/jcsb1994/Buzzer

  Written by David Skinner, July 2024

  BSD license, all text above must be included in any redistribution
 ***************************************************************************/

#include "BuzzerOnboard.h"

BuzzerOnboard::BuzzerOnboard() {}

bool BuzzerOnboard::Init(Stream *port)
{
  HardwareTest::Init(port);

  _pin = BUZZER_PIN;
  _channel = BUZZER_CHANNEL;
  ledcAttachPin(_pin, _channel);

  // this->tone(NOTE_C4, INT_MAX);

  // this->tone(NOTE_C4, 250);
  // this->tone(NOTE_D4, 250);
  // this->tone(NOTE_E4, 250);
  // this->tone(NOTE_F4, 250);
  // this->tone(NOTE_G4, 250);
  // this->tone(NOTE_A4, 250);
  // this->tone(NOTE_B4, 250);
  // this->tone(NOTE_C5, 250);
  // delay(250);
  // this->tone(NOTE_C5, 250);
  // this->tone(NOTE_B4, 250);
  // this->tone(NOTE_A4, 250);
  // this->tone(NOTE_G4, 250);
  // this->tone(NOTE_F4, 250);
  // this->tone(NOTE_E4, 250);
  // this->tone(NOTE_D4, 250);
  // this->tone(NOTE_C4, 250);
  // this->noTone();

  // _buzzer.init(BUZZER_PIN);
  // _buzzer.setMelody(&_melody);

  this->_initialised = true;
  this->Info(F("Buzzer: is initialised"));
  return true;
}

void BuzzerOnboard::Run()
{
  if (!this->IsOk())
    return;

  _buzzer.step();
}

void BuzzerOnboard::Read()
{
  if (!this->IsOk())
  {
    this->Error(F("BUZZER: is offline"));
    return;
  }

  _port->printf("%d\tBUZZER state: %s\n",
                millis(),
                this->_buzzer.hasMelody() ? "playing" : "idle");
}

void BuzzerOnboard::tone(int note, int duration)
{
  ledcSetup(_channel, note, PWM_RES);
  ledcWrite(_channel, 127);
  // delay(duration);
  // ledcWrite(_channel, 0);
}

void BuzzerOnboard::noTone()
{
  ledcWrite(_channel, 0);
}
