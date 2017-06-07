#include "StepperControl.hpp"

#include<algorithm>

#include<wiringPi.h>

#include<cmath>

#define X_STEPS_PER_MM 33.32
#define Y_STEPS_PER_MM 33.32

#define CURVE_SECTION_INCHES 0.019685


StepperControl::StepperControl(
	      char x_id, int x_steps, int x_dir_pin, int x_step_pin, int x_min_pin, int x_max_pin, int x_enable_pin,
	      char y_id, int y_steps, int y_dir_pin, int y_step_pin, int y_min_pin, int y_max_pin, int y_enable_pin,
	      int z_pin
			        ): x(x_id, x_steps, x_dir_pin, x_step_pin, x_min_pin, x_max_pin, x_enable_pin),
				   y(y_id, y_steps, y_dir_pin, y_step_pin, y_min_pin, y_max_pin, y_enable_pin),
				   z(z_pin)
{
  wiringPiSetup();
}


void StepperControl::setTargets(float x, float y)
{
  
  this->x.setTarget(x*X_STEPS_PER_MM);
  this->y.setTarget(y*Y_STEPS_PER_MM);

}


void StepperControl::ddaMove(float x, float y)
{
  
  setTargets(x,y);
  calculateDDA();
  
  do {
    
    this->x.readState();
    this->y.readState();
    
    if(this->x.can_step) {
      this->x.ddaStep(this->max_delta);
    }
    
    if(this->y.can_step) {
      this->y.ddaStep(this->max_delta);
    }
    
  } while(this->x.can_step || this->y.can_step);

}


void StepperControl::initArcMove(float x, float y, float i, float j, bool direction, float current_x, float current_y)
{
  
  float centX = i + current_x;
  float centY = j + current_y;
  
  float angleA, angleB, angle, radius, length, aX, aY, bX, bY;
  
  aX = current_x - centX;
  aY = current_y - centY;
  bX = x - centX;
  bY = y - centY;
  
  if(direction) {
    angleA = std::atan2(aY, aX);
    angleB = std::atan2(bY, bX);
  }
  
  else {
    angleA = std::atan2(bY, bX);
    angleB = std::atan2(aY, aX);
  }
  
  if(angleB <= angleA) {
    angleB += 2 * M_PI;
  }
  
  angle = angleB - angleA;
  radius = std::sqrt(aX * aX + aY * aY);
  length = radius * angle;

  int steps, s, step;
  steps = (int) ceil(length / CURVE_SECTION_INCHES);

  float pointX, pointY;
  for(s = 1; s <= steps; s++) {
    
    if(direction) {
      //step = steps - s;
      step = s;
    }
    
    else {
      //step = s;
      step = steps - s;
    }
    
    pointX = centX + radius * std::cos(angleA + angle * ((float) step / steps));
    pointY = centY + radius * std::sin(angleA + angle * ((float) step / steps));

    ddaMove(pointX, pointY);
  }          
}

void StepperControl::calculateDDA()
{
  
  this->max_delta = std::max(x.delta, y.delta);
  
  x.initDDA(this->max_delta);
  y.initDDA(this->max_delta);
  
}

void StepperControl::servoMove(int z)
{
  this->z.step(z);
}

