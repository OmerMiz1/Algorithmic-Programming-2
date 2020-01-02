//
// Created by Dor on 19/12/2019.
//

#include <utility>
#include <iostream>
#include "DefineVarCommand.h"
#include "Expression.h"

DefineVarCommand::DefineVarCommand(SymbolTable *symbolTable) : symbolTable(symbolTable) {}

/*
 * Execution has 2 options:
 * 1. Send data about var to the simulator.
 * 2. Update data received  about var from the simulator.
 */
int DefineVarCommand::execute(list<string>::iterator it) {

    Command *cmd;
    int skip;
    if (it->compare("var") == 0) {
        ++it; // "var" advance to "<var_name>"
        skip = 4;
        //TODO check if exist
    } else {
        skip = 3;
    }
    string name = *it;
    ++it; // "<var_name> advance to "<operation_type>", {"<-", "->", "="}
    string direction = *it;
    ++it; // "<operation_type>" advance to "<var_value>" {value \ another var}
    string value = *it;

    if (direction.compare("->") == 0 || direction.compare("<-") == 0) {
        this->symbolTable->setRemoteVariable(name, direction, value);
    } else if (direction.compare("=") == 0) {
        Interpreter *interpreter = new Interpreter();
        //TODO remove before submit
//        cout<<interpreter->varsCount()<<'\n'<<endl;
        interpreter->setVariables(this->symbolTable->updatedMap());
//        cout<<interpreter->varsCount()<<'\n'<<endl;
        Expression *expression = interpreter->interpret(value);
//        cout<<expression->calculate()<<'\n'<<endl;
        this->symbolTable->setVariable(name, expression->calculate());
//        cout<<symbolTable->getVariable(name)<<endl;
    } else {
        //TODO this line is only for debugging, remove before done
        throw "ERROR in add defineVarCommand with:" + name + " " + direction + " " + value;
    }
    return skip; // next command token is 4 tokens ahead.
}
