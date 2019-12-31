//
// Created by omer on 19/12/2019.
//



#include "LoopCommand.h"

LoopCommand::LoopCommand(Command *main) : ConditionCommand(main) {}

int LoopCommand::execute(list<string>::iterator it) {
    int numOfTokens = ConditionCommand::execute(it);
    advance(it, 2); // skip first line 1st token: type 2nd token: value

    // Call inner (sub) MainThread execute with loop's body scope.
    while (this->myCondition->getState()) {
        this->myMain->execute(it);
    }

    return numOfTokens;
}


