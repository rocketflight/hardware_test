/***************************************************************************
  This is a simple test for the RocketFlight Motion Pack Motion Processor

  Designed specifically to work with the Heltec Wireless Tracker V1.1
  ----> https://heltec.org/project/wireless-tracker/

  Depends on the following libraries:
  ----> https://github.com/sparkfun/SparkFun_ICM-20948_ArduinoLibrary

  Written by David Skinner, July 2024

  BSD license, all text above must be included in any redistribution
 ***************************************************************************/

#ifndef MPU_ICM_20948_h
#define MPU_ICM_20948_h

#include <ICM_20948.h>
#include "HardwareTest.h"

class MpuICM20948 : public HardwareTest
{
public:
  MpuICM20948();
  bool Init(Stream *port);
  bool Init(Stream *port, TwoWire &wirePort);
  void Run();
  void Read();
  void ReadQuaternion();
  void ReadAccelGyro();
  void ReadStats();
  void ClearStats();
  void AddStats(uint16_t header);

  float GetGyroDPS(int16_t axis_val);
  float GetAccelG(int16_t axis_val);

private:
  ICM_20948_I2C _mpu;

  // values
  double _q0, _q1, _q2, _q3;
  float _accelX, _accelY, _accelZ;
  float _gyroX, _gyroY, _gyroZ;
  int16_t _accuracy;

  // stats
  int16_t _messages[13];
  unsigned long _startMillis, _dmpCount, _accelCount, _gyroCount;
};

#endif
