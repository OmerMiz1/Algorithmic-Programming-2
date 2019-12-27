//
// Created by omer on 19/12/2019.
//



#include "LoopCommand.h"

//bellow c'tor invokes ConditionCommand's c'tor to initialize its fields.
LoopCommand::LoopCommand(string condition): ConditionCommand(move(condition)) {}

int LoopCommand::execute(list<string>::iterator it) {
  //TODO says i must have condition object here.
  while (ConditionCommand::execute()) {
    //TODO should be handled in a priority queue somehow, for now just the map
    for(auto it : this->cmdMap) {
      it.second->second->execute();
      // remove cmd from list somehow? wrap it so it can remove itself?
    }
  }
  return 0;
}


