//
// Created by omer on 19/12/2019.
//
#include <utility>
#include "DefineVarCommand.h"
DefineVarCommand::DefineVarCommand(string name, string direction, string sim)
    : name(move(name)), direction(move(direction)), sim(move(sim)) {}
int DefineVarCommand::execute() {
  //TODO implement function
  return 0;
}
