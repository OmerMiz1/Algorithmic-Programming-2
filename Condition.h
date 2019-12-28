//
// Created by Dor Refaeli on 22/12/2019.
//

#ifndef ALGORITHMICPROGRAMMINGPROJECT_CONDITION_H
#define ALGORITHMICPROGRAMMINGPROJECT_CONDITION_H


#include "Expression.h"
#include "Command.h"

class Condition {
    Condition(string str);

//TODO should be protected for LoopCommand to reuse
    string left;
    string sign;
    string right;
    Interpreter *interpreter;

public:
    void setVariables(string str);
    bool getState() const;
};


#endif //ALGORITHMICPROGRAMMINGPROJECT_CONDITION_H
