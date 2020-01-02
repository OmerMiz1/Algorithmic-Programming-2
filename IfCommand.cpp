//
// Created by omer on 19/12/2019.
//

#include "IfCommand.h"

IfCommand::IfCommand(Command *main, SymbolTable *table) : ConditionCommand(main, table) {}

int IfCommand::execute(list<string>::iterator it) {
    int numOfTokens = ConditionCommand::execute(it);
    advance(it, 2); // skip first line 1st token: type 2nd token: value

    // Call inner (sub) MainThread execute with if's body scope.
    if (this->myCondition->getState()) {
        this->myMain->execute(it);
    }
    return numOfTokens;
}
