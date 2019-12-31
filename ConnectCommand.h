//
// Created by Dor on 19/12/2019.
//

#ifndef ALGORITHMICPROGRAMMINGPROJECT__CONNECTCOMMAND_H_
#define ALGORITHMICPROGRAMMINGPROJECT__CONNECTCOMMAND_H_

#include <string>
#include <iostream>
#include <thread>
#include <cstring>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "Command.h"
#include "SymbolTable.h"
#include "ProgramState.h"

using namespace std;

class ConnectCommand : public Command {
private:
    int clientSocket;
    SymbolTable *symbolTable;
    ProgramState *programState;
    list<const char *> cmdQueue;
    int isConnect = 0;

public:
    ConnectCommand(SymbolTable *, ProgramState *);

    int execute(list<string>::iterator) override;

    void addToCmdQueue(const char *);

    void startSending();

    void setState(ProgramState *);

    void addToCmdQueue(string); // TODO to remove?
};

#endif //ALGORITHMICPROGRAMMINGPROJECT__CONNECTCOMMAND_H_
