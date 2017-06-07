#include "ServoMotor.hpp"

#include<unistd.h>

#define SERVO_PIN 26
#define DELAY 400000
#define DOWN_POS 14
#define UP_POS 17

ServoMotor::ServoMotor(int pin)
{

 softPwmCreate(pin,0,1000);
 
}

void ServoMotor::step(int z)
{
  
  if(z < 0) {
    down();
  }
  
  else if(z >= 1) {
    up();
  }
  
}

void ServoMotor::down()
{
  
  softPwmWrite (SERVO_PIN, DOWN_POS) ;
  usleep(DELAY);
  
}

void ServoMotor::up()
{
  
   softPwmWrite (SERVO_PIN, UP_POS) ;
   usleep(DELAY);

}

