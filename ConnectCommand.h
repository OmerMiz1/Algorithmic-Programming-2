//
// Created by omer on 19/12/2019.
//

#ifndef ALGORITHMICPROGRAMMINGPROJECT__CONNECTCOMMAND_H_
#define ALGORITHMICPROGRAMMINGPROJECT__CONNECTCOMMAND_H_

#include "Command.h"
#include <string>

using namespace std;

class ConnectCommand : public Command {
 private:
  int port;
  string ip;

 public:
  ConnectCommand(int port,string ip);
  //TODO ~ConnectCommand if handles threads - remember to update D'tor.
  ~ConnectCommand() = default;
  /*The reason its virtual - Eli said in one of
   the videos its good practice to do so, this way you can remember it was
   inherited or someting like that.. delete this after you read it :)*/
  virtual int execute() override;

};

#endif //ALGORITHMICPROGRAMMINGPROJECT__CONNECTCOMMAND_H_
