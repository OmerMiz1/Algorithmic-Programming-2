//
// Created by omer on 27/12/2019.
//

#ifndef ALGORITHMICPROGRAMMINGPROJECT__MAINTHREAD_H_
#define ALGORITHMICPROGRAMMINGPROJECT__MAINTHREAD_H_

#include <string>
#include <list>
#include <unordered_map>
#include <thread>

#include "Lexer.h"
#include "Parser.h"
#include "SymbolTable.h"
#include "Command.h"
#include "OpenServerCommand.h"
#include "ConnectCommand.h"
#include "DefineVarCommand.h"
#include "LoopCommand.h"
#include "IfCommand.h"
#include "Print.h"
#include "Sleep.h"
#include "ProgramState.h"


class MainThread : Command {
private:
    Parser *parser;
    SymbolTable *symTable;
    unordered_map<string, Command *> *cmdMap = new unordered_map<string, Command *>;
    ProgramState *programState = new ProgramState();

    void initCommands();

public:
    MainThread();

    explicit MainThread(SymbolTable *);

    ~MainThread();

    //TODO link running programState for OpenServerCommand, ConnectCommand, MainThread
    // if 1 of them gets an error and stops, the rest will release all memory and
    // return.
    int execute(list<string>::iterator) override;

    int execute();
};

#endif //ALGORITHMICPROGRAMMINGPROJECT__MAINTHREAD_H_
