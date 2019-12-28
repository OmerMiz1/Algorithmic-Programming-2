//
// Created by omer on 19/12/2019.
//
#include <utility>
#include "DefineVarCommand.h"
#include "Expression.h"

DefineVarCommand::DefineVarCommand() {}

/*
 * Execution has 2 options:
 * 1. Send data about var to the simulator.
 * 2. Update data received  about var from the simulator.
 */
int DefineVarCommand::execute(list<string>::iterator it) {

    Command *cmd;
    ++it; // "var" advance to "<var_name>"
    string name = *it;
    ++it; // "<var_name> advance to "<operation_type>", {"<-", "->", "="}
    string operation = *it;
    ++it; // "<operation_type>" advance to "<var_value>" {value \ another var}
    string value = *it;

    if (operation.compare("->") == 0 || operation.compare("<-") == 0) {
        this->remoteVariables[name] = make_pair(operation, value);
    } else if (operation.compare("=") == 0) {
        Interpreter *interpreter = new Interpreter();
        interpreter->setVariables(this->localVariables);
        Expression *expression = interpreter->interpret(value);
        this->localVariables[name] = expression->calculate();
    } else {
        //TODO this line is only for debugging, remove before done
        throw "ERROR in add defineVarCommand with:" + name + " " + operation + " " + value;
    }
    return 4; // next command token is 4 tokens ahead.
}
