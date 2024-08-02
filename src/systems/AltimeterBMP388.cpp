/***************************************************************************
  This is a simple test for the OpenRocketFlight Motion Pack altimeter

  Designed specifically to work with the Heltec Wireless Tracker V1.1
  ----> https://heltec.org/project/wireless-tracker/

  Depends on the following libraries:
  ----> https://github.com/adafruit/Adafruit_BMP3XX

  Written by David Skinner, July 2024

  BSD license, all text above must be included in any redistribution
 ***************************************************************************/

#include "AltimeterBMP388.h"

AltimeterBMP388::AltimeterBMP388() {}

bool AltimeterBMP388::Init(Stream *port)
{
  return this->AltimeterBMP388::Init(port, Wire);
}

bool AltimeterBMP388::Init(Stream *port, TwoWire &wirePort = Wire)
{

  HardwareTest::Init(port);

  // set up the BMP388 on I2C using the primary address
  if (!this->_bmp.begin_I2C(BMP388_ALTIMETER_ADDR1, &wirePort))
  {
    // try the backup BMP388 address (useful for testing)
    if (!this->_bmp.begin_I2C(BMP388_ALTIMETER_ADDR2, &wirePort))
    {
      this->Error(F("BMP388 altimeter: failed to initialise"));
      return false;
    }
  }

  // set up oversampling and filter initialization
  this->_bmp.setTemperatureOversampling(BMP3_OVERSAMPLING_8X);
  this->_bmp.setPressureOversampling(BMP3_OVERSAMPLING_4X);
  this->_bmp.setIIRFilterCoeff(BMP3_IIR_FILTER_COEFF_3);
  this->_bmp.setOutputDataRate(BMP3_ODR_50_HZ);

  this->_initialised = true;
  this->Info(F("BMP388 altimeter: is initialised"));
  return true;
}

void AltimeterBMP388::Read()
{

  if (!this->IsOk())
  {
    this->Error(F("BMP388 altimeter: is offline"));
    return;
  }

  if (!this->_bmp.performReading())
  {
    this->Error(F("BMP388 altimeter: failed to perform reading"));
    return;
  }

  _port->printf("%d\tBMP388 altitude: %.1fm temp: %.1fC pressure: %.1fhPa\n",
                millis(),
                this->_bmp.readAltitude(SEALEVELPRESSURE_HPA),
                this->_bmp.temperature,
                this->_bmp.pressure / 100.0);
  return;
}
