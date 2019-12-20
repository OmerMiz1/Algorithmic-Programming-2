//
// Created by omer on 19/12/2019.
//
#include <utility>
#include "DefineVarCommand.h"

DefineVarCommand::DefineVarCommand(string name, string direction, string sim)
    : name(move(name)), direction(move(direction)), sim(move(sim)) {}
/*
 * Execution has 2 options:
 * 1. Send data about var to the simulator.
 * 2. Update data received  about var from the simulator.
 */
int DefineVarCommand::execute() {
  if(direction.compare("->") != 0 && direction.compare("<-") != 0) {
    throw "Error in : DefineVarCommand:execute(). Var has no direction.";
  }

  if (direction.compare("->") == 0) {

  } else {

  }
  return 4;
}
