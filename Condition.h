//
// Created by Dor Refaeli on 22/12/2019.
//

#ifndef ALGORITHMICPROGRAMMINGPROJECT_CONDITION_H
#define ALGORITHMICPROGRAMMINGPROJECT_CONDITION_H


#include <regex>
#include <string>
#include "Expression.h"
#include "Command.h"
#include "SymbolTable.h"

class Condition {
    string left;
    string sign;
    string right;
    Interpreter *interpreter;
    SymbolTable *symbolTable;
public:
    explicit Condition(SymbolTable *, string);

    void setVariables(string str);

    bool getState() const;
};


#endif //ALGORITHMICPROGRAMMINGPROJECT_CONDITION_H
