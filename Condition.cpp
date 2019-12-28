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
    //TODO not clear if interpreter knows about the variables in the map or just
    // instantiating variables by their names. example below.
    /*if i send interpreter h0 == heading, how will he know the values of h0 and heading?
      Idea for solution, first get the variables by REFERENCE (explain after)
      and make a dedicated function in interpreter to support adding variables
      by reference. why? because this way if the var is being updated DURING a while loop for example,
      our condition will always be updated without being in charge of getting those updates.*/
    this->interpreter->setVariables(str);
}

bool Condition::getState() const {
    //TODO update interpreter variables
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
