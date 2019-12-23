//
// Created by omer on 19/12/2019.
//



#include "LoopCommand.h"

LoopCommand::LoopCommand(string condition, Parser parser) {
  this->condition = new Condition(condition);
  this->cmdMap = move(parser.getCmdMap());
  this->varMap = move(parser.getVarMap());
}

/*void LoopCommand::setCommandMap(unordered_map<string, list<pair<string, Command *> >::iterator> newMap) {
  this->cmdMap = move(newMap);
}

void LoopCommand::setVarMap(unordered_map<string,Var*> newMap){
  this->varMap = move(newMap);
}*/

int LoopCommand::execute() {
  //TODO implement
  return 0;
}
