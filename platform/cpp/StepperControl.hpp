#ifndef STEPPER_CONTROL_H
#define STEPPER_CONTROL_H

#include "LinearAxis.hpp"
#include "ServoMotor.hpp"

class StepperControl
{
  public:
    LinearAxis x;
    LinearAxis y;
    ServoMotor z;
  
    int max_delta;
  
  StepperControl(char x_id, int x_steps, int x_dir_pin, int x_step_pin, int x_min_pin, int x_max_pin, int x_enable_pin,
		 char y_id, int y_steps, int y_dir_pin, int y_step_pin, int y_min_pin, int y_max_pin, int y_enable_pin, int z_pin);
  
  void ddaMove(float x, float y);
  void setTargets(float x, float y);
  void setCurrents(float x, float y);
  void initArcMove(float x, float y, float i, float j, bool direction, float current_x, float current_y);
  void calculateDDA();
  void servoMove(int z);
};

#endif
