//
// Created by omer on 19/12/2019.
//

#ifndef ALGORITHMICPROGRAMMINGPROJECT__OPENSERVERCOMMAND_H_
#define ALGORITHMICPROGRAMMINGPROJECT__OPENSERVERCOMMAND_H_

#include "Command.h"
#include <thread>

using namespace std;
class OpenServerCommand : public Command {
 private:
  int port;
  thread t;

 public:
  OpenServerCommand(int port);
  virtual int execute();
  int openServer();
};

#endif //ALGORITHMICPROGRAMMINGPROJECT__OPENSERVERCOMMAND_H_
