/***************************************************************************
  This is a simple test for the OpenRocketFlight Motion Pack GNSS sensor

  Designed specifically to work with the Heltec Wireless Tracker V1.1
  ----> https://heltec.org/project/wireless-tracker/

  Depends on the following libraries:
  ----> https://github.com/stevemarple/MicroNMEA

  Written by David Skinner, July 2024

  BSD license, all text above must be included in any redistribution
 ***************************************************************************/

#ifndef GNSS_UC6580_h
#define GNSS_UC6580_h

#include <MicroNMEA.h>
#include "HardwareTest.h"

#define NMEA_BUFFER_BYTES 256
class GnssUC6580 : public HardwareTest
{
public:
  GnssUC6580();
  bool Init(Stream *port);
  void Run();
  void Read();

private:
  MicroNMEA _nmea;
  char _nmeaBuffer[NMEA_BUFFER_BYTES];
  unsigned long _bytes = 0;
};

#endif
