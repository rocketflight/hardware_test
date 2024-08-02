// /***************************************************************************
//   This is a simple test for the OpenRocketFlight Motion Pack Buzzer

//   Designed specifically to work with the Heltec Wireless Tracker V1.1
//   ----> https://heltec.org/project/wireless-tracker/

//   Depends on the following libraries:
//   ---->

//   Written by David Skinner, July 2024

//   BSD license, all text above must be included in any redistribution
//  ***************************************************************************/

// #include "Ram16Mb.h"

// Ram16Mb::Ram16Mb() {}

// bool Ram16Mb::Init(Stream *port)
// {
//   HardwareTest::Init(port);

//   const int FlashChipSelect = 6; // digital pin for flash chip CS pin
//   // const int FlashChipSelect = 21; // Arduino 101 built-in SPI Flash

//   void setup()
//   {
//     // uncomment these if using Teensy audio shield
//     // SPI.setSCK(14);  // Audio shield has SCK on pin 14
//     // SPI.setMOSI(7);  // Audio shield has MOSI on pin 7

//     // uncomment these if you have other SPI chips connected
//     // to keep them disabled while using only SerialFlash
//     // pinMode(4, INPUT_PULLUP);
//     // pinMode(10, INPUT_PULLUP);

//     Serial.begin(9600);

//     // wait for Arduino Serial Monitor
//     while (!Serial)
//       ;
//     delay(100);
//     Serial.println(F("All Files on SPI Flash chip:"));

//     if (!SerialFlash.begin(FlashChipSelect))
//     {
//       error("Unable to access SPI Flash chip");
//     }

//     SerialFlash.opendir();
//     while (1)
//     {
//       char filename[64];
//       uint32_t filesize;

//       if (SerialFlash.readdir(filename, sizeof(filename), filesize))
//       {
//         Serial.print(F("  "));
//         Serial.print(filename);
//         spaces(20 - strlen(filename));
//         Serial.print(F("  "));
//         Serial.print(filesize);
//         Serial.print(F(" bytes"));
//         Serial.println();
//       }
//       else
//       {
//         break; // no more files
//       }
//     }
//   }

//   void spaces(int num)
//   {
//     for (int i = 0; i < num; i++)
//     {
//       Serial.print(' ');
//     }
//   }

//   void loop()
//   {
//   }

//   void error(const char *message)
//   {
//     while (1)
//     {
//       Serial.println(message);
//       delay(2500);
//     }
//   }

//   this->_initialised = true;
//   this->Info(F("Buzzer: is initialised"));
//   return true;
// }

// void Ram16Mb::Run()
// {
//   if (!this->IsOk())
//     return;

//   _buzzer.step();
// }

// void Ram16Mb::Read()
// {
//   if (!this->IsOk())
//   {
//     this->Error(F("BUZZER: is offline"));
//     return;
//   }

//   _port->printf("%d\tBUZZER state: %s\n",
//                 millis(),
//                 this->_buzzer.hasMelody() ? "playing" : "idle");
// }
