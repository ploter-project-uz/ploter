#ifndef factory
#define factory

class Command;

#include<memory>


class Factory 
{  
public:
  
  static std::shared_ptr<Command> getCommand(const std::string &token, int n);
};

#endif
