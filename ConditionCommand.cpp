//
// Created by omer on 19/12/2019.
//

#include "ConditionCommand.h"

ConditionCommand::ConditionCommand(Command *main, SymbolTable* table)
: myMain(main), symTable(table) {}

ConditionCommand::~ConditionCommand() {
    delete myMain;
    delete symTable;
    delete myCondition;
}

int ConditionCommand::execute(list<string>::iterator it) {
    int count = countScopeTokens(it);

    // 1st token is the "condtion type" and 2nd is the condition itself (string)
    ++it;
    this->myCondition = new Condition(this->symTable, *it);
    return count;
}

/** Return the number of tokens in scope. (each line is made of 2)
 *
 * Only last line that closes scope '}' has 1 token and is being counted too.
 *
 * @param it points to the condition token (1 token after the type token)
 * @param list to update with current scopes tokens.
 * @return a counter to how many tokens has been read, to advance iterator.
 */
int ConditionCommand::countScopeTokens(list<string>::iterator it) {
    int count = 0, scopesCount = 1;

    // In case of inner scopes, keeps counting until the relevant end of scope.
    for (count = 0; it->compare("}") != 0 && scopesCount > 0; ++it, ++count) {
        if (it->compare("if") == 0 || it->compare("while") == 0) { // New scope found
            scopesCount++;
            //TODO might be a bug in nested conditions. might need to increase count
            // in both cases as well (and remove last ++count).
        } else if (it->compare("}") == 0) { // End of scope found.
            scopesCount--;
        }
    }
    ++count; // +1 for the extra '}'
    return count;
}


