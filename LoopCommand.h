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

class LoopCommand : public Command {
 private:
  Condition condition;
  unordered_map<string, list<pair<string,Command*>>::iterator> cmdMap;
  unordered_map<string,Var*> varMap;


 public:
  LoopCommand(string name,unordered_map<string, list<pair<string,Command*>>::iterator> cmds,
      unordered_map<string,Var*> vars): cmdMap(move(cmds)), varMap(move(vars)){}

  void addVar(string name, string value);
  void addCommand(string name, string value);
  virtual int execute() override {};

};

#endif //ALGORITHMICPROGRAMMINGPROJECT__LOOPCOMMAND_H_
