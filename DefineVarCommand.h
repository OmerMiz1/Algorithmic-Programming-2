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
  string name, operation, sim;
 public:
  //TODO can have: <- -> and = for assignment
  DefineVarCommand(string name, string operation, string sim);// with <-\->
  int execute(list<string>::iterator) override;
};

#endif //ALGORITHMICPROGRAMMINGPROJECT__DEFINEVARCOMMAND_H_
