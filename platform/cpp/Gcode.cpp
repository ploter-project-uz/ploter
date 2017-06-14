#include "Command.hpp"
#include "Window.hpp"
#include "StepperControl.hpp"
#include "Current.hpp"
#include "Gcode.hpp"


void G0::validate(const std::vector<std::string> &token, int n)
{
  //wszystkie dopuszczalne parametry, paramet f jest ignorowany    
  testAllParameters((char*)"xyzf", token, n);      

  //wymagane parametry, w tym wypadku x lub y, jezeli maja byc wymagane x i y to
  //nalezy wywolac funkcje dwukrotnie, najpierw z 'x', a pozniej z 'y'
  testRequiredParameter((char*)"xyz", token, n);
    
}

  
void G0::createCommand(const std::vector<std::string> &token, Current *cordinate)
{
  std::map<char, float> parameters;
  parameters = initialize(token); //pobieramy tablice asocjacyjna

  if(parameters.find('x') != parameters.end()) {
    m_x = parameters['x'];
  }
  else {
    m_x = cordinate->getX();
  }
    
  if(parameters.find('y') != parameters.end()) {
    m_y = parameters['y'];
  }
  else {
    m_y = cordinate->getY();
  }

  if(parameters.find('z') != parameters.end()) {
    m_z = parameters['z'];
  }
  else {
    m_z = cordinate->getZ();
  }
                          
}

void G0::checkParameters(Current *cordinate, int line)
{

  cordinate->checkX(m_x, line);
  cordinate->checkY(m_y, line);

}  
  
void G0::draw(const Cairo::RefPtr<Cairo::Context>& cr, int width, int height)
{
    /*
    cr->set_line_width(2.0);
    
    int x = width / 2;
    int y = height / 2;
    
    float jednostka_w = width / 50;
    float jednostka_h = height / 50;
    
    int przesun_x = jednostka_w * m_x;
    int przesun_y = jednostka_h * m_y;
    
    if(m_x_empty || m_y_empty) {
      if(m_x_empty) {
        Window::DrawArea::current_y = y - przesun_y;
      }
      
      else if(m_y_empty) {
        Window::DrawArea::current_x = x + przesun_x;
      }
    }
    
    else {
      Window::DrawArea::current_x = x + przesun_x;
      Window::DrawArea::current_y = y - przesun_y;
    }
    
    if(m_z) {
      cr->move_to(Window::DrawArea::current_x, Window::DrawArea::current_y);
    }
    
    else {
    cr->line_to(Window::DrawArea::current_x, Window::DrawArea::current_y);
    }*/
    
}

void G0::execute (StepperControl *stepper, Current *cordinate)
{
  /*1.Podnosimy lub opuszczamy mazak
    2.Ruszamy silnikami
    3.Zapamietujemy obecne wspolrzedne
  */
  cordinate->setZ(m_z);
  stepper->servoMove(m_z);
  stepper->ddaMove(m_x, m_y);
  cordinate->setCurrent(m_x, m_y);
       
}



void G2::validate(const std::vector<std::string> &token, int n)
{
    
  testAllParameters((char*)"xyzijf", token, n);
   
  testRequiredParameter((char*)"xy", token, n);
  testRequiredParameter((char*)"i", token, n);
  testRequiredParameter((char*)"j", token, n);
    
}

  
void G2::createCommand(const std::vector<std::string> &token, Current *cordinate)
{
  std::map<char, float> parameters;
    
  parameters = initialize(token);
    
  if(parameters.find('x') != parameters.end()) {
    m_x = parameters['x'];
  }
  else {
    m_x = cordinate->getX();
  }
    
  if(parameters.find('y') != parameters.end()) {
    m_y = parameters['y'];
  }
  else {
    m_y = cordinate->getY();
  }

  if(parameters.find('z') != parameters.end()) {
    m_z = parameters['z'];
  }
  else {
    m_z = cordinate->getZ();
  }
    
  m_i = parameters['i'];
  m_j = parameters['j'];

}

void G2::checkParameters(Current *cordinate, int line)
{

  cordinate->checkX(m_x, line);
  cordinate->checkY(m_y, line);

}  

  
void G2::draw(const Cairo::RefPtr<Cairo::Context>& cr, int width, int height)
{
  //todo
}

  
void G2::execute(StepperControl *stepper, Current *cordinate)
{
    
  cordinate->setZ(m_z);
  stepper->servoMove(m_z);
  stepper->initArcMove(m_x, m_y, m_i, m_j, false, cordinate->getX(), cordinate->getY());
  cordinate->setCurrent(m_x, m_y);
    
}



void G3::validate(const std::vector<std::string> &token, int n)
{
    
  testAllParameters((char*)"xyzijf", token, n);
   
  testRequiredParameter((char*)"xy", token, n);
  testRequiredParameter((char*)"i", token, n);
  testRequiredParameter((char*)"j", token, n);
  
}

  
void G3::createCommand(const std::vector<std::string> &token, Current *cordinate)
{
  std::map<char, float> parameters;
    
  parameters = initialize(token);

  if(parameters.find('x') != parameters.end()) {
    m_x = parameters['x'];
  }
  else {
    m_x = cordinate->getX();
  }
    
  if(parameters.find('y') != parameters.end()) {
    m_y = parameters['y'];
  }
  else {
    m_y = cordinate->getY();
  }

  if(parameters.find('z') != parameters.end()) {
    m_z = parameters['z'];
  }
  else {
    m_z = cordinate->getZ();
  }
  m_i = parameters['i'];
  m_j = parameters['j'];

  }

void G3::checkParameters(Current *cordinate, int line)
{

  cordinate->checkX(m_x, line);
  cordinate->checkY(m_y, line);

}  

  
void G3::draw(const Cairo::RefPtr<Cairo::Context>& cr, int width, int height)
{
    //todo
}

  
void G3::execute(StepperControl *stepper, Current *cordinate)
{
  cordinate->setZ(m_z);
  stepper->servoMove(m_z);
  stepper->initArcMove(m_x, m_y, m_i, m_j, true, cordinate->getX(), cordinate->getY());
  cordinate->setCurrent(m_x, m_y);
  
}

