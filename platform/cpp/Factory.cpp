#include "Factory.hpp"
#include "Command.hpp"
#include "Gcode.hpp"

#include<memory>

#include<string>

#define COMMAND_SIZE_MAX 3
#define COMMAND_SIZE_MIN 2


Command::SPtr Factory::getCommand(const std::string &token, int n) 
{
  
  std::string error = "Unknown command " + token + " in line number " + std::to_string(n);

  if(token.size() > COMMAND_SIZE_MAX || token.size() < COMMAND_SIZE_MIN) {
    throw error;
  }
  
  int number = std::atoi(&token[1]);
  
  if(tolower(token[0]) == 'g') {
    
    switch (number) {
      
      case 0:
      case 1:
        return std::make_shared<G0>();
        break;
	
      case 2:
        return std::make_shared<G2>();
        break;
	
      case 3:
        return std::make_shared<G3>();
        break;
	
      default:
        throw error;
    }
    
  }
  
  else if(tolower(token[0]) == 'm') {
    
    switch (number) {
      
      default:
        throw error;
    }
  }
  
  else {
    throw error;
  }
  
}



















