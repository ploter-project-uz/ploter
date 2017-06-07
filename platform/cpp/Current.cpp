#include "Current.hpp"

#include <string>

#define MAX_X 150
#define MIN_X -150
#define MAX_Y 250
#define MIN_Y -250


Current::Current()
{
  this->m_x = 0;
  this->m_y = 0;
  this->m_z = 0;
}


int Current::checkX(float x, int line)
{
  
  this->m_x = x;

  if(this->m_x > MAX_X || this->m_x < MIN_X) {
    std::string maxX = "Przekroczono zakres x w linii nr " + line;
    throw maxX;
  }
  
  return 0;
}


int Current::checkY(float y, int line)
{

  this->m_y = y;
    
  if(this->m_y > MAX_Y || this->m_y < MIN_Y) {
    std::string maxY = "Przekroczono zakres y w linii nr " + line;
    throw maxY;
  }

  return 0;
}


float Current::getX()
{

  return this->m_x;
}


float Current::getY()
{

  return this->m_y;
}


int Current::getZ()
{

  return this->m_z;
}


void Current::setX(float x)
{

  this->m_x = x;
  
}


void Current::setY(float y)
{

  this->m_y = y;
  
}


void Current::setZ(int z)
{
  this->m_z = z;
}


void Current::setCurrent(float x, float y)
{
  
  setX(x);
  setY(y);
  
}


void Current::reset()
{
  
  this->m_x = 0;
  this->m_y = 0;
  
}


