//
// Created by omer on 19/12/2019.
//

#ifndef ALGORITHMICPROGRAMMINGPROJECT__OPENSERVERCOMMAND_H_
#define ALGORITHMICPROGRAMMINGPROJECT__OPENSERVERCOMMAND_H_

#include <string>
#include <chrono>
#include <iostream>
#include <thread>
#include <sys/socket.h>
#include <netinet/in.h>
#include <zconf.h>

#include "Command.h"
#include "SymbolTable.h"
#include "Parser.h"

using namespace std;
class OpenServerCommand : public Command {
 private:
  SymbolTable *symTable;
  static bool running;
  static void startListening(int, SymbolTable*);

 public:
  explicit OpenServerCommand(SymbolTable *symTable);
  int execute(list<string>::iterator) override;

};

#endif //ALGORITHMICPROGRAMMINGPROJECT__OPENSERVERCOMMAND_H_
