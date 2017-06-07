#ifndef PARSER_HPP
#define PARSER_HPP

#include<boost/algorithm/string.hpp>

#include<vector>

#include<string>


class Parser 
{
public:
  
  std::vector<std::string> token;

  ~Parser() {}
  
  void parse(std::string text, int lineNumber);
  
  int checkLineNumberParameter();
  void emptyLineCheck();
  void deleteSpacesAtStart();
  void deleteSpacesAtEnd();
  void replaceCommas();
  void commentIgnore();
  void valueValidate(int lineNumber);
};

#endif
