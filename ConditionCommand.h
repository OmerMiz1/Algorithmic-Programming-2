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
  // C'tor may only be invoked from a subclass, we decide the condition types.
  ConditionCommand(string cond);
  string condition;
  unordered_map<string, list<pair<string,Command*>>::iterator> cmdMap;
  unordered_map<string, list<pair<string,Var*>>::iterator> varMap;
  //TODO support global vars/cmds
  /*unordered_map<string,list<pair<string,Var*>>> varMap;
  unordered_map<string,list<pair<string,Var*>>>* globalVarMap;*/

public:
  int execute(list<string>::iterator) override;
  void setCommandMap(unordered_map<string,list<pair<string,Command *>>::iterator> newMap);
  void setVarMap(unordered_map<string,list<pair<string,Var*>>::iterator> newMap);
};

#endif //ALGORITHMICPROGRAMMINGPROJECT__CONDITIONCOMMAND_H_
