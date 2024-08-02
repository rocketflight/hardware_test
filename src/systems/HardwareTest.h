#ifndef HARDWARE_TEST_h
#define HARDWARE_TEST_h

#include "config.h"

class HardwareTest
{

public:
  HardwareTest() {};

  virtual inline bool Init(Stream *port)
  {
    _port = port;
    _initialised = false;
    return true;
  };

  virtual inline void Read() {};

  virtual inline void Run() {};

  virtual inline bool IsOk()
  {
    return _initialised;
  };

  virtual inline void Error(String message)
  {
    _port->printf("%lu\t%s :( ***\n", millis(), message.c_str());
  };

  virtual inline void Info(String message)
  {
    _port->printf("%lu\t%s\n", millis(), message.c_str());
  };

protected:
  Stream *_port;
  bool _initialised;
};

#endif
