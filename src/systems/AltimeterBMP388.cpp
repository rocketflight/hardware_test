/***************************************************************************
  This is a simple test for the RocketFlight Motion Pack altimeter

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

  if (!this->_prefs.begin(PREFS_NAMESPACE))
  {
    this->Error(F("BMP388 altimeter: prefs failed initialisation"));
    return false;
  }
  //_prefs.putFloat(PREFS_MAX, 1002.513000f);

  // settle down the sensor
  for (int i = 0; i < 5; i++)
  {
    delay(100);
    if (!this->_bmp.performReading())
    {
      this->Error(F("BMP388 altimeter: failed to perform reading"));
      return false;
    }
  }

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

  this->data.altitude = this->_bmp.readAltitude(SEALEVELPRESSURE_HPA);
  this->data.pressure = this->_bmp.pressure / 100.0;
  this->data.temperature = this->_bmp.temperature;

  this->data.pressureMin = _prefs.getFloat(PREFS_MIN, PREFS_DEFAULT);
  this->data.pressureMax = _prefs.getFloat(PREFS_MAX, PREFS_DEFAULT);
  //_port->printf("now: %f min: %f max %f\n", this->data.pressure, this->data.pressureMin, this->data.pressureMax);

  if (this->data.pressure < this->data.pressureMin || this->data.pressureMin == PREFS_DEFAULT)
  {
    this->data.pressureMin = this->data.pressure;
    _port->printf("%d\tBMP388 pressure min updated to: %.2f\n", millis(), this->data.pressureMin);
    _prefs.putFloat(PREFS_MIN, this->data.pressureMin);
  }

  if (this->data.pressure > this->data.pressureMax || this->data.pressureMax == PREFS_DEFAULT)
  {
    this->data.pressureMax = this->data.pressure;
    _port->printf("%d\tBMP388 pressure max updated to: %.2f\n", millis(), this->data.pressureMax);
    _prefs.putFloat(PREFS_MAX, this->data.pressureMax);
  }

  _port->printf("%d\tBMP388 altitude: %.1fm temp: %.1fC pressure: %.2fhPa min: %.2fhPa max: %.2fhPa\n",
                millis(),
                this->data.altitude,
                this->data.temperature,
                this->data.pressure,
                this->data.pressureMin,
                this->data.pressureMax);
  return;
}

void AltimeterBMP388::Reset()
{
  if (!this->IsOk())
  {
    this->Error(F("BMP388 altimeter: is offline"));
    return;
  }

  this->data.pressureMin = PREFS_DEFAULT;
  this->data.pressureMax = PREFS_DEFAULT;
  _prefs.putFloat(PREFS_MIN, this->data.pressureMin);
  _prefs.putFloat(PREFS_MAX, this->data.pressureMax);
  _port->printf("%d\tBMP388 altimeter: reset min/max pressure\n", millis());
}