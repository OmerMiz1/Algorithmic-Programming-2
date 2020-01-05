//
// Created by omer on 19/12/2019.
//

#ifndef ALGORITHMICPROGRAMMINGPROJECT__OPENSERVERCOMMAND_H_
#define ALGORITHMICPROGRAMMINGPROJECT__OPENSERVERCOMMAND_H_

#define MAX_CHARS 1024

#include <string>
#include <chrono>
#include <iostream>
#include <thread>
#include <algorithm>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include "Command.h"
#include "SymbolTable.h"
#include "Parser.h"
#include "ProgramState.h"

using namespace std;

class OpenServerCommand : public Command {
private:
    int sockfd = 0;
    int client_sock = 0;
    bool done=false;
    SymbolTable *symTable;
    ProgramState *programState;

    void startListening();

public:
    OpenServerCommand(SymbolTable *, ProgramState *);

    ~OpenServerCommand();

    int execute(list<string>::iterator) override;

    void toTokens(const char *, list<string> *);

    void mapTokens(list<string> *, unordered_map<int, float> *);

    void updateIngoing(unordered_map<int, float> *);

    void clearOldTokens(list<string> *);

    bool *isDone() {return &(this->done);}
};

#endif //ALGORITHMICPROGRAMMINGPROJECT__OPENSERVERCOMMAND_H_
