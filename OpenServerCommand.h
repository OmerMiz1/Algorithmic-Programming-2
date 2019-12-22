//
// Created by omer on 19/12/2019.
//

#ifndef ALGORITHMICPROGRAMMINGPROJECT__OPENSERVERCOMMAND_H_
#define ALGORITHMICPROGRAMMINGPROJECT__OPENSERVERCOMMAND_H_

#include <string>
#include <iostream>
#include <thread>
#include <sys/socket.h>
#include <netinet/in.h>
#include <zconf.h>
#include "Command.h"

using namespace std;
class OpenServerCommand : public Command {
 private:
  int port;

 public:
  OpenServerCommand(string port);
  virtual int execute();
};

#endif //ALGORITHMICPROGRAMMINGPROJECT__OPENSERVERCOMMAND_H_
