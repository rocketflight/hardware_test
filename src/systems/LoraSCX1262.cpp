/***************************************************************************
  This is a simple test for the OpenRocketFlight Motion Pack LoRa Radio

  Designed specifically to work with the Heltec Wireless Tracker V1.1
  ----> https://heltec.org/project/wireless-tracker/

  Depends on the following libraries:
  ----> https://github.com/jgromes/RadioLib

  Written by David Skinner, July 2024

  BSD license, all text above must be included in any redistribution
 ***************************************************************************/

#include "LoraSCX1262.h"

LoraSCX1262::LoraSCX1262() {};

bool LoraSCX1262::Init(Stream *port)
{
  HardwareTest::Init(port);

  // placeholder
  // this->_radio_spi = SPIClass(FSPI);
  // this->_spiSettings = SPISettings(2000000, MSBFIRST, SPI_MODE0);
  // this->_radio = new Module(RADIO_NSS_PIN, RADIO_DIO_1_PIN, RADIO_RESET_PIN, RADIO_BUSY_PIN, _radio_spi, _spiSettings);
  // this->_node = LoRaWANNode(&_radio, &AU915);

  // pinMode(RADIO_NSS_PIN, OUTPUT);
  // _radio_spi.begin(LORA_CLK_PIN, LORA_MISO_PIN, LORA_MOSI_PIN, RADIO_NSS_PIN);
  // int state = _radio.begin();
  // if (state != RADIOLIB_ERR_NONE)
  // {
  //   this->Error("SCX1262 LoRa: failed to initialise");
  //   return false;
  // }

  // this->_initialised = true;
  this->Info(F("SCX1262 LoRa: is initialised"));
  return true;
}

void LoraSCX1262::Run()
{
  // placeholder
}

void LoraSCX1262::Read()
{
  if (!this->IsOk())
  {
    this->Error(F("SCX1262 LoRa: is offline"));
    return;
  }

  if (this->_bytes == 0)
  {
    this->Error(F("SCX1262 LoRa: is not receiving"));
    return;
  }

  // placeholder
}
