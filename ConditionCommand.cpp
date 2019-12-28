//
// Created by omer on 19/12/2019.
//

#include "ConditionCommand.h"


ConditionCommand::ConditionCommand(string cond) : condition(move(cond)) {}

int ConditionCommand::execute(list<string>::iterator it) {
    //TODO implement function. should return the Condition::getState() or smthing.
    return 0;
}

void ConditionCommand::setCommandMap(unordered_map<string, list<pair<string, Command *> >::iterator> newMap) {
    this->cmdMap = move(newMap);
}

void ConditionCommand::setVarMap(unordered_map<string, list<pair<string, Var *>>::iterator> newMap) {
    this->varMap = move(newMap);
}

ConditionCommand::ConditionCommand(unordered_map<string, float> *symbolTable) : symbolTable(symbolTable) {}

