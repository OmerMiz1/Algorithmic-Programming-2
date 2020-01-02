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
    //  TODO not clear if interpreter knows about the variables in the map or
    //    just instantiating variables by their names. example below.
    /* if i send interpreter h0 == heading, how will he know the values of h0 and heading?
     * Idea for solution, first get the variables by REFERENCE (explain after)
     * and make a dedicated function in interpreter to support adding variables
     * by reference. why? because this way if the var is being updated DURING a while loop for example,
     * our condition will always be updated without being in charge of getting those updates.
    */
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
