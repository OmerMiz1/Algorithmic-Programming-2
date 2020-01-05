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
    int isConnect = 0;
    bool done =false;
    SymbolTable *symbolTable;
    ProgramState *programState;
    list<const char *> cmdQueue;

public:
    /**
     * Construct a new ConnectCommand according to a SymbolTable and a ProgramState
     * @param symTable the symbol table for the command to use
     * @param programState the program state that the command uses
     */
    ConnectCommand(SymbolTable *, ProgramState *);

    ~ConnectCommand() {};

    int execute(list<string>::iterator it) override;

    /**
     * Opens a connection with the simulator and sends him data continuely, should be executed as a thread.
     */
    void startSending();

    bool* isDone() {return &(this->done);}
};

#endif //ALGORITHMICPROGRAMMINGPROJECT__CONNECTCOMMAND_H_
