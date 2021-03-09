#ifndef __CRICKET_WRAP__
#define __CRICKET_WRAP__

#include <Adafruit_Crickit.h>
#include <seesaw_servo.h>
#include <seesaw_motor.h>

namespace Crickit 
{
  enum ServoPort
  {
    port1 = 0,
    port2 = 1,
    port3 = 2,
    port4 = 3
  };

  enum MotorPort
  {
    m1 = 0,
    m2 = 1
  };

  
  enum GPIO
  {
    pin1 = CRICKIT_SIGNAL1,
    pin2 = CRICKIT_SIGNAL2, 
    pin3 = CRICKIT_SIGNAL3,
    pin4 = CRICKIT_SIGNAL4,
    pin5 = CRICKIT_SIGNAL5,
    pin6 = CRICKIT_SIGNAL6, 
    pin7 = CRICKIT_SIGNAL7,
    pin8 = CRICKIT_SIGNAL8
  };

  bool init();
  seesaw_Servo& servo(ServoPort p);
  seesaw_Motor& motor(MotorPort p);
}


#endif 