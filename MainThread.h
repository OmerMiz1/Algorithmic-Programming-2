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
    SymbolTable *symTable;
    ProgramState *programState = new ProgramState();
    MainThread *father = nullptr;
    unordered_map<string, Command *> *cmdMap;

    void initCommands();

public:
    MainThread();
    explicit MainThread(SymbolTable*, MainThread*);
    ~MainThread();

    int execute(list<string>::iterator) override;
    int execute();
};

#endif //ALGORITHMICPROGRAMMINGPROJECT__MAINTHREAD_H_
