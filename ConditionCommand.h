//
// Created by omer on 19/12/2019.
//

#ifndef ALGORITHMICPROGRAMMINGPROJECT__CONDITIONCOMMAND_H_
#define ALGORITHMICPROGRAMMINGPROJECT__CONDITIONCOMMAND_H_

#include <string>
#include <unordered_map>
#include <list>
#include <utility>
#include "Command.h"
#include "Condition.h"
#include "Var.h"

using namespace std;

class ConditionCommand: public Command{
protected:
  ConditionCommand(string cond): condition(move(cond)){};
  string condition;
  unordered_map<string, list<pair<string,Command*>>::iterator> cmdMap;
  unordered_map<string,Var*> varMap;

public:
  virtual int execute() override;
};

#endif //ALGORITHMICPROGRAMMINGPROJECT__CONDITIONCOMMAND_H_
