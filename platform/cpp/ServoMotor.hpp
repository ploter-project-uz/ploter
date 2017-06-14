#include<wiringPi.h>
#include<softPwm.h>

class ServoMotor
{
  bool current;
  public:
  ServoMotor(int pin);
  void step(int z);
  void up();
  void down();
};
