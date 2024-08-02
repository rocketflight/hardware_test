/***************************************************************************
  This is a simple test for the OpenRocketFlight Motion Pack LoRa Radio

  Designed specifically to work with the Heltec Wireless Tracker V1.1
  ----> https://heltec.org/project/wireless-tracker/

  Depends on the following libraries:
  ----> https://github.com/jgromes/RadioLib

  Written by David Skinner, July 2024

  BSD license, all text above must be included in any redistribution
 ***************************************************************************/

#ifndef LORA_SCX1262_h
#define LORA_SCX1262_h

#include <RadioLib.h>
#include "HardwareTest.h"

class LoraSCX1262 : public HardwareTest
{
public:
  LoraSCX1262();
  bool Init(Stream *port);
  void Run();
  void Read();

private:
  // placeholder
  // SPIClass _radio_spi;
  // SPISettings _spiSettings;
  // SX1262 _radio;
  // LoRaWANNode _node;
  unsigned long _bytes = 0;
};

#endif
