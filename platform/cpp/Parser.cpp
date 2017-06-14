#include "Parser.hpp"


const char* const DELIMITER = (" ");


void Parser::parse(std::string text, int lineNumber)
{
  
  boost::split(token, text, boost::is_any_of(DELIMITER), boost::token_compress_on); //tworzymy tokeny

  commentIgnore();
  checkLineNumberParameter();
  deleteSpacesAtStart();
  deleteSpacesAtEnd();
  emptyLineCheck();
  replaceCommas();
  valueValidate(lineNumber);

}


void Parser::valueValidate(int lineNumber)
{

  //sprawdzamy czy wartosci parametrow nie zawieraja niedozwolonych znakow
  int j,i;
  
  for(i = 0; i < token.size(); i++) {
    
    for(j = 1; j < token[i].size(); j++) {
      
      if(!isdigit(token[i][j]) && token[i][j] != '.' && token[i][j] != ',' && token[i][j] != '-') {
	std::string error = "Invalid value: " + token[i] + " in line number: " + std::to_string(lineNumber);
        throw error;
      }
    }
  }
  
}


int Parser::checkLineNumberParameter()
{
  
  if(tolower(token[0][0]) == 'n') {
    token.erase(token.begin());
    return 1;
  }
  
  return 0;
}


void Parser::deleteSpacesAtEnd()
{

  if(token.back() == "") {
    token.pop_back();      
  }
  
}


void Parser::deleteSpacesAtStart()
{
  if(token.front() == "") {
    token.erase(token.begin());
  }
}


void Parser::emptyLineCheck()
{
  
  if(token.front() == "") { 
    throw 1;                
  }
  
}


void Parser::commentIgnore()
{
  
  if(token[0][0] == '(' || token[0][0] == ';') {
    throw 1;
  }
  
}


void Parser::replaceCommas()
{
  for(auto& value: token) {
    std::replace(value.begin(), value.end(), ',', '.');
  }
  
}
