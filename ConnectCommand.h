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

    static void addToCmdQueue(string);

    static void addToCmdQueue(const char *);

    static void startSending(int clientSocket, SymbolTable *);

    int execute(list<string>::iterator) override;

    int skip() {
        return 3;
    }
};

#endif //ALGORITHMICPROGRAMMINGPROJECT__CONNECTCOMMAND_H_
