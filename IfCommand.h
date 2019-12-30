//
// Created by omer on 19/12/2019.
//

#ifndef ALGORITHMICPROGRAMMINGPROJECT__IFCOMMAND_H_
#define ALGORITHMICPROGRAMMINGPROJECT__IFCOMMAND_H_

#include "ConditionCommand.h"

class IfCommand : public ConditionCommand  {
 public:
  IfCommand(Command*);
  int execute(list<string>::iterator) override;
};

#endif //ALGORITHMICPROGRAMMINGPROJECT__IFCOMMAND_H_
