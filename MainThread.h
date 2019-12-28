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
#include "Sleep.h"
#include "Print.h"


class MainThread : Command {
 private:
  void initCommands(unordered_map<string, Command*>*, SymbolTable*);

 public:

  //TODO link running state for OpenServerCommand, ConnectCommand, MainThread
  // if 1 of them gets an error and stops, the rest will release all memory and
  // return.
  virtual int execute();
};

#endif //ALGORITHMICPROGRAMMINGPROJECT__MAINTHREAD_H_
