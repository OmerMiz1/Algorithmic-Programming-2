//
// Created by omer on 19/12/2019.
//

#ifndef ALGORITHMICPROGRAMMINGPROJECT__OPENSERVERCOMMAND_H_
#define ALGORITHMICPROGRAMMINGPROJECT__OPENSERVERCOMMAND_H_

#include <string>
#include <chrono>
#include <iostream>
#include <thread>
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
  int client_sock = 0;
  thread myThread;
  SymbolTable *symTable;
  ProgramState* programState;

  void startListening();

 public:
  OpenServerCommand(SymbolTable*, ProgramState*);
  int execute(list<string>::iterator) override;

};

#endif //ALGORITHMICPROGRAMMINGPROJECT__OPENSERVERCOMMAND_H_
