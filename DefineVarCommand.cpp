//
// Created by Dor on 19/12/2019.
//

#include <utility>
#include <iostream>
#include "DefineVarCommand.h"
#include "Expression.h"

DefineVarCommand::DefineVarCommand(SymbolTable *symTable) : symbolTable(symTable) {}

/*
 * Execution has 2 options:
 * 1. Send data about var to the simulator.
 * 2. Update data received  about var from the simulator.
 */
int DefineVarCommand::execute(list<string>::iterator it) {
    bool assignment = false;
    int skip;

    if (it->compare("var") == 0) {
        ++it; // "var" advance to "<var_name>"
        skip = 4;
        //TODO check if exist
    } else {
        assignment = true;
        skip = 3;
    }

    string name = *it;
    ++it; // "<var_name> advance to "<operation_type>", {"<-", "->", "="}
    string direction = *it;
    ++it; // "<operation_type>" advance to "<var_value>" {value \ another var}
    string value = *it;

    if(assignment) {
        this->symbolTable->setVariable(name, stof(value));
    } else if (direction.compare("->") == 0 || direction.compare("<-") == 0) {
        this->symbolTable->setRemoteVariable(name, direction, value);
    } else if (direction.compare("=") == 0) {
        if (this->isFloat(value)) {
            this->symbolTable->defineVariable(name, stof(value));
        } else {
            this->symbolTable->defineVariable(name, this->symbolTable->getVariable(value));
        }
    } else {
        //TODO this line is only for debugging, remove before done
        throw "ERROR in add defineVarCommand with:" + name + " " + direction + " " + value;
    }
    return skip; //returns the amount to be skipped after this command, 4 - if starts with "var", 3 - if not
}

bool DefineVarCommand::isFloat(string str) {
    bool wasDot = false;
    string::iterator it = str.begin();
    while (it != str.end()) {
        if (*it == '.') {
            if (!wasDot) {
                wasDot = true;
                it++;
                continue;
            } else {
                return false;
            }
        }
        if (*it!='0' && *it!='1' && *it!='2' && *it!='3' && *it!='4' &&
                *it!='5' && *it!='6' && *it!='7' && *it!='8' && *it!='9') {
            return false;
        }
        it++;
    }
    return true;
}

DefineVarCommand::~DefineVarCommand() {

}
