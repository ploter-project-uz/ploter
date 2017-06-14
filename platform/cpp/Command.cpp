#include "Command.hpp"


int Command::testAllParameters(char* parametrs, const std::vector<std::string> &token, int n)
{
  //jezeli podano nieprawidlowy parametr, wypisujemy blad
  char *pch;
  
  for(int i = 1; i < token.size(); i++) {
    pch = strchr(parametrs, tolower(token[i][0]));

    if(pch == NULL) {
      std::string unknown = "Unknown parameter: " + token[i] + " in line number " + std::to_string(n);
      throw unknown;
    }
  }

  return 0;
}


int Command::testRequiredParameter(char* parametrs, const std::vector<std::string> &token, int n)
{
  
  //jezeli nie podano wymaganego parametru, wypisujemy blad
  char *pch;
  
  for(int i = 1; i < token.size(); i++) {
    pch = strchr(parametrs, tolower(token[i][0]));
    
    if(pch != NULL) {
      return 0;
    }
  }
  
  std::string required = "Required parameters in line number " + std::to_string(n) + " not found";
  throw required;  
}


/*int Command::checkLineNumberParameter(const std::string &token)
{
  if(tolower(token[0]) == 'n') {
    return 1;
  }

  return 0;
  }*/

/*int Command::checkParameters(Current &cordinate, float x, float y)
{
  if(cordinate->checkX(x) == 1) {
    return 1;
  }
  else if(cordinate->checkY(y) == 1) {
    return 2;
  }

  return 0;
  }*/


/*void Command::checkMaxX(float current_x, float x, int n)
{
  
  current_x += x;
  
  if(current_x > MAX_X) {
    string MaxX = "Przekroczenie zakresu X w linii nr " + std::to_string(n);
    throw MaxX;
  }
  
  }*/


 /*void Command::checkMaxY(float current_y, float y, int n)
{
  
  current_y += y;
  
  if(current_y > MAX_Y) {
    string MaxY = "Przekroczenie zakresu Y w linii nr " + std::to_string(n);
    throw MaxY;
  }
  
  }*/


/*void Command::checkMaxZ(float current_z, float z, int n)
{
  
  current_z += z;
  
  if(current_z > MAX_Z || current_z < MIN_Z) {
    string MaxZ = "Przekroczenie zakresu Z w linii nr " + std::to_string(n);
    throw MaxZ;
  }
  
  }*/


std::map<char,float> Command::initialize(const std::vector<std::string> &token)
{
  std::map<char, float> mapa;
  
  for(int i = 1; i < token.size(); i++) {
    mapa[tolower(token[i][0])] = atof(&token[i][1]);
  }
  
  return mapa;
}






