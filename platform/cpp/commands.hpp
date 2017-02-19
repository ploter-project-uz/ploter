#ifndef commands
#define commands

#include <iostream>
using std::cout;
using std::endl;

#include <fstream>
using std::ifstream;

#include <cstring>

#include<string>
using std::string;

#include<vector>
using std::vector;

#include<boost/algorithm/string.hpp>
using boost::is_any_of;
using boost::token_compress_on;

#include<map>
using std::map;

#include<sstream>
using std::stringstream;

const int MAX_CHARS_PER_LINE = 512;
const int MAX_TOKENS_PER_LINE = 20;
const char* const DELIMITER = (" ");
const int MAX_Y = 50;
const int MAX_X = 50;


class Command;

class Factory 
{
public:
  static Command* getCommand(string token, int n);
};


class Command 
{
public:
  virtual void validator(vector<string> token, int n) = 0;
  virtual void createCommand(vector<string> token) = 0;
  virtual void execute() = 0;
  static void allParametrs(char* parametrs, vector<string> token, int n);
  static void requiredParametr(char* parametrs, vector<string> token, int n);
  static map<char, float> initialize(vector<string> token);
};


class Parser 
{
public:
  vector<string> token;
  void parser(ifstream &fin, int line);
  vector<string> getCopyOfVector(); 
};

#endif
