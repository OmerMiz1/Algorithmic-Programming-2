//
// Created by omer on 19/12/2019.
//

#ifndef ALGORITHMICPROGRAMMINGPROJECT__CONDITIONCOMMAND_H_
#define ALGORITHMICPROGRAMMINGPROJECT__CONDITIONCOMMAND_H_

#include <string>
#include <unordered_map>
#include <list>
#include <utility>
#include "Command.h"
#include "Condition.h"
#include "Var.h"
#include "SymbolTable.h"

using namespace std;

class ConditionCommand : public Command {
protected:
    SymbolTable *symTable;
    //TODO support global vars

public:
    explicit ConditionCommand(SymbolTable *table);
    int execute(list<string>::iterator) override;
};

#endif //ALGORITHMICPROGRAMMINGPROJECT__CONDITIONCOMMAND_H_
