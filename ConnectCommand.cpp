//
// Created by omer on 19/12/2019.
//

#include "ConnectCommand.h"
#include <utility>

using namespace std;

ConnectCommand::ConnectCommand(int port, string ip)
    : port(port), ip(move(ip)) {}

int ConnectCommand::execute() {
  //TODO implement function
  return 0;
}

