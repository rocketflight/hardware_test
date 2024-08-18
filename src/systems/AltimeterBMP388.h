/***************************************************************************
  This is a simple test for the RocketFlight Motion Pack altimeter

  Designed specifically to work with the Heltec Wireless Tracker V1.1
  ----> https://heltec.org/project/wireless-tracker/

  Depends on the following libraries:
  ----> https://github.com/adafruit/Adafruit_BMP3XX

  Written by David Skinner, July 2024

  BSD license, all text above must be included in any redistribution
 ***************************************************************************/

#ifndef BMP388_ALTIMETER_h
#define BMP388_ALTIMETER_h

#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP3XX.h>
#include "HardwareTest.h"

class AltimeterBMP388 : public HardwareTest
{

public:
  AltimeterBMP388();
  bool Init(Stream *port);
  bool Init(Stream *port, TwoWire &wirePort);
  void Read();

private:
  Adafruit_BMP3XX _bmp;
};

#endif
