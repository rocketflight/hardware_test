/***************************************************************************
  This is a simple test for the RocketFlight Motion Pack Buzzer

  Designed specifically to work with the Heltec Wireless Tracker V1.1
  ----> https://heltec.org/project/wireless-tracker/

  Depends on the following libraries:
  ----> https://github.com/jcsb1994/Buzzer

  Written by David Skinner, July 2024

  BSD license, all text above must be included in any redistribution
 ***************************************************************************/

#ifndef PASSIVE_BUZZER_h
#define PASSIVE_BUZZER_h

#define PWM_RES 8

#include <notes.h>
#include <Buzzer.h>
#include "HardwareTest.h"

class BuzzerOnboard : public HardwareTest
{
public:
  BuzzerOnboard();
  bool Init(Stream *port);
  void Read();
  void Run();

private:
  Buzzer _buzzer;

  Buzzer::Melody_t _melody{.nbNotes = 3,
                           .duration = {400, 400, 800},
                           .frequency = {D4_NOTE_FREQ, E4_NOTE_FREQ, G4_NOTE_FREQ}};

  int _pin;
  int _channel;
  void tone(int note, int duration);
  void noTone();
};

#endif
