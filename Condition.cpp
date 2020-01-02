//
// Created by Dor Refaeli on 22/12/2019.
//

#include "Condition.h"


using namespace std;

Condition::Condition(SymbolTable *symbolTable1, string str) {
    this->symbolTable = symbolTable1;
    regex re("\\s*(.*) (=|<|>|<=|>=|!=) (.*)");
    smatch m;
    regex_search(str, m, re);
    this->interpreter = new Interpreter();
    this->left = m[1];
    this->sign = m[2];
    this->right = m[3];
}

void Condition::setVariables(string str) {
    this->interpreter->setVariables(str);
}

bool Condition::getState() const {
    //TODO update interpreter variables
    float left = this->symbolTable->getVariable(this->left);
    float right = this->symbolTable->getVariable(this->right);
    if (this->sign == "=") {
        return left == right;
    } else if (this->sign == "<") {
        return left < right;
    } else if (this->sign == ">") {
        return left > right;
    } else if (this->sign == "<=") {
        return left <= right;
    } else if (this->sign == ">=") {
        return left >= right;
    } else if (this->sign == "!=") {
        return left != right;
    } else {
        throw "Error processing a condition";
    }
}
