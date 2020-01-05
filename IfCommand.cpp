//
// Created by omer on 19/12/2019.
//

#include "IfCommand.h"


/** main should be of type MainThread from which occurrence is being made.
 *
 * @param main calling command
 * @param table main's symbol table.
 */
IfCommand::IfCommand(Command *main, SymbolTable *table) : ConditionCommand(main, table) {}

/** Executes scope's body if condition is true.
 *
 * @param it iterator to first token ("if").
 * @return number of tokens in scope for main to skip.
 */
int IfCommand::execute(list<string>::iterator it) {
    int numOfTokens = ConditionCommand::execute(it);
    advance(it, 2); // skip first line 1st token: type 2nd token: value

    // Call inner (sub) MainThread execute with if's body scope.
    if (this->myCondition->getState()) {
        this->myMain->execute(it);
    }
    return numOfTokens;
}
