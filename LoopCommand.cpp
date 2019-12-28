//
// Created by omer on 19/12/2019.
//



#include "LoopCommand.h"

LoopCommand::LoopCommand(SymbolTable* table): ConditionCommand(table){}

int LoopCommand::execute(list<string>::iterator it) {

  //TODO says i must have condition object here.
  //TODO should be handled in a priority queue somehow, for now just the map
  return 0;
}


