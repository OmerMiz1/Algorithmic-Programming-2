//
// Created by omer on 19/12/2019.
//

#ifndef ALGORITHMICPROGRAMMINGPROJECT__LOOPCOMMAND_H_
#define ALGORITHMICPROGRAMMINGPROJECT__LOOPCOMMAND_H_

#include <unordered_map>
#include <list>
#include <string>
#include <utility>
#include "Condition.h"
#include "Var.h"
#include "Command.h"
#include "Parser.h"

class LoopCommand : protected ConditionCommand {
 private:
  unordered_map<string, list<pair<string, Command*>>::iterator> cmdMap;
  unordered_map<string,Var*> varMap;

 public:
  LoopCommand(string condition, Parser* parser);
  virtual int execute() override;

  /*void setVarMap(unordered_map<string,Var*>);
  void setCommandMap(unordered_map<string, list<pair<string,Command*>>::iterator>);*/
};

#endif //ALGORITHMICPROGRAMMINGPROJECT__LOOPCOMMAND_H_
