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
  //TODO support local variables. example:
  // var <var_name> = <var_value>, like: h0 = 10  or h0 = heading.
  // maybe create 3 Command classes?: ImportVar(<-), ExportVar(->), LocalVar(=).


  return 4;
}
