/***************************************************************************
  This is a simple test for the OpenRocketFlight Motion Pack Battery

  Designed specifically to work with the Heltec Wireless Tracker V1.1
  ----> https://heltec.org/project/wireless-tracker/

  Depends on the following libraries:
  ----> https://github.com/adafruit/Adafruit MAX1704X

  Written by David Skinner, July 2024

  BSD license, all text above must be included in any redistribution
 ***************************************************************************/

#ifndef BATTERY_MAX17048_h
#define BATTERY_MAX17048_h

#include <Adafruit_MAX1704X.h>
#include "HardwareTest.h"

class BatteryMAX17048 : public HardwareTest
{
public:
  BatteryMAX17048();
  bool Init(Stream *port);
  bool Init(Stream *port, TwoWire &wirePort);
  void Read();

private:
  Adafruit_MAX17048 _lipo;
  String DecimalHoursToHHMM(float decimalHours, int decimalPlaces);
};

#endif
