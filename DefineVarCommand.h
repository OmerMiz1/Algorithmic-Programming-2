//
// Created by Dor on 19/12/2019.
//

#ifndef ALGORITHMICPROGRAMMINGPROJECT__DEFINEVARCOMMAND_H_
#define ALGORITHMICPROGRAMMINGPROJECT__DEFINEVARCOMMAND_H_

#include "Command.h"
#include "SymbolTable.h"
#include <string>
#include <unordered_map>

using namespace std;

class DefineVarCommand : public Command {
private:
    SymbolTable *symbolTable;
public:
    /**
     * Construct a new DefineVarCommand according to a symbol table
     * @param symTable the symbol table for the DefineVarCommand
     */
    DefineVarCommand(SymbolTable *symTable);
    ~DefineVarCommand();
    int execute(list<string>::iterator) override;

private:
    /**
     * Gets a string and determines if he his of type float
     * @param str the string that needs to be checked
     * @return true if the string his a float, false otherwise
     */
    static bool isFloat(string str);
};

#endif //ALGORITHMICPROGRAMMINGPROJECT__DEFINEVARCOMMAND_H_
