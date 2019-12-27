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
  sockaddr_in address;

 public:
  /*OpenServerCommand(string port);*/
  int execute(list<string>::iterator) override;
};

#endif //ALGORITHMICPROGRAMMINGPROJECT__OPENSERVERCOMMAND_H_
