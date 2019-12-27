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
  //TODO if string comes with "" than its a string, otherwise it a value.
  /*need to make sure we handle these cases appropriately, make sure the lexer
  doesnt throw away the "".*/
  int execute(list<string>::iterator it) override {
    ++it;
    cout<<*it<<endl;
    return 2;
  }

};

#endif //ALGORITHMICPROGRAMMINGPROJECT__PRINT_H_
