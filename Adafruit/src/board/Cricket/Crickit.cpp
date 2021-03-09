#include "Crickit.h"

namespace Crickit 
{
  Adafruit_Crickit afcrickit;
  seesaw_Servo servo1(&afcrickit), 
               servo2(&afcrickit), 
               servo3(&afcrickit), 
               servo4(&afcrickit);

  seesaw_Motor motor1(&afcrickit), 
               motor2(&afcrickit);

  seesaw_Servo servos[] = {servo1, servo2, servo3, servo4};
  int hwServos[] = {CRICKIT_SERVO1, CRICKIT_SERVO2, CRICKIT_SERVO3, CRICKIT_SERVO4}; 

  seesaw_Motor motors[] = {motor1, motor2};   

  bool init()
  {
    bool b = afcrickit.begin();
    motor1.attach(CRICKIT_MOTOR_A1, CRICKIT_MOTOR_A2);
    motor2.attach(CRICKIT_MOTOR_B1, CRICKIT_MOTOR_B2);
    return b;
  }

  seesaw_Motor& motor(MotorPort p)
  {
    return motors[p];
  }

  seesaw_Servo& servo(ServoPort p)
  {
    if(!servos[p].attached())
      servos[p].attach(hwServos[p]);
      
    return servos[p];
  }
}