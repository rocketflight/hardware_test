/***************************************************************************
  This is a simple test for the OpenRocketFlight Motion Pack Battery

  Designed specifically to work with the Heltec Wireless Tracker V1.1
  ----> https://heltec.org/project/wireless-tracker/

  Depends on the following libraries:
  ----> https://github.com/adafruit/Adafruit MAX1704X

  Written by David Skinner, July 2024

  BSD license, all text above must be included in any redistribution
 ***************************************************************************/

#include "BatteryMAX17048.h"

BatteryMAX17048::BatteryMAX17048() {};

bool BatteryMAX17048::Init(Stream *port)
{
  return this->BatteryMAX17048::Init(port, Wire);
}

bool BatteryMAX17048::Init(Stream *port, TwoWire &wirePort = Wire)
{
  HardwareTest::Init(port);

  _initialised = _lipo.begin(&wirePort);
  if (!_initialised)
  {
    this->Error(F("MAX17048 Battery: failed to initialise"));
    return false;
  }

  this->Info(F("MAX17048 Battery: is initialised"));
  return true;
}

void BatteryMAX17048::Read()
{
  if (!this->IsOk())
  {
    this->Error(F("M17048: is offline"));
    return;
  }

  float cellVoltage = _lipo.cellVoltage();
  if (isnan(cellVoltage))
  {
    this->Error("M17048: battery is disconnected");
    return;
  }
  float rate = _lipo.chargeRate();
  float soc = _lipo.cellPercent();
  soc = soc > 100.0f ? 100.0f : (soc < 0.0f ? 0.0f : soc);
  float timeToCharge = (100.0f - soc) / rate;

  _port->printf("%d\tM17048 volts: %.3f soc: %.1f%% rate: %.1f%%/hr time to charge: %s\n",
                millis(),
                cellVoltage,
                soc,
                rate,
                this->DecimalHoursToHHMM(timeToCharge, 0));
}

String BatteryMAX17048::DecimalHoursToHHMM(float decimalHours, int decimalPlaces = 0)
{
  float hours = (float)(int)abs(decimalHours);
  float mins = (hours - abs(decimalHours)) * 60;
  String result = String(mins, decimalPlaces);
  while (result.length() < 2)
    result = String(F("0")) + result;
  result = String(hours, 0) + String(F(":")) + result;
  if (decimalHours < 0)
    result = String(F("-")) + result;
  return result;
}
