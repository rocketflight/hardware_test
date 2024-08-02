/***************************************************************************
  This is a simple test for the OpenRocketFlight Motion Pack GNSS sensor

  Designed specifically to work with the Heltec Wireless Tracker V1.1
  ----> https://heltec.org/project/wireless-tracker/

  Depends on the following libraries:
  ----> https://github.com/stevemarple/MicroNMEA

  Written by David Skinner, July 2024

  BSD license, all text above must be included in any redistribution
 ***************************************************************************/

#include "GnssUC6580.h"

GnssUC6580::GnssUC6580()
{
  this->_nmea = MicroNMEA(this->_nmeaBuffer, sizeof(NMEA_BUFFER_BYTES));
}

bool GnssUC6580::Init(Stream *port)
{
  HardwareTest::Init(port);

  pinMode(GNSS_CTRL_PIN, OUTPUT);
  digitalWrite(GNSS_CTRL_PIN, HIGH);
  Serial1.begin(GNSS_BAUD, SERIAL_8N1, GNSS_TX_PIN, GNSS_RX_PIN);
  delay(2000);
  Serial1.print(F("$CFGSYS,h35155*68\r\n"));

  this->_initialised = true;
  this->Info(F("UC6580 GNSS: is initialised"));
  return true;
}

void GnssUC6580::Run()
{
  char gnss_ch;
  if (Serial1.available() > 0)
  {
    gnss_ch = Serial1.read();
    _bytes++;
    this->_nmea.process(gnss_ch);
  }
}

void GnssUC6580::Read()
{
  if (!this->IsOk())
  {
    this->Error(F("UC6580 GNSS: is offline"));
    return;
  }

  if (this->_bytes == 0)
  {
    this->Error(F("UC6580 GNSS: is not receiving"));
    return;
  }

  long gnss_lat = this->_nmea.getLatitude();
  long gnss_lon = this->_nmea.getLatitude();
  long gnss_alt;
  this->_nmea.getAltitude(gnss_alt);

  _port->printf("%d\tUC6580 sats: %u valid: %s time: %04u-%02u-%02u %02u:%02u:%02u.%02u lat: %3ld.%06ld lon: %3ld.%06ld alt: %4ld.%03ld bytes: %lu\n",
                 millis(),
                 this->_nmea.getNumSatellites(),
                 this->_nmea.isValid() ? "yes" : "no",
                 this->_nmea.getYear(),
                 this->_nmea.getMonth(),
                 this->_nmea.getDay(),
                 this->_nmea.getHour(),
                 this->_nmea.getMinute(),
                 this->_nmea.getSecond(),
                 this->_nmea.getHundredths(),
                 gnss_lat / 1000000L,
                 gnss_lat % 1000000L,
                 gnss_lon / 1000000L,
                 gnss_lon % 1000000L,
                 gnss_alt / 1000L,
                 gnss_alt % 1000L,
                 this->_bytes);
}
