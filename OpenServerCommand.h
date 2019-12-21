//
// Created by omer on 19/12/2019.
//

#ifndef ALGORITHMICPROGRAMMINGPROJECT__OPENSERVERCOMMAND_H_
#define ALGORITHMICPROGRAMMINGPROJECT__OPENSERVERCOMMAND_H_

#include "Command.h"
#include <thread>
#include <netinet/in.h>
#include <iostream>

using namespace std;
class OpenServerCommand : public Command {
 private:
  int port;
  bool listening = true;

 public:
  OpenServerCommand(string port);
  virtual int execute();
};

#endif //ALGORITHMICPROGRAMMINGPROJECT__OPENSERVERCOMMAND_H_
