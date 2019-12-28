//
// Created by omer on 19/12/2019.
//

#include "IfCommand.h"
#include <utility>

IfCommand::IfCommand(SymbolTable *table):ConditionCommand(table) {}

int IfCommand::execute(list<string>::iterator it) {
  //TODO says i must have condition object here.
  if (ConditionCommand::execute()) {
    //TODO should be handled in a priority queue somehow, for now just the map
    for(auto it : this->cmdMap) {
      it.second->second->execute();
      // remove cmd from list somehow? wrap it so it can remove itself?
    }
  }
  return 0;
}
