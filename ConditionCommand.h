//
// Created by omer on 19/12/2019.
//

#ifndef ALGORITHMICPROGRAMMINGPROJECT__CONDITIONCOMMAND_H_
#define ALGORITHMICPROGRAMMINGPROJECT__CONDITIONCOMMAND_H_

#include <string>
#include <unordered_map>
#include <list>
#include <utility>

#include "Parser.h"
#include "SymbolTable.h"
#include "Command.h"
#include "Condition.h"
#include "Var.h"

using namespace std;

class ConditionCommand : public Command {
protected:
    Command *myMain = NULL;
    Condition *myCondition = NULL;
    //TODO support global vars

public:
    explicit ConditionCommand(Command *main);

    int execute(list<string>::iterator) override;

    int countScopeTokens(list<string>::iterator it);
};

#endif //ALGORITHMICPROGRAMMINGPROJECT__CONDITIONCOMMAND_H_
