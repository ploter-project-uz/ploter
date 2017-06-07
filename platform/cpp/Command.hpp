#ifndef COMMAND_HPP
#define COMMAND_HPP

#include<vector>

#include<memory>

#include<string>

#include<gtkmm.h>

#include<map>


const int COMMAND_SIZE = 3;
const char* const DELIMITER = (" ");

class StepperControl;
class Current;

class Command 
{
public:
  
  typedef std::shared_ptr<Command> SPtr;
  typedef std::vector<Command::SPtr> vector_SPtr;
  
  virtual ~Command() {}
  
  virtual void validate( const std::vector<std::string> &token, int n) = 0;
  virtual void createCommand( const std::vector<std::string> &token, Current *cordinate) = 0;
  virtual void checkParameters( Current *cordinate, int line) = 0;
  virtual void execute( StepperControl *stepper, Current *cordinate) = 0;
  virtual void draw( const Cairo::RefPtr<Cairo::Context>& cr, int width, int height) = 0;
  
  int testAllParameters(char* parametrs, const std::vector<std::string> &token, int n);
  int testRequiredParameter(char* parametrs, const std::vector<std::string> &token, int n);
  
  std::map<char, float> initialize( const std::vector<std::string> &token);

};

#endif
