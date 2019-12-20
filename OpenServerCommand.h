//
// Created by omer on 19/12/2019.
//

#ifndef ALGORITHMICPROGRAMMINGPROJECT__OPENSERVERCOMMAND_H_
#define ALGORITHMICPROGRAMMINGPROJECT__OPENSERVERCOMMAND_H_

#include "Command.h"
#include <thread>
#include <netinet/in.h>

using namespace std;
class OpenServerCommand : public Command {
 private:
  int port;
  bool listening;
  thread myThread;

 public:
  OpenServerCommand(int port) : port(port), listening(true) {};
  virtual int execute();
};

#endif //ALGORITHMICPROGRAMMINGPROJECT__OPENSERVERCOMMAND_H_
