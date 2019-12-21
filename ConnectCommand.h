//
// Created by Dor on 19/12/2019.
//

#ifndef ALGORITHMICPROGRAMMINGPROJECT__CONNECTCOMMAND_H_
#define ALGORITHMICPROGRAMMINGPROJECT__CONNECTCOMMAND_H_

#include "Command.h"
#include <string>

using namespace std;

class ConnectCommand : public Command {
 private:
  int port;
  const char *ip;
  int clientSocket;

 public:
  ConnectCommand(const char *port, const char *ip);
  void sendToHost(const char *str);
  //TODO ~ConnectCommand if handles threads - remember to update D'tor.
  ~ConnectCommand();
  virtual int execute() override;
  int skip() {
      return 3;
  }
};

#endif //ALGORITHMICPROGRAMMINGPROJECT__CONNECTCOMMAND_H_
