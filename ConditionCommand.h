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

using namespace std;

class ConditionCommand : public Command {
protected:
    unordered_map<string, float> *symbolTable; // map of <name, value>
    //TODO support global vars/cmds
    /*unordered_map<string,list<pair<string,Var*>>> varMap;
    unordered_map<string,list<pair<string,Var*>>>* globalVarMap;*/

public:
    ConditionCommand(unordered_map<string, float> *symbolTable, );

    int execute(list<string>::iterator) override;

    virtual bool done() = 0;

    void setCommandMap(unordered_map<string, list<pair<string, Command *>>::iterator> newMap);

    void setVarMap(unordered_map<string, list<pair<string, Var *>>::iterator> newMap);
};

#endif //ALGORITHMICPROGRAMMINGPROJECT__CONDITIONCOMMAND_H_
