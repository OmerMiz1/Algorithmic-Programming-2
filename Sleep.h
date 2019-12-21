//
// Created by omer on 21/12/2019.
//

#ifndef ALGORITHMICPROGRAMMINGPROJECT__SLEEP_H_
#define ALGORITHMICPROGRAMMINGPROJECT__SLEEP_H_

#include <zconf.h>
#include <string>
#include <iostream>
#include "Command.h"
using namespace std;

class Sleep : public Command {
 private:
  int d;

 public:
  Sleep(string duration) {
    try {
      d = stoi(duration);
    } catch(const char* e) {
      cout<<e<<endl;
    }
  };
  virtual int execute() override {sleep(d); return 2;}
};

#endif //ALGORITHMICPROGRAMMINGPROJECT__SLEEP_H_
