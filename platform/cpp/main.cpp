#include "commands.hpp"

int main() {
  ifstream fin;
  vector<string> token;
  int n = 0;
  Command::vector_SPtr vCommands;
  Parser tokenizer;
  fin.open("gcode.txt");
  if(!fin.good())
    return 1;

  while(true) {
    try {
      tokenizer.parser(fin, n);
    }
    catch(string error) {
      cout << error << n+1 << endl;
      exit(1);
    }
    if(fin.eof()) break;
    token = tokenizer.getCopyOfVector();
    vCommands.push_back(Factory::getCommand(token[0],n)); 
    vCommands[n]->validate(token, n); 
    vCommands[n]->createCommand(token);
    n++;
  }
 
  for(Command::SPtr& command: vCommands) {
    command->execute();
  }
  return 0;
}




