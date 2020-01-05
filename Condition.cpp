//
// Created by Dor Refaeli on 22/12/2019.
//

#include "Condition.h"


using namespace std;

Condition::Condition(SymbolTable *symTable, string str) {
    this->symbolTable = symTable;
    regex re("\\s*(.*) (=|<|>|<=|>=|!=) (.*)");
    smatch m;
    regex_search(str, m, re);
    this->left = m[1];
    this->sign = m[2];
    this->right = m[3];
}

bool Condition::getState() const {
    float leftValue = this->symbolTable->getVariable(this->left);
    float rightValue = this->symbolTable->getVariable(this->right);
    if (this->sign == "=") {
        return leftValue == rightValue;
    } else if (this->sign == "<") {
        return leftValue < rightValue;
    } else if (this->sign == ">") {
        return leftValue > rightValue;
    } else if (this->sign == "<=") {
        return leftValue <= rightValue;
    } else if (this->sign == ">=") {
        return leftValue >= rightValue;
    } else if (this->sign == "!=") {
        return leftValue != rightValue;
    } else {
        throw "Error processing a condition";
    }
}
