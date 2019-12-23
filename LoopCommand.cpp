//
// Created by omer on 19/12/2019.
//



#include "LoopCommand.h"

//bellow c'tor invokes ConditionCommand's c'tor to initialize its fields.
LoopCommand::LoopCommand(string condition, Parser* parser): ConditionCommand(move(condition)) {
  this->cmdMap = move(parser->getCmdMap());
  this->varMap = move(parser->getVarMap());
}

/*void LoopCommand::setCommandMap(unordered_map<string, list<pair<string, Command *> >::iterator> newMap) {
  this->cmdMap = move(newMap);
}

void LoopCommand::setVarMap(unordered_map<string,Var*> newMap){
  this->varMap = move(newMap);
}*/

int LoopCommand::execute() {
  //TODO says i must have condition object here.
  while (Condition::getState(this->condition)) {
    //TODO should be handled in a priority queue somehow, for now just the map
    for(auto it : this->cmdMap) {
      it.second->second->execute();
      // remove cmd from list somehow? wrap it so it can remove itself?
    }
  }
  return 0;
}
