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
    /**
     * Construct a new condition
     * @param symTable the symbol table that the condition is checked according to
     * @param str a string that describes the condition
     */
    explicit Condition(SymbolTable * symTable, string str);

    /**
     * Returns the state of the condition
     * @return true if the condition is true, false otherwise
     */
    bool getState() const;
};


#endif //ALGORITHMICPROGRAMMINGPROJECT_CONDITION_H
