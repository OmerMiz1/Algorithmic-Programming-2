//
// Created by omer on 20/12/2019.
//

#ifndef ALGORITHMICPROGRAMMINGPROJECT__PRINT_H_
#define ALGORITHMICPROGRAMMINGPROJECT__PRINT_H_

#include <string>
#include <utility>
#include <iostream>
#include "Command.h"
using namespace std;

class Print : public Command {
 private:
  string msg;

 public:
  Print(string message) : msg(move(message)) {}
  virtual int execute() override {cout<<msg<<endl; return 2;}

};

#endif //ALGORITHMICPROGRAMMINGPROJECT__PRINT_H_
