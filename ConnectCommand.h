//
// Created by Dor on 19/12/2019.
//

#ifndef ALGORITHMICPROGRAMMINGPROJECT__CONNECTCOMMAND_H_
#define ALGORITHMICPROGRAMMINGPROJECT__CONNECTCOMMAND_H_

#include "Command.h"
#include "SymbolTable.h"
#include <string>

using namespace std;

class ConnectCommand : public Command {
    SymbolTable *symbolTable;
    static list<const char *> cmdQueue;
public:

    ConnectCommand(SymbolTable *symbolTable);

    static void startSending(int clientSocket, SymbolTable *);

    int execute(list<string>::iterator) override;

};

#endif //ALGORITHMICPROGRAMMINGPROJECT__CONNECTCOMMAND_H_
