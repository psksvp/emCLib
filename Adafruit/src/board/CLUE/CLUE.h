#ifndef __ADAFRUIT_CLUE_WRAP__
#define __ADAFRUIT_CLUE_WRAP__

#include <Adafruit_Arcada.h>
#include <Adafruit_GFX.h>

namespace CLUE 
{
  struct IMU
  {
    sensors_event_t accelerometer;
    sensors_event_t gyroscope;
    sensors_event_t magnetometer;
  };

  bool init();
  void setBacklight(uint8_t l);
  float temperature();
  float airPressure();
  float altitude();
  float humidity();
  float light();
  IMU& imu();

  uint8_t readButtons();
  bool buttonA();
  bool buttonB();

  GFXcanvas16& canvas();
  void updateDisplay();
  void print(const char* s);
  void whiteLED(bool state);
  void playTone(unsigned int freq, unsigned long duration);
}

#endif