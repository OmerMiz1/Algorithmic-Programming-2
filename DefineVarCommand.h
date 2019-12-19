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
  DefineVarCommand(string name, string direction, string sim);
  virtual int execute() override;
};

#endif //ALGORITHMICPROGRAMMINGPROJECT__DEFINEVARCOMMAND_H_
