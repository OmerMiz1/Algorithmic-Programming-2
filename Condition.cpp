//
// Created by Dor Refaeli on 22/12/2019.
//

#include "Condition.h"
#include <regex>

using namespace std;
Condition::Condition(string str) {
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
    Expression *tempLeft = this->interpreter->interpret(this->left);
    Expression *tempRight = this->interpreter->interpret(this->right);
    if (this->sign == "=") {
        return tempLeft->calculate() == tempRight->calculate();
    } else if (this->sign == "<") {
        return tempLeft->calculate() < tempRight->calculate();
    } else if (this->sign == ">") {
        return tempLeft->calculate() > tempRight->calculate();
    } else if (this->sign == "<=") {
        return tempLeft->calculate() <= tempRight->calculate();
    } else if (this->sign == ">=") {
        return tempLeft->calculate() >= tempRight->calculate();
    } else if (this->sign == "!=") {
        return tempLeft->calculate() != tempRight->calculate();
    } else {
        throw "Error processing a condition";
    }
}
