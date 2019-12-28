//
// Created by omer on 19/12/2019.
//

#ifndef ALGORITHMICPROGRAMMINGPROJECT__LOOPCOMMAND_H_
#define ALGORITHMICPROGRAMMINGPROJECT__LOOPCOMMAND_H_

#include <unordered_map>
#include <list>
#include <string>
#include <utility>
#include "ConditionCommand.h"
#include "Command.h"
#include "Var.h"

class LoopCommand : public ConditionCommand {
 public:
  explicit LoopCommand(SymbolTable*);
  int execute(list<string>::iterator) override;
};

#endif //ALGORITHMICPROGRAMMINGPROJECT__LOOPCOMMAND_H_
