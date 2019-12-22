//
// Created by omer on 19/12/2019.
//

#ifndef ALGORITHMICPROGRAMMINGPROJECT__DEFINEVARCOMMAND_H_
#define ALGORITHMICPROGRAMMINGPROJECT__DEFINEVARCOMMAND_H_

#include "Command.h"
#include <string>

using namespace std;

class DefineVarCommand : public Command {
 private:
  string name, direction, sim;
 public:

  //TODO can have: <- -> and = for assignment
  DefineVarCommand(string name, string direction, string sim);// with <-\->
  DefineVarCommand(string name, string value); // assignment (var = new value)
  virtual int execute() override;
};

#endif //ALGORITHMICPROGRAMMINGPROJECT__DEFINEVARCOMMAND_H_
