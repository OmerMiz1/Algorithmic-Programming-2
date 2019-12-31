//
// Created by Dor on 19/12/2019.
//

#include <utility>
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
    if (it->compare("var") == 0) {
        ++it; // "var" advance to "<var_name>"
        //TODO check if exist
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
        interpreter->setVariables(this->symbolTable->updatedMap());
        Expression *expression = interpreter->interpret(value);
        this->symbolTable->setVariable(name, expression->calculate());
    } else {
        //TODO this line is only for debugging, remove before done
        throw "ERROR in add defineVarCommand with:" + name + " " + direction + " " + value;
    }
    return 4; // next command token is 4 tokens ahead.
}
